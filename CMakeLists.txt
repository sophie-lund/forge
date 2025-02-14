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

# Project
project(forge C CXX)

# C/C++ configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-rtti -fPIC -fsanitize=address -Werror")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Dependencies
find_package(Boost REQUIRED COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(termcolor REQUIRED)

# Libraries
add_library(
    forge
    STATIC
    forge/core/tracing.cpp
    forge/messaging/message.cpp
    forge/messaging/message_context.cpp
    forge/messaging/severity.cpp
    forge/parsing/sourcing/line_indexed_string.cpp
    forge/parsing/sourcing/domain/source.cpp
    forge/parsing/sourcing/domain/source_location.cpp
    forge/parsing/sourcing/domain/source_range.cpp
    forge/syntax_tree/domain/base_node.cpp
    forge/syntax_tree/domain/node_kind.cpp
    forge/syntax_tree/formatting/debug_formatter.cpp
    forge/syntax_tree/visitors/handler.cpp
    forge/syntax_tree/visitors/pass.cpp
    # forge/syntax_tree/scope/scope.cpp
)
target_link_libraries(
    forge
    PUBLIC
    termcolor::termcolor
)

# Tests
add_executable(
    test-forge
    forge/messaging/message_context.test.cpp
    forge/messaging/message.test.cpp
    forge/messaging/severity.test.cpp
    forge/parsing/sourcing/line_indexed_string.test.cpp
    forge/syntax_tree/operations/cloners.test.cpp
    forge/syntax_tree/operations/comparators.test.cpp
    forge/syntax_tree/formatting/debug_formatter.test.cpp
    forge/syntax_tree/domain/base_node.test.cpp
    # forge/syntax_tree/scope/scope.test.cpp
    # forge/syntax_tree/scope/symbol_resolution_handler.test.cpp
    # tests/functional/example_language.cpp
)
target_link_libraries(
    test-forge
    gtest::gtest
    termcolor::termcolor
    forge
)

# Demos
# add_executable(demo-forge-command-line demos/demo_command_line.cpp)
# target_link_libraries(
#     demo-forge-command-line
#     Boost::program_options
#     forge
# )

# add_executable(demo-forge-syntaxtree-debug-formatter demos/demo_syntax_tree_debug_formatter.cpp)
# target_link_libraries(
#     demo-forge-syntaxtree-debug-formatter
#     termcolor::termcolor
#     forge
# )
