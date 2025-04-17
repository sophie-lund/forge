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

# Be a little paranoid since we're using 'rm -rf'
if [ -z "${SCRIPT_DIRECTORY}" ] || [ ! -f "${SCRIPT_DIRECTORY}/clean.bash" ]; then
    die_error "Unable to resolve the script directory: '${SCRIPT_DIRECTORY}'"
fi

if [ ! -f "${SCRIPT_DIRECTORY}/../CMakeLists.txt" ] || [ ! -f "${SCRIPT_DIRECTORY}/../README.md" ]; then
    die_error "Unable to resolve the source directory: '${SCRIPT_DIRECTORY}/..'"
fi

# Remove the relevant files
rm -rf "${SCRIPT_DIRECTORY}/../build" "${SCRIPT_DIRECTORY}/../CMakeUserPresets.json"
