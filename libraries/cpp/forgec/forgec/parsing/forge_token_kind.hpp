// Copyright 2025 Sophie Lund
//
// This file is part of Forge.
//
// Forge is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Forge is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Forge. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <langtools/parsing/domain/token_kind.hpp>

namespace forge {
// clang-format off

// Keywords (in alphabetical order)
const lt::TokenKind TOKEN_KW_AS          = lt::TokenKind("'as'");
const lt::TokenKind TOKEN_KW_BOOL        = lt::TokenKind("'bool'");
const lt::TokenKind TOKEN_KW_BREAK       = lt::TokenKind("'break'");
const lt::TokenKind TOKEN_KW_CONST       = lt::TokenKind("'const'");
const lt::TokenKind TOKEN_KW_CONTINUE    = lt::TokenKind("'continue'");
const lt::TokenKind TOKEN_KW_DO          = lt::TokenKind("'do'");
const lt::TokenKind TOKEN_KW_ELSE        = lt::TokenKind("'else'");
const lt::TokenKind TOKEN_KW_EXPLICIT    = lt::TokenKind("'explicit'");
const lt::TokenKind TOKEN_KW_F32         = lt::TokenKind("'f32'");
const lt::TokenKind TOKEN_KW_F64         = lt::TokenKind("'f64'");
const lt::TokenKind TOKEN_KW_FALSE       = lt::TokenKind("'false'");
const lt::TokenKind TOKEN_KW_FUNC        = lt::TokenKind("'func'");
const lt::TokenKind TOKEN_KW_I16         = lt::TokenKind("'i16'");
const lt::TokenKind TOKEN_KW_I32         = lt::TokenKind("'i32'");
const lt::TokenKind TOKEN_KW_I64         = lt::TokenKind("'i64'");
const lt::TokenKind TOKEN_KW_I8          = lt::TokenKind("'i8'");
const lt::TokenKind TOKEN_KW_IF          = lt::TokenKind("'if'");
const lt::TokenKind TOKEN_KW_INHERITS    = lt::TokenKind("'inherits'");
const lt::TokenKind TOKEN_KW_INTERFACE   = lt::TokenKind("'interface'");
const lt::TokenKind TOKEN_KW_ISIZE       = lt::TokenKind("'isize'");
const lt::TokenKind TOKEN_KW_LET         = lt::TokenKind("'let'");
const lt::TokenKind TOKEN_KW_NAMESPACE   = lt::TokenKind("'namespace'");
const lt::TokenKind TOKEN_KW_RETURN      = lt::TokenKind("'return'");
const lt::TokenKind TOKEN_KW_SELF        = lt::TokenKind("'self'");
const lt::TokenKind TOKEN_KW_STRUCT      = lt::TokenKind("'struct'");
const lt::TokenKind TOKEN_KW_TRUE        = lt::TokenKind("'true'");
const lt::TokenKind TOKEN_KW_TYPE        = lt::TokenKind("'type'");
const lt::TokenKind TOKEN_KW_U16         = lt::TokenKind("'u16'");
const lt::TokenKind TOKEN_KW_U32         = lt::TokenKind("'u32'");
const lt::TokenKind TOKEN_KW_U64         = lt::TokenKind("'u64'");
const lt::TokenKind TOKEN_KW_U8          = lt::TokenKind("'u8'");
const lt::TokenKind TOKEN_KW_USIZE       = lt::TokenKind("'usize'");
const lt::TokenKind TOKEN_KW_VOID        = lt::TokenKind("'void'");
const lt::TokenKind TOKEN_KW_WHILE       = lt::TokenKind("'while'");

// Boolean operators
const lt::TokenKind TOKEN_BOOL_NOT       = lt::TokenKind("!");
const lt::TokenKind TOKEN_BOOL_AND       = lt::TokenKind("&&");
const lt::TokenKind TOKEN_BOOL_OR        = lt::TokenKind("||");

// Bitwise operators
const lt::TokenKind TOKEN_BIT_NOT        = lt::TokenKind("~");
const lt::TokenKind TOKEN_BIT_AND        = lt::TokenKind("&");
const lt::TokenKind TOKEN_BIT_AND_ASSIGN = lt::TokenKind("&=");
const lt::TokenKind TOKEN_BIT_OR         = lt::TokenKind("|");
const lt::TokenKind TOKEN_BIT_OR_ASSIGN  = lt::TokenKind("|=");
const lt::TokenKind TOKEN_BIT_XOR        = lt::TokenKind("^");
const lt::TokenKind TOKEN_BIT_XOR_ASSIGN = lt::TokenKind("^=");
const lt::TokenKind TOKEN_BIT_SHL        = lt::TokenKind("<<");
const lt::TokenKind TOKEN_BIT_SHL_ASSIGN = lt::TokenKind("<<=");
const lt::TokenKind TOKEN_BIT_SHR        = lt::TokenKind(">>");
const lt::TokenKind TOKEN_BIT_SHR_ASSIGN = lt::TokenKind(">>=");

// Arithmetic operators
const lt::TokenKind TOKEN_ADD            = lt::TokenKind("+");
const lt::TokenKind TOKEN_ADD_ASSIGN     = lt::TokenKind("+=");
const lt::TokenKind TOKEN_SUB            = lt::TokenKind("-");
const lt::TokenKind TOKEN_SUB_ASSIGN     = lt::TokenKind("-=");
const lt::TokenKind TOKEN_MUL            = lt::TokenKind("*");
const lt::TokenKind TOKEN_MUL_ASSIGN     = lt::TokenKind("*=");
const lt::TokenKind TOKEN_EXP            = lt::TokenKind("**");
const lt::TokenKind TOKEN_EXP_ASSIGN     = lt::TokenKind("**=");
const lt::TokenKind TOKEN_DIV            = lt::TokenKind("/");
const lt::TokenKind TOKEN_DIV_ASSIGN     = lt::TokenKind("/=");
const lt::TokenKind TOKEN_MOD            = lt::TokenKind("%");
const lt::TokenKind TOKEN_MOD_ASSIGN     = lt::TokenKind("%=");
const lt::TokenKind TOKEN_ASSIGN         = lt::TokenKind("=");

// Comparators
const lt::TokenKind TOKEN_EQ             = lt::TokenKind("==");
const lt::TokenKind TOKEN_NE             = lt::TokenKind("!=");
const lt::TokenKind TOKEN_LT             = lt::TokenKind("<");
const lt::TokenKind TOKEN_LE             = lt::TokenKind("<=");
const lt::TokenKind TOKEN_GT             = lt::TokenKind(">");
const lt::TokenKind TOKEN_GE             = lt::TokenKind(">=");

// Punctuation
const lt::TokenKind TOKEN_LPAREN         = lt::TokenKind("(");
const lt::TokenKind TOKEN_COMMA          = lt::TokenKind(",");
const lt::TokenKind TOKEN_RPAREN         = lt::TokenKind(")");
const lt::TokenKind TOKEN_LBRACE         = lt::TokenKind("{");
const lt::TokenKind TOKEN_SEMICOLON      = lt::TokenKind(";");
const lt::TokenKind TOKEN_RBRACE         = lt::TokenKind("}");
const lt::TokenKind TOKEN_COLON          = lt::TokenKind(":");
const lt::TokenKind TOKEN_DOT            = lt::TokenKind(".");
const lt::TokenKind TOKEN_RARROW         = lt::TokenKind("->");

// Symbols/literals
const lt::TokenKind TOKEN_SYMBOL         = lt::TokenKind("'symbol'");
const lt::TokenKind TOKEN_LITERAL_NUMBER = lt::TokenKind("number literal");

// clang-format on
}  // namespace forge
