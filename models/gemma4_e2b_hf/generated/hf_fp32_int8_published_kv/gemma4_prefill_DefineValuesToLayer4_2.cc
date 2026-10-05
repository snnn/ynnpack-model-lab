// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "DefineValues"
LAB_YNN_BUILDER_NOINLINE void BuildDefineValuesPart14(Context& ctx) {
  auto* g = ctx.g;
  const auto& weights = ctx.weights;
  g->Tensor(3584, "model.layers.11.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.11.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3585, "model.layers.11.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.11.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3586, "model.layers.11.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.11.self_attn.k_norm.weight", 512));
  g->Tensor(3587, "model.layers.11.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.11.self_attn.k_proj.weight", 196608));
  g->Tensor(3588, "model.layers.11.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.11.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3589, "model.layers.11.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.11.self_attn.o_proj.weight", 1572864));
  g->Tensor(3590, "model.layers.11.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.11.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3591, "model.layers.11.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.11.self_attn.q_norm.weight", 512));
  g->Tensor(3592, "model.layers.11.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.11.self_attn.q_proj.weight", 1572864));
  g->Tensor(3593, "model.layers.11.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.11.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3594, "model.layers.11.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.11.self_attn.v_proj.weight", 196608));
  g->Tensor(3595, "model.layers.11.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.11.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3596, "model.layers.12.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.12.input_layernorm.weight", 3072));
  g->Tensor(3597, "model.layers.12.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.12.layer_scalar", 2));
  g->Tensor(3598, "model.layers.12.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.12.mlp.down_proj.weight", 4718592));
  g->Tensor(3599, "model.layers.12.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.12.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3600, "model.layers.12.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.12.mlp.gate_proj.weight", 4718592));
  g->Tensor(3601, "model.layers.12.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.12.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3602, "model.layers.12.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.12.mlp.up_proj.weight", 4718592));
  g->Tensor(3603, "model.layers.12.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.12.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3604, "model.layers.12.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.12.per_layer_input_gate.weight", 393216));
  g->Tensor(3605, "model.layers.12.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.12.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3606, "model.layers.12.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.12.per_layer_projection.weight", 393216));
  g->Tensor(3607, "model.layers.12.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.12.per_layer_projection.weight_scale", 6144));
  g->Tensor(3608, "model.layers.12.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.12.post_attention_layernorm.weight", 3072));
  g->Tensor(3609, "model.layers.12.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.12.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3610, "model.layers.12.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.12.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3611, "model.layers.12.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.12.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3612, "model.layers.12.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.12.self_attn.k_norm.weight", 512));
  g->Tensor(3613, "model.layers.12.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.12.self_attn.k_proj.weight", 196608));
  g->Tensor(3614, "model.layers.12.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.12.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3615, "model.layers.12.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.12.self_attn.o_proj.weight", 1572864));
  g->Tensor(3616, "model.layers.12.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.12.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3617, "model.layers.12.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.12.self_attn.q_norm.weight", 512));
  g->Tensor(3618, "model.layers.12.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.12.self_attn.q_proj.weight", 1572864));
  g->Tensor(3619, "model.layers.12.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.12.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3620, "model.layers.12.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.12.self_attn.v_proj.weight", 196608));
  g->Tensor(3621, "model.layers.12.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.12.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3622, "model.layers.13.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.13.input_layernorm.weight", 3072));
  g->Tensor(3623, "model.layers.13.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.13.layer_scalar", 2));
  g->Tensor(3624, "model.layers.13.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.13.mlp.down_proj.weight", 4718592));
  g->Tensor(3625, "model.layers.13.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.13.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3626, "model.layers.13.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.13.mlp.gate_proj.weight", 4718592));
  g->Tensor(3627, "model.layers.13.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.13.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3628, "model.layers.13.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.13.mlp.up_proj.weight", 4718592));
  g->Tensor(3629, "model.layers.13.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.13.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3630, "model.layers.13.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.13.per_layer_input_gate.weight", 393216));
  g->Tensor(3631, "model.layers.13.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.13.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3632, "model.layers.13.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.13.per_layer_projection.weight", 393216));
  g->Tensor(3633, "model.layers.13.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.13.per_layer_projection.weight_scale", 6144));
  g->Tensor(3634, "model.layers.13.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.13.post_attention_layernorm.weight", 3072));
  g->Tensor(3635, "model.layers.13.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.13.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3636, "model.layers.13.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.13.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3637, "model.layers.13.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.13.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3638, "model.layers.13.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.13.self_attn.k_norm.weight", 512));
  g->Tensor(3639, "model.layers.13.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.13.self_attn.k_proj.weight", 196608));
  g->Tensor(3640, "model.layers.13.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.13.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3641, "model.layers.13.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.13.self_attn.o_proj.weight", 1572864));
  g->Tensor(3642, "model.layers.13.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.13.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3643, "model.layers.13.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.13.self_attn.q_norm.weight", 512));
  g->Tensor(3644, "model.layers.13.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.13.self_attn.q_proj.weight", 1572864));
  g->Tensor(3645, "model.layers.13.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.13.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3646, "model.layers.13.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.13.self_attn.v_proj.weight", 196608));
  g->Tensor(3647, "model.layers.13.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.13.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3648, "model.layers.14.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.14.input_layernorm.weight", 3072));
  g->Tensor(3649, "model.layers.14.self_attn.k_norm.weight", ynn_type_bf16, {512}, 0, weights("@hf/model.layers.14.self_attn.k_norm.weight", 1024));
  g->Tensor(3650, "model.layers.14.self_attn.k_proj.weight", ynn_type_int4, {512,1536}, 0, weights("@hf/model.layers.14.self_attn.k_proj.weight", 393216));
  g->Tensor(3651, "model.layers.14.self_attn.k_proj.weight_scale", ynn_type_fp32, {512,1}, 0, weights("@hf/model.layers.14.self_attn.k_proj.weight_scale", 2048));
  g->Tensor(3652, "model.layers.14.self_attn.v_proj.weight", ynn_type_int4, {512,1536}, 0, weights("@hf/model.layers.14.self_attn.v_proj.weight", 393216));
  g->Tensor(3653, "model.layers.14.self_attn.v_proj.weight_scale", ynn_type_fp32, {512,1}, 0, weights("@hf/model.layers.14.self_attn.v_proj.weight_scale", 2048));
  g->Tensor(3654, "model.layers.2.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.2.input_layernorm.weight", 3072));
  g->Tensor(3655, "model.layers.2.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.2.layer_scalar", 2));
  g->Tensor(3656, "model.layers.2.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.2.mlp.down_proj.weight", 4718592));
  g->Tensor(3657, "model.layers.2.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.2.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3658, "model.layers.2.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.2.mlp.gate_proj.weight", 4718592));
  g->Tensor(3659, "model.layers.2.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.2.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3660, "model.layers.2.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.2.mlp.up_proj.weight", 4718592));
  g->Tensor(3661, "model.layers.2.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.2.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3662, "model.layers.2.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.2.per_layer_input_gate.weight", 393216));
  g->Tensor(3663, "model.layers.2.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.2.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3664, "model.layers.2.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.2.per_layer_projection.weight", 393216));
  g->Tensor(3665, "model.layers.2.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.2.per_layer_projection.weight_scale", 6144));
  g->Tensor(3666, "model.layers.2.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.2.post_attention_layernorm.weight", 3072));
  g->Tensor(3667, "model.layers.2.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.2.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3668, "model.layers.2.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.2.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3669, "model.layers.2.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.2.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3670, "model.layers.2.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.2.self_attn.k_norm.weight", 512));
  g->Tensor(3671, "model.layers.2.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.2.self_attn.k_proj.weight", 196608));
  g->Tensor(3672, "model.layers.2.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.2.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3673, "model.layers.2.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.2.self_attn.o_proj.weight", 1572864));
  g->Tensor(3674, "model.layers.2.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.2.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3675, "model.layers.2.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.2.self_attn.q_norm.weight", 512));
  g->Tensor(3676, "model.layers.2.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.2.self_attn.q_proj.weight", 1572864));
  g->Tensor(3677, "model.layers.2.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.2.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3678, "model.layers.2.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.2.self_attn.v_proj.weight", 196608));
  g->Tensor(3679, "model.layers.2.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.2.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3680, "model.layers.3.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.3.input_layernorm.weight", 3072));
  g->Tensor(3681, "model.layers.3.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.3.layer_scalar", 2));
  g->Tensor(3682, "model.layers.3.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.3.mlp.down_proj.weight", 4718592));
  g->Tensor(3683, "model.layers.3.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.3.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3684, "model.layers.3.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.3.mlp.gate_proj.weight", 4718592));
  g->Tensor(3685, "model.layers.3.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.3.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3686, "model.layers.3.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.3.mlp.up_proj.weight", 4718592));
  g->Tensor(3687, "model.layers.3.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.3.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3688, "model.layers.3.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.3.per_layer_input_gate.weight", 393216));
  g->Tensor(3689, "model.layers.3.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.3.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3690, "model.layers.3.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.3.per_layer_projection.weight", 393216));
  g->Tensor(3691, "model.layers.3.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.3.per_layer_projection.weight_scale", 6144));
  g->Tensor(3692, "model.layers.3.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.3.post_attention_layernorm.weight", 3072));
  g->Tensor(3693, "model.layers.3.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.3.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3694, "model.layers.3.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.3.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3695, "model.layers.3.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.3.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3696, "model.layers.3.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.3.self_attn.k_norm.weight", 512));
  g->Tensor(3697, "model.layers.3.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.3.self_attn.k_proj.weight", 196608));
  g->Tensor(3698, "model.layers.3.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.3.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3699, "model.layers.3.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.3.self_attn.o_proj.weight", 1572864));
  g->Tensor(3700, "model.layers.3.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.3.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3701, "model.layers.3.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.3.self_attn.q_norm.weight", 512));
  g->Tensor(3702, "model.layers.3.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.3.self_attn.q_proj.weight", 1572864));
  g->Tensor(3703, "model.layers.3.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.3.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3704, "model.layers.3.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.3.self_attn.v_proj.weight", 196608));
  g->Tensor(3705, "model.layers.3.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.3.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3706, "model.layers.4.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.4.input_layernorm.weight", 3072));
  g->Tensor(3707, "model.layers.4.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.4.layer_scalar", 2));
  g->Tensor(3708, "model.layers.4.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.4.mlp.down_proj.weight", 4718592));
  g->Tensor(3709, "model.layers.4.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.4.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3710, "model.layers.4.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.4.mlp.gate_proj.weight", 4718592));
  g->Tensor(3711, "model.layers.4.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.4.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3712, "model.layers.4.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.4.mlp.up_proj.weight", 4718592));
  g->Tensor(3713, "model.layers.4.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.4.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3714, "model.layers.4.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.4.per_layer_input_gate.weight", 393216));
  g->Tensor(3715, "model.layers.4.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.4.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3716, "model.layers.4.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.4.per_layer_projection.weight", 393216));
  g->Tensor(3717, "model.layers.4.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.4.per_layer_projection.weight_scale", 6144));
  g->Tensor(3718, "model.layers.4.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.4.post_attention_layernorm.weight", 3072));
  g->Tensor(3719, "model.layers.4.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.4.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3720, "model.layers.4.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.4.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3721, "model.layers.4.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.4.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3722, "model.layers.4.self_attn.k_norm.weight", ynn_type_bf16, {512}, 0, weights("@hf/model.layers.4.self_attn.k_norm.weight", 1024));
  g->Tensor(3723, "model.layers.4.self_attn.k_proj.weight", ynn_type_int4, {512,1536}, 0, weights("@hf/model.layers.4.self_attn.k_proj.weight", 393216));
  g->Tensor(3724, "model.layers.4.self_attn.k_proj.weight_scale", ynn_type_fp32, {512,1}, 0, weights("@hf/model.layers.4.self_attn.k_proj.weight_scale", 2048));
  g->Tensor(3725, "model.layers.4.self_attn.o_proj.weight", ynn_type_int4, {1536,4096}, 0, weights("@hf/model.layers.4.self_attn.o_proj.weight", 3145728));
  g->Tensor(3726, "model.layers.4.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.4.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3727, "model.layers.4.self_attn.q_norm.weight", ynn_type_bf16, {512}, 0, weights("@hf/model.layers.4.self_attn.q_norm.weight", 1024));
  g->Tensor(3728, "model.layers.4.self_attn.q_proj.weight", ynn_type_int4, {4096,1536}, 0, weights("@hf/model.layers.4.self_attn.q_proj.weight", 3145728));
  g->Tensor(3729, "model.layers.4.self_attn.q_proj.weight_scale", ynn_type_fp32, {4096,1}, 0, weights("@hf/model.layers.4.self_attn.q_proj.weight_scale", 16384));
  g->Tensor(3730, "model.layers.4.self_attn.v_proj.weight", ynn_type_int4, {512,1536}, 0, weights("@hf/model.layers.4.self_attn.v_proj.weight", 393216));
  g->Tensor(3731, "model.layers.4.self_attn.v_proj.weight_scale", ynn_type_fp32, {512,1}, 0, weights("@hf/model.layers.4.self_attn.v_proj.weight_scale", 2048));
  g->Tensor(3732, "model.layers.5.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.5.input_layernorm.weight", 3072));
  g->Tensor(3733, "model.layers.5.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.5.layer_scalar", 2));
  g->Tensor(3734, "model.layers.5.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.5.mlp.down_proj.weight", 4718592));
  g->Tensor(3735, "model.layers.5.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.5.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3736, "model.layers.5.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.5.mlp.gate_proj.weight", 4718592));
  g->Tensor(3737, "model.layers.5.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.5.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3738, "model.layers.5.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.5.mlp.up_proj.weight", 4718592));
  g->Tensor(3739, "model.layers.5.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.5.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3740, "model.layers.5.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.5.per_layer_input_gate.weight", 393216));
  g->Tensor(3741, "model.layers.5.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.5.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3742, "model.layers.5.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.5.per_layer_projection.weight", 393216));
  g->Tensor(3743, "model.layers.5.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.5.per_layer_projection.weight_scale", 6144));
  g->Tensor(3744, "model.layers.5.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.5.post_attention_layernorm.weight", 3072));
  g->Tensor(3745, "model.layers.5.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.5.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3746, "model.layers.5.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.5.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3747, "model.layers.5.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.5.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3748, "model.layers.5.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.5.self_attn.k_norm.weight", 512));
  g->Tensor(3749, "model.layers.5.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.5.self_attn.k_proj.weight", 196608));
  g->Tensor(3750, "model.layers.5.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.5.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3751, "model.layers.5.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.5.self_attn.o_proj.weight", 1572864));
  g->Tensor(3752, "model.layers.5.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.5.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3753, "model.layers.5.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.5.self_attn.q_norm.weight", 512));
  g->Tensor(3754, "model.layers.5.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.5.self_attn.q_proj.weight", 1572864));
  g->Tensor(3755, "model.layers.5.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.5.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3756, "model.layers.5.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.5.self_attn.v_proj.weight", 196608));
  g->Tensor(3757, "model.layers.5.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.5.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3758, "model.layers.6.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.6.input_layernorm.weight", 3072));
  g->Tensor(3759, "model.layers.6.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.6.layer_scalar", 2));
  g->Tensor(3760, "model.layers.6.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.6.mlp.down_proj.weight", 4718592));
  g->Tensor(3761, "model.layers.6.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.6.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3762, "model.layers.6.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.6.mlp.gate_proj.weight", 4718592));
  g->Tensor(3763, "model.layers.6.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.6.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3764, "model.layers.6.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.6.mlp.up_proj.weight", 4718592));
  g->Tensor(3765, "model.layers.6.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.6.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3766, "model.layers.6.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.6.per_layer_input_gate.weight", 393216));
  g->Tensor(3767, "model.layers.6.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.6.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3768, "model.layers.6.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.6.per_layer_projection.weight", 393216));
  g->Tensor(3769, "model.layers.6.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.6.per_layer_projection.weight_scale", 6144));
  g->Tensor(3770, "model.layers.6.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.6.post_attention_layernorm.weight", 3072));
  g->Tensor(3771, "model.layers.6.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.6.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3772, "model.layers.6.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.6.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3773, "model.layers.6.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.6.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3774, "model.layers.6.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.6.self_attn.k_norm.weight", 512));
  g->Tensor(3775, "model.layers.6.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.6.self_attn.k_proj.weight", 196608));
  g->Tensor(3776, "model.layers.6.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.6.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3777, "model.layers.6.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.6.self_attn.o_proj.weight", 1572864));
  g->Tensor(3778, "model.layers.6.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.6.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3779, "model.layers.6.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.6.self_attn.q_norm.weight", 512));
  g->Tensor(3780, "model.layers.6.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.6.self_attn.q_proj.weight", 1572864));
  g->Tensor(3781, "model.layers.6.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.6.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3782, "model.layers.6.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.6.self_attn.v_proj.weight", 196608));
  g->Tensor(3783, "model.layers.6.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.6.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3784, "model.layers.7.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.7.input_layernorm.weight", 3072));
  g->Tensor(3785, "model.layers.7.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.7.layer_scalar", 2));
  g->Tensor(3786, "model.layers.7.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.7.mlp.down_proj.weight", 4718592));
  g->Tensor(3787, "model.layers.7.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.7.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3788, "model.layers.7.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.7.mlp.gate_proj.weight", 4718592));
  g->Tensor(3789, "model.layers.7.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.7.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3790, "model.layers.7.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.7.mlp.up_proj.weight", 4718592));
  g->Tensor(3791, "model.layers.7.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.7.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3792, "model.layers.7.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.7.per_layer_input_gate.weight", 393216));
  g->Tensor(3793, "model.layers.7.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.7.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3794, "model.layers.7.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.7.per_layer_projection.weight", 393216));
  g->Tensor(3795, "model.layers.7.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.7.per_layer_projection.weight_scale", 6144));
  g->Tensor(3796, "model.layers.7.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.7.post_attention_layernorm.weight", 3072));
  g->Tensor(3797, "model.layers.7.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.7.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3798, "model.layers.7.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.7.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3799, "model.layers.7.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.7.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3800, "model.layers.7.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.7.self_attn.k_norm.weight", 512));
  g->Tensor(3801, "model.layers.7.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.7.self_attn.k_proj.weight", 196608));
  g->Tensor(3802, "model.layers.7.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.7.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3803, "model.layers.7.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.7.self_attn.o_proj.weight", 1572864));
  g->Tensor(3804, "model.layers.7.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.7.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3805, "model.layers.7.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.7.self_attn.q_norm.weight", 512));
  g->Tensor(3806, "model.layers.7.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.7.self_attn.q_proj.weight", 1572864));
  g->Tensor(3807, "model.layers.7.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.7.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3808, "model.layers.7.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.7.self_attn.v_proj.weight", 196608));
  g->Tensor(3809, "model.layers.7.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.7.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3810, "model.layers.8.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.8.input_layernorm.weight", 3072));
  g->Tensor(3811, "model.layers.8.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.8.layer_scalar", 2));
  g->Tensor(3812, "model.layers.8.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.8.mlp.down_proj.weight", 4718592));
  g->Tensor(3813, "model.layers.8.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.8.mlp.down_proj.weight_scale", 6144));
  g->Tensor(3814, "model.layers.8.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.8.mlp.gate_proj.weight", 4718592));
  g->Tensor(3815, "model.layers.8.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.8.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3816, "model.layers.8.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.8.mlp.up_proj.weight", 4718592));
  g->Tensor(3817, "model.layers.8.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.8.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3818, "model.layers.8.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.8.per_layer_input_gate.weight", 393216));
  g->Tensor(3819, "model.layers.8.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.8.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3820, "model.layers.8.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.8.per_layer_projection.weight", 393216));
  g->Tensor(3821, "model.layers.8.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.8.per_layer_projection.weight_scale", 6144));
  g->Tensor(3822, "model.layers.8.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.8.post_attention_layernorm.weight", 3072));
  g->Tensor(3823, "model.layers.8.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.8.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3824, "model.layers.8.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.8.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3825, "model.layers.8.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.8.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3826, "model.layers.8.self_attn.k_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.8.self_attn.k_norm.weight", 512));
  g->Tensor(3827, "model.layers.8.self_attn.k_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.8.self_attn.k_proj.weight", 196608));
  g->Tensor(3828, "model.layers.8.self_attn.k_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.8.self_attn.k_proj.weight_scale", 1024));
  g->Tensor(3829, "model.layers.8.self_attn.o_proj.weight", ynn_type_int4, {1536,2048}, 0, weights("@hf/model.layers.8.self_attn.o_proj.weight", 1572864));
  g->Tensor(3830, "model.layers.8.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.8.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3831, "model.layers.8.self_attn.q_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.layers.8.self_attn.q_norm.weight", 512));
  g->Tensor(3832, "model.layers.8.self_attn.q_proj.weight", ynn_type_int4, {2048,1536}, 0, weights("@hf/model.layers.8.self_attn.q_proj.weight", 1572864));
  g->Tensor(3833, "model.layers.8.self_attn.q_proj.weight_scale", ynn_type_fp32, {2048,1}, 0, weights("@hf/model.layers.8.self_attn.q_proj.weight_scale", 8192));
  g->Tensor(3834, "model.layers.8.self_attn.v_proj.weight", ynn_type_int4, {256,1536}, 0, weights("@hf/model.layers.8.self_attn.v_proj.weight", 196608));
  g->Tensor(3835, "model.layers.8.self_attn.v_proj.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.8.self_attn.v_proj.weight_scale", 1024));
  g->Tensor(3836, "model.layers.9.input_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.9.input_layernorm.weight", 3072));
  g->Tensor(3837, "model.layers.9.layer_scalar", ynn_type_bf16, {1}, 0, weights("@hf/model.layers.9.layer_scalar", 2));
  g->Tensor(3838, "model.layers.9.mlp.down_proj.weight", ynn_type_int4, {1536,6144}, 0, weights("@hf/model.layers.9.mlp.down_proj.weight", 4718592));
  g->Tensor(3839, "model.layers.9.mlp.down_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.9.mlp.down_proj.weight_scale", 6144));
}

// Scope: "DefineValues"
LAB_YNN_BUILDER_NOINLINE void BuildDefineValuesPart15(Context& ctx) {
  auto* g = ctx.g;
  const auto& weights = ctx.weights;
  g->Tensor(3840, "model.layers.9.mlp.gate_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.9.mlp.gate_proj.weight", 4718592));
  g->Tensor(3841, "model.layers.9.mlp.gate_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.9.mlp.gate_proj.weight_scale", 24576));
  g->Tensor(3842, "model.layers.9.mlp.up_proj.weight", ynn_type_int4, {6144,1536}, 0, weights("@hf/model.layers.9.mlp.up_proj.weight", 4718592));
  g->Tensor(3843, "model.layers.9.mlp.up_proj.weight_scale", ynn_type_fp32, {6144,1}, 0, weights("@hf/model.layers.9.mlp.up_proj.weight_scale", 24576));
  g->Tensor(3844, "model.layers.9.per_layer_input_gate.weight", ynn_type_int8, {256,1536}, 0, weights("@hf/model.layers.9.per_layer_input_gate.weight", 393216));
  g->Tensor(3845, "model.layers.9.per_layer_input_gate.weight_scale", ynn_type_fp32, {256,1}, 0, weights("@hf/model.layers.9.per_layer_input_gate.weight_scale", 1024));
  g->Tensor(3846, "model.layers.9.per_layer_projection.weight", ynn_type_int8, {1536,256}, 0, weights("@hf/model.layers.9.per_layer_projection.weight", 393216));
  g->Tensor(3847, "model.layers.9.per_layer_projection.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.9.per_layer_projection.weight_scale", 6144));
  g->Tensor(3848, "model.layers.9.post_attention_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.9.post_attention_layernorm.weight", 3072));
  g->Tensor(3849, "model.layers.9.post_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.9.post_feedforward_layernorm.weight", 3072));
  g->Tensor(3850, "model.layers.9.post_per_layer_input_norm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.9.post_per_layer_input_norm.weight", 3072));
  g->Tensor(3851, "model.layers.9.pre_feedforward_layernorm.weight", ynn_type_bf16, {1536}, 0, weights("@hf/model.layers.9.pre_feedforward_layernorm.weight", 3072));
  g->Tensor(3852, "model.layers.9.self_attn.k_norm.weight", ynn_type_bf16, {512}, 0, weights("@hf/model.layers.9.self_attn.k_norm.weight", 1024));
  g->Tensor(3853, "model.layers.9.self_attn.k_proj.weight", ynn_type_int4, {512,1536}, 0, weights("@hf/model.layers.9.self_attn.k_proj.weight", 393216));
  g->Tensor(3854, "model.layers.9.self_attn.k_proj.weight_scale", ynn_type_fp32, {512,1}, 0, weights("@hf/model.layers.9.self_attn.k_proj.weight_scale", 2048));
  g->Tensor(3855, "model.layers.9.self_attn.o_proj.weight", ynn_type_int4, {1536,4096}, 0, weights("@hf/model.layers.9.self_attn.o_proj.weight", 3145728));
  g->Tensor(3856, "model.layers.9.self_attn.o_proj.weight_scale", ynn_type_fp32, {1536,1}, 0, weights("@hf/model.layers.9.self_attn.o_proj.weight_scale", 6144));
  g->Tensor(3857, "model.layers.9.self_attn.q_norm.weight", ynn_type_bf16, {512}, 0, weights("@hf/model.layers.9.self_attn.q_norm.weight", 1024));
  g->Tensor(3858, "model.layers.9.self_attn.q_proj.weight", ynn_type_int4, {4096,1536}, 0, weights("@hf/model.layers.9.self_attn.q_proj.weight", 3145728));
  g->Tensor(3859, "model.layers.9.self_attn.q_proj.weight_scale", ynn_type_fp32, {4096,1}, 0, weights("@hf/model.layers.9.self_attn.q_proj.weight_scale", 16384));
  g->Tensor(3860, "model.layers.9.self_attn.v_proj.weight", ynn_type_int4, {512,1536}, 0, weights("@hf/model.layers.9.self_attn.v_proj.weight", 393216));
  g->Tensor(3861, "model.layers.9.self_attn.v_proj.weight_scale", ynn_type_fp32, {512,1}, 0, weights("@hf/model.layers.9.self_attn.v_proj.weight_scale", 2048));
  g->Tensor(3862, "model.per_layer_model_projection.weight", ynn_type_bf16, {8960,1536}, 0, weights("@hf/model.per_layer_model_projection.weight", 27525120));
  g->Tensor(3863, "model.per_layer_projection_norm.weight", ynn_type_bf16, {256}, 0, weights("@hf/model.per_layer_projection_norm.weight", 512));
  g->Tensor(3864, "per_layer_token_embedding_0", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3865, "per_layer_token_embedding_1", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3866, "per_layer_token_embedding_10", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3867, "per_layer_token_embedding_11", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3868, "per_layer_token_embedding_12", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3869, "per_layer_token_embedding_13", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3870, "per_layer_token_embedding_2", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3871, "per_layer_token_embedding_3", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3872, "per_layer_token_embedding_4", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3873, "per_layer_token_embedding_5", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3874, "per_layer_token_embedding_6", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3875, "per_layer_token_embedding_7", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3876, "per_layer_token_embedding_8", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3877, "per_layer_token_embedding_9", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(3878, "positions", ynn_type_fp32, {1,1,0,1}, 1, nullptr);
  g->Tensor(3879, "updated_key_0", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3880, "updated_key_1", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3881, "updated_key_10", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3882, "updated_key_11", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3883, "updated_key_12", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3884, "updated_key_13", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3885, "updated_key_14", ynn_type_int8, {1,1,0,512}, 2, nullptr);
  g->Tensor(3886, "updated_key_2", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3887, "updated_key_3", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3888, "updated_key_4", ynn_type_int8, {1,1,0,512}, 2, nullptr);
  g->Tensor(3889, "updated_key_5", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3890, "updated_key_6", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3891, "updated_key_7", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3892, "updated_key_8", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3893, "updated_key_9", ynn_type_int8, {1,1,0,512}, 2, nullptr);
  g->Tensor(3894, "updated_value_0", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3895, "updated_value_1", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3896, "updated_value_10", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3897, "updated_value_11", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3898, "updated_value_12", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3899, "updated_value_13", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3900, "updated_value_14", ynn_type_int8, {1,1,0,512}, 2, nullptr);
  g->Tensor(3901, "updated_value_2", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3902, "updated_value_3", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3903, "updated_value_4", ynn_type_int8, {1,1,0,512}, 2, nullptr);
  g->Tensor(3904, "updated_value_5", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3905, "updated_value_6", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3906, "updated_value_7", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3907, "updated_value_8", ynn_type_int8, {1,1,0,256}, 2, nullptr);
  g->Tensor(3908, "updated_value_9", ynn_type_int8, {1,1,0,512}, 2, nullptr);
  g->Tensor(3909, "view_key_0", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3910, "view_key_1", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3911, "view_key_10", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3912, "view_key_11", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3913, "view_key_12", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3914, "view_key_13", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3915, "view_key_2", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3916, "view_key_3", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3917, "view_key_4", ynn_type_int8, {1,1,0,512}, 0, nullptr);
  g->Tensor(3918, "view_key_5", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3919, "view_key_6", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3920, "view_key_7", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3921, "view_key_8", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3922, "view_key_9", ynn_type_int8, {1,1,0,512}, 0, nullptr);
  g->Tensor(3923, "view_value_0", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3924, "view_value_1", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3925, "view_value_10", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3926, "view_value_11", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3927, "view_value_12", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3928, "view_value_13", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3929, "view_value_2", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3930, "view_value_3", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3931, "view_value_4", ynn_type_int8, {1,1,0,512}, 0, nullptr);
  g->Tensor(3932, "view_value_5", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3933, "view_value_6", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3934, "view_value_7", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3935, "view_value_8", ynn_type_int8, {1,1,0,256}, 0, nullptr);
  g->Tensor(3936, "view_value_9", ynn_type_int8, {1,1,0,512}, 0, nullptr);
}

// Scope: "DefineValues"
LAB_YNN_BUILDER_NOINLINE void BuildDefineValues(Context& ctx) {
  BuildDefineValuesPart0(ctx);
  BuildDefineValuesPart1(ctx);
  BuildDefineValuesPart2(ctx);
  BuildDefineValuesPart3(ctx);
  BuildDefineValuesPart4(ctx);
  BuildDefineValuesPart5(ctx);
  BuildDefineValuesPart6(ctx);
  BuildDefineValuesPart7(ctx);
  BuildDefineValuesPart8(ctx);
  BuildDefineValuesPart9(ctx);
  BuildDefineValuesPart10(ctx);
  BuildDefineValuesPart11(ctx);
  BuildDefineValuesPart12(ctx);
  BuildDefineValuesPart13(ctx);
  BuildDefineValuesPart14(ctx);
  BuildDefineValuesPart15(ctx);
}

// Scope: "BindInvocation"
LAB_YNN_BUILDER_NOINLINE void BuildBindInvocation(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s3 = ctx.s3;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->InputShape(3292, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{1536})});
  g->InputShape(3878, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{1})});
  g->InputShape(3262, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3277, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3864, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3263, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3278, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3865, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3269, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3284, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3870, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3270, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3285, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3871, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3271, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{512})});
  g->InputShape(3286, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{512})});
  g->InputShape(3872, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3272, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3287, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3873, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3273, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3288, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3874, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3274, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3289, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3875, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3275, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3290, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3876, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3276, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{512})});
  g->InputShape(3291, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{512})});
  g->InputShape(3877, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3264, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3279, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3866, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3265, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3280, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3867, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3266, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3281, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3868, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3267, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3282, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{256})});
  g->InputShape(3869, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(3268, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{512})});
  g->InputShape(3283, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s3,slinky::expr(int64_t{512})});
  static_assert(lab_ynn::kResourceStateContract == 1, "incompatible resource-state adapter");
  g->Resource(3262, "cache_key_0", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005997600965201855],\"zero_point\":[0]}");
  g->Resource(3263, "cache_key_1", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005761673673987389],\"zero_point\":[0]}");
  g->Resource(3264, "cache_key_10", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005712664220482111],\"zero_point\":[0]}");
  g->Resource(3265, "cache_key_11", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005907459184527397],\"zero_point\":[0]}");
  g->Resource(3266, "cache_key_12", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005788442213088274],\"zero_point\":[0]}");
  g->Resource(3267, "cache_key_13", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0059552486054599285],\"zero_point\":[0]}");
  g->Resource(3268, "cache_key_14", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.001091228099539876],\"zero_point\":[0]}");
  g->Resource(3269, "cache_key_2", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005684707313776016],\"zero_point\":[0]}");
  g->Resource(3270, "cache_key_3", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.00573749840259552],\"zero_point\":[0]}");
  g->Resource(3271, "cache_key_4", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0011563472216948867],\"zero_point\":[0]}");
  g->Resource(3272, "cache_key_5", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.006011798977851868],\"zero_point\":[0]}");
  g->Resource(3273, "cache_key_6", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0057707298547029495],\"zero_point\":[0]}");
  g->Resource(3274, "cache_key_7", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005869260523468256],\"zero_point\":[0]}");
  g->Resource(3275, "cache_key_8", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.006215503439307213],\"zero_point\":[0]}");
  g->Resource(3276, "cache_key_9", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0010733711533248425],\"zero_point\":[0]}");
  g->Resource(3277, "cache_value_0", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3278, "cache_value_1", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3279, "cache_value_10", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3280, "cache_value_11", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3281, "cache_value_12", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3282, "cache_value_13", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3283, "cache_value_14", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->Resource(3284, "cache_value_2", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3285, "cache_value_3", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3286, "cache_value_4", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->Resource(3287, "cache_value_5", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3288, "cache_value_6", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3289, "cache_value_7", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3290, "cache_value_8", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(3291, "cache_value_9", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->RequireBounds(slinky::expr(int64_t{1}) <= s3, "symbol 3 lower bound");
  g->RequireBounds(s3 <= slinky::expr(int64_t{32768}), "symbol 3 upper bound");
  g->RequireBounds(slinky::expr(int64_t{1}) <= s1, "symbol 1 lower bound");
  g->RequireBounds(s1 <= slinky::expr(int64_t{128}), "symbol 1 upper bound");
  g->RequireBounds(slinky::expr(int64_t{0}) <= s2, "symbol 2 lower bound");
  g->RequireBounds(s2 <= slinky::expr(int64_t{32768}), "symbol 2 upper bound");
  g->Require((slinky::expr(int64_t{256}) * slinky::max(slinky::expr(int64_t{1}), s3)) <= (slinky::expr(int64_t{256}) * slinky::max(slinky::expr(int64_t{1}), s3)), "overlapping resource strides");
  g->Require(s2 <= s3, "resource logical extent exceeds capacity");
  g->Require((slinky::expr(int64_t{512}) * slinky::max(slinky::expr(int64_t{1}), s3)) <= (slinky::expr(int64_t{512}) * slinky::max(slinky::expr(int64_t{1}), s3)), "overlapping resource strides");
  g->Require(s1 <= s1, "slice bounds");
  g->Require((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) <= s3, "append capacity");
  g->Require(slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))) <= (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)), "view interval");
  g->Require((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) <= (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)), "view reads uninitialized history");
  g->Require(((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) + (slinky::expr(int64_t{-1}) * slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2)))) + slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2)))) <= (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)), "consumer reads uninitialized resource capacity");
}

// Scope: "RopeTables"
LAB_YNN_BUILDER_NOINLINE void BuildRopeTables(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_multiply, 3878, 3428, 0);
  g->Unary(ynn_unary_cos, 0, 1);
  g->Unary(ynn_unary_sin, 0, 1021);
  g->Concat({1,1}, 2025, 3);
  g->Concat({1021,1021}, 2249, 3);
  g->Binary(ynn_binary_multiply, 3878, 3427, 2355);
  g->Unary(ynn_unary_cos, 2355, 2450);
  g->Unary(ynn_unary_sin, 2355, 2557);
  g->Concat({2450,2450}, 2651, 3);
  g->Concat({2557,2557}, 2750, 3);
}

// Scope: "InputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildInputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3862, 2);
  g->Matmul(3292, 2, 108, false, true);
  g->Binary(ynn_binary_multiply, 108, 3403, 204);
  g->SplitDim(204, 309, 2, {35,256});
  g->Unary(ynn_unary_square, 309, 406);
  g->Reduce(ynn_reduce_sum, 406, 2928, {3}, true);
  g->ShapeProduct(406, 2927, {3});
  g->Binary(ynn_binary_divide, 2928, 2927, 511);
  g->Binary(ynn_binary_add, 511, 3400, 617);
  g->Binary(ynn_binary_pow, 617, 3424, 708);
  g->Binary(ynn_binary_multiply, 309, 708, 819);
  g->Convert(3863, 915);
  g->Binary(ynn_binary_multiply, 819, 915, 1022);
}

// Scope: "Layer0 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 1730, 3461, 1825);
  g->Unary(ynn_unary_round, 1825, 1931);
  g->Binary(ynn_binary_max, 1931, 3328, 2026);
  g->Binary(ynn_binary_min, 2026, 3384, 2130);
  g->Binary(ynn_binary_multiply, 2130, 3461, 2167);
  g->Convert(3509, 2178);
  g->Binary(ynn_binary_multiply, 2178, 3510, 2188);
  g->Matmul(2167, 2188, 2199, false, true);
  g->Binary(ynn_binary_divide, 2199, 3404, 2210);
  g->Unary(ynn_unary_round, 2210, 2221);
  g->Binary(ynn_binary_max, 2221, 3328, 2231);
  g->Binary(ynn_binary_min, 2231, 3384, 2238);
  g->Binary(ynn_binary_multiply, 2238, 3404, 2250);
  g->Reshape(2250, 2261, {1,0,1,256});
  g->Transpose(2261, 2272, {0,2,1,3});
  g->Unary(ynn_unary_square, 2272, 2283);
  g->Reduce(ynn_reduce_sum, 2283, 3186, {3}, true);
  g->ShapeProduct(2283, 3185, {3});
  g->Binary(ynn_binary_divide, 3186, 3185, 2294);
  g->Binary(ynn_binary_add, 2294, 3400, 2305);
  g->Binary(ynn_binary_pow, 2305, 3424, 2316);
  g->Binary(ynn_binary_multiply, 2272, 2316, 2327);
  g->Convert(3508, 2338);
  g->Binary(ynn_binary_multiply, 2327, 2338, 2349);
  g->Slice(2349, 2356, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2349, 2367, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2367, 2374);
  g->Concat({2374,2356}, 2380, 3);
  g->Binary(ynn_binary_multiply, 2349, 2025, 2391);
  g->Binary(ynn_binary_multiply, 2380, 2249, 2402);
  g->Binary(ynn_binary_add, 2391, 2402, 2412);
  g->Convert(3516, 2469);
  g->Binary(ynn_binary_multiply, 2469, 3517, 2480);
  g->Matmul(2167, 2480, 2491, false, true);
  g->Binary(ynn_binary_divide, 2491, 3404, 2502);
  g->Unary(ynn_unary_round, 2502, 2513);
  g->Binary(ynn_binary_max, 2513, 3328, 2524);
  g->Binary(ynn_binary_min, 2524, 3384, 2535);
  g->Binary(ynn_binary_multiply, 2535, 3404, 2546);
  g->Reshape(2546, 2558, {1,0,1,256});
  g->Transpose(2558, 2569, {0,2,1,3});
  g->Unary(ynn_unary_square, 2569, 2575);
  g->Reduce(ynn_reduce_sum, 2575, 3225, {3}, true);
  g->ShapeProduct(2575, 3224, {3});
  g->Binary(ynn_binary_divide, 3225, 3224, 2586);
  g->Binary(ynn_binary_add, 2586, 3400, 2592);
  g->Binary(ynn_binary_pow, 2592, 3424, 2599);
  g->Binary(ynn_binary_multiply, 2569, 2599, 2610);
}

// Scope: "Layer0 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2412, 2620, 0.005997600965201855, 0);
  g->Append(3262, 2620, 3879, 2, s2, s1);
  g->View(3879, 3909, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3909, 2652, 0.005997600965201855, 0);
  g->Quantize(2610, 2663, 0.047244105488061905, 0);
  g->Append(3277, 2663, 3894, 2, s2, s1);
  g->View(3894, 3923, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3923, 2689, 0.047244105488061905, 0);
}

// Scope: "Layer0 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3514, 2751);
  g->Binary(ynn_binary_multiply, 2751, 3515, 2762);
  g->Matmul(2167, 2762, 2773, false, true);
  g->Binary(ynn_binary_divide, 2773, 3463, 2783);
  g->Unary(ynn_unary_round, 2783, 2790);
  g->Binary(ynn_binary_max, 2790, 3328, 2801);
  g->Binary(ynn_binary_min, 2801, 3384, 2805);
  g->Binary(ynn_binary_multiply, 2805, 3463, 2814);
  g->SplitDim(2814, 2825, 2, {8,256});
  g->Transpose(2825, 2835, {0,2,1,3});
  g->Unary(ynn_unary_square, 2835, 3);
  g->Reduce(ynn_reduce_sum, 3, 2849, {3}, true);
  g->ShapeProduct(3, 2848, {3});
  g->Binary(ynn_binary_divide, 2849, 2848, 14);
  g->Binary(ynn_binary_add, 14, 3400, 25);
  g->Binary(ynn_binary_pow, 25, 3424, 36);
  g->Binary(ynn_binary_multiply, 2835, 36, 42);
  g->Convert(3513, 53);
  g->Binary(ynn_binary_multiply, 42, 53, 64);
  g->Slice(64, 75, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(64, 86, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 86, 97);
  g->Concat({97,75}, 109, 3);
  g->Binary(ynn_binary_multiply, 64, 2025, 120);
  g->Binary(ynn_binary_multiply, 109, 2249, 131);
  g->Binary(ynn_binary_add, 120, 131, 142);
}

// Scope: "Layer0 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(142, 2652, 153, false, true);
  g->Mask(153, 3478, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3478, 2873, {-1}, true);
  g->Binary(ynn_binary_subtract, 3478, 2873, 2870);
  g->Unary(ynn_unary_exp, 2870, 2871);
  g->Reduce(ynn_reduce_sum, 2871, 2874, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 2874, 2872);
  g->Binary(ynn_binary_multiply, 2871, 2872, 169);
  g->Matmul(169, 2689, 178, false, false);
}

// Scope: "Layer0 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(178, 182, {0,2,1,3});
  g->FuseDims(182, 193, 2, 2);
  g->Binary(ynn_binary_divide, 193, 3436, 205);
  g->Unary(ynn_unary_round, 205, 215);
  g->Binary(ynn_binary_max, 215, 3328, 226);
  g->Binary(ynn_binary_min, 226, 3384, 237);
  g->Binary(ynn_binary_multiply, 237, 3436, 248);
  g->Convert(3511, 259);
  g->Binary(ynn_binary_multiply, 259, 3512, 265);
  g->Matmul(248, 265, 276, false, true);
  g->Binary(ynn_binary_divide, 276, 3370, 287);
  g->Unary(ynn_unary_round, 287, 298);
  g->Binary(ynn_binary_max, 298, 3328, 310);
  g->Binary(ynn_binary_min, 310, 3384, 321);
  g->Binary(ynn_binary_multiply, 321, 3370, 332);
}

// Scope: "Layer0 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3292, 1118);
  g->Reduce(ynn_reduce_sum, 1118, 3033, {2}, true);
  g->ShapeProduct(1118, 3032, {2});
  g->Binary(ynn_binary_divide, 3033, 3032, 1224);
  g->Binary(ynn_binary_add, 1224, 3400, 1320);
  g->Binary(ynn_binary_pow, 1320, 3424, 1426);
  g->Binary(ynn_binary_multiply, 3292, 1426, 1523);
  g->Convert(3492, 1628);
  g->Binary(ynn_binary_multiply, 1523, 1628, 1730);
  BuildLayer0AttentionKvProjection(ctx);
  BuildLayer0AttentionCacheUpdate(ctx);
  BuildLayer0AttentionQueryProjection(ctx);
  BuildLayer0AttentionSdpa(ctx);
  BuildLayer0AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 332, 343);
  g->Reduce(ynn_reduce_sum, 343, 2903, {2}, true);
  g->ShapeProduct(343, 2902, {2});
  g->Binary(ynn_binary_divide, 2903, 2902, 354);
  g->Binary(ynn_binary_add, 354, 3400, 365);
  g->Binary(ynn_binary_pow, 365, 3424, 376);
  g->Binary(ynn_binary_multiply, 332, 376, 382);
  g->Convert(3504, 393);
  g->Binary(ynn_binary_multiply, 382, 393, 402);
  g->Binary(ynn_binary_add, 3292, 402, 407);
}

// Scope: "Layer0 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 407, 418);
  g->Reduce(ynn_reduce_sum, 418, 2911, {2}, true);
  g->ShapeProduct(418, 2910, {2});
  g->Binary(ynn_binary_divide, 2911, 2910, 429);
  g->Binary(ynn_binary_add, 429, 3400, 439);
  g->Binary(ynn_binary_pow, 439, 3424, 450);
  g->Binary(ynn_binary_multiply, 407, 450, 461);
  g->Convert(3507, 472);
  g->Binary(ynn_binary_multiply, 461, 472, 482);
  g->Binary(ynn_binary_divide, 482, 3375, 489);
  g->Unary(ynn_unary_round, 489, 500);
  g->Binary(ynn_binary_max, 500, 3328, 512);
  g->Binary(ynn_binary_min, 512, 3384, 523);
  g->Binary(ynn_binary_multiply, 523, 3375, 534);
  g->Convert(3498, 545);
  g->Binary(ynn_binary_multiply, 545, 3499, 556);
  g->Matmul(534, 556, 567, false, true);
  g->Binary(ynn_binary_divide, 567, 3369, 578);
  g->Unary(ynn_unary_round, 578, 589);
  g->Binary(ynn_binary_max, 589, 3328, 600);
  g->Binary(ynn_binary_min, 600, 3384, 606);
  g->Binary(ynn_binary_multiply, 606, 3369, 618);
  g->Convert(3496, 669);
  g->Binary(ynn_binary_multiply, 669, 3497, 680);
  g->Matmul(534, 680, 691, false, true);
  g->Binary(ynn_binary_divide, 691, 3369, 699);
  g->Unary(ynn_unary_round, 699, 709);
  g->Binary(ynn_binary_max, 709, 3328, 720);
  g->Binary(ynn_binary_min, 720, 3384, 731);
  g->Binary(ynn_binary_multiply, 731, 3369, 742);
  g->Polynomial(742, 2960, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2960, 2961);
  g->Binary(ynn_binary_add, 2961, 2855, 2958);
  g->Binary(ynn_binary_multiply, 742, 2853, 2959);
  g->Binary(ynn_binary_multiply, 2959, 2958, 753);
  g->Binary(ynn_binary_multiply, 618, 753, 764);
  g->Binary(ynn_binary_divide, 764, 3421, 775);
  g->Unary(ynn_unary_round, 775, 786);
  g->Binary(ynn_binary_max, 786, 3328, 797);
  g->Binary(ynn_binary_min, 797, 3384, 808);
  g->Binary(ynn_binary_multiply, 808, 3421, 820);
  g->Convert(3494, 826);
  g->Binary(ynn_binary_multiply, 826, 3495, 837);
  g->Matmul(820, 837, 843, false, true);
  g->Binary(ynn_binary_divide, 843, 3364, 850);
  g->Unary(ynn_unary_round, 850, 861);
  g->Binary(ynn_binary_max, 861, 3328, 871);
  g->Binary(ynn_binary_min, 871, 3384, 882);
  g->Binary(ynn_binary_multiply, 882, 3364, 893);
  g->Unary(ynn_unary_square, 893, 904);
  g->Reduce(ynn_reduce_sum, 904, 2986, {2}, true);
  g->ShapeProduct(904, 2985, {2});
  g->Binary(ynn_binary_divide, 2986, 2985, 916);
  g->Binary(ynn_binary_add, 916, 3400, 922);
  g->Binary(ynn_binary_pow, 922, 3424, 933);
  g->Binary(ynn_binary_multiply, 893, 933, 944);
  g->Convert(3505, 955);
  g->Binary(ynn_binary_multiply, 944, 955, 966);
  g->Binary(ynn_binary_add, 407, 966, 977);
}

// Scope: "Layer0 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 988, {0,0,0,0}, {-1,-1,1,-1});
  g->Reshape(988, 999, {1,0,256});
  g->Binary(ynn_binary_add, 999, 3864, 1010);
  g->Binary(ynn_binary_multiply, 1010, 3296, 1023);
  g->Binary(ynn_binary_divide, 977, 3350, 1034);
  g->Unary(ynn_unary_round, 1034, 1044);
  g->Binary(ynn_binary_max, 1044, 3328, 1051);
  g->Binary(ynn_binary_min, 1051, 3384, 1062);
  g->Binary(ynn_binary_multiply, 1062, 3350, 1066);
  g->Convert(3500, 1075);
  g->Binary(ynn_binary_multiply, 1075, 3501, 1086);
  g->Matmul(1066, 1086, 1096, false, true);
  g->Binary(ynn_binary_divide, 1096, 3433, 1107);
  g->Unary(ynn_unary_round, 1107, 1119);
  g->Binary(ynn_binary_max, 1119, 3328, 1130);
  g->Binary(ynn_binary_min, 1130, 3384, 1141);
  g->Binary(ynn_binary_multiply, 1141, 3433, 1147);
  g->Polynomial(1147, 3022, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3022, 3023);
  g->Binary(ynn_binary_add, 3023, 2855, 3020);
  g->Binary(ynn_binary_multiply, 1147, 2853, 3021);
  g->Binary(ynn_binary_multiply, 3021, 3020, 1158);
  g->Binary(ynn_binary_multiply, 1158, 1023, 1169);
  g->Binary(ynn_binary_divide, 1169, 3373, 1180);
  g->Unary(ynn_unary_round, 1180, 1191);
  g->Binary(ynn_binary_max, 1191, 3328, 1202);
  g->Binary(ynn_binary_min, 1202, 3384, 1213);
  g->Binary(ynn_binary_multiply, 1213, 3373, 1225);
  g->Convert(3502, 1236);
  g->Binary(ynn_binary_multiply, 1236, 3503, 1247);
  g->Matmul(1225, 1247, 1258, false, true);
  g->Binary(ynn_binary_divide, 1258, 3299, 1266);
  g->Unary(ynn_unary_round, 1266, 1275);
  g->Binary(ynn_binary_max, 1275, 3328, 1284);
  g->Binary(ynn_binary_min, 1284, 3384, 1288);
  g->Binary(ynn_binary_multiply, 1288, 3299, 1299);
  g->Unary(ynn_unary_square, 1299, 1310);
  g->Reduce(ynn_reduce_sum, 1310, 3048, {2}, true);
  g->ShapeProduct(1310, 3047, {2});
  g->Binary(ynn_binary_divide, 3048, 3047, 1321);
  g->Binary(ynn_binary_add, 1321, 3400, 1332);
  g->Binary(ynn_binary_pow, 1332, 3424, 1343);
  g->Binary(ynn_binary_multiply, 1299, 1343, 1354);
  g->Convert(3506, 1365);
  g->Binary(ynn_binary_multiply, 1354, 1365, 1371);
  g->Binary(ynn_binary_add, 977, 1371, 1382);
  g->Convert(3493, 1393);
  g->Binary(ynn_binary_multiply, 1382, 1393, 1404);
}

// Scope: "Layer0"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0(Context& ctx) {
  BuildLayer0Attention(ctx);
  BuildLayer0Mlp(ctx);
  BuildLayer0PerLayerEmbedding(ctx);
}

// Scope: "Layer1 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 1482, 3325, 1488);
  g->Unary(ynn_unary_round, 1488, 1499);
  g->Binary(ynn_binary_max, 1499, 3328, 1508);
  g->Binary(ynn_binary_min, 1508, 3384, 1512);
  g->Binary(ynn_binary_multiply, 1512, 3325, 1524);
  g->Convert(3535, 1535);
  g->Binary(ynn_binary_multiply, 1535, 3536, 1545);
  g->Matmul(1524, 1545, 1556, false, true);
  g->Binary(ynn_binary_divide, 1556, 3411, 1567);
  g->Unary(ynn_unary_round, 1567, 1578);
  g->Binary(ynn_binary_max, 1578, 3328, 1588);
  g->Binary(ynn_binary_min, 1588, 3384, 1595);
  g->Binary(ynn_binary_multiply, 1595, 3411, 1606);
  g->Reshape(1606, 1617, {1,0,1,256});
  g->Transpose(1617, 1629, {0,2,1,3});
  g->Unary(ynn_unary_square, 1629, 1640);
  g->Reduce(ynn_reduce_sum, 1640, 3095, {3}, true);
  g->ShapeProduct(1640, 3094, {3});
  g->Binary(ynn_binary_divide, 3095, 3094, 1651);
  g->Binary(ynn_binary_add, 1651, 3400, 1662);
  g->Binary(ynn_binary_pow, 1662, 3424, 1673);
  g->Binary(ynn_binary_multiply, 1629, 1673, 1684);
  g->Convert(3534, 1695);
  g->Binary(ynn_binary_multiply, 1684, 1695, 1706);
  g->Slice(1706, 1712, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1706, 1723, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1723, 1731);
  g->Concat({1731,1712}, 1737, 3);
  g->Binary(ynn_binary_multiply, 1706, 2025, 1748);
  g->Binary(ynn_binary_multiply, 1737, 2249, 1759);
  g->Binary(ynn_binary_add, 1748, 1759, 1769);
  g->Convert(3542, 1826);
  g->Binary(ynn_binary_multiply, 1826, 3543, 1837);
  g->Matmul(1524, 1837, 1848, false, true);
  g->Binary(ynn_binary_divide, 1848, 3411, 1859);
  g->Unary(ynn_unary_round, 1859, 1870);
  g->Binary(ynn_binary_max, 1870, 3328, 1881);
  g->Binary(ynn_binary_min, 1881, 3384, 1892);
  g->Binary(ynn_binary_multiply, 1892, 3411, 1903);
  g->Reshape(1903, 1914, {1,0,1,256});
  g->Transpose(1914, 1925, {0,2,1,3});
  g->Unary(ynn_unary_square, 1925, 1932);
  g->Reduce(ynn_reduce_sum, 1932, 3134, {3}, true);
  g->ShapeProduct(1932, 3133, {3});
  g->Binary(ynn_binary_divide, 3134, 3133, 1943);
  g->Binary(ynn_binary_add, 1943, 3400, 1949);
  g->Binary(ynn_binary_pow, 1949, 3424, 1956);
  g->Binary(ynn_binary_multiply, 1925, 1956, 1967);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1769, 1977, 0.005761673673987389, 0);
  g->Append(3263, 1977, 3880, 2, s2, s1);
  g->View(3880, 3910, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3910, 2008, 0.005761673673987389, 0);
  g->Quantize(1967, 2019, 0.047244105488061905, 0);
  g->Append(3278, 2019, 3895, 2, s2, s1);
  g->View(3895, 3924, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3924, 2047, 0.047244105488061905, 0);
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3540, 2108);
  g->Binary(ynn_binary_multiply, 2108, 3541, 2119);
  g->Matmul(1524, 2119, 2131, false, true);
  g->Binary(ynn_binary_divide, 2131, 3368, 2141);
  g->Unary(ynn_unary_round, 2141, 2148);
  g->Binary(ynn_binary_max, 2148, 3328, 2159);
  g->Binary(ynn_binary_min, 2159, 3384, 2161);
  g->Binary(ynn_binary_multiply, 2161, 3368, 2162);
  g->SplitDim(2162, 2163, 2, {8,256});
  g->Transpose(2163, 2164, {0,2,1,3});
  g->Unary(ynn_unary_square, 2164, 2165);
  g->Reduce(ynn_reduce_sum, 2165, 3165, {3}, true);
  g->ShapeProduct(2165, 3164, {3});
  g->Binary(ynn_binary_divide, 3165, 3164, 2166);
  g->Binary(ynn_binary_add, 2166, 3400, 2168);
  g->Binary(ynn_binary_pow, 2168, 3424, 2169);
  g->Binary(ynn_binary_multiply, 2164, 2169, 2170);
  g->Convert(3539, 2171);
  g->Binary(ynn_binary_multiply, 2170, 2171, 2172);
  g->Slice(2172, 2173, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2172, 2174, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2174, 2175);
  g->Concat({2175,2173}, 2176, 3);
  g->Binary(ynn_binary_multiply, 2172, 2025, 2177);
  g->Binary(ynn_binary_multiply, 2176, 2249, 2179);
  g->Binary(ynn_binary_add, 2177, 2179, 2180);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2180, 2008, 2181, false, true);
  g->Mask(2181, 3479, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3479, 3169, {-1}, true);
  g->Binary(ynn_binary_subtract, 3479, 3169, 3166);
  g->Unary(ynn_unary_exp, 3166, 3167);
  g->Reduce(ynn_reduce_sum, 3167, 3170, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3170, 3168);
  g->Binary(ynn_binary_multiply, 3167, 3168, 2182);
  g->Matmul(2182, 2047, 2183, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2183, 2184, {0,2,1,3});
  g->FuseDims(2184, 2185, 2, 2);
  g->Binary(ynn_binary_divide, 2185, 3458, 2186);
  g->Unary(ynn_unary_round, 2186, 2187);
  g->Binary(ynn_binary_max, 2187, 3328, 2189);
  g->Binary(ynn_binary_min, 2189, 3384, 2190);
  g->Binary(ynn_binary_multiply, 2190, 3458, 2191);
  g->Convert(3537, 2192);
  g->Binary(ynn_binary_multiply, 2192, 3538, 2193);
  g->Matmul(2191, 2193, 2194, false, true);
  g->Binary(ynn_binary_divide, 2194, 3330, 2195);
  g->Unary(ynn_unary_round, 2195, 2196);
  g->Binary(ynn_binary_max, 2196, 3328, 2197);
  g->Binary(ynn_binary_min, 2197, 3384, 2198);
  g->Binary(ynn_binary_multiply, 2198, 3330, 2200);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1404, 1415);
  g->Reduce(ynn_reduce_sum, 1415, 3064, {2}, true);
  g->ShapeProduct(1415, 3063, {2});
  g->Binary(ynn_binary_divide, 3064, 3063, 1427);
  g->Binary(ynn_binary_add, 1427, 3400, 1438);
  g->Binary(ynn_binary_pow, 1438, 3424, 1449);
  g->Binary(ynn_binary_multiply, 1404, 1449, 1460);
  g->Convert(3518, 1471);
  g->Binary(ynn_binary_multiply, 1460, 1471, 1482);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2200, 2201);
  g->Reduce(ynn_reduce_sum, 2201, 3172, {2}, true);
  g->ShapeProduct(2201, 3171, {2});
  g->Binary(ynn_binary_divide, 3172, 3171, 2202);
  g->Binary(ynn_binary_add, 2202, 3400, 2203);
  g->Binary(ynn_binary_pow, 2203, 3424, 2204);
  g->Binary(ynn_binary_multiply, 2200, 2204, 2205);
  g->Convert(3530, 2206);
  g->Binary(ynn_binary_multiply, 2205, 2206, 2207);
  g->Binary(ynn_binary_add, 1404, 2207, 2208);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2208, 2209);
  g->Reduce(ynn_reduce_sum, 2209, 3174, {2}, true);
  g->ShapeProduct(2209, 3173, {2});
  g->Binary(ynn_binary_divide, 3174, 3173, 2211);
  g->Binary(ynn_binary_add, 2211, 3400, 2212);
  g->Binary(ynn_binary_pow, 2212, 3424, 2213);
  g->Binary(ynn_binary_multiply, 2208, 2213, 2214);
  g->Convert(3533, 2215);
  g->Binary(ynn_binary_multiply, 2214, 2215, 2216);
  g->Binary(ynn_binary_divide, 2216, 3416, 2217);
  g->Unary(ynn_unary_round, 2217, 2218);
  g->Binary(ynn_binary_max, 2218, 3328, 2219);
  g->Binary(ynn_binary_min, 2219, 3384, 2220);
  g->Binary(ynn_binary_multiply, 2220, 3416, 2222);
  g->Convert(3524, 2223);
  g->Binary(ynn_binary_multiply, 2223, 3525, 2224);
  g->Matmul(2222, 2224, 2225, false, true);
  g->Binary(ynn_binary_divide, 2225, 3298, 2226);
  g->Unary(ynn_unary_round, 2226, 2227);
  g->Binary(ynn_binary_max, 2227, 3328, 2228);
  g->Binary(ynn_binary_min, 2228, 3384, 2229);
  g->Binary(ynn_binary_multiply, 2229, 3298, 2230);
  g->Convert(3522, 2232);
  g->Binary(ynn_binary_multiply, 2232, 3523, 2233);
  g->Matmul(2222, 2233, 2234, false, true);
  g->Binary(ynn_binary_divide, 2234, 3298, 2235);
  g->Unary(ynn_unary_round, 2235, 2236);
  g->Binary(ynn_binary_max, 2236, 3328, 2237);
  g->Binary(ynn_binary_min, 2237, 3384, 2239);
  g->Binary(ynn_binary_multiply, 2239, 3298, 2240);
  g->Polynomial(2240, 3177, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3177, 3178);
  g->Binary(ynn_binary_add, 3178, 2855, 3175);
  g->Binary(ynn_binary_multiply, 2240, 2853, 3176);
  g->Binary(ynn_binary_multiply, 3176, 3175, 2241);
  g->Binary(ynn_binary_multiply, 2230, 2241, 2242);
  g->Binary(ynn_binary_divide, 2242, 3294, 2243);
  g->Unary(ynn_unary_round, 2243, 2244);
  g->Binary(ynn_binary_max, 2244, 3328, 2245);
  g->Binary(ynn_binary_min, 2245, 3384, 2246);
  g->Binary(ynn_binary_multiply, 2246, 3294, 2247);
  g->Convert(3520, 2248);
  g->Binary(ynn_binary_multiply, 2248, 3521, 2251);
  g->Matmul(2247, 2251, 2252, false, true);
  g->Binary(ynn_binary_divide, 2252, 3302, 2253);
  g->Unary(ynn_unary_round, 2253, 2254);
  g->Binary(ynn_binary_max, 2254, 3328, 2255);
  g->Binary(ynn_binary_min, 2255, 3384, 2256);
  g->Binary(ynn_binary_multiply, 2256, 3302, 2257);
  g->Unary(ynn_unary_square, 2257, 2258);
  g->Reduce(ynn_reduce_sum, 2258, 3180, {2}, true);
  g->ShapeProduct(2258, 3179, {2});
  g->Binary(ynn_binary_divide, 3180, 3179, 2259);
  g->Binary(ynn_binary_add, 2259, 3400, 2260);
  g->Binary(ynn_binary_pow, 2260, 3424, 2262);
  g->Binary(ynn_binary_multiply, 2257, 2262, 2263);
  g->Convert(3531, 2264);
  g->Binary(ynn_binary_multiply, 2263, 2264, 2265);
  g->Binary(ynn_binary_add, 2208, 2265, 2266);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2267, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(2267, 2268, {1,0,256});
  g->Binary(ynn_binary_add, 2268, 3865, 2269);
  g->Binary(ynn_binary_multiply, 2269, 3296, 2270);
  g->Binary(ynn_binary_divide, 2266, 3376, 2271);
  g->Unary(ynn_unary_round, 2271, 2273);
  g->Binary(ynn_binary_max, 2273, 3328, 2274);
  g->Binary(ynn_binary_min, 2274, 3384, 2275);
  g->Binary(ynn_binary_multiply, 2275, 3376, 2276);
  g->Convert(3526, 2277);
  g->Binary(ynn_binary_multiply, 2277, 3527, 2278);
  g->Matmul(2276, 2278, 2279, false, true);
  g->Binary(ynn_binary_divide, 2279, 3457, 2280);
  g->Unary(ynn_unary_round, 2280, 2281);
  g->Binary(ynn_binary_max, 2281, 3328, 2282);
  g->Binary(ynn_binary_min, 2282, 3384, 2284);
  g->Binary(ynn_binary_multiply, 2284, 3457, 2285);
  g->Polynomial(2285, 3183, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3183, 3184);
  g->Binary(ynn_binary_add, 3184, 2855, 3181);
  g->Binary(ynn_binary_multiply, 2285, 2853, 3182);
  g->Binary(ynn_binary_multiply, 3182, 3181, 2286);
  g->Binary(ynn_binary_multiply, 2286, 2270, 2287);
  g->Binary(ynn_binary_divide, 2287, 3399, 2288);
  g->Unary(ynn_unary_round, 2288, 2289);
  g->Binary(ynn_binary_max, 2289, 3328, 2290);
  g->Binary(ynn_binary_min, 2290, 3384, 2291);
  g->Binary(ynn_binary_multiply, 2291, 3399, 2292);
  g->Convert(3528, 2293);
  g->Binary(ynn_binary_multiply, 2293, 3529, 2295);
  g->Matmul(2292, 2295, 2296, false, true);
  g->Binary(ynn_binary_divide, 2296, 3386, 2297);
  g->Unary(ynn_unary_round, 2297, 2298);
  g->Binary(ynn_binary_max, 2298, 3328, 2299);
  g->Binary(ynn_binary_min, 2299, 3384, 2300);
  g->Binary(ynn_binary_multiply, 2300, 3386, 2301);
  g->Unary(ynn_unary_square, 2301, 2302);
  g->Reduce(ynn_reduce_sum, 2302, 3188, {2}, true);
  g->ShapeProduct(2302, 3187, {2});
  g->Binary(ynn_binary_divide, 3188, 3187, 2303);
  g->Binary(ynn_binary_add, 2303, 3400, 2304);
  g->Binary(ynn_binary_pow, 2304, 3424, 2306);
  g->Binary(ynn_binary_multiply, 2301, 2306, 2307);
  g->Convert(3532, 2308);
  g->Binary(ynn_binary_multiply, 2307, 2308, 2309);
  g->Binary(ynn_binary_add, 2266, 2309, 2310);
  g->Convert(3519, 2311);
  g->Binary(ynn_binary_multiply, 2310, 2311, 2312);
}

// Scope: "Layer1"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1(Context& ctx) {
  BuildLayer1Attention(ctx);
  BuildLayer1Mlp(ctx);
  BuildLayer1PerLayerEmbedding(ctx);
}

// Scope: "Layer2 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2320, 3454, 2321);
  g->Unary(ynn_unary_round, 2321, 2322);
  g->Binary(ynn_binary_max, 2322, 3328, 2323);
  g->Binary(ynn_binary_min, 2323, 3384, 2324);
  g->Binary(ynn_binary_multiply, 2324, 3454, 2325);
  g->Convert(3671, 2326);
  g->Binary(ynn_binary_multiply, 2326, 3672, 2328);
  g->Matmul(2325, 2328, 2329, false, true);
  g->Binary(ynn_binary_divide, 2329, 3462, 2330);
  g->Unary(ynn_unary_round, 2330, 2331);
  g->Binary(ynn_binary_max, 2331, 3328, 2332);
  g->Binary(ynn_binary_min, 2332, 3384, 2333);
  g->Binary(ynn_binary_multiply, 2333, 3462, 2334);
  g->Reshape(2334, 2335, {1,0,1,256});
  g->Transpose(2335, 2336, {0,2,1,3});
  g->Unary(ynn_unary_square, 2336, 2337);
  g->Reduce(ynn_reduce_sum, 2337, 3192, {3}, true);
  g->ShapeProduct(2337, 3191, {3});
  g->Binary(ynn_binary_divide, 3192, 3191, 2339);
  g->Binary(ynn_binary_add, 2339, 3400, 2340);
  g->Binary(ynn_binary_pow, 2340, 3424, 2341);
  g->Binary(ynn_binary_multiply, 2336, 2341, 2342);
  g->Convert(3670, 2343);
  g->Binary(ynn_binary_multiply, 2342, 2343, 2344);
  g->Slice(2344, 2345, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2344, 2346, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2346, 2347);
  g->Concat({2347,2345}, 2348, 3);
  g->Binary(ynn_binary_multiply, 2344, 2025, 2350);
  g->Binary(ynn_binary_multiply, 2348, 2249, 2351);
  g->Binary(ynn_binary_add, 2350, 2351, 2352);
  g->Convert(3678, 2353);
  g->Binary(ynn_binary_multiply, 2353, 3679, 2354);
  g->Matmul(2325, 2354, 2357, false, true);
  g->Binary(ynn_binary_divide, 2357, 3462, 2358);
  g->Unary(ynn_unary_round, 2358, 2359);
  g->Binary(ynn_binary_max, 2359, 3328, 2360);
  g->Binary(ynn_binary_min, 2360, 3384, 2361);
  g->Binary(ynn_binary_multiply, 2361, 3462, 2362);
  g->Reshape(2362, 2363, {1,0,1,256});
  g->Transpose(2363, 2364, {0,2,1,3});
  g->Unary(ynn_unary_square, 2364, 2365);
  g->Reduce(ynn_reduce_sum, 2365, 3194, {3}, true);
  g->ShapeProduct(2365, 3193, {3});
  g->Binary(ynn_binary_divide, 3194, 3193, 2366);
  g->Binary(ynn_binary_add, 2366, 3400, 2368);
  g->Binary(ynn_binary_pow, 2368, 3424, 2369);
  g->Binary(ynn_binary_multiply, 2364, 2369, 2370);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2352, 2371, 0.005684707313776016, 0);
  g->Append(3269, 2371, 3886, 2, s2, s1);
  g->View(3886, 3915, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3915, 2372, 0.005684707313776016, 0);
  g->Quantize(2370, 2373, 0.047244105488061905, 0);
  g->Append(3284, 2373, 3901, 2, s2, s1);
  g->View(3901, 3929, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3929, 2375, 0.047244105488061905, 0);
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3676, 2376);
  g->Binary(ynn_binary_multiply, 2376, 3677, 2377);
  g->Matmul(2325, 2377, 2378, false, true);
  g->Binary(ynn_binary_divide, 2378, 3414, 2379);
  g->Unary(ynn_unary_round, 2379, 2381);
  g->Binary(ynn_binary_max, 2381, 3328, 2382);
  g->Binary(ynn_binary_min, 2382, 3384, 2383);
  g->Binary(ynn_binary_multiply, 2383, 3414, 2384);
  g->SplitDim(2384, 2385, 2, {8,256});
  g->Transpose(2385, 2386, {0,2,1,3});
  g->Unary(ynn_unary_square, 2386, 2387);
  g->Reduce(ynn_reduce_sum, 2387, 3196, {3}, true);
  g->ShapeProduct(2387, 3195, {3});
  g->Binary(ynn_binary_divide, 3196, 3195, 2388);
  g->Binary(ynn_binary_add, 2388, 3400, 2389);
  g->Binary(ynn_binary_pow, 2389, 3424, 2390);
  g->Binary(ynn_binary_multiply, 2386, 2390, 2392);
  g->Convert(3675, 2393);
  g->Binary(ynn_binary_multiply, 2392, 2393, 2394);
  g->Slice(2394, 2395, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2394, 2396, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2396, 2397);
  g->Concat({2397,2395}, 2398, 3);
  g->Binary(ynn_binary_multiply, 2394, 2025, 2399);
  g->Binary(ynn_binary_multiply, 2398, 2249, 2400);
  g->Binary(ynn_binary_add, 2399, 2400, 2401);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2401, 2372, 2403, false, true);
  g->Mask(2403, 3484, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3484, 3200, {-1}, true);
  g->Binary(ynn_binary_subtract, 3484, 3200, 3197);
  g->Unary(ynn_unary_exp, 3197, 3198);
  g->Reduce(ynn_reduce_sum, 3198, 3201, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3201, 3199);
  g->Binary(ynn_binary_multiply, 3198, 3199, 2404);
  g->Matmul(2404, 2375, 2405, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2405, 2406, {0,2,1,3});
  g->FuseDims(2406, 2407, 2, 2);
  g->Binary(ynn_binary_divide, 2407, 3365, 2408);
  g->Unary(ynn_unary_round, 2408, 2409);
  g->Binary(ynn_binary_max, 2409, 3328, 2410);
  g->Binary(ynn_binary_min, 2410, 3384, 2411);
  g->Binary(ynn_binary_multiply, 2411, 3365, 2413);
  g->Convert(3673, 2414);
  g->Binary(ynn_binary_multiply, 2414, 3674, 2415);
  g->Matmul(2413, 2415, 2416, false, true);
  g->Binary(ynn_binary_divide, 2416, 3354, 2417);
  g->Unary(ynn_unary_round, 2417, 2418);
  g->Binary(ynn_binary_max, 2418, 3328, 2419);
  g->Binary(ynn_binary_min, 2419, 3384, 2420);
  g->Binary(ynn_binary_multiply, 2420, 3354, 2421);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2312, 2313);
  g->Reduce(ynn_reduce_sum, 2313, 3190, {2}, true);
  g->ShapeProduct(2313, 3189, {2});
  g->Binary(ynn_binary_divide, 3190, 3189, 2314);
  g->Binary(ynn_binary_add, 2314, 3400, 2315);
  g->Binary(ynn_binary_pow, 2315, 3424, 2317);
  g->Binary(ynn_binary_multiply, 2312, 2317, 2318);
  g->Convert(3654, 2319);
  g->Binary(ynn_binary_multiply, 2318, 2319, 2320);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2421, 2422);
  g->Reduce(ynn_reduce_sum, 2422, 3203, {2}, true);
  g->ShapeProduct(2422, 3202, {2});
  g->Binary(ynn_binary_divide, 3203, 3202, 2423);
  g->Binary(ynn_binary_add, 2423, 3400, 2424);
  g->Binary(ynn_binary_pow, 2424, 3424, 2425);
  g->Binary(ynn_binary_multiply, 2421, 2425, 2426);
  g->Convert(3666, 2427);
  g->Binary(ynn_binary_multiply, 2426, 2427, 2428);
  g->Binary(ynn_binary_add, 2312, 2428, 2429);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2429, 2430);
  g->Reduce(ynn_reduce_sum, 2430, 3205, {2}, true);
  g->ShapeProduct(2430, 3204, {2});
  g->Binary(ynn_binary_divide, 3205, 3204, 2431);
  g->Binary(ynn_binary_add, 2431, 3400, 2432);
  g->Binary(ynn_binary_pow, 2432, 3424, 2433);
  g->Binary(ynn_binary_multiply, 2429, 2433, 2434);
  g->Convert(3669, 2435);
  g->Binary(ynn_binary_multiply, 2434, 2435, 2436);
  g->Binary(ynn_binary_divide, 2436, 3447, 2437);
  g->Unary(ynn_unary_round, 2437, 2438);
  g->Binary(ynn_binary_max, 2438, 3328, 2439);
  g->Binary(ynn_binary_min, 2439, 3384, 2440);
  g->Binary(ynn_binary_multiply, 2440, 3447, 2441);
  g->Convert(3660, 2442);
  g->Binary(ynn_binary_multiply, 2442, 3661, 2443);
  g->Matmul(2441, 2443, 2444, false, true);
  g->Binary(ynn_binary_divide, 2444, 3361, 2445);
  g->Unary(ynn_unary_round, 2445, 2446);
  g->Binary(ynn_binary_max, 2446, 3328, 2447);
  g->Binary(ynn_binary_min, 2447, 3384, 2448);
  g->Binary(ynn_binary_multiply, 2448, 3361, 2449);
  g->Convert(3658, 2451);
  g->Binary(ynn_binary_multiply, 2451, 3659, 2452);
  g->Matmul(2441, 2452, 2453, false, true);
  g->Binary(ynn_binary_divide, 2453, 3361, 2454);
  g->Unary(ynn_unary_round, 2454, 2455);
  g->Binary(ynn_binary_max, 2455, 3328, 2456);
  g->Binary(ynn_binary_min, 2456, 3384, 2457);
  g->Binary(ynn_binary_multiply, 2457, 3361, 2458);
  g->Polynomial(2458, 3208, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3208, 3209);
  g->Binary(ynn_binary_add, 3209, 2855, 3206);
  g->Binary(ynn_binary_multiply, 2458, 2853, 3207);
  g->Binary(ynn_binary_multiply, 3207, 3206, 2459);
  g->Binary(ynn_binary_multiply, 2449, 2459, 2460);
  g->Binary(ynn_binary_divide, 2460, 3420, 2461);
  g->Unary(ynn_unary_round, 2461, 2462);
  g->Binary(ynn_binary_max, 2462, 3328, 2463);
  g->Binary(ynn_binary_min, 2463, 3384, 2464);
  g->Binary(ynn_binary_multiply, 2464, 3420, 2465);
  g->Convert(3656, 2466);
  g->Binary(ynn_binary_multiply, 2466, 3657, 2467);
  g->Matmul(2465, 2467, 2468, false, true);
  g->Binary(ynn_binary_divide, 2468, 3432, 2470);
  g->Unary(ynn_unary_round, 2470, 2471);
  g->Binary(ynn_binary_max, 2471, 3328, 2472);
  g->Binary(ynn_binary_min, 2472, 3384, 2473);
  g->Binary(ynn_binary_multiply, 2473, 3432, 2474);
  g->Unary(ynn_unary_square, 2474, 2475);
  g->Reduce(ynn_reduce_sum, 2475, 3211, {2}, true);
  g->ShapeProduct(2475, 3210, {2});
  g->Binary(ynn_binary_divide, 3211, 3210, 2476);
  g->Binary(ynn_binary_add, 2476, 3400, 2477);
  g->Binary(ynn_binary_pow, 2477, 3424, 2478);
  g->Binary(ynn_binary_multiply, 2474, 2478, 2479);
  g->Convert(3667, 2481);
  g->Binary(ynn_binary_multiply, 2479, 2481, 2482);
  g->Binary(ynn_binary_add, 2429, 2482, 2483);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2484, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(2484, 2485, {1,0,256});
  g->Binary(ynn_binary_add, 2485, 3870, 2486);
  g->Binary(ynn_binary_multiply, 2486, 3296, 2487);
  g->Binary(ynn_binary_divide, 2483, 3406, 2488);
  g->Unary(ynn_unary_round, 2488, 2489);
  g->Binary(ynn_binary_max, 2489, 3328, 2490);
  g->Binary(ynn_binary_min, 2490, 3384, 2492);
  g->Binary(ynn_binary_multiply, 2492, 3406, 2493);
  g->Convert(3662, 2494);
  g->Binary(ynn_binary_multiply, 2494, 3663, 2495);
  g->Matmul(2493, 2495, 2496, false, true);
  g->Binary(ynn_binary_divide, 2496, 3360, 2497);
  g->Unary(ynn_unary_round, 2497, 2498);
  g->Binary(ynn_binary_max, 2498, 3328, 2499);
  g->Binary(ynn_binary_min, 2499, 3384, 2500);
  g->Binary(ynn_binary_multiply, 2500, 3360, 2501);
  g->Polynomial(2501, 3214, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3214, 3215);
  g->Binary(ynn_binary_add, 3215, 2855, 3212);
  g->Binary(ynn_binary_multiply, 2501, 2853, 3213);
  g->Binary(ynn_binary_multiply, 3213, 3212, 2503);
  g->Binary(ynn_binary_multiply, 2503, 2487, 2504);
  g->Binary(ynn_binary_divide, 2504, 3465, 2505);
  g->Unary(ynn_unary_round, 2505, 2506);
  g->Binary(ynn_binary_max, 2506, 3328, 2507);
  g->Binary(ynn_binary_min, 2507, 3384, 2508);
  g->Binary(ynn_binary_multiply, 2508, 3465, 2509);
  g->Convert(3664, 2510);
  g->Binary(ynn_binary_multiply, 2510, 3665, 2511);
  g->Matmul(2509, 2511, 2512, false, true);
  g->Binary(ynn_binary_divide, 2512, 3362, 2514);
  g->Unary(ynn_unary_round, 2514, 2515);
  g->Binary(ynn_binary_max, 2515, 3328, 2516);
  g->Binary(ynn_binary_min, 2516, 3384, 2517);
  g->Binary(ynn_binary_multiply, 2517, 3362, 2518);
  g->Unary(ynn_unary_square, 2518, 2519);
  g->Reduce(ynn_reduce_sum, 2519, 3217, {2}, true);
  g->ShapeProduct(2519, 3216, {2});
  g->Binary(ynn_binary_divide, 3217, 3216, 2520);
  g->Binary(ynn_binary_add, 2520, 3400, 2521);
  g->Binary(ynn_binary_pow, 2521, 3424, 2522);
  g->Binary(ynn_binary_multiply, 2518, 2522, 2523);
  g->Convert(3668, 2525);
  g->Binary(ynn_binary_multiply, 2523, 2525, 2526);
  g->Binary(ynn_binary_add, 2483, 2526, 2527);
  g->Convert(3655, 2528);
  g->Binary(ynn_binary_multiply, 2527, 2528, 2529);
}

// Scope: "Layer2"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2(Context& ctx) {
  BuildLayer2Attention(ctx);
  BuildLayer2Mlp(ctx);
  BuildLayer2PerLayerEmbedding(ctx);
}

// Scope: "Layer3 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2537, 3440, 2538);
  g->Unary(ynn_unary_round, 2538, 2539);
  g->Binary(ynn_binary_max, 2539, 3328, 2540);
  g->Binary(ynn_binary_min, 2540, 3384, 2541);
  g->Binary(ynn_binary_multiply, 2541, 3440, 2542);
  g->Convert(3697, 2543);
  g->Binary(ynn_binary_multiply, 2543, 3698, 2544);
  g->Matmul(2542, 2544, 2545, false, true);
  g->Binary(ynn_binary_divide, 2545, 3293, 2547);
  g->Unary(ynn_unary_round, 2547, 2548);
  g->Binary(ynn_binary_max, 2548, 3328, 2549);
  g->Binary(ynn_binary_min, 2549, 3384, 2550);
  g->Binary(ynn_binary_multiply, 2550, 3293, 2551);
  g->Reshape(2551, 2552, {1,0,1,256});
  g->Transpose(2552, 2553, {0,2,1,3});
  g->Unary(ynn_unary_square, 2553, 2554);
  g->Reduce(ynn_reduce_sum, 2554, 3221, {3}, true);
  g->ShapeProduct(2554, 3220, {3});
  g->Binary(ynn_binary_divide, 3221, 3220, 2555);
  g->Binary(ynn_binary_add, 2555, 3400, 2556);
  g->Binary(ynn_binary_pow, 2556, 3424, 2559);
  g->Binary(ynn_binary_multiply, 2553, 2559, 2560);
  g->Convert(3696, 2561);
  g->Binary(ynn_binary_multiply, 2560, 2561, 2562);
  g->Slice(2562, 2563, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2562, 2564, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2564, 2565);
  g->Concat({2565,2563}, 2566, 3);
  g->Binary(ynn_binary_multiply, 2562, 2025, 2567);
  g->Binary(ynn_binary_multiply, 2566, 2249, 2568);
  g->Binary(ynn_binary_add, 2567, 2568, 2570);
  g->Convert(3704, 2571);
  g->Binary(ynn_binary_multiply, 2571, 3705, 2572);
  g->Matmul(2542, 2572, 2573, false, true);
  g->Binary(ynn_binary_divide, 2573, 3293, 2574);
  g->Unary(ynn_unary_round, 2574, 2576);
  g->Binary(ynn_binary_max, 2576, 3328, 2577);
  g->Binary(ynn_binary_min, 2577, 3384, 2578);
  g->Binary(ynn_binary_multiply, 2578, 3293, 2579);
  g->Reshape(2579, 2580, {1,0,1,256});
  g->Transpose(2580, 2581, {0,2,1,3});
  g->Unary(ynn_unary_square, 2581, 2582);
  g->Reduce(ynn_reduce_sum, 2582, 3223, {3}, true);
  g->ShapeProduct(2582, 3222, {3});
  g->Binary(ynn_binary_divide, 3223, 3222, 2583);
  g->Binary(ynn_binary_add, 2583, 3400, 2584);
  g->Binary(ynn_binary_pow, 2584, 3424, 2585);
  g->Binary(ynn_binary_multiply, 2581, 2585, 2587);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2570, 2588, 0.00573749840259552, 0);
  g->Append(3270, 2588, 3887, 2, s2, s1);
  g->View(3887, 3916, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3916, 2589, 0.00573749840259552, 0);
  g->Quantize(2587, 2590, 0.047244105488061905, 0);
  g->Append(3285, 2590, 3902, 2, s2, s1);
  g->View(3902, 3930, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3930, 2591, 0.047244105488061905, 0);
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3702, 2593);
  g->Binary(ynn_binary_multiply, 2593, 3703, 2594);
  g->Matmul(2542, 2594, 2595, false, true);
  g->Binary(ynn_binary_divide, 2595, 3476, 2596);
  g->Unary(ynn_unary_round, 2596, 2597);
  g->Binary(ynn_binary_max, 2597, 3328, 2598);
  g->Binary(ynn_binary_min, 2598, 3384, 2600);
  g->Binary(ynn_binary_multiply, 2600, 3476, 2601);
  g->SplitDim(2601, 2602, 2, {8,256});
  g->Transpose(2602, 2603, {0,2,1,3});
  g->Unary(ynn_unary_square, 2603, 2604);
  g->Reduce(ynn_reduce_sum, 2604, 3227, {3}, true);
  g->ShapeProduct(2604, 3226, {3});
  g->Binary(ynn_binary_divide, 3227, 3226, 2605);
  g->Binary(ynn_binary_add, 2605, 3400, 2606);
  g->Binary(ynn_binary_pow, 2606, 3424, 2607);
  g->Binary(ynn_binary_multiply, 2603, 2607, 2608);
  g->Convert(3701, 2609);
  g->Binary(ynn_binary_multiply, 2608, 2609, 2611);
  g->Slice(2611, 2612, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2611, 2613, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2613, 2614);
  g->Concat({2614,2612}, 2615, 3);
  g->Binary(ynn_binary_multiply, 2611, 2025, 2616);
  g->Binary(ynn_binary_multiply, 2615, 2249, 2617);
  g->Binary(ynn_binary_add, 2616, 2617, 2618);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2618, 2589, 2619, false, true);
  g->Mask(2619, 3485, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3485, 3231, {-1}, true);
  g->Binary(ynn_binary_subtract, 3485, 3231, 3228);
  g->Unary(ynn_unary_exp, 3228, 3229);
  g->Reduce(ynn_reduce_sum, 3229, 3232, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3232, 3230);
  g->Binary(ynn_binary_multiply, 3229, 3230, 2621);
  g->Matmul(2621, 2591, 2622, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2622, 2623, {0,2,1,3});
  g->FuseDims(2623, 2624, 2, 2);
  g->Binary(ynn_binary_divide, 2624, 3313, 2625);
  g->Unary(ynn_unary_round, 2625, 2626);
  g->Binary(ynn_binary_max, 2626, 3328, 2627);
  g->Binary(ynn_binary_min, 2627, 3384, 2628);
  g->Binary(ynn_binary_multiply, 2628, 3313, 2629);
  g->Convert(3699, 2630);
  g->Binary(ynn_binary_multiply, 2630, 3700, 2631);
  g->Matmul(2629, 2631, 2632, false, true);
  g->Binary(ynn_binary_divide, 2632, 3396, 2633);
  g->Unary(ynn_unary_round, 2633, 2634);
  g->Binary(ynn_binary_max, 2634, 3328, 2635);
  g->Binary(ynn_binary_min, 2635, 3384, 2636);
  g->Binary(ynn_binary_multiply, 2636, 3396, 2637);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2529, 2530);
  g->Reduce(ynn_reduce_sum, 2530, 3219, {2}, true);
  g->ShapeProduct(2530, 3218, {2});
  g->Binary(ynn_binary_divide, 3219, 3218, 2531);
  g->Binary(ynn_binary_add, 2531, 3400, 2532);
  g->Binary(ynn_binary_pow, 2532, 3424, 2533);
  g->Binary(ynn_binary_multiply, 2529, 2533, 2534);
  g->Convert(3680, 2536);
  g->Binary(ynn_binary_multiply, 2534, 2536, 2537);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2637, 2638);
  g->Reduce(ynn_reduce_sum, 2638, 3234, {2}, true);
  g->ShapeProduct(2638, 3233, {2});
  g->Binary(ynn_binary_divide, 3234, 3233, 2639);
  g->Binary(ynn_binary_add, 2639, 3400, 2640);
  g->Binary(ynn_binary_pow, 2640, 3424, 2641);
  g->Binary(ynn_binary_multiply, 2637, 2641, 2642);
  g->Convert(3692, 2643);
  g->Binary(ynn_binary_multiply, 2642, 2643, 2644);
  g->Binary(ynn_binary_add, 2529, 2644, 2645);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2645, 2646);
  g->Reduce(ynn_reduce_sum, 2646, 3236, {2}, true);
  g->ShapeProduct(2646, 3235, {2});
  g->Binary(ynn_binary_divide, 3236, 3235, 2647);
  g->Binary(ynn_binary_add, 2647, 3400, 2648);
  g->Binary(ynn_binary_pow, 2648, 3424, 2649);
  g->Binary(ynn_binary_multiply, 2645, 2649, 2650);
  g->Convert(3695, 2653);
  g->Binary(ynn_binary_multiply, 2650, 2653, 2654);
  g->Binary(ynn_binary_divide, 2654, 3333, 2655);
  g->Unary(ynn_unary_round, 2655, 2656);
  g->Binary(ynn_binary_max, 2656, 3328, 2657);
  g->Binary(ynn_binary_min, 2657, 3384, 2658);
  g->Binary(ynn_binary_multiply, 2658, 3333, 2659);
  g->Convert(3686, 2660);
  g->Binary(ynn_binary_multiply, 2660, 3687, 2661);
  g->Matmul(2659, 2661, 2662, false, true);
  g->Binary(ynn_binary_divide, 2662, 3459, 2664);
  g->Unary(ynn_unary_round, 2664, 2665);
  g->Binary(ynn_binary_max, 2665, 3328, 2666);
  g->Binary(ynn_binary_min, 2666, 3384, 2667);
  g->Binary(ynn_binary_multiply, 2667, 3459, 2668);
  g->Convert(3684, 2669);
  g->Binary(ynn_binary_multiply, 2669, 3685, 2670);
  g->Matmul(2659, 2670, 2671, false, true);
  g->Binary(ynn_binary_divide, 2671, 3459, 2672);
  g->Unary(ynn_unary_round, 2672, 2673);
  g->Binary(ynn_binary_max, 2673, 3328, 2674);
  g->Binary(ynn_binary_min, 2674, 3384, 2675);
  g->Binary(ynn_binary_multiply, 2675, 3459, 2676);
  g->Polynomial(2676, 3239, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3239, 3240);
  g->Binary(ynn_binary_add, 3240, 2855, 3237);
  g->Binary(ynn_binary_multiply, 2676, 2853, 3238);
  g->Binary(ynn_binary_multiply, 3238, 3237, 2677);
  g->Binary(ynn_binary_multiply, 2668, 2677, 2678);
  g->Binary(ynn_binary_divide, 2678, 3441, 2679);
  g->Unary(ynn_unary_round, 2679, 2680);
  g->Binary(ynn_binary_max, 2680, 3328, 2681);
  g->Binary(ynn_binary_min, 2681, 3384, 2682);
  g->Binary(ynn_binary_multiply, 2682, 3441, 2683);
  g->Convert(3682, 2684);
  g->Binary(ynn_binary_multiply, 2684, 3683, 2685);
  g->Matmul(2683, 2685, 2686, false, true);
  g->Binary(ynn_binary_divide, 2686, 3446, 2687);
  g->Unary(ynn_unary_round, 2687, 2688);
  g->Binary(ynn_binary_max, 2688, 3328, 2690);
  g->Binary(ynn_binary_min, 2690, 3384, 2691);
  g->Binary(ynn_binary_multiply, 2691, 3446, 2692);
  g->Unary(ynn_unary_square, 2692, 2693);
  g->Reduce(ynn_reduce_sum, 2693, 3242, {2}, true);
  g->ShapeProduct(2693, 3241, {2});
  g->Binary(ynn_binary_divide, 3242, 3241, 2694);
  g->Binary(ynn_binary_add, 2694, 3400, 2695);
  g->Binary(ynn_binary_pow, 2695, 3424, 2696);
  g->Binary(ynn_binary_multiply, 2692, 2696, 2697);
  g->Convert(3693, 2698);
  g->Binary(ynn_binary_multiply, 2697, 2698, 2699);
  g->Binary(ynn_binary_add, 2645, 2699, 2700);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2701, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(2701, 2702, {1,0,256});
  g->Binary(ynn_binary_add, 2702, 3871, 2703);
  g->Binary(ynn_binary_multiply, 2703, 3296, 2704);
  g->Binary(ynn_binary_divide, 2700, 3390, 2705);
  g->Unary(ynn_unary_round, 2705, 2706);
  g->Binary(ynn_binary_max, 2706, 3328, 2707);
  g->Binary(ynn_binary_min, 2707, 3384, 2708);
  g->Binary(ynn_binary_multiply, 2708, 3390, 2709);
  g->Convert(3688, 2710);
  g->Binary(ynn_binary_multiply, 2710, 3689, 2711);
  g->Matmul(2709, 2711, 2712, false, true);
  g->Binary(ynn_binary_divide, 2712, 3467, 2713);
  g->Unary(ynn_unary_round, 2713, 2714);
  g->Binary(ynn_binary_max, 2714, 3328, 2715);
  g->Binary(ynn_binary_min, 2715, 3384, 2716);
  g->Binary(ynn_binary_multiply, 2716, 3467, 2717);
  g->Polynomial(2717, 3245, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3245, 3246);
  g->Binary(ynn_binary_add, 3246, 2855, 3243);
  g->Binary(ynn_binary_multiply, 2717, 2853, 3244);
  g->Binary(ynn_binary_multiply, 3244, 3243, 2718);
  g->Binary(ynn_binary_multiply, 2718, 2704, 2719);
  g->Binary(ynn_binary_divide, 2719, 3348, 2720);
  g->Unary(ynn_unary_round, 2720, 2721);
  g->Binary(ynn_binary_max, 2721, 3328, 2722);
  g->Binary(ynn_binary_min, 2722, 3384, 2723);
  g->Binary(ynn_binary_multiply, 2723, 3348, 2724);
  g->Convert(3690, 2725);
  g->Binary(ynn_binary_multiply, 2725, 3691, 2726);
  g->Matmul(2724, 2726, 2727, false, true);
  g->Binary(ynn_binary_divide, 2727, 3402, 2728);
  g->Unary(ynn_unary_round, 2728, 2729);
  g->Binary(ynn_binary_max, 2729, 3328, 2730);
  g->Binary(ynn_binary_min, 2730, 3384, 2731);
  g->Binary(ynn_binary_multiply, 2731, 3402, 2732);
  g->Unary(ynn_unary_square, 2732, 2733);
  g->Reduce(ynn_reduce_sum, 2733, 3248, {2}, true);
  g->ShapeProduct(2733, 3247, {2});
  g->Binary(ynn_binary_divide, 3248, 3247, 2734);
  g->Binary(ynn_binary_add, 2734, 3400, 2735);
  g->Binary(ynn_binary_pow, 2735, 3424, 2736);
  g->Binary(ynn_binary_multiply, 2732, 2736, 2737);
  g->Convert(3694, 2738);
  g->Binary(ynn_binary_multiply, 2737, 2738, 2739);
  g->Binary(ynn_binary_add, 2700, 2739, 2740);
  g->Convert(3681, 2741);
  g->Binary(ynn_binary_multiply, 2740, 2741, 2742);
}

// Scope: "Layer3"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3(Context& ctx) {
  BuildLayer3Attention(ctx);
  BuildLayer3Mlp(ctx);
  BuildLayer3PerLayerEmbedding(ctx);
}

// Scope: "Layer4 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2749, 3349, 2752);
  g->Unary(ynn_unary_round, 2752, 2753);
  g->Binary(ynn_binary_max, 2753, 3328, 2754);
  g->Binary(ynn_binary_min, 2754, 3384, 2755);
  g->Binary(ynn_binary_multiply, 2755, 3349, 2756);
  g->Convert(3723, 2757);
  g->Binary(ynn_binary_multiply, 2757, 3724, 2758);
  g->Matmul(2756, 2758, 2759, false, true);
  g->Binary(ynn_binary_divide, 2759, 3306, 2760);
  g->Unary(ynn_unary_round, 2760, 2761);
  g->Binary(ynn_binary_max, 2761, 3328, 2763);
  g->Binary(ynn_binary_min, 2763, 3384, 2764);
  g->Binary(ynn_binary_multiply, 2764, 3306, 2765);
  g->Reshape(2765, 2766, {1,0,1,512});
  g->Transpose(2766, 2767, {0,2,1,3});
  g->Unary(ynn_unary_square, 2767, 2768);
  g->Reduce(ynn_reduce_sum, 2768, 3252, {3}, true);
  g->ShapeProduct(2768, 3251, {3});
  g->Binary(ynn_binary_divide, 3252, 3251, 2769);
  g->Binary(ynn_binary_add, 2769, 3400, 2770);
  g->Binary(ynn_binary_pow, 2770, 3424, 2771);
  g->Binary(ynn_binary_multiply, 2767, 2771, 2772);
  g->Convert(3722, 2774);
  g->Binary(ynn_binary_multiply, 2772, 2774, 2775);
  g->Slice(2775, 2776, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2775, 2777, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2777, 2778);
  g->Concat({2778,2776}, 2779, 3);
  g->Binary(ynn_binary_multiply, 2775, 2651, 2780);
  g->Binary(ynn_binary_multiply, 2779, 2750, 2781);
  g->Binary(ynn_binary_add, 2780, 2781, 2782);
  g->Convert(3730, 2784);
  g->Binary(ynn_binary_multiply, 2784, 3731, 2785);
  g->Matmul(2756, 2785, 2786, false, true);
  g->Binary(ynn_binary_divide, 2786, 3306, 2787);
  g->Unary(ynn_unary_round, 2787, 2788);
  g->Binary(ynn_binary_max, 2788, 3328, 2789);
  g->Binary(ynn_binary_min, 2789, 3384, 2791);
  g->Binary(ynn_binary_multiply, 2791, 3306, 2792);
  g->Reshape(2792, 2793, {1,0,1,512});
  g->Transpose(2793, 2794, {0,2,1,3});
  g->Unary(ynn_unary_square, 2794, 2795);
  g->Reduce(ynn_reduce_sum, 2795, 3254, {3}, true);
  g->ShapeProduct(2795, 3253, {3});
  g->Binary(ynn_binary_divide, 3254, 3253, 2796);
  g->Binary(ynn_binary_add, 2796, 3400, 2797);
  g->Binary(ynn_binary_pow, 2797, 3424, 2798);
  g->Binary(ynn_binary_multiply, 2794, 2798, 2799);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2782, 2800, 0.0011563472216948867, 0);
  g->Append(3271, 2800, 3888, 2, s2, s1);
  g->View(3888, 3917, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3917, 2802, 0.0011563472216948867, 0);
  g->Quantize(2799, 2803, 0.01785714365541935, 0);
  g->Append(3286, 2803, 3903, 2, s2, s1);
  g->View(3903, 3931, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3931, 2804, 0.01785714365541935, 0);
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3728, 2806);
  g->Binary(ynn_binary_multiply, 2806, 3729, 2807);
  g->Matmul(2756, 2807, 2808, false, true);
  g->Binary(ynn_binary_divide, 2808, 3378, 2809);
  g->Unary(ynn_unary_round, 2809, 2810);
  g->Binary(ynn_binary_max, 2810, 3328, 2811);
  g->Binary(ynn_binary_min, 2811, 3384, 2812);
  g->Binary(ynn_binary_multiply, 2812, 3378, 2813);
  g->SplitDim(2813, 2815, 2, {8,512});
  g->Transpose(2815, 2816, {0,2,1,3});
  g->Unary(ynn_unary_square, 2816, 2817);
  g->Reduce(ynn_reduce_sum, 2817, 3256, {3}, true);
  g->ShapeProduct(2817, 3255, {3});
  g->Binary(ynn_binary_divide, 3256, 3255, 2818);
  g->Binary(ynn_binary_add, 2818, 3400, 2819);
  g->Binary(ynn_binary_pow, 2819, 3424, 2820);
  g->Binary(ynn_binary_multiply, 2816, 2820, 2821);
  g->Convert(3727, 2822);
  g->Binary(ynn_binary_multiply, 2821, 2822, 2823);
  g->Slice(2823, 2824, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2823, 2826, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2826, 2827);
  g->Concat({2827,2824}, 2828, 3);
  g->Binary(ynn_binary_multiply, 2823, 2651, 2829);
  g->Binary(ynn_binary_multiply, 2828, 2750, 2830);
  g->Binary(ynn_binary_add, 2829, 2830, 2831);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2831, 2802, 2832, false, true);
  g->Mask(2832, 3486, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 3486, 3260, {-1}, true);
  g->Binary(ynn_binary_subtract, 3486, 3260, 3257);
  g->Unary(ynn_unary_exp, 3257, 3258);
  g->Reduce(ynn_reduce_sum, 3258, 3261, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3261, 3259);
  g->Binary(ynn_binary_multiply, 3258, 3259, 2833);
  g->Matmul(2833, 2804, 2834, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2834, 2836, {0,2,1,3});
  g->FuseDims(2836, 2837, 2, 2);
  g->Binary(ynn_binary_divide, 2837, 3372, 2838);
  g->Unary(ynn_unary_round, 2838, 2839);
  g->Binary(ynn_binary_max, 2839, 3328, 2840);
  g->Binary(ynn_binary_min, 2840, 3384, 2841);
  g->Binary(ynn_binary_multiply, 2841, 3372, 2842);
  g->Convert(3725, 2843);
  g->Binary(ynn_binary_multiply, 2843, 3726, 2844);
  g->Matmul(2842, 2844, 2845, false, true);
  g->Binary(ynn_binary_divide, 2845, 3340, 4);
  g->Unary(ynn_unary_round, 4, 5);
  g->Binary(ynn_binary_max, 5, 3328, 6);
  g->Binary(ynn_binary_min, 6, 3384, 7);
  g->Binary(ynn_binary_multiply, 7, 3340, 8);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2742, 2743);
  g->Reduce(ynn_reduce_sum, 2743, 3250, {2}, true);
  g->ShapeProduct(2743, 3249, {2});
  g->Binary(ynn_binary_divide, 3250, 3249, 2744);
  g->Binary(ynn_binary_add, 2744, 3400, 2745);
  g->Binary(ynn_binary_pow, 2745, 3424, 2746);
  g->Binary(ynn_binary_multiply, 2742, 2746, 2747);
  g->Convert(3706, 2748);
  g->Binary(ynn_binary_multiply, 2747, 2748, 2749);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 8, 9);
  g->Reduce(ynn_reduce_sum, 9, 2847, {2}, true);
  g->ShapeProduct(9, 2846, {2});
  g->Binary(ynn_binary_divide, 2847, 2846, 10);
  g->Binary(ynn_binary_add, 10, 3400, 11);
  g->Binary(ynn_binary_pow, 11, 3424, 12);
  g->Binary(ynn_binary_multiply, 8, 12, 13);
  g->Convert(3718, 15);
  g->Binary(ynn_binary_multiply, 13, 15, 16);
  g->Binary(ynn_binary_add, 2742, 16, 17);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 17, 18);
  g->Reduce(ynn_reduce_sum, 18, 2851, {2}, true);
  g->ShapeProduct(18, 2850, {2});
  g->Binary(ynn_binary_divide, 2851, 2850, 19);
  g->Binary(ynn_binary_add, 19, 3400, 20);
  g->Binary(ynn_binary_pow, 20, 3424, 21);
  g->Binary(ynn_binary_multiply, 17, 21, 22);
  g->Convert(3721, 23);
  g->Binary(ynn_binary_multiply, 22, 23, 24);
  g->Binary(ynn_binary_divide, 24, 3334, 26);
  g->Unary(ynn_unary_round, 26, 27);
  g->Binary(ynn_binary_max, 27, 3328, 28);
  g->Binary(ynn_binary_min, 28, 3384, 29);
  g->Binary(ynn_binary_multiply, 29, 3334, 30);
  g->Convert(3712, 31);
  g->Binary(ynn_binary_multiply, 31, 3713, 32);
  g->Matmul(30, 32, 33, false, true);
  g->Binary(ynn_binary_divide, 33, 3450, 34);
  g->Unary(ynn_unary_round, 34, 35);
  g->Binary(ynn_binary_max, 35, 3328, 37);
  g->Binary(ynn_binary_min, 37, 3384, 38);
  g->Binary(ynn_binary_multiply, 38, 3450, 39);
  g->Convert(3710, 40);
  g->Binary(ynn_binary_multiply, 40, 3711, 41);
  g->Matmul(30, 41, 43, false, true);
  g->Binary(ynn_binary_divide, 43, 3450, 44);
  g->Unary(ynn_unary_round, 44, 45);
  g->Binary(ynn_binary_max, 45, 3328, 46);
  g->Binary(ynn_binary_min, 46, 3384, 47);
  g->Binary(ynn_binary_multiply, 47, 3450, 48);
  g->Polynomial(48, 2856, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2856, 2857);
  g->Binary(ynn_binary_add, 2857, 2855, 2852);
  g->Binary(ynn_binary_multiply, 48, 2853, 2854);
  g->Binary(ynn_binary_multiply, 2854, 2852, 49);
  g->Binary(ynn_binary_multiply, 39, 49, 50);
  g->Binary(ynn_binary_divide, 50, 3332, 51);
  g->Unary(ynn_unary_round, 51, 52);
  g->Binary(ynn_binary_max, 52, 3328, 54);
  g->Binary(ynn_binary_min, 54, 3384, 55);
  g->Binary(ynn_binary_multiply, 55, 3332, 56);
  g->Convert(3708, 57);
  g->Binary(ynn_binary_multiply, 57, 3709, 58);
  g->Matmul(56, 58, 59, false, true);
  g->Binary(ynn_binary_divide, 59, 3415, 60);
  g->Unary(ynn_unary_round, 60, 61);
  g->Binary(ynn_binary_max, 61, 3328, 62);
  g->Binary(ynn_binary_min, 62, 3384, 63);
  g->Binary(ynn_binary_multiply, 63, 3415, 65);
  g->Unary(ynn_unary_square, 65, 66);
  g->Reduce(ynn_reduce_sum, 66, 2859, {2}, true);
  g->ShapeProduct(66, 2858, {2});
  g->Binary(ynn_binary_divide, 2859, 2858, 67);
  g->Binary(ynn_binary_add, 67, 3400, 68);
  g->Binary(ynn_binary_pow, 68, 3424, 69);
  g->Binary(ynn_binary_multiply, 65, 69, 70);
  g->Convert(3719, 71);
  g->Binary(ynn_binary_multiply, 70, 71, 72);
  g->Binary(ynn_binary_add, 17, 72, 73);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 74, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(74, 76, {1,0,256});
  g->Binary(ynn_binary_add, 76, 3872, 77);
  g->Binary(ynn_binary_multiply, 77, 3296, 78);
  g->Binary(ynn_binary_divide, 73, 3460, 79);
  g->Unary(ynn_unary_round, 79, 80);
  g->Binary(ynn_binary_max, 80, 3328, 81);
  g->Binary(ynn_binary_min, 81, 3384, 82);
  g->Binary(ynn_binary_multiply, 82, 3460, 83);
  g->Convert(3714, 84);
  g->Binary(ynn_binary_multiply, 84, 3715, 85);
  g->Matmul(83, 85, 87, false, true);
  g->Binary(ynn_binary_divide, 87, 3300, 88);
  g->Unary(ynn_unary_round, 88, 89);
  g->Binary(ynn_binary_max, 89, 3328, 90);
  g->Binary(ynn_binary_min, 90, 3384, 91);
  g->Binary(ynn_binary_multiply, 91, 3300, 92);
  g->Polynomial(92, 2862, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2862, 2863);
  g->Binary(ynn_binary_add, 2863, 2855, 2860);
  g->Binary(ynn_binary_multiply, 92, 2853, 2861);
  g->Binary(ynn_binary_multiply, 2861, 2860, 93);
  g->Binary(ynn_binary_multiply, 93, 78, 94);
  g->Binary(ynn_binary_divide, 94, 3379, 95);
  g->Unary(ynn_unary_round, 95, 96);
  g->Binary(ynn_binary_max, 96, 3328, 98);
  g->Binary(ynn_binary_min, 98, 3384, 99);
  g->Binary(ynn_binary_multiply, 99, 3379, 100);
  g->Convert(3716, 101);
  g->Binary(ynn_binary_multiply, 101, 3717, 102);
  g->Matmul(100, 102, 103, false, true);
  g->Binary(ynn_binary_divide, 103, 3388, 104);
  g->Unary(ynn_unary_round, 104, 105);
  g->Binary(ynn_binary_max, 105, 3328, 106);
  g->Binary(ynn_binary_min, 106, 3384, 107);
  g->Binary(ynn_binary_multiply, 107, 3388, 110);
  g->Unary(ynn_unary_square, 110, 111);
  g->Reduce(ynn_reduce_sum, 111, 2865, {2}, true);
  g->ShapeProduct(111, 2864, {2});
  g->Binary(ynn_binary_divide, 2865, 2864, 112);
  g->Binary(ynn_binary_add, 112, 3400, 113);
  g->Binary(ynn_binary_pow, 113, 3424, 114);
  g->Binary(ynn_binary_multiply, 110, 114, 115);
  g->Convert(3720, 116);
  g->Binary(ynn_binary_multiply, 115, 116, 117);
  g->Binary(ynn_binary_add, 73, 117, 118);
  g->Convert(3707, 119);
  g->Binary(ynn_binary_multiply, 118, 119, 121);
}

// Scope: "Layer4"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4(Context& ctx) {
  BuildLayer4Attention(ctx);
  BuildLayer4Mlp(ctx);
  BuildLayer4PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
