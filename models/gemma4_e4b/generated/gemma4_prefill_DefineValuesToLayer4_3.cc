// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "DefineValues"
LAB_YNN_BUILDER_NOINLINE void BuildDefineValuesPart21(Context& ctx) {
  auto* g = ctx.g;
  const auto& weights = ctx.weights;
  g->Tensor(5376, "model.layers.12.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.12.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5377, "model.layers.13.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.13.input_layernorm.weight.f32", 10240));
  g->Tensor(5378, "model.layers.13.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.13.layer_scalar.f32", 4));
  g->Tensor(5379, "model.layers.13.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.13.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5380, "model.layers.13.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.13.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5381, "model.layers.13.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.13.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5382, "model.layers.13.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.13.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5383, "model.layers.13.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.13.per_layer_projection.weight.i8", 655360));
  g->Tensor(5384, "model.layers.13.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.13.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5385, "model.layers.13.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.13.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5386, "model.layers.13.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.13.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5387, "model.layers.13.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.13.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5388, "model.layers.13.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.13.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5389, "model.layers.13.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.13.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5390, "model.layers.13.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.13.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5391, "model.layers.13.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.13.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5392, "model.layers.13.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.13.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5393, "model.layers.13.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.13.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5394, "model.layers.14.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.14.input_layernorm.weight.f32", 10240));
  g->Tensor(5395, "model.layers.14.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.14.layer_scalar.f32", 4));
  g->Tensor(5396, "model.layers.14.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.14.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5397, "model.layers.14.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.14.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5398, "model.layers.14.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.14.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5399, "model.layers.14.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.14.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5400, "model.layers.14.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.14.per_layer_projection.weight.i8", 655360));
  g->Tensor(5401, "model.layers.14.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.14.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5402, "model.layers.14.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.14.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5403, "model.layers.14.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.14.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5404, "model.layers.14.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.14.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5405, "model.layers.14.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.14.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5406, "model.layers.14.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.14.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5407, "model.layers.14.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.14.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5408, "model.layers.14.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.14.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5409, "model.layers.14.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.14.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5410, "model.layers.14.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.14.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5411, "model.layers.15.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.15.input_layernorm.weight.f32", 10240));
  g->Tensor(5412, "model.layers.15.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.15.layer_scalar.f32", 4));
  g->Tensor(5413, "model.layers.15.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.15.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5414, "model.layers.15.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.15.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5415, "model.layers.15.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.15.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5416, "model.layers.15.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.15.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5417, "model.layers.15.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.15.per_layer_projection.weight.i8", 655360));
  g->Tensor(5418, "model.layers.15.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.15.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5419, "model.layers.15.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.15.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5420, "model.layers.15.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.15.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5421, "model.layers.15.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.15.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5422, "model.layers.15.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.15.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5423, "model.layers.15.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.15.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5424, "model.layers.15.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.15.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5425, "model.layers.15.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.15.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5426, "model.layers.15.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.15.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5427, "model.layers.15.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.15.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5428, "model.layers.16.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.16.input_layernorm.weight.f32", 10240));
  g->Tensor(5429, "model.layers.16.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.16.layer_scalar.f32", 4));
  g->Tensor(5430, "model.layers.16.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.16.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5431, "model.layers.16.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.16.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5432, "model.layers.16.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.16.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5433, "model.layers.16.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.16.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5434, "model.layers.16.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.16.per_layer_projection.weight.i8", 655360));
  g->Tensor(5435, "model.layers.16.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.16.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5436, "model.layers.16.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.16.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5437, "model.layers.16.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.16.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5438, "model.layers.16.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.16.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5439, "model.layers.16.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.16.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5440, "model.layers.16.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.16.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5441, "model.layers.16.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.16.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5442, "model.layers.16.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.16.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5443, "model.layers.16.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.16.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5444, "model.layers.16.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.16.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5445, "model.layers.17.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.17.input_layernorm.weight.f32", 10240));
  g->Tensor(5446, "model.layers.17.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.17.layer_scalar.f32", 4));
  g->Tensor(5447, "model.layers.17.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.17.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5448, "model.layers.17.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.17.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5449, "model.layers.17.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.17.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5450, "model.layers.17.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.17.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5451, "model.layers.17.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.17.per_layer_projection.weight.i8", 655360));
  g->Tensor(5452, "model.layers.17.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.17.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5453, "model.layers.17.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.17.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5454, "model.layers.17.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.17.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5455, "model.layers.17.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.17.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5456, "model.layers.17.self_attn.k_norm.weight", ynn_type_fp32, {512}, 0, weights("tensors/model.layers.17.self_attn.k_norm.weight.f32", 2048));
  g->Tensor(5457, "model.layers.17.self_attn.k_proj.weight", ynn_type_int4, {1024,2560}, 0, weights("tensors/model.layers.17.self_attn.k_proj.weight.i4", 1310720));
  g->Tensor(5458, "model.layers.17.self_attn.o_proj.weight", ynn_type_int4, {2560,4096}, 0, weights("tensors/model.layers.17.self_attn.o_proj.weight.i4", 5242880));
  g->Tensor(5459, "model.layers.17.self_attn.q_norm.weight", ynn_type_fp32, {512}, 0, weights("tensors/model.layers.17.self_attn.q_norm.weight.f32", 2048));
  g->Tensor(5460, "model.layers.17.self_attn.q_proj.weight", ynn_type_int4, {4096,2560}, 0, weights("tensors/model.layers.17.self_attn.q_proj.weight.i4", 5242880));
  g->Tensor(5461, "model.layers.17.self_attn.v_proj.weight", ynn_type_int4, {1024,2560}, 0, weights("tensors/model.layers.17.self_attn.v_proj.weight.i4", 1310720));
  g->Tensor(5462, "model.layers.18.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.18.input_layernorm.weight.f32", 10240));
  g->Tensor(5463, "model.layers.18.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.18.layer_scalar.f32", 4));
  g->Tensor(5464, "model.layers.18.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.18.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5465, "model.layers.18.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.18.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5466, "model.layers.18.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.18.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5467, "model.layers.18.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.18.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5468, "model.layers.18.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.18.per_layer_projection.weight.i8", 655360));
  g->Tensor(5469, "model.layers.18.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.18.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5470, "model.layers.18.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.18.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5471, "model.layers.18.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.18.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5472, "model.layers.18.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.18.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5473, "model.layers.18.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.18.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5474, "model.layers.18.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.18.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5475, "model.layers.18.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.18.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5476, "model.layers.18.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.18.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5477, "model.layers.18.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.18.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5478, "model.layers.18.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.18.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5479, "model.layers.19.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.19.input_layernorm.weight.f32", 10240));
  g->Tensor(5480, "model.layers.19.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.19.layer_scalar.f32", 4));
  g->Tensor(5481, "model.layers.19.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.19.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5482, "model.layers.19.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.19.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5483, "model.layers.19.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.19.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5484, "model.layers.19.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.19.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5485, "model.layers.19.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.19.per_layer_projection.weight.i8", 655360));
  g->Tensor(5486, "model.layers.19.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.19.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5487, "model.layers.19.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.19.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5488, "model.layers.19.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.19.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5489, "model.layers.19.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.19.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5490, "model.layers.19.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.19.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5491, "model.layers.19.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.19.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5492, "model.layers.19.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.19.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5493, "model.layers.19.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.19.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5494, "model.layers.19.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.19.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5495, "model.layers.19.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.19.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5496, "model.layers.2.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.2.input_layernorm.weight.f32", 10240));
  g->Tensor(5497, "model.layers.2.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.2.layer_scalar.f32", 4));
  g->Tensor(5498, "model.layers.2.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.2.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5499, "model.layers.2.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.2.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5500, "model.layers.2.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.2.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5501, "model.layers.2.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.2.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5502, "model.layers.2.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.2.per_layer_projection.weight.i8", 655360));
  g->Tensor(5503, "model.layers.2.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.2.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5504, "model.layers.2.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.2.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5505, "model.layers.2.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.2.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5506, "model.layers.2.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.2.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5507, "model.layers.2.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.2.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5508, "model.layers.2.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.2.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5509, "model.layers.2.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.2.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5510, "model.layers.2.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.2.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5511, "model.layers.2.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.2.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5512, "model.layers.2.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.2.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5513, "model.layers.20.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.20.input_layernorm.weight.f32", 10240));
  g->Tensor(5514, "model.layers.20.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.20.layer_scalar.f32", 4));
  g->Tensor(5515, "model.layers.20.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.20.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5516, "model.layers.20.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.20.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5517, "model.layers.20.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.20.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5518, "model.layers.20.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.20.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5519, "model.layers.20.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.20.per_layer_projection.weight.i8", 655360));
  g->Tensor(5520, "model.layers.20.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.20.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5521, "model.layers.20.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.20.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5522, "model.layers.20.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.20.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5523, "model.layers.20.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.20.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5524, "model.layers.20.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.20.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5525, "model.layers.20.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.20.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5526, "model.layers.20.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.20.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5527, "model.layers.20.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.20.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5528, "model.layers.20.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.20.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5529, "model.layers.20.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.20.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5530, "model.layers.21.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.21.input_layernorm.weight.f32", 10240));
  g->Tensor(5531, "model.layers.21.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.21.layer_scalar.f32", 4));
  g->Tensor(5532, "model.layers.21.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.21.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5533, "model.layers.21.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.21.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5534, "model.layers.21.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.21.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5535, "model.layers.21.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.21.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5536, "model.layers.21.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.21.per_layer_projection.weight.i8", 655360));
  g->Tensor(5537, "model.layers.21.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.21.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5538, "model.layers.21.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.21.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5539, "model.layers.21.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.21.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5540, "model.layers.21.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.21.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5541, "model.layers.21.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.21.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5542, "model.layers.21.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.21.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5543, "model.layers.21.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.21.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5544, "model.layers.21.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.21.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5545, "model.layers.21.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.21.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5546, "model.layers.21.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.21.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5547, "model.layers.22.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.22.input_layernorm.weight.f32", 10240));
  g->Tensor(5548, "model.layers.22.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.22.layer_scalar.f32", 4));
  g->Tensor(5549, "model.layers.22.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.22.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5550, "model.layers.22.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.22.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5551, "model.layers.22.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.22.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5552, "model.layers.22.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.22.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5553, "model.layers.22.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.22.per_layer_projection.weight.i8", 655360));
  g->Tensor(5554, "model.layers.22.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.22.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5555, "model.layers.22.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.22.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5556, "model.layers.22.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.22.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5557, "model.layers.22.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.22.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5558, "model.layers.22.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.22.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5559, "model.layers.22.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.22.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5560, "model.layers.22.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.22.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5561, "model.layers.22.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.22.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5562, "model.layers.22.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.22.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5563, "model.layers.22.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.22.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5564, "model.layers.23.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.23.input_layernorm.weight.f32", 10240));
  g->Tensor(5565, "model.layers.23.self_attn.k_norm.weight", ynn_type_fp32, {512}, 0, weights("tensors/model.layers.23.self_attn.k_norm.weight.f32", 2048));
  g->Tensor(5566, "model.layers.23.self_attn.k_proj.weight", ynn_type_int4, {1024,2560}, 0, weights("tensors/model.layers.23.self_attn.k_proj.weight.i4", 1310720));
  g->Tensor(5567, "model.layers.23.self_attn.v_proj.weight", ynn_type_int4, {1024,2560}, 0, weights("tensors/model.layers.23.self_attn.v_proj.weight.i4", 1310720));
  g->Tensor(5568, "model.layers.3.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.3.input_layernorm.weight.f32", 10240));
  g->Tensor(5569, "model.layers.3.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.3.layer_scalar.f32", 4));
  g->Tensor(5570, "model.layers.3.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.3.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5571, "model.layers.3.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.3.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5572, "model.layers.3.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.3.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5573, "model.layers.3.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.3.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5574, "model.layers.3.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.3.per_layer_projection.weight.i8", 655360));
  g->Tensor(5575, "model.layers.3.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.3.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5576, "model.layers.3.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.3.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5577, "model.layers.3.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.3.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5578, "model.layers.3.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.3.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5579, "model.layers.3.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.3.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5580, "model.layers.3.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.3.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5581, "model.layers.3.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.3.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5582, "model.layers.3.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.3.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5583, "model.layers.3.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.3.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5584, "model.layers.3.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.3.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5585, "model.layers.4.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.4.input_layernorm.weight.f32", 10240));
  g->Tensor(5586, "model.layers.4.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.4.layer_scalar.f32", 4));
  g->Tensor(5587, "model.layers.4.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.4.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5588, "model.layers.4.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.4.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5589, "model.layers.4.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.4.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5590, "model.layers.4.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.4.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5591, "model.layers.4.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.4.per_layer_projection.weight.i8", 655360));
  g->Tensor(5592, "model.layers.4.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.4.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5593, "model.layers.4.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.4.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5594, "model.layers.4.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.4.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5595, "model.layers.4.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.4.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5596, "model.layers.4.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.4.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5597, "model.layers.4.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.4.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5598, "model.layers.4.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.4.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5599, "model.layers.4.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.4.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5600, "model.layers.4.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.4.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5601, "model.layers.4.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.4.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5602, "model.layers.5.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.5.input_layernorm.weight.f32", 10240));
  g->Tensor(5603, "model.layers.5.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.5.layer_scalar.f32", 4));
  g->Tensor(5604, "model.layers.5.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.5.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5605, "model.layers.5.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.5.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5606, "model.layers.5.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.5.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5607, "model.layers.5.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.5.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5608, "model.layers.5.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.5.per_layer_projection.weight.i8", 655360));
  g->Tensor(5609, "model.layers.5.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.5.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5610, "model.layers.5.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.5.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5611, "model.layers.5.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.5.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5612, "model.layers.5.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.5.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5613, "model.layers.5.self_attn.k_norm.weight", ynn_type_fp32, {512}, 0, weights("tensors/model.layers.5.self_attn.k_norm.weight.f32", 2048));
  g->Tensor(5614, "model.layers.5.self_attn.k_proj.weight", ynn_type_int4, {1024,2560}, 0, weights("tensors/model.layers.5.self_attn.k_proj.weight.i4", 1310720));
  g->Tensor(5615, "model.layers.5.self_attn.o_proj.weight", ynn_type_int4, {2560,4096}, 0, weights("tensors/model.layers.5.self_attn.o_proj.weight.i4", 5242880));
  g->Tensor(5616, "model.layers.5.self_attn.q_norm.weight", ynn_type_fp32, {512}, 0, weights("tensors/model.layers.5.self_attn.q_norm.weight.f32", 2048));
  g->Tensor(5617, "model.layers.5.self_attn.q_proj.weight", ynn_type_int4, {4096,2560}, 0, weights("tensors/model.layers.5.self_attn.q_proj.weight.i4", 5242880));
  g->Tensor(5618, "model.layers.5.self_attn.v_proj.weight", ynn_type_int4, {1024,2560}, 0, weights("tensors/model.layers.5.self_attn.v_proj.weight.i4", 1310720));
  g->Tensor(5619, "model.layers.6.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.6.input_layernorm.weight.f32", 10240));
  g->Tensor(5620, "model.layers.6.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.6.layer_scalar.f32", 4));
  g->Tensor(5621, "model.layers.6.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.6.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5622, "model.layers.6.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.6.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5623, "model.layers.6.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.6.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5624, "model.layers.6.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.6.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5625, "model.layers.6.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.6.per_layer_projection.weight.i8", 655360));
  g->Tensor(5626, "model.layers.6.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.6.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5627, "model.layers.6.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.6.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5628, "model.layers.6.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.6.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5629, "model.layers.6.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.6.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5630, "model.layers.6.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.6.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5631, "model.layers.6.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.6.self_attn.k_proj.weight.i4", 655360));
}

// Scope: "DefineValues"
LAB_YNN_BUILDER_NOINLINE void BuildDefineValuesPart22(Context& ctx) {
  auto* g = ctx.g;
  const auto& weights = ctx.weights;
  g->Tensor(5632, "model.layers.6.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.6.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5633, "model.layers.6.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.6.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5634, "model.layers.6.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.6.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5635, "model.layers.6.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.6.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5636, "model.layers.7.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.7.input_layernorm.weight.f32", 10240));
  g->Tensor(5637, "model.layers.7.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.7.layer_scalar.f32", 4));
  g->Tensor(5638, "model.layers.7.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.7.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5639, "model.layers.7.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.7.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5640, "model.layers.7.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.7.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5641, "model.layers.7.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.7.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5642, "model.layers.7.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.7.per_layer_projection.weight.i8", 655360));
  g->Tensor(5643, "model.layers.7.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.7.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5644, "model.layers.7.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.7.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5645, "model.layers.7.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.7.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5646, "model.layers.7.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.7.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5647, "model.layers.7.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.7.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5648, "model.layers.7.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.7.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5649, "model.layers.7.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.7.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5650, "model.layers.7.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.7.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5651, "model.layers.7.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.7.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5652, "model.layers.7.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.7.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5653, "model.layers.8.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.8.input_layernorm.weight.f32", 10240));
  g->Tensor(5654, "model.layers.8.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.8.layer_scalar.f32", 4));
  g->Tensor(5655, "model.layers.8.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.8.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5656, "model.layers.8.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.8.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5657, "model.layers.8.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.8.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5658, "model.layers.8.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.8.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5659, "model.layers.8.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.8.per_layer_projection.weight.i8", 655360));
  g->Tensor(5660, "model.layers.8.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.8.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5661, "model.layers.8.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.8.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5662, "model.layers.8.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.8.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5663, "model.layers.8.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.8.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5664, "model.layers.8.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.8.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5665, "model.layers.8.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.8.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5666, "model.layers.8.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.8.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5667, "model.layers.8.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.8.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5668, "model.layers.8.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.8.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5669, "model.layers.8.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.8.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5670, "model.layers.9.input_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.9.input_layernorm.weight.f32", 10240));
  g->Tensor(5671, "model.layers.9.layer_scalar", ynn_type_fp32, {1}, 0, weights("tensors/model.layers.9.layer_scalar.f32", 4));
  g->Tensor(5672, "model.layers.9.mlp.down_proj.weight", ynn_type_int4, {2560,10240}, 0, weights("tensors/model.layers.9.mlp.down_proj.weight.i4", 13107200));
  g->Tensor(5673, "model.layers.9.mlp.gate_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.9.mlp.gate_proj.weight.i4", 13107200));
  g->Tensor(5674, "model.layers.9.mlp.up_proj.weight", ynn_type_int4, {10240,2560}, 0, weights("tensors/model.layers.9.mlp.up_proj.weight.i4", 13107200));
  g->Tensor(5675, "model.layers.9.per_layer_input_gate.weight", ynn_type_int8, {256,2560}, 0, weights("tensors/model.layers.9.per_layer_input_gate.weight.i8", 655360));
  g->Tensor(5676, "model.layers.9.per_layer_projection.weight", ynn_type_int8, {2560,256}, 0, weights("tensors/model.layers.9.per_layer_projection.weight.i8", 655360));
  g->Tensor(5677, "model.layers.9.post_attention_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.9.post_attention_layernorm.weight.f32", 10240));
  g->Tensor(5678, "model.layers.9.post_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.9.post_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5679, "model.layers.9.post_per_layer_input_norm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.9.post_per_layer_input_norm.weight.f32", 10240));
  g->Tensor(5680, "model.layers.9.pre_feedforward_layernorm.weight", ynn_type_fp32, {2560}, 0, weights("tensors/model.layers.9.pre_feedforward_layernorm.weight.f32", 10240));
  g->Tensor(5681, "model.layers.9.self_attn.k_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.9.self_attn.k_norm.weight.f32", 1024));
  g->Tensor(5682, "model.layers.9.self_attn.k_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.9.self_attn.k_proj.weight.i4", 655360));
  g->Tensor(5683, "model.layers.9.self_attn.o_proj.weight", ynn_type_int4, {2560,2048}, 0, weights("tensors/model.layers.9.self_attn.o_proj.weight.i4", 2621440));
  g->Tensor(5684, "model.layers.9.self_attn.q_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.layers.9.self_attn.q_norm.weight.f32", 1024));
  g->Tensor(5685, "model.layers.9.self_attn.q_proj.weight", ynn_type_int4, {2048,2560}, 0, weights("tensors/model.layers.9.self_attn.q_proj.weight.i4", 2621440));
  g->Tensor(5686, "model.layers.9.self_attn.v_proj.weight", ynn_type_int4, {512,2560}, 0, weights("tensors/model.layers.9.self_attn.v_proj.weight.i4", 655360));
  g->Tensor(5687, "model.per_layer_model_projection.weight", ynn_type_int8, {10752,2560}, 0, weights("tensors/model.per_layer_model_projection.weight.i8", 27525120));
  g->Tensor(5688, "model.per_layer_projection_norm.weight", ynn_type_fp32, {256}, 0, weights("tensors/model.per_layer_projection_norm.weight.f32", 1024));
  g->Tensor(5689, "per_layer_token_embedding_0", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5690, "per_layer_token_embedding_1", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5691, "per_layer_token_embedding_10", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5692, "per_layer_token_embedding_11", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5693, "per_layer_token_embedding_12", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5694, "per_layer_token_embedding_13", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5695, "per_layer_token_embedding_14", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5696, "per_layer_token_embedding_15", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5697, "per_layer_token_embedding_16", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5698, "per_layer_token_embedding_17", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5699, "per_layer_token_embedding_18", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5700, "per_layer_token_embedding_19", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5701, "per_layer_token_embedding_2", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5702, "per_layer_token_embedding_20", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5703, "per_layer_token_embedding_21", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5704, "per_layer_token_embedding_22", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5705, "per_layer_token_embedding_3", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5706, "per_layer_token_embedding_4", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5707, "per_layer_token_embedding_5", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5708, "per_layer_token_embedding_6", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5709, "per_layer_token_embedding_7", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5710, "per_layer_token_embedding_8", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5711, "per_layer_token_embedding_9", ynn_type_fp32, {1,0,256}, 1, nullptr);
  g->Tensor(5712, "positions", ynn_type_fp32, {1,1,0,1}, 1, nullptr);
  g->Tensor(5713, "updated_key_0", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5714, "updated_key_1", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5715, "updated_key_10", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5716, "updated_key_11", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5717, "updated_key_12", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5718, "updated_key_13", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5719, "updated_key_14", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5720, "updated_key_15", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5721, "updated_key_16", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5722, "updated_key_17", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5723, "updated_key_18", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5724, "updated_key_19", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5725, "updated_key_2", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5726, "updated_key_20", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5727, "updated_key_21", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5728, "updated_key_22", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5729, "updated_key_23", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5730, "updated_key_3", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5731, "updated_key_4", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5732, "updated_key_5", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5733, "updated_key_6", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5734, "updated_key_7", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5735, "updated_key_8", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5736, "updated_key_9", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5737, "updated_value_0", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5738, "updated_value_1", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5739, "updated_value_10", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5740, "updated_value_11", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5741, "updated_value_12", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5742, "updated_value_13", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5743, "updated_value_14", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5744, "updated_value_15", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5745, "updated_value_16", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5746, "updated_value_17", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5747, "updated_value_18", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5748, "updated_value_19", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5749, "updated_value_2", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5750, "updated_value_20", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5751, "updated_value_21", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5752, "updated_value_22", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5753, "updated_value_23", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5754, "updated_value_3", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5755, "updated_value_4", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5756, "updated_value_5", ynn_type_int8, {1,2,0,512}, 2, nullptr);
  g->Tensor(5757, "updated_value_6", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5758, "updated_value_7", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5759, "updated_value_8", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5760, "updated_value_9", ynn_type_int8, {1,2,0,256}, 2, nullptr);
  g->Tensor(5761, "view_key_0", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5762, "view_key_1", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5763, "view_key_10", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5764, "view_key_11", ynn_type_int8, {1,2,0,512}, 0, nullptr);
  g->Tensor(5765, "view_key_12", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5766, "view_key_13", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5767, "view_key_14", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5768, "view_key_15", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5769, "view_key_16", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5770, "view_key_17", ynn_type_int8, {1,2,0,512}, 0, nullptr);
  g->Tensor(5771, "view_key_18", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5772, "view_key_19", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5773, "view_key_2", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5774, "view_key_20", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5775, "view_key_21", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5776, "view_key_22", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5777, "view_key_3", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5778, "view_key_4", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5779, "view_key_5", ynn_type_int8, {1,2,0,512}, 0, nullptr);
  g->Tensor(5780, "view_key_6", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5781, "view_key_7", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5782, "view_key_8", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5783, "view_key_9", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5784, "view_value_0", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5785, "view_value_1", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5786, "view_value_10", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5787, "view_value_11", ynn_type_int8, {1,2,0,512}, 0, nullptr);
  g->Tensor(5788, "view_value_12", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5789, "view_value_13", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5790, "view_value_14", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5791, "view_value_15", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5792, "view_value_16", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5793, "view_value_17", ynn_type_int8, {1,2,0,512}, 0, nullptr);
  g->Tensor(5794, "view_value_18", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5795, "view_value_19", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5796, "view_value_2", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5797, "view_value_20", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5798, "view_value_21", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5799, "view_value_22", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5800, "view_value_3", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5801, "view_value_4", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5802, "view_value_5", ynn_type_int8, {1,2,0,512}, 0, nullptr);
  g->Tensor(5803, "view_value_6", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5804, "view_value_7", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5805, "view_value_8", ynn_type_int8, {1,2,0,256}, 0, nullptr);
  g->Tensor(5806, "view_value_9", ynn_type_int8, {1,2,0,256}, 0, nullptr);
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
  BuildDefineValuesPart16(ctx);
  BuildDefineValuesPart17(ctx);
  BuildDefineValuesPart18(ctx);
  BuildDefineValuesPart19(ctx);
  BuildDefineValuesPart20(ctx);
  BuildDefineValuesPart21(ctx);
  BuildDefineValuesPart22(ctx);
}

// Scope: "BindInvocation"
LAB_YNN_BUILDER_NOINLINE void BuildBindInvocation(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s3 = ctx.s3;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->InputShape(5239, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{2560})});
  g->InputShape(5712, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{1})});
  g->InputShape(5191, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5215, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5689, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5192, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5216, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5690, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5203, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5227, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5701, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5208, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5232, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5705, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5209, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5233, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5706, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5210, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5234, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5707, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5211, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5235, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5708, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5212, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5236, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5709, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5213, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5237, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5710, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5214, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5238, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5711, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5193, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5217, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5691, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5194, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5218, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5692, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5195, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5219, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5693, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5196, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5220, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5694, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5197, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5221, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5695, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5198, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5222, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5696, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5199, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5223, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5697, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5200, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5224, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5698, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5201, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5225, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5699, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5202, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5226, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5700, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5204, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5228, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5702, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5205, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5229, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5703, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5206, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5230, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{256})});
  g->InputShape(5704, {slinky::expr(int64_t{1}),s1,slinky::expr(int64_t{256})});
  g->InputShape(5207, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  g->InputShape(5231, {slinky::expr(int64_t{1}),slinky::expr(int64_t{2}),s3,slinky::expr(int64_t{512})});
  static_assert(lab_ynn::kResourceStateContract == 1, "incompatible resource-state adapter");
  g->Resource(5191, "cache_key_0", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005997600965201855],\"zero_point\":[0]}");
  g->Resource(5192, "cache_key_1", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.006118622608482838],\"zero_point\":[0]}");
  g->Resource(5193, "cache_key_10", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0057654301635921],\"zero_point\":[0]}");
  g->Resource(5194, "cache_key_11", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0011474735802039504],\"zero_point\":[0]}");
  g->Resource(5195, "cache_key_12", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005684707313776016],\"zero_point\":[0]}");
  g->Resource(5196, "cache_key_13", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0057707298547029495],\"zero_point\":[0]}");
  g->Resource(5197, "cache_key_14", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005712664220482111],\"zero_point\":[0]}");
  g->Resource(5198, "cache_key_15", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005989333149045706],\"zero_point\":[0]}");
  g->Resource(5199, "cache_key_16", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005929071456193924],\"zero_point\":[0]}");
  g->Resource(5200, "cache_key_17", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.001110153621993959],\"zero_point\":[0]}");
  g->Resource(5201, "cache_key_18", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.00573749840259552],\"zero_point\":[0]}");
  g->Resource(5202, "cache_key_19", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005869260523468256],\"zero_point\":[0]}");
  g->Resource(5203, "cache_key_2", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.006215503439307213],\"zero_point\":[0]}");
  g->Resource(5204, "cache_key_20", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005907459184527397],\"zero_point\":[0]}");
  g->Resource(5205, "cache_key_21", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0060269939713180065],\"zero_point\":[0]}");
  g->Resource(5206, "cache_key_22", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.0059552486054599285],\"zero_point\":[0]}");
  g->Resource(5207, "cache_key_23", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.001091228099539876],\"zero_point\":[0]}");
  g->Resource(5208, "cache_key_3", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005788442213088274],\"zero_point\":[0]}");
  g->Resource(5209, "cache_key_4", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.00596147496253252],\"zero_point\":[0]}");
  g->Resource(5210, "cache_key_5", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.001090860809199512],\"zero_point\":[0]}");
  g->Resource(5211, "cache_key_6", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005761673673987389],\"zero_point\":[0]}");
  g->Resource(5212, "cache_key_7", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.006011798977851868],\"zero_point\":[0]}");
  g->Resource(5213, "cache_key_8", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005679573863744736],\"zero_point\":[0]}");
  g->Resource(5214, "cache_key_9", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.005719248205423355],\"zero_point\":[0]}");
  g->Resource(5215, "cache_value_0", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5216, "cache_value_1", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5217, "cache_value_10", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5218, "cache_value_11", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->Resource(5219, "cache_value_12", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5220, "cache_value_13", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5221, "cache_value_14", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5222, "cache_value_15", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5223, "cache_value_16", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5224, "cache_value_17", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->Resource(5225, "cache_value_18", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5226, "cache_value_19", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5227, "cache_value_2", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5228, "cache_value_20", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5229, "cache_value_21", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5230, "cache_value_22", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5231, "cache_value_23", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->Resource(5232, "cache_value_3", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5233, "cache_value_4", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5234, "cache_value_5", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.01785714365541935],\"zero_point\":[0]}");
  g->Resource(5235, "cache_value_6", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5236, "cache_value_7", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5237, "cache_value_8", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->Resource(5238, "cache_value_9", 2, s2, "{\"axis\":0,\"dtype\":\"i8\",\"scale\":[0.047244105488061905],\"zero_point\":[0]}");
  g->RequireBounds(slinky::expr(int64_t{1}) <= s3, "symbol 3 lower bound");
  g->RequireBounds(s3 <= slinky::expr(int64_t{32768}), "symbol 3 upper bound");
  g->RequireBounds(slinky::expr(int64_t{1}) <= s1, "symbol 1 lower bound");
  g->RequireBounds(s1 <= slinky::expr(int64_t{128}), "symbol 1 upper bound");
  g->RequireBounds(slinky::expr(int64_t{0}) <= s2, "symbol 2 lower bound");
  g->RequireBounds(s2 <= slinky::expr(int64_t{32768}), "symbol 2 upper bound");
  g->Require((slinky::expr(int64_t{256}) * slinky::max(slinky::expr(int64_t{1}), s3)) <= (slinky::expr(int64_t{256}) * slinky::max(slinky::expr(int64_t{1}), s3)), "overlapping resource strides");
  g->Require((slinky::expr(int64_t{2}) * slinky::expr(int64_t{256}) * slinky::max(slinky::expr(int64_t{1}), s3)) <= (slinky::expr(int64_t{2}) * slinky::expr(int64_t{256}) * slinky::max(slinky::expr(int64_t{1}), s3)), "overlapping resource strides");
  g->Require(s2 <= s3, "resource logical extent exceeds capacity");
  g->Require((slinky::expr(int64_t{512}) * slinky::max(slinky::expr(int64_t{1}), s3)) <= (slinky::expr(int64_t{512}) * slinky::max(slinky::expr(int64_t{1}), s3)), "overlapping resource strides");
  g->Require((slinky::expr(int64_t{2}) * slinky::expr(int64_t{512}) * slinky::max(slinky::expr(int64_t{1}), s3)) <= (slinky::expr(int64_t{2}) * slinky::expr(int64_t{512}) * slinky::max(slinky::expr(int64_t{1}), s3)), "overlapping resource strides");
  g->Require(s1 <= s1, "slice bounds");
  g->Require((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) <= s3, "append capacity");
  g->Require(slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))) <= (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)), "view interval");
  g->Require((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) <= (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)), "view reads uninitialized history");
  g->Require(((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) + (slinky::expr(int64_t{-1}) * slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2)))) + slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2)))) <= (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)), "consumer reads uninitialized resource capacity");
  g->Require(slinky::expr(int64_t{0}) <= ((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) + (slinky::expr(int64_t{-1}) * slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))))), "slice length");
  g->Require(((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) + (slinky::expr(int64_t{-1}) * slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))))) <= ((slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)) + (slinky::expr(int64_t{-1}) * slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))))), "slice bounds");
}

// Scope: "Embedding"
LAB_YNN_BUILDER_NOINLINE void BuildEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_multiply, 5239, 5242, 0);
}

// Scope: "RopeTables"
LAB_YNN_BUILDER_NOINLINE void BuildRopeTables(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_multiply, 5712, 5244, 1);
  g->Unary(ynn_unary_cos, 1, 1036);
  g->Unary(ynn_unary_sin, 1, 2079);
  g->Concat({1036,1036}, 2394, 3);
  g->Concat({2079,2079}, 2498, 3);
  g->Binary(ynn_binary_multiply, 5712, 5243, 2601);
  g->Unary(ynn_unary_cos, 2601, 2704);
  g->Unary(ynn_unary_sin, 2601, 2806);
  g->Concat({2704,2704}, 2909, 3);
  g->Concat({2806,2806}, 2, 3);
}

// Scope: "InputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildInputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(0, 104, 0.0393700897693634, 0);
  g->Transpose(5687, 3120, {1,0});
  g->Binary(ynn_binary_multiply, 3117, 3119, 3115);
  g->Dot(104, 3120, YNN_INVALID_VALUE_ID, 3114, 1);
  g->DequantizeTensor(3114, YNN_INVALID_VALUE_ID, 3115, 3116);
  g->QuantizeTensor(3116, 5190, 3118, 206);
  g->Dequantize(206, 310, 0.001953135011717677, 0);
  g->SplitDim(310, 418, 2, {42,256});
}

// Scope: "Layer0 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1037, 1145, 0.5009142160415649, 0);
  g->Transpose(5304, 3580, {1,0});
  g->Binary(ynn_binary_multiply, 3577, 3579, 3575);
  g->Dot(1145, 3580, YNN_INVALID_VALUE_ID, 3574, 1);
  g->DequantizeTensor(3574, YNN_INVALID_VALUE_ID, 3575, 3576);
  g->QuantizeTensor(3576, 5190, 3578, 1246);
  g->Dequantize(1246, 1348, 1.3228346109390259, 0);
  g->SplitDim(1348, 1454, 2, {2,256});
  g->Transpose(1454, 1559, {0,2,1,3});
  g->Unary(ynn_unary_square, 1559, 1661);
  g->Reduce(ynn_reduce_sum, 1661, 4841, {3}, true);
  g->ShapeProduct(1661, 4840, {3});
  g->Binary(ynn_binary_divide, 4841, 4840, 1766);
  g->Binary(ynn_binary_add, 1766, 5241, 1873);
  g->Unary(ynn_unary_rsqrt, 1873, 1976);
  g->Binary(ynn_binary_multiply, 1559, 1976, 2080);
  g->Binary(ynn_binary_multiply, 2080, 5303, 2184);
  g->Slice(2184, 2291, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2184, 2323, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2323, 2332);
  g->Concat({2332,2291}, 2343, 3);
  g->Binary(ynn_binary_multiply, 2184, 2394, 2353);
  g->Binary(ynn_binary_multiply, 2343, 2498, 2363);
  g->Binary(ynn_binary_add, 2353, 2363, 2374);
  g->Transpose(5308, 4097, {1,0});
  g->Binary(ynn_binary_multiply, 3577, 4096, 4094);
  g->Dot(1145, 4097, YNN_INVALID_VALUE_ID, 4093, 1);
  g->DequantizeTensor(4093, YNN_INVALID_VALUE_ID, 4094, 4095);
  g->QuantizeTensor(4095, 5190, 3578, 2395);
  g->Dequantize(2395, 2406, 1.3228346109390259, 0);
  g->SplitDim(2406, 2417, 2, {2,256});
  g->Transpose(2417, 2428, {0,2,1,3});
  g->Unary(ynn_unary_square, 2428, 2439);
  g->Reduce(ynn_reduce_sum, 2439, 5031, {3}, true);
  g->ShapeProduct(2439, 5030, {3});
  g->Binary(ynn_binary_divide, 5031, 5030, 2450);
  g->Binary(ynn_binary_add, 2450, 5241, 2460);
  g->Unary(ynn_unary_rsqrt, 2460, 2466);
  g->Binary(ynn_binary_multiply, 2428, 2466, 2477);
}

// Scope: "Layer0 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2374, 2488, 0.005997600965201855, 0);
  g->Append(5191, 2488, 5713, 2, s2, s1);
  g->View(5713, 5761, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2477, 2518, 0.047244105488061905, 0);
  g->Append(5215, 2518, 5737, 2, s2, s1);
  g->View(5737, 5784, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer0 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5307, 4174, {1,0});
  g->Binary(ynn_binary_multiply, 3577, 4173, 4170);
  g->Dot(1145, 4174, YNN_INVALID_VALUE_ID, 4169, 1);
  g->DequantizeTensor(4169, YNN_INVALID_VALUE_ID, 4170, 4171);
  g->QuantizeTensor(4171, 5190, 4172, 2558);
  g->Dequantize(2558, 2569, 0.9803149700164795, 0);
  g->SplitDim(2569, 2580, 2, {8,256});
  g->Transpose(2580, 2591, {0,2,1,3});
  g->Unary(ynn_unary_square, 2591, 2602);
  g->Reduce(ynn_reduce_sum, 2602, 5071, {3}, true);
  g->ShapeProduct(2602, 5070, {3});
  g->Binary(ynn_binary_divide, 5071, 5070, 2608);
  g->Binary(ynn_binary_add, 2608, 5241, 2619);
  g->Unary(ynn_unary_rsqrt, 2619, 2630);
  g->Binary(ynn_binary_multiply, 2591, 2630, 2639);
  g->Binary(ynn_binary_multiply, 2639, 5306, 2650);
  g->Slice(2650, 2661, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2650, 2671, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2671, 2682);
  g->Concat({2682,2661}, 2693, 3);
  g->Binary(ynn_binary_multiply, 2650, 2394, 2705);
  g->Binary(ynn_binary_multiply, 2693, 2498, 2716);
  g->Binary(ynn_binary_add, 2705, 2716, 2727);
}

// Scope: "Layer0 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5761, 2737, 0.005997600965201855, 0);
  g->Dequantize(5784, 2748, 0.047244105488061905, 0);
  g->Slice(2727, 2754, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2737, 2765, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2748, 2775, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2754, 2765, 2785, false, true);
  g->Mask(2785, 5246, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5246, 5127, {-1}, true);
  g->Binary(ynn_binary_subtract, 5246, 5127, 5124);
  g->Unary(ynn_unary_exp, 5124, 5125);
  g->Reduce(ynn_reduce_sum, 5125, 5128, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5128, 5126);
  g->Binary(ynn_binary_multiply, 5125, 5126, 2807);
  g->Matmul(2807, 2775, 2817, false, false);
  g->Slice(2727, 2828, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2737, 2839, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2748, 2850, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2828, 2839, 2861, false, true);
  g->Mask(2861, 5247, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5247, 5150, {-1}, true);
  g->Binary(ynn_binary_subtract, 5247, 5150, 5147);
  g->Unary(ynn_unary_exp, 5147, 5148);
  g->Reduce(ynn_reduce_sum, 5148, 5151, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5151, 5149);
  g->Binary(ynn_binary_multiply, 5148, 5149, 2881);
  g->Matmul(2881, 2850, 2890, false, false);
  g->Concat({2817,2890}, 2898, 1);
}

// Scope: "Layer0 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2898, 2910, {0,2,1,3});
  g->FuseDims(2910, 2920, 2, 2);
  g->Quantize(2920, 2930, 0.030880915001034737, 0);
  g->Transpose(5305, 4315, {1,0});
  g->Binary(ynn_binary_multiply, 4312, 4314, 4310);
  g->Dot(2930, 4315, YNN_INVALID_VALUE_ID, 4309, 1);
  g->DequantizeTensor(4309, YNN_INVALID_VALUE_ID, 4310, 4311);
  g->QuantizeTensor(4311, 5190, 4313, 2941);
  g->Dequantize(2941, 2951, 0.12185609340667725, 0);
}

// Scope: "Layer0 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 0, 520);
  g->Reduce(ynn_reduce_sum, 520, 4528, {2}, true);
  g->ShapeProduct(520, 4527, {2});
  g->Binary(ynn_binary_divide, 4528, 4527, 624);
  g->Binary(ynn_binary_add, 624, 5241, 732);
  g->Unary(ynn_unary_rsqrt, 732, 834);
  g->Binary(ynn_binary_multiply, 0, 834, 935);
  g->Binary(ynn_binary_multiply, 935, 5292, 1037);
  BuildLayer0AttentionKvProjection(ctx);
  BuildLayer0AttentionCacheUpdate(ctx);
  BuildLayer0AttentionQueryProjection(ctx);
  BuildLayer0AttentionSdpa(ctx);
  BuildLayer0AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2951, 2962);
  g->Reduce(ynn_reduce_sum, 2962, 5179, {2}, true);
  g->ShapeProduct(2962, 5178, {2});
  g->Binary(ynn_binary_divide, 5179, 5178, 2973);
  g->Binary(ynn_binary_add, 2973, 5241, 2984);
  g->Unary(ynn_unary_rsqrt, 2984, 2995);
  g->Binary(ynn_binary_multiply, 2951, 2995, 3006);
  g->Binary(ynn_binary_multiply, 3006, 5299, 3);
  g->Binary(ynn_binary_add, 3, 0, 13);
}

// Scope: "Layer0 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 13, 21);
  g->Reduce(ynn_reduce_sum, 21, 4359, {2}, true);
  g->ShapeProduct(21, 4358, {2});
  g->Binary(ynn_binary_divide, 4359, 4358, 30);
  g->Binary(ynn_binary_add, 30, 5241, 41);
  g->Unary(ynn_unary_rsqrt, 41, 51);
  g->Binary(ynn_binary_multiply, 13, 51, 61);
  g->Binary(ynn_binary_multiply, 61, 5302, 72);
  g->Quantize(72, 82, 0.05929328873753548, 0);
  g->Transpose(5296, 3062, {1,0});
  g->Binary(ynn_binary_multiply, 3059, 3061, 3057);
  g->Dot(82, 3062, YNN_INVALID_VALUE_ID, 3056, 1);
  g->DequantizeTensor(3056, YNN_INVALID_VALUE_ID, 3057, 3058);
  g->QuantizeTensor(3058, 5190, 3060, 93);
  g->Dequantize(93, 105, 0.05561024695634842, 0);
  g->Transpose(5295, 3081, {1,0});
  g->Binary(ynn_binary_multiply, 3059, 3080, 3078);
  g->Dot(82, 3081, YNN_INVALID_VALUE_ID, 3077, 1);
  g->DequantizeTensor(3077, YNN_INVALID_VALUE_ID, 3078, 3079);
  g->QuantizeTensor(3079, 5190, 3060, 126);
  g->Dequantize(126, 137, 0.05561024695634842, 0);
  g->Polynomial(137, 4396, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4396, 4397);
  g->Binary(ynn_binary_add, 4397, 4364, 4394);
  g->Binary(ynn_binary_multiply, 137, 4376, 4395);
  g->Binary(ynn_binary_multiply, 4395, 4394, 148);
  g->Binary(ynn_binary_multiply, 105, 148, 158);
  g->Quantize(158, 164, 0.2618110179901123, 0);
  g->Transpose(5294, 3106, {1,0});
  g->Binary(ynn_binary_multiply, 3103, 3105, 3101);
  g->Dot(164, 3106, YNN_INVALID_VALUE_ID, 3100, 1);
  g->DequantizeTensor(3100, YNN_INVALID_VALUE_ID, 3101, 3102);
  g->QuantizeTensor(3102, 5190, 3104, 175);
  g->Dequantize(175, 186, 0.1098586767911911, 0);
  g->Unary(ynn_unary_square, 186, 196);
  g->Reduce(ynn_reduce_sum, 196, 4413, {2}, true);
  g->ShapeProduct(196, 4412, {2});
  g->Binary(ynn_binary_divide, 4413, 4412, 207);
  g->Binary(ynn_binary_add, 207, 5241, 218);
  g->Unary(ynn_unary_rsqrt, 218, 228);
  g->Binary(ynn_binary_multiply, 186, 228, 239);
  g->Binary(ynn_binary_multiply, 239, 5300, 250);
  g->Binary(ynn_binary_add, 250, 13, 261);
}

// Scope: "Layer0 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 272, {0,0,0,0}, {-1,-1,1,-1});
  g->Reshape(272, 283, {1,0,256});
  g->Unary(ynn_unary_square, 283, 294);
  g->Reduce(ynn_reduce_sum, 294, 4439, {2}, true);
  g->ShapeProduct(294, 4438, {2});
  g->Binary(ynn_binary_divide, 4439, 4438, 304);
  g->Binary(ynn_binary_add, 304, 5241, 311);
  g->Unary(ynn_unary_rsqrt, 311, 322);
  g->Binary(ynn_binary_multiply, 283, 322, 333);
  g->Binary(ynn_binary_multiply, 333, 5688, 342);
  g->Binary(ynn_binary_multiply, 5689, 5245, 353);
  g->Binary(ynn_binary_add, 342, 353, 364);
  g->Binary(ynn_binary_multiply, 364, 5240, 374);
  g->Quantize(261, 385, 1.4798848628997803, 0);
  g->Transpose(5297, 3203, {1,0});
  g->Binary(ynn_binary_multiply, 3200, 3202, 3198);
  g->Dot(385, 3203, YNN_INVALID_VALUE_ID, 3197, 1);
  g->DequantizeTensor(3197, YNN_INVALID_VALUE_ID, 3198, 3199);
  g->QuantizeTensor(3199, 5190, 3201, 396);
  g->Dequantize(396, 407, 0.028174221515655518, 0);
  g->Polynomial(407, 4474, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4474, 4475);
  g->Binary(ynn_binary_add, 4475, 4364, 4472);
  g->Binary(ynn_binary_multiply, 407, 4376, 4473);
  g->Binary(ynn_binary_multiply, 4473, 4472, 419);
  g->Binary(ynn_binary_multiply, 419, 374, 430);
  g->Quantize(430, 440, 0.059793319553136826, 0);
  g->Transpose(5298, 3236, {1,0});
  g->Binary(ynn_binary_multiply, 3233, 3235, 3231);
  g->Dot(440, 3236, YNN_INVALID_VALUE_ID, 3230, 1);
  g->DequantizeTensor(3230, YNN_INVALID_VALUE_ID, 3231, 3232);
  g->QuantizeTensor(3232, 5190, 3234, 451);
  g->Dequantize(451, 457, 0.05135427787899971, 0);
  g->Unary(ynn_unary_square, 457, 468);
  g->Reduce(ynn_reduce_sum, 468, 4483, {2}, true);
  g->ShapeProduct(468, 4482, {2});
  g->Binary(ynn_binary_divide, 4483, 4482, 478);
  g->Binary(ynn_binary_add, 478, 5241, 488);
  g->Unary(ynn_unary_rsqrt, 488, 499);
  g->Binary(ynn_binary_multiply, 457, 499, 510);
  g->Binary(ynn_binary_multiply, 510, 5301, 521);
  g->Binary(ynn_binary_add, 261, 521, 532);
  g->Binary(ynn_binary_multiply, 532, 5293, 543);
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
  g->Quantize(603, 614, 0.7235185503959656, 0);
  g->Transpose(5321, 3306, {1,0});
  g->Binary(ynn_binary_multiply, 3303, 3305, 3301);
  g->Dot(614, 3306, YNN_INVALID_VALUE_ID, 3300, 1);
  g->DequantizeTensor(3300, YNN_INVALID_VALUE_ID, 3301, 3302);
  g->QuantizeTensor(3302, 5190, 3304, 625);
  g->Dequantize(625, 635, 0.3779527544975281, 0);
  g->SplitDim(635, 646, 2, {2,256});
  g->Transpose(646, 656, {0,2,1,3});
  g->Unary(ynn_unary_square, 656, 667);
  g->Reduce(ynn_reduce_sum, 667, 4547, {3}, true);
  g->ShapeProduct(667, 4546, {3});
  g->Binary(ynn_binary_divide, 4547, 4546, 678);
  g->Binary(ynn_binary_add, 678, 5241, 689);
  g->Unary(ynn_unary_rsqrt, 689, 700);
  g->Binary(ynn_binary_multiply, 656, 700, 711);
  g->Binary(ynn_binary_multiply, 711, 5320, 722);
  g->Slice(722, 733, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(722, 741, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 741, 750);
  g->Concat({750,733}, 761, 3);
  g->Binary(ynn_binary_multiply, 722, 2394, 771);
  g->Binary(ynn_binary_multiply, 761, 2498, 781);
  g->Binary(ynn_binary_add, 771, 781, 792);
  g->Transpose(5325, 3395, {1,0});
  g->Binary(ynn_binary_multiply, 3303, 3394, 3392);
  g->Dot(614, 3395, YNN_INVALID_VALUE_ID, 3391, 1);
  g->DequantizeTensor(3391, YNN_INVALID_VALUE_ID, 3392, 3393);
  g->QuantizeTensor(3393, 5190, 3304, 812);
  g->Dequantize(812, 823, 0.3779527544975281, 0);
  g->SplitDim(823, 835, 2, {2,256});
  g->Transpose(835, 846, {0,2,1,3});
  g->Unary(ynn_unary_square, 846, 857);
  g->Reduce(ynn_reduce_sum, 857, 4595, {3}, true);
  g->ShapeProduct(857, 4594, {3});
  g->Binary(ynn_binary_divide, 4595, 4594, 868);
  g->Binary(ynn_binary_add, 868, 5241, 878);
  g->Unary(ynn_unary_rsqrt, 878, 884);
  g->Binary(ynn_binary_multiply, 846, 884, 895);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(792, 906, 0.006118622608482838, 0);
  g->Append(5192, 906, 5714, 2, s2, s1);
  g->View(5714, 5762, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(895, 936, 0.047244105488061905, 0);
  g->Append(5216, 936, 5738, 2, s2, s1);
  g->View(5738, 5785, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5324, 3472, {1,0});
  g->Binary(ynn_binary_multiply, 3303, 3471, 3468);
  g->Dot(614, 3472, YNN_INVALID_VALUE_ID, 3467, 1);
  g->DequantizeTensor(3467, YNN_INVALID_VALUE_ID, 3468, 3469);
  g->QuantizeTensor(3469, 5190, 3470, 976);
  g->Dequantize(976, 987, 0.3385826647281647, 0);
  g->SplitDim(987, 998, 2, {8,256});
  g->Transpose(998, 1009, {0,2,1,3});
  g->Unary(ynn_unary_square, 1009, 1019);
  g->Reduce(ynn_reduce_sum, 1019, 4635, {3}, true);
  g->ShapeProduct(1019, 4634, {3});
  g->Binary(ynn_binary_divide, 4635, 4634, 1025);
  g->Binary(ynn_binary_add, 1025, 5241, 1038);
  g->Unary(ynn_unary_rsqrt, 1038, 1049);
  g->Binary(ynn_binary_multiply, 1009, 1049, 1058);
  g->Binary(ynn_binary_multiply, 1058, 5323, 1069);
  g->Slice(1069, 1080, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1069, 1090, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1090, 1101);
  g->Concat({1101,1080}, 1112, 3);
  g->Binary(ynn_binary_multiply, 1069, 2394, 1123);
  g->Binary(ynn_binary_multiply, 1112, 2498, 1134);
  g->Binary(ynn_binary_add, 1123, 1134, 1146);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5762, 1156, 0.006118622608482838, 0);
  g->Dequantize(5785, 1167, 0.047244105488061905, 0);
  g->Slice(1146, 1173, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1156, 1184, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1167, 1194, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1173, 1184, 1204, false, true);
  g->Mask(1204, 5268, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5268, 4691, {-1}, true);
  g->Binary(ynn_binary_subtract, 5268, 4691, 4688);
  g->Unary(ynn_unary_exp, 4688, 4689);
  g->Reduce(ynn_reduce_sum, 4689, 4692, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4692, 4690);
  g->Binary(ynn_binary_multiply, 4689, 4690, 1225);
  g->Matmul(1225, 1194, 1235, false, false);
  g->Slice(1146, 1247, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1156, 1258, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1167, 1269, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1247, 1258, 1280, false, true);
  g->Mask(1280, 5269, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5269, 4714, {-1}, true);
  g->Binary(ynn_binary_subtract, 5269, 4714, 4711);
  g->Unary(ynn_unary_exp, 4711, 4712);
  g->Reduce(ynn_reduce_sum, 4712, 4715, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4715, 4713);
  g->Binary(ynn_binary_multiply, 4712, 4713, 1300);
  g->Matmul(1300, 1269, 1309, false, false);
  g->Concat({1235,1309}, 1317, 1);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1317, 1328, {0,2,1,3});
  g->FuseDims(1328, 1338, 2, 2);
  g->Quantize(1338, 1349, 0.026943907141685486, 0);
  g->Transpose(5322, 3626, {1,0});
  g->Binary(ynn_binary_multiply, 3623, 3625, 3621);
  g->Dot(1349, 3626, YNN_INVALID_VALUE_ID, 3620, 1);
  g->DequantizeTensor(3620, YNN_INVALID_VALUE_ID, 3621, 3622);
  g->QuantizeTensor(3622, 5190, 3624, 1360);
  g->Dequantize(1360, 1370, 0.4272114038467407, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 543, 554);
  g->Reduce(ynn_reduce_sum, 554, 4515, {2}, true);
  g->ShapeProduct(554, 4514, {2});
  g->Binary(ynn_binary_divide, 4515, 4514, 565);
  g->Binary(ynn_binary_add, 565, 5241, 576);
  g->Unary(ynn_unary_rsqrt, 576, 586);
  g->Binary(ynn_binary_multiply, 543, 586, 595);
  g->Binary(ynn_binary_multiply, 595, 5309, 603);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1370, 1381);
  g->Reduce(ynn_reduce_sum, 1381, 4743, {2}, true);
  g->ShapeProduct(1381, 4742, {2});
  g->Binary(ynn_binary_divide, 4743, 4742, 1392);
  g->Binary(ynn_binary_add, 1392, 5241, 1403);
  g->Unary(ynn_unary_rsqrt, 1403, 1414);
  g->Binary(ynn_binary_multiply, 1370, 1414, 1425);
  g->Binary(ynn_binary_multiply, 1425, 5316, 1436);
  g->Binary(ynn_binary_add, 1436, 543, 1446);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1446, 1455);
  g->Reduce(ynn_reduce_sum, 1455, 4759, {2}, true);
  g->ShapeProduct(1455, 4758, {2});
  g->Binary(ynn_binary_divide, 4759, 4758, 1464);
  g->Binary(ynn_binary_add, 1464, 5241, 1475);
  g->Unary(ynn_unary_rsqrt, 1475, 1485);
  g->Binary(ynn_binary_multiply, 1446, 1485, 1495);
  g->Binary(ynn_binary_multiply, 1495, 5319, 1506);
  g->Quantize(1506, 1516, 0.10782907903194427, 0);
  g->Transpose(5313, 3710, {1,0});
  g->Binary(ynn_binary_multiply, 3707, 3709, 3705);
  g->Dot(1516, 3710, YNN_INVALID_VALUE_ID, 3704, 1);
  g->DequantizeTensor(3704, YNN_INVALID_VALUE_ID, 3705, 3706);
  g->QuantizeTensor(3706, 5190, 3708, 1527);
  g->Dequantize(1527, 1538, 0.11811024695634842, 0);
  g->Transpose(5312, 3729, {1,0});
  g->Binary(ynn_binary_multiply, 3707, 3728, 3726);
  g->Dot(1516, 3729, YNN_INVALID_VALUE_ID, 3725, 1);
  g->DequantizeTensor(3725, YNN_INVALID_VALUE_ID, 3726, 3727);
  g->QuantizeTensor(3727, 5190, 3708, 1560);
  g->Dequantize(1560, 1571, 0.11811024695634842, 0);
  g->Polynomial(1571, 4794, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4794, 4795);
  g->Binary(ynn_binary_add, 4795, 4364, 4792);
  g->Binary(ynn_binary_multiply, 1571, 4376, 4793);
  g->Binary(ynn_binary_multiply, 4793, 4792, 1582);
  g->Binary(ynn_binary_multiply, 1538, 1582, 1592);
  g->Quantize(1592, 1598, 0.7204724550247192, 0);
  g->Transpose(5311, 3753, {1,0});
  g->Binary(ynn_binary_multiply, 3750, 3752, 3748);
  g->Dot(1598, 3753, YNN_INVALID_VALUE_ID, 3747, 1);
  g->DequantizeTensor(3747, YNN_INVALID_VALUE_ID, 3748, 3749);
  g->QuantizeTensor(3749, 5190, 3751, 1609);
  g->Dequantize(1609, 1620, 0.3018769919872284, 0);
  g->Unary(ynn_unary_square, 1620, 1630);
  g->Reduce(ynn_reduce_sum, 1630, 4811, {2}, true);
  g->ShapeProduct(1630, 4810, {2});
  g->Binary(ynn_binary_divide, 4811, 4810, 1640);
  g->Binary(ynn_binary_add, 1640, 5241, 1651);
  g->Unary(ynn_unary_rsqrt, 1651, 1662);
  g->Binary(ynn_binary_multiply, 1620, 1662, 1673);
  g->Binary(ynn_binary_multiply, 1673, 5317, 1684);
  g->Binary(ynn_binary_add, 1684, 1446, 1695);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1706, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(1706, 1717, {1,0,256});
  g->Unary(ynn_unary_square, 1717, 1728);
  g->Reduce(ynn_reduce_sum, 1728, 4837, {2}, true);
  g->ShapeProduct(1728, 4836, {2});
  g->Binary(ynn_binary_divide, 4837, 4836, 1738);
  g->Binary(ynn_binary_add, 1738, 5241, 1744);
  g->Unary(ynn_unary_rsqrt, 1744, 1755);
  g->Binary(ynn_binary_multiply, 1717, 1755, 1767);
  g->Binary(ynn_binary_multiply, 1767, 5688, 1776);
  g->Binary(ynn_binary_multiply, 5690, 5245, 1787);
  g->Binary(ynn_binary_add, 1776, 1787, 1798);
  g->Binary(ynn_binary_multiply, 1798, 5240, 1808);
  g->Quantize(1695, 1819, 2.70694637298584, 0);
  g->Transpose(5314, 3843, {1,0});
  g->Binary(ynn_binary_multiply, 3841, 3842, 3839);
  g->Dot(1819, 3843, YNN_INVALID_VALUE_ID, 3838, 1);
  g->DequantizeTensor(3838, YNN_INVALID_VALUE_ID, 3839, 3840);
  g->QuantizeTensor(3840, 5190, 3551, 1830);
  g->Dequantize(1830, 1841, 0.02706693857908249, 0);
  g->Polynomial(1841, 4874, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4874, 4875);
  g->Binary(ynn_binary_add, 4875, 4364, 4872);
  g->Binary(ynn_binary_multiply, 1841, 4376, 4873);
  g->Binary(ynn_binary_multiply, 4873, 4872, 1852);
  g->Binary(ynn_binary_multiply, 1852, 1808, 1863);
  g->Quantize(1863, 1874, 0.06299213320016861, 0);
  g->Transpose(5315, 3876, {1,0});
  g->Binary(ynn_binary_multiply, 3873, 3875, 3871);
  g->Dot(1874, 3876, YNN_INVALID_VALUE_ID, 3870, 1);
  g->DequantizeTensor(3870, YNN_INVALID_VALUE_ID, 3871, 3872);
  g->QuantizeTensor(3872, 5190, 3874, 1885);
  g->Dequantize(1885, 1891, 0.0333825945854187, 0);
  g->Unary(ynn_unary_square, 1891, 1902);
  g->Reduce(ynn_reduce_sum, 1902, 4883, {2}, true);
  g->ShapeProduct(1902, 4882, {2});
  g->Binary(ynn_binary_divide, 4883, 4882, 1912);
  g->Binary(ynn_binary_add, 1912, 5241, 1922);
  g->Unary(ynn_unary_rsqrt, 1922, 1933);
  g->Binary(ynn_binary_multiply, 1891, 1933, 1944);
  g->Binary(ynn_binary_multiply, 1944, 5318, 1954);
  g->Binary(ynn_binary_add, 1695, 1954, 1965);
  g->Binary(ynn_binary_multiply, 1965, 5310, 1977);
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
  g->Quantize(2037, 2048, 0.13570576906204224, 0);
  g->Transpose(5508, 3946, {1,0});
  g->Binary(ynn_binary_multiply, 3944, 3945, 3942);
  g->Dot(2048, 3946, YNN_INVALID_VALUE_ID, 3941, 1);
  g->DequantizeTensor(3941, YNN_INVALID_VALUE_ID, 3942, 3943);
  g->QuantizeTensor(3943, 5190, 3425, 2058);
  g->Dequantize(2058, 2068, 0.20570868253707886, 0);
  g->SplitDim(2068, 2081, 2, {2,256});
  g->Transpose(2081, 2091, {0,2,1,3});
  g->Unary(ynn_unary_square, 2091, 2102);
  g->Reduce(ynn_reduce_sum, 2102, 4945, {3}, true);
  g->ShapeProduct(2102, 4944, {3});
  g->Binary(ynn_binary_divide, 4945, 4944, 2113);
  g->Binary(ynn_binary_add, 2113, 5241, 2124);
  g->Unary(ynn_unary_rsqrt, 2124, 2135);
  g->Binary(ynn_binary_multiply, 2091, 2135, 2146);
  g->Binary(ynn_binary_multiply, 2146, 5507, 2157);
  g->Slice(2157, 2167, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2157, 2175, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2175, 2185);
  g->Concat({2185,2167}, 2196, 3);
  g->Binary(ynn_binary_multiply, 2157, 2394, 2206);
  g->Binary(ynn_binary_multiply, 2196, 2498, 2216);
  g->Binary(ynn_binary_add, 2206, 2216, 2227);
  g->Transpose(5512, 4034, {1,0});
  g->Binary(ynn_binary_multiply, 3944, 4033, 4031);
  g->Dot(2048, 4034, YNN_INVALID_VALUE_ID, 4030, 1);
  g->DequantizeTensor(4030, YNN_INVALID_VALUE_ID, 4031, 4032);
  g->QuantizeTensor(4032, 5190, 3425, 2247);
  g->Dequantize(2247, 2258, 0.20570868253707886, 0);
  g->SplitDim(2258, 2269, 2, {2,256});
  g->Transpose(2269, 2280, {0,2,1,3});
  g->Unary(ynn_unary_square, 2280, 2292);
  g->Reduce(ynn_reduce_sum, 2292, 4993, {3}, true);
  g->ShapeProduct(2292, 4992, {3});
  g->Binary(ynn_binary_divide, 4993, 4992, 2303);
  g->Binary(ynn_binary_add, 2303, 5241, 2313);
  g->Unary(ynn_unary_rsqrt, 2313, 2319);
  g->Binary(ynn_binary_multiply, 2280, 2319, 2320);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2227, 2321, 0.006215503439307213, 0);
  g->Append(5203, 2321, 5725, 2, s2, s1);
  g->View(5725, 5773, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2320, 2322, 0.047244105488061905, 0);
  g->Append(5227, 2322, 5749, 2, s2, s1);
  g->View(5749, 5796, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5511, 4066, {1,0});
  g->Binary(ynn_binary_multiply, 3944, 4065, 4062);
  g->Dot(2048, 4066, YNN_INVALID_VALUE_ID, 4061, 1);
  g->DequantizeTensor(4061, YNN_INVALID_VALUE_ID, 4062, 4063);
  g->QuantizeTensor(4063, 5190, 4064, 2324);
  g->Dequantize(2324, 2325, 0.21259844303131104, 0);
  g->SplitDim(2325, 2326, 2, {8,256});
  g->Transpose(2326, 2327, {0,2,1,3});
  g->Unary(ynn_unary_square, 2327, 2328);
  g->Reduce(ynn_reduce_sum, 2328, 4997, {3}, true);
  g->ShapeProduct(2328, 4996, {3});
  g->Binary(ynn_binary_divide, 4997, 4996, 2329);
  g->Binary(ynn_binary_add, 2329, 5241, 2330);
  g->Unary(ynn_unary_rsqrt, 2330, 2331);
  g->Binary(ynn_binary_multiply, 2327, 2331, 2333);
  g->Binary(ynn_binary_multiply, 2333, 5510, 2334);
  g->Slice(2334, 2335, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2334, 2336, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2336, 2337);
  g->Concat({2337,2335}, 2338, 3);
  g->Binary(ynn_binary_multiply, 2334, 2394, 2339);
  g->Binary(ynn_binary_multiply, 2338, 2498, 2340);
  g->Binary(ynn_binary_add, 2339, 2340, 2341);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5773, 2342, 0.006215503439307213, 0);
  g->Dequantize(5796, 2344, 0.047244105488061905, 0);
  g->Slice(2341, 2345, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2342, 2346, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2344, 2347, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2345, 2346, 2348, false, true);
  g->Mask(2348, 5276, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5276, 5001, {-1}, true);
  g->Binary(ynn_binary_subtract, 5276, 5001, 4998);
  g->Unary(ynn_unary_exp, 4998, 4999);
  g->Reduce(ynn_reduce_sum, 4999, 5002, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5002, 5000);
  g->Binary(ynn_binary_multiply, 4999, 5000, 2349);
  g->Matmul(2349, 2347, 2350, false, false);
  g->Slice(2341, 2351, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2342, 2352, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2344, 2354, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2351, 2352, 2355, false, true);
  g->Mask(2355, 5277, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5277, 5006, {-1}, true);
  g->Binary(ynn_binary_subtract, 5277, 5006, 5003);
  g->Unary(ynn_unary_exp, 5003, 5004);
  g->Reduce(ynn_reduce_sum, 5004, 5007, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5007, 5005);
  g->Binary(ynn_binary_multiply, 5004, 5005, 2356);
  g->Matmul(2356, 2354, 2357, false, false);
  g->Concat({2350,2357}, 2358, 1);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2358, 2359, {0,2,1,3});
  g->FuseDims(2359, 2360, 2, 2);
  g->Quantize(2360, 2361, 0.02595965564250946, 0);
  g->Transpose(5509, 4073, {1,0});
  g->Binary(ynn_binary_multiply, 4070, 4072, 4068);
  g->Dot(2361, 4073, YNN_INVALID_VALUE_ID, 4067, 1);
  g->DequantizeTensor(4067, YNN_INVALID_VALUE_ID, 4068, 4069);
  g->QuantizeTensor(4069, 5190, 4071, 2362);
  g->Dequantize(2362, 2364, 0.07314001023769379, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1977, 1988);
  g->Reduce(ynn_reduce_sum, 1988, 4915, {2}, true);
  g->ShapeProduct(1988, 4914, {2});
  g->Binary(ynn_binary_divide, 4915, 4914, 1999);
  g->Binary(ynn_binary_add, 1999, 5241, 2010);
  g->Unary(ynn_unary_rsqrt, 2010, 2020);
  g->Binary(ynn_binary_multiply, 1977, 2020, 2029);
  g->Binary(ynn_binary_multiply, 2029, 5496, 2037);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2364, 2365);
  g->Reduce(ynn_reduce_sum, 2365, 5009, {2}, true);
  g->ShapeProduct(2365, 5008, {2});
  g->Binary(ynn_binary_divide, 5009, 5008, 2366);
  g->Binary(ynn_binary_add, 2366, 5241, 2367);
  g->Unary(ynn_unary_rsqrt, 2367, 2368);
  g->Binary(ynn_binary_multiply, 2364, 2368, 2369);
  g->Binary(ynn_binary_multiply, 2369, 5503, 2370);
  g->Binary(ynn_binary_add, 2370, 1977, 2371);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2371, 2372);
  g->Reduce(ynn_reduce_sum, 2372, 5011, {2}, true);
  g->ShapeProduct(2372, 5010, {2});
  g->Binary(ynn_binary_divide, 5011, 5010, 2373);
  g->Binary(ynn_binary_add, 2373, 5241, 2375);
  g->Unary(ynn_unary_rsqrt, 2375, 2376);
  g->Binary(ynn_binary_multiply, 2371, 2376, 2377);
  g->Binary(ynn_binary_multiply, 2377, 5506, 2378);
  g->Quantize(2378, 2379, 0.04597063735127449, 0);
  g->Transpose(5500, 4080, {1,0});
  g->Binary(ynn_binary_multiply, 4077, 4079, 4075);
  g->Dot(2379, 4080, YNN_INVALID_VALUE_ID, 4074, 1);
  g->DequantizeTensor(4074, YNN_INVALID_VALUE_ID, 4075, 4076);
  g->QuantizeTensor(4076, 5190, 4078, 2380);
  g->Dequantize(2380, 2381, 0.0703740268945694, 0);
  g->Transpose(5499, 4085, {1,0});
  g->Binary(ynn_binary_multiply, 4077, 4084, 4082);
  g->Dot(2379, 4085, YNN_INVALID_VALUE_ID, 4081, 1);
  g->DequantizeTensor(4081, YNN_INVALID_VALUE_ID, 4082, 4083);
  g->QuantizeTensor(4083, 5190, 4078, 2382);
  g->Dequantize(2382, 2383, 0.0703740268945694, 0);
  g->Polynomial(2383, 5014, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5014, 5015);
  g->Binary(ynn_binary_add, 5015, 4364, 5012);
  g->Binary(ynn_binary_multiply, 2383, 4376, 5013);
  g->Binary(ynn_binary_multiply, 5013, 5012, 2384);
  g->Binary(ynn_binary_multiply, 2381, 2384, 2385);
  g->Quantize(2385, 2386, 0.33070865273475647, 0);
  g->Transpose(5498, 4092, {1,0});
  g->Binary(ynn_binary_multiply, 4089, 4091, 4087);
  g->Dot(2386, 4092, YNN_INVALID_VALUE_ID, 4086, 1);
  g->DequantizeTensor(4086, YNN_INVALID_VALUE_ID, 4087, 4088);
  g->QuantizeTensor(4088, 5190, 4090, 2387);
  g->Dequantize(2387, 2388, 0.16312803328037262, 0);
  g->Unary(ynn_unary_square, 2388, 2389);
  g->Reduce(ynn_reduce_sum, 2389, 5017, {2}, true);
  g->ShapeProduct(2389, 5016, {2});
  g->Binary(ynn_binary_divide, 5017, 5016, 2390);
  g->Binary(ynn_binary_add, 2390, 5241, 2391);
  g->Unary(ynn_unary_rsqrt, 2391, 2392);
  g->Binary(ynn_binary_multiply, 2388, 2392, 2393);
  g->Binary(ynn_binary_multiply, 2393, 5504, 2396);
  g->Binary(ynn_binary_add, 2396, 2371, 2397);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2398, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(2398, 2399, {1,0,256});
  g->Unary(ynn_unary_square, 2399, 2400);
  g->Reduce(ynn_reduce_sum, 2400, 5019, {2}, true);
  g->ShapeProduct(2400, 5018, {2});
  g->Binary(ynn_binary_divide, 5019, 5018, 2401);
  g->Binary(ynn_binary_add, 2401, 5241, 2402);
  g->Unary(ynn_unary_rsqrt, 2402, 2403);
  g->Binary(ynn_binary_multiply, 2399, 2403, 2404);
  g->Binary(ynn_binary_multiply, 2404, 5688, 2405);
  g->Binary(ynn_binary_multiply, 5701, 5245, 2407);
  g->Binary(ynn_binary_add, 2405, 2407, 2408);
  g->Binary(ynn_binary_multiply, 2408, 5240, 2409);
  g->Quantize(2397, 2410, 0.5168190598487854, 0);
  g->Transpose(5501, 4104, {1,0});
  g->Binary(ynn_binary_multiply, 4101, 4103, 4099);
  g->Dot(2410, 4104, YNN_INVALID_VALUE_ID, 4098, 1);
  g->DequantizeTensor(4098, YNN_INVALID_VALUE_ID, 4099, 4100);
  g->QuantizeTensor(4100, 5190, 4102, 2411);
  g->Dequantize(2411, 2412, 0.03641733527183533, 0);
  g->Polynomial(2412, 5022, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5022, 5023);
  g->Binary(ynn_binary_add, 5023, 4364, 5020);
  g->Binary(ynn_binary_multiply, 2412, 4376, 5021);
  g->Binary(ynn_binary_multiply, 5021, 5020, 2413);
  g->Binary(ynn_binary_multiply, 2413, 2409, 2414);
  g->Quantize(2414, 2415, 0.12598426640033722, 0);
  g->Transpose(5502, 4111, {1,0});
  g->Binary(ynn_binary_multiply, 4108, 4110, 4106);
  g->Dot(2415, 4111, YNN_INVALID_VALUE_ID, 4105, 1);
  g->DequantizeTensor(4105, YNN_INVALID_VALUE_ID, 4106, 4107);
  g->QuantizeTensor(4107, 5190, 4109, 2416);
  g->Dequantize(2416, 2418, 0.050657037645578384, 0);
  g->Unary(ynn_unary_square, 2418, 2419);
  g->Reduce(ynn_reduce_sum, 2419, 5025, {2}, true);
  g->ShapeProduct(2419, 5024, {2});
  g->Binary(ynn_binary_divide, 5025, 5024, 2420);
  g->Binary(ynn_binary_add, 2420, 5241, 2421);
  g->Unary(ynn_unary_rsqrt, 2421, 2422);
  g->Binary(ynn_binary_multiply, 2418, 2422, 2423);
  g->Binary(ynn_binary_multiply, 2423, 5505, 2424);
  g->Binary(ynn_binary_add, 2397, 2424, 2425);
  g->Binary(ynn_binary_multiply, 2425, 5497, 2426);
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
  g->Quantize(2433, 2434, 0.09872813522815704, 0);
  g->Transpose(5580, 4118, {1,0});
  g->Binary(ynn_binary_multiply, 4115, 4117, 4113);
  g->Dot(2434, 4118, YNN_INVALID_VALUE_ID, 4112, 1);
  g->DequantizeTensor(4112, YNN_INVALID_VALUE_ID, 4113, 4114);
  g->QuantizeTensor(4114, 5190, 4116, 2435);
  g->Dequantize(2435, 2436, 0.1446850597858429, 0);
  g->SplitDim(2436, 2437, 2, {2,256});
  g->Transpose(2437, 2438, {0,2,1,3});
  g->Unary(ynn_unary_square, 2438, 2440);
  g->Reduce(ynn_reduce_sum, 2440, 5029, {3}, true);
  g->ShapeProduct(2440, 5028, {3});
  g->Binary(ynn_binary_divide, 5029, 5028, 2441);
  g->Binary(ynn_binary_add, 2441, 5241, 2442);
  g->Unary(ynn_unary_rsqrt, 2442, 2443);
  g->Binary(ynn_binary_multiply, 2438, 2443, 2444);
  g->Binary(ynn_binary_multiply, 2444, 5579, 2445);
  g->Slice(2445, 2446, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2445, 2447, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2447, 2448);
  g->Concat({2448,2446}, 2449, 3);
  g->Binary(ynn_binary_multiply, 2445, 2394, 2451);
  g->Binary(ynn_binary_multiply, 2449, 2498, 2452);
  g->Binary(ynn_binary_add, 2451, 2452, 2453);
  g->Transpose(5584, 4123, {1,0});
  g->Binary(ynn_binary_multiply, 4115, 4122, 4120);
  g->Dot(2434, 4123, YNN_INVALID_VALUE_ID, 4119, 1);
  g->DequantizeTensor(4119, YNN_INVALID_VALUE_ID, 4120, 4121);
  g->QuantizeTensor(4121, 5190, 4116, 2454);
  g->Dequantize(2454, 2455, 0.1446850597858429, 0);
  g->SplitDim(2455, 2456, 2, {2,256});
  g->Transpose(2456, 2457, {0,2,1,3});
  g->Unary(ynn_unary_square, 2457, 2458);
  g->Reduce(ynn_reduce_sum, 2458, 5033, {3}, true);
  g->ShapeProduct(2458, 5032, {3});
  g->Binary(ynn_binary_divide, 5033, 5032, 2459);
  g->Binary(ynn_binary_add, 2459, 5241, 2461);
  g->Unary(ynn_unary_rsqrt, 2461, 2462);
  g->Binary(ynn_binary_multiply, 2457, 2462, 2463);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2453, 2464, 0.005788442213088274, 0);
  g->Append(5208, 2464, 5730, 2, s2, s1);
  g->View(5730, 5777, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2463, 2465, 0.047244105488061905, 0);
  g->Append(5232, 2465, 5754, 2, s2, s1);
  g->View(5754, 5800, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5583, 4129, {1,0});
  g->Binary(ynn_binary_multiply, 4115, 4128, 4125);
  g->Dot(2434, 4129, YNN_INVALID_VALUE_ID, 4124, 1);
  g->DequantizeTensor(4124, YNN_INVALID_VALUE_ID, 4125, 4126);
  g->QuantizeTensor(4126, 5190, 4127, 2467);
  g->Dequantize(2467, 2468, 0.12253937870264053, 0);
  g->SplitDim(2468, 2469, 2, {8,256});
  g->Transpose(2469, 2470, {0,2,1,3});
  g->Unary(ynn_unary_square, 2470, 2471);
  g->Reduce(ynn_reduce_sum, 2471, 5035, {3}, true);
  g->ShapeProduct(2471, 5034, {3});
  g->Binary(ynn_binary_divide, 5035, 5034, 2472);
  g->Binary(ynn_binary_add, 2472, 5241, 2473);
  g->Unary(ynn_unary_rsqrt, 2473, 2474);
  g->Binary(ynn_binary_multiply, 2470, 2474, 2475);
  g->Binary(ynn_binary_multiply, 2475, 5582, 2476);
  g->Slice(2476, 2478, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2476, 2479, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2479, 2480);
  g->Concat({2480,2478}, 2481, 3);
  g->Binary(ynn_binary_multiply, 2476, 2394, 2482);
  g->Binary(ynn_binary_multiply, 2481, 2498, 2483);
  g->Binary(ynn_binary_add, 2482, 2483, 2484);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5777, 2485, 0.005788442213088274, 0);
  g->Dequantize(5800, 2486, 0.047244105488061905, 0);
  g->Slice(2484, 2487, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2485, 2489, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2486, 2490, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2487, 2489, 2491, false, true);
  g->Mask(2491, 5278, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5278, 5039, {-1}, true);
  g->Binary(ynn_binary_subtract, 5278, 5039, 5036);
  g->Unary(ynn_unary_exp, 5036, 5037);
  g->Reduce(ynn_reduce_sum, 5037, 5040, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5040, 5038);
  g->Binary(ynn_binary_multiply, 5037, 5038, 2492);
  g->Matmul(2492, 2490, 2493, false, false);
  g->Slice(2484, 2494, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2485, 2495, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2486, 2496, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2494, 2495, 2497, false, true);
  g->Mask(2497, 5279, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5279, 5044, {-1}, true);
  g->Binary(ynn_binary_subtract, 5279, 5044, 5041);
  g->Unary(ynn_unary_exp, 5041, 5042);
  g->Reduce(ynn_reduce_sum, 5042, 5045, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5045, 5043);
  g->Binary(ynn_binary_multiply, 5042, 5043, 2499);
  g->Matmul(2499, 2496, 2500, false, false);
  g->Concat({2493,2500}, 2501, 1);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2501, 2502, {0,2,1,3});
  g->FuseDims(2502, 2503, 2, 2);
  g->Quantize(2503, 2504, 0.02276083640754223, 0);
  g->Transpose(5581, 4136, {1,0});
  g->Binary(ynn_binary_multiply, 4133, 4135, 4131);
  g->Dot(2504, 4136, YNN_INVALID_VALUE_ID, 4130, 1);
  g->DequantizeTensor(4130, YNN_INVALID_VALUE_ID, 4131, 4132);
  g->QuantizeTensor(4132, 5190, 4134, 2505);
  g->Dequantize(2505, 2506, 0.050406839698553085, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2426, 2427);
  g->Reduce(ynn_reduce_sum, 2427, 5027, {2}, true);
  g->ShapeProduct(2427, 5026, {2});
  g->Binary(ynn_binary_divide, 5027, 5026, 2429);
  g->Binary(ynn_binary_add, 2429, 5241, 2430);
  g->Unary(ynn_unary_rsqrt, 2430, 2431);
  g->Binary(ynn_binary_multiply, 2426, 2431, 2432);
  g->Binary(ynn_binary_multiply, 2432, 5568, 2433);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2506, 2507);
  g->Reduce(ynn_reduce_sum, 2507, 5047, {2}, true);
  g->ShapeProduct(2507, 5046, {2});
  g->Binary(ynn_binary_divide, 5047, 5046, 2508);
  g->Binary(ynn_binary_add, 2508, 5241, 2509);
  g->Unary(ynn_unary_rsqrt, 2509, 2510);
  g->Binary(ynn_binary_multiply, 2506, 2510, 2511);
  g->Binary(ynn_binary_multiply, 2511, 5575, 2512);
  g->Binary(ynn_binary_add, 2512, 2426, 2513);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2513, 2514);
  g->Reduce(ynn_reduce_sum, 2514, 5049, {2}, true);
  g->ShapeProduct(2514, 5048, {2});
  g->Binary(ynn_binary_divide, 5049, 5048, 2515);
  g->Binary(ynn_binary_add, 2515, 5241, 2516);
  g->Unary(ynn_unary_rsqrt, 2516, 2517);
  g->Binary(ynn_binary_multiply, 2513, 2517, 2519);
  g->Binary(ynn_binary_multiply, 2519, 5578, 2520);
  g->Quantize(2520, 2521, 0.0688801258802414, 0);
  g->Transpose(5572, 4143, {1,0});
  g->Binary(ynn_binary_multiply, 4140, 4142, 4138);
  g->Dot(2521, 4143, YNN_INVALID_VALUE_ID, 4137, 1);
  g->DequantizeTensor(4137, YNN_INVALID_VALUE_ID, 4138, 4139);
  g->QuantizeTensor(4139, 5190, 4141, 2522);
  g->Dequantize(2522, 2523, 0.06496063619852066, 0);
  g->Transpose(5571, 4148, {1,0});
  g->Binary(ynn_binary_multiply, 4140, 4147, 4145);
  g->Dot(2521, 4148, YNN_INVALID_VALUE_ID, 4144, 1);
  g->DequantizeTensor(4144, YNN_INVALID_VALUE_ID, 4145, 4146);
  g->QuantizeTensor(4146, 5190, 4141, 2524);
  g->Dequantize(2524, 2525, 0.06496063619852066, 0);
  g->Polynomial(2525, 5052, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5052, 5053);
  g->Binary(ynn_binary_add, 5053, 4364, 5050);
  g->Binary(ynn_binary_multiply, 2525, 4376, 5051);
  g->Binary(ynn_binary_multiply, 5051, 5050, 2526);
  g->Binary(ynn_binary_multiply, 2523, 2526, 2527);
  g->Quantize(2527, 2528, 0.2303149700164795, 0);
  g->Transpose(5570, 4155, {1,0});
  g->Binary(ynn_binary_multiply, 4152, 4154, 4150);
  g->Dot(2528, 4155, YNN_INVALID_VALUE_ID, 4149, 1);
  g->DequantizeTensor(4149, YNN_INVALID_VALUE_ID, 4150, 4151);
  g->QuantizeTensor(4151, 5190, 4153, 2529);
  g->Dequantize(2529, 2530, 0.10468774288892746, 0);
  g->Unary(ynn_unary_square, 2530, 2531);
  g->Reduce(ynn_reduce_sum, 2531, 5055, {2}, true);
  g->ShapeProduct(2531, 5054, {2});
  g->Binary(ynn_binary_divide, 5055, 5054, 2532);
  g->Binary(ynn_binary_add, 2532, 5241, 2533);
  g->Unary(ynn_unary_rsqrt, 2533, 2534);
  g->Binary(ynn_binary_multiply, 2530, 2534, 2535);
  g->Binary(ynn_binary_multiply, 2535, 5576, 2536);
  g->Binary(ynn_binary_add, 2536, 2513, 2537);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2538, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(2538, 2539, {1,0,256});
  g->Unary(ynn_unary_square, 2539, 2540);
  g->Reduce(ynn_reduce_sum, 2540, 5057, {2}, true);
  g->ShapeProduct(2540, 5056, {2});
  g->Binary(ynn_binary_divide, 5057, 5056, 2541);
  g->Binary(ynn_binary_add, 2541, 5241, 2542);
  g->Unary(ynn_unary_rsqrt, 2542, 2543);
  g->Binary(ynn_binary_multiply, 2539, 2543, 2544);
  g->Binary(ynn_binary_multiply, 2544, 5688, 2545);
  g->Binary(ynn_binary_multiply, 5705, 5245, 2546);
  g->Binary(ynn_binary_add, 2545, 2546, 2547);
  g->Binary(ynn_binary_multiply, 2547, 5240, 2548);
  g->Quantize(2537, 2549, 0.5823876857757568, 0);
  g->Transpose(5573, 4162, {1,0});
  g->Binary(ynn_binary_multiply, 4159, 4161, 4157);
  g->Dot(2549, 4162, YNN_INVALID_VALUE_ID, 4156, 1);
  g->DequantizeTensor(4156, YNN_INVALID_VALUE_ID, 4157, 4158);
  g->QuantizeTensor(4158, 5190, 4160, 2550);
  g->Dequantize(2550, 2551, 0.040600404143333435, 0);
  g->Polynomial(2551, 5060, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5060, 5061);
  g->Binary(ynn_binary_add, 5061, 4364, 5058);
  g->Binary(ynn_binary_multiply, 2551, 4376, 5059);
  g->Binary(ynn_binary_multiply, 5059, 5058, 2552);
  g->Binary(ynn_binary_multiply, 2552, 2548, 2553);
  g->Quantize(2553, 2554, 0.09350394457578659, 0);
  g->Transpose(5574, 4168, {1,0});
  g->Binary(ynn_binary_multiply, 3387, 4167, 4164);
  g->Dot(2554, 4168, YNN_INVALID_VALUE_ID, 4163, 1);
  g->DequantizeTensor(4163, YNN_INVALID_VALUE_ID, 4164, 4165);
  g->QuantizeTensor(4165, 5190, 4166, 2555);
  g->Dequantize(2555, 2556, 0.0440652035176754, 0);
  g->Unary(ynn_unary_square, 2556, 2557);
  g->Reduce(ynn_reduce_sum, 2557, 5063, {2}, true);
  g->ShapeProduct(2557, 5062, {2});
  g->Binary(ynn_binary_divide, 5063, 5062, 2559);
  g->Binary(ynn_binary_add, 2559, 5241, 2560);
  g->Unary(ynn_unary_rsqrt, 2560, 2561);
  g->Binary(ynn_binary_multiply, 2556, 2561, 2562);
  g->Binary(ynn_binary_multiply, 2562, 5577, 2563);
  g->Binary(ynn_binary_add, 2537, 2563, 2564);
  g->Binary(ynn_binary_multiply, 2564, 5569, 2565);
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
  g->Quantize(2572, 2573, 0.20282812416553497, 0);
  g->Transpose(5597, 4181, {1,0});
  g->Binary(ynn_binary_multiply, 4178, 4180, 4176);
  g->Dot(2573, 4181, YNN_INVALID_VALUE_ID, 4175, 1);
  g->DequantizeTensor(4175, YNN_INVALID_VALUE_ID, 4176, 4177);
  g->QuantizeTensor(4177, 5190, 4179, 2574);
  g->Dequantize(2574, 2575, 0.16338583827018738, 0);
  g->SplitDim(2575, 2576, 2, {2,256});
  g->Transpose(2576, 2577, {0,2,1,3});
  g->Unary(ynn_unary_square, 2577, 2578);
  g->Reduce(ynn_reduce_sum, 2578, 5067, {3}, true);
  g->ShapeProduct(2578, 5066, {3});
  g->Binary(ynn_binary_divide, 5067, 5066, 2579);
  g->Binary(ynn_binary_add, 2579, 5241, 2581);
  g->Unary(ynn_unary_rsqrt, 2581, 2582);
  g->Binary(ynn_binary_multiply, 2577, 2582, 2583);
  g->Binary(ynn_binary_multiply, 2583, 5596, 2584);
  g->Slice(2584, 2585, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2584, 2586, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2586, 2587);
  g->Concat({2587,2585}, 2588, 3);
  g->Binary(ynn_binary_multiply, 2584, 2394, 2589);
  g->Binary(ynn_binary_multiply, 2588, 2498, 2590);
  g->Binary(ynn_binary_add, 2589, 2590, 2592);
  g->Transpose(5601, 4186, {1,0});
  g->Binary(ynn_binary_multiply, 4178, 4185, 4183);
  g->Dot(2573, 4186, YNN_INVALID_VALUE_ID, 4182, 1);
  g->DequantizeTensor(4182, YNN_INVALID_VALUE_ID, 4183, 4184);
  g->QuantizeTensor(4184, 5190, 4179, 2593);
  g->Dequantize(2593, 2594, 0.16338583827018738, 0);
  g->SplitDim(2594, 2595, 2, {2,256});
  g->Transpose(2595, 2596, {0,2,1,3});
  g->Unary(ynn_unary_square, 2596, 2597);
  g->Reduce(ynn_reduce_sum, 2597, 5069, {3}, true);
  g->ShapeProduct(2597, 5068, {3});
  g->Binary(ynn_binary_divide, 5069, 5068, 2598);
  g->Binary(ynn_binary_add, 2598, 5241, 2599);
  g->Unary(ynn_unary_rsqrt, 2599, 2600);
  g->Binary(ynn_binary_multiply, 2596, 2600, 2603);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2592, 2604, 0.00596147496253252, 0);
  g->Append(5209, 2604, 5731, 2, s2, s1);
  g->View(5731, 5778, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2603, 2605, 0.047244105488061905, 0);
  g->Append(5233, 2605, 5755, 2, s2, s1);
  g->View(5755, 5801, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5600, 4192, {1,0});
  g->Binary(ynn_binary_multiply, 4178, 4191, 4188);
  g->Dot(2573, 4192, YNN_INVALID_VALUE_ID, 4187, 1);
  g->DequantizeTensor(4187, YNN_INVALID_VALUE_ID, 4188, 4189);
  g->QuantizeTensor(4189, 5190, 4190, 2606);
  g->Dequantize(2606, 2607, 0.16240158677101135, 0);
  g->SplitDim(2607, 2609, 2, {8,256});
  g->Transpose(2609, 2610, {0,2,1,3});
  g->Unary(ynn_unary_square, 2610, 2611);
  g->Reduce(ynn_reduce_sum, 2611, 5073, {3}, true);
  g->ShapeProduct(2611, 5072, {3});
  g->Binary(ynn_binary_divide, 5073, 5072, 2612);
  g->Binary(ynn_binary_add, 2612, 5241, 2613);
  g->Unary(ynn_unary_rsqrt, 2613, 2614);
  g->Binary(ynn_binary_multiply, 2610, 2614, 2615);
  g->Binary(ynn_binary_multiply, 2615, 5599, 2616);
  g->Slice(2616, 2617, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2616, 2618, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2618, 2620);
  g->Concat({2620,2617}, 2621, 3);
  g->Binary(ynn_binary_multiply, 2616, 2394, 2622);
  g->Binary(ynn_binary_multiply, 2621, 2498, 2623);
  g->Binary(ynn_binary_add, 2622, 2623, 2624);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5778, 2625, 0.00596147496253252, 0);
  g->Dequantize(5801, 2626, 0.047244105488061905, 0);
  g->Slice(2624, 2627, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2625, 2628, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2626, 2629, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2627, 2628, 2631, false, true);
  g->Mask(2631, 5280, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5280, 5077, {-1}, true);
  g->Binary(ynn_binary_subtract, 5280, 5077, 5074);
  g->Unary(ynn_unary_exp, 5074, 5075);
  g->Reduce(ynn_reduce_sum, 5075, 5078, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5078, 5076);
  g->Binary(ynn_binary_multiply, 5075, 5076, 2632);
  g->Matmul(2632, 2629, 2633, false, false);
  g->Slice(2624, 2634, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2625, 2635, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2626, 2636, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2634, 2635, 2637, false, true);
  g->Mask(2637, 5281, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5281, 5082, {-1}, true);
  g->Binary(ynn_binary_subtract, 5281, 5082, 5079);
  g->Unary(ynn_unary_exp, 5079, 5080);
  g->Reduce(ynn_reduce_sum, 5080, 5083, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5083, 5081);
  g->Binary(ynn_binary_multiply, 5080, 5081, 2638);
  g->Matmul(2638, 2636, 2640, false, false);
  g->Concat({2633,2640}, 2641, 1);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2641, 2642, {0,2,1,3});
  g->FuseDims(2642, 2643, 2, 2);
  g->Quantize(2643, 2644, 0.024114182218909264, 0);
  g->Transpose(5598, 4199, {1,0});
  g->Binary(ynn_binary_multiply, 4196, 4198, 4194);
  g->Dot(2644, 4199, YNN_INVALID_VALUE_ID, 4193, 1);
  g->DequantizeTensor(4193, YNN_INVALID_VALUE_ID, 4194, 4195);
  g->QuantizeTensor(4195, 5190, 4197, 2645);
  g->Dequantize(2645, 2646, 0.05563074350357056, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2565, 2566);
  g->Reduce(ynn_reduce_sum, 2566, 5065, {2}, true);
  g->ShapeProduct(2566, 5064, {2});
  g->Binary(ynn_binary_divide, 5065, 5064, 2567);
  g->Binary(ynn_binary_add, 2567, 5241, 2568);
  g->Unary(ynn_unary_rsqrt, 2568, 2570);
  g->Binary(ynn_binary_multiply, 2565, 2570, 2571);
  g->Binary(ynn_binary_multiply, 2571, 5585, 2572);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2646, 2647);
  g->Reduce(ynn_reduce_sum, 2647, 5085, {2}, true);
  g->ShapeProduct(2647, 5084, {2});
  g->Binary(ynn_binary_divide, 5085, 5084, 2648);
  g->Binary(ynn_binary_add, 2648, 5241, 2649);
  g->Unary(ynn_unary_rsqrt, 2649, 2651);
  g->Binary(ynn_binary_multiply, 2646, 2651, 2652);
  g->Binary(ynn_binary_multiply, 2652, 5592, 2653);
  g->Binary(ynn_binary_add, 2653, 2565, 2654);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2654, 2655);
  g->Reduce(ynn_reduce_sum, 2655, 5087, {2}, true);
  g->ShapeProduct(2655, 5086, {2});
  g->Binary(ynn_binary_divide, 5087, 5086, 2656);
  g->Binary(ynn_binary_add, 2656, 5241, 2657);
  g->Unary(ynn_unary_rsqrt, 2657, 2658);
  g->Binary(ynn_binary_multiply, 2654, 2658, 2659);
  g->Binary(ynn_binary_multiply, 2659, 5595, 2660);
  g->Quantize(2660, 2662, 0.04694453626871109, 0);
  g->Transpose(5589, 4205, {1,0});
  g->Binary(ynn_binary_multiply, 4203, 4204, 4201);
  g->Dot(2662, 4205, YNN_INVALID_VALUE_ID, 4200, 1);
  g->DequantizeTensor(4200, YNN_INVALID_VALUE_ID, 4201, 4202);
  g->QuantizeTensor(4202, 5190, 3297, 2663);
  g->Dequantize(2663, 2664, 0.0664370134472847, 0);
  g->Transpose(5588, 4210, {1,0});
  g->Binary(ynn_binary_multiply, 4203, 4209, 4207);
  g->Dot(2662, 4210, YNN_INVALID_VALUE_ID, 4206, 1);
  g->DequantizeTensor(4206, YNN_INVALID_VALUE_ID, 4207, 4208);
  g->QuantizeTensor(4208, 5190, 3297, 2665);
  g->Dequantize(2665, 2666, 0.0664370134472847, 0);
  g->Polynomial(2666, 5090, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5090, 5091);
  g->Binary(ynn_binary_add, 5091, 4364, 5088);
  g->Binary(ynn_binary_multiply, 2666, 4376, 5089);
  g->Binary(ynn_binary_multiply, 5089, 5088, 2667);
  g->Binary(ynn_binary_multiply, 2664, 2667, 2668);
  g->Quantize(2668, 2669, 0.2027559131383896, 0);
  g->Transpose(5587, 4216, {1,0});
  g->Binary(ynn_binary_multiply, 3351, 4215, 4212);
  g->Dot(2669, 4216, YNN_INVALID_VALUE_ID, 4211, 1);
  g->DequantizeTensor(4211, YNN_INVALID_VALUE_ID, 4212, 4213);
  g->QuantizeTensor(4213, 5190, 4214, 2670);
  g->Dequantize(2670, 2672, 0.0875178799033165, 0);
  g->Unary(ynn_unary_square, 2672, 2673);
  g->Reduce(ynn_reduce_sum, 2673, 5093, {2}, true);
  g->ShapeProduct(2673, 5092, {2});
  g->Binary(ynn_binary_divide, 5093, 5092, 2674);
  g->Binary(ynn_binary_add, 2674, 5241, 2675);
  g->Unary(ynn_unary_rsqrt, 2675, 2676);
  g->Binary(ynn_binary_multiply, 2672, 2676, 2677);
  g->Binary(ynn_binary_multiply, 2677, 5593, 2678);
  g->Binary(ynn_binary_add, 2678, 2654, 2679);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2680, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(2680, 2681, {1,0,256});
  g->Unary(ynn_unary_square, 2681, 2683);
  g->Reduce(ynn_reduce_sum, 2683, 5095, {2}, true);
  g->ShapeProduct(2683, 5094, {2});
  g->Binary(ynn_binary_divide, 5095, 5094, 2684);
  g->Binary(ynn_binary_add, 2684, 5241, 2685);
  g->Unary(ynn_unary_rsqrt, 2685, 2686);
  g->Binary(ynn_binary_multiply, 2681, 2686, 2687);
  g->Binary(ynn_binary_multiply, 2687, 5688, 2688);
  g->Binary(ynn_binary_multiply, 5706, 5245, 2689);
  g->Binary(ynn_binary_add, 2688, 2689, 2690);
  g->Binary(ynn_binary_multiply, 2690, 5240, 2691);
  g->Quantize(2679, 2692, 0.5713114738464355, 0);
  g->Transpose(5590, 4223, {1,0});
  g->Binary(ynn_binary_multiply, 4220, 4222, 4218);
  g->Dot(2692, 4223, YNN_INVALID_VALUE_ID, 4217, 1);
  g->DequantizeTensor(4217, YNN_INVALID_VALUE_ID, 4218, 4219);
  g->QuantizeTensor(4219, 5190, 4221, 2694);
  g->Dequantize(2694, 2695, 0.06594488769769669, 0);
  g->Polynomial(2695, 5098, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5098, 5099);
  g->Binary(ynn_binary_add, 5099, 4364, 5096);
  g->Binary(ynn_binary_multiply, 2695, 4376, 5097);
  g->Binary(ynn_binary_multiply, 5097, 5096, 2696);
  g->Binary(ynn_binary_multiply, 2696, 2691, 2697);
  g->Quantize(2697, 2698, 0.4055117964744568, 0);
  g->Transpose(5591, 4230, {1,0});
  g->Binary(ynn_binary_multiply, 4227, 4229, 4225);
  g->Dot(2698, 4230, YNN_INVALID_VALUE_ID, 4224, 1);
  g->DequantizeTensor(4224, YNN_INVALID_VALUE_ID, 4225, 4226);
  g->QuantizeTensor(4226, 5190, 4228, 2699);
  g->Dequantize(2699, 2700, 0.10920456796884537, 0);
  g->Unary(ynn_unary_square, 2700, 2701);
  g->Reduce(ynn_reduce_sum, 2701, 5101, {2}, true);
  g->ShapeProduct(2701, 5100, {2});
  g->Binary(ynn_binary_divide, 5101, 5100, 2702);
  g->Binary(ynn_binary_add, 2702, 5241, 2703);
  g->Unary(ynn_unary_rsqrt, 2703, 2706);
  g->Binary(ynn_binary_multiply, 2700, 2706, 2707);
  g->Binary(ynn_binary_multiply, 2707, 5594, 2708);
  g->Binary(ynn_binary_add, 2679, 2708, 2709);
  g->Binary(ynn_binary_multiply, 2709, 5586, 2710);
}

// Scope: "Layer4"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4(Context& ctx) {
  BuildLayer4Attention(ctx);
  BuildLayer4Mlp(ctx);
  BuildLayer4PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
