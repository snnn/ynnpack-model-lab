// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include <sys/resource.h>
#include <unistd.h>

#include <fstream>
#include <vector>
#ifdef __GLIBC__
#include <malloc.h>
#endif

#include "runtime/rust/bridge_internal.h"
#include "runtime/ynnpack_capacity.h"

namespace {
std::vector<size_t> Shape(const size_t* shape, size_t rank) {
  LabRequire(rank <= YNN_MAX_TENSOR_RANK && (!rank || shape), "Invalid rank");
  return rank ? std::vector<size_t>(shape, shape + rank)
              : std::vector<size_t>{};
}
}  // namespace

extern "C" {
#ifdef LAB_RUNTIME_TEST_HOOKS
void lab_test_live_handles(size_t* graphs, size_t* assets) noexcept {
  *graphs = lab_test_graphs;
  *assets = lab_test_assets;
}
void lab_test_fail_compile_after(int successful) noexcept {
  lab_test_compile_countdown = successful;
}
#endif
void lab_assets_delete(LabAssets* assets) noexcept { delete assets; }
void lab_graph_delete(LabGraph* graph) noexcept { delete graph; }
void lab_resource_delete(LabResource* resource) noexcept { delete resource; }

int32_t lab_resources_migrate(LabResource* const* before,
                              LabResource* const* after, size_t count,
                              size_t capacity, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(count <= 512 && (!count || (before && after)), "Invalid migration owners");
    lab_ynn::CapacityVariant old, next;
    next.capacity = capacity;
    for (size_t i = 0; i < count; ++i) {
      LabRequire(before[i] && after[i], "Missing migration owner");
      old.resources[std::to_string(i)] = before[i]->state;
      next.resources[std::to_string(i)] = after[i]->state;
    }
    lab_ynn_runtime::StateMigrationLease lease(old.LogicalStates(), next.LogicalStates());
    next.MigrateFrom(old);
    lease.Commit();
  });
}

int32_t lab_graph_compile(LabGraph* graph, size_t threads,
                          LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && threads >= 1 && threads <= 256,
               "Invalid graph/threads");
#ifdef LAB_RUNTIME_TEST_HOOKS
    if (lab_test_compile_countdown == 0) {
      lab_test_compile_countdown = -1;
      throw std::runtime_error("Injected later-phase preparation failure");
    }
    if (lab_test_compile_countdown > 0) --lab_test_compile_countdown;
#endif
    graph->graph->Compile(threads);
    graph->prepared_pipeline = graph->graph->pipeline();
    if (graph->trace) graph->trace->Bind();
    graph->construction.reset();
  });
}
int32_t lab_graph_bind(LabGraph* graph, const char* name, void* data,
                       size_t bytes, const size_t* shape, size_t rank,
                       int32_t optional, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && name && data, "Invalid tensor binding");
    if (optional && !graph->graph->Has(name)) return;
    graph->graph->Bind(name, data, bytes, Shape(shape, rank));
  });
}
int32_t lab_graph_scalar(LabGraph* graph, const char* name, int64_t value,
                         LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && name, "Invalid scalar binding");
    graph->graph->ScalarValue(name, value);
  });
}
int32_t lab_graph_run(LabGraph* graph, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph, "Null graph");
    graph->graph->Run();
    LabRequire(graph->prepared_pipeline.same_as(graph->graph->pipeline()),
               "Prepared pipeline changed during invocation");
  });
}
int32_t lab_graph_trace(LabGraph* graph, const char* plan, const char* output,
                        LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && plan && output, "Invalid trace request");
    if (*plan) {
      LabRequire(graph->construction && !graph->trace,
                 "Trace must precede preparation");
      graph->trace = std::make_unique<lab::ValueTrace>(*graph->graph, plan);
    } else {
      LabRequire(graph->trace && *output, "Missing trace/output");
      graph->trace->Save(output);
    }
  });
}
int32_t lab_graph_shape(LabGraph* graph, const char* name, size_t* dims,
                        size_t* rank, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && name && dims && rank, "Invalid shape request");
    const auto& buffer = graph->graph->InspectionBuffer(name);
    LabRequire(buffer.rank <= 8, "Invalid inspection rank");
    *rank = buffer.rank;
    for (size_t i = 0; i < buffer.rank; ++i)
      dims[i] = buffer.dim(buffer.rank - 1 - i).extent();
  });
}
int32_t lab_graph_weight_stats(LabGraph* graph, uint64_t values[3],
                               LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && values, "Invalid weight-only statistics request");
    const auto& stats = graph->graph->weight_only_statistics();
    values[0] = stats.calls.load();
    values[1] = stats.native_dot_calls.load();
    values[2] = stats.worker_scratch_bytes.load();
  });
}
int32_t lab_graph_counters(LabGraph* graph, LabCounters* out,
                           LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && out, "Invalid counters request");
    const auto c = graph->graph->counters();
    *out = {c.append_calls, c.append_bytes, c.view_copy_bytes};
  });
}
int32_t lab_graph_diagnostics(LabGraph* graph, const char* pipeline,
                              const char* profile, int32_t memory,
                              LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && pipeline && profile, "Invalid diagnostics options");
    // Profile attachment precedes Compile; pipeline/scratch follow it.
    if (*profile) {
      graph->profile = graph->graph->TrackExecution();
      graph->profile_output.open(profile);
      if (!graph->profile_output)
        throw std::runtime_error("Cannot open profile");
    }
    if (*pipeline) {
      std::ofstream out(pipeline);
      graph->graph->Print(out);
      if (!out) throw std::runtime_error("Cannot write pipeline");
    }
    if (memory) graph->scratch = graph->graph->TrackScratchAllocations();
  });
}
int32_t lab_graph_profile_step(LabGraph* graph, const char* name, int32_t rep,
                               size_t step, size_t position, size_t rows,
                               int32_t prefill, int32_t action,
                               LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && name && graph->profile, "No execution profile");
    if (action == 0)
      graph->profile->WriteMetadata(graph->profile_output);
    else if (action == 1)
      graph->profile->BeginStep(name, rep, step, position, rows, prefill != 0);
    else if (action == 2 || action == 3)
      graph->profile->EndStep(graph->profile_output, action == 2);
    else
      throw std::invalid_argument("Invalid profile action");
    if (!graph->profile_output)
      throw std::runtime_error("Cannot write profile");
  });
}
int32_t lab_graph_memory(LabGraph* graph, LabMemory* out,
                         LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && out, "Invalid memory request");
    *out = {};
    out->root = graph->graph->RetainedRootScratchBytes();
    if (graph->scratch) {
      out->live = graph->scratch->live.load();
      out->peak = graph->scratch->peak.load();
      out->allocated = graph->scratch->allocated.load();
      out->allocations = graph->scratch->allocations.load();
    }
  });
}
int32_t lab_resource_bytes(LabGraph* graph, const char* name, const size_t* shape,
                           size_t rank, size_t* out, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && name && out, "Invalid resource geometry query");
    *out = graph->graph->ResourceStorageBytes(name, Shape(shape, rank));
  });
}
int32_t lab_resource_create(LabGraph* graph, const char* name, void* data,
                            size_t bytes, const size_t* shape, size_t rank,
                            LabResource** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(graph && name && data && bytes && out,
               "Invalid resource storage");
    auto resource = std::make_unique<LabResource>();
    resource->state =
        graph->graph->NewResourceState(name, data, bytes, Shape(shape, rank));
    *out = resource.release();
  });
}
int32_t lab_resource_reset(LabResource* resource, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(resource, "Null resource");
    resource->state->Reset();
  });
}
int32_t lab_resource_import(LabResource* resource, size_t prefix,
                            LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(resource, "Null resource");
    resource->state->ImportPrefix(prefix);
  });
}
int32_t lab_resource_status(LabResource* resource, uint64_t values[3],
                            LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(resource && values, "Invalid resource status");
    values[0] = resource->state->committed_extent();
    values[1] = resource->state->reset_epoch();
    values[2] = resource->state->poisoned();
  });
}
int32_t lab_graph_resource(LabGraph* graph, const char* name,
                           LabResource* resource, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(graph && name && resource, "Invalid resource binding");
    graph->graph->BindResource(name, resource->state);
  });
}
uint64_t lab_rss_bytes() noexcept {
  // C++ stream construction may allocate: keep exceptions inside the ABI.
  try {
    std::ifstream f("/proc/self/statm");
    uint64_t total = 0, resident = 0;
    if (f >> total >> resident) return resident * sysconf(_SC_PAGESIZE);
  } catch (...) {
  }
  return 0;
}
uint64_t lab_peak_rss_bytes() noexcept {
  struct rusage usage{};
  return getrusage(RUSAGE_SELF, &usage) == 0 ? uint64_t(usage.ru_maxrss) * 1024
                                             : 0;
}
int32_t lab_allocator_bytes(uint64_t values[3]) noexcept {
  if (!values) return 0;
#ifdef __GLIBC__
#if __GLIBC_PREREQ(2, 33)
  const auto heap = mallinfo2();
  values[0] = heap.uordblks;
  values[1] = heap.fordblks;
  values[2] = heap.hblkhd;
  return 1;
#endif
#endif
  return 0;
}
}  // extern "C"
