// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use std::collections::BTreeMap;
#[allow(
    dead_code,
    unused_imports,
    unused_variables,
    unused_mut,
    non_snake_case,
    irrefutable_let_patterns
)]
mod generated {
    extern crate alloc;
    include!(concat!(env!("OUT_DIR"), "/regions.rs"));
}
struct Facts<'a> {
    g: &'a Graph,
    producers: &'a BTreeMap<String, usize>,
    users: &'a BTreeMap<String, Vec<usize>>,
    skipped: &'a BTreeSet<usize>,
}
impl generated::Context for Facts<'_> {
    fn depthwise(&mut self, i: usize) -> Option<usize> {
        let n = &self.g.nodes[i];
        if n.op != Op::DepthwiseConv2D || n.inputs.len() != 2 {
            return None;
        }
        let s = n.attributes.spatial.as_ref()?;
        if s.same || s.multiplier != 1 || s.strides != [1, 1] || s.dilations != [1, 1] {
            return None;
        }
        self.producers.get(&n.inputs[0]).copied()
    }
    fn expanded(&mut self, i: usize) -> Option<usize> {
        let n = &self.g.nodes[i];
        if !matches!(n.op, Op::Reshape | Op::ExpandDims) || n.inputs.len() != 1 {
            return None;
        }
        self.producers.get(&n.inputs[0]).copied()
    }
    fn history_concat(&mut self, i: usize) -> Option<()> {
        let n = &self.g.nodes[i];
        (n.op == Op::Concat && n.attributes.axis == 1 && n.inputs.len() == 2).then_some(())
    }
    fn history_state(&mut self, i: usize) -> Option<usize> {
        let siblings = self.users.get(&self.g.nodes[i].outputs[0])?;
        if siblings.len() != 2 {
            return None;
        }
        let slices = siblings
            .iter()
            .copied()
            .filter(|&j| self.g.nodes[j].op == Op::Slice)
            .collect::<Vec<_>>();
        (slices.len() == 1).then(|| slices[0])
    }
    fn region_legal(&mut self, i: usize, e: usize, c: usize, r: usize) -> u8 {
        self.legal(i, e, c, r) as u8
    }
}
impl Facts<'_> {
    fn legal(&self, i: usize, e: usize, c: usize, r: usize) -> bool {
        let g = self.g;
        let nodes = &g.nodes;
        let users = self.users;
        let n = &nodes[i];
        let expand = &nodes[e];
        let cat = &nodes[c];
        let shape = |name: &String| -> Option<Vec<i64>> {
            g.values
                .get(name)?
                .tensor
                .shape
                .iter()
                .map(Expr::literal)
                .collect()
        };
        let (history, fresh) = (&cat.inputs[0], &cat.inputs[1]);
        let (Some(hs), Some(xs), Some(ws)) = (shape(history), shape(fresh), shape(&n.inputs[1]))
        else {
            return false;
        };
        if hs.len() != 3 || xs.len() != 3 || ws.len() != 4 {
            return false;
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
            return false;
        }

        if users.get(&expand.outputs[0]) != Some(&vec![i]) {
            return false;
        }
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
            return false;
        }
        let region = [c, e, r, i];
        if region.iter().any(|j| {
            !nodes[*j].waits.is_empty()
                || !nodes[*j].completes.is_empty()
                || self.skipped.contains(j)
        }) {
            return false;
        }
        if [&cat.outputs[0], &expand.outputs[0]]
            .iter()
            .any(|y| g.outputs.contains(y))
        {
            return false;
        }
        if region
            .iter()
            .flat_map(|j| nodes[*j].inputs.iter().chain(&nodes[*j].outputs))
            .any(|x| g.values[x].tensor.dtype != Dtype::F32 || g.values[x].tensor.quant.is_some())
        {
            return false;
        }

        true
    }
}
/// Match against an immutable graph; commit disjoint replacements in source order.
pub(super) fn causal_conv(g: &mut Graph) {
    let mut producers = BTreeMap::new();
    let mut users = BTreeMap::<String, Vec<usize>>::new();
    for (i, n) in g.nodes.iter().enumerate() {
        for y in &n.outputs {
            producers.insert(y.clone(), i);
        }
        for x in &n.inputs {
            users.entry(x.clone()).or_default().push(i);
        }
    }
    let mut skipped = BTreeSet::new();
    let mut replacements = BTreeMap::new();
    for i in 0..g.nodes.len() {
        let mut facts = Facts {
            g,
            producers: &producers,
            users: &users,
            skipped: &skipped,
        };
        let Some(generated::Region::Causal {
            conv,
            expand,
            concat,
            state,
        }) = generated::constructor_causal_region(&mut facts, i)
        else {
            continue;
        };
        let n = &g.nodes[conv];
        let cat = &g.nodes[concat];
        let history = &g.nodes[state];
        replacements.insert(
            conv,
            Node {
                op: Op::CausalDepthwiseConv,
                inputs: vec![
                    cat.inputs[1].clone(),
                    n.inputs[1].clone(),
                    cat.inputs[0].clone(),
                ],
                outputs: vec![n.outputs[0].clone(), history.outputs[0].clone()],
                attributes: Attributes {
                    position: history.attributes.starts[1].clone(),
                    ..Attributes::default()
                },
                ..n.clone()
            },
        );
        skipped.extend([concat, expand, state]);
    }
    g.nodes = std::mem::take(&mut g.nodes)
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
/// Decode construction uses the same ordered, fallible primitive bridge as FC.
pub(super) fn decode_rows(g: &mut Graph) -> Result<()> {
    let old = std::mem::take(&mut g.nodes);
    let mut lowerer = Lowerer {
        g: std::mem::take(g),
        scope: String::new(),
        counter: 0,
    };
    for n in old {
        rules::decode(&mut lowerer, &n)?;
    }
    *g = lowerer.g;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    fn causal() -> Graph {
        let p: Program = serde_json::from_str(include_str!(
            "../../../../tests/compiler/fixtures/causal_conv/causal_t7_c67.program.json"
        ))
        .unwrap();
        p.phases.into_values().next().unwrap()
    }
    #[test]
    fn failed_region_matches_preserve_values_names_and_nodes() {
        let mut positive = causal();
        causal_conv(&mut positive);
        assert!(positive
            .nodes
            .iter()
            .any(|n| n.op == Op::CausalDepthwiseConv));
        for variant in 0..6 {
            let mut g = causal();
            match variant {
                0 => g.outputs.push("joined".into()),
                1 => g.outputs.push("spatial".into()),
                2 => g.nodes[0].waits.push("ready".into()),
                3 => g.nodes[1].completes.push("done".into()),
                4 => {
                    let mut n = g.nodes[3].clone();
                    n.outputs = vec!["second".into()];
                    g.nodes.push(n);
                }
                _ => g.nodes[3].attributes.spatial.as_mut().unwrap().strides = vec![2, 1],
            }
            let before = serde_json::to_value(&g).unwrap();
            causal_conv(&mut g);
            assert_eq!(serde_json::to_value(&g).unwrap(), before, "case {variant}");
        }
    }
}
