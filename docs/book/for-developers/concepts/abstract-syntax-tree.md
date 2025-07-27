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

# Abstract Syntax Tree (AST)

The AST is implemented as a tree of structs that represent parsed Forge code. The structs are written by hand which has the advantage of quicker implementation and better optimization, but it also means that code consistency needs to be maintained manually. Make sure to follow these guidelines when adding new structs.

## Code map

All of the code is defined in [`crates/forge-core/src/ast/*`](https://github.com/sophie-lund/forge/tree/main/crates/forge-core/src/ast). It's split up into files by concern:

- [`structs.rs`](https://github.com/sophie-lund/forge/blob/main/crates/forge-core/src/ast/structs.rs): Where the structs themselves are defined.
- [`traits.rs`](https://github.com/sophie-lund/forge/blob/main/crates/forge-core/src/ast/traits.rs): The traits that the structs must implement to provide shared functionality.
- [`impls.rs`](https://github.com/sophie-lund/forge/blob/main/crates/forge-core/src/ast/impls.rs): The implementations of the traits in `traits.rs` for the structs in `structs.rs`. This code can be hard to read and repetitive, so it's put in a separate file so keep the other two files more readable.

## Adding a new AST node type

This is an example struct definition in `structs.rs`:

```rust
#[derive(Debug, Clone, Serialize)]
pub struct ExprCall<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub callee: Box<Expr<'sctx>>,

    pub args: Vec<Expr<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for ExprCall<'ctx> {}
```

Let's go through it step by step.

All of them must implement the `Debug`, `Clone`, and `Serialize` traits. These can be automatically derived:

```rust
#[derive(Debug, Clone, Serialize)]
```

Then the struct needs to contain some standard attributes. Right now the only one is `source_range`, but this may expand in the future:

```rust
#[serde(rename = "sourceRange")]
pub source_range: Option<SourceRange<'sctx>>,
```

!!! todo

    This page needs to be expanded.

## Adding a new category of AST nodes
