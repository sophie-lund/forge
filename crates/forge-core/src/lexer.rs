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

use thiserror::Error;

use crate::{SourceError, SourceLocation, SourceRange, SourceRef, Token, TokenKind};

#[derive(Error, Debug)]
pub enum LexingError {
    #[error("source error: {0}")]
    SourceError(#[from] SourceError),
}

struct LexerState<'ctx> {
    first_location: SourceLocation<'ctx>,
    last_location: SourceLocation<'ctx>,
    tokens: Vec<Token<'ctx>>,
}

impl<'ctx> LexerState<'ctx> {
    fn new(first_location: SourceLocation<'ctx>) -> Self {
        Self {
            first_location: first_location.clone(),
            last_location: first_location,
            tokens: Vec::new(),
        }
    }

    fn are_more_graphemes(&self) -> bool {
        self.last_location.offset < self.last_location.source.content.len()
    }

    fn peek_next_grapheme(&self) -> Result<String, LexingError> {
        Ok(self.last_location.peek_next_grapheme()?)
    }

    fn read_next_grapheme(&mut self) -> Result<String, LexingError> {
        Ok(self.last_location.read_next_grapheme()?)
    }

    fn current_range(&self) -> SourceRange<'ctx> {
        SourceRange::new_from_locations(&self.first_location, &self.last_location)
    }

    fn skip_token(&mut self) {
        self.first_location = self.last_location.clone()
    }

    fn push_token(&mut self, kind: TokenKind) {
        let token = Token::new(self.current_range(), kind);

        self.tokens.push(token);
        self.skip_token();
    }
}

fn is_whitespace(grapheme: &str) -> bool {
    grapheme.chars().all(|c| c.is_whitespace())
}

fn is_symbol_start(grapheme: &str) -> bool {
    return grapheme
        .chars()
        .all(|c| c.is_ascii_alphabetic() || c == '_' || !c.is_ascii());
}

fn is_symbol_continuation(grapheme: &str) -> bool {
    return grapheme
        .chars()
        .all(|c| c.is_ascii_alphanumeric() || c == '_' || !c.is_ascii());
}

fn is_digit(grapheme: &str) -> bool {
    grapheme.chars().all(|c| c.is_ascii_digit())
}

pub fn lex(source: SourceRef<'_>) -> Result<Vec<Token<'_>>, LexingError> {
    let mut state = LexerState::new(source.start());

    while state.are_more_graphemes() {
        let grapheme = state.peek_next_grapheme()?;

        if is_whitespace(&grapheme) {
            state.read_next_grapheme()?;
            state.skip_token();
        } else if is_symbol_start(&grapheme) {
            state.read_next_grapheme()?;

            while state.are_more_graphemes() {
                let grapheme = state.peek_next_grapheme()?;
                if is_symbol_continuation(&grapheme) {
                    state.read_next_grapheme()?;
                } else {
                    break;
                }
            }

            match state.current_range().content()? {
                "bool" => state.push_token(TokenKind::KWBool),
                "i8" => state.push_token(TokenKind::KWI8),
                "i16" => state.push_token(TokenKind::KWI16),
                "i32" => state.push_token(TokenKind::KWI32),
                "i64" => state.push_token(TokenKind::KWI64),
                "u8" => state.push_token(TokenKind::KWU8),
                "u16" => state.push_token(TokenKind::KWU16),
                "u32" => state.push_token(TokenKind::KWU32),
                "u64" => state.push_token(TokenKind::KWU64),
                "f32" => state.push_token(TokenKind::KWF32),
                "f64" => state.push_token(TokenKind::KWF64),
                _ => state.push_token(TokenKind::Symbol),
            }
        } else if is_digit(&grapheme) {
            state.read_next_grapheme()?;

            while state.are_more_graphemes() {
                let grapheme = state.peek_next_grapheme()?;
                if is_symbol_continuation(&grapheme) {
                    state.read_next_grapheme()?;
                } else {
                    break;
                }
            }

            state.push_token(TokenKind::Number); // Placeholder for numeric tokens
        } else {
            panic!("invalid character");
        }
    }

    Ok(state.tokens)
}

#[cfg(test)]
mod tests {
    use crate::SourceContext;

    use super::*;

    #[test]
    fn test_smoke() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "i32 x 123".to_owned())
            .unwrap();

        let tokens = lex(source).unwrap();

        assert_eq!(tokens.len(), 3);
        assert_eq!(tokens[0].kind, TokenKind::KWI32);
        assert_eq!(tokens[0].range.content().unwrap(), "i32");
        assert_eq!(tokens[1].kind, TokenKind::Symbol);
        assert_eq!(tokens[1].range.content().unwrap(), "x");
        assert_eq!(tokens[2].kind, TokenKind::Number);
        assert_eq!(tokens[2].range.content().unwrap(), "123");
    }
}
