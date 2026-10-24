# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
# Diagnostic host utility using the same compiler as runtime preparation.
if(LAB_BUILD_DIAGNOSTICS AND NOT CMAKE_CROSSCOMPILING)
  set(lab_compile_tool "${CMAKE_CURRENT_BINARY_DIR}/ynn-compile${CMAKE_EXECUTABLE_SUFFIX}")
  set(lab_compile_cargo_dir "${CMAKE_CURRENT_BINARY_DIR}/cargo-compiler")
  add_custom_command(OUTPUT "${lab_compile_tool}"
    COMMAND ${CMAKE_COMMAND} -E env "CARGO_HOME=${LAB_CARGO_HOME}"
      "CARGO_TARGET_DIR=${lab_compile_cargo_dir}" ${LAB_CARGO} build --release --frozen
      --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml" --features diagnostic-tools --bin ynn-compile
    COMMAND ${CMAKE_COMMAND} -E copy "${lab_compile_cargo_dir}/release/ynn-compile" "${lab_compile_tool}"
    DEPENDS ${lab_rust_sources} rust/Cargo.toml rust/Cargo.lock VERBATIM)
  add_custom_target(ynn_compile ALL DEPENDS "${lab_compile_tool}")
endif()

# Semantic authoring/formatting does not enable offline target compilation.
if(NOT CMAKE_CROSSCOMPILING)
  set(lab_authoring_cargo_dir "${CMAKE_CURRENT_BINARY_DIR}/cargo-authoring")
  set(lab_program_tool "${CMAKE_CURRENT_BINARY_DIR}/ynn-program${CMAKE_EXECUTABLE_SUFFIX}")
  add_custom_command(OUTPUT "${lab_program_tool}"
    COMMAND ${CMAKE_COMMAND} -E env "CARGO_HOME=${LAB_CARGO_HOME}"
      "CARGO_TARGET_DIR=${lab_authoring_cargo_dir}" ${LAB_CARGO} build --release --frozen
      --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml" --features authoring-tools --bin ynn-program
    COMMAND ${CMAKE_COMMAND} -E copy "${lab_authoring_cargo_dir}/release/ynn-program" "${lab_program_tool}"
    DEPENDS ${lab_rust_sources} rust/Cargo.toml rust/Cargo.lock VERBATIM)
  add_custom_target(ynn_program ALL DEPENDS "${lab_program_tool}")
  set(lab_qwen_author "${CMAKE_CURRENT_BINARY_DIR}/ynn-qwen3${CMAKE_EXECUTABLE_SUFFIX}")
  add_custom_command(OUTPUT "${lab_qwen_author}"
    COMMAND ${CMAKE_COMMAND} -E env "CARGO_HOME=${LAB_CARGO_HOME}"
      "CARGO_TARGET_DIR=${lab_authoring_cargo_dir}" ${LAB_CARGO} build --release --frozen
      --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml" --features authoring-tools --bin ynn-qwen3
    COMMAND ${CMAKE_COMMAND} -E copy "${lab_authoring_cargo_dir}/release/ynn-qwen3" "${lab_qwen_author}"
    DEPENDS ${lab_rust_sources} rust/Cargo.toml rust/Cargo.lock VERBATIM)
  add_custom_target(ynn_qwen3 ALL DEPENDS "${lab_qwen_author}")
endif()

if(BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
  add_test(NAME model_packages COMMAND ${Python3_EXECUTABLE}
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_model_packages.py --runner $<TARGET_FILE:ynn-llm>)
  if(LAB_BUILD_DIAGNOSTICS)
    add_test(NAME compiler_numerics COMMAND ${Python3_EXECUTABLE}
      ${CMAKE_CURRENT_SOURCE_DIR}/tools/test_compiler_fixtures.py
      --compiler ${lab_compile_tool} --runner $<TARGET_FILE:plan_fixture>
      --known-failures --package-reference ${CMAKE_CURRENT_SOURCE_DIR}/tests/compiler/package_hashes.json)
  endif()
endif()

if(BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
  add_test(NAME compiler_packages COMMAND ${Python3_EXECUTABLE} -m unittest discover
    -s ${CMAKE_CURRENT_SOURCE_DIR}/tests -p test_compiler_packages.py)
  set_tests_properties(compiler_packages PROPERTIES
    ENVIRONMENT "YNNPACK_PROGRAM_TOOL=${lab_program_tool};PYTHONDONTWRITEBYTECODE=1")
endif()
