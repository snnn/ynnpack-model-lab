// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::*;
use crate::plan::{Arg, Data, Expr, Op};
use serde_json::{json, Value};
const SQUARE: &str = include_str!("../../../tests/rust/square.ynn");
fn report(p: &Plan) -> Value {
    serde_json::to_value(p).unwrap()
}
fn roundtrip(plan: &Plan) -> String {
    let text = printer::print(plan).unwrap();
    assert_eq!(plan, &parse(&text).unwrap());
    assert_eq!(text, format(&text).unwrap());
    crate::plan::ValidatedPlan::from_bytes(text.as_bytes()).unwrap();
    text
}
fn parsed(body: &str) -> Plan {
    parse(&format!(
        "ynn 1 resource_contract=1 completion_contract=1 profiling=explicit {{ {body} }}"
    ))
    .unwrap()
}
fn error(source: &str, expected: &str) {
    let e = check(source).unwrap_err().to_string();
    assert!(e.contains(expected), "Expected {expected}: {e}");
    assert!(
        e.lines()
            .next()
            .unwrap()
            .split(':')
            .take(2)
            .all(|s| s.parse::<usize>().is_ok()),
        "{e}"
    );
}
#[test]
fn handwritten_square_matches_typed_commands() {
    let p = parse(SQUARE).unwrap();
    assert_eq!(p.value_count, 2);
    assert_eq!(
        p.commands.iter().map(|c| c.op).collect::<Vec<_>>(),
        [Op::Tensor, Op::Tensor, Op::Binary]
    );
    assert_eq!(
        p.commands[2].args,
        vec![
            Arg::Binary("multiply".into()),
            Arg::Int(0),
            Arg::Int(0),
            Arg::Int(1)
        ]
    );
    let text = roundtrip(&p);
    assert!(text.contains("let squared:"));
    assert!(!text.contains("Tensor("));
    assert_eq!(
        p,
        parse(&SQUARE.replace("mul(x, x)", "mul(rhs=x, lhs=x,)")).unwrap()
    );
    assert!(check(&inspect(SQUARE).unwrap()).is_err());
}
#[test]
fn fp32_comparisons_roundtrip_with_byte_boolean_results() {
    for operator in [
        "less",
        "less_equal",
        "greater",
        "greater_equal",
        "equal",
        "not_equal",
    ] {
        let source = format!(
            "ynn 1 resource_contract=1 completion_contract=1 {{
                input x: fp32[1]; input y: fp32[4];
                let result: uint8[4] = {operator}(x, y, shape=[4]);
                output result;
            }}"
        );
        let plan = parse(&source).unwrap();
        let text = roundtrip(&plan);
        assert!(text.contains(&format!("= {operator}(x, y, shape=[4])")));
        assert!(plan.commands.iter().any(|c| c.op == Op::Compare));
        for invalid in [
            source.replace("fp32", "int32"),
            source.replace("uint8[4]", "fp32[4]"),
            source.replace("shape=[4]", "shape=[4, 1]"),
            source.replace("x: fp32[1]", "x: fp32[1, 1]"),
        ] {
            error(&invalid, "Comparison");
        }
    }
}
#[test]
fn diagnoses_bad_syntax_references_and_types() {
    for (from, to, expected) in [
        ("ynn 1", "ynn 2", "Unsupported graph format"),
        (
            "completion_contract=1",
            "completion_contract=2",
            "Unsupported native contract",
        ),
        ("mul(x, x)", "mul(missing, x)", "Unknown tensor missing"),
        ("mul(x, x)", "mul(0, x)", "Expected a tensor reference"),
        ("mul(x, x)", "mul(x, x, lhs=x)", "Duplicate field lhs"),
        ("mul(x, x)", "mul(left=x, rhs=x)", "Unknown field left"),
        ("mul(x, x)", "mul(x)", "Missing field rhs"),
        ("mul(x, x)", "missing(x)", "Unknown operation missing"),
        ("[4]", "[9223372036854775808]", "signed 64-bit integer"),
        ("let squared", "let x", "Duplicate tensor x"),
        ("fp32", "bogus", "Unsupported dtype"),
        ("[4]", "[?]", "Unknown dimension ?"),
        ("output squared", "output missing", "Unknown output missing"),
        (
            "profiling=explicit",
            "profiling=magic",
            "Expected auto or explicit",
        ),
        ("mul(x, x)", "matmul(x, x)", "Missing field adjoint_lhs"),
    ] {
        let s = SQUARE.replacen(from, to, 1);
        assert_ne!(s, SQUARE, "{from}");
        error(&s, expected);
    }
    error(
        &SQUARE.replace(
            "let squared = mul(x, x)",
            "let squared: storage<fp32[4]> = mul(x, squared)",
        ),
        "producer",
    );
    for source in [
        "",
        "/* unclosed",
        "ynn 1 resource_contract=1 completion_contract=1 {",
        "λ",
        "\"unterminated",
    ] {
        assert!(check(source).is_err());
    }
    assert!(check(&format!("{SQUARE} trailing")).is_err());
}
#[test]
fn exact_float_bits_signed_indices_and_expression_trees_survive() {
    let plan = parsed(
        r#"
        input x: fp32[4];
        dim position = parameter("position") in 0..=100;
        @guard(message="position bound", mode="ordinary") require (position + -1) <= max(0, position);
        let squared: storage<fp32[4]> = polynomial(x, coefficients=[-0.0, bits("0000000000000001"), bits("3FF0000000000000")]);
        output squared;
        metadata { symbol position = 7; }
    "#,
    );
    let text = roundtrip(&plan);
    assert!(text.contains("symbol position = 7"));
    assert!(text.contains("(position + -1)"));
    assert!(text.contains("coefficients=[-0,"));
    for bits in ["7ff0000000000000", "7ff8000000000001", "1234"] {
        assert!(check(&text.replace("3FF0000000000000", bits)).is_err());
    }
    for replacement in [
        "unknown(position, -1)",
        "(missing + -1)",
        "(position // 0)",
        "(9223372036854775807 + 1)",
    ] {
        assert!(check(&text.replace("(position + -1)", replacement)).is_err());
    }
}
#[test]
fn constants_alias_collisions_and_escaped_names_survive() {
    let mut p = parse(SQUARE).unwrap();
    p.commands[0].args[1] = Arg::Text("a/b".into());
    p.commands[1].args[1] = Arg::Text("a_b".into());
    p.commands.insert(
        2,
        crate::plan::RawCommand {
            op: Op::Tensor,
            args: vec![
                Arg::Int(2),
                Arg::Text("a_b_v1".into()),
                Arg::Dtype("fp32".into()),
                Arg::Ints(vec![4]),
                Arg::Int(0),
                Arg::Data(Some(Data {
                    path: "@parameters/weight.bin".into(),
                    bytes: 16,
                    sha256: "a".repeat(64),
                })),
            ],
        },
    );
    p.value_count = 3;
    let text = roundtrip(&p);
    assert!(text.contains("weight a_b_v1_v2:"));
    assert!(check(&text.replace("@parameters/weight.bin", "../escape.bin")).is_err());
    for name in ["quote \" slash \\ newline\nUnicode λ", "none"] {
        p.commands[0].args[1] = Arg::Text(name.into());
        roundtrip(&p);
    }
    p.commands[2].op = Op::ConstantOutput;
    p.commands[2].args.remove(4);
    roundtrip(&p);
}
#[test]
fn native_operands_and_absent_bias_remain_distinct() {
    let p = parsed(&format!(
        r#"
        input x: fp32[1,4];
        weight packed: packed_i4[4,4] = asset(path="@parameters/packed.bin", bytes=8, sha256="{}");
        let out: storage<fp32[1,4]> = dot(x, native(packed), none, contraction_dims=1);
        output out;
    "#,
        "a".repeat(64)
    ));
    let text = roundtrip(&p);
    assert!(text.contains("dot(x, native(packed), none, contraction_dims=1)"));
    error(&text.replace("dot(x,", "dot(native(x),"), "packed carrier");
    assert!(check(&text.replace("dot(x,", "dot(none,")).is_err());
}
#[test]
fn structured_resource_encodings_are_validated() {
    let source = r#"ynn 1 resource_contract=1 completion_contract=1 {
        @resource(name="K", axis=0, encoding=encoding(dtype=int8, axis=0, scales=[0.03125], zero_points=[0]))
        state K: int8[4]; require committed(K) == 0; output K;
    }"#;
    roundtrip(&parse(source).unwrap());
    for (a, b) in [
        ("dtype=int8", "dtype=fp32"),
        ("scales=[0.03125]", "scales=[0]"),
        ("zero_points=[0]", "zero_points=[]"),
        ("zero_points=[0]", "zero_points=[128]"),
        ("axis=0, scales", "axis=none, scales"),
        ("axis=0, scales", "axis=1, scales"),
    ] {
        assert!(check(&source.replace(a, b)).is_err(), "{b}");
    }
}
#[test]
fn arithmetic_precedence_comments_and_aliases_preserve_trees() {
    let plan = parsed(
        "# // here is a comment\n input x: fp32[1]; output x;\n\
        dim p = parameter(\"position\") in -10..=10;\n\
        let n: index = -3 + p * 2 // 3;\n\
        require n <= ceil_div(p, 2); # trailing comment\n\
        require -9223372036854775808 <= -3 // 2;",
    );
    assert_eq!(
        report(&plan)["commands"][2]["args"][0],
        json!({"expr":{"add":[{"known":-3},{"floor_div":[{"mul":[{"symbol":0},{"known":2}]},{"known":3}]}]}})
    );
    assert_eq!(
        report(&plan)["commands"][3]["args"][0],
        json!({"expr":{"known":i64::MIN}})
    );
    roundtrip(&plan);
    assert!(check(&SQUARE.replace("# Copyright 2026 @snnn.", "// not a comment")).is_err());
    error(
        &SQUARE.replace("input x:", "let bad: index = 1 / 2; input x:"),
        "integer division",
    );
}
#[test]
fn auto_profiles_annotations_and_completion_groups_are_lossless() {
    let source=SQUARE.replace("profiling=explicit","profiling=auto").replace("let squared", "@profile(name=\"block0\", kind=\"custom.square\", input_names=[\"left\", \"right\"]) let squared");
    let value = parse(&source).unwrap();
    assert_eq!(report(&value)["commands"][2]["op"], "BeginProfileOperation");
    assert_eq!(
        report(&value)["commands"][2]["args"][0],
        json!({"text":"block0"})
    );
    let text = roundtrip(&value);
    assert!(!text.contains("begin_profile"));
    assert!(text.contains("profile squared = profile("));
    let grouped = parsed(
        r#"
        input x: fp32[4];
        profile(name="group", kind="two ops", inputs=[x], outputs=[z], input_names=["x"]) {
          operation(waits=[], defines=["first"], outputs=[y]) { let y = mul(x, x); }
          operation(waits=["first"], defines=["second"], outputs=[z]) { let z = add(y, x); }
        }
        output z;
    "#,
    );
    let text = roundtrip(&grouped);
    assert!(text.contains("operation(waits=[\"first\"]"));
    error(
        &text.replace("waits=[\"first\"]", "waits=[\"missing\"]"),
        "completion dependency",
    );
}
#[test]
fn multiple_results_and_explicit_attributes() {
    let value = parsed(
        r#"
        input x: fp32[4];
        let (a: storage<fp32[2]>, b: storage<fp32[2]>) = split(x, axis=0, unstack=false);
        let (q: storage<int8[2]>, scale: storage<fp32[1]>) = dynamic_quantization(a);
        output b; output q; output scale;
    "#,
    );
    let text = roundtrip(&value);
    assert!(text.contains("let (a:"));
    assert!(text.contains("unstack=false"));
    error(
        &text.replace(", unstack=false", ""),
        "Missing field unstack",
    );
    let logical = parsed("input x: fp32[4]; let y: fp32[4] = mul(x, x); output y;");
    assert_eq!(report(&logical)["commands"][3]["op"], "ResultShape");
    roundtrip(&logical);
}
const STATE: &str = include_str!("../../../tests/rust/kv_append.ynn");
#[test]
fn symbolic_shapes_checked_arithmetic_and_state_preconditions() {
    let value = parse(STATE).unwrap();
    let diagnostic = report(&value);
    let commands = diagnostic["commands"].as_array().unwrap();
    assert_eq!(
        commands.iter().filter(|c| c["op"] == "InputShape").count(),
        2
    );
    assert!(commands
        .iter()
        .any(|c| c["op"] == "Guard" && c["args"][4] == json!({"text":"checked"})));
    assert!(commands
        .iter()
        .any(|c| c["op"] == "Resource" && c["args"][3] == json!({"expr":{"symbol":1}})));
    roundtrip(&value);
    error(&STATE.replace("checked(p + T)", "p + T"), "overflow");
    error(
        &STATE.replace("committed(K) == p", "committed(K) <= p"),
        "requires equality",
    );
    error(&STATE.replace("C, 8", "?, 8"), "Unknown dimension ?");
    error(
        &STATE.replace("let end = checked(p + T);", "let end: index = end + 1;"),
        "Unknown dimension end",
    );
    error(
        &STATE.replace("rows=T", "rows=missing"),
        "Unknown dimension missing",
    );
}
#[test]
fn metadata_is_validated_instead_of_ignored() {
    for (metadata, expected) in [
        ("mystery x = 1;", "Unknown metadata"),
        (
            "name missing = \"oops\";",
            "Unknown or invalid metadata target",
        ),
        ("name x = \"a\"; name x = \"b\";", "Duplicate metadata"),
        ("name x = \"\\q\";", "invalid escape"),
        ("profile x = none;", "Unknown or invalid metadata target"),
        ("profile squared = profile(typo=1);", "Unknown field typo"),
        ("order [x, x];", "Invalid or duplicate tensor identity"),
        ("order [x];", "every tensor exactly once"),
        ("symbol x = 5;", "Unknown or invalid metadata target"),
    ] {
        let source = SQUARE.replace(
            "output squared;",
            &format!("output squared; metadata {{ {metadata} }}"),
        );
        error(&source, expected);
    }
    error(
        &SQUARE.replace("input x:", "@surprise() input x:"),
        "Unknown or duplicate annotation",
    );
    error(
        &SQUARE.replace("input x:", "@shape(1) input x:"),
        "Invalid arguments",
    );
}
#[test]
fn successful_parsing_obeys_direct_loader_limits() {
    for depth in [15, 25, 35, 50, 60, 64] {
        let nested = format!("{}0{}", "add(".repeat(depth), ", 0)".repeat(depth));
        let source=format!("ynn 1 resource_contract=1 completion_contract=1 {{ input x: storage<fp32[1]>; input_shape x=[add(1,{nested})]; output x; }}");
        match parse(&source) {
            Ok(_) => {
                crate::plan::ValidatedPlan::from_bytes(source.as_bytes()).unwrap();
                assert!(check(&source).is_ok());
            }
            Err(e) => {
                assert!(depth >= 35, "Shallow expression rejected: {e}");
                assert!(
                    e.to_string().contains("limit") || e.to_string().contains("budget"),
                    "{e}"
                );
            }
        }
    }
}
#[test]
fn unused_expressions_are_still_validated() {
    for expr in [
        "1 // 0",
        "floor_div(1)",
        "min()",
        "9223372036854775807 + 1",
        "missing + 1",
    ] {
        let source = SQUARE.replace("input x:", &format!("let bad: index = {expr}; input x:"));
        assert!(check(&source).is_err(), "{expr}");
    }
}
#[test]
fn bounded_parser_rejects_deep_and_truncated_inputs_without_panicking() {
    for expression in [
        format!("{}0{}", "add(".repeat(300), ")".repeat(300)),
        vec!["1"; 300].join(" + "),
    ] {
        error(&SQUARE.replace("[4]", &format!("[{expression}]")), "limit");
    }
    let list = format!("[{}]", vec!["1"; 1025].join(","));
    error(&SQUARE.replace("[4]", &list), "1024");
    // A short sequence of aliases must not expand exponentially without a bound.
    let mut aliases = String::from("let d0: index = 1;\n");
    for i in 1..20 {
        aliases.push_str(&format!("let d{i}: index = d{} + d{};\n", i - 1, i - 1));
    }
    error(
        &SQUARE.replace("input x:", &format!("{aliases}input x:")),
        "budget",
    );
    for i in 0..SQUARE.len() {
        if !SQUARE.is_char_boundary(i) {
            continue;
        }
        let _ = check(&SQUARE[..i]);
        let corrupted = format!("{}λ{}", &SQUARE[..i], &SQUARE[i..]);
        let _ = check(&corrupted);
    }
}
#[test]
fn pure_functions_preserve_hierarchy_and_expand_hygienically() {
    let source = r#"ynn 1 resource_contract=1 completion_contract=1 {
      fn square_fn(x: storage<fp32[4]>) -> (result: storage<fp32[4]>) {
        Binary(operator=multiply, lhs=x, rhs=x, output=result);
        return(result);
      }
      fn twice(x: storage<fp32[4]>) -> (result: storage<fp32[4]>) {
        value temporary: storage<fp32[4]>;
        value temporary_: storage<fp32[4]>;
        invoke square_fn(x) -> (temporary);
        invoke square_fn(temporary) -> (temporary_);
        Copy(input=temporary_, output=result);
        return(result);
      }
      input x: storage<fp32[4]>;
      value y: storage<fp32[4]>;
      value z: storage<fp32[4]>;
      value __fn1_temporary: storage<fp32[4]>;
      @scope(name="layer0") invoke twice(x) -> (y);
      @scope(name="layer1") invoke twice(x) -> (z);
      output y;
      output z;
    }"#;
    super::check(source).unwrap();
    let formatted = super::format(source).unwrap();
    assert!(formatted.contains("fn twice") && formatted.contains("invoke square_fn"));
    assert_eq!(formatted, super::format(&formatted).unwrap());
    let flat = super::printer::print(&super::parse(source).unwrap()).unwrap();
    assert!(!flat.contains("invoke") && !flat.contains("fn twice"));
    assert_eq!(super::parse(source).unwrap(), super::parse(&flat).unwrap());
}

#[test]
fn functions_reject_recursion_captures_effects_and_bad_interfaces() {
    let prefix = "ynn 1 resource_contract=1 completion_contract=1 {";
    for body in [
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { return(y); }",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { invoke f(x) -> (y); return(y); }",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { Copy(input=hidden, output=y); return(y); } input hidden: storage<fp32[4]>;",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { Copy(input=x, output=y); return(x); }",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { value x: storage<fp32[4]>; return(y); }",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { Copy(input=x, output=y); return(y); } input x: storage<int32[4]>; value y: storage<fp32[4]>; invoke f(x) -> (y);",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { Copy(input=x, output=y); return(y); } input x: storage<fp32[5]>; value y: storage<fp32[4]>; invoke f(x) -> (y);",
        "fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { BeginOperation(waits=[]); Copy(input=x, output=y); EndOperation(defines=[], outputs=[y]); return(y); }",
    ] {
        let source = format!("{prefix}{body}}}");
        let failure = std::panic::catch_unwind(|| super::check(&source));
        assert!(failure.is_ok(), "panicked on {body}");
        assert!(failure.unwrap().is_err(), "accepted {body}");
    }
}

#[test]
fn function_expansion_is_bounded_and_rejects_resource_operands() {
    let mut source = "ynn 1 resource_contract=1 completion_contract=1 {\n".to_string();
    source.push_str("fn f0(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { Copy(input=x, output=y); return(y); }\n");
    for i in 1..19 {
        source.push_str(&format!("fn f{i}(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) {{ value t: storage<fp32[4]>; invoke f{}(x) -> (t); invoke f{}(t) -> (y); return(y); }}\n", i-1, i-1));
    }
    source.push('}');
    let error = super::check(&source).unwrap_err().to_string();
    assert!(
        error.contains("limit") || error.contains("budget"),
        "{error}"
    );
    let source = r#"ynn 1 resource_contract=1 completion_contract=1 {
      fn f(x: storage<fp32[4]>) -> (y: storage<fp32[4]>) { Copy(input=x, output=y); return(y); }
      input x: storage<fp32[4]>;
      value y: storage<fp32[4]>;
      Resource(owner=x, name="cache", axis=0, entry_extent=4, encoding=encoding(dtype=fp32, axis=none, scales=[], zero_points=[]));
      invoke f(x) -> (y);
      output y;
    }"#;
    assert!(super::check(source)
        .unwrap_err()
        .to_string()
        .contains("resource"));
}
