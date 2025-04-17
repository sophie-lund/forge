#!/bin/bash

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

set +e

# Get script directory
SCRIPT_DIRECTORY="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Load common functions
. "${SCRIPT_DIRECTORY}/common.bash"

# Evaluate paths
SOURCE_DIRECTORY="${SCRIPT_DIRECTORY}/.."
BUILD_DIRECTORY="${SCRIPT_DIRECTORY}/../build"

# Get arguments
BUILD_MODE="$1"

# Declare functions
function install_conan_dependencies_debug() {
    log_info "Installing Conan dependencies with build type Debug"

    if ! conan install "${SOURCE_DIRECTORY}" \
        "--output-folder=${BUILD_DIRECTORY}" \
        --build=missing \
        --settings=build_type=Debug; then
        die_error "Conan install failed"
    fi
}

function install_conan_dependencies_release() {
    log_info "Installing Conan dependencies with build type Release"

    if ! conan install "${SOURCE_DIRECTORY}" \
        "--output-folder=${BUILD_DIRECTORY}" \
        --build=missing \
        --settings=build_type=Release; then
        die_error "Conan install failed"
    fi
}

function configure_cmake_debug() {
    log_info "Configuring CMake build with build type Debug"

    if ! cmake \
        -B "${BUILD_DIRECTORY}" \
        -S "${SOURCE_DIRECTORY}" \
        -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DFORGE_BUILD_TESTS=on \
        -DFORGE_BUILD_DEMOS=on \
        -DFORGE_ENABLE_COVERAGE=off \
        -DFUZZTEST_FUZZING_MODE=off \
        -G Ninja; then
        die_error "CMake configure failed"
    fi
}

function configure_cmake_debug_coverage() {
    log_info "Configuring CMake build with build type Debug and coverage enabled"

    if ! cmake \
        -B "${BUILD_DIRECTORY}" \
        -S "${SOURCE_DIRECTORY}" \
        -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DFORGE_BUILD_TESTS=on \
        -DFORGE_BUILD_DEMOS=on \
        -DFORGE_ENABLE_COVERAGE=on \
        -DFUZZTEST_FUZZING_MODE=off \
        -G Ninja; then
        die_error "CMake configure failed"
    fi
}

function configure_cmake_debug_fuzz() {
    log_info "Configuring CMake build with build type Debug and fuzzing mode enabled"

    if ! cmake \
        -B "${BUILD_DIRECTORY}" \
        -S "${SOURCE_DIRECTORY}" \
        -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DFORGE_BUILD_TESTS=on \
        -DFORGE_BUILD_DEMOS=on \
        -DFORGE_ENABLE_COVERAGE=off \
        -DFUZZTEST_FUZZING_MODE=on \
        -G Ninja; then
        die_error "CMake configure failed"
    fi
}

function configure_cmake_release() {
    log_info "Configuring CMake build with build type Release"
    
    if ! cmake \
        -B "${BUILD_DIRECTORY}" \
        -S "${SOURCE_DIRECTORY}" \
        -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DFORGE_BUILD_TESTS=off \
        -DFORGE_BUILD_DEMOS=off \
        -DFORGE_ENABLE_COVERAGE=off \
        -DFUZZTEST_FUZZING_MODE=off \
        -G Ninja; then
        die_error "CMake configure failed"
    fi
}

function build_project() {
    log_info "Building project"

    if ! cmake --build "${BUILD_DIRECTORY}"; then
        exit 1
    fi
}

# Build
case "${BUILD_MODE}" in
    "debug")
        install_conan_dependencies_debug
        configure_cmake_debug
        build_project
        ;;
    "debug:coverage")
        install_conan_dependencies_debug
        configure_cmake_debug_coverage
        build_project
        ;;
    "debug:fuzz")
        install_conan_dependencies_debug
        configure_cmake_debug_fuzz
        build_project
        ;;
    "release")
        install_conan_dependencies_release
        configure_cmake_release
        build_project
        ;;
    "")
        build_project
        ;;
    *)
        echo "error: invalid build mode"
        echo
        echo "valid are:"
        echo "  debug"
        echo "  debug:coverage"
        echo "  debug:fuzz"
        echo "  release"
        exit 1
        ;;
esac
