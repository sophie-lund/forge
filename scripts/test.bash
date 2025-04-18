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
BUILD_DIRECTORY="${SCRIPT_DIRECTORY}/../build"

# Declare functions
function run_all_tests_with_prefix() {
    for FILE in $(find "${BUILD_DIRECTORY}" -iname "$1" -type f -perm +111); do
        FILE_BASENAME="$(basename "${FILE}")"
        
        log_info "Running test: ${FILE_BASENAME}"
        
        if ! (cd "${BUILD_DIRECTORY}" && ASAN_OPTIONS=detect_container_overflow=0 "${FILE}"); then
            die_error "Test failed: ${FILE_BASENAME}"
        fi
    done
}

function generate_coverage_report() {
    if ! lcov \
        --capture \
        --directory "${BUILD_DIRECTORY}" \
        --output-file "${BUILD_DIRECTORY}/coverage.info" \
        --erase-functions \
        __cxx_global_var_init \
        --ignore-errors unsupported \
        --rc derive_function_end_line=0; then
        die_error "Failed to gather coverage info"
    fi

	if ! lcov \
        --remove "${BUILD_DIRECTORY}/coverage.info" \
        '/usr/*' \
        '/opt/*' \
        '*.conan2*' \
        '*/tests/*' \
        '*.test.cpp' \
        '*/_deps/*' \
        --output-file "${BUILD_DIRECTORY}/coverage.info" \
        --rc derive_function_end_line=0 \
        --ignore-errors unused; then
        die_error "Failed to filter coverage info"
    fi

	if ! genhtml "${BUILD_DIRECTORY}/coverage.info" \
        --output-directory "${BUILD_DIRECTORY}/coverage-report" \
        --ignore-errors inconsistent,corrupt,category; then
        die_error "Failed to generate HTML coverage report"
    fi

    log_info "Coverage report available at: file://${BUILD_DIRECTORY}/coverage-report/index.html"
}

# If no arguments are passed, run all non-fuzz, non-bench tests
if [ -z "$1" ]; then
    "${SCRIPT_DIRECTORY}/build.bash" debug

    run_all_tests_with_prefix 'test-external'
    run_all_tests_with_prefix 'test-unit-*'
    run_all_tests_with_prefix 'test-functional-*'

    exit 0
fi

# Gather coverage info for all relevant tests
if [ "$1" == "coverage" ]; then
    # Clean and build first
    "${SCRIPT_DIRECTORY}/clean.bash"
    "${SCRIPT_DIRECTORY}/build.bash" debug:coverage

    # Then run tests in arbitrary order
    run_all_tests_with_prefix 'test-unit-*'
    run_all_tests_with_prefix 'test-functional-*'

    # And generate coverage report
    generate_coverage_report

    exit 0
fi

# Gather coverage info for only unit tests
if [ "$1" == "coverage:unit" ]; then
    # Clean and build first
    "${SCRIPT_DIRECTORY}/clean.bash"
    "${SCRIPT_DIRECTORY}/build.bash" debug:coverage

    # Then run tests in arbitrary order
    run_all_tests_with_prefix 'test-unit-*' "${@:2}"

    # And generate coverage report
    generate_coverage_report

    exit 0
fi

# Run only fuzz tests in unit test mode
if [ "$1" == "fuzz" ] && [ -z "$2" ]; then
    # Build first
    "${SCRIPT_DIRECTORY}/build.bash" debug:fuzz

    # Then run tests in arbitrary order
    run_all_tests_with_prefix 'test-fuzz-*'

    exit 0
fi

# Run a specific fuzz test in fuzz mode
if [ "$1" == "fuzz" ] && [ -n "$2" ]; then
    # Build first
    "${SCRIPT_DIRECTORY}/build.bash" debug:fuzz

    # Find the test binary
    if [ ! -f "${BUILD_DIRECTORY}/$2" ]; then
        die_error "Test binary not found: ${BUILD_DIRECTORY}/$2"
    fi

    # Fuzz
    if [ -z "$3" ]; then
        die_error "Fuzz test requires a filter argument"
    fi

    ASAN_OPTIONS=detect_container_overflow=0 "${BUILD_DIRECTORY}/$2" "--fuzz=$3" "${@:4}"

    exit 0
fi

# Run a specific bench test
if [ "$1" == "bench" ]; then
    if [ -z "$2" ]; then
        die_error "Bench test requires a test name argument"
    fi

    # Build first
    "${SCRIPT_DIRECTORY}/build.bash"

    # Find the test binary
    if [ ! -f "${BUILD_DIRECTORY}/$2" ]; then
        die_error "Test binary not found: ${BUILD_DIRECTORY}/$2"
    fi

    ASAN_OPTIONS=detect_container_overflow=0 "${BUILD_DIRECTORY}/$2" "${@:3}"

    exit 0
fi

# Run a specific test
if [ -n "$1" ]; then
    # Build first
    "${SCRIPT_DIRECTORY}/build.bash"

    # Find the test binary
    if [ ! -f "${BUILD_DIRECTORY}/$1" ]; then
        die_error "Test binary not found: ${BUILD_DIRECTORY}/$1"
    fi

    ASAN_OPTIONS=detect_container_overflow=0 "${BUILD_DIRECTORY}/$1" "${@:2}"

    exit 0
fi
