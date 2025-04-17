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

# Support LLVM from Homebrew
if (EXISTS "/opt/homebrew/opt/llvm/bin/llvm-config")
    set(FORGE_LLVM_CONFIG_BIN "/opt/homebrew/opt/llvm/bin/llvm-config")
else()
    set(FORGE_LLVM_CONFIG_BIN "llvm-config")
endif()

# Get CMake directories from llvm-config
execute_process(
    COMMAND ${FORGE_LLVM_CONFIG_BIN} --cmakedir
    OUTPUT_VARIABLE LLVM_CMAKE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Add them to the prefix path
list(APPEND CMAKE_PREFIX_PATH ${LLVM_CMAKE_DIR})
