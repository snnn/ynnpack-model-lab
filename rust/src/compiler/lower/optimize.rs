// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use std::collections::BTreeMap;
pub(super) fn run(mut g: Graph, options: &CompileOptions, function: bool) -> Result<Graph> {
    // Quantized public values carry their parameter tensors as part of the ABI.
    if !function {
        for name in g.outputs.clone() {
            if let Some(p) = g.values[&name]
                .tensor
                .quant
                .as_ref()
                .and_then(|q| q.parameters.as_ref())
            {
                for parameter in [&p.scales, &p.zeros] {
                    if !g.outputs.contains(parameter) {
                        g.outputs.push(parameter.clone());
                    }
                }
            }
        }
    }
    // Explicit physical resource capabilities belong here, never in the importer.
    for r in &g.resources {
        let t = &g.values[&r.owner].tensor;
        if r.selected && t.dtype.bits() >= 8 && (t.dtype != Dtype::F32 || t.quant.is_some()) {
            return Err(Error::invalid(
                "Target-selected resources require FP32 or packed codes",
            ));
        }
        if !r.selected && t.dtype.bits() >= 8 {
            let mut stride = Expr::Known(1);
            let mut dense = vec![];
            for d in t.shape.iter().rev() {
                dense.push(stride.clone());
                stride = Expr::product([
                    stride,
                    d.literal()
                        .map(|n| Expr::Known(n.max(1)))
                        .unwrap_or_else(|| Expr::Max(vec![Expr::Known(1), d.clone()])),
                ]);
            }
            dense.reverse();
            if !r.strides.is_empty()
                && r.strides.iter().map(geometry).collect::<Vec<_>>()
                    != dense.iter().map(geometry).collect::<Vec<_>>()
            {
                return Err(Error::invalid(format!(
                    "Contiguous external resource owner required: {} {:?} != {:?}",
                    r.name,
                    r.strides.iter().map(geometry).collect::<Vec<_>>(),
                    dense.iter().map(geometry).collect::<Vec<_>>()
                )));
            }
        }
    }
    for n in &g.nodes {
        if n.op == Op::ResourceAppend && g.values[&n.inputs[1]].resource.is_some() {
            return Err(Error::invalid("Independent fresh append payload required"));
        }
    }
    for y in &g.outputs {
        let v = &g.values[y];
        if v.tensor.dtype.bits() < 8 && v.resource.as_ref().is_some_and(|r| !r.owner) {
            return Err(Error::invalid("Packed resource view requires a consumer"));
        }
    }
    let originals = std::mem::take(&mut g.nodes);
    for mut n in originals {
        if options.schedule_masks && n.op == Op::CausalMask {
            n.op = Op::ScheduledMask;
        }
        // Independent symbolic singleton alternatives require explicit broadcasts.
        if matches!(
            n.op,
            Op::Add
                | Op::Sub
                | Op::Mul
                | Op::Div
                | Op::Minimum
                | Op::Maximum
                | Op::Pow
                | Op::Prelu
                | Op::Matmul
        ) {
            let matrix = if n.op == Op::Matmul { 2 } else { 0 };
            let lhs = g.shape(&n.inputs[0])?;
            let rhs = g.shape(&n.inputs[1])?;
            let out = g.shape(&n.outputs[0])?;
            let na = lhs.len() - matrix;
            let nb = rhs.len() - matrix;
            let nr = out.len() - matrix;
            let mut shapes = [lhs.clone(), rhs.clone()];
            let mut expand = [false, false];
            for back in 0..na.min(nb) {
                let a = &lhs[na - 1 - back];
                let b = &rhs[nb - 1 - back];
                if a == b || *a == Expr::Known(1) || *b == Expr::Known(1) {
                    continue;
                }
                for (i, dim) in [na - 1 - back, nb - 1 - back].into_iter().enumerate() {
                    if shapes[i][dim] != out[nr - 1 - back] {
                        shapes[i][dim] = out[nr - 1 - back].clone();
                        expand[i] = true;
                    }
                }
            }
            for i in 0..2 {
                if expand[i] {
                    let name = g.fresh(&format!("{}/broadcast{i}", n.outputs[0]));
                    g.emit(Node {
                        op: Op::BroadcastTo,
                        inputs: vec![n.inputs[i].clone()],
                        outputs: vec![name.clone()],
                        attributes: Attributes {
                            shape: shapes[i].clone(),
                            ..Attributes::default()
                        },
                        waits: n.waits.clone(),
                        completes: vec![],
                        scope: n.scope.clone(),
                    })?;
                    n.inputs[i] = name;
                }
            }
        }
        if options.target_views
            && n.op == Op::Reshape
            && n.waits.is_empty()
            && n.completes.is_empty()
        {
            let (a, b) = (g.shape(&n.inputs[0])?, g.shape(&n.outputs[0])?);
            let mut prefix = 0;
            let mut suffix = 0;
            while prefix < a.len().min(b.len()) && a[prefix] == b[prefix] {
                prefix += 1;
            }
            while suffix + prefix < a.len().min(b.len())
                && a[a.len() - 1 - suffix] == b[b.len() - 1 - suffix]
            {
                suffix += 1;
            }
            let (ni, no) = (a.len() - prefix - suffix, b.len() - prefix - suffix);
            let split = b[prefix..b.len() - suffix].to_vec();
            if ni > 0
                && no > 0
                && split.iter().filter(|x| x.literal().is_none()).count() <= 1
                && !split.contains(&Expr::Known(0))
            {
                let mut input = n.inputs[0].clone();
                if ni > 1 {
                    let dest = if no == 1 {
                        n.outputs[0].clone()
                    } else {
                        g.fresh(&(n.outputs[0].clone() + "/fused"))
                    };
                    g.emit(Node {
                        op: Op::FuseDims,
                        inputs: vec![input],
                        outputs: vec![dest.clone()],
                        attributes: Attributes {
                            axis: prefix as i64,
                            integers: vec![ni as i64],
                            ..Attributes::default()
                        },
                        ..n.clone()
                    })?;
                    input = dest;
                }
                if no > 1 {
                    g.emit(Node {
                        op: Op::SplitDim,
                        inputs: vec![input],
                        attributes: Attributes {
                            axis: prefix as i64,
                            shape: split,
                            ..Attributes::default()
                        },
                        ..n.clone()
                    })?;
                    continue;
                }
                if ni > 1 {
                    continue;
                }
            }
        }
        g.nodes.push(n);
    }
    if options.cleanup {
        // Target decomposition can create equivalent pure temporaries after the
        // source frontend has finished. Never merge completion/resource reads.
        let mut seen = BTreeMap::<String, String>::new();
        let mut aliases = BTreeMap::<String, String>::new();
        let mut literals = BTreeMap::<String, String>::new();
        for (name, value) in &g.values {
            if !value.constant
                || g.inputs.contains(name)
                || g.outputs.contains(name)
                || value
                    .tensor
                    .quant
                    .as_ref()
                    .is_some_and(|q| q.parameters.is_some())
            {
                continue;
            }
            let payload = if let Some(a) = &value.data {
                serde_json::to_string(&(a.bytes, &a.sha256))?
            } else {
                use sha2::{Digest, Sha256};
                {
                    let bytes = literal_bytes(value)?;
                    serde_json::to_string(&(bytes.len(), format!("{:x}", Sha256::digest(&bytes))))?
                }
            };
            let key = serde_json::to_string(&(&value.tensor, payload))?;
            if let Some(previous) = literals.get(&key) {
                aliases.insert(name.clone(), previous.clone());
            } else {
                literals.insert(key, name.clone());
            }
        }
        for n in &mut g.nodes {
            for input in &mut n.inputs {
                if let Some(old) = aliases.get(input) {
                    *input = old.clone();
                }
            }
            if n.outputs.len() != 1
                || !n.waits.is_empty()
                || !n.completes.is_empty()
                || matches!(
                    n.op,
                    Op::ResourceAppend
                        | Op::ResourceView
                        | Op::Call
                        | Op::GatedDeltaRule
                        | Op::CausalDepthwiseConv
                )
                || n.inputs.iter().chain(&n.outputs).any(|x| {
                    g.values.get(x).is_some_and(|v| {
                        v.resource.is_some()
                            || v.tensor
                                .quant
                                .as_ref()
                                .is_some_and(|q| q.parameters.is_some())
                    })
                })
            {
                continue;
            }
            let output = n.outputs[0].clone();
            let key = serde_json::to_string(&(
                n.op,
                &n.inputs,
                &n.attributes,
                &g.values[&output].tensor,
                &n.scope,
            ))?;
            if let Some(previous) = seen.get(&key) {
                if g.outputs.contains(&output) {
                    n.op = Op::Copy;
                    n.inputs = vec![previous.clone()];
                    n.attributes = Attributes::default();
                } else {
                    aliases.insert(output, previous.clone());
                }
            } else {
                seen.insert(key, output);
            }
        }
        g.nodes
            .retain(|n| !n.outputs.iter().any(|y| aliases.contains_key(y)));
        // Eliminate only pure dead nodes and redundant forwarding temporaries.
        let mut uses = BTreeMap::<String, usize>::new();
        for n in &g.nodes {
            for x in &n.inputs {
                *uses.entry(x.clone()).or_default() += 1;
            }
        }
        let mut replacements = BTreeMap::new();
        for n in &g.nodes {
            if n.op == Op::Copy
                && n.waits.is_empty()
                && n.completes.is_empty()
                && n.inputs.len() == 1
                && n.outputs.len() == 1
                && !g.outputs.contains(&n.outputs[0])
                && g.values[&n.outputs[0]].resource.is_none()
                && g.values[&n.inputs[0]].resource.is_none()
            {
                replacements.insert(n.outputs[0].clone(), n.inputs[0].clone());
            }
        }
        let resolve = |name: &String| {
            let mut x = name.clone();
            for _ in 0..replacements.len() {
                if let Some(next) = replacements.get(&x) {
                    x = next.clone();
                } else {
                    break;
                }
            }
            x
        };
        for n in &mut g.nodes {
            for x in &mut n.inputs {
                *x = resolve(x);
            }
        }
        g.nodes
            .retain(|n| !n.outputs.iter().any(|y| replacements.contains_key(y)));
        let mut live: BTreeSet<_> = g.outputs.iter().cloned().collect();
        let mut live_completions: BTreeSet<_> = g.completions.iter().cloned().collect();
        let mut keep = vec![];
        for n in g.nodes.iter().rev() {
            loop {
                let prev = live.len();
                for name in live.clone() {
                    if let Some(p) = g
                        .values
                        .get(&name)
                        .and_then(|v| v.tensor.quant.as_ref())
                        .and_then(|q| q.parameters.as_ref())
                    {
                        live.insert(p.scales.clone());
                        live.insert(p.zeros.clone());
                    }
                }
                if prev == live.len() {
                    break;
                }
            }
            let needed = n.outputs.iter().any(|x| live.contains(x))
                || n.completes.iter().any(|x| live_completions.contains(x))
                || matches!(n.op, Op::ResourceAppend | Op::Call);
            if needed {
                live.extend(n.inputs.iter().cloned());
                live_completions.extend(n.waits.iter().cloned());
                keep.push(n.clone());
            }
        }
        keep.reverse();
        g.nodes = keep;
        for n in &g.nodes {
            for x in n.inputs.iter().chain(&n.outputs) {
                live.insert(x.clone());
            }
        }
        live.extend(g.inputs.iter().cloned());
        for r in &g.resources {
            live.insert(r.owner.clone());
        }
        // Quantization descriptors are semantic references even when not ordinary operands.
        loop {
            let prev = live.len();
            for name in live.clone() {
                if let Some(p) = g
                    .values
                    .get(&name)
                    .and_then(|v| v.tensor.quant.as_ref())
                    .and_then(|q| q.parameters.as_ref())
                {
                    live.insert(p.scales.clone());
                    live.insert(p.zeros.clone());
                }
            }
            if prev == live.len() {
                break;
            }
        }
        g.values.retain(|name, _| live.contains(name));
    }
    Ok(g)
}
