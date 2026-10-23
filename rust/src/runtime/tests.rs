// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use crate::compiler::*;
use sha2::{Digest, Sha256};
extern "C" {
    fn lab_test_live_handles(graphs: *mut usize, assets: *mut usize);
    fn lab_test_fail_compile_after(successful: i32);
}
fn live() -> (usize, usize) {
    let (mut graphs, mut assets) = (0, 0);
    unsafe {
        lab_test_live_handles(&mut graphs, &mut assets);
    }
    (graphs, assets)
}
pub(crate) fn preparation() -> Result<()> {
    let baseline = live();
    let root = std::env::temp_dir().join(format!("ynn-prepare-{}", std::process::id()));
    std::fs::create_dir(&root)?;
    let weights = [1.0f32, 2.0, 3.0, 4.0]
        .into_iter()
        .flat_map(f32::to_le_bytes)
        .collect::<Vec<_>>();
    std::fs::write(root.join("weights.bin"), &weights)?;
    let assets = AssetStore::open(&root, &root)?;
    let data = crate::plan::Data { path: "@parameters/weights.bin".into(), bytes: weights.len(), sha256: format!("{:x}", Sha256::digest(&weights)) };
    assets.assets.verify_embedding(&data)?;
    assert!(!assets.assets.verify(&data)?.is_null());
    let mut bad_embedding = data.clone();
    bad_embedding.sha256 = "0".repeat(64);
    assert!(assets.assets.verify_embedding(&bad_embedding).is_err());
    let fresh = AssetStore::open(&root, &root)?;
    assert!(fresh.assets.verify_embedding(&bad_embedding).is_err());
    drop(fresh);
    drop(assets);
    let ty = TensorType {
        shape: vec![Expr::Known(4)],
        ..Default::default()
    };
    let mut builder = compiler::GraphBuilder::default();
    builder.input("x", ty.clone())?;
    builder.constant(
        "w",
        ty.clone(),
        Asset {
            path: "@parameters/weights.bin".into(),
            bytes: weights.len(),
            sha256: format!("{:x}", Sha256::digest(&weights)),
        },
    )?;
    builder.value(
        "c",
        Value {
            tensor: ty,
            constant: true,
            floats: vec![1.0.into(); 4],
            ..Default::default()
        },
    )?;
    builder.operation(Op::Add, &["x", "w"], "sum", Attributes::default())?;
    builder.operation(Op::Add, &["sum", "c"], "y", Attributes::default())?;
    let graph = builder.finish(&["y"]);
    let program = Program {
        phases: BTreeMap::from([("prefill".into(), graph.clone()), ("decode".into(), graph)]),
        ..Default::default()
    };
    let make = |p: &Program| {
        prepare(
            p,
            AssetStore::open(&root, &root)?,
            PrepareOptions {
                threads: 1,
                ..Default::default()
            },
        )
    };

    // The tensor contract must bind exactly the graph interface before native
    // construction. Keep storage alive independently of the source contract.
    let binding = |name: &str| tensor::TensorBinding {
        name: name.into(), dtype: "fp32".into(), shape: vec![4],
    };
    let phase = tensor::TensorPhase {
        inputs: vec![binding("x")], outputs: vec![binding("y")],
    };
    let spec = tensor::TensorExecutionSpec {
        format: "ynn-tensor-execution".into(), version: 1,
        graphs: BTreeMap::from([("prefill".into(), phase.clone()), ("decode".into(), phase)]),
    };
    let tensor_prepare = |spec: &tensor::TensorExecutionSpec| prepare(
        &program, AssetStore::open(&root, &root)?,
        PrepareOptions { threads: 1, tensors: Some(spec), ..Default::default() },
    );
    for invalid in 0..5 {
        let mut bad = spec.clone();
        let phase = bad.graphs.get_mut("decode").unwrap();
        match invalid {
            0 => phase.outputs.clear(),
            1 => phase.inputs[0].shape = vec![5],
            2 => phase.inputs[0].dtype = "int4".into(),
            3 => phase.outputs[0].name = "x".into(),
            _ => { bad.graphs.remove("decode"); },
        }
        assert!(tensor_prepare(&bad).is_err());
        assert_eq!(live(), baseline);
    }
    // Consuming source input must release it before any native graph exists.
    // Prepared constants and mappings must remain valid for later invocation.
    struct OwnedInput {
        program: Program,
        dropped: Rc<std::cell::Cell<bool>>,
        live_graphs: usize,
    }
    impl std::borrow::Borrow<Program> for OwnedInput {
        fn borrow(&self) -> &Program { &self.program }
    }
    impl Drop for OwnedInput {
        fn drop(&mut self) {
            assert_eq!(live().0, self.live_graphs);
            self.dropped.set(true);
        }
    }
    let dropped = Rc::new(std::cell::Cell::new(false));
    let prepared = prepare(
        OwnedInput { program: program.clone(), dropped: dropped.clone(), live_graphs: baseline.0 },
        AssetStore::open(&root, &root)?,
        PrepareOptions { threads: 1, tensors: Some(&spec), ..Default::default() },
    )?;
    assert!(dropped.get());
    let mut tensors = tensor::TensorSession::from_prepared(prepared)?;
    drop(spec);
    assert!(tensors.input_mut("decode", "y").is_err());
    assert!(tensors.output("decode", "x").is_err());
    assert!(tensors.invoke("missing").is_err());
    tensors.input_f32_mut("decode", "x")?.copy_from_slice(&[2., 4., 6., 8.]);
    tensors.invoke("decode")?;
    assert_eq!(tensors.output_f32("decode", "y")?, &[4., 7., 10., 13.]);
    tensors.input_f32_mut("decode", "x")?.fill(0.);
    tensors.invoke("decode")?;
    assert_eq!(tensors.output_f32("decode", "y")?, &[2., 3., 4., 5.]);
    drop(tensors);
    assert_eq!(live(), baseline);

    // Both stored representations carry an identity. A valid compressed member
    // followed by another member or junk must not hide unvalidated content.
    use std::io::Write;
    let bytes = serde_json::to_vec(&program)?;
    let execution = b"{}";
    std::fs::write(root.join("execution.json"), execution)?;
    let write_package = |file: &str, stored: &[u8]| -> Result<()> {
        std::fs::write(root.join(file), stored)?;
        std::fs::write(root.join("model.json"), serde_json::to_vec(&serde_json::json!({
            "package": {"format":"ynn-semantic-package", "version":1,
                "program.json":{"file":file,"bytes":stored.len(),"sha256":format!("{:x}",Sha256::digest(stored))},
                "execution.json":{"bytes":execution.len(),"sha256":format!("{:x}",Sha256::digest(execution))}}
        }))?)?;
        Ok(())
    };
    write_package("program.json", &bytes)?;
    assert_eq!(package::ModelPackage::read(&root)?.program.phases.len(), 2);
    let mut encoder = flate2::write::GzEncoder::new(Vec::new(), flate2::Compression::default());
    encoder.write_all(&bytes)?;
    let compressed = encoder.finish()?;
    write_package("program.json.gz", &compressed)?;
    assert_eq!(package::ModelPackage::read(&root)?.program.phases.len(), 2);
    std::fs::write(root.join("execution.json"), b"[]")?;
    assert!(package::ModelPackage::read(&root).is_err());
    std::fs::write(root.join("execution.json"), execution)?;
    let mut trailing = compressed.clone();
    trailing.extend_from_slice(&compressed);
    write_package("program.json.gz", &trailing)?;
    assert!(package::ModelPackage::read(&root).is_err());
    write_package("program.json.gz", &compressed[..compressed.len()-4])?;
    assert!(package::ModelPackage::read(&root).is_err());
    for file in ["program.json", "program.json.gz", "execution.json", "model.json"] {
        std::fs::remove_file(root.join(file))?;
    }

    let mut bad = program.clone();
    bad.version = 999;
    assert!(make(&bad).is_err());
    assert_eq!(live(), baseline);
    let mut bad = program.clone();
    bad.phases
        .get_mut("decode")
        .unwrap()
        .values
        .get_mut("w")
        .unwrap()
        .data
        .as_mut()
        .unwrap()
        .sha256 = "0".repeat(64);
    assert!(make(&bad).is_err());
    assert_eq!(live(), baseline);
    let mut bad = program.clone();
    bad.phases
        .get_mut("prefill")
        .unwrap()
        .values
        .get_mut("w")
        .unwrap()
        .data
        .as_mut()
        .unwrap()
        .path = "@parameters/missing.bin".into();
    assert!(make(&bad).is_err());
    assert_eq!(live(), baseline);
    // The second native compile fails after the first graph has been prepared.
    unsafe {
        lab_test_fail_compile_after(1);
    }
    let error = make(&program).err().unwrap();
    assert!(error.message.contains("later-phase"));
    assert_eq!(live(), baseline);
    for _ in 0..32 {
        drop(make(&program)?);
        assert_eq!(live(), baseline);
    }

    let mut prepared = make(&program)?;
    assert_eq!(prepared.stats.compiler_calls, 1);
    assert_eq!(prepared.stats.prepared_phases, 2);
    assert!(prepared.stats.generated_constant_bytes > 0);
    drop(program);
    drop(weights); // No retained reference to source or compile temporaries.
    std::fs::remove_file(root.join("weights.bin"))?;
    std::fs::remove_dir(&root)?; // Both the mapping and generated buffers must survive.
    let input = ffi::Buffer::new(4, 2.0f32);
    let output = ffi::Buffer::new(4, 0.0f32);
    for graph in prepared.graphs.values_mut() {
        unsafe {
            graph.bind(c"x", &input, &[4], false)?;
            graph.bind(c"y", &output, &[], false)?;
        }
        for _ in 0..8 {
            graph.run()?;
            assert_eq!(&*output, &[4., 5., 6., 7.]);
        }
    }
    assert_eq!(prepared.stats.compiler_calls, 1);
    drop(prepared);
    assert_eq!(live(), baseline);
    println!("Runtime preparation: bad inputs, atomic failure, constants/mappings and repeated drop passed");
    Ok(())
}
