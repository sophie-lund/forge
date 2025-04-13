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

.PHONY: build test coverage clean ref docs docs-serve

build:
	conan install . --output-folder=build --build=missing --settings=build_type=Debug
	cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja
	cmake --build build

test: build
	cd build && ./test-forge

coverage: test
	lcov --capture --directory build --output-file build/coverage.info --erase-functions __cxx_global_var_init --ignore-errors unsupported --rc derive_function_end_line=0
	lcov --remove build/coverage.info '/usr/*' '/opt/*' '*.conan2*' '*/tests/*' '*.test.cpp' --output-file build/coverage.info --rc derive_function_end_line=0 --ignore-errors unused
	genhtml build/coverage.info --output-directory build/coverage-report --ignore-errors inconsistent,corrupt,category
	@echo
	@echo "Open: file://$$(realpath build/coverage-report/index.html)"

clean:
	rm -rf build ./CMakeUserPresets.json

ref:
	@cd docs && doxygen Doxyfile
	@echo
	@echo "Open: file://$$(realpath docs/ref/html/index.html)"

docs:
	cd docs && mkdocs build

docs-serve:
	cd docs && mkdocs serve
