// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
fn fixture(name: &str) -> Program {
    let path = std::path::Path::new(env!("CARGO_MANIFEST_DIR"))
        .join("../tests/compiler/fixtures")
        .join(format!("{name}.program.json"));
    serde_json::from_slice(&std::fs::read(path).unwrap()).unwrap()
}
#[test]
fn attention_permissions_preserve_native_operation() {
    let base = fixture("ynnpack_attention/native_boolean_q1_regular");
    let compiled = compile(&base).unwrap();
    assert!(compiled
        .graphs
        .values()
        .all(|g| g.nodes.iter().all(|n| n.op != Op::Sdpa)));
    for denied in 0..4 {
        let mut p = base.clone();
        for g in p.phases.values_mut() {
            let n = g.nodes.iter_mut().find(|n| n.op == Op::Sdpa).unwrap();
            let a = n.attributes.attention.as_mut().unwrap();
            match denied {
                0 => a.reassociate = false,
                1 => a.reorder_reduction = false,
                2 => a.masked_nonfinite = false,
                _ => a.all_masked_nan = false,
            }
        }
        let result = compile(&p).unwrap();
        assert!(result
            .graphs
            .values()
            .all(|g| g.nodes.iter().any(|n| n.op == Op::Sdpa)));
    }
}
#[test]
fn vector_fc_bias_and_completion_lower_inside_functions() {
    for bias in [false, true] {
        let mut b = GraphBuilder::default();
        b.input("x", ty(&[3])).unwrap();
        b.input("w", ty(&[2, 3])).unwrap();
        let mut inputs = vec!["x", "w"];
        if bias {
            b.input("bias", ty(&[2])).unwrap();
            inputs.push("bias");
        }
        b.operation(Op::FullyConnected, &inputs, "y", Attributes::default())
            .unwrap();
        let mut g = b.finish(&["y"]);
        let lowered = lower::lower(&g, &CompileOptions::default()).unwrap();
        assert_eq!(lowered.values["y"].tensor.shape, ty(&[2]).shape);
        assert!(lowered.nodes.iter().all(|n| n.op != Op::FullyConnected));
        g.nodes[0].completes = vec!["done".into()];
        g.completions = vec!["done".into()];
        let lowered = lower::lower(&g, &CompileOptions::default()).unwrap();
        assert_eq!(lowered.nodes.last().unwrap().completes, ["done"]);
        let mut outer = Graph::default();
        outer.functions.insert("linear".into(), g);
        let lowered = lower::lower(&outer, &CompileOptions::default()).unwrap();
        assert!(lowered.functions["linear"]
            .nodes
            .iter()
            .all(|n| n.op != Op::FullyConnected));
        assert_eq!(
            lowered.functions["linear"].nodes.last().unwrap().completes,
            ["done"]
        );
    }
}
#[test]
fn quantized_fc_errors_do_not_fall_back_to_float() {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3])).unwrap();
    let mut w = ty(&[2, 3]);
    w.dtype = Dtype::I8;
    w.quant = Some(Quantization {
        axis: 0,
        scales: vec![0.5.into(), 0.25.into()],
        zeros: vec![0],
        ..Quantization::default()
    });
    b.input("w", w).unwrap();
    b.operation(Op::FullyConnected, &["x", "w"], "y", Attributes::default())
        .unwrap();
    let base = b.finish(&["y"]);
    lower::lower(&base, &CompileOptions::default()).unwrap();
    for (case, expected) in [
        (0, "FC requires symmetric per-output-channel weights"),
        (1, "FC channel scale count"),
        (2, "FC requires symmetric per-tensor activation scales"),
        (3, "Quantized FC bias lowering unsupported"),
    ] {
        let mut g = base.clone();
        match case {
            0 => {
                g.values
                    .get_mut("w")
                    .unwrap()
                    .tensor
                    .quant
                    .as_mut()
                    .unwrap()
                    .zeros = vec![1]
            }
            1 => {
                g.values
                    .get_mut("w")
                    .unwrap()
                    .tensor
                    .quant
                    .as_mut()
                    .unwrap()
                    .scales = vec![]
            }
            2 => {
                let x = &mut g.values.get_mut("x").unwrap().tensor;
                x.dtype = Dtype::I8;
                x.quant = Some(Quantization {
                    scales: vec![0.0.into()],
                    zeros: vec![0],
                    ..Quantization::default()
                });
            }
            _ => {
                g.values.insert(
                    "bias".into(),
                    Value {
                        tensor: ty(&[2]),
                        ..Value::default()
                    },
                );
                g.nodes[0].inputs.push("bias".into());
            }
        }
        let before = serde_json::to_value(&g).unwrap();
        assert_eq!(
            lower::lower(&g, &CompileOptions::default())
                .unwrap_err()
                .message,
            expected
        );
        assert_eq!(serde_json::to_value(&g).unwrap(), before);
    }
}
