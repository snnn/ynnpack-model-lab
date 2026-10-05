// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/benchmark_cases.h"

#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>

#include "runtime/benchmark_io.h"

namespace {
void Check(bool value, const char* message) {
  if (!value) throw std::runtime_error(message);
}
void Fails(const std::function<void()>& function) {
  try {
    function();
  } catch (const std::exception&) {
    return;
  }
  throw std::runtime_error("Expected invalid input to fail");
}
lab::Options Parse(std::vector<std::string> args) {
  std::vector<char*> argv;
  for (auto& arg : args) argv.push_back(arg.data());
  return lab::ParseOptions(argv.size(), argv.data());
}
}  // namespace
int main(int argc, char** argv) {
  try {
    Check(argc == 2, "Expected temporary directory");
    auto directory = std::filesystem::path(argv[1]) / std::to_string(getpid());
    std::filesystem::create_directories(directory);
    const auto cases = (directory / "cases.tsv").string();
    lab::Options options;
    options.cases_file = cases;
    options.cache_capacity = 3;
    auto write = [&](const std::string& data) {
      std::ofstream file(cases, std::ios::binary);
      file << data;
    };
    write("# comment\r\n\na\t0,3\t2\r\nb\t1\t-\n");
    const auto frontend = lab::ResolveBenchmarkCases(options, 4);
    Check(frontend.resolved_tsv == "a\t0,3\t2\nb\t1\t-\n", "TSV bytes changed");
    const auto metadata = lab::ParseBenchmarkJson(frontend.metadata_json);
    Check(lab::BenchmarkInteger(metadata, "tokenizer_encode_calls") == 0,
          "TSV should not tokenize");
    Check(lab::BenchmarkField<minijson::number>(metadata,
                                                "tokenizer_load_ms") == 0,
          "TSV should not load a tokenizer");
    frontend.Save(directory.string());
    Check(lab::ReadBenchmarkFile((directory / "resolved_cases.tsv").string()) ==
              frontend.resolved_tsv,
          "Fixture write failed");
    options.cache_capacity = 2;
    Fails([&] { lab::ResolveBenchmarkCases(options, 4); });
    options.cache_capacity = 3;
    for (const auto& invalid :
         {"a\t0\t-\nb\t4\t-\n", "a\t-\t-\n", "a\t0\t-\na\t1\t-\n", "a\t0,\t-\n",
          "a\t-1\t-\n", "a\t0\n", "\n", "a/b\t0\t-\n", "a\t1.5\t-\n"}) {
      write(invalid);
      Fails([&] { lab::ResolveBenchmarkCases(options, 4); });
    }
    std::vector<std::string> args{
        "runner", "--bundle_dir=unused", "--parameter_dir=unused",
        "--output_dir=unused", "--cases_file=" + cases};
    Check(Parse(args).cases_file == cases, "Legacy runner CLI failed");
    auto duplicate = args;
    duplicate.push_back("--cases_file=other");
    Fails([&] { Parse(duplicate); });
    auto empty = args;
    empty.back() = "--cases_file=";
    Fails([&] { Parse(empty); });
    args.back() = "--prompt=";
    args.push_back("--tokenizer_dir=unused");
#if LAB_ENABLE_TOKENIZERS
    Check(Parse(args).has_prompt, "Empty literal prompt lost presence");
#else
    Fails([&] { Parse(args); });
#endif
    auto ambiguous = args;
    ambiguous.push_back("--text_cases_file=unused");
    Fails([&] { Parse(ambiguous); });
    ambiguous = args;
    ambiguous.push_back("--prompt_file=unused");
    Fails([&] { Parse(ambiguous); });
    ambiguous = args;
    ambiguous.push_back("--prompt_lengths=1");
    Fails([&] { Parse(ambiguous); });
    std::filesystem::remove_all(directory);
    std::cout << "Benchmark case validation passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
