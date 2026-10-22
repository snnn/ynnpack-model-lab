"""TorchAO weight quantization with the converter's signed integer ranges.

INT8 weights use [-127, 127]; INT4 and INT2 retain their full signed ranges,
[-8, 7] and [-2, 1]. All use symmetric mapping with zero point zero. Bounds
apply while quantizing the original floating weights, never by clipping an
already quantized tensor.
"""

from __future__ import annotations

from typing import Any, Callable

import torch


# Limit floating temporaries while quantizing large embeddings. The returned
# integer data and per-block scales necessarily cover the complete weight.
_MAX_CHUNK_ELEMENTS = 1 << 20
_FLOAT_DTYPES = (torch.float16, torch.bfloat16, torch.float32)


def symmetric_weight_bounds(target_dtype: torch.dtype) -> tuple[int, int]:
    """Return the converter's bounds for zero-point-zero weight quantization.

    INT2 and INT4 use the full signed range. Other supported widths retain
    equal positive and negative bounds, including INT8's [-127, 127].
    """
    for bits in range(2, 9):
        if target_dtype == getattr(torch, f"int{bits}", None):
            qmax = (1 << (bits - 1)) - 1
            return (-qmax - 1 if bits in (2, 4) else -qmax), qmax
    raise ValueError(f"Expected a signed INT2 through INT8 weight dtype, got {target_dtype}")


def _hqq_with_bounds(
    weight: torch.Tensor, block_size: tuple[int, ...], qmin: int, qmax: int
) -> tuple[torch.Tensor, torch.Tensor]:
    # TorchAO's public tensor factories infer full-range bounds from the dtype.
    # Its existing scale-only HQQ primitive accepts explicit bounds, but is not
    # public. Keep this version-dependent access isolated and fail explicitly
    # if it disappears; an affine fallback would change the requested recipe.
    try:
        from torchao.quantization.quant_primitives import (
            _choose_qparams_and_quantize_scale_only_hqq,
        )
    except ImportError as exc:
        raise RuntimeError(
            "This TorchAO version lacks HQQ_SCALE_ONLY with explicit integer bounds"
        ) from exc
    return _choose_qparams_and_quantize_scale_only_hqq(weight, block_size, qmin, qmax)


@torch.no_grad()
def quantize_symmetric_weight(
    weight: torch.Tensor,
    *,
    target_dtype: torch.dtype,
    granularity: Any,
    scale_dtype: torch.dtype | None = torch.float32,
    activation_quantization: Any = None,
    algorithm: Any = None,
    mapping_type: Any = None,
    tensor_type: str = "intx",
) -> torch.Tensor:
    """Quantize original 2-D floating weights without mutating their storage.

    ``tensor_type='int8'`` preserves the tensor representation used by
    Int8WeightOnlyConfig; ``'intx'`` preserves export-oriented INTx tensors and
    their optional activation quantization. Default symmetric affine scales are
    absmax/((qmax-qmin)/2): absmax/127 for INT8, absmax/7.5 for INT4, and
    absmax/1.5 for INT2. SYMMETRIC_NO_CLIPPING_ERR retains TorchAO's separate
    positive and negative endpoint scaling. HQQ_SCALE_ONLY retains TorchAO's
    iterative scale optimization, independent of mapping_type, with the
    selected integer bounds.
    """
    from torchao.quantization.quant_primitives import (
        MappingType,
        choose_qparams_affine,
        quantize_affine,
    )
    from torchao.quantization.quantize_.workflows import IntxChooseQParamsAlgorithm
    from torchao.quantization.quantize_.workflows.int8.int8_tensor import Int8Tensor
    from torchao.quantization.quantize_.workflows.intx.intx_unpacked_to_int8_tensor import (
        IntxUnpackedToInt8Tensor,
    )
    from torchao.quantization.utils import get_block_size

    qmin, qmax = symmetric_weight_bounds(target_dtype)
    if type(weight) not in (torch.Tensor, torch.nn.Parameter):
        raise TypeError("Symmetric quantization requires original floating weights, not a tensor subclass")
    if weight.dtype not in _FLOAT_DTYPES or weight.ndim != 2 or weight.numel() == 0:
        raise ValueError("Symmetric weight quantization requires a nonempty 2-D FP16, BF16, or FP32 tensor")
    if tensor_type not in ("int8", "intx"):
        raise ValueError(f"Unsupported quantized tensor representation: {tensor_type}")
    if tensor_type == "int8" and (target_dtype != torch.int8 or activation_quantization is not None):
        raise ValueError("The int8 tensor representation is only supported for INT8 weight-only quantization")
    scale_dtype = weight.dtype if scale_dtype is None else scale_dtype
    if scale_dtype not in _FLOAT_DTYPES:
        raise ValueError(f"Unsupported weight scale dtype: {scale_dtype}")
    algorithm = IntxChooseQParamsAlgorithm.AFFINE if algorithm is None else algorithm
    if algorithm not in (IntxChooseQParamsAlgorithm.AFFINE, IntxChooseQParamsAlgorithm.HQQ_SCALE_ONLY):
        raise ValueError(f"Unsupported symmetric weight quantization algorithm: {algorithm}")
    mapping_type = MappingType.SYMMETRIC if mapping_type is None else mapping_type
    if mapping_type not in (MappingType.SYMMETRIC, MappingType.SYMMETRIC_NO_CLIPPING_ERR):
        raise ValueError("Integer weight quantization requires symmetric mapping with zero point zero")

    block_size = tuple(get_block_size(tuple(weight.shape), granularity))
    if len(block_size) != 2 or block_size[0] != 1:
        raise ValueError("Symmetric weight quantization requires row-wise PerAxis(0), PerRow(), or PerGroup granularity")
    if any(block <= 0 or size % block for size, block in zip(weight.shape, block_size)):
        raise ValueError(f"Weight shape {tuple(weight.shape)} is not divisible by block size {block_size}")
    nrows, ncols = weight.shape
    scale_shape = (nrows, ncols // block_size[1])
    qdata = torch.empty(weight.shape, dtype=torch.int8, device=weight.device)
    scale = torch.empty(scale_shape, dtype=scale_dtype, device=weight.device)
    zero_point = torch.zeros(scale_shape, dtype=torch.int8, device=weight.device)
    rows_per_chunk = max(1, _MAX_CHUNK_ELEMENTS // ncols)
    for start in range(0, nrows, rows_per_chunk):
        end = min(nrows, start + rows_per_chunk)
        chunk = weight.detach()[start:end].to(torch.float32)
        if not bool(torch.isfinite(chunk).all()):
            raise ValueError("Cannot quantize weights containing NaN or infinity")
        if algorithm == IntxChooseQParamsAlgorithm.HQQ_SCALE_ONLY:
            chunk_qdata, chunk_scale = _hqq_with_bounds(chunk, block_size, qmin, qmax)
            chunk_scale = chunk_scale.to(scale_dtype)
            # Re-round with the stored scale if it lost precision. The scale
            # still comes from HQQ and uses the selected integer bounds.
            if scale_dtype != torch.float32:
                chunk_qdata = quantize_affine(
                    chunk, block_size, chunk_scale, zero_point[start:end],
                    output_dtype=torch.int8, quant_min=qmin, quant_max=qmax,
                )
        else:
            chunk_scale, chunk_zero = choose_qparams_affine(
                chunk, mapping_type, block_size, torch.int8,
                quant_min=qmin, quant_max=qmax, scale_dtype=scale_dtype,
                zero_point_dtype=torch.int8, keepdim=True,
                eps=torch.finfo(torch.float32).eps,
            )
            chunk_qdata = quantize_affine(
                chunk, block_size, chunk_scale, chunk_zero,
                output_dtype=torch.int8, quant_min=qmin, quant_max=qmax,
            )
        if not bool(torch.isfinite(chunk_scale).all()) or not bool((chunk_scale > 0).all()):
            raise ValueError(f"Weight scales cannot be represented as finite positive {scale_dtype} values")
        qdata[start:end].copy_(chunk_qdata)
        scale[start:end].copy_(chunk_scale)

    if tensor_type == "int8":
        return Int8Tensor(qdata, scale, list(block_size), weight.dtype, zero_point=zero_point)
    return IntxUnpackedToInt8Tensor(
        qdata=qdata, scale=scale, zero_point=zero_point,
        target_dtype=target_dtype, block_size=block_size, dtype=weight.dtype,
        activation_quantization=activation_quantization,
    )


def _validate_existing_weight(weight: torch.Tensor, target_dtype: torch.dtype) -> None:
    """Permit repeated application without silently changing imported values."""
    actual_dtype = getattr(weight, "target_dtype", torch.int8)
    if actual_dtype != target_dtype:
        raise ValueError(f"Existing quantized weight dtype {actual_dtype} does not match requested {target_dtype}")
    qmin, qmax = symmetric_weight_bounds(actual_dtype)
    qdata = getattr(weight, "qdata", None)
    if not isinstance(qdata, torch.Tensor) or qdata.dtype != torch.int8:
        raise TypeError("Unsupported existing quantized weight representation")
    if qdata.numel():
        # Reductions operate directly on strided storage, unlike flattening,
        # which can copy a complete imported weight.
        actual_min, actual_max = torch.aminmax(qdata)
        if actual_min.item() < qmin or actual_max.item() > qmax:
            raise ValueError(
                f"Existing quantized weights exceed the supported range [{qmin}, {qmax}]; "
                "requantize from the original floating weights"
            )
    zero_point = getattr(weight, "zero_point", None)
    if zero_point is not None and bool((zero_point != 0).any()):
        raise ValueError("Existing quantized weights require zero point zero")


def quantize_symmetric_module_(
    module: torch.nn.Module, config: Any, *, parameter_name: str = "weight"
) -> torch.nn.Module:
    """Apply a supported TorchAO recipe to one module's original weight."""
    from torchao.quantization import (
        Int8DynamicActivationIntxWeightConfig,
        Int8WeightOnlyConfig,
        IntxWeightOnlyConfig,
    )
    from torchao.quantization.quant_primitives import MappingType
    from torchao.quantization.quantize_.workflows import IntxPackingFormat

    if getattr(config, "version", None) != 2:
        raise ValueError("Symmetric weight quantization requires a version 2 TorchAO recipe")
    kwargs: dict[str, Any] = {}
    if isinstance(config, Int8WeightOnlyConfig):
        # Int8Tensor.from_hp also chooses FP32 scales for every source dtype.
        kwargs.update(target_dtype=torch.int8, granularity=config.granularity, tensor_type="int8")
    elif isinstance(config, Int8DynamicActivationIntxWeightConfig):
        if config.act_mapping_type != MappingType.ASYMMETRIC:
            raise ValueError("Unsupported activation mapping for export-oriented INTx quantization")
        kwargs.update(
            target_dtype=config.weight_dtype, granularity=config.weight_granularity,
            scale_dtype=config.weight_scale_dtype,
            activation_quantization="int8_asym_per_token",
            algorithm=config.intx_choose_qparams_algorithm,
        )
    elif isinstance(config, IntxWeightOnlyConfig):
        kwargs.update(
            target_dtype=config.weight_dtype, granularity=config.granularity,
            scale_dtype=config.scale_dtype, algorithm=config.intx_choose_qparams_algorithm,
        )
    else:
        raise TypeError(f"Unsupported symmetric weight recipe: {type(config).__name__}")
    if not isinstance(config, Int8WeightOnlyConfig):
        if config.intx_packing_format != IntxPackingFormat.UNPACKED_TO_INT8:
            raise ValueError("Symmetric weight export requires UNPACKED_TO_INT8 packing")
        mapping_type = getattr(config, "weight_mapping_type", getattr(config, "mapping_type", None))
        if mapping_type not in (MappingType.SYMMETRIC, MappingType.SYMMETRIC_NO_CLIPPING_ERR):
            raise ValueError("Integer weight quantization requires symmetric mapping with zero point zero")
        kwargs["mapping_type"] = mapping_type
    weight = getattr(module, parameter_name)
    if type(weight) not in (torch.Tensor, torch.nn.Parameter):
        _validate_existing_weight(weight, kwargs["target_dtype"])
        return module
    new_weight = quantize_symmetric_weight(weight, **kwargs)
    setattr(module, parameter_name, torch.nn.Parameter(new_weight, requires_grad=False))
    return module


def quantize_symmetric_(
    model: torch.nn.Module,
    config: Any,
    filter_fn: Callable[[torch.nn.Module, str], bool] | None = None,
    *,
    parameter_name: str = "weight",
) -> None:
    """Use TorchAO's module selection with converter symmetric weight recipes."""
    from torchao.quantization import ModuleFqnToConfig, quantize_

    from ynnpack_assets.torchao_symmetric_config import SymmetricWeightConfig

    if parameter_name != "weight":
        if filter_fn is not None or isinstance(config, ModuleFqnToConfig):
            raise ValueError("A custom parameter_name is supported only for a single module recipe")
        quantize_symmetric_module_(model, config, parameter_name=parameter_name)
        return
    if isinstance(config, ModuleFqnToConfig):
        config = ModuleFqnToConfig({
            name: recipe if recipe is None or isinstance(recipe, SymmetricWeightConfig) else SymmetricWeightConfig(recipe)
            for name, recipe in config.fqn_to_config.items()
        })
    elif not isinstance(config, SymmetricWeightConfig):
        config = SymmetricWeightConfig(config)
    quantize_(model, config, filter_fn=filter_fn)
