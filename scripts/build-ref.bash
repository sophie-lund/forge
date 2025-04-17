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

# Build ref
(cd "${SOURCE_DIRECTORY}/docs" && doxygen Doxyfile)

log_info "Reference available at: file://${SOURCE_DIRECTORY}/docs/ref/html/index.html"
