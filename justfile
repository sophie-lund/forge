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

# Build Forge with an optional build mode.
build mode="":
    #!/usr/bin/env bash
    set -eu
    
    . ./scripts/dx-scripts/lib/cxx.bash

    build_cxx \
        FORGE \
        "{{justfile_directory()}}" \
        "{{justfile_directory()}}/build" \
        debug \
        "{{mode}}"

test:
    #!/usr/bin/env bash
    set -eu
    
    . ./scripts/dx-scripts/lib/cxx.bash

    test_cxx \
        FORGE \
        "{{justfile_directory()}}" \
        "{{justfile_directory()}}/build" \
        all

clean:
    #!/usr/bin/env bash
    set -eu
    
    rm -rf build CMakeUserPresets.json CMakeCache.txt dist docs/ref docs/site

build-book:
    #!/usr/bin/env bash
    set -eu
    
    (cd "docs" && mkdocs build)

serve-book:
    #!/usr/bin/env bash
    set -eu
    
    (cd "docs" && mkdocs serve)

build-ref:
    #!/usr/bin/env bash
    set -eu

    . ./scripts/dx-scripts/lib/logging.bash
    
    (cd "docs" && doxygen Doxyfile)

    log_info "Reference available at: file://{{justfile_directory()}}/docs/ref/html/index.html"
