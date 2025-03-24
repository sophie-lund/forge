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
    forge/core/unicode.cpp
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
    forge/parsing/syntax_parsing/syntax_parsing_context.cpp
    forge/syntax_tree/domain/base_node.cpp
    forge/syntax_tree/domain/node_kind.cpp
    forge/syntax_tree/formatting/debug_formatter.cpp
    forge/syntax_tree/scope/isymbol_resolving_node.cpp
    forge/syntax_tree/scope/scope.cpp
    forge/syntax_tree/visitors/ihandler.cpp
    forge/syntax_tree/visitors/ivisitor.cpp
    forge/syntax_tree/visitors/pass.cpp
)
target_link_libraries(
    forge
    PUBLIC
    icu::icu
    termcolor::termcolor
    ${LLVM_LIBS}
)

# Tests
add_executable(
    test-forge
    forge/codegen/codegen_context.test.cpp
    forge/core/execute_binary.test.cpp
    forge/messaging/message_context.test.cpp
    forge/messaging/message.test.cpp
    forge/messaging/severity.test.cpp
    forge/parsing/reading/grapheme_cluster_reader.test.cpp
    forge/parsing/reading/line_indexed_unicode_string.test.cpp
    forge/syntax_tree/domain/base_node.test.cpp
    forge/syntax_tree/formatting/debug_formatter.test.cpp
    forge/syntax_tree/operations/cloners.test.cpp
    forge/syntax_tree/operations/comparators.test.cpp
    forge/syntax_tree/scope/scope.test.cpp
    forge/syntax_tree/scope/symbol_resolution_handler.test.cpp
    tests/external/llvm.test.cpp
    tests/integration/example_language.test.cpp
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

# Binaries
add_executable(forge-cli forge/main.cpp)
target_link_libraries(
    forge-cli
    forge
)
set_target_properties(forge-cli PROPERTIES OUTPUT_NAME forge)
