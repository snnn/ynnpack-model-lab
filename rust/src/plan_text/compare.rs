// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Structural comparison is deliberately conservative. It expands construction
//! functions and normalizes identities/asset locations, but never assumes two
//! different arithmetic programs are numerically equivalent.
use crate::{
    plan::{Arg, Expr, Op, Plan},
    Result,
};
use serde_json::{json, Value};
use sha2::{Digest, Sha256};
use std::collections::BTreeMap;
fn hash(value: &impl serde::Serialize) -> String {
    format!("{:x}", Sha256::digest(serde_json::to_vec(value).unwrap()))
}
fn id(arg: &Arg) -> i64 {
    match arg {
        Arg::Int(n) | Arg::Native(n) => *n,
        _ => unreachable!(),
    }
}
fn expr(e: &Expr, symbols: &BTreeMap<u32, u32>) -> Expr {
    match e {
        Expr::Symbol(s) => Expr::Symbol(symbols[s]),
        Expr::Known(n) => Expr::Known(*n),
        Expr::Add(xs) => Expr::Add(xs.iter().map(|x| expr(x, symbols)).collect()),
        Expr::Mul(xs) => Expr::Mul(xs.iter().map(|x| expr(x, symbols)).collect()),
        Expr::Min(xs) => Expr::Min(xs.iter().map(|x| expr(x, symbols)).collect()),
        Expr::Max(xs) => Expr::Max(xs.iter().map(|x| expr(x, symbols)).collect()),
        Expr::FloorDiv(xs) => Expr::FloorDiv(xs.iter().map(|x| expr(x, symbols)).collect()),
        Expr::CeilDiv(xs) => Expr::CeilDiv(xs.iter().map(|x| expr(x, symbols)).collect()),
    }
}
fn canonical(plan: &Plan) -> Value {
    let mut names = BTreeMap::<i64, String>::new();
    let mut symbols = BTreeMap::new();
    let mut declarations = BTreeMap::new();
    let mut assets = BTreeMap::new();
    for c in &plan.commands {
        if c.op.declares_tensor() {
            let n = id(&c.args[0]);
            let data = c.args.last().unwrap();
            let constant = matches!(data, Arg::Data(Some(_)));
            let mut schema = vec![
                serde_json::to_value(c.op).unwrap(),
                serde_json::to_value(&c.args[2..4]).unwrap(),
            ];
            if let Arg::Data(Some(d)) = data {
                let data = json!({"bytes":d.bytes,"sha256":d.sha256});
                assets.insert(d.sha256.clone(), d.bytes);
                schema.push(data);
            } else {
                schema.push(json!(null));
            }
            let input = c.args.len() == 6 && matches!(c.args[4],Arg::Int(f) if f&1!=0);
            let output = matches!(c.op, Op::ConstantOutput | Op::PackedConstantOutput)
                || c.args.len() == 6 && matches!(c.args[4],Arg::Int(f) if f&2!=0);
            if constant {
                names.insert(n, format!("constant/{}", hash(&schema)));
            } else if input {
                names.insert(
                    n,
                    format!("input/{}", serde_json::to_string(&c.args[1]).unwrap()),
                );
            }
            declarations.insert(n, (schema, input, output));
        }
    }
    for c in &plan.commands {
        if c.op == Op::Symbol {
            let old = id(&c.args[0]) as u32;
            let next = symbols.len() as u32;
            symbols.insert(old, next);
        }
    }
    let mut serial = 0;
    let mut value = |n: i64| -> String {
        if n == u32::MAX as i64 {
            return "none".into();
        }
        names
            .entry(n)
            .or_insert_with(|| {
                let result = format!("value/{serial}");
                serial += 1;
                result
            })
            .clone()
    };
    let mut commands = vec![];
    let mut histogram = BTreeMap::new();
    for c in &plan.commands {
        if c.op.declares_tensor()
            || matches!(c.op, Op::BeginProfileOperation | Op::EndProfileOperation)
        {
            continue;
        }
        *histogram.entry(c.op.name()).or_insert(0usize) += 1;
        let mut args = vec![];
        for (i, a) in c.args.iter().enumerate() {
            if c.op == Op::Symbol {
                args.push(if i == 0 {
                    json!(symbols[&(id(a) as u32)])
                } else if i == 4 && matches!(&c.args[1],Arg::Text(s) if s=="Axis") {
                    json!(value(id(a)))
                } else {
                    serde_json::to_value(a).unwrap()
                });
                continue;
            }
            if c.op == Op::Guard && c.op.fields()[i] == "message" {
                args.push(json!("guard"));
                continue;
            }
            let kind = c.op.signature()[i];
            args.push(match (kind, a) {
                ("id" | "optional" | "operand", Arg::Int(n)) => json!({"id":value(*n)}),
                ("operand", Arg::Native(n)) => json!({"native":value(*n)}),
                ("ids", Arg::Ints(ns)) => json!(ns.iter().map(|n| value(*n)).collect::<Vec<_>>()),
                (_, Arg::Expr(e)) => json!(expr(e, &symbols)),
                (_, Arg::Exprs(es)) => {
                    json!(es.iter().map(|e| expr(e, &symbols)).collect::<Vec<_>>())
                }
                _ => serde_json::to_value(a).unwrap(),
            });
        }
        commands.push(json!({"op":c.op,"args":args}));
    }
    // Preserve public bindings, including unused inputs, but ignore unused private
    // declarations and aliases introduced by function capture lifting.
    let tensors = declarations
        .into_iter()
        .filter_map(|(id, (schema, input, output))| {
            names.get(&id).map(|name| {
                (
                    name.clone(),
                    json!({"schema":schema,"input":input,"output":output}),
                )
            })
        })
        .collect::<BTreeMap<_, _>>();
    json!({"resource_contract":plan.resource_contract,"completion_contract":plan.completion_contract,"tensors":tensors,"commands":commands,"assets":assets,"histogram":histogram})
}
/// A mismatch is diagnostic evidence, never evidence of numerical failure.
pub fn compare(left: &str, right: &str) -> Result<Value> {
    super::check(left)?;
    super::check(right)?;
    let a = canonical(&super::parse(left)?);
    let b = canonical(&super::parse(right)?);
    let ac = a["commands"].as_array().unwrap();
    let bc = b["commands"].as_array().unwrap();
    let at = (0..ac.len().max(bc.len())).find(|i| ac.get(*i) != bc.get(*i));
    Ok(
        json!({"format":"ynn-construction-comparison-v1","same_construction":a==b,"same_assets":a["assets"]==b["assets"],"same_tensor_contracts":a["tensors"]==b["tensors"],"left_sha256":hash(&a),"right_sha256":hash(&b),"left_operations":a["histogram"],"right_operations":b["histogram"],"first_command_difference":at.map(|i|json!({"index":i,"left":ac.get(i),"right":bc.get(i)})),"interpretation":"Structural equality is useful regression evidence; numerical tests remain required. Different arithmetic, guard, state, or completion contracts are not normalized away."}),
    )
}
#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn ignores_local_names_but_detects_changed_coefficients() {
        let a="ynn 1 resource_contract=1 completion_contract=1 { input x: storage<fp32[2]>; value y: storage<fp32[2]>; output y; Unary(operator=square, input=x, output=y); }";
        let b = a
            .replace("value y:", "value z:")
            .replace("output y;", "output z;")
            .replace("output=y", "output=z");
        assert_eq!(compare(a, &b).unwrap()["same_construction"], true);
        let b = b.replace("square", "negate");
        assert_eq!(compare(a, &b).unwrap()["same_construction"], false);
    }
}
