// Copyright 2026 The LiteRT Authors.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// https://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#ifdef __GLIBC__
#include <malloc.h>
#endif

#include "runtime/ynnpack_support.h"

#if defined(LAB_GEMMA4_HF)
#include "gemma4_decode.h"
#include "gemma4_hf_config.h"
#include "gemma4_prefill.h"
#include "models/gemma4/hf_assets.h"
#elif defined(LAB_GENERATED_OVERRIDE)
#include "gemma4_decode.h"
#include "gemma4_prefill.h"
#elif defined(LAB_GEMMA4_E4B)
#include "models/gemma4_e4b/generated/gemma4_decode.h"
#include "models/gemma4_e4b/generated/gemma4_prefill.h"
#else
#include "models/gemma4_e2b/generated/gemma4_decode.h"
#include "models/gemma4_e2b/generated/gemma4_prefill.h"
#endif
#include "runtime/benchmark_cases.h"
#include "runtime/model_assets.h"
#include "runtime/options.h"
#if defined(LAB_ENABLE_VALUE_TRACE)
#include "runtime/value_trace.h"
#endif

namespace {
using Clock = std::chrono::steady_clock;
using Config = lab::Gemma4Config;
Config ModelConfig() {
#if defined(LAB_GEMMA4_E4B)
  return Config::E4B();
#else
  return Config::E2B();
#endif
}
lab::Options options;

double Ms(Clock::time_point start) {
  return std::chrono::duration<double, std::milli>(Clock::now() - start)
      .count();
}
long PeakRss() {
  struct rusage r{};
  getrusage(RUSAGE_SELF, &r);
  return r.ru_maxrss;
}
long Rss() {
  std::ifstream f("/proc/self/statm");
  long total = 0, resident = 0;
  f >> total >> resident;
  return resident * (sysconf(_SC_PAGESIZE) / 1024);
}
void Dump(const std::string& name, const void* ptr, size_t bytes) {
  std::ofstream f(name, std::ios::binary);
  if (!f.write(static_cast<const char*>(ptr), bytes))
    throw std::runtime_error("dump failed");
}

#if defined(LAB_GEMMA4_HF)
using Weights = lab::TensorProvider;
using ModelAssets = lab::HfModelAssets;
#if defined(LAB_HF_FLOAT_ACTIVATIONS)
using Activation = float;
#else
using Activation = uint16_t;
#endif
#else
using Weights = lab::Weights;
using ModelAssets = lab::ModelAssets;
using Activation = float;
constexpr size_t kKvElementBytes = 1;
#endif

struct Cache {
  lab::KvOwner spec;
  std::vector<int8_t> k, v;
  std::shared_ptr<lab_ynn::ResourceState> key_state, value_state;
};
class Runner {
 public:
  Runner()
#if defined(LAB_GEMMA4_HF)
      : weights_(options.hf_model_dir, options.asset_manifest,
                 options.cache_dir, options.parameter_dir),
#else
      : weights_(options.bundle_dir, options.parameter_dir),
#endif
        capacity_(options.cache_capacity),
        max_rows_(options.prefill_rows) {
#if defined(LAB_GEMMA4_HF)
    if (options.hf_model_dir.empty() || options.asset_manifest.empty() ||
        options.cache_dir.empty())
      throw std::invalid_argument(
          "HF build needs source, manifest, and derived cache paths");
#else
    if (!options.hf_model_dir.empty())
      throw std::invalid_argument(
          "Use a Gemma4 HF executable for safetensors assets");
#endif
    if (capacity_ <= 0 || capacity_ > 32768 || max_rows_ < 1 ||
        max_rows_ > 128 || options.num_threads < 1)
      throw std::invalid_argument("invalid capacity/rows/threads");
#if defined(LAB_GEMMA4_HF)
    embeddings_ = std::make_unique<ModelAssets>(weights_, kHfSourceIdentity);
#else
    embeddings_ = std::make_unique<ModelAssets>(options.bundle_dir, weights_,
                                                ModelConfig());
#endif
    for (auto s : embeddings_->owners) {
      caches_.push_back(
          {s,
           std::vector<int8_t>(kKvElementBytes * size_t(capacity_) *
                                   s.head_dim * s.num_heads +
                               64),
           std::vector<int8_t>(kKvElementBytes * size_t(capacity_) *
                                   s.head_dim * s.num_heads +
                               64)});
    }
    auto resolver = [&](const char* p, size_t n) { return weights_.Get(p, n); };
    for (int i = 0; i < 2; ++i) {
      auto at = Clock::now();
      std::cerr << "Authoring " << (i ? "decode" : "prefill") << "\n";
      graph_[i] =
          i ? BuildGemma4Decode(resolver) : BuildGemma4Prefill(resolver);
#if defined(LAB_ENABLE_VALUE_TRACE)
      if (!options.trace_plan.empty())
        trace_[i] = std::make_unique<lab::ValueTrace>(
            *graph_[i],
            options.trace_plan + (i ? "/decode.tsv" : "/prefill.tsv"));
#endif
      std::cerr << "Preparing " << i << " values, author_ms=" << Ms(at)
                << " rss_kib=" << Rss() << "\n";
      if (i && options.profile_execution == "decode")
        execution_profile_ = graph_[i]->TrackExecution();
      graph_[i]->Compile(options.num_threads);
      if (options.report_memory)
        scratch_[i] = graph_[i]->TrackScratchAllocations();
#if defined(LAB_ENABLE_VALUE_TRACE)
      if (trace_[i]) trace_[i]->Bind();
#endif
      std::cerr << "Prepared " << i << " ms=" << Ms(at) << " rss_kib=" << Rss()
                << " peak=" << PeakRss() << "\n";
      if (options.dump_pipeline) {
        std::ofstream f(options.output_dir +
                        (i ? "/decode.ir.txt" : "/prefill.ir.txt"));
        graph_[i]->Print(f);
      }
    }
    logits_.resize(ModelConfig().vocab_size + 16);
    ple_.resize(ModelConfig().num_layers);
  }
  void Reset() {
    for (auto& cache : caches_) {
      if (cache.key_state) cache.key_state->Reset();
      if (cache.value_state) cache.value_state->Reset();
    }
    position_ = 0;
  }
  int position() const { return position_; }
  const float* logits() const { return logits_.data(); }
  void Prefix(const std::vector<int32_t>& tokens) {
    for (size_t p = 0; p + 1 < tokens.size();) {
      size_t count = std::min<size_t>(max_rows_, tokens.size() - 1 - p);
      Chunk(tokens.data() + p, count, false);
      p += count;
    }
  }
  void Decode(int32_t token) { Chunk(&token, 1, true); }
  std::shared_ptr<lab_ynn::ExecutionProfile> execution_profile() const {
    return execution_profile_;
  }
  void Save(const std::string& path) const {
    Dump(path, logits_.data(), ModelConfig().vocab_size * sizeof(float));
    for (const auto& c : caches_) {
      for (int head = 0; head < c.spec.num_heads; ++head) {
        auto prefix = path + ".owner" + std::to_string(c.spec.owner);
        if (c.spec.num_heads > 1) prefix += ".head" + std::to_string(head);
        size_t offset =
            kKvElementBytes * size_t(head) * capacity_ * c.spec.head_dim;
        const std::string suffix = kKvElementBytes == 2 ? ".bf16" : ".i8";
        Dump(prefix + ".k" + suffix, c.k.data() + offset,
             kKvElementBytes * size_t(position_) * c.spec.head_dim);
        Dump(prefix + ".v" + suffix, c.v.data() + offset,
             kKvElementBytes * size_t(position_) * c.spec.head_dim);
      }
    }
  }
  lab_ynn::Counters counters() const {
    auto a = graph_[0]->counters(), b = graph_[1]->counters();
    a.append_bytes += b.append_bytes;
    a.append_calls += b.append_calls;
    a.view_copy_bytes += b.view_copy_bytes;
    return a;
  }
  void ReportMemory(const std::string& phase, std::ostream& output) const {
    // Diagnostics run outside timed regions. Root scratch is exact; libc
    // statistics describe the allocator, not which operator owns each block.
    output << "{\"phase\":\"" << phase << "\",\"rss_kib\":" << Rss()
           << ",\"peak_rss_kib\":" << PeakRss()
           << ",\"prefill_root_scratch_bytes\":"
           << graph_[0]->RetainedRootScratchBytes()
           << ",\"decode_root_scratch_bytes\":"
           << graph_[1]->RetainedRootScratchBytes();
    for (int i = 0; i < 2; ++i) {
      const char* name = i ? "decode" : "prefill";
      if (!scratch_[i]) continue;
      output << ",\"" << name
             << "_scratch_live_bytes\":" << scratch_[i]->live.load() << ",\""
             << name << "_scratch_peak_bytes\":" << scratch_[i]->peak.load()
             << ",\"" << name
             << "_scratch_allocated_bytes\":" << scratch_[i]->allocated.load()
             << ",\"" << name << "_scratch_allocation_calls\":"
             << scratch_[i]->allocations.load();
    }
#ifdef __GLIBC__
#if __GLIBC_PREREQ(2, 33)
    const auto heap = mallinfo2();
    output << ",\"libc_allocated_arena_bytes\":" << heap.uordblks
           << ",\"libc_free_arena_bytes\":" << heap.fordblks
           << ",\"libc_mmap_bytes\":" << heap.hblkhd;
#endif
#endif
    std::ifstream smaps("/proc/self/smaps_rollup");
    for (std::string line; std::getline(smaps, line);) {
      std::istringstream fields(line);
      std::string name, unit;
      size_t value;
      if (!(fields >> name >> value >> unit) || unit != "kB") continue;
      if (name == "Anonymous:" || name == "Private_Dirty:" ||
          name == "Private_Clean:" || name == "Shared_Clean:" ||
          name == "Swap:")
        output << ",\"" << name.substr(0, name.size() - 1)
               << "_kib\":" << value;
    }
    output << "}\n";
    output.flush();
  }

 private:
  std::shared_ptr<const lab_ynn::ScratchStatistics> scratch_[2];
  void Chunk(const int32_t* tokens, size_t count, bool decode) {
    if (position_ + count > capacity_)
      throw std::invalid_argument("context capacity exceeded");
    const auto config = ModelConfig();
    for (size_t i = 0; i < count; ++i)
      if (tokens[i] < 0 || tokens[i] >= config.vocab_size)
        throw std::invalid_argument("bad token");
    embedded_.resize(count * config.embed_dim);
    positions_.resize(count);
    for (auto& p : ple_) p.resize(count * config.per_layer_input_dim);
    embeddings_->token_embedding->Lookup(tokens, count, embedded_.data());
    embeddings_->emb_per_layer_table->LookupPerLayer(
        tokens, count, config.num_layers, config.per_layer_input_dim, ple_);
    auto& g = *graph_[decode];
    for (size_t i = 0; i < count; ++i) positions_[i] = position_ + i;
    g.ScalarValue("position", position_);
    g.Bind("embedded_input", embedded_.data(),
           embedded_.size() * sizeof(Activation),
           {1, count, size_t(config.embed_dim)});
    g.Bind("positions", positions_.data(), positions_.size() * sizeof(float),
           {1, 1, count, 1});
    for (int i = 0; i < config.num_layers; ++i) {
      auto name = "per_layer_token_embedding_" + std::to_string(i);
      if (g.Has(name))
        g.Bind(name, ple_[i].data(), ple_[i].size() * sizeof(Activation),
               {1, count, size_t(config.per_layer_input_dim)});
    }
    size_t expected_bytes = 0;
    for (auto& c : caches_) {
      auto shape =
          std::vector<size_t>{1, size_t(c.spec.num_heads), size_t(capacity_),
                              size_t(c.spec.head_dim)};
      const auto key_name = "cache_key_" + std::to_string(c.spec.owner);
      const auto value_name = "cache_value_" + std::to_string(c.spec.owner);
      if (!c.key_state)
        c.key_state =
            g.NewResourceState(key_name, c.k.data(), c.k.size(), shape);
      if (!c.value_state)
        c.value_state =
            g.NewResourceState(value_name, c.v.data(), c.v.size(), shape);
      g.BindResource(key_name, c.key_state);
      g.BindResource(value_name, c.value_state);
      expected_bytes +=
          kKvElementBytes * 2 * count * c.spec.head_dim * c.spec.num_heads;
    }
    if (decode)
      g.Bind("logits", logits_.data(), logits_.size() * sizeof(float));
    auto before = g.counters();
    g.Run();
#if defined(LAB_ENABLE_VALUE_TRACE)
    if (trace_[decode]) {
      const auto directory =
          options.output_dir + "/trace/" + std::to_string(trace_call_++) +
          (decode ? "-decode-p" : "-prefill-p") + std::to_string(position_) +
          "-q" + std::to_string(count);
      trace_[decode]->Save(directory);
    }
#endif
    auto after = g.counters();
    if (after.append_bytes - before.append_bytes != expected_bytes ||
        after.append_calls - before.append_calls != 2 * caches_.size() ||
        after.view_copy_bytes)
      throw std::runtime_error("append/view copy contract violated");
    position_ += count;
  }
  Weights weights_;
  std::unique_ptr<ModelAssets> embeddings_;
  int capacity_, max_rows_, position_ = 0;
  std::vector<Cache> caches_;
  std::unique_ptr<lab_ynn::Graph> graph_[2];
  std::shared_ptr<lab_ynn::ExecutionProfile> execution_profile_;
#if defined(LAB_ENABLE_VALUE_TRACE)
  std::unique_ptr<lab::ValueTrace> trace_[2];
  size_t trace_call_ = 0;
#endif
  std::vector<Activation> embedded_;
  std::vector<float> positions_, logits_;
  std::vector<std::vector<Activation>> ple_;
};

void Main() {
  const auto frontend =
      lab::ResolveBenchmarkCases(options, ModelConfig().vocab_size);
  auto output = options.output_dir;
  if (output.empty() || std::filesystem::exists(output))
    throw std::invalid_argument("new output directory required");
  std::filesystem::create_directories(output);
  frontend.Save(output);
  {
    std::ofstream metadata(output + "/run.json");
    metadata << "{\"profile\":\""
#if defined(LAB_GEMMA4_HF)
             << kHfProfile << "\",\"source_identity\":\"" << kHfSourceIdentity
#else
             << "published_static_qat_" << ModelConfig().variant
#endif
             << "\",\"kv_element_bytes\":" << kKvElementBytes
             << ",\"cache_capacity\":" << options.cache_capacity
             << ",\"prefill_rows\":" << options.prefill_rows
             << ",\"threads\":" << options.num_threads
             << ",\"warmups\":" << options.warmup_runs
             << ",\"profile_execution\":"
             << lab_ynn::ProfileJson(options.profile_execution)
             << ",\"timings_valid_for_benchmark\":"
             << (options.profile_execution == "none" &&
                         !options.report_memory && !options.dump_outputs
                     ? "true"
                     : "false")
             << ",\"report_memory\":"
             << (options.report_memory ? "true" : "false")
             << ",\"repetitions\":" << options.measured_runs << "}\n";
  }
  auto start = Clock::now();
  Runner runner;
  const double setup_ms = Ms(start);
  const long setup_rss = Rss();
  auto profile = runner.execution_profile();
  std::ofstream profile_output;
  if (profile) {
    profile_output.open(output + "/execution_profile.jsonl");
    if (!profile_output)
      throw std::runtime_error("cannot open execution profile");
    profile->WriteMetadata(profile_output);
  }
  std::ofstream memory;
  if (options.report_memory) {
    memory.open(output + "/memory.jsonl");
    if (!memory) throw std::runtime_error("cannot open memory diagnostics");
    runner.ReportMemory("setup", memory);
  }
  std::ofstream timings(output + "/timings.jsonl");
  timings << std::setprecision(12);
  for (const auto& benchmark_case : frontend.cases) {
    const auto& prompt = benchmark_case.prompt;
    auto decode = benchmark_case.continuation;
    decode.insert(decode.begin(), prompt.back());
    for (int rep = -options.warmup_runs; rep < options.measured_runs; ++rep) {
      runner.Reset();
      start = Clock::now();
      runner.Prefix(prompt);
      double prefix_ms = Ms(start);
      const auto request = benchmark_case.name + "/" + std::to_string(rep);
      if (options.report_memory)
        runner.ReportMemory(request + "/prefix", memory);
      for (size_t step = 0; step < decode.size(); ++step) {
        const bool collect = profile && rep >= 0 && step > 0;
        if (collect)
          profile->BeginStep(benchmark_case.name, rep, step, runner.position());
        // Flush a failed step as incomplete; state must be discarded on error.
        struct ProfileStep {
          lab_ynn::ExecutionProfile* profile;
          std::ostream& output;
          bool complete = false;
          ~ProfileStep() {
            if (profile && !complete) {
              try {
                profile->EndStep(output, false);
              } catch (...) {
              }
            }
          }
        } profile_step{collect ? profile.get() : nullptr, profile_output};
        start = Clock::now();
        runner.Decode(decode[step]);
        const double decode_ms = Ms(start);
        const auto* logits = runner.logits();
        if (!std::all_of(logits, logits + ModelConfig().vocab_size,
                         [](float f) { return std::isfinite(f); }))
          throw std::runtime_error("nonfinite logits");
        auto argmax =
            std::max_element(logits, logits + ModelConfig().vocab_size) -
            logits;
        const auto token_ms = Ms(start);
        if (collect) {
          profile_step.complete = true;
          profile->EndStep(profile_output);
        }
        auto c = runner.counters();
        timings << "{\"case\":\"" << benchmark_case.name
                << "\",\"repetition\":" << rep << ",\"step\":" << step
                << ",\"setup_ms\":" << setup_ms
                << ",\"setup_rss_kib\":" << setup_rss
                << ",\"prefix_ms\":" << prefix_ms
                << ",\"decode_ms\":" << decode_ms
                << ",\"token_ms\":" << token_ms
                << ",\"context\":" << runner.position()
                << ",\"argmax\":" << argmax << ",\"peak_rss_kib\":" << PeakRss()
                << ",\"rss_kib\":" << Rss()
                << ",\"append_bytes\":" << c.append_bytes
                << ",\"view_copy_bytes\":" << c.view_copy_bytes << "}\n";
        timings.flush();
        if (options.report_memory && step == 0)
          runner.ReportMemory(request + "/first_decode", memory);
        if (rep == 0 && options.dump_outputs) {
          std::ostringstream suffix;
          if (step == 0)
            suffix << ".prefill.f32";
          else
            suffix << ".decode_" << std::setfill('0') << std::setw(4) << step
                   << ".f32";
          runner.Save(output + "/" + benchmark_case.name + suffix.str());
        }
      }
      std::cerr << benchmark_case.name << " rep=" << rep
                << " prefix_ms=" << prefix_ms << "\n";
    }
  }
}
}  // namespace
int Execute() {
  try {
    Main();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
int main(int argc, char** argv) {
  try {
    options = lab::ParseOptions(argc, argv);
#if defined(LAB_GEMMA4_E4B) || defined(LAB_GEMMA4_HF)
    // E4B and the BF16 author's deeper Slinky IR need more than Android's
    // default stack. Reserve a stack for preparation and execution;
    // physical pages are committed on demand. The waiting main thread does no
    // inference work and is not an extra compute worker.
    pthread_attr_t attr;
    int error = pthread_attr_init(&attr);
    if (error) throw std::runtime_error("pthread_attr_init failed");
    error = pthread_attr_setstacksize(&attr, 64 * 1024 * 1024);
    int status = 1;
    pthread_t thread;
    if (!error) {
      error = pthread_create(
          &thread, &attr,
          [](void* out) -> void* {
            *static_cast<int*>(out) = Execute();
            return nullptr;
          },
          &status);
    }
    pthread_attr_destroy(&attr);
    if (error) throw std::runtime_error("Cannot create model execution thread");
    if (pthread_join(thread, nullptr))
      throw std::runtime_error("pthread_join failed");
    return status;
#else
    return Execute();
#endif
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
