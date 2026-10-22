// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Optional static benchmark rendering of the validated native schema.
//! Models use `.ynn`; this renderer deliberately rejects assets and symbols.
use crate::{
    plan::{Arg, Expr},
    Error, Result,
};
fn argument(a: &Arg) -> Result<String> {
    Ok(match a {
        Arg::Int(x) => x.to_string(),
        Arg::Text(x) => serde_json::to_string(x)?,
        Arg::Bool(x) => x.to_string(),
        Arg::Dtype(x) => format!("ynn_type_{x}"),
        Arg::Binary(x) => format!("ynn_binary_{x}"),
        Arg::Unary(x) => format!("ynn_unary_{x}"),
        Arg::Reduce(x) => format!("ynn_reduce_{x}"),
        Arg::Ints(xs) => format!("{{{}}}",xs.iter().map(ToString::to_string).collect::<Vec<_>>().join(", ")),
        Arg::Texts(xs) => format!("{{{}}}",xs.iter().map(serde_json::to_string).collect::<std::result::Result<Vec<_>,_>>()?.join(", ")),
        Arg::Expr(Expr::Known(x)) => x.to_string(),
        Arg::Exprs(xs) => format!("{{{}}}",xs.iter().map(|x|argument(&Arg::Expr(x.clone()))).collect::<Result<Vec<_>>>()?.join(", ")),
        Arg::Data(None) => "nullptr".into(),
        _ => return Err(Error::invalid("Static C++ benchmark rendering requires fixed shapes, no assets, and integer coefficients")),
    })
}
pub fn statements(source: &str) -> Result<String> {
    super::check(source)?;
    let p = super::parse(source)?;
    p.commands
        .iter()
        .map(|c| {
            Ok(format!(
                "graph.{}({});\n",
                c.op.name(),
                c.args
                    .iter()
                    .map(argument)
                    .collect::<Result<Vec<_>>>()?
                    .join(", ")
            ))
        })
        .collect()
}
#[cfg(test)]
mod tests {
    #[test]
    fn static_builder_uses_the_validated_command_schema() {
        let code=super::statements("ynn 1 resource_contract=1 completion_contract=1 {input x: storage<fp32[2]>; value y: storage<fp32[2]>; output y; Unary(operator=square,input=x,output=y);}").unwrap();
        assert!(code.contains("ynn_unary_square"));
    }
}
