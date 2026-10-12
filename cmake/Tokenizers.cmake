# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
# HF tokenizers is a direct Rust dependency. Only SentencePiece needs a C ABI.
foreach(path sentencepiece/CMakeLists.txt abseil/CMakeLists.txt)
  if(NOT EXISTS "${LAB_DEPS}/${path}")
    message(FATAL_ERROR "Missing ${path}; run python3 tools/bootstrap.py")
  endif()
endforeach()
set(SPM_ENABLE_SHARED OFF CACHE BOOL "" FORCE)
set(SPM_ENABLE_TCMALLOC OFF CACHE BOOL "" FORCE)
set(SPM_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(SPM_LAB_ABSL_DIR "${LAB_DEPS}/abseil")
add_subdirectory("${LAB_DEPS}/sentencepiece" deps/sentencepiece EXCLUDE_FROM_ALL)
add_library(lab_sentencepiece STATIC runtime/rust/sentencepiece.cc)
target_include_directories(lab_sentencepiece PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${LAB_DEPS}/sentencepiece/src")
target_link_libraries(lab_sentencepiece PUBLIC sentencepiece-static)
