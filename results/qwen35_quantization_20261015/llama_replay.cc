// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Fixed-token CPU replay. Uses the same TSV cases and phase split as the lab.
#include "llama.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace fs = std::filesystem;
using Clock = std::chrono::steady_clock;
double ms(Clock::time_point start) {
  return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}
struct Case { std::string name; std::vector<llama_token> prompt, continuation; };
std::vector<llama_token> tokens(const std::string& text, int vocabulary) {
  if (text == "-") return {};
  std::istringstream stream(text);
  std::vector<llama_token> result;
  std::string value;
  while (std::getline(stream, value, ',')) {
    size_t used = 0;
    int id = std::stoi(value, &used);
    if (used != value.size() || id < 0 || id >= vocabulary) throw std::runtime_error("Invalid token ID");
    result.push_back(id);
  }
  return result;
}
struct Trace {
  int fd = -1;
  Trace() {
    if (const char* path = std::getenv("QWEN_REPLAY_TRACE_FIFO")) {
      fd = open(path, O_WRONLY | O_NONBLOCK | O_CLOEXEC | O_NOFOLLOW);
      struct stat info {};
      if (fd < 0 || fstat(fd, &info) || !S_ISFIFO(info.st_mode))
        throw std::runtime_error("Cannot open trace FIFO");
    }
  }
  ~Trace() { if (fd >= 0) close(fd); }
  void mark(bool begin) {
    if (fd < 0) return;
    std::string text = begin ? "section_begin decode\n" : "section_end decode\n";
    if (write(fd, text.data(), text.size()) != ssize_t(text.size()))
      throw std::runtime_error("Cannot write trace marker");
  }
};
struct Profile {
  std::ofstream file;
  std::string name, phase;
  int rep = 0, step = 0;
  Clock::time_point start;
  static bool callback(ggml_tensor* tensor, bool ask, void* user) {
    auto& p = *static_cast<Profile*>(user);
    if (!p.file.is_open()) return false;
    if (ask) { p.start = Clock::now(); return true; }
    const double elapsed = ms(p.start);
    p.file << "{\"case\":" << std::quoted(p.name) << ",\"phase\":" << std::quoted(p.phase)
           << ",\"rep\":" << p.rep << ",\"step\":" << p.step << ",\"name\":" << std::quoted(tensor->name)
           << ",\"op\":" << std::quoted(ggml_op_name(tensor->op)) << ",\"ms\":" << elapsed
           << ",\"output_bytes\":" << ggml_nbytes(tensor) << ",\"inputs\":[";
    bool first = true;
    for (auto* src : tensor->src) if (src) {
      if (!first) p.file << ',';
      first = false;
      p.file << "{\"name\":" << std::quoted(src->name) << ",\"type\":" << std::quoted(ggml_type_name(src->type))
             << ",\"op\":" << std::quoted(ggml_op_name(src->op)) << ",\"bytes\":" << ggml_nbytes(src) << ",\"shape\":[";
      for (int i = 0; i < 4; ++i) p.file << (i ? "," : "") << src->ne[i];
      p.file << "]}";
    }
    p.file << "]}\n";
    return true;
  }
};

int main(int argc, char** argv) try {
  std::map<std::string, std::string> args;
  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    const auto equals = arg.find('=');
    if (arg == "--dump_outputs" || arg == "--profile_nodes" || arg == "--score_tokens") args[arg] = "true";
    else if (equals != std::string::npos) args[arg.substr(0, equals)] = arg.substr(equals + 1);
    else if (i + 1 < argc) args[arg] = argv[++i];
    else throw std::runtime_error("Expected --option=value");
  }
  for (const auto& [key, value] : args)
    if (key != "--model" && key != "--cases_file" && key != "--output_dir" &&
        key != "--num_threads" && key != "--cache_capacity" && key != "--prefill_rows" &&
        key != "--warmup_runs" && key != "--measured_runs" && key != "--dump_outputs" && key != "--profile_nodes" && key != "--score_tokens")
      throw std::runtime_error("Unknown option: " + key);
  auto number = [&](const char* key, int fallback) {
    return args.count(key) ? std::stoi(args.at(key)) : fallback;
  };
  const int threads = number("--num_threads", 4), capacity = number("--cache_capacity", 2048);
  const int rows = number("--prefill_rows", 128), warmups = number("--warmup_runs", 1);
  const int reps = number("--measured_runs", 3);
  const bool dump = args.count("--dump_outputs");
  const bool score = args.count("--score_tokens");
  if (threads <= 0 || capacity <= 0 || rows <= 0 || warmups < 0 || reps <= 0)
    throw std::runtime_error("Invalid dimensions/repetitions");
  if (score && (warmups != 0 || reps != 1 || dump || args.count("--profile_nodes")))
    throw std::runtime_error("Scoring requires zero warmups, one repetition and no diagnostics");
  const fs::path output(args.at("--output_dir"));
  if (!fs::create_directory(output)) throw std::runtime_error("Output must be a fresh directory");
  Trace trace;
  Profile profile;
  if (args.count("--profile_nodes")) profile.file.open(output / "nodes.jsonl");
  if ((score || dump || profile.file.is_open()) && trace.fd >= 0) throw std::runtime_error("Diagnostics are incompatible with bandwidth measurements");
  llama_backend_init();
  const auto setup_start = Clock::now();
  auto mp = llama_model_default_params();
  mp.n_gpu_layers = 0;
  llama_model* model = llama_model_load_from_file(args.at("--model").c_str(), mp);
  if (!model) throw std::runtime_error("Model load failed");
  auto cp = llama_context_default_params();
  cp.n_ctx = capacity; cp.n_batch = cp.n_ubatch = rows;
  cp.n_threads = cp.n_threads_batch = threads;
  cp.type_k = cp.type_v = GGML_TYPE_F32;
  cp.offload_kqv = cp.op_offload = false;
  cp.flash_attn_type = LLAMA_FLASH_ATTN_TYPE_ENABLED;
  if (profile.file.is_open()) { cp.cb_eval = &Profile::callback; cp.cb_eval_user_data = &profile; }
  llama_context* ctx = llama_init_from_model(model, cp);
  if (!ctx) throw std::runtime_error("Context creation failed");
  const int vocabulary = llama_vocab_n_tokens(llama_model_get_vocab(model));
  const double setup_ms = ms(setup_start);
  std::ifstream input(args.at("--cases_file"));
  if (!input) throw std::runtime_error("Cannot read cases");
  std::vector<Case> cases;
  std::string line;
  while (std::getline(input, line)) {
    if (line.empty() || line[0] == '#') continue;
    const auto a = line.find('\t'), b = line.find('\t', a + 1);
    if (a == std::string::npos || b == std::string::npos) throw std::runtime_error("Invalid TSV row");
    Case c{line.substr(0, a), tokens(line.substr(a + 1, b - a - 1), vocabulary), tokens(line.substr(b + 1), vocabulary)};
    if (c.name.empty() || c.name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-") != std::string::npos ||
        c.prompt.empty() || c.prompt.size() + c.continuation.size() > size_t(capacity))
      throw std::runtime_error("Invalid case/capacity");
    if (std::any_of(cases.begin(), cases.end(), [&](const auto& x) {return x.name == c.name;}))
      throw std::runtime_error("Duplicate case");
    cases.push_back(std::move(c));
  }
  if (cases.empty()) throw std::runtime_error("No cases");
  fs::copy_file(args.at("--cases_file"), output / "resolved_cases.tsv");
  llama_batch batch = llama_batch_init(rows, 0, 1);
  auto invoke = [&](const llama_token* ids, int count, int position, bool logits) {
    batch.n_tokens = count;
    for (int i = 0; i < count; ++i) {
      batch.token[i] = ids[i]; batch.pos[i] = position + i;
      batch.n_seq_id[i] = 1; batch.seq_id[i][0] = 0;
      batch.logits[i] = logits && (score || i == count - 1);
    }
    if (llama_decode(ctx, batch)) throw std::runtime_error("Decode failed");
    llama_synchronize(ctx);
  };
  std::ofstream timing(output / "timings.jsonl"), windows(output / "trace.jsonl");
  timing << std::setprecision(12); windows << std::setprecision(12);
  if (score) {
    double total = 0; size_t count = 0;
    std::ofstream records(output / "quality-blocks.jsonl");
    for (const auto& c : cases) {
      std::vector<llama_token> ids = c.prompt;
      ids.insert(ids.end(), c.continuation.begin(), c.continuation.end());
      if (ids.size() < 2) throw std::runtime_error("Scoring needs at least two tokens");
      llama_memory_clear(llama_get_memory(ctx), true);
      double loss = 0;
      for (size_t start = 0; start < ids.size() - 1; start += rows) {
        const size_t size = std::min(size_t(rows), ids.size() - 1 - start);
        invoke(ids.data() + start, size, start, true);
        for (size_t row = 0; row < size; ++row) {
          const float* values = llama_get_logits_ith(ctx, row);
          if (!values || !std::all_of(values, values + vocabulary, [](float v) {return std::isfinite(v);}))
            throw std::runtime_error("Nonfinite scoring logits");
          double maximum = *std::max_element(values, values + vocabulary), sum = 0;
          for (int i = 0; i < vocabulary; ++i) sum += std::exp(double(values[i]) - maximum);
          loss += std::log(sum) + maximum - values[ids[start + row + 1]];
        }
      }
      total += loss; count += ids.size() - 1;
      records << std::setprecision(12) << "{\"case\":" << std::quoted(c.name) << ",\"tokens\":" << ids.size()-1
              << ",\"nll\":" << loss << "}\n";
      records.flush();
    }
    std::ofstream(output / "quality.json") << std::setprecision(12) << "{\"tokens\":" << count
        << ",\"mean_loss\":" << total/count << ",\"perplexity\":" << std::exp(total/count) << "}\n";
    std::ofstream(output / "completion.json") << "{\"status\":\"completed\",\"cases\":" << cases.size() << "}\n";
    llama_batch_free(batch); llama_free(ctx); llama_model_free(model); llama_backend_free();
    return 0;
  }
  for (const auto& c : cases) for (int rep = -warmups; rep < reps; ++rep) {
    profile.name = c.name; profile.rep = rep; profile.phase = "prefill"; profile.step = 0;
    llama_memory_clear(llama_get_memory(ctx), true);
    auto start = Clock::now();
    int position = 0;
    while (position < int(c.prompt.size()) - 1) {
      int count = std::min(rows, int(c.prompt.size()) - 1 - position);
      invoke(c.prompt.data() + position, count, position, false);
      position += count;
      ++profile.step;
    }
    const double prefix_ms = ms(start);
    auto trace_start = Clock::now();
    for (size_t step = 0; step <= c.continuation.size(); ++step) {
      profile.phase = "decode"; profile.step = step;
      if (step == 1 && rep >= 0 && trace.fd >= 0) { trace.mark(true); trace_start = Clock::now(); }
      const llama_token id = step ? c.continuation[step - 1] : c.prompt.back();
      start = Clock::now();
      invoke(&id, 1, position++, true);
      const double decode_ms = ms(start);
      const float* logits = llama_get_logits_ith(ctx, -1);
      if (!logits || !std::all_of(logits, logits + vocabulary, [](float v) {return std::isfinite(v);}))
        throw std::runtime_error("Missing/nonfinite logits");
      const int argmax = std::max_element(logits, logits + vocabulary) - logits;
      const double token_ms = ms(start);
      if (rep < 0) continue;
      timing << "{\"case\":" << std::quoted(c.name) << ",\"rep\":" << rep << ",\"step\":" << step
             << ",\"prompt_tokens\":" << c.prompt.size() << ",\"prefix_ms\":" << prefix_ms
             << ",\"prefix_graph_ms\":" << prefix_ms << ",\"decode_ms\":" << decode_ms
             << ",\"token_ms\":" << token_ms << ",\"argmax\":" << argmax << ",\"position\":" << position << "}\n";
      if (dump) {
        std::ofstream file(output / (c.name + "_r" + std::to_string(rep) + "_s" + std::to_string(step) + ".logits.bin"), std::ios::binary);
        file.write(reinterpret_cast<const char*>(logits), vocabulary * sizeof(float));
        if (!file) throw std::runtime_error("Cannot save logits");
      }
    }
    if (rep >= 0 && trace.fd >= 0 && !c.continuation.empty()) {
      trace.mark(false);
      windows << "{\"case\":" << std::quoted(c.name) << ",\"rep\":" << rep
              << ",\"tokens\":" << c.continuation.size() << ",\"elapsed_ms\":" << ms(trace_start) << "}\n";
    }
  }
  struct rusage usage {}; getrusage(RUSAGE_SELF, &usage);
  std::ofstream(output / "setup.json") << "{\"setup_ms\":" << setup_ms << "}\n";
  std::ofstream(output / "memory.json") << "{\"peak_rss_bytes\":" << uint64_t(usage.ru_maxrss) * 1024 << "}\n";
  std::ofstream(output / "run.json") << "{\"runner\":\"llama_replay\",\"status\":\"completed\",\"cases\":" << cases.size()
      << ",\"threads\":" << threads << ",\"cache_capacity\":" << capacity << ",\"prefill_rows\":" << rows
      << ",\"warmups\":" << warmups << ",\"repetitions\":" << reps << ",\"kv_dtype\":\"fp32\",\"flash_attention\":true"
      << ",\"timings_valid_for_benchmark\":" << (dump || profile.file.is_open() ? "false" : "true") << "}\n";
  llama_batch_free(batch); llama_free(ctx); llama_model_free(model); llama_backend_free();
  return 0;
} catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
