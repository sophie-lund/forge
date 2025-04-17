# Copyright 2025 Sophie Lund
#
# This file is part of Forge.
#
# Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
# General Public License as published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along with Forge. If not, see
# <https://www.gnu.org/licenses/>.

# ------------------------------------------------------------------------------
# PROJECT
# ------------------------------------------------------------------------------

# CMake
cmake_minimum_required(VERSION 3.31)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
set(CMAKE_COLOR_DIAGNOSTICS ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Pre-project CMake includes
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/llvm.cmake)

# Project
project(forge C CXX)

# Post-project CMake includes
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpp.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)

# ------------------------------------------------------------------------------
# LIBRARY: langtools
# ------------------------------------------------------------------------------

add_library(
    lib-langtools
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/codegen/codegen_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/codegen/jit_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/execute_binary.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/init.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/null_streambuf.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/string_utilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/tracing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/unicode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/messaging/message_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/messaging/message.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/messaging/severity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/source_location.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/source_range.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/source.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/token_kind.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/token.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/lexing/base_lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/lexing/lexer_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/reading/grapheme_cluster_reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/reading/line_indexed_unicode_string.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/syntax_parsing/parser_fragments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/syntax_parsing/parsing_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/reporting/get_sample_lines.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/reporting/reporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/domain/base_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/domain/node_kind.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/formatting/debug_formatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/scope/isymbol_resolving_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/scope/scope.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/visitors/ihandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/visitors/ivisitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/visitors/pass.cpp
)
set_target_properties(
    lib-langtools
    PROPERTIES
    OUTPUT_NAME langtools
)
target_compile_options(
    lib-langtools
    PRIVATE
    ${FORGE_CXX_FLAGS}
)
target_link_options(
    lib-langtools
    PRIVATE
    ${FORGE_LINK_FLAGS}
)
target_include_directories(
    lib-langtools
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools
)
target_link_libraries(
    lib-langtools
    PUBLIC
    gtest
    icu::icu
    termcolor::termcolor
    ${LLVM_LIBS}
)

if (FORGE_BUILD_TESTS)
    add_executable(
        test-unit-langtools
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/codegen/codegen_context.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/execute_binary.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/math_utilities.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/string_utilities.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/null_streambuf.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/core/init.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/messaging/message_context.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/messaging/message.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/messaging/severity.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/reading/grapheme_cluster_reader.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/reading/line_indexed_unicode_string.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/domain/base_node.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/formatting/debug_formatter.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/operations/casting.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/operations/cloners.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/operations/comparators.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/scope/scope.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/syntax_tree/scope/symbol_resolution_handler.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/source_location.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/domain/source_range.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/lexing/lexer_context.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/parsing/syntax_parsing/parsing_context.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/langtools/reporting/get_sample_lines.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/tests/setup.cpp
    )
    target_compile_options(
        test-unit-langtools
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        test-unit-langtools
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        test-unit-langtools
        lib-langtools
        gtest_main
    )

    add_executable(
        test-functional-langtools
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/tests/functional/example_language.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/tests/setup.cpp
    )
    target_compile_options(
        test-functional-langtools
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        test-functional-langtools
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        test-functional-langtools
        lib-langtools
        gtest_main
    )
endif()

if (FORGE_BUILD_DEMOS)
    add_executable(
        demo-langtools-abort
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/demos/demo_abort.cpp
    )
    target_compile_options(
        demo-langtools-abort
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        demo-langtools-abort
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        demo-langtools-abort
        lib-langtools
    )

    add_executable(
        demo-langtools-assert
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/demos/demo_assert.cpp
    )
    target_compile_options(
        demo-langtools-assert
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        demo-langtools-assert
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        demo-langtools-assert
        lib-langtools
    )

    add_executable(
        demo-langtools-reporting
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/demos/demo_reporting.cpp
    )
    target_compile_options(
        demo-langtools-reporting
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        demo-langtools-reporting
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        demo-langtools-reporting
        lib-langtools
    )

    add_executable(
        demo-langtools-syntax-tree-debug-formatter
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/langtools/demos/demo_syntax_tree_debug_formatter.cpp
    )
    target_compile_options(
        demo-langtools-syntax-tree-debug-formatter
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        demo-langtools-syntax-tree-debug-formatter
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        demo-langtools-syntax-tree-debug-formatter
        lib-langtools
    )
endif()

# ------------------------------------------------------------------------------
# LIBRARY: forgec
# ------------------------------------------------------------------------------

add_library(
    lib-forgec
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/forge_codegen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/forge_formatters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/forge_message_emitters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/handlers/iforge_handler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/handlers/validation/type_resolution.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/handlers/validation/type_validation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/handlers/validation/well_formed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/parsing/forge_lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/parsing/forge_parsers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/base_forge_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/base_declaration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_function.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_namespace.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_structured_type.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_type_alias.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_variable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/base_statement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_basic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_block.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_if.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_value.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_while.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/translation_unit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/base_type.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_basic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_function.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_structured.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_symbol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_unary.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_with_bit_width.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/base_value.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_binary.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_call.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_cast.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_literal_bool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_literal_number.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_symbol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_unary.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/testing/integration_test_harness.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/type_logic/get_arithmetic_containing_type.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/type_logic/get_casting_mode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/type_logic/type_predicates.cpp
)
set_target_properties(
    lib-forgec
    PROPERTIES
    OUTPUT_NAME forgec
)
target_compile_options(
    lib-forgec
    PRIVATE
    ${FORGE_CXX_FLAGS}
)
target_link_options(
    lib-forgec
    PRIVATE
    ${FORGE_LINK_FLAGS}
)
target_include_directories(
    lib-forgec
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec
)
target_link_libraries(
    lib-forgec
    PUBLIC
    lib-langtools
    gtest
    termcolor::termcolor
    ${LLVM_LIBS}
)

if (FORGE_BUILD_TESTS)
    add_executable(
        test-unit-forgec
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/parsing/forge_lexer.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/parsing/forge_parsers.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_function.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_namespace.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_structured_type.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_type_alias.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/declarations/declaration_variable.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_basic.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_block.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_if.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_value.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/statements/statement_while.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/translation_unit.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_basic.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_function.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_structured.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_symbol.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_unary.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/types/type_with_bit_width.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_binary.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_call.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_cast.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_literal_bool.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_literal_number.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_symbol.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/syntax_tree/values/value_unary.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/forgec/type_logic/type_predicates.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/setup.cpp
    )
    target_compile_options(
        test-unit-forgec
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        test-unit-forgec
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        test-unit-forgec
        lib-forgec
        gtest_main
    )

    add_executable(
        test-functional-forgec
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/add.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bit_and.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bit_not.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bit_or.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bit_shl.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bit_shr.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bit_xor.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bool_and.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bool_not.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/bool_or.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/detect_evens.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/div.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/eq.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/function_returns_zero.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/ge.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/gt.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/identity_function.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/le.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/lt.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/mod.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/mul.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/ne.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/neg.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/pos.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/pure_math/sub.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/functional/std_samples/limits.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/setup.cpp
    )
    target_compile_options(
        test-functional-forgec
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        test-functional-forgec
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        test-functional-forgec
        lib-forgec
        gtest_main
    )

    add_executable(
        test-fuzz-forgec
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/fuzz/fuzz_lexer_binary.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cpp/forgec/tests/setup.cpp
    )
    target_link_options(
        test-fuzz-forgec
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        test-fuzz-forgec
        PRIVATE
        lib-forgec
    )
    link_fuzztest(test-fuzz-forgec)
endif()

# ------------------------------------------------------------------------------
# BINARY: forgec
# ------------------------------------------------------------------------------

add_executable(
    bin-forgec
    ${CMAKE_CURRENT_SOURCE_DIR}/binaries/cpp/forgec/forgec/main.cpp
)
set_target_properties(
    bin-forgec
    PROPERTIES
    OUTPUT_NAME forgec
)
target_compile_options(
    bin-forgec
    PRIVATE
    ${FORGE_CXX_FLAGS}
)
target_link_options(
    bin-forgec
    PRIVATE
    ${FORGE_LINK_FLAGS}
    ${FORGE_EXE_LINKER_FLAGS}
)
target_link_libraries(
    bin-forgec
    lib-forgec
)

# ------------------------------------------------------------------------------
# EXTERNAL TESTS
# ------------------------------------------------------------------------------

if (FORGE_BUILD_TESTS)
    add_executable(
        test-external
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/external/llvm.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/setup.cpp
    )
    target_compile_options(
        test-external
        PRIVATE
        ${FORGE_CXX_FLAGS}
    )
    target_link_options(
        test-external
        PRIVATE
        ${FORGE_LINK_FLAGS}
        ${FORGE_EXE_LINKER_FLAGS}
    )
    target_link_libraries(
        test-external
        lib-langtools
        gtest_main
    )
endif()
