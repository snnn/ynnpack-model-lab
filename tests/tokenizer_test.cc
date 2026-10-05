// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/tokenizer.h"

#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>

#include "runtime/benchmark_cases.h"
#include "runtime/benchmark_io.h"
#include "runtime/sha256.h"

namespace {
namespace fs = std::filesystem;
void Check(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}
void Fails(const std::function<void()>& operation) {
  try {
    operation();
  } catch (const std::exception&) {
    return;
  }
  throw std::runtime_error("Expected failure");
}
void Write(const fs::path& path, const std::string& data) {
  fs::create_directories(path.parent_path());
  std::ofstream file(path, std::ios::binary);
  Check(bool(file.write(data.data(), data.size())), "write failed");
}
std::vector<int32_t> Ids(const minijson::object& object, const char* key) {
  std::vector<int32_t> ids;
  for (const auto& value : lab::BenchmarkField<minijson::array>(object, key))
    ids.push_back(static_cast<int32_t>(*value.as<minijson::number>()));
  return ids;
}
void BadPayload(const fs::path& directory, const std::string& data,
                const std::string& format) {
  Write(directory / "payload", data);
  Write(directory / "manifest.json",
        "{\"version\":1,\"format\":" + lab::JsonString(format) +
            ",\"file\":\"payload\",\"bytes\":" + std::to_string(data.size()) +
            ",\"sha256\":" +
            lab::JsonString(lab::Sha256::Digest(data.data(), data.size())) +
            ",\"source\":{\"repo\":\"test\",\"revision\":\"v1\"},"
            "\"vocab_size\":320,\"prefix_ids\":[1],\"suffix_ids\":[]}");
  Fails([&] { lab::Tokenizer::Load(directory.string()); });
}
void Test(const fs::path& fixtures, const fs::path& temp) {
  for (const std::string kind : {"hf", "sp"}) {
    const auto directory = fixtures / kind;
    auto tokenizer = lab::Tokenizer::Load(directory.string());
    const auto golden = lab::ParseBenchmarkJson(
        lab::ReadBenchmarkFile((directory / "golden.json").string()));
    for (const auto& value :
         lab::BenchmarkField<minijson::array>(golden, "cases")) {
      const auto object = *value.as<minijson::object>();
      const auto text = lab::BenchmarkField<std::string>(object, "text");
      const auto ids = Ids(object, "ids");
      Check(tokenizer->Encode(text) == ids,
            "IDs differ from independent Python reference");
      Check(tokenizer->Decode(ids) ==
                lab::BenchmarkField<std::string>(object, "decoded"),
            "Decoded text differs from reference");
      Check(tokenizer->Encode(text) == ids, "Repeated encode changed IDs");
    }
    for (const auto& text :
         {std::string("\xc0\x80", 2), std::string("\xed\xa0\x80", 3),
          std::string("\xf4\x90\x80\x80", 4), std::string("\xe2\x82", 2),
          std::string("\x80", 1)})
      Fails([&] { tokenizer->Encode(text); });
    Fails([&] { tokenizer->Decode({-1}); });
    Fails([&] { tokenizer->Decode({320}); });
    lab::Options options;
    options.tokenizer_dir = directory.string();
    options.has_prompt = true;
    options.prompt = "hello world";
    options.has_continuation = true;
    options.continuation = " there";
    auto frontend = lab::ResolveBenchmarkCases(options, 320);
    const auto& c = frontend.cases.at(0);
    Check(c.prompt.front() == 1, "Manifest prefix missing");
    auto body = tokenizer->Encode(options.prompt);
    Check(std::vector<int32_t>(c.prompt.begin() + 1, c.prompt.end()) == body,
          "Prompt encoding or policy incorrect");
    Check(c.continuation == tokenizer->Encode(options.continuation),
          "Continuation policy incorrect");
    const auto json = lab::ParseBenchmarkJson(frontend.metadata_json);
    Check(lab::BenchmarkInteger(json, "tokenizer_encode_calls") == 2,
          "Encode count incorrect");
    Check(lab::BenchmarkField<std::string>(json, "resolved_cases_sha256") ==
              lab::Sha256::Digest(frontend.resolved_tsv.data(),
                                  frontend.resolved_tsv.size()),
          "Resolved fixture identity incorrect");
    Fails([&] { lab::ResolveBenchmarkCases(options, 319); });
    const auto probe_metadata = lab::ParseBenchmarkJson(
        lab::ResolveBenchmarkCases(options, 0).metadata_json);
    minijson::value model_vocabulary;
    Check(probe_metadata.at("model_vocab_size", &model_vocabulary) &&
              model_vocabulary.str() == "null",
          "Weights-free probe should not claim a model vocabulary");
    Check(lab::ResolveBenchmarkCases(options, 512).resolved_tsv ==
              frontend.resolved_tsv,
          "Padded model vocabulary changed tokenizer IDs");
    options.cache_capacity =
        static_cast<int>(c.prompt.size() + c.continuation.size());
    Check(lab::ResolveBenchmarkCases(options, 320).resolved_tsv ==
              frontend.resolved_tsv,
          "Capacity boundary changed IDs");
    --options.cache_capacity;
    Fails([&] { lab::ResolveBenchmarkCases(options, 320); });
    options.cache_capacity = 2048;
    options.prompt.clear();
    options.continuation.clear();
    Check(lab::ResolveBenchmarkCases(options, 320).cases[0].prompt ==
              std::vector<int32_t>{1},
          "Empty text should retain manifest prefix");
    // Files preserve leading/trailing whitespace, newlines, and NUL bytes.
    const std::string exact(" hello\n\0world\n", 14);
    Write(temp / "prompt.txt", exact);
    options.has_prompt = false;
    options.has_prompt_file = true;
    options.prompt_file = (temp / "prompt.txt").string();
    auto file_case = lab::ResolveBenchmarkCases(options, 320).cases[0];
    auto expected = tokenizer->Encode(exact);
    expected.insert(expected.begin(), 1);
    Check(file_case.prompt == expected, "Prompt file bytes changed");
    options.has_prompt_file = false;
    options.has_continuation = false;
    options.text_cases_file = (temp / "cases.jsonl").string();
    Write(options.text_cases_file,
          "{\"name\":\"one\",\"prompt\":" + lab::JsonString(exact) +
              "}\n"
              "{\"name\":\"two\",\"prompt\":\"hello\",\"continuation\":\" "
              "world\"}\n");
    auto multi = lab::ResolveBenchmarkCases(options, 320);
    Check(multi.cases.size() == 2 && multi.cases[0].prompt == expected,
          "JSONL resolution differs");
    Write(temp / "resolved.tsv", multi.resolved_tsv);
    lab::Options tsv;
    tsv.cases_file = (temp / "resolved.tsv").string();
    Check(
        lab::ResolveBenchmarkCases(tsv, 320).resolved_tsv == multi.resolved_tsv,
        "TSV export does not replay");
    for (const std::string bad :
         {"{\"name\":\"one\",\"prompt\":\"hello\"}\n{\"name\":\"one\","
          "\"prompt\":\"world\"}\n",
          "{\"name\":\"../bad\",\"prompt\":\"x\"}\n",
          "{\"name\":\"one\",\"prompt\":3}\n",
          "{\"name\":\"one\",\"prompt\":\"x\",\"extra\":true}\n",
          "{\"name\":\"one\",\"prompt\":\"\\ud800\"}\n",
          "{\"name\":\"one\",\"prompt\":\"x\",\"prompt\":\"y\"}\n",
          "{} trailing\n", "\n"}) {
      Write(options.text_cases_file, bad);
      Fails([&] { lab::ResolveBenchmarkCases(options, 320); });
    }
    options.text_cases_file.clear();
    options.corpus_file = (temp / "corpus.txt").string();
    // Byte-level HF and byte-fallback SP each emit one ID for each of these
    // unseen repeated ASCII characters, independently checked below.
    const std::string corpus(1100, '~');
    Write(options.corpus_file, corpus);
    auto stream = tokenizer->Encode(corpus);
    Check(stream.size() == corpus.size(),
          "Unexpected test corpus tokenization");
    options.prompt_lengths = "1,128,129,130,511,512,513,1024";
    options.continuation_tokens = 2;
    auto matrix = lab::ResolveBenchmarkCases(options, 320);
    Check(matrix.cases.size() == 8, "Wrong corpus matrix count");
    const std::vector<int> lengths{1, 128, 129, 130, 511, 512, 513, 1024};
    for (size_t i = 0; i < lengths.size(); ++i) {
      auto prompt = std::vector<int32_t>{1};
      prompt.insert(prompt.end(), stream.begin(),
                    stream.begin() + lengths[i] - 1);
      Check(matrix.cases[i].prompt == prompt,
            "Corpus prompt slicing incorrect");
      Check(matrix.cases[i].continuation ==
                std::vector<int32_t>(stream.begin() + lengths[i] - 1,
                                     stream.begin() + lengths[i] + 1),
            "Corpus continuation slicing incorrect");
    }
    Check(lab::BenchmarkInteger(lab::ParseBenchmarkJson(matrix.metadata_json),
                                "tokenizer_encode_calls") == 1,
          "Corpus should encode once");
    options.prompt_lengths = "1,1";
    Fails([&] { lab::ResolveBenchmarkCases(options, 320); });
    options.prompt_lengths = "1100";
    options.continuation_tokens = 2;
    Fails([&] { lab::ResolveBenchmarkCases(options, 320); });
    options.prompt_lengths = "0";
    Fails([&] { lab::ResolveBenchmarkCases(options, 320); });
    // A different model policy contributes both a prefix and a suffix to P.
    const auto policy_dir = temp / (kind + "-suffix");
    auto policy =
        lab::ReadBenchmarkFile((directory / "manifest.json").string());
    const auto at = policy.find("\"suffix_ids\": []");
    Check(at != std::string::npos, "Missing fixture suffix field");
    policy.replace(at, std::string("\"suffix_ids\": []").size(),
                   "\"suffix_ids\": [3]");
    Write(policy_dir / "manifest.json", policy);
    const auto file = tokenizer->manifest().file;
    Write(policy_dir / file,
          lab::ReadBenchmarkFile((directory / file).string()));
    options.tokenizer_dir = policy_dir.string();
    options.prompt_lengths = "4";
    const auto with_suffix = lab::ResolveBenchmarkCases(options, 320).cases[0];
    Check(with_suffix.prompt ==
              std::vector<int32_t>({1, stream[0], stream[1], 3}),
          "Corpus suffix policy did not count toward prompt length");
    Check(with_suffix.continuation ==
              std::vector<int32_t>({stream[2], stream[3]}),
          "Suffix policy shifted corpus continuation incorrectly");
    options.prompt_lengths = "1";
    Fails([&] { lab::ResolveBenchmarkCases(options, 320); });
  }
  BadPayload(temp / "bad-hf", "{bad json", "hf_json");
  BadPayload(temp / "bad-sp", "not a protobuf", "sentencepiece");
  BadPayload(temp / "unsupported", "anything", "unknown");
  const auto payload =
      lab::ReadBenchmarkFile((fixtures / "hf/tokenizer.json").string());
  for (const std::string key : {"padding", "truncation"}) {
    auto automatic = payload;
    const auto marker = "\"" + key + "\": null";
    const auto at = automatic.find(marker);
    Check(at != std::string::npos, "Missing fixture padding/truncation field");
    const std::string config =
        key == "padding"
            ? R"({"strategy":"BatchLongest","direction":"Right","pad_to_multiple_of":null,"pad_id":0,"pad_type_id":0,"pad_token":"<unk>"})"
            : R"({"direction":"Right","max_length":3,"strategy":"LongestFirst","stride":0})";
    automatic.replace(at, marker.size(), "\"" + key + "\":" + config);
    BadPayload(temp / key, automatic, "hf_json");
  }
  auto corrupted = payload;
  corrupted[0] ^= 1;
  const auto copy = temp / "hash-mismatch";
  Write(copy / "manifest.json",
        lab::ReadBenchmarkFile((fixtures / "hf/manifest.json").string()));
  Write(copy / "tokenizer.json", corrupted);
  Fails([&] { lab::Tokenizer::Load(copy.string()); });
  const std::string sparse =
      R"({"version":"1.0","added_tokens":[],"normalizer":null,"pre_tokenizer":null,"post_processor":null,"decoder":null,"model":{"type":"BPE","unk_token":"<unk>","vocab":{"<unk>":0,"a":7},"merges":[]}})";
  const auto sparse_dir = temp / "sparse";
  Write(sparse_dir / "tokenizer.json", sparse);
  Write(sparse_dir / "manifest.json",
        "{\"version\":1,\"format\":\"hf_json\",\"file\":\"tokenizer.json\","
        "\"bytes\":" +
            std::to_string(sparse.size()) + ",\"sha256\":" +
            lab::JsonString(lab::Sha256::Digest(sparse.data(), sparse.size())) +
            ",\"vocab_size\":8,\"prefix_ids\":[7],\"suffix_ids\":[],"
            "\"source\":{\"repo\":\"test\",\"revision\":\"v1\"}}");
  auto sparse_tokenizer = lab::Tokenizer::Load(sparse_dir.string());
  Check(sparse_tokenizer->Encode("a") == std::vector<int32_t>{7},
        "Sparse vocabulary extent was treated as the token count");
  Fails([&] { sparse_tokenizer->Decode({1}); });
  lab::Options invalid;
  invalid.cases_file = "cases.tsv";
  invalid.has_prompt = true;
  Fails([&] { lab::ValidateInputOptions(invalid); });
  invalid.has_prompt = false;
  invalid.has_continuation = true;
  Fails([&] { lab::ValidateInputOptions(invalid); });
  invalid.has_continuation = false;
  invalid.has_prompt_lengths = true;
  Fails([&] { lab::ValidateInputOptions(invalid); });
}
}  // namespace
int main(int argc, char** argv) {
  try {
    Check(argc == 3, "Expected fixture and temporary directory paths");
    const fs::path temp = fs::path(argv[2]) / std::to_string(getpid());
    fs::create_directories(temp);
    Test(argv[1], temp);
    fs::remove_all(temp);
    std::cout << "Native tokenizer references and benchmark inputs passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
