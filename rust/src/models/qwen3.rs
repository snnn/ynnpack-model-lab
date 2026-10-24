// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Qwen3 equations authored using the public deferred program API.
use crate::{compiler::*, Error, Result};
use serde::Deserialize;
use std::collections::BTreeMap;
#[derive(Deserialize)]
pub struct Weight {
    pub shape: Vec<i64>,
    pub dtype: Dtype,
    pub asset: Asset,
    #[serde(default)]
    pub scale_asset: Option<Asset>,
    pub scales: Vec<Real>,
}
#[derive(Deserialize)]
pub struct Assets {
    pub format: String,
    pub recipe: String,
    pub config: serde_json::Value,
    pub weights: BTreeMap<String, Weight>,
}
fn dims(xs: &[i64]) -> Vec<Expr> {
    xs.iter().map(|x| Expr::Known(*x)).collect()
}
fn tensor(dtype: Dtype, shape: Vec<Expr>) -> TensorType {
    TensorType {
        dtype,
        shape,
        quant: None,
    }
}
struct Author<'a> {
    b: GraphBuilder,
    assets: &'a Assets,
    serial: usize,
    scope: String,
}
impl<'a> Author<'a> {
    fn name(&mut self, kind: &str) -> String {
        self.serial += 1;
        format!("{}/{kind}_{}", self.scope, self.serial)
    }
    fn op(&mut self, op: Op, inputs: &[&str], a: Attributes) -> Result<String> {
        let y = self.name(&op.name());
        self.b.operation(op, inputs, &y, a)?;
        self.b.graph.nodes.last_mut().unwrap().scope = self.scope.clone();
        Ok(y)
    }
    fn typed(&mut self, op: Op, inputs: &[&str], ty: TensorType, a: Attributes) -> Result<String> {
        let y = self.name(&op.name());
        self.b.value(
            &y,
            Value {
                tensor: ty,
                ..Value::default()
            },
        )?;
        self.b.operation(op, inputs, &y, a)?;
        self.b.graph.nodes.last_mut().unwrap().scope = self.scope.clone();
        Ok(y)
    }
    fn unary(&mut self, op: Op, x: &str) -> Result<String> {
        self.op(op, &[x], Attributes::default())
    }
    fn binary(&mut self, op: Op, x: &str, y: &str) -> Result<String> {
        self.op(op, &[x, y], Attributes::default())
    }
    fn scalar(&mut self, x: f32) -> Result<String> {
        let n = format!("constant/{:08x}", x.to_bits());
        if !self.b.graph.values.contains_key(&n) {
            self.b.value(
                &n,
                Value {
                    tensor: tensor(Dtype::F32, vec![]),
                    constant: true,
                    floats: vec![(x as f64).into()],
                    ..Value::default()
                },
            )?;
        }
        Ok(n)
    }
    fn weight(&mut self, name: &str, quantized: bool) -> Result<String> {
        let key = format!("weight/{name}");
        if !self.b.graph.values.contains_key(&key) {
            let w = self
                .assets
                .weights
                .get(name)
                .ok_or_else(|| Error::invalid(format!("Missing checkpoint weight {name}")))?;
            let mut ty = tensor(w.dtype, dims(&w.shape));
            if quantized && !w.scales.is_empty() {
                ty.quant = Some(Quantization {
                    axis: 0,
                    scales: w.scales.clone(),
                    zeros: vec![0],
                    ..Quantization::default()
                });
            }
            self.b.constant(&key, ty, w.asset.clone())?;
        }
        Ok(key)
    }
    fn linear(&mut self, x: &str, name: &str) -> Result<String> {
        let w = self.weight(name, true)?;
        self.op(Op::FullyConnected, &[x, &w], Attributes::default())
    }
    fn reshape(&mut self, x: &str, shape: Vec<Expr>) -> Result<String> {
        self.op(
            Op::Reshape,
            &[x],
            Attributes {
                shape,
                ..Attributes::default()
            },
        )
    }
    fn transpose(&mut self, x: &str, order: &[i64]) -> Result<String> {
        self.op(
            Op::Transpose,
            &[x],
            Attributes {
                integers: order.into(),
                ..Attributes::default()
            },
        )
    }
    fn rms(&mut self, x: &str, name: &str, eps: f32) -> Result<String> {
        let sq = self.unary(Op::Square, x)?;
        let mean = self.op(
            Op::Mean,
            &[&sq],
            Attributes {
                axes: vec![-1],
                ..Attributes::default()
            },
        )?;
        let eps = self.scalar(eps)?;
        let variance = self.binary(Op::Add, &mean, &eps)?;
        let inv = self.unary(Op::Rsqrt, &variance)?;
        let normalized = self.binary(Op::Mul, x, &inv)?;
        let w = self.weight(name, false)?;
        self.binary(Op::Mul, &normalized, &w)
    }
    fn rope(&mut self, x: &str, cos: &str, sin: &str, shape: Vec<Expr>) -> Result<String> {
        let d = shape[3].literal().unwrap();
        let mut half = shape;
        half[3] = Expr::Known(d / 2);
        let mut starts = dims(&[0, 0, 0, 0]);
        let first = self.op(
            Op::Slice,
            &[x],
            Attributes {
                starts: starts.clone(),
                lengths: half.clone(),
                ..Attributes::default()
            },
        )?;
        starts[3] = Expr::Known(d / 2);
        let last = self.op(
            Op::Slice,
            &[x],
            Attributes {
                starts,
                lengths: half,
                ..Attributes::default()
            },
        )?;
        let last = self.unary(Op::Neg, &last)?;
        let rotated = self.op(
            Op::Concat,
            &[&last, &first],
            Attributes {
                axis: 3,
                ..Attributes::default()
            },
        )?;
        let direct = self.binary(Op::Mul, x, cos)?;
        let turn = self.binary(Op::Mul, &rotated, sin)?;
        self.binary(Op::Add, &direct, &turn)
    }
    fn cache(
        &mut self,
        name: &str,
        x: &str,
        shape: Vec<Expr>,
        axis: i64,
    ) -> Result<(String, String)> {
        let position = Expr::Symbol(1);
        let end = Expr::sum([position.clone(), Expr::Symbol(2)]);
        let mut strides = vec![Expr::Known(1); shape.len()];
        for i in (0..shape.len() - 1).rev() {
            strides[i] = Expr::product([strides[i + 1].clone(), shape[i + 1].clone()]);
        }
        self.b.input(name, tensor(Dtype::F32, shape.clone()))?;
        let reference = ResourceRef {
            name: name.into(),
            owner: true,
            generation: 0,
            extent: position.clone(),
            origins: dims(&[0, 0, 0, 0]),
            strides: strides.clone(),
        };
        self.b.graph.values.get_mut(name).unwrap().resource = Some(reference.clone());
        self.b.graph.resources.push(Resource {
            name: name.into(),
            owner: name.into(),
            axis,
            entry: position.clone(),
            strides: vec![],
            selected: true,
        });
        let mut fresh_shape = shape.clone();
        fresh_shape[axis as usize] = Expr::Symbol(2);
        let fresh = self.op(
            Op::Slice,
            &[x],
            Attributes {
                starts: dims(&[0, 0, 0, 0]),
                lengths: fresh_shape,
                ..Attributes::default()
            },
        )?;
        let next = format!("{name}/next");
        let mut next_ref = reference.clone();
        next_ref.generation = 1;
        next_ref.extent = end.clone();
        self.b.value(
            &next,
            Value {
                tensor: tensor(Dtype::F32, shape.clone()),
                resource: Some(next_ref.clone()),
                ..Value::default()
            },
        )?;
        self.b.operation(
            Op::ResourceAppend,
            &[name, &fresh],
            &next,
            Attributes {
                axis,
                position,
                ..Attributes::default()
            },
        )?;
        let mut view_shape = shape;
        view_shape[axis as usize] = end.clone();
        let view = self.name("cache_view");
        next_ref.owner = false;
        self.b.value(
            &view,
            Value {
                tensor: tensor(Dtype::F32, view_shape),
                resource: Some(next_ref),
                ..Value::default()
            },
        )?;
        self.b.operation(
            Op::ResourceView,
            &[&next],
            &view,
            Attributes {
                axis,
                begin: Expr::Known(0),
                end,
                ..Attributes::default()
            },
        )?;
        Ok((next, view))
    }
}
impl Assets {
    fn size(&self, name: &str) -> Result<i64> {
        self.config[name]
            .as_i64()
            .filter(|v| *v > 0)
            .ok_or_else(|| Error::invalid(format!("Invalid model dimension {name}")))
    }
    pub fn program(&self, capacity: i64, prefill: i64) -> Result<Program> {
        if self.format != "qwen3-checkpoint-assets-v1"
            || self.recipe != "mixed_int8_int8_mlp_only"
            || capacity < 1
            || prefill < 1
            || prefill > capacity
        {
            return Err(Error::invalid("Invalid Qwen3 authoring contract"));
        }
        let mut p = Program::default();
        p.phases
            .insert("prefill".into(), self.phase(capacity, prefill, false)?);
        p.phases
            .insert("decode".into(), self.phase(capacity, 1, true)?);
        Ok(p)
    }
    fn phase(&self, capacity: i64, rows: i64, decode: bool) -> Result<Graph> {
        let (hidden, heads, kv, depth, layers, vocab) = (
            self.size("hidden_size")?,
            self.size("num_attention_heads")?,
            self.size("num_key_value_heads")?,
            self.size("head_dim")?,
            self.size("num_hidden_layers")?,
            self.size("vocab_size")?,
        );
        if heads % kv != 0 {
            return Err(Error::invalid("Qwen3 head geometry"));
        }
        let eps = self.config["rms_norm_eps"]
            .as_f64()
            .ok_or_else(|| Error::invalid("Missing RMS epsilon"))? as f32;
        let mut a = Author {
            b: GraphBuilder::default(),
            assets: self,
            serial: 0,
            scope: "embedding".into(),
        };
        a.b.input("token_ids", tensor(Dtype::I32, dims(&[1, rows])))?;
        a.b.input("input_pos", tensor(Dtype::I32, dims(&[rows])))?;
        a.b.input("mask", tensor(Dtype::F32, dims(&[1, 1, rows, capacity])))?;
        a.b.graph.symbols = vec![
            Symbol {
                id: 1,
                lower: 0,
                upper: capacity,
                binding: SymbolSource::Parameter {
                    name: "position".into(),
                    value: String::new(),
                },
            },
            Symbol {
                id: 2,
                lower: 1,
                upper: rows,
                binding: SymbolSource::Parameter {
                    name: "valid_rows".into(),
                    value: String::new(),
                },
            },
        ];
        let end = Expr::sum([Expr::Symbol(1), Expr::Symbol(2)]);
        a.b.graph.guards.push(Guard {
            lhs: end.clone(),
            rhs: Expr::Known(capacity),
            relation: "le".into(),
            reason: "Cache capacity".into(),
            mode: "checked".into(),
        });
        let embedding = a.weight("model.embed_tokens.weight", false)?;
        let codes = a.typed(
            Op::Gather,
            &[&embedding, "token_ids"],
            tensor(Dtype::I8, dims(&[1, rows, hidden])),
            Attributes::default(),
        )?;
        let ew = &self.weights["model.embed_tokens.weight"];
        a.b.constant(
            "embedding_scales",
            tensor(Dtype::F32, dims(&[vocab])),
            ew.scale_asset
                .clone()
                .ok_or_else(|| Error::invalid("Missing embedding scale asset"))?,
        )?;
        let scales = a.typed(
            Op::Gather,
            &["embedding_scales", "token_ids"],
            tensor(Dtype::F32, dims(&[1, rows])),
            Attributes::default(),
        )?;
        let scales = a.reshape(&scales, dims(&[1, rows, 1]))?;
        let mut x = a.typed(
            Op::DequantizeTensor,
            &[&codes, &scales],
            tensor(Dtype::F32, dims(&[1, rows, hidden])),
            Attributes::default(),
        )?;
        a.scope = "rotary".into();
        let positions = a.op(
            Op::Cast,
            &["input_pos"],
            Attributes {
                result_dtype: Some(Dtype::F32),
                ..Attributes::default()
            },
        )?;
        let positions = a.reshape(&positions, dims(&[rows, 1]))?;
        let inv = a.weight("rotary.inv_freq", false)?;
        let angles = a.binary(Op::Mul, &positions, &inv)?;
        let angles = a.op(
            Op::Concat,
            &[&angles, &angles],
            Attributes {
                axis: 1,
                ..Attributes::default()
            },
        )?;
        let cos = a.unary(Op::Cos, &angles)?;
        let sin = a.unary(Op::Sin, &angles)?;
        let cos = a.reshape(&cos, dims(&[1, 1, rows, depth]))?;
        let sin = a.reshape(&sin, dims(&[1, 1, rows, depth]))?;
        let mask = a.op(
            Op::Slice,
            &["mask"],
            Attributes {
                starts: dims(&[0, 0, 0, 0]),
                lengths: vec![
                    Expr::Known(1),
                    Expr::Known(1),
                    Expr::Known(rows),
                    end.clone(),
                ],
                ..Attributes::default()
            },
        )?;
        let mut states = vec![];
        for layer in 0..layers {
            let first = a.b.graph.nodes.len();
            a.scope = format!("layer/{layer}");
            let base = format!("model.layers.{layer}");
            let residual = x.clone();
            let normalized = a.rms(&x, &format!("{base}.input_layernorm.weight"), eps)?;
            let k = a.linear(&normalized, &format!("{base}.self_attn.k_proj.weight"))?;
            let k = a.reshape(&k, dims(&[1, rows, kv, depth]))?;
            let k = a.rms(&k, &format!("{base}.self_attn.k_norm.weight"), eps)?;
            let k = a.transpose(&k, &[0, 2, 1, 3])?;
            let k = a.rope(&k, &cos, &sin, dims(&[1, kv, rows, depth]))?;
            let v = a.linear(&normalized, &format!("{base}.self_attn.v_proj.weight"))?;
            let v = a.reshape(&v, dims(&[1, rows, kv, depth]))?;
            let v = a.transpose(&v, &[0, 2, 3, 1])?;
            let (kn, k) = a.cache(
                &format!("kv_cache_k_{layer}"),
                &k,
                dims(&[1, kv, capacity, depth]),
                2,
            )?;
            let (vn, v) = a.cache(
                &format!("kv_cache_v_{layer}"),
                &v,
                dims(&[1, kv, depth, capacity]),
                3,
            )?;
            states.extend([kn.clone(), vn.clone()]);
            if !decode && layer + 1 == layers {
                a.b.outline(first, &[kn, vn], &format!("decoder_{layer}"), &a.scope)?;
                break;
            }
            let q = a.linear(&normalized, &format!("{base}.self_attn.q_proj.weight"))?;
            let q = a.reshape(&q, dims(&[1, rows, heads, depth]))?;
            let q = a.rms(&q, &format!("{base}.self_attn.q_norm.weight"), eps)?;
            let q = a.transpose(&q, &[0, 2, 1, 3])?;
            let q = a.rope(&q, &cos, &sin, dims(&[1, heads, rows, depth]))?;
            let v = a.transpose(&v, &[0, 1, 3, 2])?;
            let attention = Attention {
                heads: (0..heads).map(|h| h / (heads / kv)).collect(),
                scale: (1.0 / (depth as f64).sqrt()).into(),
                mask: 2,
                causal: false,
                window: 0,
                query_position: Expr::Symbol(1),
                key_position: Expr::Known(0),
                query_length: None,
                key_length: None,
                all_masked_nan: true,
                reassociate: true,
                reorder_reduction: true,
                masked_nonfinite: true,
                fp32: true,
            };
            let context = a.typed(
                Op::Sdpa,
                &[&q, &k, &v, &mask],
                tensor(Dtype::F32, dims(&[1, heads, rows, depth])),
                Attributes {
                    attention: Some(attention),
                    ..Attributes::default()
                },
            )?;
            let context = a.transpose(&context, &[0, 2, 1, 3])?;
            let context = a.reshape(&context, dims(&[1, rows, heads * depth]))?;
            let out = a.linear(&context, &format!("{base}.self_attn.o_proj.weight"))?;
            x = a.binary(Op::Add, &residual, &out)?;
            let residual = x.clone();
            let normalized = a.rms(&x, &format!("{base}.post_attention_layernorm.weight"), eps)?;
            let gate = a.linear(&normalized, &format!("{base}.mlp.gate_proj.weight"))?;
            let up = a.linear(&normalized, &format!("{base}.mlp.up_proj.weight"))?;
            let sigmoid = a.unary(Op::Logistic, &gate)?;
            let swish = a.binary(Op::Mul, &gate, &sigmoid)?;
            let gated = a.binary(Op::Mul, &swish, &up)?;
            let down = a.linear(&gated, &format!("{base}.mlp.down_proj.weight"))?;
            x = a.binary(Op::Add, &residual, &down)?;
            a.b.outline(
                first,
                &[kn, vn, x.clone()],
                &format!("decoder_{layer}"),
                &a.scope,
            )?;
        }
        if decode {
            a.scope = "head".into();
            let norm = a.rms(&x, "model.norm.weight", eps)?;
            let logits = a.linear(&norm, "lm_head.weight")?;
            a.b.graph.outputs = vec![logits];
        } else {
            a.b.graph.outputs = states;
        }
        Ok(a.b.graph)
    }
}

impl Assets {
    /// Input/state roles for the public author, independent of a serialized plan.
    pub fn execution(&self, program: &Program, capacity: i64, rows: i64) -> Result<crate::runtime::ExecutionSpec> {
        use serde_json::json;
        let mut phases = BTreeMap::new();
        for phase in ["prefill", "decode"] {
            let g = program.phases.get(phase).ok_or_else(|| Error::invalid("Missing Qwen phase"))?;
            phases.insert(phase, json!({"logits":if phase=="decode"{g.outputs.first()}else{None},
                "row_policy":"padded","scalars":{"position":"position","valid_rows":"valid_rows"},
                "inputs":[{"name":"token_ids","dtype":"int32","shape":[1,"rows"],"recipe":{"kind":"tokens"}},
                    {"name":"input_pos","dtype":"int32","shape":["rows"],"recipe":{"kind":"positions"}},
                    {"name":"mask","dtype":"fp32","shape":[1,1,"rows","capacity"],
                     "recipe":{"kind":"mask","window":null,"masked":"finite_min"}}]}));
        }
        let g = &program.phases["decode"];
        let resources = g.resources.iter().map(|r| {
            let shape = g.values[&r.owner].tensor.shape.iter().map(|d| d.literal()
                .ok_or_else(|| Error::invalid("Qwen resource must have fixed capacity")))
                .collect::<Result<Vec<_>>>()?;
            Ok(json!({"name":r.owner,"axis":r.axis,"dtype":"fp32","shape":shape}))
        }).collect::<Result<Vec<_>>>()?;
        let spec: crate::runtime::ExecutionSpec = serde_json::from_value(json!({
            "format":"ynn-llm-execution","contract":2,
            "compatibility":crate::runtime::execution::Compatibility::ynnpack(),
            "model":"qwen3-rust","capacity":capacity,
            "prefill_rows":rows,"vocabulary":self.config["vocab_size"],"prefill_after_decode":false,
            "graphs":phases,"resources":resources,"fixed_states":[],"embeddings":{}}))?;
        spec.validate()?;
        Ok(spec)
    }
}
