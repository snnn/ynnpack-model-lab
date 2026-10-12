// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#define LAB_NOEXCEPT noexcept
extern "C" {
#else
#define LAB_NOEXCEPT
#endif

// Private, versioned-together C ABI for the Rust wrapper. Every fallible call
// catches C++ exceptions. Error text is caller-owned and NUL terminated.
typedef struct LabAssets LabAssets;
typedef struct LabGraph LabGraph;
typedef struct LabResource LabResource;
typedef struct LabError {
  int32_t kind;  // 1: invalid argument/contract; 2: backend; 3: unexpected.
  char message[1024];
} LabError;
typedef struct LabCounters {
  uint64_t append_calls, append_bytes, view_copy_bytes;
} LabCounters;
typedef struct LabConfig {
  uint32_t vocab, width, layers, ple_width, owners;
} LabConfig;
typedef struct LabKvSpec {
  uint32_t owner, heads, width;
} LabKvSpec;

const char* lab_model_name(void) LAB_NOEXCEPT;
int32_t lab_assets_create(const char* bundle, const char* parameters,
                          LabAssets** out, LabError* error) LAB_NOEXCEPT;
int32_t lab_assets_create_hf(const char* source, const char* manifest,
                             const char* cache, const char* parameters,
                             const char* identity, int32_t bf16,
                             LabAssets** out, LabError*) LAB_NOEXCEPT;
void lab_assets_delete(LabAssets* assets) LAB_NOEXCEPT;
// Construction-only ABI. Rust validates the complete artifact before calling
// these functions; all slices are borrowed only for the duration of a call.
typedef struct LabPlanArg {
  uint32_t kind, reserved;
  int64_t integer;
  double real;
  const void* data;
  size_t count;
} LabPlanArg;
int32_t lab_assets_data(LabAssets*, const char*, size_t, const void**,
                        LabError*) LAB_NOEXCEPT;
int32_t lab_plan_create(size_t, LabGraph**, LabError*) LAB_NOEXCEPT;
int32_t lab_plan_expr(LabGraph*, uint32_t, int64_t, const uint32_t*, size_t,
                      uint32_t*, LabError*) LAB_NOEXCEPT;
int32_t lab_plan_command(LabGraph*, const char*, const LabPlanArg*, size_t,
                         LabError*) LAB_NOEXCEPT;
int32_t lab_assets_config(LabAssets*, LabConfig*, LabError*) LAB_NOEXCEPT;
int32_t lab_assets_owner(LabAssets*, size_t, LabKvSpec*,
                         LabError*) LAB_NOEXCEPT;
int32_t lab_assets_embed(LabAssets*, const int32_t* tokens, size_t count,
                         void* embedded, size_t embedded_count,
                         void* const* ple, size_t layers, size_t ple_count,
                         size_t element_bytes, LabError*) LAB_NOEXCEPT;

// Assets outlive all graphs created from them. Bound allocations and resource
// handles outlive graph destruction. Rust owns and enforces these
// relationships.

void lab_graph_delete(LabGraph*) LAB_NOEXCEPT;
int32_t lab_graph_compile(LabGraph*, size_t threads, LabError*) LAB_NOEXCEPT;
int32_t lab_graph_bind(LabGraph*, const char* name, void* data, size_t bytes,
                       const size_t* shape, size_t rank, int32_t optional,
                       LabError*) LAB_NOEXCEPT;
int32_t lab_graph_scalar(LabGraph*, const char*, int64_t,
                         LabError*) LAB_NOEXCEPT;
int32_t lab_graph_run(LabGraph*, LabError*) LAB_NOEXCEPT;
// Fixture-only synchronous checks at append boundaries. No pointers are
// retained after this call, including on a failed invocation.
typedef struct LabAppendCheck {
  size_t append;
  const void* actual;
  const void* expected;
  size_t bytes;
} LabAppendCheck;
int32_t lab_fixture_run(LabGraph*, const LabAppendCheck*, size_t checks,
                        size_t appends, size_t fail_after,
                        LabError*) LAB_NOEXCEPT;
int32_t lab_graph_trace(LabGraph*, const char* plan, const char* output,
                        LabError*) LAB_NOEXCEPT;
int32_t lab_graph_shape(LabGraph*, const char* name, size_t* dims, size_t* rank,
                        LabError*) LAB_NOEXCEPT;
int32_t lab_graph_weight_stats(LabGraph*, uint64_t values[3],
                               LabError*) LAB_NOEXCEPT;
int32_t lab_graph_counters(LabGraph*, LabCounters*, LabError*) LAB_NOEXCEPT;
int32_t lab_resource_create(LabGraph*, const char*, void*, size_t,
                            const size_t*, size_t, LabResource**,
                            LabError*) LAB_NOEXCEPT;
void lab_resource_delete(LabResource*) LAB_NOEXCEPT;
int32_t lab_resource_reset(LabResource*, LabError*) LAB_NOEXCEPT;
int32_t lab_resource_import(LabResource*, size_t, LabError*) LAB_NOEXCEPT;
int32_t lab_resource_status(LabResource*, uint64_t[3], LabError*) LAB_NOEXCEPT;
int32_t lab_graph_resource(LabGraph*, const char*, LabResource*,
                           LabError*) LAB_NOEXCEPT;

uint64_t lab_rss_bytes(void) LAB_NOEXCEPT;
uint64_t lab_peak_rss_bytes(void) LAB_NOEXCEPT;
int32_t lab_allocator_bytes(uint64_t values[3]) LAB_NOEXCEPT;

// Optional diagnostics use the existing native profiler and scratch counters.
int32_t lab_graph_diagnostics(LabGraph*, const char* pipeline_path,
                              const char* profile_path, int32_t memory,
                              LabError*) LAB_NOEXCEPT;
int32_t lab_graph_profile_step(LabGraph*, const char* case_name,
                               int32_t repetition, size_t step, size_t position,
                               size_t rows, int32_t prefill, int32_t action,
                               LabError*) LAB_NOEXCEPT;
typedef struct LabMemory {
  uint64_t root, live, peak, allocated, allocations;
} LabMemory;
int32_t lab_graph_memory(LabGraph*, LabMemory*, LabError*) LAB_NOEXCEPT;

// Rust supplies the application; CMake supplies main and the native link graph.
int32_t lab_rust_main(int32_t argc, const char* const* argv) LAB_NOEXCEPT;

#ifdef __cplusplus
}
#endif
#undef LAB_NOEXCEPT
