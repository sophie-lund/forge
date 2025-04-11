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

# CMake
cmake_minimum_required(VERSION 3.31)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
set(CMAKE_COLOR_DIAGNOSTICS ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Support LLVM from Homebrew
if(EXISTS "/opt/homebrew/opt/llvm/bin/llvm-config")
    execute_process(
        COMMAND /opt/homebrew/opt/llvm/bin/llvm-config --cmakedir
        OUTPUT_VARIABLE LLVM_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    list(APPEND CMAKE_PREFIX_PATH ${LLVM_CMAKE_DIR})
else()
    execute_process(
        COMMAND llvm-config --cmakedir
        OUTPUT_VARIABLE LLVM_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    list(APPEND CMAKE_PREFIX_PATH ${LLVM_CMAKE_DIR})
endif()

# Project
project(forge C CXX)

# C/C++ configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-rtti -fPIC -Werror")
set(CMAKE_LINK_FLAGS "${CMAKE_LINK_FLAGS} -Wall -Wextra -fno-rtti -fPIC -Werror")

# Dependencies
find_package(Boost REQUIRED COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(termcolor REQUIRED)
find_package(ICU REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR} ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(
    LLVM_LIBS
    core
    executionengine
    irreader
    native
    nativecodegen
    orcjit
    support
)

# Libraries
add_library(
    forge
    STATIC
    forge/codegen/codegen_context.cpp
    forge/codegen/jit_context.cpp
    forge/core/execute_binary.cpp
    forge/core/init.cpp
    forge/core/null_streambuf.cpp
    forge/core/tracing.cpp
    forge/core/string_utilities.cpp
    forge/core/unicode.cpp
    forge/reporting/reporter.cpp
    forge/reporting/get_sample_lines.cpp
    forge/language/handlers/validation/well_formed.cpp
    forge/language/handlers/iforge_handler.cpp
    forge/language/forge_codegen.cpp
    forge/language/type_logic/get_arithmetic_containing_type.cpp
    forge/language/type_logic/type_predicates.cpp
    forge/language/type_logic/get_casting_mode.cpp
    forge/language/handlers/validation/type_resolution.cpp
    forge/language/handlers/validation/type_validation.cpp
    forge/language/parsing/forge_lexer.cpp
    forge/language/parsing/forge_parsers.cpp
    forge/language/forge_formatters.cpp
    forge/language/forge_message_emitters.cpp
    forge/language/syntax_tree/base_forge_node.cpp
    forge/language/syntax_tree/types/base_type.cpp
    forge/language/syntax_tree/types/type_basic.cpp
    forge/language/syntax_tree/types/type_with_bit_width.cpp
    forge/language/syntax_tree/types/type_function.cpp
    forge/language/syntax_tree/types/type_unary.cpp
    forge/language/syntax_tree/types/type_structured.cpp
    forge/language/syntax_tree/types/type_symbol.cpp
    forge/language/syntax_tree/values/base_value.cpp
    forge/language/syntax_tree/values/value_literal_bool.cpp
    forge/language/syntax_tree/values/value_literal_number.cpp
    forge/language/syntax_tree/values/value_symbol.cpp
    forge/language/syntax_tree/values/value_unary.cpp
    forge/language/syntax_tree/values/value_binary.cpp
    forge/language/syntax_tree/values/value_cast.cpp
    forge/language/syntax_tree/values/value_call.cpp
    forge/language/syntax_tree/statements/base_statement.cpp
    forge/language/syntax_tree/statements/statement_value.cpp
    forge/language/syntax_tree/statements/statement_if.cpp
    forge/language/syntax_tree/statements/statement_while.cpp
    forge/language/syntax_tree/statements/statement_basic.cpp
    forge/language/syntax_tree/statements/statement_block.cpp
    forge/language/syntax_tree/declarations/base_declaration.cpp
    forge/language/syntax_tree/declarations/declaration_variable.cpp
    forge/language/syntax_tree/declarations/declaration_function.cpp
    forge/language/syntax_tree/declarations/declaration_structured_type.cpp
    forge/language/syntax_tree/declarations/declaration_type_alias.cpp
    forge/language/syntax_tree/declarations/declaration_namespace.cpp
    forge/language/syntax_tree/translation_unit.cpp
    forge/messaging/message_context.cpp
    forge/messaging/message.cpp
    forge/messaging/severity.cpp
    forge/parsing/domain/source_location.cpp
    forge/parsing/domain/source_range.cpp
    forge/parsing/domain/source.cpp
    forge/parsing/domain/token_kind.cpp
    forge/parsing/domain/token.cpp
    forge/parsing/lexing/base_lexer.cpp
    forge/parsing/lexing/lexer_context.cpp
    forge/parsing/reading/grapheme_cluster_reader.cpp
    forge/parsing/reading/line_indexed_unicode_string.cpp
    forge/parsing/syntax_parsing/parser_fragments.cpp
    forge/parsing/syntax_parsing/parsing_context.cpp
    forge/syntax_tree/domain/base_node.cpp
    forge/syntax_tree/domain/node_kind.cpp
    forge/syntax_tree/formatting/debug_formatter.cpp
    forge/syntax_tree/scope/isymbol_resolving_node.cpp
    forge/syntax_tree/scope/scope.cpp
    forge/syntax_tree/visitors/ihandler.cpp
    forge/syntax_tree/visitors/ivisitor.cpp
    forge/syntax_tree/visitors/pass.cpp
    forge/testing/integration_test_harness.cpp
)
target_link_libraries(
    forge
    PUBLIC
    gtest::gtest
    icu::icu
    termcolor::termcolor
    ${LLVM_LIBS}
)

# Tests
add_executable(
    test-forge
    forge/codegen/codegen_context.test.cpp
    forge/core/execute_binary.test.cpp
    forge/core/math_utilities.test.cpp
    forge/messaging/message_context.test.cpp
    forge/language/syntax_tree/types/type_basic.test.cpp
    forge/language/syntax_tree/types/type_with_bit_width.test.cpp
    forge/language/syntax_tree/types/type_symbol.test.cpp
    forge/language/syntax_tree/types/type_unary.test.cpp
    forge/language/syntax_tree/types/type_function.test.cpp
    forge/language/syntax_tree/types/type_structured.test.cpp
    forge/language/syntax_tree/values/value_literal_bool.test.cpp
    forge/language/syntax_tree/values/value_literal_number.test.cpp
    forge/language/syntax_tree/values/value_symbol.test.cpp
    forge/language/syntax_tree/values/value_unary.test.cpp
    forge/language/syntax_tree/values/value_binary.test.cpp
    forge/language/syntax_tree/values/value_cast.test.cpp
    forge/language/syntax_tree/values/value_call.test.cpp
    forge/language/syntax_tree/statements/statement_basic.test.cpp
    forge/language/syntax_tree/statements/statement_value.test.cpp
    forge/language/syntax_tree/statements/statement_if.test.cpp
    forge/language/syntax_tree/statements/statement_while.test.cpp
    forge/language/syntax_tree/statements/statement_block.test.cpp
    forge/language/syntax_tree/declarations/declaration_variable.test.cpp
    forge/language/syntax_tree/declarations/declaration_type_alias.test.cpp
    forge/language/syntax_tree/declarations/declaration_function.test.cpp
    forge/language/syntax_tree/declarations/declaration_namespace.test.cpp
    forge/language/syntax_tree/declarations/declaration_structured_type.test.cpp
    forge/language/syntax_tree/translation_unit.test.cpp
    forge/language/type_logic/type_predicates.test.cpp
    forge/messaging/message.test.cpp
    forge/messaging/severity.test.cpp
    forge/language/parsing/forge_lexer.test.cpp
    forge/language/parsing/forge_parsers.test.cpp
    forge/parsing/reading/grapheme_cluster_reader.test.cpp
    forge/parsing/reading/line_indexed_unicode_string.test.cpp
    forge/syntax_tree/domain/base_node.test.cpp
    forge/syntax_tree/formatting/debug_formatter.test.cpp
    forge/syntax_tree/operations/cloners.test.cpp
    forge/syntax_tree/operations/casting.test.cpp
    forge/syntax_tree/operations/comparators.test.cpp
    forge/syntax_tree/scope/scope.test.cpp
    forge/syntax_tree/scope/symbol_resolution_handler.test.cpp
    tests/external/llvm.test.cpp
    tests/integration/example_language.test.cpp
    tests/integration/pure_math/function_returns_zero.test.cpp
    tests/integration/pure_math/identity_function.test.cpp
    tests/integration/pure_math/single_operators.test.cpp
    tests/setup.cpp
)
target_link_libraries(
    test-forge
    forge
    gtest::gtest
)

# Demos
add_executable(demo-forge-command-line demos/demo_command_line.cpp)
target_link_libraries(
    demo-forge-command-line
    Boost::program_options
    forge
)

add_executable(demo-forge-syntaxtree-debug-formatter demos/demo_syntax_tree_debug_formatter.cpp)
target_link_libraries(
    demo-forge-syntaxtree-debug-formatter
    forge
)

add_executable(demo-forge-reporting demos/demo_reporting.cpp)
target_link_libraries(
    demo-forge-reporting
    forge
)

add_executable(demo-forge-assert demos/demo_assert.cpp)
target_link_libraries(
    demo-forge-assert
    forge
)

add_executable(demo-forge-abort demos/demo_abort.cpp)
target_link_libraries(
    demo-forge-abort
    forge
)

# Binaries
add_executable(forge-cli forge/main.cpp)
target_link_libraries(
    forge-cli
    forge
)
set_target_properties(forge-cli PROPERTIES OUTPUT_NAME forge)
