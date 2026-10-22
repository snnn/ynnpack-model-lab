from __future__ import annotations

import unittest
from unittest import mock

import torch

from ynnpack_assets.torchao_weight_quantization import (
    quantize_symmetric_,
    quantize_symmetric_module_,
    quantize_symmetric_weight,
    symmetric_weight_bounds,
)


class SymmetricWeightQuantizationTest(unittest.TestCase):
    def test_affine_uses_dtype_specific_endpoints_and_absmax_scale(self):
        from torchao.quantization.granularity import PerAxis, PerGroup

        for bits in (2, 4, 8):
            target_dtype = getattr(torch, f"int{bits}")
            qmin, qmax = {2: (-2, 1), 4: (-8, 7), 8: (-127, 127)}[bits]
            scale_divisor = (qmax - qmin) / 2
            for granularity in (PerAxis(0), PerGroup(4)):
                with self.subTest(bits=bits, granularity=granularity):
                    weight = scale_divisor * torch.tensor([
                        [-1.0, 1.0, 0.0, 0.5, -2.0, 2.0, 0.0, 1.0],
                        [-4.0, 4.0, 0.0, 2.0, -8.0, 8.0, 0.0, 4.0],
                    ])
                    before = weight.clone()
                    quantized = quantize_symmetric_weight(
                        weight, target_dtype=target_dtype, granularity=granularity,
                    )
                    self.assertEqual(quantized.qdata.min().item(), qmin)
                    self.assertEqual(quantized.qdata.max().item(), qmax)
                    self.assertEqual(torch.count_nonzero(quantized.zero_point).item(), 0)
                    expected_scale = (
                        torch.tensor([[2.0], [8.0]]) if isinstance(granularity, PerAxis)
                        else torch.tensor([[1.0, 2.0], [4.0, 8.0]])
                    )
                    torch.testing.assert_close(quantized.scale, expected_scale)
                    torch.testing.assert_close(weight, before, rtol=0, atol=0)

    def test_negative_dominant_weights_are_requantized_from_float(self):
        from torchao.quantization.granularity import PerAxis

        weight = torch.tensor([[-1.0, 0.5, 0.0, 0.25]])
        for bits in (2, 4, 8):
            with self.subTest(bits=bits):
                qmin, qmax = {2: (-2, 1), 4: (-8, 7), 8: (-127, 127)}[bits]
                expected_scale = torch.tensor(2.0 / (qmax - qmin))
                quantized = quantize_symmetric_weight(
                    weight, target_dtype=getattr(torch, f"int{bits}"), granularity=PerAxis(0),
                )
                expected_qdata = torch.round(weight / expected_scale).clamp(qmin, qmax).to(torch.int8)
                torch.testing.assert_close(quantized.qdata, expected_qdata, rtol=0, atol=0)
                self.assertEqual(quantized.scale.item(), expected_scale.item())
                torch.testing.assert_close(quantized.dequantize(), expected_qdata.float() * expected_scale)

    def test_lowbit_generation_matches_stock_torchao(self):
        from torchao.quantization.granularity import PerAxis, PerGroup
        from torchao.quantization.quantize_.workflows import IntxChooseQParamsAlgorithm
        from torchao.quantization.quantize_.workflows.intx.intx_unpacked_to_int8_tensor import (
            IntxUnpackedToInt8Tensor,
        )

        weight = torch.tensor([
            [-1.0, -0.8, -0.7, 0.45, 0.55, 0.9, 0.0, 0.0],
            [-3.0, 0.2, 0.1, 0.0, 0.01, -0.01, 0.0, 0.0],
        ])
        for bits in (2, 4):
            target_dtype = getattr(torch, f"int{bits}")
            for granularity, block_size in ((PerAxis(0), (1, 8)), (PerGroup(4), (1, 4))):
                for algorithm in (IntxChooseQParamsAlgorithm.AFFINE, IntxChooseQParamsAlgorithm.HQQ_SCALE_ONLY):
                    with self.subTest(bits=bits, granularity=granularity, algorithm=algorithm):
                        expected = IntxUnpackedToInt8Tensor.from_hp(
                            weight, block_size, target_dtype,
                            intx_choose_qparams_algorithm=algorithm,
                        )
                        actual = quantize_symmetric_weight(
                            weight, target_dtype=target_dtype, granularity=granularity,
                            algorithm=algorithm,
                        )
                        torch.testing.assert_close(actual.qdata, expected.qdata, rtol=0, atol=0)
                        torch.testing.assert_close(actual.scale, expected.scale, rtol=0, atol=0)
                        torch.testing.assert_close(actual.zero_point, expected.zero_point, rtol=0, atol=0)

    def test_zero_rows_and_source_scale_dtypes(self):
        from torchao.quantization.granularity import PerAxis

        for source_dtype in (torch.float16, torch.bfloat16, torch.float32):
            for scale_dtype in (torch.float16, torch.bfloat16, torch.float32):
                with self.subTest(source=source_dtype, scale=scale_dtype):
                    weight = torch.tensor([[0.0, 0.0], [-0.01, 0.01]], dtype=source_dtype)
                    quantized = quantize_symmetric_weight(
                        weight, target_dtype=torch.int8, granularity=PerAxis(0), scale_dtype=scale_dtype,
                    )
                    self.assertEqual(quantized.dtype, source_dtype)
                    self.assertEqual(quantized.scale.dtype, scale_dtype)
                    self.assertTrue(bool(torch.isfinite(quantized.scale).all()))
                    self.assertTrue(bool((quantized.scale > 0).all()))
                    self.assertEqual(torch.count_nonzero(quantized.qdata[0]).item(), 0)
                    self.assertGreaterEqual(quantized.qdata.min().item(), -127)
                    self.assertLessEqual(quantized.qdata.max().item(), 127)

    def test_no_clipping_mapping_is_preserved_by_weight_and_dynamic_recipes(self):
        from torchao.quantization import (
            Int8DynamicActivationIntxWeightConfig,
            IntxWeightOnlyConfig,
            quantize_,
        )
        from torchao.quantization.granularity import PerAxis
        from torchao.quantization.quant_primitives import MappingType
        from torchao.quantization.quantize_.workflows import IntxChooseQParamsAlgorithm

        # Include negative-dominant and positive-dominant rows. With full
        # low-bit bounds, this mapping has different scales from SYMMETRIC.
        weight = torch.tensor([[-8.0, -6.0, -5.0, 1.0], [4.0, 2.0, -1.0, -3.0]])
        for bits in (2, 4):
            dtype = getattr(torch, f"int{bits}")
            for algorithm in (IntxChooseQParamsAlgorithm.AFFINE, IntxChooseQParamsAlgorithm.HQQ_SCALE_ONLY):
                for dynamic in (False, True):
                    with self.subTest(bits=bits, algorithm=algorithm, dynamic=dynamic):
                        config = (
                            Int8DynamicActivationIntxWeightConfig(
                                weight_dtype=dtype, weight_granularity=PerAxis(0),
                                weight_scale_dtype=torch.float32,
                                weight_mapping_type=MappingType.SYMMETRIC_NO_CLIPPING_ERR,
                                intx_choose_qparams_algorithm=algorithm, version=2,
                            ) if dynamic else IntxWeightOnlyConfig(
                                weight_dtype=dtype, granularity=PerAxis(0),
                                scale_dtype=torch.float32,
                                mapping_type=MappingType.SYMMETRIC_NO_CLIPPING_ERR,
                                intx_choose_qparams_algorithm=algorithm, version=2,
                            )
                        )
                        expected, actual = (torch.nn.Linear(4, 2, bias=False) for _ in range(2))
                        with torch.no_grad():
                            expected.weight.copy_(weight)
                            actual.weight.copy_(weight)
                        quantize_(expected, config)
                        quantize_symmetric_module_(actual, config)
                        torch.testing.assert_close(actual.weight.qdata, expected.weight.qdata, rtol=0, atol=0)
                        torch.testing.assert_close(actual.weight.scale, expected.weight.scale, rtol=0, atol=0)
                        torch.testing.assert_close(actual.weight.zero_point, expected.weight.zero_point, rtol=0, atol=0)
                        self.assertEqual(actual.weight.activation_quantization, expected.weight.activation_quantization)
                        if algorithm == IntxChooseQParamsAlgorithm.AFFINE:
                            default_mapping = quantize_symmetric_weight(
                                weight, target_dtype=dtype, granularity=PerAxis(0),
                            )
                            self.assertFalse(torch.equal(actual.weight.scale, default_mapping.scale))

    def test_chunking_keeps_results_and_handles_noncontiguous_weights(self):
        from torchao.quantization.granularity import PerGroup

        weight = torch.arange(-80, 80, dtype=torch.float32).reshape(8, 20).t()
        original = weight.clone()
        full = quantize_symmetric_weight(weight, target_dtype=torch.int4, granularity=PerGroup(4))
        with mock.patch("ynnpack_assets.torchao_weight_quantization._MAX_CHUNK_ELEMENTS", 16):
            chunked = quantize_symmetric_weight(weight, target_dtype=torch.int4, granularity=PerGroup(4))
        torch.testing.assert_close(chunked.qdata, full.qdata, rtol=0, atol=0)
        torch.testing.assert_close(chunked.scale, full.scale, rtol=0, atol=0)
        torch.testing.assert_close(weight, original, rtol=0, atol=0)

    def test_hqq_retains_algorithm_with_dtype_specific_bounds(self):
        from torchao.quantization.granularity import PerAxis
        from torchao.quantization.quant_primitives import _choose_qparams_and_quantize_scale_only_hqq
        from torchao.quantization.quantize_.workflows import IntxChooseQParamsAlgorithm

        weight = torch.tensor([[-1.0, -0.8, -0.7, 0.45, 0.55, 0.9]])
        for bits in (2, 4, 8):
            with self.subTest(bits=bits):
                qmin, qmax = symmetric_weight_bounds(getattr(torch, f"int{bits}"))
                expected_qdata, expected_scale = _choose_qparams_and_quantize_scale_only_hqq(
                    weight, (1, 6), qmin, qmax,
                )
                quantized = quantize_symmetric_weight(
                    weight, target_dtype=getattr(torch, f"int{bits}"), granularity=PerAxis(0),
                    algorithm=IntxChooseQParamsAlgorithm.HQQ_SCALE_ONLY,
                )
                torch.testing.assert_close(quantized.qdata, expected_qdata.to(torch.int8), rtol=0, atol=0)
                torch.testing.assert_close(quantized.scale, expected_scale, rtol=0, atol=0)
                self.assertGreaterEqual(quantized.qdata.min().item(), qmin)
                self.assertLessEqual(quantized.qdata.max().item(), qmax)
                self.assertEqual(torch.count_nonzero(quantized.zero_point).item(), 0)
                if bits == 2:
                    self.assertLess(quantized.scale.item(), weight.abs().max().item())

    def test_hqq_unavailable_fails_without_affine_fallback(self):
        from torchao.quantization.granularity import PerAxis
        from torchao.quantization.quantize_.workflows import IntxChooseQParamsAlgorithm

        with mock.patch(
            "ynnpack_assets.torchao_weight_quantization._hqq_with_bounds",
            side_effect=RuntimeError("HQQ unavailable"),
        ):
            with self.assertRaisesRegex(RuntimeError, "HQQ unavailable"):
                quantize_symmetric_weight(
                    torch.ones(2, 4), target_dtype=torch.int2, granularity=PerAxis(0),
                    algorithm=IntxChooseQParamsAlgorithm.HQQ_SCALE_ONLY,
                )

    def test_legacy_int8_tensor_retains_weight_only_forward(self):
        from torchao.quantization import Int8WeightOnlyConfig

        linear = torch.nn.Linear(32, 5)
        quantize_symmetric_module_(linear, Int8WeightOnlyConfig(version=2))
        self.assertEqual(type(linear.weight).__name__, "Int8Tensor")
        self.assertGreaterEqual(linear.weight.qdata.min().item(), -127)
        sample = torch.randn(3, 32)
        expected = torch.nn.functional.linear(sample, linear.weight.dequantize(), linear.bias)
        torch.testing.assert_close(linear(sample), expected, rtol=1e-5, atol=1e-6)

    def test_recipe_scale_dtype_defaults_are_preserved(self):
        from torchao.quantization import Int8WeightOnlyConfig, IntxWeightOnlyConfig

        for dtype in (torch.float16, torch.bfloat16, torch.float32):
            with self.subTest(dtype=dtype):
                legacy = torch.nn.Linear(32, 4, dtype=dtype)
                quantize_symmetric_module_(legacy, Int8WeightOnlyConfig(version=2))
                self.assertEqual(legacy.weight.scale.dtype, torch.float32)
                self.assertEqual(legacy.weight.dtype, dtype)
                native = torch.nn.Embedding(4, 32, dtype=dtype)
                quantize_symmetric_module_(native, IntxWeightOnlyConfig(scale_dtype=None, version=2))
                self.assertEqual(native.weight.scale.dtype, dtype)
                self.assertEqual(native.weight.dtype, dtype)

    def test_embedding_int8_and_int4_forward(self):
        from torchao.quantization import IntxWeightOnlyConfig
        from torchao.quantization.granularity import PerAxis

        for dtype in (torch.int8, torch.int4):
            with self.subTest(dtype=dtype):
                embedding = torch.nn.Embedding(7, 32)
                config = IntxWeightOnlyConfig(weight_dtype=dtype, granularity=PerAxis(0), version=2)
                quantize_symmetric_module_(embedding, config)
                self.assertEqual(type(embedding.weight).__name__, "IntxUnpackedToInt8Tensor")
                self.assertIsNone(embedding.weight.activation_quantization)
                indices = torch.tensor([[0, 3, 6]])
                expected = torch.nn.functional.embedding(indices, embedding.weight.dequantize())
                torch.testing.assert_close(embedding(indices), expected, rtol=0, atol=0)

    def test_dynamic_activation_policy_unchanged(self):
        from torchao.quantization import Int8DynamicActivationIntxWeightConfig
        from torchao.quantization.granularity import PerAxis

        linear = torch.nn.Linear(32, 5)
        config = Int8DynamicActivationIntxWeightConfig(
            weight_dtype=torch.int4, weight_granularity=PerAxis(0), weight_scale_dtype=torch.float32, version=2,
        )
        quantize_symmetric_module_(linear, config)
        self.assertEqual(linear.weight.activation_quantization, "int8_asym_per_token")
        self.assertGreaterEqual(linear.weight.qdata.min().item(), -8)
        self.assertTrue(bool(torch.isfinite(linear(torch.randn(2, 32))).all()))

    def test_module_map_and_filter_preserve_selection(self):
        from torchao.quantization import Int8WeightOnlyConfig, IntxWeightOnlyConfig, ModuleFqnToConfig
        from torchao.quantization.granularity import PerAxis

        model = torch.nn.ModuleDict({"embedding": torch.nn.Embedding(4, 32), "linear": torch.nn.Linear(32, 4), "skip": torch.nn.Linear(32, 4)})
        skip_weight = model["skip"].weight
        quantize_symmetric_(model, ModuleFqnToConfig({
            "embedding": IntxWeightOnlyConfig(weight_dtype=torch.int4, granularity=PerAxis(0), version=2),
            "linear": Int8WeightOnlyConfig(version=2),
            "skip": None,
        }))
        self.assertEqual(model["embedding"].weight.target_dtype, torch.int4)
        self.assertEqual(type(model["linear"].weight).__name__, "Int8Tensor")
        self.assertIs(model["skip"].weight, skip_weight)
        other = torch.nn.Sequential(torch.nn.Linear(32, 4), torch.nn.Linear(4, 3))
        quantize_symmetric_(other, Int8WeightOnlyConfig(version=2), filter_fn=lambda module, name: name == "0")
        self.assertEqual(type(other[0].weight).__name__, "Int8Tensor")
        self.assertIs(type(other[1].weight), torch.nn.Parameter)

    def test_existing_weights_are_validated_without_mutation(self):
        from torchao.quantization import IntxWeightOnlyConfig
        from torchao.quantization.granularity import PerAxis

        for bits, minimum, rejected in ((2, -2, -3), (4, -8, -9), (8, -127, -128)):
            with self.subTest(bits=bits):
                module = torch.nn.Linear(4, 2)
                config = IntxWeightOnlyConfig(
                    weight_dtype=getattr(torch, f"int{bits}"), granularity=PerAxis(0), version=2,
                )
                quantize_symmetric_module_(module, config)
                original = module.weight
                module.weight.qdata[0, 0] = minimum
                before = module.weight.qdata.clone()
                quantize_symmetric_module_(module, config)
                self.assertIs(module.weight, original)
                torch.testing.assert_close(module.weight.qdata, before, rtol=0, atol=0)
                module.weight.qdata[0, 0] = rejected
                with self.assertRaisesRegex(ValueError, "original floating weights"):
                    quantize_symmetric_module_(module, config)
                self.assertEqual(module.weight.qdata[0, 0].item(), rejected)
                module.weight.qdata[0, 0] = minimum
                module.weight.zero_point[0, 0] = 1
                with self.assertRaisesRegex(ValueError, "zero point zero"):
                    quantize_symmetric_module_(module, config)

    def test_invalid_inputs_are_rejected(self):
        from torchao.quantization.granularity import PerAxis
        from torchao.quantization.quant_primitives import MappingType

        for dtype in (torch.int1, torch.uint8, torch.float32):
            with self.subTest(dtype=dtype), self.assertRaises(ValueError):
                symmetric_weight_bounds(dtype)
        for value in (float("nan"), float("inf"), float("-inf")):
            with self.subTest(value=value), self.assertRaisesRegex(ValueError, "NaN or infinity"):
                quantize_symmetric_weight(torch.tensor([[value]]), target_dtype=torch.int4, granularity=PerAxis(0))
        with self.assertRaisesRegex(ValueError, "2-D"):
            quantize_symmetric_weight(torch.ones(4), target_dtype=torch.int4, granularity=PerAxis(0))
        with self.assertRaisesRegex(ValueError, "zero point zero"):
            quantize_symmetric_weight(
                torch.ones(2, 4), target_dtype=torch.int4, granularity=PerAxis(0),
                mapping_type=MappingType.ASYMMETRIC,
            )


if __name__ == "__main__":
    unittest.main()
