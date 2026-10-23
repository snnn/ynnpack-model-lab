# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
find_program(LAB_CARGO cargo REQUIRED)
set(LAB_CARGO_HOME "${LAB_DEPS}/cargo" CACHE PATH "Bootstrapped Cargo cache")
set(LAB_RUST_TARGET "" CACHE STRING "Optional Rust target triple (required for cross builds)")
set(lab_rust_target_args)
set(lab_rust_env "CARGO_HOME=${LAB_CARGO_HOME}")
set(lab_rust_subdir "release")
if(ANDROID)
  if(NOT ANDROID_ABI STREQUAL "arm64-v8a")
    message(FATAL_ERROR "Rust runtime Android builds currently support arm64-v8a")
  endif()
  if(NOT LAB_RUST_TARGET)
    set(LAB_RUST_TARGET aarch64-linux-android)
  endif()
  if(NOT LAB_RUST_TARGET STREQUAL "aarch64-linux-android")
    message(FATAL_ERROR "arm64-v8a requires LAB_RUST_TARGET=aarch64-linux-android")
  endif()
  get_filename_component(ndk_bin "${CMAKE_C_COMPILER}" DIRECTORY)
  string(REGEX REPLACE "^android-" "" ndk_api "${ANDROID_PLATFORM}")
  set(ndk_cc "${ndk_bin}/aarch64-linux-android${ndk_api}-clang")
  if(NOT EXISTS "${ndk_cc}")
    message(FATAL_ERROR "Missing NDK API compiler: ${ndk_cc}")
  endif()
  list(APPEND lab_rust_env "CC_aarch64_linux_android=${ndk_cc}"
    "AR_aarch64_linux_android=${CMAKE_AR}"
    "CARGO_TARGET_AARCH64_LINUX_ANDROID_LINKER=${ndk_cc}")
elseif(CMAKE_CROSSCOMPILING AND NOT LAB_RUST_TARGET)
  message(FATAL_ERROR "Set LAB_RUST_TARGET for the Rust runtime cross build")
endif()
if(LAB_RUST_TARGET)
  list(APPEND lab_rust_target_args --target "${LAB_RUST_TARGET}")
  set(lab_rust_subdir "${LAB_RUST_TARGET}/release")
endif()
file(GLOB_RECURSE lab_rust_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rust/src/*.rs" "${CMAKE_CURRENT_SOURCE_DIR}/rust/src/*.isle")
list(APPEND lab_rust_sources "${CMAKE_CURRENT_SOURCE_DIR}/rust/build.rs")
find_package(Threads REQUIRED)
include(${CMAKE_CURRENT_LIST_DIR}/RustOperations.cmake)

function(lab_add_rust_library target features)
  set(cargo_dir "${CMAKE_CURRENT_BINARY_DIR}/cargo-${target}")
  set(archive "${cargo_dir}/${lab_rust_subdir}/libynnpack_lab.a")
  add_custom_command(OUTPUT "${archive}"
    BYPRODUCTS "${cargo_dir}/${lab_rust_subdir}/libynnpack_lab.rlib"
    COMMAND ${CMAKE_COMMAND} -E env ${lab_rust_env}
            "CARGO_TARGET_DIR=${cargo_dir}" ${LAB_CARGO} build --lib --release --frozen
            --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml"
            --features "${features}" ${lab_rust_target_args}
    DEPENDS ${lab_rust_sources} rust/Cargo.toml rust/Cargo.lock
    COMMENT "Building Rust runtime (${features}; locked, offline Cargo)"
    VERBATIM)
  add_custom_target(${target}_build DEPENDS "${archive}")
  add_library(${target} STATIC IMPORTED GLOBAL)
  set_target_properties(${target} PROPERTIES IMPORTED_LOCATION "${archive}")
  add_dependencies(${target} ${target}_build)
  target_link_libraries(${target} INTERFACE Threads::Threads ${CMAKE_DL_LIBS} m)
  # Like rustc's executable linker, discard unused Rust codegen sections. The
  # weights-free frontend binaries must not pull in unused backend ABI calls.
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR ANDROID)
    target_link_options(${target} INTERFACE "LINKER:--gc-sections")
  endif()
  if(features MATCHES "tokenizers")
    target_link_libraries(${target} INTERFACE lab_sentencepiece)
  endif()
endfunction()

# Diagnostic plan utility: a host Rust binary with no native backend linkage.
if(NOT CMAKE_CROSSCOMPILING)
  set(lab_plan_tool "${CMAKE_CURRENT_BINARY_DIR}/ynn-plan${CMAKE_EXECUTABLE_SUFFIX}")
  set(lab_plan_cargo_dir "${CMAKE_CURRENT_BINARY_DIR}/cargo-ynn-plan")
  add_custom_command(OUTPUT "${lab_plan_tool}"
    COMMAND ${CMAKE_COMMAND} -E env "CARGO_HOME=${LAB_CARGO_HOME}"
            "CARGO_TARGET_DIR=${lab_plan_cargo_dir}" ${LAB_CARGO} build --release --frozen
            --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml"
            --features plan-tool --bin ynn-plan
    COMMAND ${CMAKE_COMMAND} -E copy
            "${lab_plan_cargo_dir}/release/ynn-plan${CMAKE_EXECUTABLE_SUFFIX}" "${lab_plan_tool}"
    DEPENDS ${lab_rust_sources} rust/Cargo.toml rust/Cargo.lock
    COMMENT "Building handwritten plan parser/printer (locked, offline Cargo)"
    VERBATIM)
  add_custom_target(ynn_plan ALL DEPENDS "${lab_plan_tool}")
endif()

lab_add_rust_library(lab_rust_vision "vision")
add_executable(vision runtime/rust/main.cc runtime/rust/vision.cc
  runtime/rust/bridge.cc runtime/rust/plan.cc third_party/minijson.cc)
target_compile_options(vision PRIVATE -O1)
target_link_libraries(vision PRIVATE lab_rust_vision lab_runtime)

set(lab_probe_features "tokenizer-probe")
set(lab_frontend_test_features "frontend-tests")
if(LAB_ENABLE_TOKENIZERS)
  string(APPEND lab_probe_features ",tokenizers")
  string(APPEND lab_frontend_test_features ",tokenizers")
endif()
lab_add_rust_library(lab_rust_probe "${lab_probe_features}")
add_executable(tokenizer_probe runtime/rust/main.cc)
target_include_directories(tokenizer_probe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(tokenizer_probe PRIVATE lab_rust_probe)
lab_add_rust_library(lab_rust_plan_fixture "fixture")
add_executable(plan_fixture runtime/rust/main.cc runtime/rust/fixture.cc
  runtime/rust/bridge.cc runtime/rust/plan.cc third_party/minijson.cc)
target_compile_options(plan_fixture PRIVATE -O1)
target_link_libraries(plan_fixture PRIVATE lab_rust_plan_fixture lab_runtime)
add_executable(qwen3 runtime/rust/main.cc runtime/rust/fixture.cc
  runtime/rust/embedding.cc runtime/rust/hf.cc
  runtime/rust/bridge.cc runtime/rust/plan.cc third_party/minijson.cc)
target_compile_options(qwen3 PRIVATE -O1)
target_link_libraries(qwen3 PRIVATE lab_rust_llm lab_runtime)
set(lab_llm_features "llm")
if(LAB_ENABLE_TOKENIZERS)
  string(APPEND lab_llm_features ",tokenizers")
endif()
lab_add_rust_library(lab_rust_llm "${lab_llm_features}")
add_executable(ynn-llm runtime/rust/main.cc runtime/rust/fixture.cc
  runtime/rust/embedding.cc runtime/rust/hf.cc runtime/rust/bridge.cc runtime/rust/plan.cc third_party/minijson.cc)
target_compile_options(ynn-llm PRIVATE -O1)
target_compile_definitions(ynn-llm PRIVATE LAB_ENABLE_VALUE_TRACE=1)
target_link_libraries(ynn-llm PRIVATE lab_rust_llm lab_runtime)
foreach(variant e2b e4b)
  add_executable(gemma4_${variant} runtime/rust/main.cc runtime/rust/fixture.cc
    runtime/rust/embedding.cc runtime/rust/hf.cc
    runtime/rust/bridge.cc runtime/rust/plan.cc third_party/minijson.cc)
  target_compile_options(gemma4_${variant} PRIVATE -O1)
  target_compile_definitions(gemma4_${variant} PRIVATE LAB_ENABLE_VALUE_TRACE=1)
  target_link_libraries(gemma4_${variant} PRIVATE lab_rust_llm lab_runtime)
endforeach()

if(BUILD_TESTING)
  lab_add_rust_library(lab_rust_frontend_tests "${lab_frontend_test_features}")
  add_executable(frontend_test runtime/rust/main.cc)
  target_include_directories(frontend_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  target_link_libraries(frontend_test PRIVATE lab_rust_frontend_tests)
  add_test(NAME benchmark_cases COMMAND frontend_test cases
    "${CMAKE_CURRENT_BINARY_DIR}/benchmark-test-data")
  if(LAB_ENABLE_TOKENIZERS)
    add_test(NAME tokenizers COMMAND frontend_test tokenizers
      "${CMAKE_CURRENT_SOURCE_DIR}/tests/tokenizers"
      "${CMAKE_CURRENT_BINARY_DIR}/tokenizer-test-data")
  endif()
  lab_add_rust_library(lab_rust_fixtures "vision,native-tests")
  add_executable(rust_native_test runtime/rust/main.cc runtime/rust/bridge.cc runtime/rust/plan.cc
    tests/rust/fixture.cc tests/state_views_test.cc third_party/minijson.cc)
  target_link_libraries(rust_native_test PRIVATE lab_rust_fixtures lab_runtime)
  target_compile_definitions(rust_native_test PRIVATE LAB_RUNTIME_TEST_HOOKS=1)
  add_dependencies(rust_native_test lab_rust_vision_build)
  target_compile_options(rust_native_test PRIVATE -O1)
  add_test(NAME state_views COMMAND rust_native_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/rust")
  if(NOT CMAKE_CROSSCOMPILING)
    add_test(NAME plan_text COMMAND ${Python3_EXECUTABLE}
      "${CMAKE_CURRENT_SOURCE_DIR}/tests/rust/check_plan_text.py"
      --tool "${lab_plan_tool}" --state-runner "$<TARGET_FILE:rust_native_test>")
    find_program(LAB_RUSTC rustc REQUIRED)
    add_test(NAME rust_borrow_contracts COMMAND ${Python3_EXECUTABLE}
      "${CMAKE_CURRENT_SOURCE_DIR}/tests/rust/check_types.py" --rustc "${LAB_RUSTC}"
      --library "${CMAKE_CURRENT_BINARY_DIR}/cargo-lab_rust_vision/${lab_rust_subdir}/libynnpack_lab.rlib")
    add_test(NAME rust_types COMMAND ${CMAKE_COMMAND} -E env
      "CARGO_HOME=${LAB_CARGO_HOME}" "CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}/cargo-rust-tests"
      ${LAB_CARGO} test --frozen --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml"
      --features vision)
    add_test(NAME rust_gemma_types COMMAND ${CMAKE_COMMAND} -E env
      "CARGO_HOME=${LAB_CARGO_HOME}" "CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}/cargo-rust-tests"
      ${LAB_CARGO} test --frozen --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml"
      --features gemma)
  endif()
endif()

# Backend-independent model names and state lifecycle, using a tiny semantic fixture.
lab_add_rust_library(lab_rust_llm_tests "llm-tests")
add_executable(llm_session_test runtime/rust/main.cc runtime/rust/fixture.cc
  runtime/rust/embedding.cc runtime/rust/hf.cc runtime/rust/bridge.cc runtime/rust/plan.cc third_party/minijson.cc)
target_compile_options(llm_session_test PRIVATE -O1)
target_link_libraries(llm_session_test PRIVATE lab_rust_llm_tests lab_runtime)
if(BUILD_TESTING)
  add_test(NAME llm_session COMMAND llm_session_test
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/llm_session")
endif()
