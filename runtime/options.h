// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace lab {
inline std::vector<std::string> Split(const std::string& s, char delim) {
  std::vector<std::string> parts;
  size_t start = 0, end;
  while ((end = s.find(delim, start)) != std::string::npos) {
    parts.push_back(s.substr(start, end - start));
    start = end + 1;
  }
  parts.push_back(s.substr(start));
  return parts;
}
struct Options {
  std::string bundle_dir, parameter_dir, cases_file, output_dir;
  std::string hf_model_dir, asset_manifest, cache_dir;
  std::string trace_plan;
  std::string profile_execution = "none";
  std::string tokenizer_dir, text_cases_file, corpus_file;
  std::string prompt, prompt_file, continuation, continuation_file;
  std::string prompt_lengths = "17,128,1024";
  int continuation_tokens = 32;
  bool has_prompt = false, has_continuation = false;
  bool has_prompt_file = false, has_continuation_file = false;
  bool has_prompt_lengths = false, has_continuation_tokens = false;
  int cache_capacity = 2048, num_threads = 4, prefill_rows = 128;
  int warmup_runs = 1, measured_runs = 3;
  bool dump_outputs = false, dump_pipeline = false, report_memory = false;
};
inline void ValidateInputOptions(const Options& o) {
  const bool explicit_text = o.has_prompt || o.has_prompt_file;
  const int modes = !o.cases_file.empty() + !o.text_cases_file.empty() +
                    !o.corpus_file.empty() + explicit_text;
  if (modes != 1 || (o.has_prompt && o.has_prompt_file) ||
      (o.has_continuation && o.has_continuation_file))
    throw std::invalid_argument("Choose exactly one input mode; use --help");
  if ((o.has_continuation || o.has_continuation_file) && !explicit_text)
    throw std::invalid_argument(
        "Continuation text requires an explicit prompt");
  if ((o.has_prompt_lengths || o.has_continuation_tokens) &&
      o.corpus_file.empty())
    throw std::invalid_argument("Length options require --corpus_file");
  if (o.continuation_tokens < 0)
    throw std::invalid_argument("Negative continuation count");
  if (o.cases_file.empty() == o.tokenizer_dir.empty())
    throw std::invalid_argument(
        "Text input requires --tokenizer_dir; TSV uses token IDs directly");
#if !LAB_ENABLE_TOKENIZERS
  if (o.cases_file.empty())
    throw std::invalid_argument("Text input requires LAB_ENABLE_TOKENIZERS=ON");
#endif
}
inline Options ParseOptions(int argc, char** argv, bool require_model = true) {
  Options o;
  std::set<std::string> seen;
  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    if (arg == "--help" || arg == "-h") {
      std::cout << (require_model ? "Gemma4 YNNPACK experiment\n"
                                  : "Tokenizer benchmark case probe\n")
                << "Required: ";
      if (require_model) std::cout << "--bundle_dir=DIR --parameter_dir=DIR ";
      std::cout
          << "--output_dir=NEW_DIR\n"
          << "Input (choose one): --cases_file=TSV (model runner only)\n"
          << "  --tokenizer_dir=DIR --prompt=TEXT (or --prompt_file=FILE)\n"
          << "    optional --continuation=TEXT (or --continuation_file=FILE)\n"
          << "  --tokenizer_dir=DIR --text_cases_file=JSONL\n"
          << "  --tokenizer_dir=DIR --corpus_file=FILE "
             "--prompt_lengths=17,128,1024\n"
          << "    --continuation_tokens=32\n"
          << "Options: --cache_capacity=2048 --num_threads=4 "
             "--prefill_rows=128\n"
          << "         --warmup_runs=1 --measured_runs=3 --dump_outputs "
             "--dump_pipeline --report_memory\n"
          << "         --profile_execution=none|decode (diagnostic timings)\n"
          << "HF builds: replace --bundle_dir with --hf_model_dir=DIR "
             "--asset_manifest=FILE --cache_dir=DIR\n";
#if defined(LAB_ENABLE_VALUE_TRACE)
      std::cout << "Diagnostic build: --trace_plan=DIR (changes graph outputs; "
                   "do not use for performance measurements)\n";
#endif
      std::exit(0);
    }
    auto equals = arg.find('=');
    std::string key = arg.substr(0, equals), value;
    if (!seen.insert(key).second)
      throw std::invalid_argument("Repeated option: " + key);
    if (equals != std::string::npos)
      value = arg.substr(equals + 1);
    else if (key == "--dump_outputs" || key == "--dump_pipeline" ||
             key == "--report_memory")
      value = "true";
    else if (++i < argc)
      value = argv[i];
    else
      throw std::invalid_argument("Missing value for " + key);
    if (value.empty() && key != "--prompt" && key != "--continuation")
      throw std::invalid_argument("Empty value for " + key);
    auto integer = [&] {
      size_t end;
      int n = std::stoi(value, &end);
      if (end != value.size())
        throw std::invalid_argument("Invalid integer: " + value);
      return n;
    };
    auto boolean = [&] {
      if (value == "true" || value == "1") return true;
      if (value == "false" || value == "0") return false;
      throw std::invalid_argument("Invalid boolean: " + value);
    };
    if (key == "--bundle_dir")
      o.bundle_dir = value;
    else if (key == "--parameter_dir")
      o.parameter_dir = value;
    else if (key == "--hf_model_dir")
      o.hf_model_dir = value;
    else if (key == "--asset_manifest")
      o.asset_manifest = value;
    else if (key == "--cache_dir")
      o.cache_dir = value;
#if defined(LAB_ENABLE_VALUE_TRACE)
    else if (key == "--trace_plan")
      o.trace_plan = value;
#endif
    else if (key == "--cases_file")
      o.cases_file = value;
    else if (key == "--tokenizer_dir")
      o.tokenizer_dir = value;
    else if (key == "--text_cases_file")
      o.text_cases_file = value;
    else if (key == "--corpus_file")
      o.corpus_file = value;
    else if (key == "--prompt") {
      o.prompt = value;
      o.has_prompt = true;
    } else if (key == "--prompt_file") {
      o.prompt_file = value;
      o.has_prompt_file = true;
    } else if (key == "--continuation") {
      o.continuation = value;
      o.has_continuation = true;
    } else if (key == "--continuation_file") {
      o.continuation_file = value;
      o.has_continuation_file = true;
    } else if (key == "--prompt_lengths") {
      o.prompt_lengths = value;
      o.has_prompt_lengths = true;
    } else if (key == "--continuation_tokens") {
      o.continuation_tokens = integer();
      o.has_continuation_tokens = true;
    } else if (key == "--output_dir")
      o.output_dir = value;
    else if (key == "--cache_capacity")
      o.cache_capacity = integer();
    else if (key == "--num_threads")
      o.num_threads = integer();
    else if (key == "--prefill_rows")
      o.prefill_rows = integer();
    else if (key == "--warmup_runs")
      o.warmup_runs = integer();
    else if (key == "--measured_runs")
      o.measured_runs = integer();
    else if (key == "--dump_outputs")
      o.dump_outputs = boolean();
    else if (key == "--dump_pipeline")
      o.dump_pipeline = boolean();
    else if (key == "--report_memory")
      o.report_memory = boolean();
    else if (key == "--profile_execution")
      o.profile_execution = value;
    else
      throw std::invalid_argument("Unknown option: " + key);
  }
  const bool hf = !o.hf_model_dir.empty() && !o.asset_manifest.empty() &&
                  !o.cache_dir.empty();
  if ((require_model &&
       ((o.bundle_dir.empty() && !hf) || o.parameter_dir.empty())) ||
      o.output_dir.empty() || o.warmup_runs < 0 || o.measured_runs < 1 ||
      o.cache_capacity < 1 || o.cache_capacity > 32768 || o.num_threads < 1 ||
      o.num_threads > 256 || o.prefill_rows < 1 || o.prefill_rows > 128)
    throw std::invalid_argument("Invalid/missing options; use --help");
  ValidateInputOptions(o);
  if (o.profile_execution != "none" && o.profile_execution != "decode")
    throw std::invalid_argument("--profile_execution must be none or decode");
  if (!require_model && o.profile_execution != "none")
    throw std::invalid_argument("Execution profiling requires a model runner");
  return o;
}
}  // namespace lab
