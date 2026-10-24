// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use std::collections::BTreeMap;
fn ty(shape: &[i64]) -> TensorType {
    TensorType {
        shape: shape.iter().copied().map(Expr::Known).collect(),
        ..TensorType::default()
    }
}
fn program(g: Graph) -> Program {
    Program {
        phases: BTreeMap::from([("model".into(), g)]),
        ..Program::default()
    }
}
#[test]
fn phase_options_are_local_and_reject_unknown_phases() {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3, 4])).unwrap();
    b.operation(Op::Reshape, &["x"], "y", Attributes { shape: ty(&[6, 4]).shape, ..Default::default() }).unwrap();
    let graph = b.finish(&["y"]);
    let mut p = Program { phases: BTreeMap::from([("prefill".into(), graph.clone()), ("decode".into(), graph)]), ..Default::default() };
    let original = compile(&p).unwrap();
    p.phase_options.insert("prefill".into(), CompileOptions { target_views: false, ..Default::default() });
    let changed = compile(&p).unwrap();
    assert_eq!(original.plans["decode"], changed.plans["decode"]);
    assert_ne!(original.plans["prefill"], changed.plans["prefill"]);
    p.phase_options.insert("typo".into(), CompileOptions::default());
    assert!(compile(&p).is_err());
}
fn simple(op: Op) -> Graph {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3])).unwrap();
    b.operation(op, &["x"], "y", Attributes::default()).unwrap();
    b.finish(&["y"])
}
#[test]
fn decomposition_preserves_completion_join() {
    let mut g = simple(Op::Softmax);
    g.nodes[0].completes = vec!["ready".into()];
    g.completions = vec!["ready".into()];
    let c = compile(&program(g)).unwrap();
    let g = &c.graphs["model"];
    assert!(g.nodes.iter().all(|n| n.op != Op::Softmax));
    assert_eq!(g.nodes.last().unwrap().completes, ["ready"]);
    assert!(g.nodes.last().unwrap().waits.len() > 2);
    assert!(crate::plan_text::parse(&c.plans["model"])
        .unwrap()
        .commands
        .iter()
        .any(|c| c.op == crate::plan::Op::CompletionOutput));
}
#[test]
fn result_contracts_and_duplicate_inputs_fail_without_mutation() {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3])).unwrap();
    assert!(b.input("x", ty(&[99])).is_err());
    assert_eq!(b.graph.values["x"].tensor.shape, ty(&[2, 3]).shape);
    b.value(
        "y",
        Value {
            tensor: ty(&[9]),
            ..Value::default()
        },
    )
    .unwrap();
    assert!(b
        .operation(Op::Square, &["x"], "y", Attributes::default())
        .is_err());
    assert!(b.graph.nodes.is_empty());
}
#[test]
fn shape_control_requires_explicit_supported_contract() {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3])).unwrap();
    assert!(b
        .operation(Op::ResourceView, &["x"], "view", Attributes::default())
        .is_err());
}
#[test]
fn target_views_do_not_escape_as_source_ir() {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3, 4])).unwrap();
    b.operation(
        Op::Reshape,
        &["x"],
        "y",
        Attributes {
            shape: ty(&[6, 4]).shape,
            ..Attributes::default()
        },
    )
    .unwrap();
    let c = compile(&program(b.finish(&["y"]))).unwrap();
    assert!(crate::plan_text::parse(&c.plans["model"])
        .unwrap()
        .commands
        .iter()
        .any(|c| c.op == crate::plan::Op::FuseDims));
}
fn call_graph(body: Graph, tensor: TensorType) -> Graph {
    let mut g = Graph::default();
    g.values.insert(
        "x".into(),
        Value {
            tensor: tensor.clone(),
            ..Value::default()
        },
    );
    g.inputs = vec!["x".into()];
    g.values.insert(
        "y".into(),
        Value {
            tensor,
            ..Value::default()
        },
    );
    g.outputs = vec!["y".into()];
    g.nodes = vec![Node {
        op: Op::Call,
        inputs: vec!["x".into()],
        outputs: vec!["y".into()],
        attributes: Attributes {
            call: Some(Call {
                function: "f".into(),
                indices: BTreeMap::new(),
            }),
            ..Attributes::default()
        },
        scope: "caller".into(),
        waits: vec![],
        completes: vec![],
    }];
    g.functions.insert("f".into(), body);
    g
}
#[test]
fn function_can_return_argument_or_immutable_constant() {
    let mut b = GraphBuilder::default();
    b.input("arg", ty(&[2, 3])).unwrap();
    let c = compile(&program(call_graph(b.finish(&["arg"]), ty(&[2, 3])))).unwrap();
    assert!(c.plans["model"].contains("Copy"));
    let mut b = GraphBuilder::default();
    b.input("arg", ty(&[2, 3])).unwrap();
    b.value(
        "literal",
        Value {
            tensor: ty(&[2, 3]),
            floats: vec![2.0.into(); 6],
            constant: true,
            ..Value::default()
        },
    )
    .unwrap();
    let c = compile(&program(call_graph(b.finish(&["literal"]), ty(&[2, 3])))).unwrap();
    assert_eq!(c.assets.len(), 1);
}
#[test]
fn packed_constraints_flow_from_caller_into_callee() {
    let tensor = TensorType {
        dtype: Dtype::I4,
        shape: vec![Expr::Known(4)],
        quant: None,
    };
    let mut b = GraphBuilder::default();
    b.input("arg", tensor.clone()).unwrap();
    b.operation(Op::Copy, &["arg"], "out", Attributes::default())
        .unwrap();
    let mut g = call_graph(b.finish(&["out"]), tensor.clone());
    g.values.insert(
        "reversed".into(),
        Value {
            tensor,
            ..Value::default()
        },
    );
    g.nodes.push(Node {
        op: Op::Reverse,
        inputs: vec!["y".into()],
        outputs: vec!["reversed".into()],
        attributes: Attributes {
            axes: vec![0],
            ..Attributes::default()
        },
        scope: String::new(),
        waits: vec![],
        completes: vec![],
    });
    g.outputs = vec!["reversed".into()];
    let c = compile(&program(g)).unwrap();
    let line = c.plans["model"]
        .lines()
        .find(|l| l.contains("fn template"))
        .unwrap();
    assert!(line.contains("storage<packed_i4[4]>"));
    assert_eq!(c.report["model"]["packed_storage"]["x"]["bits"], 4);
}
#[test]
fn native_templates_lift_exact_literals_and_assets() {
    let mut g = Graph::default();
    for (i, scale) in [0.25, 0.75].iter().enumerate() {
        let mut b = GraphBuilder::default();
        b.input("x", ty(&[2, 3])).unwrap();
        b.value(
            "weight",
            Value {
                tensor: ty(&[1]),
                floats: vec![(*scale).into()],
                constant: true,
                ..Value::default()
            },
        )
        .unwrap();
        b.operation(Op::Mul, &["x", "weight"], "y", Attributes::default())
            .unwrap();
        let name = format!("f{i}");
        let x = format!("x{i}");
        let y = format!("y{i}");
        g.values.insert(
            x.clone(),
            Value {
                tensor: ty(&[2, 3]),
                ..Value::default()
            },
        );
        g.values.insert(
            y.clone(),
            Value {
                tensor: ty(&[2, 3]),
                ..Value::default()
            },
        );
        g.inputs.push(x.clone());
        g.outputs.push(y.clone());
        g.functions.insert(name.clone(), b.finish(&["y"]));
        g.nodes.push(Node {
            op: Op::Call,
            inputs: vec![x],
            outputs: vec![y],
            attributes: Attributes {
                call: Some(Call {
                    function: name,
                    indices: BTreeMap::new(),
                }),
                ..Attributes::default()
            },
            scope: String::new(),
            waits: vec![],
            completes: vec![],
        });
    }
    let c = compile(&program(g)).unwrap();
    assert_eq!(c.plans["model"].matches("fn template").count(), 1);
    assert_eq!(c.assets.len(), 2);
}
#[test]
fn malformed_semantic_programs_return_errors() {
    let base = simple(Op::Softmax);
    let mut cases = vec![];
    let mut g = base.clone();
    g.nodes[0].inputs.clear();
    cases.push(g);
    let mut g = base.clone();
    g.nodes[0].outputs.clear();
    cases.push(g);
    let mut g = base.clone();
    g.nodes[0].inputs[0] = "missing".into();
    cases.push(g);
    let mut g = base.clone();
    g.nodes[0].waits = vec!["undefined".into()];
    cases.push(g);
    let mut g = base;
    g.values.get_mut("x").unwrap().tensor.shape = vec![Expr::Symbol(99)];
    cases.push(g);
    for g in cases {
        let result = std::panic::catch_unwind(|| compile(&program(g)));
        assert!(result.is_ok());
        assert!(result.unwrap().is_err());
    }
}
#[test]
fn failed_package_write_publishes_nothing() {
    let mut c = compile(&program(simple(Op::Square))).unwrap();
    c.assets.insert("../bad".into(), vec![1]);
    let dir = std::env::temp_dir().join(format!("ynn-compiler-atomic-{}", std::process::id()));
    assert!(!dir.exists());
    assert!(c.write(&dir).is_err());
    assert!(!dir.exists());
}

#[test]
fn malformed_author_operations_are_errors_not_panics() {
    for (op, axes) in [
        (Op::Select, vec![]),
        (Op::Concat, vec![]),
        (Op::ExpandDims, vec![2, 2]),
        (Op::BroadcastLike, vec![1]),
    ] {
        let result = std::panic::catch_unwind(|| {
            let mut b = GraphBuilder::default();
            b.input("x", ty(&[2])).unwrap();
            b.operation(
                op,
                &["x"],
                "bad",
                Attributes {
                    axes,
                    ..Attributes::default()
                },
            )
        });
        assert!(result.is_ok());
        if op != Op::Concat {
            assert!(result.unwrap().is_err());
        }
    }
}
#[test]
fn conflicting_constant_hints_cannot_change_asset_meaning() {
    let mut b = GraphBuilder::default();
    b.value(
        "c",
        Value {
            tensor: ty(&[1]),
            constant: true,
            floats: vec![1.0.into()],
            data: Some(Asset {
                path: "@parameters/test.bin".into(),
                bytes: 4,
                sha256: "0".repeat(64),
            }),
            ..Value::default()
        },
    )
    .unwrap();
    assert!(compile(&program(b.finish(&["c"])))
        .unwrap_err()
        .message
        .contains("disagree"));
}

#[test]
fn target_created_equivalence_gets_exact_cleanup() {
    let mut b = GraphBuilder::default();
    b.input("x", ty(&[2, 3])).unwrap();
    b.value(
        "zero",
        Value {
            tensor: ty(&[1]),
            constant: true,
            floats: vec![0.0.into()],
            ..Value::default()
        },
    )
    .unwrap();
    b.operation(Op::Relu, &["x"], "relu", Attributes::default())
        .unwrap();
    b.operation(
        Op::Maximum,
        &["x", "zero"],
        "maximum",
        Attributes::default(),
    )
    .unwrap();
    b.operation(Op::Add, &["relu", "maximum"], "out", Attributes::default())
        .unwrap();
    let c = compile(&program(b.finish(&["out"]))).unwrap();
    assert_eq!(
        c.graphs["model"]
            .nodes
            .iter()
            .filter(|n| n.op == Op::Maximum)
            .count(),
        1
    );
}
#[test]
fn phases_reject_incompatible_persistent_storage_before_publication() {
    fn owner(n: i64) -> Graph {
        let mut b = GraphBuilder::default();
        b.input("state", ty(&[n, 4])).unwrap();
        b.graph.resources.push(Resource {
            name: "shared".into(),
            owner: "state".into(),
            axis: 0,
            entry: Expr::Known(0),
            strides: vec![],
            selected: false,
        });
        b.finish(&["state"])
    }
    let p = Program {
        phases: BTreeMap::from([("prefill".into(), owner(8)), ("decode".into(), owner(9))]),
        ..Program::default()
    };
    assert!(compile(&p).unwrap_err().message.contains("cross-phase"));
}

#[test]
fn dynamic_matmul_validates_selected_rhs_head_before_broadcasting() {
    for (lhs, transpose_rhs, expected) in [
        ([1, 3, 1, 8], true, [1, 3, 1, 16]),
        ([1, 1, 3, 16], false, [1, 1, 3, 8]),
    ] {
        let mut b = GraphBuilder::default();
        b.input("lhs", ty(&lhs)).unwrap();
        let mut rhs = ty(&[1, 2, 16, 8]);
        rhs.dtype = Dtype::I8;
        rhs.quant = Some(Quantization {
            scales: vec![0.125.into()],
            zeros: vec![0],
            ..Quantization::default()
        });
        b.input("rhs", rhs).unwrap();
        let attributes = Attributes {
            adj_y: transpose_rhs,
            integers: vec![1],
            ..Attributes::default()
        };
        b.operation(Op::DynamicMatmul, &["lhs", "rhs"], "y", attributes)
            .unwrap();
        assert_eq!(b.graph.values["y"].tensor, ty(&expected));
        let mut p = program(b.finish(&["y"]));
        compile(&p).unwrap();
        p.phases.get_mut("model").unwrap().nodes[0]
            .attributes
            .integers = vec![2];
        assert!(compile(&p)
            .unwrap_err()
            .message
            .contains("head selection bounds"));
        p.phases.get_mut("model").unwrap().nodes[0]
            .attributes
            .integers = vec![0];
        p.phases
            .get_mut("model")
            .unwrap()
            .values
            .get_mut("lhs")
            .unwrap()
            .tensor
            .dtype = Dtype::I8;
        assert!(compile(&p).unwrap_err().message.contains("FP32 lhs"));
    }
}

#[test]
fn low_precision_extended_activations_fail_before_emission() {
    for op in [Op::Prelu, Op::HardSwish] {
        for dtype in [Dtype::F16, Dtype::Bf16] {
            let mut b = GraphBuilder::default();
            let mut t = ty(&[2, 3]);
            t.dtype = dtype;
            b.input("x", t.clone()).unwrap();
            b.input("slope", t).unwrap();
            let inputs = if op == Op::Prelu {
                vec!["x", "slope"]
            } else {
                vec!["x"]
            };
            b.operation(op, &inputs, "y", Attributes::default())
                .unwrap();
            assert!(compile(&program(b.finish(&["y"])))
                .unwrap_err()
                .message
                .contains("FP32"));
        }
    }
}
#[test]
fn native_linear_parameters_cannot_diverge_from_quantization() {
    for name in ["blockwise_fc/blockwise_7_64", "weight_only/linear4"] {
        let path = std::path::Path::new(env!("CARGO_MANIFEST_DIR"))
            .join(format!("../tests/compiler/fixtures/{name}.program.ynn"));
        let p = crate::program_text::read(&path).unwrap();
        let c = compile(&p).unwrap();
        let mut p = Program {
            phases: c.graphs,
            ..p
        };
        let node = p
            .phases
            .values_mut()
            .flat_map(|g| &mut g.nodes)
            .find(|n| {
                matches!(
                    n.op,
                    Op::BlockwiseFullyConnected | Op::NativeWeightOnlyLinear
                )
            })
            .unwrap();
        node.attributes.integers = vec![999];
        assert!(compile(&p).unwrap_err().message.contains("group size"));
    }
}
#[test]
fn quantized_results_publish_parameter_companions() {
    let p = crate::program_text::read(&std::path::Path::new(env!("CARGO_MANIFEST_DIR"))
        .join("../tests/compiler/fixtures/packed_quantization/quant_gather_i4.program.ynn")).unwrap();
    let c = compile(&p).unwrap();
    let g = &c.graphs["model"];
    let q = g.values["q"]
        .tensor
        .quant
        .as_ref()
        .unwrap()
        .parameters
        .as_ref()
        .unwrap();
    assert!(g.outputs.contains(&q.scales) && g.outputs.contains(&q.zeros));
    assert_eq!(
        c.report["model"]["quantization_companion_outputs"]["q"],
        serde_json::json!([q.scales, q.zeros])
    );
}

mod isle;
