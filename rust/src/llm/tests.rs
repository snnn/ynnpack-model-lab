// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::{package::Package,session::Session};
use crate::{frontend::Options,Result};
use std::path::Path;

pub(super) fn run(args:&[String])->Result<()> {
    runtime_session()?;
    let root=Path::new(&args[1]);
    let mut options=Options::parse(&["test".into(),format!("--bundle_dir={}",root.display()),
        format!("--parameter_dir={}/parameters",root.display()),"--cache_capacity=8".into(),
        "--prefill_rows=1".into(),"--cases_file=unused.tsv".into(),"--output_dir=unused-output".into(),"--num_threads=1".into()],true)?.unwrap();
    let mut session=Session::load(root,root,&root.join("parameters"),Package::read(root)?,&options)?;
    session.invoke(&[0],false,None)?;
    session.invoke(&[1],true,None)?;
    assert_eq!(&*session.logits,&[3.,6.,9.,12.]);
    assert_eq!(session.position,2);
    if let Some(growth) = args.get(2) {
        let larger=Path::new(growth);
        let replacement=Session::load(larger,larger,&larger.join("parameters"),Package::read(larger)?,&options)?;
        let old=session.caches.iter().map(|(_,r)|r.data().to_vec()).collect::<Vec<_>>();
        session.reserve_capacity(replacement)?;
        assert_eq!(session.position,2);
        assert_eq!(&*session.logits,&[3.,6.,9.,12.]);
        for (i,(_,r)) in session.caches.iter().enumerate() {
            assert_eq!(r.status()?[0],2);
            assert_eq!(&r.data()[..32],&old[i][..32]);
        }
    }
    // Rejected calls must leave the current state usable and unchanged.
    for (tokens,decode) in [(&[][..],true),(&[4][..],true),(&[1,2][..],true),(&[1][..],false)] {
        assert!(session.invoke(tokens,decode,None).is_err());
        assert_eq!(session.position,2);
    }
    session.invoke(&[2],true,None)?;
    assert_eq!(&*session.logits,&[7.,14.,21.,28.]);
    // Reset restores both buffers, including after a failed native execution.
    session.reset()?;
    session.invoke(&[1],true,None)?;
    assert_eq!(&*session.logits,&[2.,4.,6.,8.]);
    assert!(session.invoke(&[3],true,None).is_err());
    assert!(session.invoke(&[0],true,None).is_err());
    session.reset()?;
    for _ in 0..session.package.capacity {session.invoke(&[0],true,None)?;}
    let cap=session.package.capacity as f32;
    assert_eq!(&*session.logits,&[cap,2.*cap,3.*cap,4.*cap]);
    assert!(session.invoke(&[0],true,None).is_err());
    session.reset()?;
    session.invoke(&[2],true,None)?;
    assert_eq!(&*session.logits,&[4.,8.,12.,16.]);
    // Profiles must be independently readable, including the very first step.
    let output=std::env::temp_dir().join(format!("ynn-llm-profile-{}-{}",std::process::id(),
        std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).unwrap().as_nanos()));
    std::fs::create_dir(&output).unwrap();
    options.output_dir=output.to_string_lossy().into_owned();
    options.profile_execution="all".into();
    let mut profiled=Session::load(root,root,&root.join("parameters"),Package::read(root)?,&options)?;
    profiled.invoke(&[0],false,Some(("first",0,0)))?;
    profiled.invoke(&[1],true,Some(("first",0,0)))?;
    assert_eq!(&*profiled.logits,&[3.,6.,9.,12.]);
    drop(profiled); // Flush each phase's output stream before reading it.
    for phase in ["prefill","decode"] {
        let text=std::fs::read_to_string(output.join(format!("{phase}_execution_profile.jsonl"))).unwrap();
        let records=text.lines().map(|s|serde_json::from_str::<serde_json::Value>(s).unwrap()).collect::<Vec<_>>();
        assert_eq!(records.len(),2);
        assert_eq!(records[0]["type"],"metadata");
        let calls=records[0]["calls"].as_array().unwrap();
        assert!(!calls.is_empty());
        assert_eq!(records[1]["type"],"step");
        assert_eq!(records[1]["phase"],phase);
        assert_eq!(records[1]["step"],0);
        assert_eq!(records[1]["complete"],true);
        let events=records[1]["events"].as_array().unwrap();
        assert!(!events.is_empty());
        assert!(events.iter().all(|e|calls.iter().any(|c|c["id"]==e[1])));
    }
    std::fs::remove_dir_all(output).unwrap();
    println!("Session reset, transitions, bounds, rejection, poisoning and profile metadata passed");Ok(())
}

fn runtime_session() -> Result<()> {
    use crate::{compiler::*, runtime::*};
    use std::collections::BTreeMap;
    let mut b = GraphBuilder::default();
    b.input("x", TensorType { shape: vec![Expr::Known(1)], ..Default::default() })?;
    b.value("bias", Value { tensor: TensorType { shape: vec![Expr::Known(1),Expr::Known(4)], ..Default::default() },
        constant: true, floats: vec![1.0.into(),2.0.into(),3.0.into(),4.0.into()], ..Default::default() })?;
    b.operation(Op::Add, &["x","bias"], "logits", Attributes::default())?;
    let g = b.finish(&["logits"]);
    let program = Program { phases: BTreeMap::from([("prefill".into(),g.clone()),("decode".into(),g)]), ..Default::default() };
    let phase = serde_json::json!({"logits":null,"row_policy":"valid","scalars":{},
        "inputs":[{"name":"x","dtype":"fp32","shape":["rows"],"recipe":{"kind":"positions"}}]});
    let mut value = serde_json::json!({"format":"ynn-llm-execution","model":"tiny-semantic",
        "capacity":8,"prefill_rows":1,"vocabulary":4,"prefill_after_decode":false,
        "graphs":{"prefill":phase,"decode":phase},"resources":[],"fixed_states":[],"embeddings":{}});
    value["graphs"]["decode"]["logits"] = serde_json::json!("logits");
    value["graphs"]["prefill"]["logits"] = serde_json::json!("logits");
    let spec: ExecutionSpec = serde_json::from_value(value)?;
    let make = |spec: &ExecutionSpec| prepare(&program,AssetStore::open(Path::new(""),Path::new(""))?,
        PrepareOptions { threads:1, execution:Some(spec), ..Default::default() });
    let mut wrong = spec.clone(); wrong.vocabulary = 5;
    assert!(make(&wrong).is_err());
    assert!(Session::from_prepared(make(&spec)?,wrong).is_err());
    let mut session = Session::from_prepared(make(&spec)?,spec)?;
    drop(program);
    session.invoke(&[0],false,None)?;
    session.invoke(&[1],true,None)?;
    assert_eq!(session.logits(),&[2.,3.,4.,5.]);
    assert_eq!(session.preparation.compiler_calls,1);
    assert!(session.invoke(&[4],true,None).is_err());
    for _ in 0..6 { session.invoke(&[0],true,None)?; }
    assert_eq!(session.position(),8);
    assert!(session.invoke(&[0],true,None).is_err());
    session.reset()?;
    session.invoke(&[0],true,None)?;
    assert_eq!(session.logits(),&[1.,2.,3.,4.]);
    Ok(())
}
