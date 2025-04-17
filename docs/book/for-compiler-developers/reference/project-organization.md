<!--
Copyright 2025 Sophie Lund

This file is part of Forge.

Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with Forge. If not, see
<https://www.gnu.org/licenses/>.
-->

# Project organization

Forge's code is stored as a monorepo, which means there's a lot of different types of code all in one place. The repository's directory structure aims to make it easier to navigate.

## Directory structure

-   **`binaries/`** - Source code for binaries that can be executed
    -   `cpp/` - Binaries written in C++ (see [C++ project structure](#c-project-structure) how these binary projects are structured)
    -   `forge/` - Binaries written in Forge
-   **`docs/`** - Documentation for the project
    -   `book/` - The book (what you're reading right now)
    -   `ref/` - C++ library reference (this is automatically generated and is not in source control)
-   **`libraries/`** - Source code for libraries
    -   `cpp/` - Libraries written in C++ (see [C++ project structure](#c-project-structure) how these library projects are structured)
    -   `forge/` - Libraries written in Forge
-   **`scripts/`** - Scripts to automate common tasks
-   **`tests/`** - Source code for tests that are not specific to any one library or command
    -   **`external/`** - Tests for external libraries to make sure they work as expected
        -   `cpp/`
        -   ...
    -   **`integration/`** - Tests that span multiple libraries or components
        -   `cpp/`
        -   `bash/` - BASH scripts that run integration tests
        -   ...
    -   **`regression/`** - Regression tests
        -   `cpp/`
        -   `forge/`
        -   `bash/`
        -   ...

## C++ project structure

Forge uses the canonical project structure [proposed by Boris Kolpackov](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html) for C++ code.

-   **`<project name>/`** - The root directory of the project
    -   **`<project name>/`** - C++ source code
        -   `<file name>.hpp` - Header file
        -   `<file name>.cpp` - Source file
        -   `<file name>.test.cpp` - Unit test file
        -   ...
    -   **`tests/`** - Tests for the library
        -   `functional/` - Functional tests
        -   `demo/` - Demos
        -   `fuzz/` - Fuzz tests
        -   `bench/` - Benchmarks
