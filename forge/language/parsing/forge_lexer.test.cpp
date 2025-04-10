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

#include <forge/language/parsing/forge_lexer.hpp>
#include <forge/language/parsing/forge_token_kind.hpp>

using namespace forge;

TEST(language_forge_lexer, empty) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_as) {
  Source source("--", LineIndexedUnicodeString("as"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_AS);
  ASSERT_EQ(tokens[0].value, u"as");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_bool) {
  Source source("--", LineIndexedUnicodeString("bool"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_BOOL);
  ASSERT_EQ(tokens[0].value, u"bool");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_break) {
  Source source("--", LineIndexedUnicodeString("break"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_BREAK);
  ASSERT_EQ(tokens[0].value, u"break");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_const) {
  Source source("--", LineIndexedUnicodeString("const"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_CONST);
  ASSERT_EQ(tokens[0].value, u"const");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_continue) {
  Source source("--", LineIndexedUnicodeString("continue"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_CONTINUE);
  ASSERT_EQ(tokens[0].value, u"continue");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_do) {
  Source source("--", LineIndexedUnicodeString("do"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_DO);
  ASSERT_EQ(tokens[0].value, u"do");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_else) {
  Source source("--", LineIndexedUnicodeString("else"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_ELSE);
  ASSERT_EQ(tokens[0].value, u"else");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_explicit) {
  Source source("--", LineIndexedUnicodeString("explicit"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_EXPLICIT);
  ASSERT_EQ(tokens[0].value, u"explicit");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_f32) {
  Source source("--", LineIndexedUnicodeString("f32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_F32);
  ASSERT_EQ(tokens[0].value, u"f32");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_f64) {
  Source source("--", LineIndexedUnicodeString("f64"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_F64);
  ASSERT_EQ(tokens[0].value, u"f64");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_false) {
  Source source("--", LineIndexedUnicodeString("false"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_FALSE);
  ASSERT_EQ(tokens[0].value, u"false");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_func) {
  Source source("--", LineIndexedUnicodeString("func"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_FUNC);
  ASSERT_EQ(tokens[0].value, u"func");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_i16) {
  Source source("--", LineIndexedUnicodeString("i16"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_I16);
  ASSERT_EQ(tokens[0].value, u"i16");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_i32) {
  Source source("--", LineIndexedUnicodeString("i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_I32);
  ASSERT_EQ(tokens[0].value, u"i32");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_i8) {
  Source source("--", LineIndexedUnicodeString("i8"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_I8);
  ASSERT_EQ(tokens[0].value, u"i8");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_if) {
  Source source("--", LineIndexedUnicodeString("if"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_IF);
  ASSERT_EQ(tokens[0].value, u"if");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_inherits) {
  Source source("--", LineIndexedUnicodeString("inherits"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_INHERITS);
  ASSERT_EQ(tokens[0].value, u"inherits");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_interface) {
  Source source("--", LineIndexedUnicodeString("interface"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_INTERFACE);
  ASSERT_EQ(tokens[0].value, u"interface");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_isize) {
  Source source("--", LineIndexedUnicodeString("isize"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_ISIZE);
  ASSERT_EQ(tokens[0].value, u"isize");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_let) {
  Source source("--", LineIndexedUnicodeString("let"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_LET);
  ASSERT_EQ(tokens[0].value, u"let");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_namespace) {
  Source source("--", LineIndexedUnicodeString("namespace"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_NAMESPACE);
  ASSERT_EQ(tokens[0].value, u"namespace");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_return) {
  Source source("--", LineIndexedUnicodeString("return"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_RETURN);
  ASSERT_EQ(tokens[0].value, u"return");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_self) {
  Source source("--", LineIndexedUnicodeString("self"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_SELF);
  ASSERT_EQ(tokens[0].value, u"self");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_struct) {
  Source source("--", LineIndexedUnicodeString("struct"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_STRUCT);
  ASSERT_EQ(tokens[0].value, u"struct");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_true) {
  Source source("--", LineIndexedUnicodeString("true"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_TRUE);
  ASSERT_EQ(tokens[0].value, u"true");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_type) {
  Source source("--", LineIndexedUnicodeString("type"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_TYPE);
  ASSERT_EQ(tokens[0].value, u"type");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u16) {
  Source source("--", LineIndexedUnicodeString("u16"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U16);
  ASSERT_EQ(tokens[0].value, u"u16");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u32) {
  Source source("--", LineIndexedUnicodeString("u32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U32);
  ASSERT_EQ(tokens[0].value, u"u32");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u64) {
  Source source("--", LineIndexedUnicodeString("u64"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U64);
  ASSERT_EQ(tokens[0].value, u"u64");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_u8) {
  Source source("--", LineIndexedUnicodeString("u8"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_U8);
  ASSERT_EQ(tokens[0].value, u"u8");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_usize) {
  Source source("--", LineIndexedUnicodeString("usize"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_USIZE);
  ASSERT_EQ(tokens[0].value, u"usize");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_void) {
  Source source("--", LineIndexedUnicodeString("void"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_VOID);
  ASSERT_EQ(tokens[0].value, u"void");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_kw_while) {
  Source source("--", LineIndexedUnicodeString("while"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_KW_WHILE);
  ASSERT_EQ(tokens[0].value, u"while");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bool_not) {
  Source source("--", LineIndexedUnicodeString("!"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_NOT);
  ASSERT_EQ(tokens[0].value, u"!");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bool_and) {
  Source source("--", LineIndexedUnicodeString("&&"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_AND);
  ASSERT_EQ(tokens[0].value, u"&&");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bool_or) {
  Source source("--", LineIndexedUnicodeString("||"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_OR);
  ASSERT_EQ(tokens[0].value, u"||");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_not) {
  Source source("--", LineIndexedUnicodeString("~"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_NOT);
  ASSERT_EQ(tokens[0].value, u"~");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_and) {
  Source source("--", LineIndexedUnicodeString("&"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_AND);
  ASSERT_EQ(tokens[0].value, u"&");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_and_assign) {
  Source source("--", LineIndexedUnicodeString("&="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_AND_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"&=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_or) {
  Source source("--", LineIndexedUnicodeString("|"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_OR);
  ASSERT_EQ(tokens[0].value, u"|");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_or_assign) {
  Source source("--", LineIndexedUnicodeString("|="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_OR_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"|=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_xor) {
  Source source("--", LineIndexedUnicodeString("^"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_XOR);
  ASSERT_EQ(tokens[0].value, u"^");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_xor_assign) {
  Source source("--", LineIndexedUnicodeString("^="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_XOR_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"^=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shl) {
  Source source("--", LineIndexedUnicodeString("<<"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHL);
  ASSERT_EQ(tokens[0].value, u"<<");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shl_assign) {
  Source source("--", LineIndexedUnicodeString("<<="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHL_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"<<=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shr) {
  Source source("--", LineIndexedUnicodeString(">>"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHR);
  ASSERT_EQ(tokens[0].value, u">>");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_bit_shr_assign) {
  Source source("--", LineIndexedUnicodeString(">>="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_BIT_SHR_ASSIGN);
  ASSERT_EQ(tokens[0].value, u">>=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_add) {
  Source source("--", LineIndexedUnicodeString("+"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_ADD);
  ASSERT_EQ(tokens[0].value, u"+");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_add_assign) {
  Source source("--", LineIndexedUnicodeString("+="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_ADD_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"+=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_sub) {
  Source source("--", LineIndexedUnicodeString("-"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SUB);
  ASSERT_EQ(tokens[0].value, u"-");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_sub_assign) {
  Source source("--", LineIndexedUnicodeString("-="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SUB_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"-=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mul) {
  Source source("--", LineIndexedUnicodeString("*"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MUL);
  ASSERT_EQ(tokens[0].value, u"*");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mul_assign) {
  Source source("--", LineIndexedUnicodeString("*="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MUL_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"*=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_exp) {
  Source source("--", LineIndexedUnicodeString("**"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_EXP);
  ASSERT_EQ(tokens[0].value, u"**");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_exp_assign) {
  Source source("--", LineIndexedUnicodeString("**="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_EXP_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"**=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_div) {
  Source source("--", LineIndexedUnicodeString("/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DIV);
  ASSERT_EQ(tokens[0].value, u"/");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_div_assign) {
  Source source("--", LineIndexedUnicodeString("/="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DIV_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"/=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mod) {
  Source source("--", LineIndexedUnicodeString("%"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MOD);
  ASSERT_EQ(tokens[0].value, u"%");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_mod_assign) {
  Source source("--", LineIndexedUnicodeString("%="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_MOD_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"%=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_assign) {
  Source source("--", LineIndexedUnicodeString("="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_ASSIGN);
  ASSERT_EQ(tokens[0].value, u"=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_eq) {
  Source source("--", LineIndexedUnicodeString("=="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_EQ);
  ASSERT_EQ(tokens[0].value, u"==");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_ne) {
  Source source("--", LineIndexedUnicodeString("!="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_NE);
  ASSERT_EQ(tokens[0].value, u"!=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_lt) {
  Source source("--", LineIndexedUnicodeString("<"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LT);
  ASSERT_EQ(tokens[0].value, u"<");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_le) {
  Source source("--", LineIndexedUnicodeString("<="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LE);
  ASSERT_EQ(tokens[0].value, u"<=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_gt) {
  Source source("--", LineIndexedUnicodeString(">"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_GT);
  ASSERT_EQ(tokens[0].value, u">");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_ge) {
  Source source("--", LineIndexedUnicodeString(">="));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_GE);
  ASSERT_EQ(tokens[0].value, u">=");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_lparen) {
  Source source("--", LineIndexedUnicodeString("("));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LPAREN);
  ASSERT_EQ(tokens[0].value, u"(");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_comma) {
  Source source("--", LineIndexedUnicodeString(","));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_COMMA);
  ASSERT_EQ(tokens[0].value, u",");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_rparen) {
  Source source("--", LineIndexedUnicodeString(")"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_RPAREN);
  ASSERT_EQ(tokens[0].value, u")");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_lbrace) {
  Source source("--", LineIndexedUnicodeString("{"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LBRACE);
  ASSERT_EQ(tokens[0].value, u"{");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_semicolon) {
  Source source("--", LineIndexedUnicodeString(";"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SEMICOLON);
  ASSERT_EQ(tokens[0].value, u";");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_rbrace) {
  Source source("--", LineIndexedUnicodeString("}"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_RBRACE);
  ASSERT_EQ(tokens[0].value, u"}");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_colon) {
  Source source("--", LineIndexedUnicodeString(":"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_COLON);
  ASSERT_EQ(tokens[0].value, u":");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_dot) {
  Source source("--", LineIndexedUnicodeString("."));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DOT);
  ASSERT_EQ(tokens[0].value, u".");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_rarrow) {
  Source source("--", LineIndexedUnicodeString("->"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_RARROW);
  ASSERT_EQ(tokens[0].value, u"->");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_symbol) {
  Source source("--", LineIndexedUnicodeString("x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"x");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, one_token_literal_number) {
  Source source("--", LineIndexedUnicodeString("5"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LITERAL_NUMBER);
  ASSERT_EQ(tokens[0].value, u"5");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, space) {
  Source source("--", LineIndexedUnicodeString(" "));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, tab) {
  Source source("--", LineIndexedUnicodeString("\t"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, newline) {
  Source source("--", LineIndexedUnicodeString("\n"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line) {
  Source source("--", LineIndexedUnicodeString("// asdf"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block) {
  Source source("--", LineIndexedUnicodeString("/* asdf */"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, kw_with_prefix) {
  Source source("--", LineIndexedUnicodeString("_if"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"_if");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, kw_with_suffix) {
  Source source("--", LineIndexedUnicodeString("if_"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"if_");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, greedy_punctuation) {
  Source source("--", LineIndexedUnicodeString("!!"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 2);
  ASSERT_EQ(tokens[0].kind, TOKEN_BOOL_NOT);
  ASSERT_EQ(tokens[0].value, u"!");
  ASSERT_EQ(tokens[1].kind, TOKEN_BOOL_NOT);
  ASSERT_EQ(tokens[1].value, u"!");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, symbol_unicode) {
  Source source("--", LineIndexedUnicodeString("你好"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"你好");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, number_with_symbol_prefix) {
  Source source("--", LineIndexedUnicodeString("_1"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"_1");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, number_with_dots) {
  Source source("--", LineIndexedUnicodeString("10.."));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LITERAL_NUMBER);
  ASSERT_EQ(tokens[0].value, u"10..");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, number_with_separators) {
  Source source("--", LineIndexedUnicodeString("1_000"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_LITERAL_NUMBER);
  ASSERT_EQ(tokens[0].value, u"1_000");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, many_whitespace) {
  Source source(
      "--", LineIndexedUnicodeString("  \t\t\n\n \t\n \t\n \t\n \t\n \t\n"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_ended_with_newline) {
  Source source("--", LineIndexedUnicodeString("// asdf\n"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, symbol_then_comment_line) {
  Source source("--", LineIndexedUnicodeString("x// asdf"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"x");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_then_symbol) {
  Source source("--", LineIndexedUnicodeString("// asdf\nx"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].value, u"x");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_empty_then_file_end) {
  Source source("--", LineIndexedUnicodeString("//"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_empty_then_newline) {
  Source source("--", LineIndexedUnicodeString("//\n"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_line_with_many_slashes) {
  Source source("--", LineIndexedUnicodeString("////////"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_empty) {
  Source source("--", LineIndexedUnicodeString("/**/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_unended) {
  Source source("--", LineIndexedUnicodeString("/*"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 1);
}

TEST(language_forge_lexer, comment_block_one_star) {
  Source source("--", LineIndexedUnicodeString("/*/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 1);
}

TEST(language_forge_lexer, comment_block_many_stars) {
  Source source("--", LineIndexedUnicodeString("/******/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_extra_slash_at_beginning) {
  Source source("--", LineIndexedUnicodeString("//******/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_extra_slash_at_end) {
  Source source("--", LineIndexedUnicodeString("/******//"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].kind, TOKEN_DIV);
  ASSERT_EQ(tokens[0].value, u"/");
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, comment_block_with_newlines) {
  Source source("--", LineIndexedUnicodeString("/*\n\nasdf\n\n*/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 0);
  ASSERT_EQ(message_context.messages().size(), 0);
}

TEST(language_forge_lexer, symbol_then_comment_block) {
  Source source("--", LineIndexedUnicodeString("x/**/"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(message_context.messages().size(), 0);
}
