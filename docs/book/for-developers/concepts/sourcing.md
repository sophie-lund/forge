<!--
Copyright 2025 Sophie Lund

This file is part of Forge.

Forge is free software: you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
License for more details.

You should have received a copy of the GNU General Public License along with Forge. If not, see
<https://www.gnu.org/licenses/>.
-->

# Sourcing

Sourcing is how source code is loaded from various sources and read. It can be read from files on disk or strings in memory. Source code is also ephemeral - it may be edited by a developer at any time.

## Unicode characters and column numbers

Column numbers are simple in ASCII because a symbol on screen is one byte. But with Unicode, one symbol on screen can be represented with many bytes. For example, this is a single symbol - try selecting it:

> ﷽

This single symbol is made up of the following 3 bytes `ef b7 bd`, but still is treated as one single symbol by editors. Thus we should treat it as one column for [error reporting](https://www.gnu.org/prep/standards/standards.html#Errors).

The Unicode standard uses the term [**extended grapheme clusters**](https://www.unicode.org/reports/tr29/#Grapheme_Cluster_Boundaries) to refer to a single symbol on screen. In order to keep things simple, Forge treats source code as a sequence of extended grapheme clusters. When iterating over them, each cluster either takes up a single column or is a newline character.

## Terminology

- **Source** - one file or string that contains source code.
- **Grapheme** - the source code calls extended grapheme clusters "graphemes" for brevity, much like the [`unicode_segmentation`](https://docs.rs/unicode-segmentation/latest/unicode_segmentation/) crate.
- **Source location** - a reference to a specific grapheme in source code containing the byte offset, line number, and column number.
- **Source range** - a span of source code between two source locations, implemented as one location and a length in bytes.

## Lookahead and lexing

Forge's lexer is implemented by hand, so to keep things simple source code is read one grapheme at a time but with a one-grapheme lookahead. This means that you can both read and peek the next grapheme.
