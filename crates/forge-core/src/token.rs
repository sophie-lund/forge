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

use std::fmt::Display;

use serde::Serialize;

use crate::SourceRange;

/// The kind of a token in the Forge language.
#[derive(Debug, Clone, Copy, PartialEq, Serialize)]
pub enum TokenKind {
    #[serde(rename = "kwBool")]
    KWBool,

    #[serde(rename = "kwI8")]
    KWI8,

    #[serde(rename = "kwI16")]
    KWI16,

    #[serde(rename = "kwI32")]
    KWI32,

    #[serde(rename = "kwI64")]
    KWI64,

    #[serde(rename = "kwU8")]
    KWU8,

    #[serde(rename = "kwU16")]
    KWU16,

    #[serde(rename = "kwU32")]
    KWU32,

    #[serde(rename = "kwU64")]
    KWU64,

    #[serde(rename = "kwF32")]
    KWF32,

    #[serde(rename = "kwF64")]
    KWF64,

    #[serde(rename = "kwTrue")]
    KWTrue,

    #[serde(rename = "kwFalse")]
    KWFalse,

    #[serde(rename = "kwReturn")]
    KWReturn,

    #[serde(rename = "kwIf")]
    KWIf,

    #[serde(rename = "kwElse")]
    KWElse,

    #[serde(rename = "kwWhile")]
    KWWhile,

    #[serde(rename = "kwDo")]
    KWDo,

    #[serde(rename = "kwContinue")]
    KWContinue,

    #[serde(rename = "kwBreak")]
    KWBreak,

    #[serde(rename = "kwFn")]
    KWFn,

    #[serde(rename = "kwLet")]
    KWLet,

    #[serde(rename = "symbol")]
    Symbol,

    #[serde(rename = "number")]
    Number,

    #[serde(rename = "logNot")]
    LogNot,

    #[serde(rename = "logAnd")]
    LogAnd,

    #[serde(rename = "logOr")]
    LogOr,

    #[serde(rename = "bitNot")]
    BitNot,

    #[serde(rename = "bitAnd")]
    BitAnd,

    #[serde(rename = "bitOr")]
    BitOr,

    #[serde(rename = "bitXor")]
    BitXor,

    #[serde(rename = "bitShL")]
    BitShL,

    #[serde(rename = "bitShR")]
    BitShR,

    #[serde(rename = "add")]
    Add,

    #[serde(rename = "sub")]
    Sub,

    #[serde(rename = "mul")]
    Mul,

    #[serde(rename = "div")]
    Div,

    #[serde(rename = "mod")]
    Mod,

    #[serde(rename = "lt")]
    LT,

    #[serde(rename = "le")]
    LE,

    #[serde(rename = "gt")]
    GT,

    #[serde(rename = "ge")]
    GE,

    #[serde(rename = "ne")]
    NE,

    #[serde(rename = "eq")]
    EQ,

    #[serde(rename = "assign")]
    Assign,

    #[serde(rename = "bitAndAssign")]
    BitAndAssign,

    #[serde(rename = "bitOrAssign")]
    BitOrAssign,

    #[serde(rename = "bitXorAssign")]
    BitXorAssign,

    #[serde(rename = "bitShLAssign")]
    BitShLAssign,

    #[serde(rename = "bitShRAssign")]
    BitShRAssign,

    #[serde(rename = "addAssign")]
    AddAssign,

    #[serde(rename = "subAssign")]
    SubAssign,

    #[serde(rename = "mulAssign")]
    MulAssign,

    #[serde(rename = "divAssign")]
    DivAssign,

    #[serde(rename = "modAssign")]
    ModAssign,

    #[serde(rename = "lParen")]
    LParen,

    #[serde(rename = "rParen")]
    RParen,

    #[serde(rename = "comma")]
    Comma,

    #[serde(rename = "lBrace")]
    LBrace,

    #[serde(rename = "rBrace")]
    RBrace,

    #[serde(rename = "semicolon")]
    Semicolon,
}

impl Display for TokenKind {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::KWBool => write!(f, "'bool'"),
            Self::KWI8 => write!(f, "'i8'"),
            Self::KWI16 => write!(f, "'i16'"),
            Self::KWI32 => write!(f, "'i32'"),
            Self::KWI64 => write!(f, "'i64'"),
            Self::KWU8 => write!(f, "'u8'"),
            Self::KWU16 => write!(f, "'u16'"),
            Self::KWU32 => write!(f, "'u32'"),
            Self::KWU64 => write!(f, "'u64'"),
            Self::KWF32 => write!(f, "'f32'"),
            Self::KWF64 => write!(f, "'f64'"),
            Self::KWTrue => write!(f, "'true'"),
            Self::KWFalse => write!(f, "'false'"),
            Self::KWReturn => write!(f, "'return'"),
            Self::KWIf => write!(f, "'if'"),
            Self::KWElse => write!(f, "'else'"),
            Self::KWWhile => write!(f, "'while'"),
            Self::KWDo => write!(f, "'do'"),
            Self::KWContinue => write!(f, "'continue'"),
            Self::KWBreak => write!(f, "'break'"),
            Self::KWFn => write!(f, "'fn'"),
            Self::KWLet => write!(f, "'let'"),
            Self::Symbol => write!(f, "symbol"),
            Self::Number => write!(f, "number literal"),
            Self::LogNot => write!(f, "'!'"),
            Self::LogAnd => write!(f, "'&&'"),
            Self::LogOr => write!(f, "'||'"),
            Self::BitNot => write!(f, "'~'"),
            Self::BitAnd => write!(f, "'&'"),
            Self::BitOr => write!(f, "'|'"),
            Self::BitXor => write!(f, "'^'"),
            Self::BitShL => write!(f, "'<<'"),
            Self::BitShR => write!(f, "'>>'"),
            Self::Add => write!(f, "'+'"),
            Self::Sub => write!(f, "'-'"),
            Self::Mul => write!(f, "'*'"),
            Self::Div => write!(f, "'/'"),
            Self::Mod => write!(f, "'%'"),
            Self::LT => write!(f, "'<'"),
            Self::LE => write!(f, "'<='"),
            Self::GT => write!(f, "'>'"),
            Self::GE => write!(f, "'>='"),
            Self::NE => write!(f, "'!='"),
            Self::EQ => write!(f, "'=='"),
            Self::Assign => write!(f, "'='"),
            Self::BitAndAssign => write!(f, "'&='"),
            Self::BitOrAssign => write!(f, "'|='"),
            Self::BitXorAssign => write!(f, "'^='"),
            Self::BitShLAssign => write!(f, "'<<='"),
            Self::BitShRAssign => write!(f, "'>>='"),
            Self::AddAssign => write!(f, "'+='"),
            Self::SubAssign => write!(f, "'-='"),
            Self::MulAssign => write!(f, "'*='"),
            Self::DivAssign => write!(f, "'/='"),
            Self::ModAssign => write!(f, "'%='"),
            Self::LParen => write!(f, "'('"),
            Self::RParen => write!(f, "')'"),
            Self::Comma => write!(f, "','"),
            Self::LBrace => write!(f, "'{{'"),
            Self::RBrace => write!(f, "'}}'"),
            Self::Semicolon => write!(f, "';'"),
        }
    }
}

/// A lexical token in the Forge language.
#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct Token<'sctx> {
    /// The range in the source code from which this token is taken.
    pub range: SourceRange<'sctx>,

    /// The kind of the token.
    pub kind: TokenKind,
}

impl<'sctx> Token<'sctx> {
    /// Creates a new token from components.
    pub fn new(range: SourceRange<'sctx>, kind: TokenKind) -> Self {
        Self { range, kind }
    }
}
