// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::*;

fn square() -> Plan {
    crate::plan_text::parse(include_str!("../../../tests/rust/square.ynn")).unwrap()
}
fn validate(plan: Plan) -> Result<()> {
    plan.into_validated().map(|_| ())
}
#[test]
fn requires_supported_contracts_and_commands() {
    for field in 0..3 {
        let mut p = square();
        match field {
            0 => p.version = 2,
            1 => p.resource_contract = 2,
            _ => p.completion_contract = 2,
        }
        assert!(validate(p).is_err());
    }
    let mut p = square();
    p.commands[2].args[0] = Arg::Binary("unknown".into());
    assert!(validate(p).is_err());
    assert!(
        ValidatedPlan::from_bytes(br#"{"format":"ynnpack-construction-plan","version":1}"#)
            .is_err()
    );
}
#[test]
fn requires_declared_values_and_exactly_one_output_producer() {
    for id in [99, 1] {
        let mut p = square();
        p.commands[2].args[1] = Arg::Int(id);
        assert!(validate(p).is_err());
    }
    let mut p = square();
    p.commands.pop();
    assert!(validate(p).is_err());
    let mut p = square();
    p.commands.push(p.commands[2].clone());
    assert!(validate(p).is_err());
    let mut p = square();
    p.commands[1].args[1] = Arg::Text("x".into());
    assert!(validate(p).is_err());
}
#[test]
fn requires_valid_constant_identity_size_and_path() {
    let mut p = square();
    p.commands[0].args[4] = Arg::Int(0);
    let data = Data {
        path: "@parameters/test.bin".into(),
        bytes: 16,
        sha256: "a".repeat(64),
    };
    p.commands[0].args[5] = Arg::Data(Some(data.clone()));
    assert!(validate(p.clone()).is_ok());
    for path in [
        "/absolute.bin",
        "../escape.bin",
        "@parameters/../escape",
        "",
    ] {
        let mut bad = p.clone();
        let mut d = data.clone();
        d.path = path.into();
        bad.commands[0].args[5] = Arg::Data(Some(d));
        assert!(validate(bad).is_err());
    }
    for bytes in [0, 4, 17] {
        let mut bad = p.clone();
        let mut d = data.clone();
        d.bytes = bytes;
        bad.commands[0].args[5] = Arg::Data(Some(d));
        assert!(validate(bad).is_err());
    }
    let mut d = data;
    d.sha256 = "unverified".into();
    p.commands[0].args[5] = Arg::Data(Some(d));
    assert!(validate(p).is_err());
}
#[test]
fn completion_dependencies_must_be_declared_and_balanced() {
    for waits in [vec![], vec!["unproduced".into()]] {
        let mut p = square();
        p.commands.push(RawCommand {
            op: Op::BeginOperation,
            args: vec![Arg::Texts(waits)],
        });
        assert!(validate(p).is_err());
    }
}
#[test]
fn overflowing_axis_attributes_are_rejected_without_panicking() {
    let mut p = square();
    p.commands[2] = RawCommand {
        op: Op::FuseDims,
        args: vec![
            Arg::Int(0),
            Arg::Int(1),
            Arg::Int(i64::MAX),
            Arg::Int(i64::MAX),
        ],
    };
    assert!(validate(p).is_err());
}
#[test]
fn checked_invocation_guards_protect_only_their_own_arithmetic() {
    let source = r#"ynn 1 resource_contract=1 completion_contract=1 {
      input x: fp32[1]; output x;
      dim p = parameter("position") in 0..=9223372036854775807;
      require (2 * p) <= 4;
    }"#;
    assert!(crate::plan_text::check(source).is_err());
    let guarded = source.replace("require", "let bound = checked(2 * p); require");
    assert!(crate::plan_text::check(&guarded).is_ok());
    assert!(
        crate::plan_text::check(&guarded.replace("require (2 * p)", "require (2 + p)")).is_err()
    );
}
#[test]
fn expressions_reject_unbound_symbols_overflow_and_invalid_division() {
    let symbols = HashMap::from([(1, (-7, 9)), (2, (2, 3))]);
    let bounds = |expr: Expr| expr.bounds(&symbols, &mut 4096, 0);
    assert_eq!(
        bounds(Expr::FloorDiv(vec![Expr::Symbol(1), Expr::Symbol(2)])).unwrap(),
        (-4, 4)
    );
    assert_eq!(
        bounds(Expr::CeilDiv(vec![Expr::Symbol(1), Expr::Symbol(2)])).unwrap(),
        (-3, 5)
    );
    assert!(bounds(Expr::Symbol(3)).is_err());
    assert!(bounds(Expr::Add(vec![Expr::Known(i64::MAX), Expr::Known(1)])).is_err());
    assert!(bounds(Expr::Mul(vec![Expr::Known(i64::MIN), Expr::Known(-1)])).is_err());
    assert!(bounds(Expr::FloorDiv(vec![Expr::Known(1), Expr::Known(0)])).is_err());
    assert!(bounds(Expr::CeilDiv(vec![Expr::Known(1), Expr::Symbol(1)])).is_err());
    assert!(bounds(Expr::Min(vec![])).is_err());
}

#[test]
fn validates_all_published_plans_without_model_weights() {
    let models = Path::new(env!("CARGO_MANIFEST_DIR")).join("../models");
    for model in [
        "resnet18",
        "resnet34",
        "resnet50",
        "resnet101",
        "resnet152",
        "resnext50_32x4d",
        "wide_resnet50_2",
        "mobilenet_v2",
    ] {
        ValidatedPlan::read(
            &models
                .join("vision")
                .join(model)
                .join("generated/graph.ynn"),
        )
        .unwrap_or_else(|e| panic!("{model}: {e}"));
    }
    let mut packages = Vec::new();
    for model in ["gemma4_e2b", "gemma4_e4b"] {
        packages.push(models.join(model).join("generated"));
        for profile in ["fp32_rows", "int8_batch", "int8_rows"] {
            packages.push(models.join(model).join("attention").join(profile));
        }
    }
    for profile in [
        "hf_static_int8_published_kv",
        "hf_fp32_int8_published_kv",
        "hf_bf16",
        "hf_bf16_int8_raw_kv",
        "hf_bf16_int8_published_kv",
    ] {
        packages.push(models.join("gemma4_e2b_hf/generated").join(profile));
    }
    for package in packages {
        for phase in ["prefill", "decode"] {
            let path = package.join(format!("gemma4_{phase}.ynn"));
            ValidatedPlan::read(&path).unwrap_or_else(|e| panic!("{}: {e}", path.display()));
        }
    }
}
