# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Explicit native control plans for adapter benchmarks."""
def packed_transpose_control(bits, rows, cols):
    if bits not in (2, 4) or not 0 < rows <= 8192 or not 0 < cols <= 8192:
        raise ValueError('Unsupported packed transpose benchmark geometry')
    return f'''ynn 1 resource_contract=1 completion_contract=1 {{
input x: storage<packed_i{bits}[{rows}, {cols}]>;
value y: storage<packed_i{bits}[{cols}, {rows}]>;
value expanded: storage<int8[{rows}, {cols}]>;
value transposed: storage<int8[{cols}, {rows}]>;
output y;
PackedRoute(route="copy", inputs=[x], output=expanded, shape=[{rows}, {cols}], attributes=[], starts=[], axis=0, mode=0);
Transpose(input=expanded, output=transposed, permutation=[1, 0]);
PackedRoute(route="copy", inputs=[transposed], output=y, shape=[{cols}, {rows}], attributes=[], starts=[], axis=0, mode=0);
}}
'''
