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

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Configuration
configure_file(ForgeConfig.hpp.in ForgeConfig.hpp)

# Dependencies
find_package(Boost REQUIRED COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(termcolor REQUIRED)

# Libraries
add_library(
    forge
    STATIC
    lib/core/Tracing.cpp
    lib/messaging/Message.cpp
    lib/messaging/MessageContext.cpp
    lib/messaging/Severity.cpp
    lib/parsing/sourcing/Domain.cpp
    lib/parsing/sourcing/LineIndexedString.cpp
)
target_link_libraries(
    forge
    PUBLIC
    termcolor::termcolor
)

# Tests
add_executable(
    test-forge
    lib/messaging/MessageContextTest.cpp
    lib/messaging/MessageTest.cpp
    lib/messaging/SeverityTest.cpp
    lib/parsing/sourcing/LineIndexedStringTest.cpp
    lib/syntaxtree/ClonersTest.cpp
    lib/syntaxtree/ComparatorsTest.cpp
    lib/syntaxtree/DebugFormatterTest.cpp
    lib/syntaxtree/NodeTest.cpp
    lib/syntaxtree/ScopeTest.cpp
    lib/syntaxtree/SymbolResolutionHandlerTest.cpp
    test/ExampleLanguage.cpp
)
target_link_libraries(
    test-forge
    gtest::gtest
    termcolor::termcolor
    forge
)

# Demos
add_executable(demo-forge-command-line demo/DemoCommandLine.cpp)
target_link_libraries(demo-forge-command-line Boost::program_options)

add_executable(demo-forge-syntaxtree-debug-formatter demo/DemoSyntaxTreeDebugFormatter.cpp)
target_link_libraries(
    demo-forge-syntaxtree-debug-formatter
    termcolor::termcolor
)
