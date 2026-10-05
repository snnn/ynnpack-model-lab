// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstring>
#include <set>

#include "runtime/model_assets.h"
#include "runtime/sha256.h"

namespace lab {
// The Python safetensors reader validates headers/indexes and writes spans.
// This provider checks those spans, hashes the used payloads, and maps each
// original shard once. The asset directory must remain immutable while mapped.
class TensorProvider {
 public:
  TensorProvider(std::string source, std::string manifest, std::string cache,
                 std::string parameters)
      : manifest_(ReadJson(manifest)),
        tensors_(Field<Object>(manifest_, "tensors")),
        source_(std::move(source)),
        cache_(std::move(cache)),
        files_(source_, std::move(parameters)),
        derived_(cache_, cache_) {}
  const Object& manifest() const { return manifest_; }
  Object Record(const std::string& name) const {
    return Field<Object>(tensors_, name);
  }
  const uint8_t* Raw(const std::string& name) {
    const auto rec = Record(name);
    const auto file = Field<std::string>(rec, "file");
    const auto shard = Field<Object>(Field<Object>(manifest_, "shards"), file);
    const size_t offset = Integer(rec, "offset"), n = Integer(rec, "bytes");
    const size_t total = Integer(shard, "bytes");
    if (!n || offset > total || n > total - offset)
      throw std::invalid_argument("Tensor span out of bounds: " + name);
    const auto* p =
        static_cast<const uint8_t*>(files_.Get(file.c_str(), total)) + offset;
    if (!verified_.count(name)) {
      if (Sha256::Digest(p, n) != Field<std::string>(rec, "sha256"))
        throw std::runtime_error("Tensor hash mismatch: " + name);
      verified_.insert(name);
    }
    return p;
  }
  const void* Get(const char* path, size_t bytes) {
    const std::string key(path);
    if (key.rfind("@parameters/", 0) == 0) {
      const void* data = files_.Get(path, bytes);
      if (!verified_.count(key)) {
        if (key.substr(12) != Sha256::Digest(data, bytes) + ".bin")
          throw std::runtime_error("Parameter hash mismatch");
        verified_.insert(key);
      }
      return data;
    }
    if (key.rfind("@hf/", 0) != 0)
      throw std::invalid_argument("Unknown tensor provider");
    const auto name = key.substr(4);
    const auto rec = Record(name);
    if (Integer(rec, "bytes") != bytes)
      throw std::invalid_argument("Tensor size mismatch");
    const auto* data = Raw(name);
    if (Field<std::string>(rec, "encoding") == "identity") {
      // Safetensors guarantees bounds, not C++ pointer alignment. Coefficients
      // can begin at offset 2 mod 4. Copy only such small misaligned constants.
      if (reinterpret_cast<uintptr_t>(data) % 4 &&
          Field<std::string>(rec, "dtype") == "F32") {
        auto& storage = aligned_[name];
        if (storage.empty()) {
          storage.resize((bytes + 7) / 8);
          std::memcpy(storage.data(), data, bytes);
        }
        return storage.data();
      }
      return data;
    }
    if (Field<std::string>(rec, "encoding") != "offset_binary_low_first")
      throw std::invalid_argument("Unknown tensor encoding");
    const auto bits = Integer(rec, "bits");
    if (bits != 2 && bits != 4)
      throw std::invalid_argument("Unknown packed width");
    const uint8_t xor_mask = bits == 2 ? 0xaa : 0x88;
    const auto hash = Field<std::string>(rec, "sha256");
    if (hash.size() != 64 ||
        hash.find_first_not_of("0123456789abcdef") != std::string::npos)
      throw std::invalid_argument("Invalid tensor hash");
    const auto filename = hash + ".signed" + std::to_string(bits) + "-v1.bin";
    const auto full = cache_ + "/" + filename;
    if (!std::filesystem::exists(full)) {
      std::filesystem::create_directories(cache_);
      std::string pattern = full + ".tmp-XXXXXX";
      std::vector<char> temp(pattern.begin(), pattern.end());
      temp.push_back(0);
      int fd = mkstemp(temp.data());
      if (fd < 0) throw std::runtime_error("Cannot create derived cache");
      try {
        std::array<uint8_t, 65536> block;
        for (size_t at = 0; at < bytes;) {
          const size_t n = std::min(block.size(), bytes - at);
          for (size_t i = 0; i < n; ++i) block[i] = data[at + i] ^ xor_mask;
          size_t written = 0;
          while (written < n) {
            const auto result = write(fd, block.data() + written, n - written);
            if (result <= 0)
              throw std::runtime_error("Derived cache write failed");
            written += result;
          }
          at += n;
        }
        const int status = close(fd);
        fd = -1;
        if (status) throw std::runtime_error("Derived cache close failed");
        std::filesystem::rename(temp.data(), full);
      } catch (...) {
        if (fd >= 0) close(fd);
        unlink(temp.data());
        throw;
      }
    }
    const auto* converted =
        static_cast<const uint8_t*>(derived_.Get(filename.c_str(), bytes));
    if (!verified_derived_.count(filename)) {
      // Verify by reversing the recode; cache truncation/staleness/corruption
      // must never silently change the checkpoint.
      Sha256 h;
      std::array<uint8_t, 65536> block;
      for (size_t at = 0; at < bytes;) {
        const size_t n = std::min(block.size(), bytes - at);
        for (size_t i = 0; i < n; ++i) block[i] = converted[at + i] ^ xor_mask;
        h.Update(block.data(), n);
        at += n;
      }
      if (h.Finish() != hash)
        throw std::runtime_error("Corrupt derived cache: " + full);
      verified_derived_.insert(filename);
    }
    return converted;
  }

 private:
  Object manifest_, tensors_;
  std::string source_, cache_;
  Weights files_, derived_;
  std::set<std::string> verified_, verified_derived_;
  std::map<std::string, std::vector<uint64_t>> aligned_;
};
}  // namespace lab
