// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Small immutable target temporaries. Never fold an explicitly evaluated boundary.
use super::*;
fn shape(v: &Value) -> Option<Vec<usize>> {
    v.tensor
        .shape
        .iter()
        .map(|d| usize::try_from(d.literal()?).ok())
        .collect()
}
fn numbers(v: &Value) -> Option<Vec<f64>> {
    if !v.constant {
        return None;
    }
    if !v.floats.is_empty() {
        Some(v.floats.iter().map(|x| x.get()).collect())
    } else if !v.integers.is_empty() {
        Some(v.integers.iter().map(|x| *x as f64).collect())
    } else if shape(v)?.iter().product::<usize>() == 0 {
        Some(vec![])
    } else {
        None
    }
}
fn cast(x: f64, d: Dtype) -> f64 {
    match d {
        Dtype::F32 => (x as f32) as f64,
        Dtype::F64 => x,
        Dtype::Bool => {
            if x != 0.0 {
                1.0
            } else {
                0.0
            }
        }
        Dtype::I2 => x.trunc().clamp(-2.0, 1.0),
        Dtype::I4 => x.trunc().clamp(-8.0, 7.0),
        Dtype::I8 => (x as i8) as f64,
        Dtype::U8 => (x as u8) as f64,
        Dtype::I32 => (x as i32) as f64,
        _ => x,
    }
}
fn index(mut flat: usize, shape: &[usize]) -> Vec<usize> {
    let mut c = vec![0; shape.len()];
    for i in (0..shape.len()).rev() {
        c[i] = flat % shape[i];
        flat /= shape[i];
    }
    c
}
fn flat(c: &[usize], s: &[usize]) -> usize {
    c.iter().zip(s).fold(0, |i, (c, s)| i * s + c)
}
fn broadcast_index(c: &[usize], shape: &[usize]) -> usize {
    flat(
        &c[c.len() - shape.len()..]
            .iter()
            .zip(shape)
            .map(|(i, n)| if *n == 1 { 0 } else { *i })
            .collect::<Vec<_>>(),
        shape,
    )
}
fn evaluate(g: &Graph, n: &Node) -> Option<Vec<f64>> {
    use Op::*;
    if !n.waits.is_empty()
        || !n.completes.is_empty()
        || !n.attributes.fold_constants
        || n.outputs.len() != 1
    {
        return None;
    }
    let output = &g.values[&n.outputs[0]];
    let dims = shape(output)?;
    let count = dims.iter().try_fold(1usize, |a, b| a.checked_mul(*b))?;
    if count > 65536 {
        return None;
    }
    let xs = n
        .inputs
        .iter()
        .map(|x| numbers(g.values.get(x)?))
        .collect::<Option<Vec<_>>>()?;
    let shapes = n
        .inputs
        .iter()
        .map(|x| shape(&g.values[x]))
        .collect::<Option<Vec<_>>>()?;
    // Preserve backend-specific NaN and signed-zero min/max behavior.
    if (xs.iter().flatten().any(|x| !x.is_finite())
        && !(n.op == Cast && output.tensor.dtype == Dtype::Bool))
        || matches!(n.op, Minimum | Maximum)
    {
        return None;
    }
    let a = &n.attributes;
    let values = match n.op {
        Copy | Reshape | Squeeze | ExpandDims | FuseDims | SplitDim | QuantizationCodes
        | WithQuantization
            if xs[0].len() == count =>
        {
            xs[0].clone()
        }
        Cast if matches!(
            output.tensor.dtype,
            Dtype::F32
                | Dtype::F64
                | Dtype::I2
                | Dtype::I4
                | Dtype::I8
                | Dtype::I32
                | Dtype::U8
                | Dtype::Bool
        ) =>
        {
            xs[0]
                .iter()
                .map(|x| cast(*x, output.tensor.dtype))
                .collect()
        }
        Transpose => {
            let input = &shapes[0];
            (0..count)
                .map(|i| {
                    let c = index(i, &dims);
                    let mut src = vec![0; input.len()];
                    for (j, a) in a.integers.iter().enumerate() {
                        src[*a as usize] = c[j];
                    }
                    xs[0][flat(&src, input)]
                })
                .collect()
        }
        Reverse => {
            let axes = a
                .axes
                .iter()
                .map(|a| axis(*a, shapes[0].len()).ok())
                .collect::<Option<Vec<_>>>()?;
            (0..count)
                .map(|i| {
                    let mut c = index(i, &dims);
                    for a in &axes {
                        c[*a] = dims[*a] - 1 - c[*a];
                    }
                    xs[0][flat(&c, &shapes[0])]
                })
                .collect()
        }
        BroadcastTo => (0..count)
            .map(|i| xs[0][broadcast_index(&index(i, &dims), &shapes[0])])
            .collect(),
        Slice => {
            let starts = if a.starts.is_empty() {
                a.integers
                    .iter()
                    .map(|x| usize::try_from(*x).ok())
                    .collect::<Option<Vec<_>>>()?
            } else {
                a.starts
                    .iter()
                    .map(|d| usize::try_from(d.literal()?).ok())
                    .collect::<Option<Vec<_>>>()?
            };
            (0..count)
                .map(|i| {
                    let c = index(i, &dims)
                        .iter()
                        .zip(&starts)
                        .map(|(i, s)| i + s)
                        .collect::<Vec<_>>();
                    xs[0].get(flat(&c, &shapes[0])).copied()
                })
                .collect::<Option<_>>()?
        }
        Add | Sub | Mul | Div | Minimum | Maximum if output.tensor.dtype == Dtype::F32 => (0
            ..count)
            .map(|i| {
                let c = index(i, &dims);
                let x = xs[0][broadcast_index(&c, &shapes[0])] as f32;
                let y = xs[1][broadcast_index(&c, &shapes[1])] as f32;
                (match n.op {
                    Add => x + y,
                    Sub => x - y,
                    Mul => x * y,
                    Div => x / y,
                    Minimum => x.min(y),
                    Maximum => x.max(y),
                    _ => unreachable!(),
                }) as f64
            })
            .collect(),
        Neg if output.tensor.dtype == Dtype::I32 => xs[0]
            .iter()
            .map(|x| (*x as i32).wrapping_neg() as f64)
            .collect(),
        ReduceSum if output.tensor.dtype == Dtype::I32 => {
            let axes = a
                .axes
                .iter()
                .map(|a| axis(*a, shapes[0].len()).ok())
                .collect::<Option<BTreeSet<_>>>()?;
            let mut sums = vec![0i32; count];
            for (i, x) in xs[0].iter().enumerate() {
                let c = index(i, &shapes[0])
                    .into_iter()
                    .enumerate()
                    .filter_map(|(a, c)| {
                        if axes.contains(&a) {
                            n.attributes.keep_dims.then_some(0)
                        } else {
                            Some(c)
                        }
                    })
                    .collect::<Vec<_>>();
                let dest = flat(&c, &dims);
                sums[dest] = sums[dest].wrapping_add(*x as i32);
            }
            sums.iter().map(|x| *x as f64).collect()
        }
        _ => return None,
    };
    Some(values)
}
pub(super) fn fold(g: &mut Graph) {
    let nodes = std::mem::take(&mut g.nodes);
    for n in nodes {
        if let Some(data) = evaluate(g, &n) {
            let v = g.values.get_mut(&n.outputs[0]).unwrap();
            v.constant = true;
            v.data = None;
            if matches!(v.tensor.dtype, Dtype::F32 | Dtype::F64) {
                v.floats = data.into_iter().map(Real::from).collect();
                v.integers.clear();
            } else {
                v.integers = data.into_iter().map(|x| x as i64).collect();
                v.floats.clear();
            }
        } else {
            g.nodes.push(n);
        }
    }
}
