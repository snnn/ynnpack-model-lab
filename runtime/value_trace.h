// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "runtime/options.h"
#include "runtime/ynnpack_support.h"

namespace lab {
// Optional diagnostic outputs. They can inhibit backend fusions, so this is
// deliberately enabled only in separate trace executables, never benchmarks.
class ValueTrace {
 public:
  ValueTrace(lab_ynn::Graph& graph, const std::string& plan) : graph_(graph) {
    std::ifstream f(plan);
    if (!f) throw std::invalid_argument("Cannot read trace plan: " + plan);
    for (std::string line; std::getline(f, line);) {
      if (line.empty() || line[0] == '#') continue;
      const auto v = Split(line, '\t');
      if (v.size() != 5 || v[0].empty() ||
          v[0].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRS"
                                 "TUVWXYZ0123456789_.-") != std::string::npos ||
          (v[2] != "f32" && v[2] != "bf16" && v[2] != "i8") ||
          (v[4] != "input" && v[4] != "output"))
        throw std::invalid_argument("Invalid trace plan record");
      if (items_.count(v[0]))
        throw std::invalid_argument("Duplicate trace label");
      size_t end;
      const size_t bytes = std::stoull(v[3], &end);
      if (end != v[3].size() || !bytes || bytes > 256 * 1024 * 1024)
        throw std::invalid_argument("Invalid trace buffer size");
      items_[v[0]] = {v[1], v[2]};
      graph_.ExposeForInspection(v[1]);
      if (v[4] == "output") {
        auto& b = buffers_[v[1]];
        b.resize(std::max(b.size(), (bytes + 63) / sizeof(uint64_t)));
      }
    }
  }
  void Bind() {
    for (auto& [name, data] : buffers_)
      graph_.Bind(name, data.data(), data.size() * sizeof(uint64_t));
  }
  void Save(const std::string& directory) const {
    if (!std::filesystem::create_directories(directory))
      throw std::invalid_argument("Trace output directory already exists");
    std::ofstream metadata(directory + "/values.tsv");
    for (const auto& [label, item] : items_) {
      const auto& buffer = graph_.InspectionBuffer(item.name);
      const size_t width = item.dtype == "f32"    ? 4
                           : item.dtype == "bf16" ? 2
                                                  : 1;
      if (buffer.elem_size != width)
        throw std::runtime_error("Trace type mismatch");
      slinky::buffer<void, 8> dense(buffer);
      size_t stride = width;
      for (size_t d = 0; d < dense.rank; ++d) {
        dense.mutable_dim(d).set_stride(stride);
        dense.mutable_dim(d).set_fold_factor(slinky::dim::unfolded);
        stride *= dense.dim(d).extent();
      }
      std::vector<uint64_t> storage((dense.size_bytes() + 7) / 8);
      static_cast<slinky::raw_buffer&>(dense).base = storage.data();
      slinky::copy(buffer, dense);
      const auto file = label + "." + item.dtype;
      std::ofstream out(directory + "/" + file, std::ios::binary);
      if (!out.write(static_cast<const char*>(dense.base()),
                     dense.size_bytes()))
        throw std::runtime_error("Trace write failed");
      metadata << label << '\t' << item.name << '\t' << item.dtype << '\t';
      for (int d = buffer.rank - 1; d >= 0; --d)
        metadata << (d == buffer.rank - 1 ? "" : ",") << buffer.dim(d).extent();
      metadata << '\n';
    }
  }

 private:
  struct Item {
    std::string name, dtype;
  };
  lab_ynn::Graph& graph_;
  std::map<std::string, Item> items_;
  std::map<std::string, std::vector<uint64_t>> buffers_;
};
}  // namespace lab
