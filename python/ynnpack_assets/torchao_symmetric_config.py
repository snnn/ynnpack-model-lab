"""TorchAO dispatch adapter for the converter's symmetric weight policy."""

from dataclasses import dataclass

from torchao.core.config import AOBaseConfig
from torchao.quantization.transform_module import register_quantize_module_handler


@dataclass
class SymmetricWeightConfig(AOBaseConfig):
    """Apply TorchAO with narrow INT8 and full-range INT4/INT2 weights.

    This is an execution adapter, not a checkpoint format. Saved HF checkpoints
    retain the wrapped standard configuration and record the weight policy
    separately so stock TorchAO can deserialize their tensor subclasses.
    """

    base_config: AOBaseConfig


@register_quantize_module_handler(SymmetricWeightConfig)
def _quantize_symmetric_module(module, config, *, parameter_name="weight"):
    from ynnpack_assets.torchao_weight_quantization import quantize_symmetric_module_

    return quantize_symmetric_module_(
        module, config.base_config, parameter_name=parameter_name
    )
