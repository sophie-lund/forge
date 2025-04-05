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

# Coding standards

## Overview

- The Forge compiler is written in [C++23](https://en.cppreference.com/w/cpp/23) and [C23](https://en.cppreference.com/w/c/23) where C code is used
- It is formatted using [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) with [Google's style rules](https://google.github.io/styleguide/cppguide.html)
- Unless otherwise specified, code should follow [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- Standards are good to have but they shouldn't get in the way of fast, iterative development
- They also shouldn't get in the way of code working effectively

## Error handling

- Use `std::expected` whenever possible
- Use `MessageContext` when emitting errors during recursive operations where `std::expected` does not make sense
- Use `[[nodiscard]]` for functions that return some kind of status

## Inheritance

- Use `final` instead of `override` whenever possible
