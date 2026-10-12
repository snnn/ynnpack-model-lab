// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstddef>
#include <cstdint>

// Only the SentencePiece engine crosses this boundary. Rust owns manifests,
// validation, policy and provenance. Borrowed output lives until the next call
// on the same handle or its destruction; Rust copies it before either happens.
struct LabSentencePiece;
extern "C" {
int32_t lab_sp_create(const uint8_t* data, size_t size, LabSentencePiece** out,
                      int32_t* vocab, char* error, size_t error_size) noexcept;
int32_t lab_sp_encode(LabSentencePiece*, const uint8_t* text, size_t size,
                      const int32_t** ids, size_t* count, char* error,
                      size_t error_size) noexcept;
int32_t lab_sp_decode(LabSentencePiece*, const int32_t* ids, size_t count,
                      const uint8_t** text, size_t* size, char* error,
                      size_t error_size) noexcept;
void lab_sp_delete(LabSentencePiece*) noexcept;
}
