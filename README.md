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

# Toy Language

Yep. Back at _this_ shit again.

## Target architecture

- Lexer capable of reading in extended grapheme clusters
- An AST capable of:
  - Storing FQNs
  - Storing scoped symbol tables
- A recursive descent parser
- A FQN resolver that builds a scoped symbol tables
- A system for making queries about the language model (see https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#languageFeatures)
  - What declaration is being referred to by this symbol?
  - What type is this expression?
  - What other code references this declaration?
  - etc.
- A system for rule checking about the language model
  - Do the operands to an addition operator combine to create a valid output?
  - Does the returned expression's type match the return type of the surrounding function?
  - etc.

## Cross-cutting concerns

- Everything must be multi-threadable
- Everything must have a cancellation token
  - How do you support cancellation without function coloring?

## Data model

- Message
  - These will be created and destroyed frequently, so they should have minimal memory footprints
- Token
- AST Node
  - Can be parsed or synthetic
  - Can be marked as dirty by an edit
  - Needs easy traversal in all directions
- FQN
- Symbol Table
- Predicate
  - Something that takes one or more AST nodes and returns a boolean
- Query
  - Something that can be run against the language model and which returns results
- Rule
  - Something that can be run against the language model and which returns zero or more errors

## Declaration queries

**If you have a symbol, how do you find its declaration?**

Iteratively increase scope, starting at the current scope and increasing to parent scopes in turn.

## Type queries

**If you have an expression, how do you find its type?**

Ideally, it would be based entirely on the expression itself. Just recursively find the types of child expressions and combine them in turn.

**If you have a declaration, how do you find its type?**

Ideally, build the type directly one-to-one from the top-level declaration node. For functions with inferred return types, you'd have to look at the return statements.

## Running rules

You can apply rules to nodes in the AST. They aren't always applicable based on the rule predicate. But to fully check a translation unit you can just visit the whole tree and apply rules to every node.
