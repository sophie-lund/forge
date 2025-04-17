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

find_package(Boost REQUIRED COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(termcolor REQUIRED)
find_package(ICU REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
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
