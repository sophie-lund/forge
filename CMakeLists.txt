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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-rtti -fPIC -fsanitize=address")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Dependencies
find_package(Boost REQUIRED COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(termcolor REQUIRED)

# Libraries
add_library(
    forge
    STATIC
    forge/core/Tracing.cpp
    forge/messaging/Message.cpp
    forge/messaging/MessageContext.cpp
    forge/messaging/Severity.cpp
    forge/parsing/sourcing/LineIndexedString.cpp
    forge/parsing/sourcing/domain/Source.cpp
    forge/parsing/sourcing/domain/SourceLocation.cpp
    forge/parsing/sourcing/domain/SourceRange.cpp
)
target_link_libraries(
    forge
    PUBLIC
    termcolor::termcolor
)

# Tests
add_executable(
    test-forge
    forge/messaging/MessageContext.test.cpp
    forge/messaging/Message.test.cpp
    forge/messaging/Severity.test.cpp
    forge/parsing/sourcing/LineIndexedString.test.cpp
    forge/syntaxtree/operations/Cloners.test.cpp
    forge/syntaxtree/operations/Comparators.test.cpp
    forge/syntaxtree/formatting/DebugFormatter.test.cpp
    forge/syntaxtree/domain/Node.test.cpp
    forge/syntaxtree/scope/Scope.test.cpp
    forge/syntaxtree/scope/SymbolResolutionHandler.test.cpp
    tests/functional/ExampleLanguage.cpp
)
target_link_libraries(
    test-forge
    gtest::gtest
    termcolor::termcolor
    forge
)

# Demos
add_executable(demo-forge-command-line demos/DemoCommandLine.cpp)
target_link_libraries(
    demo-forge-command-line
    Boost::program_options
    forge
)

add_executable(demo-forge-syntaxtree-debug-formatter demos/DemoSyntaxTreeDebugFormatter.cpp)
target_link_libraries(
    demo-forge-syntaxtree-debug-formatter
    termcolor::termcolor
    forge
)
