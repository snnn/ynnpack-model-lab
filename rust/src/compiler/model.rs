// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
pub use crate::plan::Expr;
use crate::{Error, Result};
use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;

/// IEEE binary64 bits, including signed zero and nonfinite values.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct Real(pub u64);
impl Real {
    pub fn get(self) -> f64 {
        f64::from_bits(self.0)
    }
}
impl From<f64> for Real {
    fn from(x: f64) -> Self {
        Self(x.to_bits())
    }
}
impl Default for Real {
    fn default() -> Self {
        1.0.into()
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum Dtype {
    F32,
    F16,
    Bf16,
    F64,
    I2,
    I4,
    I8,
    U8,
    I32,
    Bool,
}
impl Default for Dtype {
    fn default() -> Self {
        Self::F32
    }
}
impl Dtype {
    pub fn bits(self) -> usize {
        match self {
            Self::I2 => 2,
            Self::I4 => 4,
            Self::I8 | Self::U8 | Self::Bool => 8,
            Self::F16 | Self::Bf16 => 16,
            Self::F32 | Self::I32 => 32,
            Self::F64 => 64,
        }
    }
    pub fn native(self) -> &'static str {
        match self {
            Self::F32 => "fp32",
            Self::F16 => "fp16",
            Self::Bf16 => "bf16",
            Self::F64 => "fp64",
            Self::I2 => "int2",
            Self::I4 => "int4",
            Self::I8 => "int8",
            Self::U8 | Self::Bool => "uint8",
            Self::I32 => "int32",
        }
    }
}
#[derive(Clone, Debug, Default, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Quantization {
    pub axis: i64,
    #[serde(default)]
    pub scales: Vec<Real>,
    #[serde(default)]
    pub zeros: Vec<i64>,
    #[serde(default)]
    pub parameters: Option<QuantizationParameters>,
    #[serde(default)]
    pub blockwise: bool,
}
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct QuantizationParameters {
    pub scales: String,
    pub zeros: String,
    pub axes: Vec<i64>,
    pub blocks: Vec<i64>,
}
#[derive(Clone, Debug, Default, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct TensorType {
    pub dtype: Dtype,
    pub shape: Vec<Expr>,
    #[serde(default)]
    pub quant: Option<Quantization>,
}
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Asset {
    pub path: String,
    pub bytes: usize,
    pub sha256: String,
}
#[derive(Clone, Debug, Default, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Value {
    pub tensor: TensorType,
    #[serde(default)]
    pub data: Option<Asset>,
    #[serde(default)]
    pub integers: Vec<i64>,
    #[serde(default)]
    pub floats: Vec<Real>,
    #[serde(default)]
    pub constant: bool,
    #[serde(default)]
    pub resource: Option<ResourceRef>,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ResourceRef {
    pub name: String,
    pub owner: bool,
    pub generation: u64,
    pub extent: Expr,
    pub origins: Vec<Expr>,
    pub strides: Vec<Expr>,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Resource {
    pub name: String,
    pub owner: String,
    pub axis: i64,
    pub entry: Expr,
    pub strides: Vec<Expr>,
    pub selected: bool,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(tag = "source", rename_all = "snake_case", deny_unknown_fields)]
pub enum SymbolSource {
    Axis {
        value: String,
        axis: usize,
    },
    Parameter {
        name: String,
        #[serde(default)]
        value: String,
    },
    Instance {
        name: String,
    },
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Symbol {
    pub id: u32,
    pub lower: i64,
    pub upper: i64,
    pub binding: SymbolSource,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Guard {
    pub lhs: Expr,
    pub rhs: Expr,
    pub relation: String,
    pub reason: String,
    pub mode: String,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Attention {
    pub heads: Vec<i64>,
    pub scale: Real,
    pub mask: i64,
    pub causal: bool,
    pub window: i64,
    pub query_position: Expr,
    pub key_position: Expr,
    pub query_length: Option<Expr>,
    pub key_length: Option<Expr>,
    pub all_masked_nan: bool,
    pub reassociate: bool,
    pub reorder_reduction: bool,
    pub masked_nonfinite: bool,
    pub fp32: bool,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Spatial {
    pub kernel: Vec<i64>,
    pub strides: Vec<i64>,
    pub dilations: Vec<i64>,
    pub same: bool,
    pub multiplier: i64,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Call {
    pub function: String,
    pub indices: BTreeMap<u32, Expr>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum Op {
    #[serde(rename = "copy")]
    Copy,
    #[serde(rename = "add")]
    Add,
    #[serde(rename = "sub")]
    Sub,
    #[serde(rename = "mul")]
    Mul,
    #[serde(rename = "div")]
    Div,
    #[serde(rename = "maximum")]
    Maximum,
    #[serde(rename = "minimum")]
    Minimum,
    #[serde(rename = "pow")]
    Pow,
    #[serde(rename = "matmul")]
    Matmul,
    #[serde(rename = "fully_connected")]
    FullyConnected,
    #[serde(rename = "weight_only_linear")]
    WeightOnlyLinear,
    #[serde(rename = "softmax")]
    Softmax,
    #[serde(rename = "mean")]
    Mean,
    #[serde(rename = "reduce_sum")]
    ReduceSum,
    #[serde(rename = "reduce_max")]
    ReduceMax,
    #[serde(rename = "reduce_min")]
    ReduceMin,
    #[serde(rename = "reduce_min_max")]
    ReduceMinMax,
    #[serde(rename = "reduce_sum_squared")]
    ReduceSumSquared,
    #[serde(rename = "exp")]
    Exp,
    #[serde(rename = "erf")]
    Erf,
    #[serde(rename = "abs")]
    Abs,
    #[serde(rename = "log")]
    Log,
    #[serde(rename = "logistic")]
    Logistic,
    #[serde(rename = "tanh")]
    Tanh,
    #[serde(rename = "neg")]
    Neg,
    #[serde(rename = "sin")]
    Sin,
    #[serde(rename = "cos")]
    Cos,
    #[serde(rename = "sqrt")]
    Sqrt,
    #[serde(rename = "rsqrt")]
    Rsqrt,
    #[serde(rename = "square")]
    Square,
    #[serde(rename = "round")]
    Round,
    #[serde(rename = "cast")]
    Cast,
    #[serde(rename = "prelu")]
    Prelu,
    #[serde(rename = "hard_swish")]
    HardSwish,
    #[serde(rename = "leaky_relu")]
    LeakyRelu,
    #[serde(rename = "elu")]
    Elu,
    #[serde(rename = "relu")]
    Relu,
    #[serde(rename = "relu6")]
    Relu6,
    #[serde(rename = "relu_n1_to_1")]
    ReluN1To1,
    #[serde(rename = "relu_0_to_1")]
    Relu0To1,
    #[serde(rename = "l2_normalization")]
    L2Normalization,
    #[serde(rename = "l2_norm_epsilon")]
    L2NormEpsilon,
    #[serde(rename = "gelu")]
    Gelu,
    #[serde(rename = "shape_tensor")]
    ShapeTensor,
    #[serde(rename = "reshape")]
    Reshape,
    #[serde(rename = "transpose")]
    Transpose,
    #[serde(rename = "slice")]
    Slice,
    #[serde(rename = "concat")]
    Concat,
    #[serde(rename = "broadcast_to")]
    BroadcastTo,
    #[serde(rename = "broadcast_like")]
    BroadcastLike,
    #[serde(rename = "slice_like")]
    SliceLike,
    #[serde(rename = "fuse_dims")]
    FuseDims,
    #[serde(rename = "split_dim")]
    SplitDim,
    #[serde(rename = "split")]
    Split,
    #[serde(rename = "even_split")]
    EvenSplit,
    #[serde(rename = "unstack")]
    Unstack,
    #[serde(rename = "stack")]
    Stack,
    #[serde(rename = "squeeze")]
    Squeeze,
    #[serde(rename = "expand_dims")]
    ExpandDims,
    #[serde(rename = "reverse")]
    Reverse,
    #[serde(rename = "tile")]
    Tile,
    #[serde(rename = "pad")]
    Pad,
    #[serde(rename = "select")]
    Select,
    #[serde(rename = "gather")]
    Gather,
    #[serde(rename = "less")]
    Less,
    #[serde(rename = "less_equal")]
    LessEqual,
    #[serde(rename = "greater")]
    Greater,
    #[serde(rename = "greater_equal")]
    GreaterEqual,
    #[serde(rename = "equal")]
    Equal,
    #[serde(rename = "not_equal")]
    NotEqual,
    #[serde(rename = "quantize")]
    Quantize,
    #[serde(rename = "dequantize")]
    Dequantize,
    #[serde(rename = "quantization_parameters")]
    QuantizationParameters,
    #[serde(rename = "quantization_codes")]
    QuantizationCodes,
    #[serde(rename = "with_quantization")]
    WithQuantization,
    #[serde(rename = "resource_append")]
    ResourceAppend,
    #[serde(rename = "resource_view")]
    ResourceView,
    #[serde(rename = "sdpa")]
    Sdpa,
    #[serde(rename = "causal_mask")]
    CausalMask,
    #[serde(rename = "scheduled_mask")]
    ScheduledMask,
    #[serde(rename = "dynamic_matmul")]
    DynamicMatmul,
    #[serde(rename = "dynamic_quantization")]
    DynamicQuantization,
    #[serde(rename = "quantize_tensor")]
    QuantizeTensor,
    #[serde(rename = "dequantize_tensor")]
    DequantizeTensor,
    #[serde(rename = "dot")]
    Dot,
    #[serde(rename = "get_shape")]
    GetShape,
    #[serde(rename = "polynomial")]
    Polynomial,
    #[serde(rename = "native_weight_only_linear")]
    NativeWeightOnlyLinear,
    #[serde(rename = "blockwise_fully_connected")]
    BlockwiseFullyConnected,
    #[serde(rename = "conv2d")]
    Conv2D,
    #[serde(rename = "depthwise_conv2d")]
    DepthwiseConv2D,
    #[serde(rename = "average_pool2d")]
    AveragePool2D,
    #[serde(rename = "max_pool2d")]
    MaxPool2D,
    #[serde(rename = "gated_delta_rule")]
    GatedDeltaRule,
    #[serde(rename = "causal_depthwise_conv")]
    CausalDepthwiseConv,
    #[serde(rename = "call")]
    Call,
}
impl Op {
    pub fn name(self) -> String {
        serde_json::to_value(self)
            .unwrap()
            .as_str()
            .unwrap()
            .to_owned()
    }
}
fn zero() -> Expr {
    Expr::Known(0)
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(default, deny_unknown_fields)]
pub struct Attributes {
    pub axis: i64,
    pub axes: Vec<i64>,
    pub integers: Vec<i64>,
    pub sizes: Vec<i64>,
    pub shape: Vec<Expr>,
    pub starts: Vec<Expr>,
    pub lengths: Vec<Expr>,
    pub begin: Expr,
    pub end: Expr,
    pub position: Expr,
    pub window: i64,
    pub adj_x: bool,
    pub adj_y: bool,
    pub keep_dims: bool,
    pub approximate: bool,
    pub fold_constants: bool,
    pub beta: Real,
    pub coefficients: Vec<Real>,
    pub pad_mode: i64,
    pub contraction_dims: usize,
    pub attention: Option<Attention>,
    pub spatial: Option<Spatial>,
    pub call: Option<Call>,
    pub result_dtype: Option<Dtype>,
}
impl Default for Attributes {
    fn default() -> Self {
        Self {
            axis: 0,
            axes: vec![],
            integers: vec![],
            sizes: vec![],
            shape: vec![],
            starts: vec![],
            lengths: vec![],
            begin: zero(),
            end: zero(),
            position: zero(),
            window: 0,
            adj_x: false,
            adj_y: false,
            keep_dims: true,
            approximate: false,
            fold_constants: true,
            beta: Real::default(),
            coefficients: vec![],
            pad_mode: 0,
            contraction_dims: 1,
            attention: None,
            spatial: None,
            call: None,
            result_dtype: None,
        }
    }
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Node {
    pub op: Op,
    pub inputs: Vec<String>,
    pub outputs: Vec<String>,
    #[serde(default)]
    pub attributes: Attributes,
    #[serde(default)]
    pub waits: Vec<String>,
    #[serde(default)]
    pub completes: Vec<String>,
    #[serde(default)]
    pub scope: String,
}
#[derive(Clone, Debug, Default, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Graph {
    pub values: BTreeMap<String, Value>,
    pub inputs: Vec<String>,
    pub outputs: Vec<String>,
    pub nodes: Vec<Node>,
    #[serde(default)]
    pub symbols: Vec<Symbol>,
    #[serde(default)]
    pub guards: Vec<Guard>,
    #[serde(default)]
    pub resources: Vec<Resource>,
    #[serde(default)]
    pub completions: Vec<String>,
    #[serde(default)]
    pub functions: BTreeMap<String, Graph>,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(default, deny_unknown_fields)]
pub struct CompileOptions {
    pub cleanup: bool,
    pub target_views: bool,
    /// Diagnostic ablation: retain only `fuse` or `split` target views.
    pub keep_views: Option<String>,
    pub schedule_masks: bool,
    pub group_decode_rows: bool,
    pub packed_adapter: bool,
    pub check_shapes: bool,
}
impl Default for CompileOptions {
    fn default() -> Self {
        Self {
            cleanup: true,
            target_views: true,
            keep_views: None,
            schedule_masks: true,
            group_decode_rows: false,
            packed_adapter: false,
            check_shapes: true,
        }
    }
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Program {
    pub version: u32,
    pub phases: BTreeMap<String, Graph>,
    #[serde(default)]
    pub options: CompileOptions,
    #[serde(default, skip_serializing_if = "BTreeMap::is_empty")]
    pub phase_options: BTreeMap<String, CompileOptions>,
}
impl Default for Program {
    fn default() -> Self {
        Self {
            version: 1,
            phases: BTreeMap::new(),
            options: CompileOptions::default(),
            phase_options: BTreeMap::new(),
        }
    }
}
impl Expr {
    pub fn constant(x: i64) -> Self {
        Self::Known(x)
    }
    pub fn symbol(x: u32) -> Self {
        Self::Symbol(x)
    }
    pub fn literal(&self) -> Option<i64> {
        if let Self::Known(x) = self {
            Some(*x)
        } else {
            None
        }
    }
    pub fn product(xs: impl IntoIterator<Item = Self>) -> Self {
        let xs: Vec<_> = xs.into_iter().collect();
        if let Some(v) = xs.iter().try_fold(1i64, |a, x| a.checked_mul(x.literal()?)) {
            Self::Known(v)
        } else {
            Self::Mul(xs)
        }
    }
    pub fn sum(xs: impl IntoIterator<Item = Self>) -> Self {
        let xs: Vec<_> = xs.into_iter().collect();
        if let Some(v) = xs.iter().try_fold(0i64, |a, x| a.checked_add(x.literal()?)) {
            Self::Known(v)
        } else {
            Self::Add(xs)
        }
    }
    pub fn render(&self) -> String {
        match self {
            Self::Known(n) => n.to_string(),
            Self::Symbol(n) => format!("s{n}"),
            x => {
                let (name, args) = match x {
                    Self::Add(a) => ("add", a),
                    Self::Mul(a) => ("mul", a),
                    Self::Min(a) => ("min", a),
                    Self::Max(a) => ("max", a),
                    Self::FloorDiv(a) => ("floor_div", a),
                    Self::CeilDiv(a) => ("ceil_div", a),
                    _ => unreachable!(),
                };
                format!(
                    "{}({})",
                    name,
                    args.iter().map(Self::render).collect::<Vec<_>>().join(", ")
                )
            }
        }
    }
}
pub(crate) fn axis(axis: i64, rank: usize) -> Result<usize> {
    if rank == 0 || axis < -(rank as i64) || axis >= rank as i64 {
        return Err(Error::invalid("Axis outside tensor rank"));
    }
    Ok(axis.rem_euclid(rank as i64) as usize)
}

/// Compare dimension geometry without rewriting checked runtime arithmetic.
pub(crate) fn geometry(e: &Expr) -> String {
    fn normalize(e: &Expr) -> Expr {
        match e {
            Expr::Mul(xs) => {
                let mut terms = vec![];
                let mut k = 1i64;
                for x in xs.iter().map(normalize) {
                    let factors = if let Expr::Mul(ys) = x { ys } else { vec![x] };
                    for y in factors {
                        if let Expr::Known(v) = y {
                            if let Some(n) = k.checked_mul(v) {
                                k = n
                            } else {
                                terms.push(Expr::Known(v));
                            }
                        } else {
                            terms.push(y);
                        }
                    }
                }
                if k != 1 || terms.is_empty() {
                    terms.push(Expr::Known(k));
                }
                terms.sort_by_cached_key(|x| serde_json::to_string(x).unwrap());
                if terms.len() == 1 {
                    terms.remove(0)
                } else {
                    Expr::Mul(terms)
                }
            }
            Expr::Add(xs) => {
                let mut terms = xs
                    .iter()
                    .map(normalize)
                    .filter(|x| x.literal() != Some(0))
                    .collect::<Vec<_>>();
                if terms.len() == 1 {
                    terms.remove(0)
                } else if terms.is_empty() {
                    Expr::Known(0)
                } else {
                    Expr::Add(terms)
                }
            }
            _ => e.clone(),
        }
    }
    serde_json::to_string(&normalize(e)).unwrap()
}

/// Encode literal hints with the same exact storage convention as emission.
pub(crate) fn literal_bytes(v: &Value) -> Result<Vec<u8>> {
    let mut bytes = vec![];
    if !v.floats.is_empty() {
        for n in &v.floats {
            if v.tensor.dtype == Dtype::F32 {
                bytes.extend((n.get() as f32).to_le_bytes());
            } else {
                return Err(Error::invalid(
                    "Non-FP32 literals require exact asset bytes",
                ));
            }
        }
    } else if v.tensor.dtype.bits() < 8 {
        let bits = v.tensor.dtype.bits();
        let lo = -(1i64 << (bits - 1));
        let hi = (1i64 << (bits - 1)) - 1;
        bytes.resize((v.integers.len() * bits).div_ceil(8), 0);
        for (i, x) in v.integers.iter().enumerate() {
            if *x < lo || *x > hi {
                return Err(Error::invalid("Packed constant code range"));
            }
            bytes[i * bits / 8] |= ((*x as u8) & ((1 << bits) - 1)) << ((i * bits) % 8);
        }
    } else {
        for x in &v.integers {
            match v.tensor.dtype {
                Dtype::I32 => bytes.extend(
                    i32::try_from(*x)
                        .map_err(|_| Error::invalid("INT32 literal overflow"))?
                        .to_le_bytes(),
                ),
                Dtype::I8 => bytes.push(
                    i8::try_from(*x).map_err(|_| Error::invalid("INT8 literal overflow"))? as u8,
                ),
                Dtype::U8 | Dtype::Bool => bytes
                    .push(u8::try_from(*x).map_err(|_| Error::invalid("Byte literal overflow"))?),
                _ => return Err(Error::invalid("Literal needs exact byte asset")),
            }
        }
    }
    if bytes.is_empty() {
        bytes.push(0);
    }
    Ok(bytes)
}

/// Physical element strides selected by this backend. Capacity strides survive
/// every live-history view; logical extent never changes allocation geometry.
pub(crate) fn resolved_strides(resource: &Resource, tensor: &TensorType) -> Vec<Expr> {
    if tensor.dtype.bits() < 8 && !resource.strides.is_empty() {
        return resource.strides.clone();
    }
    let mut stride = Expr::Known(1);
    let mut result = vec![];
    for d in tensor.shape.iter().rev() {
        result.push(stride.clone());
        stride = Expr::product([
            stride,
            d.literal()
                .map(|n| Expr::Known(n.max(1)))
                .unwrap_or_else(|| Expr::Max(vec![Expr::Known(1), d.clone()])),
        ]);
    }
    result.reverse();
    result
}
