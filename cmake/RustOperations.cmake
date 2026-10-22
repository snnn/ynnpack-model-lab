# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
# One operation library is shared by Rust runners and direct C++ graph tests.
# It has no application entry point and contains the sole blockwise policy.
file(GLOB_RECURSE lab_operation_sources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/rust/operations/src/*.rs"
  "${CMAKE_CURRENT_SOURCE_DIR}/rust/operations/src/*.isle")
set(lab_operations_dir "${CMAKE_CURRENT_BINARY_DIR}/cargo-operations")
set(lab_operations_archive "${lab_operations_dir}/${lab_rust_subdir}/libynnpack_operations.a")
add_custom_command(OUTPUT "${lab_operations_archive}"
  COMMAND ${CMAKE_COMMAND} -E env ${lab_rust_env}
    "CARGO_TARGET_DIR=${lab_operations_dir}" ${LAB_CARGO} build --lib --release --frozen
    --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/operations/Cargo.toml" ${lab_rust_target_args}
  DEPENDS ${lab_operation_sources} rust/operations/Cargo.toml
    rust/operations/Cargo.lock rust/operations/build.rs
  VERBATIM)
add_custom_target(lab_operations_build DEPENDS "${lab_operations_archive}")
add_library(lab_operations STATIC IMPORTED GLOBAL)
set_target_properties(lab_operations PROPERTIES IMPORTED_LOCATION "${lab_operations_archive}")
add_dependencies(lab_operations lab_operations_build)
target_link_libraries(lab_operations INTERFACE Threads::Threads ${CMAKE_DL_LIBS} m)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR ANDROID)
  target_link_options(lab_operations INTERFACE "LINKER:--gc-sections")
endif()
add_library(lab_dot_bridge STATIC runtime/rust/dot.cc)
target_include_directories(lab_dot_bridge PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(lab_dot_bridge PRIVATE -O1 -ffp-contract=off)
target_link_libraries(lab_dot_bridge PRIVATE ynnpack slinky_thread_pool_impl)
target_link_libraries(lab_runtime INTERFACE lab_operations lab_dot_bridge)
if(BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
  add_test(NAME rust_operations COMMAND ${CMAKE_COMMAND} -E env ${lab_rust_env}
    "CARGO_TARGET_DIR=${lab_operations_dir}" ${LAB_CARGO} test --frozen
    --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/operations/Cargo.toml")
endif()
