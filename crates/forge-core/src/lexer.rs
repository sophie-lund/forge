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

use crate::{
    MessageSeverity, OutputMessage, SourceError, SourceLocation, SourceRange, SourceRef, Token,
    TokenKind,
};

#[derive(Error, Debug)]
pub enum LexingError {
    #[error("source error: {0}")]
    SourceError(#[from] SourceError),
}

struct LexerState<'sctx> {
    first_location: SourceLocation<'sctx>,
    last_location: SourceLocation<'sctx>,
    tokens: Vec<Token<'sctx>>,
}

impl<'sctx> LexerState<'sctx> {
    fn new(first_location: SourceLocation<'sctx>) -> Self {
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

    fn current_range(&self) -> SourceRange<'sctx> {
        SourceRange::new_from_locations(&self.first_location, &self.last_location)
    }

    fn skip_token(&mut self) {
        assert!(
            self.current_range().byte_length > 0,
            "cannot skip empty token"
        );

        self.first_location = self.last_location.clone()
    }

    fn push_token(&mut self, kind: TokenKind) {
        assert!(
            self.current_range().byte_length > 0,
            "cannot push empty token"
        );

        let token = Token::new(self.current_range(), kind);

        self.tokens.push(token);
        self.skip_token();
    }
}

fn is_whitespace(grapheme: &str) -> bool {
    assert!(!grapheme.is_empty(), "grapheme cannot be empty");

    grapheme.chars().all(|c| c.is_whitespace())
}

fn is_symbol_start(grapheme: &str) -> bool {
    assert!(!grapheme.is_empty(), "grapheme cannot be empty");

    return grapheme
        .chars()
        .all(|c| c.is_ascii_alphabetic() || c == '_' || !c.is_ascii());
}

fn is_symbol_continuation(grapheme: &str) -> bool {
    assert!(!grapheme.is_empty(), "grapheme cannot be empty");

    return grapheme
        .chars()
        .all(|c| c.is_ascii_alphanumeric() || c == '_' || !c.is_ascii());
}

fn is_digit(grapheme: &str) -> bool {
    assert!(!grapheme.is_empty(), "grapheme cannot be empty");

    grapheme.chars().all(|c| c.is_ascii_digit())
}

pub fn lex<'sctx>(
    source: SourceRef<'sctx>,
    msg: &mut impl OutputMessage<'sctx>,
) -> Result<Vec<Token<'sctx>>, LexingError> {
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
                "true" => state.push_token(TokenKind::KWTrue),
                "false" => state.push_token(TokenKind::KWFalse),
                "return" => state.push_token(TokenKind::KWReturn),
                "if" => state.push_token(TokenKind::KWIf),
                "else" => state.push_token(TokenKind::KWElse),
                "while" => state.push_token(TokenKind::KWWhile),
                "do" => state.push_token(TokenKind::KWDo),
                "continue" => state.push_token(TokenKind::KWContinue),
                "break" => state.push_token(TokenKind::KWBreak),
                "fn" => state.push_token(TokenKind::KWFn),
                "let" => state.push_token(TokenKind::KWLet),
                _ => state.push_token(TokenKind::Symbol),
            }
        } else if is_digit(&grapheme) {
            state.read_next_grapheme()?;

            while state.are_more_graphemes() {
                let grapheme = state.peek_next_grapheme()?;
                if grapheme == "e" {
                    state.read_next_grapheme()?;

                    if state.are_more_graphemes() && state.peek_next_grapheme()? == "-" {
                        state.read_next_grapheme()?;
                    }
                } else if grapheme == "." {
                    state.read_next_grapheme()?;
                } else if is_symbol_continuation(&grapheme) {
                    state.read_next_grapheme()?;
                } else {
                    break;
                }
            }

            state.push_token(TokenKind::Number);
        } else if grapheme == "!" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::NE);
            } else {
                state.push_token(TokenKind::LogNot);
            }
        } else if grapheme == "|" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "|" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::LogOr);
            } else if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::BitOrAssign);
            } else {
                state.push_token(TokenKind::BitOr);
            }
        } else if grapheme == "&" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "&" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::LogAnd);
            } else if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::BitAndAssign);
            } else {
                state.push_token(TokenKind::BitAnd);
            }
        } else if grapheme == "~" {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::BitNot);
        } else if grapheme == "^" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::BitXorAssign);
            } else {
                state.push_token(TokenKind::BitXor);
            }
        } else if grapheme == "<" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "<" {
                state.read_next_grapheme()?;

                if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                    state.read_next_grapheme()?;

                    state.push_token(TokenKind::BitShLAssign);
                } else {
                    state.push_token(TokenKind::BitShL);
                }
            } else if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;

                state.push_token(TokenKind::LE);
            } else {
                state.push_token(TokenKind::LT);
            }
        } else if grapheme == ">" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == ">" {
                state.read_next_grapheme()?;

                if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                    state.read_next_grapheme()?;

                    state.push_token(TokenKind::BitShRAssign);
                } else {
                    state.push_token(TokenKind::BitShR);
                }
            } else if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;

                state.push_token(TokenKind::GE);
            } else {
                state.push_token(TokenKind::GT);
            }
        } else if grapheme == "=" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::EQ);
            } else {
                state.push_token(TokenKind::Assign);
            }
        } else if grapheme == "+" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::AddAssign);
            } else {
                state.push_token(TokenKind::Add);
            }
        } else if grapheme == "-" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::SubAssign);
            } else {
                state.push_token(TokenKind::Sub);
            }
        } else if grapheme == "*" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::MulAssign);
            } else {
                state.push_token(TokenKind::Mul);
            }
        } else if grapheme == "/" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::DivAssign);
            } else {
                state.push_token(TokenKind::Div);
            }
        } else if grapheme == "%" {
            state.read_next_grapheme()?;

            if state.are_more_graphemes() && state.peek_next_grapheme()? == "=" {
                state.read_next_grapheme()?;
                state.push_token(TokenKind::ModAssign);
            } else {
                state.push_token(TokenKind::Mod);
            }
        } else if grapheme == "(" {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::LParen);
        } else if grapheme == ")" {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::RParen);
        } else if grapheme == "," {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::Comma);
        } else if grapheme == "{" {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::LBrace);
        } else if grapheme == "}" {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::RBrace);
        } else if grapheme == ";" {
            state.read_next_grapheme()?;

            state.push_token(TokenKind::Semicolon);
        } else {
            state.read_next_grapheme()?;

            msg.output_message(
                state.current_range(),
                MessageSeverity::Error,
                format!("unexpected character: {:?}", grapheme),
            );

            state.skip_token();
        }
    }

    Ok(state.tokens)
}

#[cfg(test)]
mod tests {
    use crate::{MessageBuffer, SourceContext};

    use super::*;

    #[test]
    fn test_smoke() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string(
                "test.frg".to_owned(),
                r#"
                bool
                i8
                i16
                i32
                i64
                u8
                u16
                u32
                u64
                f32
                f64
                true
                false
                return
                if
                else
                while
                do
                continue
                break
                fn
                let
                x
                _1
                ﷽
                ❤️
                5
                1_000
                5.3
                1.2e5
                1.2e-5
                3____
                !
                &&
                ||
                ~
                &
                |
                ^
                <<
                >>
                +
                -
                *
                /
                %
                <
                <=
                >
                >=
                !=
                ==
                =
                &=
                |=
                ^=
                <<=
                >>=
                +=
                -=
                *=
                /=
                %=
                (
                )
                ,
                {
                }
                ;
                `
            "# // the last ` is an invalid character
                .to_owned(),
            )
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 69);
        let mut index = 0;

        assert_eq!(tokens[index].kind, TokenKind::KWBool);
        assert_eq!(tokens[index].range.content().unwrap(), "bool");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWI8);
        assert_eq!(tokens[index].range.content().unwrap(), "i8");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWI16);
        assert_eq!(tokens[index].range.content().unwrap(), "i16");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWI32);
        assert_eq!(tokens[index].range.content().unwrap(), "i32");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWI64);
        assert_eq!(tokens[index].range.content().unwrap(), "i64");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWU8);
        assert_eq!(tokens[index].range.content().unwrap(), "u8");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWU16);
        assert_eq!(tokens[index].range.content().unwrap(), "u16");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWU32);
        assert_eq!(tokens[index].range.content().unwrap(), "u32");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWU64);
        assert_eq!(tokens[index].range.content().unwrap(), "u64");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWF32);
        assert_eq!(tokens[index].range.content().unwrap(), "f32");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWF64);
        assert_eq!(tokens[index].range.content().unwrap(), "f64");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWTrue);
        assert_eq!(tokens[index].range.content().unwrap(), "true");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWFalse);
        assert_eq!(tokens[index].range.content().unwrap(), "false");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWReturn);
        assert_eq!(tokens[index].range.content().unwrap(), "return");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWIf);
        assert_eq!(tokens[index].range.content().unwrap(), "if");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWElse);
        assert_eq!(tokens[index].range.content().unwrap(), "else");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWWhile);
        assert_eq!(tokens[index].range.content().unwrap(), "while");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWDo);
        assert_eq!(tokens[index].range.content().unwrap(), "do");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWContinue);
        assert_eq!(tokens[index].range.content().unwrap(), "continue");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWBreak);
        assert_eq!(tokens[index].range.content().unwrap(), "break");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWFn);
        assert_eq!(tokens[index].range.content().unwrap(), "fn");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::KWLet);
        assert_eq!(tokens[index].range.content().unwrap(), "let");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Symbol);
        assert_eq!(tokens[index].range.content().unwrap(), "x");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Symbol);
        assert_eq!(tokens[index].range.content().unwrap(), "_1");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Symbol);
        assert_eq!(tokens[index].range.content().unwrap(), "﷽");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Symbol);
        assert_eq!(tokens[index].range.content().unwrap(), "❤️");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Number);
        assert_eq!(tokens[index].range.content().unwrap(), "5");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Number);
        assert_eq!(tokens[index].range.content().unwrap(), "1_000");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Number);
        assert_eq!(tokens[index].range.content().unwrap(), "5.3");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Number);
        assert_eq!(tokens[index].range.content().unwrap(), "1.2e5");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Number);
        assert_eq!(tokens[index].range.content().unwrap(), "1.2e-5");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Number);
        assert_eq!(tokens[index].range.content().unwrap(), "3____");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LogNot);
        assert_eq!(tokens[index].range.content().unwrap(), "!");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LogAnd);
        assert_eq!(tokens[index].range.content().unwrap(), "&&");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LogOr);
        assert_eq!(tokens[index].range.content().unwrap(), "||");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitNot);
        assert_eq!(tokens[index].range.content().unwrap(), "~");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitAnd);
        assert_eq!(tokens[index].range.content().unwrap(), "&");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitOr);
        assert_eq!(tokens[index].range.content().unwrap(), "|");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitXor);
        assert_eq!(tokens[index].range.content().unwrap(), "^");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitShL);
        assert_eq!(tokens[index].range.content().unwrap(), "<<");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitShR);
        assert_eq!(tokens[index].range.content().unwrap(), ">>");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Add);
        assert_eq!(tokens[index].range.content().unwrap(), "+");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Sub);
        assert_eq!(tokens[index].range.content().unwrap(), "-");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Mul);
        assert_eq!(tokens[index].range.content().unwrap(), "*");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Div);
        assert_eq!(tokens[index].range.content().unwrap(), "/");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Mod);
        assert_eq!(tokens[index].range.content().unwrap(), "%");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LT);
        assert_eq!(tokens[index].range.content().unwrap(), "<");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LE);
        assert_eq!(tokens[index].range.content().unwrap(), "<=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::GT);
        assert_eq!(tokens[index].range.content().unwrap(), ">");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::GE);
        assert_eq!(tokens[index].range.content().unwrap(), ">=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::NE);
        assert_eq!(tokens[index].range.content().unwrap(), "!=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::EQ);
        assert_eq!(tokens[index].range.content().unwrap(), "==");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Assign);
        assert_eq!(tokens[index].range.content().unwrap(), "=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitAndAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "&=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitOrAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "|=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitXorAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "^=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitShLAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "<<=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::BitShRAssign);
        assert_eq!(tokens[index].range.content().unwrap(), ">>=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::AddAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "+=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::SubAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "-=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::MulAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "*=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::DivAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "/=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::ModAssign);
        assert_eq!(tokens[index].range.content().unwrap(), "%=");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LParen);
        assert_eq!(tokens[index].range.content().unwrap(), "(");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::RParen);
        assert_eq!(tokens[index].range.content().unwrap(), ")");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Comma);
        assert_eq!(tokens[index].range.content().unwrap(), ",");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::LBrace);
        assert_eq!(tokens[index].range.content().unwrap(), "{");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::RBrace);
        assert_eq!(tokens[index].range.content().unwrap(), "}");
        index += 1;

        assert_eq!(tokens[index].kind, TokenKind::Semicolon);
        assert_eq!(tokens[index].range.content().unwrap(), ";");
        index += 1;

        assert_eq!(index, 69);
        assert_eq!(msg.messages.len(), 1);
    }
}
