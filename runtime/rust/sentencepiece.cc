// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/rust/sentencepiece.h"

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "sentencepiece_processor.h"

struct LabSentencePiece {
  sentencepiece::SentencePieceProcessor processor;
  std::vector<int> ids;
  std::string text;
};
namespace {
void Check(const sentencepiece::util::Status& status) {
  if (!status.ok()) throw std::invalid_argument(status.ToString());
}
template <class F>
int32_t Catch(char* error, size_t size, F&& f) noexcept {
  try {
    f();
    return 0;
  } catch (const std::exception& e) {
    if (error && size) std::snprintf(error, size, "%s", e.what());
  } catch (...) {
    if (error && size)
      std::snprintf(error, size, "Unknown SentencePiece error");
  }
  return 1;
}
}  // namespace
extern "C" {
int32_t lab_sp_create(const uint8_t* data, size_t size, LabSentencePiece** out,
                      int32_t* vocab, char* error, size_t error_size) noexcept {
  *out = nullptr;
  return Catch(error, error_size, [&] {
    auto handle = std::make_unique<LabSentencePiece>();
    Check(handle->processor.LoadFromSerializedProto(
        std::string_view(reinterpret_cast<const char*>(data), size)));
    *vocab = handle->processor.GetPieceSize();
    *out = handle.release();
  });
}
int32_t lab_sp_encode(LabSentencePiece* handle, const uint8_t* text,
                      size_t size, const int32_t** ids, size_t* count,
                      char* error, size_t error_size) noexcept {
  return Catch(error, error_size, [&] {
    Check(handle->processor.Encode(
        std::string_view(reinterpret_cast<const char*>(text), size),
        &handle->ids));
    static_assert(sizeof(int) == sizeof(int32_t));
    *ids = handle->ids.data();
    *count = handle->ids.size();
  });
}
int32_t lab_sp_decode(LabSentencePiece* handle, const int32_t* ids,
                      size_t count, const uint8_t** text, size_t* size,
                      char* error, size_t error_size) noexcept {
  return Catch(error, error_size, [&] {
    Check(handle->processor.Decode(std::vector<int>(ids, ids + count),
                                   &handle->text));
    *text = reinterpret_cast<const uint8_t*>(handle->text.data());
    *size = handle->text.size();
  });
}
void lab_sp_delete(LabSentencePiece* handle) noexcept { delete handle; }
}
