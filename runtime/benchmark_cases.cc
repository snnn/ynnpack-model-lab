// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/benchmark_cases.h"

#include <sys/resource.h>
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>

#include "runtime/benchmark_io.h"
#include "runtime/sha256.h"
#include "runtime/tokenizer.h"

namespace lab {
namespace {
using Clock = std::chrono::steady_clock;
double Elapsed(Clock::time_point start) {
  return std::chrono::duration<double, std::milli>(Clock::now() - start)
      .count();
}
long CurrentRss() {
  std::ifstream file("/proc/self/statm");
  long total = 0, resident = 0;
  file >> total >> resident;
  return resident * (sysconf(_SC_PAGESIZE) / 1024);
}
long PeakRss() {
  rusage usage{};
  getrusage(RUSAGE_SELF, &usage);
  return usage.ru_maxrss;
}
std::string Hash(const std::string& data) {
  return Sha256::Digest(data.data(), data.size());
}
std::string Ids(const std::vector<int32_t>& ids, char separator = ',') {
  if (ids.empty()) return "-";
  std::string out;
  for (auto id : ids) {
    if (!out.empty()) out += separator;
    out += std::to_string(id);
  }
  return out;
}
int PositiveInteger(const std::string& text, bool allow_zero) {
  if (text.empty() || text.find_first_not_of("0123456789") != std::string::npos)
    throw std::invalid_argument("Invalid nonnegative integer: " + text);
  size_t end;
  int value = std::stoi(text, &end);
  if (end != text.size() || (!allow_zero && value == 0))
    throw std::invalid_argument("Invalid positive integer: " + text);
  return value;
}
std::vector<int32_t> TokenIds(const std::string& field) {
  std::vector<int32_t> ids;
  if (field == "-") return ids;
  for (const auto& text : Split(field, ','))
    ids.push_back(PositiveInteger(text, true));
  return ids;
}
void ValidateCase(const BenchmarkCase& c, int vocabulary, int capacity,
                  std::set<std::string>& names) {
  if (c.name.empty() ||
      c.name.find_first_not_of(
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-") !=
          std::string::npos)
    throw std::invalid_argument("Case names must be simple identifiers");
  if (!names.insert(c.name).second)
    throw std::invalid_argument("Duplicate case name: " + c.name);
  if (c.prompt.empty())
    throw std::invalid_argument("Empty resolved prompt: " + c.name);
  if (c.prompt.size() > static_cast<size_t>(capacity) ||
      c.continuation.size() > static_cast<size_t>(capacity) - c.prompt.size())
    throw std::invalid_argument("Prompt + continuation exceeds capacity: " +
                                c.name);
  for (const auto* ids : {&c.prompt, &c.continuation})
    for (auto id : *ids)
      if (id < 0 || id >= vocabulary)
        throw std::invalid_argument("Token ID outside model vocabulary: " +
                                    c.name);
}
void Write(const std::string& path, const std::string& data) {
  std::ofstream file(path, std::ios::binary);
  if (!file.write(data.data(), data.size()))
    throw std::runtime_error("Cannot write: " + path);
}
}  // namespace

void BenchmarkFrontend::Save(const std::string& output_dir) const {
  Write(output_dir + "/resolved_cases.tsv", resolved_tsv);
  Write(output_dir + "/frontend.json", metadata_json);
}

BenchmarkFrontend ResolveBenchmarkCases(const Options& options,
                                        int vocab_size) {
  ValidateInputOptions(options);
  if (options.cache_capacity < 1)
    throw std::invalid_argument("Invalid benchmark capacity");
  const auto start = Clock::now();
  const int model_vocab_size = vocab_size;
  const long rss_before = CurrentRss(), peak_before = PeakRss();
  BenchmarkFrontend result;
  std::string input_records, case_records, tokenizer_record = "null", mode;
  double load_ms = 0, encode_ms = 0;
  size_t encode_calls = 0;
  auto input = [&](const char* role, const std::string& path,
                   const std::string& data) {
    if (!input_records.empty()) input_records += ',';
    input_records += "{\"role\":" + JsonString(role) +
                     ",\"path\":" + JsonString(path) +
                     ",\"bytes\":" + std::to_string(data.size()) +
                     ",\"sha256\":" + JsonString(Hash(data)) + '}';
  };
  if (!options.cases_file.empty()) {
    mode = "token_ids";
    if (vocab_size <= 0)
      throw std::invalid_argument("TSV requires a model vocabulary size");
    auto data = ReadBenchmarkFile(options.cases_file);
    input("cases", options.cases_file, data);
    std::istringstream lines(data);
    for (std::string line; std::getline(lines, line);) {
      if (!line.empty() && line.back() == '\r') line.pop_back();
      if (line.empty() || line[0] == '#') continue;
      const auto fields = Split(line, '\t');
      if (fields.size() != 3)
        throw std::invalid_argument("Expected three TSV fields");
      result.cases.push_back(
          {fields[0], TokenIds(fields[1]), TokenIds(fields[2])});
    }
  } else {
    const auto load_start = Clock::now();
    auto tokenizer = Tokenizer::Load(options.tokenizer_dir);
    load_ms = Elapsed(load_start);
    const auto& manifest = tokenizer->manifest();
    // Models may pad their embedding/head vocabulary beyond the tokenizer's
    // ID extent. Every emitted ID must still fit the actual model vocabulary.
    if (vocab_size && vocab_size < manifest.vocab_size)
      throw std::invalid_argument(
          "Tokenizer vocabulary exceeds model vocabulary");
    if (!vocab_size) vocab_size = manifest.vocab_size;
    const auto policy_size =
        manifest.prefix_ids.size() + manifest.suffix_ids.size();
    tokenizer_record =
        "{\"directory\":" + JsonString(options.tokenizer_dir) +
        ",\"format\":" + JsonString(manifest.format) +
        ",\"file\":" + JsonString(manifest.file) +
        ",\"bytes\":" + std::to_string(manifest.bytes) +
        ",\"sha256\":" + JsonString(manifest.sha256) +
        ",\"manifest_sha256\":" + JsonString(manifest.manifest_sha256) +
        ",\"source\":" + manifest.source_json +
        ",\"vocab_size\":" + std::to_string(manifest.vocab_size) +
        ",\"prefix_ids\":[" +
        (manifest.prefix_ids.empty() ? "" : Ids(manifest.prefix_ids)) +
        "],\"suffix_ids\":[" +
        (manifest.suffix_ids.empty() ? "" : Ids(manifest.suffix_ids)) + "]}";
    auto encode = [&](const std::string& text) {
      const auto encode_start = Clock::now();
      auto ids = tokenizer->Encode(text);
      encode_ms += Elapsed(encode_start);
      ++encode_calls;
      return ids;
    };
    auto text_case = [&](const std::string& name, const std::string& prompt,
                         const std::string& continuation) {
      BenchmarkCase c{name, manifest.prefix_ids, {}};
      const auto ids = encode(prompt);
      c.prompt.insert(c.prompt.end(), ids.begin(), ids.end());
      c.prompt.insert(c.prompt.end(), manifest.suffix_ids.begin(),
                      manifest.suffix_ids.end());
      c.continuation = encode(continuation);
      result.cases.push_back(std::move(c));
    };
    if (!options.corpus_file.empty()) {
      mode = "corpus";
      auto data = ReadBenchmarkFile(options.corpus_file);
      input("corpus", options.corpus_file, data);
      const auto ids = encode(data);
      std::set<int> lengths;
      for (const auto& text : Split(options.prompt_lengths, ',')) {
        const int length = PositiveInteger(text, false);
        if (!lengths.insert(length).second)
          throw std::invalid_argument("Duplicate corpus prompt length");
        if (static_cast<size_t>(length) < policy_size ||
            length > options.cache_capacity ||
            options.continuation_tokens > options.cache_capacity - length)
          throw std::invalid_argument(
              "Invalid corpus prompt/continuation length");
        const size_t body_size = length - policy_size;
        if (body_size > ids.size() ||
            static_cast<size_t>(options.continuation_tokens) >
                ids.size() - body_size)
          throw std::invalid_argument(
              "Corpus has too few tokens for requested lengths");
        BenchmarkCase c{
            "prompt_" + std::to_string(length), manifest.prefix_ids, {}};
        c.prompt.insert(c.prompt.end(), ids.begin(), ids.begin() + body_size);
        c.prompt.insert(c.prompt.end(), manifest.suffix_ids.begin(),
                        manifest.suffix_ids.end());
        c.continuation.assign(
            ids.begin() + body_size,
            ids.begin() + body_size + options.continuation_tokens);
        result.cases.push_back(std::move(c));
      }
    } else if (!options.text_cases_file.empty()) {
      mode = "text_cases";
      auto data = ReadBenchmarkFile(options.text_cases_file);
      input("text_cases", options.text_cases_file, data);
      std::istringstream lines(data);
      size_t line_number = 0;
      for (std::string line; std::getline(lines, line);) {
        ++line_number;
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        try {
          const auto object = ParseBenchmarkJson(line);
          for (const auto& key : object.keys())
            if (key != "name" && key != "prompt" && key != "continuation")
              throw std::invalid_argument("Unknown text case field: " + key);
          const auto name = BenchmarkField<std::string>(object, "name");
          const auto prompt = BenchmarkField<std::string>(object, "prompt");
          std::string continuation;
          if (object.count("continuation"))
            continuation = BenchmarkField<std::string>(object, "continuation");
          text_case(name, prompt, continuation);
        } catch (const std::exception& error) {
          throw std::invalid_argument("Text case line " +
                                      std::to_string(line_number) + ": " +
                                      error.what());
        }
      }
    } else {
      mode = "prompt";
      const auto prompt = options.has_prompt_file
                              ? ReadBenchmarkFile(options.prompt_file)
                              : options.prompt;
      const auto continuation =
          options.has_continuation_file
              ? ReadBenchmarkFile(options.continuation_file)
              : options.continuation;
      input("prompt", options.has_prompt_file ? options.prompt_file : "",
            prompt);
      input("continuation",
            options.has_continuation_file ? options.continuation_file : "",
            continuation);
      text_case("prompt", prompt, continuation);
    }
    // Model measurements use the resolved IDs after releasing tokenizer memory.
    tokenizer.reset();
  }
  if (result.cases.empty()) throw std::invalid_argument("No benchmark cases");
  std::set<std::string> names;
  for (const auto& c : result.cases) {
    ValidateCase(c, vocab_size, options.cache_capacity, names);
    result.resolved_tsv +=
        c.name + '\t' + Ids(c.prompt) + '\t' + Ids(c.continuation) + '\n';
    if (!case_records.empty()) case_records += ',';
    case_records +=
        "{\"name\":" + JsonString(c.name) +
        ",\"prompt_tokens\":" + std::to_string(c.prompt.size()) +
        ",\"continuation_tokens\":" + std::to_string(c.continuation.size()) +
        '}';
  }
  std::ostringstream metadata;
  metadata << std::setprecision(12)
           << "{\"version\":1,\"mode\":" << JsonString(mode)
           << ",\"tokenizer\":" << tokenizer_record << ",\"model_vocab_size\":"
           << (model_vocab_size ? std::to_string(model_vocab_size) : "null")
           << ",\"inputs\":[" << input_records << "],\"cases\":["
           << case_records << ']' << ",\"resolved_cases_sha256\":"
           << JsonString(Hash(result.resolved_tsv))
           << ",\"tokenizer_load_ms\":" << load_ms
           << ",\"tokenizer_encode_ms\":" << encode_ms
           << ",\"tokenizer_encode_calls\":" << encode_calls
           << ",\"frontend_total_ms\":" << Elapsed(start)
           << ",\"rss_before_kib\":" << rss_before
           << ",\"rss_after_release_kib\":" << CurrentRss()
           << ",\"peak_rss_before_kib\":" << peak_before
           << ",\"peak_rss_after_release_kib\":" << PeakRss() << "}\n";
  result.metadata_json = metadata.str();
  return result;
}
}  // namespace lab
