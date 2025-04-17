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

#include <gtest/gtest.h>

#include <forgec/parsing/forge_lexer.hpp>
#include <forgec/parsing/forge_token_kind.hpp>

using namespace forge;

TEST(language_forge_lexer, empty) {
  lt::Source source("--", lt::LineIndexedUnicodeString(""));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_as) {
  lt::Source source("--", lt::LineIndexedUnicodeString("as"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_AS);
  ASSERT_EQ(tokens[0].value, u"as");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_bool) {
  lt::Source source("--", lt::LineIndexedUnicodeString("bool"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_BOOL);
  ASSERT_EQ(tokens[0].value, u"bool");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_break) {
  lt::Source source("--", lt::LineIndexedUnicodeString("break"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_BREAK);
  ASSERT_EQ(tokens[0].value, u"break");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_const) {
  lt::Source source("--", lt::LineIndexedUnicodeString("const"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_CONST);
  ASSERT_EQ(tokens[0].value, u"const");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_continue) {
  lt::Source source("--", lt::LineIndexedUnicodeString("continue"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_CONTINUE);
  ASSERT_EQ(tokens[0].value, u"continue");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_do) {
  lt::Source source("--", lt::LineIndexedUnicodeString("do"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_DO);
  ASSERT_EQ(tokens[0].value, u"do");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_else) {
  lt::Source source("--", lt::LineIndexedUnicodeString("else"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_ELSE);
  ASSERT_EQ(tokens[0].value, u"else");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_explicit) {
  lt::Source source("--", lt::LineIndexedUnicodeString("explicit"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_EXPLICIT);
  ASSERT_EQ(tokens[0].value, u"explicit");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_f32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("f32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_F32);
  ASSERT_EQ(tokens[0].value, u"f32");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_f64) {
  lt::Source source("--", lt::LineIndexedUnicodeString("f64"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_F64);
  ASSERT_EQ(tokens[0].value, u"f64");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_false) {
  lt::Source source("--", lt::LineIndexedUnicodeString("false"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_FALSE);
  ASSERT_EQ(tokens[0].value, u"false");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_func) {
  lt::Source source("--", lt::LineIndexedUnicodeString("func"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_FUNC);
  ASSERT_EQ(tokens[0].value, u"func");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_i16) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i16"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_I16);
  ASSERT_EQ(tokens[0].value, u"i16");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_i32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_I32);
  ASSERT_EQ(tokens[0].value, u"i32");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_i8) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i8"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_I8);
  ASSERT_EQ(tokens[0].value, u"i8");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_if) {
  lt::Source source("--", lt::LineIndexedUnicodeString("if"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_IF);
  ASSERT_EQ(tokens[0].value, u"if");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_inherits) {
  lt::Source source("--", lt::LineIndexedUnicodeString("inherits"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_INHERITS);
  ASSERT_EQ(tokens[0].value, u"inherits");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_interface) {
  lt::Source source("--", lt::LineIndexedUnicodeString("interface"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_INTERFACE);
  ASSERT_EQ(tokens[0].value, u"interface");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_isize) {
  lt::Source source("--", lt::LineIndexedUnicodeString("isize"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_ISIZE);
  ASSERT_EQ(tokens[0].value, u"isize");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_let) {
  lt::Source source("--", lt::LineIndexedUnicodeString("let"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_LET);
  ASSERT_EQ(tokens[0].value, u"let");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_namespace) {
  lt::Source source("--", lt::LineIndexedUnicodeString("namespace"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_NAMESPACE);
  ASSERT_EQ(tokens[0].value, u"namespace");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_return) {
  lt::Source source("--", lt::LineIndexedUnicodeString("return"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_RETURN);
  ASSERT_EQ(tokens[0].value, u"return");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_self) {
  lt::Source source("--", lt::LineIndexedUnicodeString("self"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_SELF);
  ASSERT_EQ(tokens[0].value, u"self");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_struct) {
  lt::Source source("--", lt::LineIndexedUnicodeString("struct"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_STRUCT);
  ASSERT_EQ(tokens[0].value, u"struct");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_true) {
  lt::Source source("--", lt::LineIndexedUnicodeString("true"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_TRUE);
  ASSERT_EQ(tokens[0].value, u"true");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_type) {
  lt::Source source("--", lt::LineIndexedUnicodeString("type"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_TYPE);
  ASSERT_EQ(tokens[0].value, u"type");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u16) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u16"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U16);
  ASSERT_EQ(tokens[0].value, u"u16");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U32);
  ASSERT_EQ(tokens[0].value, u"u32");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u64) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u64"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U64);
  ASSERT_EQ(tokens[0].value, u"u64");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u8) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u8"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U8);
  ASSERT_EQ(tokens[0].value, u"u8");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_usize) {
  lt::Source source("--", lt::LineIndexedUnicodeString("usize"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_USIZE);
  ASSERT_EQ(tokens[0].value, u"usize");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_void) {
  lt::Source source("--", lt::LineIndexedUnicodeString("void"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_VOID);
  ASSERT_EQ(tokens[0].value, u"void");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_while) {
  lt::Source source("--", lt::LineIndexedUnicodeString("while"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_WHILE);
  ASSERT_EQ(tokens[0].value, u"while");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bool_not) {
  lt::Source source("--", lt::LineIndexedUnicodeString("!"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_NOT);
  ASSERT_EQ(tokens[0].value, u"!");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bool_and) {
  lt::Source source("--", lt::LineIndexedUnicodeString("&&"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_AND);
  ASSERT_EQ(tokens[0].value, u"&&");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bool_or) {
  lt::Source source("--", lt::LineIndexedUnicodeString("||"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_OR);
  ASSERT_EQ(tokens[0].value, u"||");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_not) {
  lt::Source source("--", lt::LineIndexedUnicodeString("~"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_NOT);
  ASSERT_EQ(tokens[0].value, u"~");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_and) {
  lt::Source source("--", lt::LineIndexedUnicodeString("&"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_AND);
  ASSERT_EQ(tokens[0].value, u"&");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_and_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("&="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_AND_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"&=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_or) {
  lt::Source source("--", lt::LineIndexedUnicodeString("|"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_OR);
  ASSERT_EQ(tokens[0].value, u"|");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_or_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("|="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_OR_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"|=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_xor) {
  lt::Source source("--", lt::LineIndexedUnicodeString("^"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_XOR);
  ASSERT_EQ(tokens[0].value, u"^");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_xor_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("^="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_XOR_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"^=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shl) {
  lt::Source source("--", lt::LineIndexedUnicodeString("<<"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHL);
  ASSERT_EQ(tokens[0].value, u"<<");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shl_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("<<="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHL_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"<<=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shr) {
  lt::Source source("--", lt::LineIndexedUnicodeString(">>"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHR);
  ASSERT_EQ(tokens[0].value, u">>");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shr_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString(">>="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHR_ASSIGN);
  ASSERT_EQ(tokens[0].value, u">>=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_add) {
  lt::Source source("--", lt::LineIndexedUnicodeString("+"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_ADD);
  ASSERT_EQ(tokens[0].value, u"+");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_add_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("+="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_ADD_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"+=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_sub) {
  lt::Source source("--", lt::LineIndexedUnicodeString("-"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SUB);
  ASSERT_EQ(tokens[0].value, u"-");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_sub_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("-="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SUB_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"-=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mul) {
  lt::Source source("--", lt::LineIndexedUnicodeString("*"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MUL);
  ASSERT_EQ(tokens[0].value, u"*");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mul_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("*="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MUL_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"*=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_exp) {
  lt::Source source("--", lt::LineIndexedUnicodeString("**"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_EXP);
  ASSERT_EQ(tokens[0].value, u"**");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_exp_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("**="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_EXP_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"**=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_div) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DIV);
  ASSERT_EQ(tokens[0].value, u"/");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_div_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DIV_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"/=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mod) {
  lt::Source source("--", lt::LineIndexedUnicodeString("%"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MOD);
  ASSERT_EQ(tokens[0].value, u"%");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mod_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("%="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MOD_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"%=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_eq) {
  lt::Source source("--", lt::LineIndexedUnicodeString("=="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_EQ);
  ASSERT_EQ(tokens[0].value, u"==");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_ne) {
  lt::Source source("--", lt::LineIndexedUnicodeString("!="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_NE);
  ASSERT_EQ(tokens[0].value, u"!=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_lt) {
  lt::Source source("--", lt::LineIndexedUnicodeString("<"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LT);
  ASSERT_EQ(tokens[0].value, u"<");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_le) {
  lt::Source source("--", lt::LineIndexedUnicodeString("<="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LE);
  ASSERT_EQ(tokens[0].value, u"<=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_gt) {
  lt::Source source("--", lt::LineIndexedUnicodeString(">"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_GT);
  ASSERT_EQ(tokens[0].value, u">");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_ge) {
  lt::Source source("--", lt::LineIndexedUnicodeString(">="));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_GE);
  ASSERT_EQ(tokens[0].value, u">=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_lparen) {
  lt::Source source("--", lt::LineIndexedUnicodeString("("));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LPAREN);
  ASSERT_EQ(tokens[0].value, u"(");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_comma) {
  lt::Source source("--", lt::LineIndexedUnicodeString(","));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_COMMA);
  ASSERT_EQ(tokens[0].value, u",");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_rparen) {
  lt::Source source("--", lt::LineIndexedUnicodeString(")"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_RPAREN);
  ASSERT_EQ(tokens[0].value, u")");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_lbrace) {
  lt::Source source("--", lt::LineIndexedUnicodeString("{"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LBRACE);
  ASSERT_EQ(tokens[0].value, u"{");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_semicolon) {
  lt::Source source("--", lt::LineIndexedUnicodeString(";"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SEMICOLON);
  ASSERT_EQ(tokens[0].value, u";");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_rbrace) {
  lt::Source source("--", lt::LineIndexedUnicodeString("}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_RBRACE);
  ASSERT_EQ(tokens[0].value, u"}");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_colon) {
  lt::Source source("--", lt::LineIndexedUnicodeString(":"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_COLON);
  ASSERT_EQ(tokens[0].value, u":");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_dot) {
  lt::Source source("--", lt::LineIndexedUnicodeString("."));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DOT);
  ASSERT_EQ(tokens[0].value, u".");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_rarrow) {
  lt::Source source("--", lt::LineIndexedUnicodeString("->"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_RARROW);
  ASSERT_EQ(tokens[0].value, u"->");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_symbol) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"x");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_literal_number) {
  lt::Source source("--", lt::LineIndexedUnicodeString("5"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LITERAL_NUMBER);
  ASSERT_EQ(tokens[0].value, u"5");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, space) {
  lt::Source source("--", lt::LineIndexedUnicodeString(" "));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, tab) {
  lt::Source source("--", lt::LineIndexedUnicodeString("\t"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, newline) {
  lt::Source source("--", lt::LineIndexedUnicodeString("\n"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line) {
  lt::Source source("--", lt::LineIndexedUnicodeString("// asdf"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/* asdf */"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, kw_with_prefix) {
  lt::Source source("--", lt::LineIndexedUnicodeString("_if"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"_if");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, kw_with_suffix) {
  lt::Source source("--", lt::LineIndexedUnicodeString("if_"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"if_");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, greedy_punctuation) {
  lt::Source source("--", lt::LineIndexedUnicodeString("!!"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 2);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_NOT);
  ASSERT_EQ(tokens[0].value, u"!");
  ASSERT_EQ(tokens[1].kind, TOKEN_BOOL_NOT);
  ASSERT_EQ(tokens[1].value, u"!");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, symbol_unicode) {
  lt::Source source("--", lt::LineIndexedUnicodeString("你好"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"你好");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, number_with_symbol_prefix) {
  lt::Source source("--", lt::LineIndexedUnicodeString("_1"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"_1");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, number_with_dots) {
  lt::Source source("--", lt::LineIndexedUnicodeString("10.."));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LITERAL_NUMBER);
  ASSERT_EQ(tokens[0].value, u"10..");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, number_with_separators) {
  lt::Source source("--", lt::LineIndexedUnicodeString("1_000"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LITERAL_NUMBER);
  ASSERT_EQ(tokens[0].value, u"1_000");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, many_whitespace) {
  lt::Source source("--", lt::LineIndexedUnicodeString(
                              "  \t\t\n\n \t\n \t\n \t\n \t\n \t\n"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_ended_with_newline) {
  lt::Source source("--", lt::LineIndexedUnicodeString("// asdf\n"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, symbol_then_comment_line) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x// asdf"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"x");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_then_symbol) {
  lt::Source source("--", lt::LineIndexedUnicodeString("// asdf\nx"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"x");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_empty_then_file_end) {
  lt::Source source("--", lt::LineIndexedUnicodeString("//"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_empty_then_newline) {
  lt::Source source("--", lt::LineIndexedUnicodeString("//\n"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_with_many_slashes) {
  lt::Source source("--", lt::LineIndexedUnicodeString("////////"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_empty) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/**/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_unended) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/*"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 1);
}

TEST(language_forge_lexer, comment_block_one_star) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/*/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 1);
}

TEST(language_forge_lexer, comment_block_many_stars) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/******/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_extra_slash_at_beginning) {
  lt::Source source("--", lt::LineIndexedUnicodeString("//******/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_extra_slash_at_end) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/******//"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DIV);
  ASSERT_EQ(tokens[0].value, u"/");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_with_newlines) {
  lt::Source source("--", lt::LineIndexedUnicodeString("/*\n\nasdf\n\n*/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, symbol_then_comment_block) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x/**/"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(message_context.messages().size(), 0);
}
