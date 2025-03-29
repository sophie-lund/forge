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

#include <forge/parsing/domain/token_kind.hpp>

namespace forge {
// clang-format off

// Keywords (in alphabetical order)
const TokenKind TOKEN_KW_AS          = TokenKind("'as'");
const TokenKind TOKEN_KW_BOOL        = TokenKind("'bool'");
const TokenKind TOKEN_KW_BREAK       = TokenKind("'break'");
const TokenKind TOKEN_KW_CONST       = TokenKind("'const'");
const TokenKind TOKEN_KW_CONTINUE    = TokenKind("'continue'");
const TokenKind TOKEN_KW_DO          = TokenKind("'do'");
const TokenKind TOKEN_KW_ELSE        = TokenKind("'else'");
const TokenKind TOKEN_KW_EXPLICIT    = TokenKind("'explicit'");
const TokenKind TOKEN_KW_F32         = TokenKind("'f32'");
const TokenKind TOKEN_KW_F64         = TokenKind("'f64'");
const TokenKind TOKEN_KW_FALSE       = TokenKind("'false'");
const TokenKind TOKEN_KW_FUNC        = TokenKind("'func'");
const TokenKind TOKEN_KW_I16         = TokenKind("'i16'");
const TokenKind TOKEN_KW_I32         = TokenKind("'i32'");
const TokenKind TOKEN_KW_I64         = TokenKind("'i64'");
const TokenKind TOKEN_KW_I8          = TokenKind("'i8'");
const TokenKind TOKEN_KW_IF          = TokenKind("'if'");
const TokenKind TOKEN_KW_INHERITS    = TokenKind("'inherits'");
const TokenKind TOKEN_KW_INTERFACE   = TokenKind("'interface'");
const TokenKind TOKEN_KW_ISIZE       = TokenKind("'isize'");
const TokenKind TOKEN_KW_LET         = TokenKind("'let'");
const TokenKind TOKEN_KW_NAMESPACE   = TokenKind("'namespace'");
const TokenKind TOKEN_KW_RETURN      = TokenKind("'return'");
const TokenKind TOKEN_KW_SELF        = TokenKind("'self'");
const TokenKind TOKEN_KW_STRUCT      = TokenKind("'struct'");
const TokenKind TOKEN_KW_TRUE        = TokenKind("'true'");
const TokenKind TOKEN_KW_TYPE        = TokenKind("'type'");
const TokenKind TOKEN_KW_U16         = TokenKind("'u16'");
const TokenKind TOKEN_KW_U32         = TokenKind("'u32'");
const TokenKind TOKEN_KW_U64         = TokenKind("'u64'");
const TokenKind TOKEN_KW_U8          = TokenKind("'u8'");
const TokenKind TOKEN_KW_USIZE       = TokenKind("'usize'");
const TokenKind TOKEN_KW_VOID        = TokenKind("'void'");
const TokenKind TOKEN_KW_WHILE       = TokenKind("'while'");

// Boolean operators
const TokenKind TOKEN_BOOL_NOT       = TokenKind("!");
const TokenKind TOKEN_BOOL_AND       = TokenKind("&&");
const TokenKind TOKEN_BOOL_OR        = TokenKind("||");

// Bitwise operators
const TokenKind TOKEN_BIT_NOT        = TokenKind("~");
const TokenKind TOKEN_BIT_AND        = TokenKind("&");
const TokenKind TOKEN_BIT_AND_ASSIGN = TokenKind("&=");
const TokenKind TOKEN_BIT_OR         = TokenKind("|");
const TokenKind TOKEN_BIT_OR_ASSIGN  = TokenKind("|=");
const TokenKind TOKEN_BIT_XOR        = TokenKind("^");
const TokenKind TOKEN_BIT_XOR_ASSIGN = TokenKind("^=");
const TokenKind TOKEN_BIT_SHL        = TokenKind("<<");
const TokenKind TOKEN_BIT_SHL_ASSIGN = TokenKind("<<=");
const TokenKind TOKEN_BIT_SHR        = TokenKind(">>");
const TokenKind TOKEN_BIT_SHR_ASSIGN = TokenKind(">>=");

// Arithmetic operators
const TokenKind TOKEN_ADD            = TokenKind("+");
const TokenKind TOKEN_ADD_ASSIGN     = TokenKind("+=");
const TokenKind TOKEN_SUB            = TokenKind("-");
const TokenKind TOKEN_SUB_ASSIGN     = TokenKind("-=");
const TokenKind TOKEN_MUL            = TokenKind("*");
const TokenKind TOKEN_MUL_ASSIGN     = TokenKind("*=");
const TokenKind TOKEN_EXP            = TokenKind("**");
const TokenKind TOKEN_EXP_ASSIGN     = TokenKind("**=");
const TokenKind TOKEN_DIV            = TokenKind("/");
const TokenKind TOKEN_DIV_ASSIGN     = TokenKind("/=");
const TokenKind TOKEN_MOD            = TokenKind("%");
const TokenKind TOKEN_MOD_ASSIGN     = TokenKind("%=");
const TokenKind TOKEN_ASSIGN         = TokenKind("=");

// Comparators
const TokenKind TOKEN_EQ             = TokenKind("==");
const TokenKind TOKEN_NE             = TokenKind("!=");
const TokenKind TOKEN_LT             = TokenKind("<");
const TokenKind TOKEN_LE             = TokenKind("<=");
const TokenKind TOKEN_GT             = TokenKind(">");
const TokenKind TOKEN_GE             = TokenKind(">=");

// Punctuation
const TokenKind TOKEN_LPAREN         = TokenKind("(");
const TokenKind TOKEN_COMMA          = TokenKind(",");
const TokenKind TOKEN_RPAREN         = TokenKind(")");
const TokenKind TOKEN_LBRACE         = TokenKind("{");
const TokenKind TOKEN_SEMICOLON      = TokenKind(";");
const TokenKind TOKEN_RBRACE         = TokenKind("}");
const TokenKind TOKEN_COLON          = TokenKind(":");
const TokenKind TOKEN_DOT            = TokenKind(".");
const TokenKind TOKEN_RARROW         = TokenKind("->");

// Symbols/literals
const TokenKind TOKEN_SYMBOL         = TokenKind("'symbol'");
const TokenKind TOKEN_LITERAL_NUMBER = TokenKind("number literal");

// clang-format on
}  // namespace forge
