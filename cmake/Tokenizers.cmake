# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
# Use the pinned Rust C ABI and SentencePiece processor, without the upstream
# online Cargo build or unused RWKV/MsgPack wrapper.
find_program(LAB_CARGO cargo REQUIRED)
set(LAB_CARGO_HOME "${LAB_DEPS}/cargo" CACHE PATH "Bootstrapped Cargo cache")
set(LAB_RUST_TARGET "" CACHE STRING "Optional Rust target triple (required for cross builds)")
foreach(path tokenizers-cpp/rust/Cargo.lock sentencepiece/CMakeLists.txt)
  if(NOT EXISTS "${LAB_DEPS}/${path}")
    message(FATAL_ERROR "Missing ${path}; run python3 tools/bootstrap.py")
  endif()
endforeach()
set(rust_env "CARGO_HOME=${LAB_CARGO_HOME}" "CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}/cargo")
set(rust_target_args)
set(rust_output "${CMAKE_CURRENT_BINARY_DIR}/cargo/release/libtokenizers_c.a")
if(ANDROID)
  if(NOT ANDROID_ABI STREQUAL "arm64-v8a")
    message(FATAL_ERROR "Tokenizer Android cross build currently supports arm64-v8a")
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
  list(APPEND rust_env "CC_aarch64_linux_android=${ndk_cc}"
       "AR_aarch64_linux_android=${CMAKE_AR}"
       "CARGO_TARGET_AARCH64_LINUX_ANDROID_LINKER=${ndk_cc}")
elseif(CMAKE_CROSSCOMPILING AND NOT LAB_RUST_TARGET)
  message(FATAL_ERROR "Set LAB_RUST_TARGET for a tokenizer cross build")
endif()
if(LAB_RUST_TARGET)
  list(APPEND rust_target_args --target "${LAB_RUST_TARGET}")
  set(rust_output "${CMAKE_CURRENT_BINARY_DIR}/cargo/${LAB_RUST_TARGET}/release/libtokenizers_c.a")
endif()
add_custom_command(OUTPUT "${rust_output}"
  COMMAND ${CMAKE_COMMAND} -E env ${rust_env} ${LAB_CARGO} build --release --frozen
          --manifest-path "${LAB_DEPS}/tokenizers-cpp/rust/Cargo.toml" ${rust_target_args}
  DEPENDS "${LAB_DEPS}/tokenizers-cpp/rust/Cargo.toml"
          "${LAB_DEPS}/tokenizers-cpp/rust/Cargo.lock"
          "${LAB_DEPS}/tokenizers-cpp/rust/src/lib.rs"
  COMMENT "Building pinned HF tokenizer (locked, offline Cargo)"
  VERBATIM)
add_custom_target(lab_hf_tokenizer_build DEPENDS "${rust_output}")
add_library(lab_hf_tokenizer STATIC IMPORTED GLOBAL)
set_target_properties(lab_hf_tokenizer PROPERTIES IMPORTED_LOCATION "${rust_output}")
add_dependencies(lab_hf_tokenizer lab_hf_tokenizer_build)
set(SPM_ENABLE_SHARED OFF CACHE BOOL "" FORCE)
set(SPM_ENABLE_TCMALLOC OFF CACHE BOOL "" FORCE)
set(SPM_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(SPM_LAB_ABSL_DIR "${LAB_DEPS}/abseil")
add_subdirectory("${LAB_DEPS}/sentencepiece" deps/sentencepiece EXCLUDE_FROM_ALL)
find_package(Threads REQUIRED)
target_include_directories(lab_benchmark PRIVATE "${LAB_DEPS}/sentencepiece/src")
target_link_libraries(lab_benchmark PRIVATE lab_hf_tokenizer sentencepiece-static
                      Threads::Threads ${CMAKE_DL_LIBS})
if(UNIX)
  target_link_libraries(lab_benchmark PRIVATE m)
endif()
