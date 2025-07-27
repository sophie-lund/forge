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

use crate::{
    IsNode, MessageSeverity, OutputMessage, Token, TokenKind, Type, TypeBool, TypeFloat, TypeInt,
    TypeMissing, TypePointer,
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
