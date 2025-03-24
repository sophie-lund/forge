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

# Naming convention

| Type of name               | Convention                                                       | Examples                                                                           |
| -------------------------- | ---------------------------------------------------------------- | ---------------------------------------------------------------------------------- |
| Directory                  | Snake case                                                       | `syntax_tree/`                                                                     |
| File                       | Snake case                                                       | `source_location.hpp`                                                              |
| Class                      | Pascal case                                                      | `SourceLocation`                                                                   |
| Base class                 | Pascal case prefixed with `Base`                                 | `BaseNode`                                                                         |
| Interface class            | Pascal case prefixed with `I`, should describe an action ideally | `IFormatDebug`                                                                     |
| Enum                       | Pascal case                                                      | `TokenType`                                                                        |
| Enum value                 | Snake case                                                       | `value_add`                                                                        |
| Function/variable          | Snake case                                                       | `get_children`                                                                     |
| Public or protected method | Snake case                                                       | `get_children`                                                                     |
| Private method             | Snake case prefixed with `_`                                     | `_get_children`                                                                    |
| Public or protected member | Snake case                                                       | `children`                                                                         |
| Private member             | Snake case prefixed with `_`                                     | `_children`                                                                        |
| Namespaces                 | Snake case                                                       | `forge`                                                                            |
| Global constant            | Screaming snake case                                             | `MAX_NODES`                                                                        |
| Macro                      | Screaming snake case prefixed with `FRG_`                        | `FRG_DEBUG`                                                                        |
| Template parameter         | Pascal case prefixed with `T`                                    | `TNode`                                                                            |
| Google test names          | Snake case containing the full path of the file                  | `parsing_sourcing_source_location` for `parsing/sourcing/source_location.test.cpp` |
| Google test case names     | Snake case                                                       | `simple_happy`                                                                     |
