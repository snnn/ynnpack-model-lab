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
