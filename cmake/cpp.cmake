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

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(FORGE_CXX_FLAGS -Wall -Wextra -fno-rtti -fPIC -Werror)
set(FORGE_LINK_FLAGS -Wall -Wextra -fno-rtti -fPIC -Werror)

if (FORGE_ENABLE_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Code coverage enabled")
        set(FORGE_CXX_FLAGS ${FORGE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage)
        set(FORGE_EXE_LINKER_FLAGS --coverage)
    else()
        message(WARNING "Code coverage is only supported with GCC or Clang")
    endif()
endif()

if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
    set(FORGE_CXX_FLAGS ${FORGE_CXX_FLAGS} -DNDEBUG)
endif()

if (FORGE_BUILD_TESTS)
    set(FORGE_CXX_FLAGS ${FORGE_CXX_FLAGS} -DLT_BUILD_TESTS -DFRG_BUILD_TESTS)
endif()

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(FORGE_CXX_FLAGS ${FORGE_CXX_FLAGS} -DFRG_POINTER_BIT_WIDTH=32)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(FORGE_CXX_FLAGS ${FORGE_CXX_FLAGS} -DFRG_POINTER_BIT_WIDTH=64)
else()
    message(FATAL_ERROR "Only 32 and 64 bit architectures are supported")
endif()
