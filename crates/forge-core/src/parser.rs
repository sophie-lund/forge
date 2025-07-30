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

use std::num;

use crate::{
    Expr, ExprBool, ExprFloat, ExprInt, IsNode, MessageSeverity, OutputMessage, SourceRange, Token,
    TokenKind, Type, TypeBool, TypeFloat, TypeInt, TypeMissing, TypePointer,
};

#[derive(Clone)]
struct ParserState<'sctx, 'tokens> {
    tokens: &'tokens [Token<'sctx>],
    index: usize,
}

impl<'sctx, 'tokens> ParserState<'sctx, 'tokens> {
    fn new(tokens: &'tokens [Token<'sctx>]) -> Self {
        Self { tokens, index: 0 }
    }

    fn are_more_tokens(&self) -> bool {
        self.index < self.tokens.len()
    }

    fn peek_next_token(&self) -> &'tokens Token<'sctx> {
        assert!(
            self.are_more_tokens(),
            "no more tokens available to peek at"
        );

        &self.tokens[self.index]
    }

    fn read_next_token(&mut self) -> &'tokens Token<'sctx> {
        assert!(
            self.are_more_tokens(),
            "no more tokens available to peek at"
        );

        self.index += 1;

        &self.tokens[self.index - 1]
    }
}

fn try_parse<'sctx, 'tokens, TNode, TOutputMessage, TParser>(
    state: &mut ParserState<'sctx, 'tokens>,
    msgs: &mut TOutputMessage,
    parser: TParser,
) -> Option<TNode>
where
    TNode: IsNode<'sctx>,
    TOutputMessage: OutputMessage<'sctx>,
    TParser: Fn(&mut ParserState<'sctx, 'tokens>, &mut TOutputMessage) -> Option<TNode>,
{
    let state_save = state.clone();

    let node = parser(state, msgs);

    if node.is_some() {
        node
    } else {
        *state = state_save;
        None
    }
}

fn is_at_type_ending<'sctx, 'tokens>(state: &ParserState<'sctx, 'tokens>) -> bool {
    if !state.are_more_tokens() {
        return true;
    }

    let token = state.peek_next_token();

    match token.kind {
        TokenKind::KWTrue
        | TokenKind::KWFalse
        | TokenKind::KWReturn
        | TokenKind::KWIf
        | TokenKind::KWElse
        | TokenKind::KWWhile
        | TokenKind::KWBreak
        | TokenKind::KWContinue
        | TokenKind::KWFn
        | TokenKind::KWLet
        | TokenKind::Assign
        | TokenKind::RParen
        | TokenKind::Comma
        | TokenKind::RBrace
        | TokenKind::Semicolon => true,
        _ => false,
    }
}

fn parse_type_bool<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    _msgs: &mut impl OutputMessage<'sctx>,
) -> Option<TypeBool<'sctx>> {
    if !state.are_more_tokens() {
        return None;
    }

    let token = state.read_next_token();

    if token.kind == TokenKind::KWBool {
        Some(TypeBool::new_from_source(token.range.clone()))
    } else {
        None
    }
}

fn parse_type_int<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    _msgs: &mut impl OutputMessage<'sctx>,
) -> Option<TypeInt<'sctx>> {
    if !state.are_more_tokens() {
        return None;
    }

    let token = state.read_next_token();

    if token.kind == TokenKind::KWI8 {
        Some(TypeInt::new_from_source(token.range.clone(), 8, true))
    } else if token.kind == TokenKind::KWI16 {
        Some(TypeInt::new_from_source(token.range.clone(), 16, true))
    } else if token.kind == TokenKind::KWI32 {
        Some(TypeInt::new_from_source(token.range.clone(), 32, true))
    } else if token.kind == TokenKind::KWI64 {
        Some(TypeInt::new_from_source(token.range.clone(), 64, true))
    } else if token.kind == TokenKind::KWU8 {
        Some(TypeInt::new_from_source(token.range.clone(), 8, false))
    } else if token.kind == TokenKind::KWU16 {
        Some(TypeInt::new_from_source(token.range.clone(), 16, false))
    } else if token.kind == TokenKind::KWU32 {
        Some(TypeInt::new_from_source(token.range.clone(), 32, false))
    } else if token.kind == TokenKind::KWU64 {
        Some(TypeInt::new_from_source(token.range.clone(), 64, false))
    } else {
        None
    }
}

fn parse_type_float<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    _msgs: &mut impl OutputMessage<'sctx>,
) -> Option<TypeFloat<'sctx>> {
    if !state.are_more_tokens() {
        return None;
    }

    let token = state.read_next_token();

    if token.kind == TokenKind::KWF32 {
        Some(TypeFloat::new_from_source(token.range.clone(), 32))
    } else if token.kind == TokenKind::KWF64 {
        Some(TypeFloat::new_from_source(token.range.clone(), 64))
    } else {
        None
    }
}

fn parse_type_pointer<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    msgs: &mut impl OutputMessage<'sctx>,
) -> Option<TypePointer<'sctx>> {
    if !state.are_more_tokens() {
        return None;
    }

    let token = state.read_next_token();

    if token.kind != TokenKind::Mul {
        return None;
    }

    if is_at_type_ending(state) {
        Some(TypePointer::new_from_source(
            token.range.clone(),
            TypeMissing::new(),
        ))
    } else {
        let Some(deref_type) = parse_type(state, msgs) else {
            msgs.output_message(
                token.range.clone(),
                MessageSeverity::Error,
                format!(
                    "{} must be followed by a type in order to make a pointer type",
                    token.kind
                ),
            );

            return None;
        };

        Some(TypePointer::new_from_source(
            token.range.clone(),
            deref_type,
        ))
    }
}

fn parse_type<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    msgs: &mut impl OutputMessage<'sctx>,
) -> Option<Type<'sctx>> {
    if let Some(type_pointer) = try_parse(state, msgs, parse_type_pointer) {
        Some(Type::Pointer(type_pointer))
    } else if let Some(type_bool) = try_parse(state, msgs, parse_type_bool) {
        Some(Type::Bool(type_bool))
    } else if let Some(type_int) = try_parse(state, msgs, parse_type_int) {
        Some(Type::Int(type_int))
    } else if let Some(type_float) = try_parse(state, msgs, parse_type_float) {
        Some(Type::Float(type_float))
    } else {
        None
    }
}

fn parse_expr_bool<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    _msgs: &mut impl OutputMessage<'sctx>,
) -> Option<ExprBool<'sctx>> {
    if !state.are_more_tokens() {
        return None;
    }

    let token = state.read_next_token();

    if token.kind == TokenKind::KWTrue {
        Some(ExprBool::new_from_source(token.range.clone(), true))
    } else if token.kind == TokenKind::KWFalse {
        Some(ExprBool::new_from_source(token.range.clone(), false))
    } else {
        None
    }
}

/// Extract the base of a number literal from the prefix at its front.
///
/// # Returns
///
/// A tuple `(base, remaining)` where `base` is the numeric base (2, 8, 10, or 16) and `remaining`
/// is the content after the prefix has been stripped.
fn parse_number_base(content: &str) -> (u32, &str) {
    if content.starts_with("0x") || content.starts_with("0X") {
        (16, &content[2..])
    } else if content.starts_with("0b") || content.starts_with("0B") {
        (2, &content[2..])
    } else if content.starts_with("0o") || content.starts_with("0O") {
        (8, &content[2..])
    } else {
        (10, content)
    }
}

fn parse_number_type_suffix<'sctx>(content: &str, base: u32) -> (Option<Type<'sctx>>, &str) {
    if content.ends_with("i8") {
        (
            Some(Type::Int(TypeInt::new(8, true))),
            &content[..content.len() - 2],
        )
    } else if content.ends_with("i16") {
        (
            Some(Type::Int(TypeInt::new(16, true))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("i32") {
        (
            Some(Type::Int(TypeInt::new(32, true))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("i64") {
        (
            Some(Type::Int(TypeInt::new(64, true))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("u8") {
        (
            Some(Type::Int(TypeInt::new(8, false))),
            &content[..content.len() - 2],
        )
    } else if content.ends_with("u16") {
        (
            Some(Type::Int(TypeInt::new(16, false))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("u32") {
        (
            Some(Type::Int(TypeInt::new(32, false))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("u64") {
        (
            Some(Type::Int(TypeInt::new(64, false))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("f32") && base == 10 {
        (
            Some(Type::Float(TypeFloat::new(32))),
            &content[..content.len() - 3],
        )
    } else if content.ends_with("f64") && base == 10 {
        (
            Some(Type::Float(TypeFloat::new(64))),
            &content[..content.len() - 3],
        )
    } else {
        (None, content)
    }
}

/// Gets the integer value of a digit byte based on the specified base.
///
/// # Returns
///
/// - `Some(value)` if the digit is valid for the base.
/// - `None` if the digit is invalid for the base.
fn get_digit_value(digit_byte: u8, base: u32) -> Option<u64> {
    match base {
        2 => {
            if digit_byte == b'0' || digit_byte == b'1' {
                Some((digit_byte - b'0') as u64)
            } else {
                None
            }
        }
        8 => {
            if digit_byte >= b'0' && digit_byte <= b'7' {
                Some((digit_byte - b'0') as u64)
            } else {
                None
            }
        }
        10 => {
            if digit_byte >= b'0' && digit_byte <= b'9' {
                Some((digit_byte - b'0') as u64)
            } else {
                None
            }
        }
        16 => {
            if digit_byte >= b'0' && digit_byte <= b'9' {
                Some((digit_byte - b'0') as u64)
            } else if digit_byte >= b'a' && digit_byte <= b'f' {
                Some((digit_byte - b'a' + 10) as u64)
            } else if digit_byte >= b'A' && digit_byte <= b'F' {
                Some((digit_byte - b'A' + 10) as u64)
            } else {
                None
            }
        }
        _ => None,
    }
}

/// The returned values from [`parse_digits`].
struct ParseDigitsOutput {
    /// The integer value parsed from the digits.
    ///
    /// If no digits were parsed, this will be zero.
    parsed_value: u64,

    /// How many digits were parsed.
    ///
    /// **Note:** this might be zero.
    n_digits: usize,

    /// The decimal factor for the parsed value.
    ///
    /// This will be 0.1 if the base is 10 and one digit was parsed, 0.01 if two digits were parsed,
    /// etc. It is used to convert the integer value into a float if there is a decimal part.
    decimal_factor: f64,
}

/// Parses as many digits as possible from the start of the content string.
///
/// # Arguments
///
/// - `content`: The string content to parse digits from.
/// - `base`: The numeric base to use for parsing (2, 8, 10, or 16).
///
/// # Returns
///
/// A tuple `(output, remaining)` where `output` contains the returned values and `remaining` is the
/// content after the digits have been parsed.
fn parse_digits(content: &str, base: u32) -> (ParseDigitsOutput, &str) {
    let mut index = 0;
    let mut parsed_value = 0u64;
    let mut decimal_factor = 1f64;

    while index < content.len() {
        if content.as_bytes()[index] == b'_' {
            index += 1;
        } else if let Some(digit_value) = get_digit_value(content.as_bytes()[index], base) {
            parsed_value *= base as u64;
            parsed_value += digit_value;
            decimal_factor /= base as f64;
            index += 1;
        } else {
            break;
        }
    }

    (
        ParseDigitsOutput {
            parsed_value,
            n_digits: index,
            decimal_factor,
        },
        &content[index..],
    )
}

fn try_parse_decimal_part<'sctx, 'content>(
    msgs: &mut impl OutputMessage<'sctx>,
    range: &SourceRange<'sctx>,
    content: &'content str,
    base: u32,
) -> (Option<f64>, &'content str) {
    if !content.starts_with('.') {
        return (None, content);
    }

    let (decimal_part, content) = parse_digits(&content[1..], base);

    if decimal_part.n_digits == 0 {
        msgs.output_message(
            range.clone(),
            MessageSeverity::Error,
            "decimal part must have at least one digit".to_owned(),
        );
        return (Some(0.0), content);
    }

    (
        Some((decimal_part.parsed_value as f64) * decimal_part.decimal_factor),
        content,
    )
}

fn try_parse_exponent_part<'sctx, 'content>(
    msgs: &mut impl OutputMessage<'sctx>,
    range: &SourceRange<'sctx>,
    content: &'content str,
    base: u32,
) -> (Option<i64>, &'content str) {
    if base != 10 || !content.starts_with('e') {
        return (None, content);
    }

    if content[1..].starts_with('-') {
        let (exponent_part, content) = parse_digits(&content[2..], base);

        if exponent_part.n_digits == 0 {
            msgs.output_message(
                range.clone(),
                MessageSeverity::Error,
                "exponent part must have at least one digit".to_owned(),
            );
            return (Some(0), content);
        }

        (Some(-(exponent_part.parsed_value as i64)), content)
    } else {
        let (exponent_part, content) = parse_digits(&content[1..], base);

        if exponent_part.n_digits == 0 {
            msgs.output_message(
                range.clone(),
                MessageSeverity::Error,
                "exponent part must have at least one digit".to_owned(),
            );
            return (Some(0), content);
        }

        (Some(exponent_part.parsed_value as i64), content)
    }
}

fn parse_expr_int_or_float<'sctx, 'tokens>(
    state: &mut ParserState<'sctx, 'tokens>,
    msgs: &mut impl OutputMessage<'sctx>,
) -> Option<Expr<'sctx>> {
    // Return None early if its not a number token
    if !state.are_more_tokens() {
        return None;
    }

    let token = state.read_next_token();

    if token.kind != TokenKind::Number {
        return None;
    }

    // Grab the text content of the number token
    let content = token
        .range
        .content()
        .expect("number token must have content");

    assert!(
        !content.is_empty(),
        "number token content must not be empty"
    );

    // Extract the base prefix, if there is one
    let (base, content) = parse_number_base(content);

    if content.starts_with('0') {
        msgs.output_message(
            token.range.clone(),
            MessageSeverity::Warning,
            "number literal starts with a '0' but will be treated as base 10 - use the '0o' prefix for base 8 numbers".to_owned(),
        );
    } else if content.is_empty() {
        msgs.output_message(
            token.range.clone(),
            MessageSeverity::Error,
            "number literal does not have any digits".to_owned(),
        );
        return Some(ExprInt::new_i32_from_source(token.range.clone(), 0).into());
    }

    // Parse the type suffix if it exists
    let (type_suffix, content) = parse_number_type_suffix(content, base);

    // Parse as many integer digits as possible
    let (int_part, content) = parse_digits(content, base);

    // Parse the decimal part if it exists
    let (decimal_part, content) = try_parse_decimal_part(msgs, &token.range, content, base);

    // If it is a decimal number...
    if let Some(decimal_part) = decimal_part {
        // Parse the exponent part if it exists
        let (exponent_part, content) = try_parse_exponent_part(msgs, &token.range, content, base);

        // If there is any content left over, then it's illegal characters
        if !content.is_empty() {
            msgs.output_message(
                token.range.clone(),
                MessageSeverity::Error,
                format!(
                    "unexpected character in number literal literal: '{}'",
                    &content[..1]
                ),
            );
            return None;
        }

        // Calculate the final f64 value
        let final_value = int_part.parsed_value as f64
            + (decimal_part * (base as f64).powf(exponent_part.unwrap_or(0) as f64));

        // Convert it to the target type
        match type_suffix {
            Some(Type::Float(TypeFloat {
                bit_width: 32,
                source_range: _,
            })) => {
                Some(ExprFloat::new_f32_from_source(token.range.clone(), final_value as f32).into())
            }
            Some(Type::Float(TypeFloat {
                bit_width: 64,
                source_range: _,
            }))
            | None => Some(ExprFloat::new_f64_from_source(token.range.clone(), final_value).into()),
            Some(Type::Int(_)) => {
                msgs.output_message(
                    token.range.clone(),
                    MessageSeverity::Error,
                    "number literal has an integer type suffix but has a decimal point".to_owned(),
                );
                None
            }
            _ => {
                panic!(
                    "unexpected type suffix for number literal: {:?}",
                    type_suffix
                )
            }
        }
    }
    // If it is an integer...
    else {
        // If there is any content left over, then it's illegal characters
        if !content.is_empty() {
            msgs.output_message(
                token.range.clone(),
                MessageSeverity::Error,
                format!(
                    "unexpected character in number literal literal: '{}'",
                    &content[..1]
                ),
            );
            return None;
        }

        // Convert it to the target type
        match type_suffix {
            Some(Type::Int(TypeInt {
                bit_width: 8,
                signed: true,
                source_range: _,
            })) => Some(
                ExprInt::new_i8_from_source(token.range.clone(), int_part.parsed_value as i8)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 16,
                signed: true,
                source_range: _,
            })) => Some(
                ExprInt::new_i16_from_source(token.range.clone(), int_part.parsed_value as i16)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 32,
                signed: true,
                source_range: _,
            }))
            | None => Some(
                ExprInt::new_i32_from_source(token.range.clone(), int_part.parsed_value as i32)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 64,
                signed: true,
                source_range: _,
            })) => Some(
                ExprInt::new_i64_from_source(token.range.clone(), int_part.parsed_value as i64)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 8,
                signed: false,
                source_range: _,
            })) => Some(
                ExprInt::new_u8_from_source(token.range.clone(), int_part.parsed_value as u8)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 16,
                signed: false,
                source_range: _,
            })) => Some(
                ExprInt::new_u16_from_source(token.range.clone(), int_part.parsed_value as u16)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 32,
                signed: false,
                source_range: _,
            })) => Some(
                ExprInt::new_u32_from_source(token.range.clone(), int_part.parsed_value as u32)
                    .into(),
            ),
            Some(Type::Int(TypeInt {
                bit_width: 64,
                signed: false,
                source_range: _,
            })) => Some(
                ExprInt::new_u64_from_source(token.range.clone(), int_part.parsed_value as u64)
                    .into(),
            ),
            Some(Type::Float(TypeFloat {
                bit_width: 32,
                source_range: _,
            })) => Some(
                ExprFloat::new_f32_from_source(token.range.clone(), int_part.parsed_value as f32)
                    .into(),
            ),
            Some(Type::Float(TypeFloat {
                bit_width: 64,
                source_range: _,
            })) => Some(
                ExprFloat::new_f64_from_source(token.range.clone(), int_part.parsed_value as f64)
                    .into(),
            ),
            _ => {
                panic!(
                    "unexpected type suffix for number literal: {:?}",
                    type_suffix
                )
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::{MessageBuffer, SourceContext, lex};

    use super::*;

    #[test]
    fn test_parser_state() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "x y z".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 3);

        let mut state = ParserState::new(&tokens);

        assert!(state.are_more_tokens());
        let token = state.peek_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "x");
        let token = state.peek_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "x");

        assert!(state.are_more_tokens());
        let token = state.read_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "x");

        assert!(state.are_more_tokens());
        let token = state.peek_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "y");
        let token = state.read_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "y");

        assert!(state.are_more_tokens());
        let token = state.peek_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "z");
        let token = state.read_next_token();
        assert_eq!(token.kind, TokenKind::Symbol);
        assert_eq!(token.range.content().unwrap(), "z");

        assert!(!state.are_more_tokens());
    }

    #[test]
    fn test_parse_type_bool_success() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "bool".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_bool(&mut state, &mut msg);

        assert!(node.is_some());
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_type_bool_failure_empty() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 0);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_bool(&mut state, &mut msg);

        assert!(node.is_none());
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_type_bool_failure_wrong_token() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "x".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_bool(&mut state, &mut msg);

        assert!(node.is_none());
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_try_parse_success() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "bool".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_bool(&mut state, &mut msg);

        assert_eq!(state.index, 1);
        assert!(node.is_some());
        assert_eq!(msg.messages.len(), 0);

        let mut state = ParserState::new(&tokens);

        let node = try_parse(&mut state, &mut msg, parse_type_bool);

        assert_eq!(state.index, 1);
        assert!(node.is_some());
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_try_parse_failure() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "x".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_bool(&mut state, &mut msg);

        assert_eq!(state.index, 1);
        assert!(node.is_none());
        assert_eq!(msg.messages.len(), 0);

        let mut state = ParserState::new(&tokens);

        let node = try_parse(&mut state, &mut msg, parse_type_bool);

        assert_eq!(state.index, 0);
        assert!(node.is_none());
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_i32_success() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "i32".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_int(&mut state, &mut msg);

        assert_eq!(node, Some(TypeInt::new(32, true)));
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_f64_success() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "f64".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_float(&mut state, &mut msg);

        assert_eq!(node, Some(TypeFloat::new(64)));
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_type_pointer_success_i32() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "*i32".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 2);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_pointer(&mut state, &mut msg);

        assert_eq!(node, Some(TypePointer::new(TypeInt::new(32, true))));
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_type_pointer_success_i32_double() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "**i32".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 3);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_pointer(&mut state, &mut msg);

        assert_eq!(
            node,
            Some(TypePointer::new(TypePointer::new(TypeInt::new(32, true))))
        );
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_type_pointer_success_missing() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "*".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 1);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_pointer(&mut state, &mut msg);

        assert_eq!(node, Some(TypePointer::new(TypeMissing::new())));
        assert_eq!(msg.messages.len(), 0);
    }

    #[test]
    fn test_parse_type_pointer_failure_bad_token() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("--".to_owned(), "*+".to_owned())
            .unwrap();

        let mut msg = MessageBuffer::default();

        let tokens = lex(source, &mut msg).unwrap();

        assert_eq!(tokens.len(), 2);

        let mut state = ParserState::new(&tokens);

        let node = parse_type_pointer(&mut state, &mut msg);

        assert!(node.is_none());
        assert_eq!(msg.messages.len(), 1);
    }
}
