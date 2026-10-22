// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use std::collections::BTreeMap;
/// Fuse only an exclusive convolution-history region with identical state semantics.
pub(super) fn causal_conv(g: &mut Graph) {
    let nodes = g.nodes.clone();
    let mut producers = BTreeMap::new();
    let mut users = BTreeMap::<String, Vec<usize>>::new();
    for (i, n) in nodes.iter().enumerate() {
        for y in &n.outputs {
            producers.insert(y.clone(), i);
        }
        for x in &n.inputs {
            users.entry(x.clone()).or_default().push(i);
        }
    }
    let shape = |name: &String| -> Option<Vec<i64>> {
        g.values
            .get(name)?
            .tensor
            .shape
            .iter()
            .map(Expr::literal)
            .collect()
    };
    let mut skipped = BTreeSet::new();
    let mut replacements = BTreeMap::new();
    for (i, n) in nodes.iter().enumerate() {
        if n.op != Op::DepthwiseConv2D || n.inputs.len() != 2 {
            continue;
        }
        let Some(s) = &n.attributes.spatial else {
            continue;
        };
        if s.same || s.multiplier != 1 || s.strides != [1, 1] || s.dilations != [1, 1] {
            continue;
        }
        let Some(&e) = producers.get(&n.inputs[0]) else {
            continue;
        };
        let expand = &nodes[e];
        if !matches!(expand.op, Op::Reshape | Op::ExpandDims) || expand.inputs.len() != 1 {
            continue;
        }
        let Some(&c) = producers.get(&expand.inputs[0]) else {
            continue;
        };
        let cat = &nodes[c];
        if cat.op != Op::Concat || cat.attributes.axis != 1 || cat.inputs.len() != 2 {
            continue;
        }
        let (history, fresh) = (&cat.inputs[0], &cat.inputs[1]);
        let (Some(hs), Some(xs), Some(ws)) = (shape(history), shape(fresh), shape(&n.inputs[1]))
        else {
            continue;
        };
        if hs.len() != 3 || xs.len() != 3 || ws.len() != 4 {
            continue;
        }
        let (b, t, ch) = (xs[0], xs[1], xs[2]);
        let kernel = hs[1] + 1;
        if b <= 0
            || t <= 0
            || ch <= 0
            || kernel < 2
            || hs != [b, kernel - 1, ch]
            || ws != [1, kernel, 1, ch]
            || shape(&expand.outputs[0]) != Some(vec![b, t + kernel - 1, 1, ch])
            || shape(&n.outputs[0]) != Some(vec![b, t, 1, ch])
        {
            continue;
        }
        let siblings = users.get(&cat.outputs[0]).cloned().unwrap_or_default();
        if siblings.len() != 2 || users.get(&expand.outputs[0]) != Some(&vec![i]) {
            continue;
        }
        let slices = siblings
            .iter()
            .filter(|j| nodes[**j].op == Op::Slice)
            .copied()
            .collect::<Vec<_>>();
        if slices.len() != 1 {
            continue;
        }
        let r = slices[0];
        let state = &nodes[r];
        let starts = &state.attributes.starts;
        if starts.len() != 3
            || starts[0] != Expr::Known(0)
            || starts[2] != Expr::Known(0)
            || shape(&state.outputs[0]) != Some(hs)
            || users
                .get(&state.outputs[0])
                .is_some_and(|u| u.iter().any(|j| *j < i))
        {
            continue;
        }
        let region = [c, e, r, i];
        if region.iter().any(|j| {
            !nodes[*j].waits.is_empty() || !nodes[*j].completes.is_empty() || skipped.contains(j)
        }) {
            continue;
        }
        if [&cat.outputs[0], &expand.outputs[0]]
            .iter()
            .any(|y| g.outputs.contains(y))
        {
            continue;
        }
        if region
            .iter()
            .flat_map(|j| nodes[*j].inputs.iter().chain(&nodes[*j].outputs))
            .any(|x| g.values[x].tensor.dtype != Dtype::F32 || g.values[x].tensor.quant.is_some())
        {
            continue;
        }
        replacements.insert(
            i,
            Node {
                op: Op::CausalDepthwiseConv,
                inputs: vec![fresh.clone(), n.inputs[1].clone(), history.clone()],
                outputs: vec![n.outputs[0].clone(), state.outputs[0].clone()],
                attributes: Attributes {
                    position: starts[1].clone(),
                    ..Attributes::default()
                },
                ..n.clone()
            },
        );
        skipped.extend([c, e, r]);
    }
    g.nodes = nodes
        .into_iter()
        .enumerate()
        .filter_map(|(i, n)| {
            if skipped.contains(&i) {
                None
            } else {
                Some(replacements.remove(&i).unwrap_or(n))
            }
        })
        .collect();
}
/// Fold singleton decode query rows into the head batch when the RHS broadcasts.
pub(super) fn decode_rows(g: &mut Graph) -> Result<()> {
    let old = std::mem::take(&mut g.nodes);
    for n in old {
        let eligible = n.op == Op::Matmul
            && !n.attributes.adj_x
            && n.inputs.len() == 2
            && n.outputs.len() == 1
            && n.waits.is_empty()
            && n.completes.is_empty();
        if eligible {
            let a = &g.values[&n.inputs[0]].tensor;
            let b = &g.values[&n.inputs[1]].tensor;
            let out = &g.values[&n.outputs[0]].tensor;
            if [a, b, out]
                .iter()
                .all(|t| t.dtype == Dtype::F32 && t.quant.is_none() && t.shape.len() == 4)
                && a.shape[2] == Expr::Known(1)
                && b.shape[1] == Expr::Known(1)
                && a.shape[1].literal().is_some_and(|h| h > 1)
            {
                let mut shape = a.shape.clone();
                shape.swap(1, 2);
                let row = g.fresh(&(n.outputs[0].clone() + "/rows"));
                g.emit(Node {
                    op: Op::Reshape,
                    inputs: vec![n.inputs[0].clone()],
                    outputs: vec![row.clone()],
                    attributes: Attributes {
                        shape,
                        ..Attributes::default()
                    },
                    ..n.clone()
                })?;
                let dot = g.fresh(&(n.outputs[0].clone() + "/dot"));
                g.emit(Node {
                    inputs: vec![row, n.inputs[1].clone()],
                    outputs: vec![dot.clone()],
                    ..n.clone()
                })?;
                let shape = g.values[&n.outputs[0]].tensor.shape.clone();
                g.emit(Node {
                    op: Op::Reshape,
                    inputs: vec![dot],
                    attributes: Attributes {
                        shape,
                        ..Attributes::default()
                    },
                    ..n.clone()
                })?;
                continue;
            }
        }
        g.nodes.push(n);
    }
    Ok(())
}
