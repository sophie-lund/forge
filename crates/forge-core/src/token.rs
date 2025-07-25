// Copyright 2025 Sophie Lund
//
// This file is part of Forge.
//
// Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with Forge. If not, see
// <https://www.gnu.org/licenses/>.

use crate::SourceRange;

/// The kind of a token in the Forge language.
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum TokenKind {
    KWBool,
    KWI8,
    KWI16,
    KWI32,
    KWI64,
    KWU8,
    KWU16,
    KWU32,
    KWU64,
    KWF32,
    KWF64,
    Symbol,
    Number,
}

/// A lexical token in the Forge language.
#[derive(Debug, Clone, PartialEq)]
pub struct Token<'ctx> {
    /// The range in the source code from which this token is taken.
    pub range: SourceRange<'ctx>,

    /// The kind of the token.
    pub kind: TokenKind,
}

impl<'ctx> Token<'ctx> {
    /// Creates a new token from components.
    pub fn new(range: SourceRange<'ctx>, kind: TokenKind) -> Self {
        Self { range, kind }
    }
}
