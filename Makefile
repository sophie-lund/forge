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

.PHONY: build clean ref docs

build:
	conan install . --output-folder=build --build=missing --settings=build_type=Debug
	cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja
	cmake --build build

test: build
	cd build && ./test-forge

clean:
	rm -rf build ./CMakeUserPresets.json

ref:
	@cd docs && doxygen Doxyfile
	@echo
	@echo "Open: file://$(realpath docs/ref/html/index.html)"

docs:
	cd docs && mkdocs build

docs-serve:
	cd docs && mkdocs serve
