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

# Getting started

## System dependencies

To build and run this project, you will need the following dependencies installed on your system:

-   **Core build tools**
    -   On macOS: `xcode-select --install`
-   **CMake**
    -   On macOS: `brew install cmake`
-   **Conan**
    -   `pipx install conan`
-   **Doxygen**
    -   On macOS: `brew install doxygen`
-   **MkDocs**
    -   `pipx install mkdocs`
    -   `pipx inject mkdocs mkdocs-material`
-   **LCOV**
    -   On macOS: `brew install lcov`

## Building the project

```shell
make build
```

## Running tests

```shell
make test
```

## Additional reading

See the [`Makefile`](https://github.com/sophie-lund/forge/blob/main/Makefile) for additional commands to run. Also see [Project organization](./project-organization.md) for where to find things within the repository.
