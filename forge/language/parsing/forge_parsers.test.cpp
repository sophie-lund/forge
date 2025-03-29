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

#include <forge/core/string_utilities.hpp>
#include <forge/language/parsing/forge_lexer.hpp>
#include <forge/language/parsing/forge_parsers.hpp>
#include <forge/language/parsing/forge_token_kind.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

using namespace forge;

TEST(language_forge_parsers, type_bool) {
  Source source("--", LineIndexedUnicodeString("bool"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  kind = bool\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_void) {
  Source source("--", LineIndexedUnicodeString("void"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  kind = void\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_isize) {
  Source source("--", LineIndexedUnicodeString("isize"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  kind = isize\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_usize) {
  Source source("--", LineIndexedUnicodeString("usize"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  kind = usize\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_symbol) {
  Source source("--", LineIndexedUnicodeString("String"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_symbol]\n"
            "  name = \"String\"\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i8) {
  Source source("--", LineIndexedUnicodeString("i8"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = signed_int\n"
            "  bit_width = 8\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i16) {
  Source source("--", LineIndexedUnicodeString("i16"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = signed_int\n"
            "  bit_width = 16\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i32) {
  Source source("--", LineIndexedUnicodeString("i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = signed_int\n"
            "  bit_width = 32\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i64) {
  Source source("--", LineIndexedUnicodeString("i64"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = signed_int\n"
            "  bit_width = 64\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u8) {
  Source source("--", LineIndexedUnicodeString("u8"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = unsigned_int\n"
            "  bit_width = 8\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u16) {
  Source source("--", LineIndexedUnicodeString("u16"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = unsigned_int\n"
            "  bit_width = 16\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u32) {
  Source source("--", LineIndexedUnicodeString("u32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = unsigned_int\n"
            "  bit_width = 32\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u64) {
  Source source("--", LineIndexedUnicodeString("u64"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = unsigned_int\n"
            "  bit_width = 64\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_f32) {
  Source source("--", LineIndexedUnicodeString("f32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = float\n"
            "  bit_width = 32\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_f64) {
  Source source("--", LineIndexedUnicodeString("f64"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = float\n"
            "  bit_width = 64\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_const_i32) {
  Source source("--", LineIndexedUnicodeString("const i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  kind = signed_int\n"
            "  bit_width = 32\n"
            "  is_const = true");
}

TEST(language_forge_parsers, type_i32_pointer) {
  Source source("--", LineIndexedUnicodeString("*i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_pointer_to_const_i32) {
  Source source("--", LineIndexedUnicodeString("*const i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = true\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_const_pointer_to_i32) {
  Source source("--", LineIndexedUnicodeString("const *i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  is_const = true");
}

TEST(language_forge_parsers, type_const_pointer_to_const_i32) {
  Source source("--", LineIndexedUnicodeString("const *const i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = true\n"
            "  is_const = true");
}

TEST(language_forge_parsers, type_double_pointer_i32_with_space) {
  Source source("--", LineIndexedUnicodeString("* *i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_unary]\n"
            "    kind = pointer\n"
            "    operand_type = [type_with_bit_width]\n"
            "      kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_double_pointer_i32_without_space) {
  Source source("--", LineIndexedUnicodeString("**i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_unary]\n"
            "    kind = pointer\n"
            "    operand_type = [type_with_bit_width]\n"
            "      kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_triple_pointer_i32_without_space) {
  Source source("--", LineIndexedUnicodeString("***i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  kind = pointer\n"
            "  operand_type = [type_unary]\n"
            "    kind = pointer\n"
            "    operand_type = [type_unary]\n"
            "      kind = pointer\n"
            "      operand_type = [type_with_bit_width]\n"
            "        kind = signed_int\n"
            "        bit_width = 32\n"
            "        is_const = false\n"
            "      is_const = false\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, value_literal_bool_false) {
  Source source("--", LineIndexedUnicodeString("false"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_literal_bool]\n"
            "  value = false");
}

TEST(language_forge_parsers, value_literal_bool_true) {
  Source source("--", LineIndexedUnicodeString("true"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_literal_bool]\n"
            "  value = true");
}

TEST(language_forge_parsers, value_literal_number_0) {
  Source source("--", LineIndexedUnicodeString("0"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_literal_number]\n"
            "  type = [type_with_bit_width]\n"
            "    kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  value = 0");
}

TEST(language_forge_parsers, value_symbol) {
  Source source("--", LineIndexedUnicodeString("x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_symbol]\n"
            "  name = \"x\"");
}

TEST(language_forge_parsers, value_member_access) {
  Source source("--", LineIndexedUnicodeString("x.y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = .\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_parenthesis) {
  Source source("--", LineIndexedUnicodeString("(x.y)"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = .\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_function_call_no_args) {
  Source source("--", LineIndexedUnicodeString("f()"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_call]\n"
            "  callee = [value_symbol]\n"
            "    name = \"f\"\n"
            "  args = []");
}

TEST(language_forge_parsers, value_function_call_one_arg) {
  Source source("--", LineIndexedUnicodeString("f(x)"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_call]\n"
            "  callee = [value_symbol]\n"
            "    name = \"f\"\n"
            "  args = \n"
            "    [0] = [value_symbol]\n"
            "      name = \"x\"");
}

TEST(language_forge_parsers, value_function_call_two_args) {
  Source source("--", LineIndexedUnicodeString("f(x, y)"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_call]\n"
            "  callee = [value_symbol]\n"
            "    name = \"f\"\n"
            "  args = \n"
            "    [0] = [value_symbol]\n"
            "      name = \"x\"\n"
            "    [1] = [value_symbol]\n"
            "      name = \"y\"");
}

TEST(language_forge_parsers, value_deref) {
  Source source("--", LineIndexedUnicodeString("*x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = *\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_getaddr) {
  Source source("--", LineIndexedUnicodeString("&x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = &\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_neg) {
  Source source("--", LineIndexedUnicodeString("-x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = -\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_pos) {
  Source source("--", LineIndexedUnicodeString("+x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = +\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_bit_not) {
  Source source("--", LineIndexedUnicodeString("~x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = ~\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_bool_not) {
  Source source("--", LineIndexedUnicodeString("!x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = !\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_exp) {
  Source source("--", LineIndexedUnicodeString("x ** y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = **\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_mul) {
  Source source("--", LineIndexedUnicodeString("x * y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = *\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_div) {
  Source source("--", LineIndexedUnicodeString("x / y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = /\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_mod) {
  Source source("--", LineIndexedUnicodeString("x % y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = %\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_add) {
  Source source("--", LineIndexedUnicodeString("x + y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = +\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_sub) {
  Source source("--", LineIndexedUnicodeString("x - y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = -\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_shl) {
  Source source("--", LineIndexedUnicodeString("x << y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = <<\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_shr) {
  Source source("--", LineIndexedUnicodeString("x >> y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = >>\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_and) {
  Source source("--", LineIndexedUnicodeString("x & y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = &\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_xor) {
  Source source("--", LineIndexedUnicodeString("x ^ y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = ^\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_or) {
  Source source("--", LineIndexedUnicodeString("x | y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = |\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_eq) {
  Source source("--", LineIndexedUnicodeString("x == y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = ==\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_ne) {
  Source source("--", LineIndexedUnicodeString("x != y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = !=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_lt) {
  Source source("--", LineIndexedUnicodeString("x < y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = <\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_le) {
  Source source("--", LineIndexedUnicodeString("x <= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = <=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_gt) {
  Source source("--", LineIndexedUnicodeString("x > y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = >\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_ge) {
  Source source("--", LineIndexedUnicodeString("x >= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = >=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bool_and) {
  Source source("--", LineIndexedUnicodeString("x && y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = &&\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bool_or) {
  Source source("--", LineIndexedUnicodeString("x || y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = ||\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_cast) {
  Source source("--", LineIndexedUnicodeString("x as i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_cast]\n"
            "  value = [value_symbol]\n"
            "    name = \"x\"\n"
            "  type = [type_with_bit_width]\n"
            "    kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false");
}

TEST(language_forge_parsers, value_bit_and_assign) {
  Source source("--", LineIndexedUnicodeString("x &= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = &=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_or_assign) {
  Source source("--", LineIndexedUnicodeString("x |= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = |=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_xor_assign) {
  Source source("--", LineIndexedUnicodeString("x ^= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = ^=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_shl_assign) {
  Source source("--", LineIndexedUnicodeString("x <<= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = <<=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_bit_shr_assign) {
  Source source("--", LineIndexedUnicodeString("x >>= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = >>=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_add_assign) {
  Source source("--", LineIndexedUnicodeString("x += y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = +=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_sub_assign) {
  Source source("--", LineIndexedUnicodeString("x -= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = -=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_mul_assign) {
  Source source("--", LineIndexedUnicodeString("x *= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = *=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_exp_assign) {
  Source source("--", LineIndexedUnicodeString("x **= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = **=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_div_assign) {
  Source source("--", LineIndexedUnicodeString("x /= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = /=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_mod_assign) {
  Source source("--", LineIndexedUnicodeString("x %= y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = %=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_assign) {
  Source source("--", LineIndexedUnicodeString("x = y"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = =\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_symbol]\n"
            "    name = \"y\"");
}

TEST(language_forge_parsers, value_precedence_unary) {
  Source source("--", LineIndexedUnicodeString("*&-+~!x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = *\n"
            "  operand = [value_unary]\n"
            "    operator = &\n"
            "    operand = [value_unary]\n"
            "      operator = -\n"
            "      operand = [value_unary]\n"
            "        operator = +\n"
            "        operand = [value_unary]\n"
            "          operator = ~\n"
            "          operand = [value_unary]\n"
            "            operator = !\n"
            "            operand = [value_symbol]\n"
            "              name = \"x\"");
}

TEST(language_forge_parsers, value_precedence_unary_reversed) {
  Source source("--", LineIndexedUnicodeString("!~+-&*x"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = !\n"
            "  operand = [value_unary]\n"
            "    operator = ~\n"
            "    operand = [value_unary]\n"
            "      operator = +\n"
            "      operand = [value_unary]\n"
            "        operator = -\n"
            "        operand = [value_unary]\n"
            "          operator = &\n"
            "          operand = [value_unary]\n"
            "            operator = *\n"
            "            operand = [value_symbol]\n"
            "              name = \"x\"");
}

TEST(language_forge_parsers, value_precedence_multiplicative) {
  Source source("--", LineIndexedUnicodeString("x * y / z % w"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = *\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = /\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_binary]\n"
            "      operator = %\n"
            "      lhs = [value_symbol]\n"
            "        name = \"z\"\n"
            "      rhs = [value_symbol]\n"
            "        name = \"w\"");
}

TEST(language_forge_parsers, value_precedence_multiplicative_reversed) {
  Source source("--", LineIndexedUnicodeString("x % y / z * w"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = %\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = /\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_binary]\n"
            "      operator = *\n"
            "      lhs = [value_symbol]\n"
            "        name = \"z\"\n"
            "      rhs = [value_symbol]\n"
            "        name = \"w\"");
}

TEST(language_forge_parsers, value_precedence_additive) {
  Source source("--", LineIndexedUnicodeString("x + y - z"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = +\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = -\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_symbol]\n"
            "      name = \"z\"");
}

TEST(language_forge_parsers, value_precedence_additive_reversed) {
  Source source("--", LineIndexedUnicodeString("x - y + z"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = -\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = +\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_symbol]\n"
            "      name = \"z\"");
}

TEST(language_forge_parsers, value_precedence_bit_shifts) {
  Source source("--", LineIndexedUnicodeString("x << y >> z"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = <<\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = >>\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_symbol]\n"
            "      name = \"z\"");
}

TEST(language_forge_parsers, value_precedence_bit_shifts_reversed) {
  Source source("--", LineIndexedUnicodeString("x >> y << z"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = >>\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = <<\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_symbol]\n"
            "      name = \"z\"");
}

TEST(language_forge_parsers, value_precedence_binary_conjunctive) {
  Source source("--", LineIndexedUnicodeString("x & y ^ z"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = &\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = ^\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_symbol]\n"
            "      name = \"z\"");
}

TEST(language_forge_parsers, value_precedence_binary_conjunctive_reversed) {
  Source source("--", LineIndexedUnicodeString("x ^ y & z"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = ^\n"
            "  lhs = [value_symbol]\n"
            "    name = \"x\"\n"
            "  rhs = [value_binary]\n"
            "    operator = &\n"
            "    lhs = [value_symbol]\n"
            "      name = \"y\"\n"
            "    rhs = [value_symbol]\n"
            "      name = \"z\"");
}

TEST(language_forge_parsers, value_precedence_binary_comparative) {
  Source source("--",
                LineIndexedUnicodeString("a == b != c < d <= e > f >= g"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = ==\n"
            "  lhs = [value_symbol]\n"
            "    name = \"a\"\n"
            "  rhs = [value_binary]\n"
            "    operator = !=\n"
            "    lhs = [value_symbol]\n"
            "      name = \"b\"\n"
            "    rhs = [value_binary]\n"
            "      operator = <\n"
            "      lhs = [value_symbol]\n"
            "        name = \"c\"\n"
            "      rhs = [value_binary]\n"
            "        operator = <=\n"
            "        lhs = [value_symbol]\n"
            "          name = \"d\"\n"
            "        rhs = [value_binary]\n"
            "          operator = >\n"
            "          lhs = [value_symbol]\n"
            "            name = \"e\"\n"
            "          rhs = [value_binary]\n"
            "            operator = >=\n"
            "            lhs = [value_symbol]\n"
            "              name = \"f\"\n"
            "            rhs = [value_symbol]\n"
            "              name = \"g\"");
}

TEST(language_forge_parsers, value_precedence_binary_comparative_reversed) {
  Source source("--",
                LineIndexedUnicodeString("a != b == c > d >= e < f <= g"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = !=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"a\"\n"
            "  rhs = [value_binary]\n"
            "    operator = ==\n"
            "    lhs = [value_symbol]\n"
            "      name = \"b\"\n"
            "    rhs = [value_binary]\n"
            "      operator = >\n"
            "      lhs = [value_symbol]\n"
            "        name = \"c\"\n"
            "      rhs = [value_binary]\n"
            "        operator = >=\n"
            "        lhs = [value_symbol]\n"
            "          name = \"d\"\n"
            "        rhs = [value_binary]\n"
            "          operator = <\n"
            "          lhs = [value_symbol]\n"
            "            name = \"e\"\n"
            "          rhs = [value_binary]\n"
            "            operator = <=\n"
            "            lhs = [value_symbol]\n"
            "              name = \"f\"\n"
            "            rhs = [value_symbol]\n"
            "              name = \"g\"");
}

TEST(language_forge_parsers, value_precedence_assignments) {
  Source source(
      "--",
      LineIndexedUnicodeString(
          "a &= b |= c ^= d <<= e >>= f += g -= h *= i /= j %= k **= l = m"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = &=\n"
            "  lhs = [value_symbol]\n"
            "    name = \"a\"\n"
            "  rhs = [value_binary]\n"
            "    operator = |=\n"
            "    lhs = [value_symbol]\n"
            "      name = \"b\"\n"
            "    rhs = [value_binary]\n"
            "      operator = ^=\n"
            "      lhs = [value_symbol]\n"
            "        name = \"c\"\n"
            "      rhs = [value_binary]\n"
            "        operator = <<=\n"
            "        lhs = [value_symbol]\n"
            "          name = \"d\"\n"
            "        rhs = [value_binary]\n"
            "          operator = >>=\n"
            "          lhs = [value_symbol]\n"
            "            name = \"e\"\n"
            "          rhs = [value_binary]\n"
            "            operator = +=\n"
            "            lhs = [value_symbol]\n"
            "              name = \"f\"\n"
            "            rhs = [value_binary]\n"
            "              operator = -=\n"
            "              lhs = [value_symbol]\n"
            "                name = \"g\"\n"
            "              rhs = [value_binary]\n"
            "                operator = *=\n"
            "                lhs = [value_symbol]\n"
            "                  name = \"h\"\n"
            "                rhs = [value_binary]\n"
            "                  operator = /=\n"
            "                  lhs = [value_symbol]\n"
            "                    name = \"i\"\n"
            "                  rhs = [value_binary]\n"
            "                    operator = %=\n"
            "                    lhs = [value_symbol]\n"
            "                      name = \"j\"\n"
            "                    rhs = [value_binary]\n"
            "                      operator = **=\n"
            "                      lhs = [value_symbol]\n"
            "                        name = \"k\"\n"
            "                      rhs = [value_binary]\n"
            "                        operator = =\n"
            "                        lhs = [value_symbol]\n"
            "                          name = \"l\"\n"
            "                        rhs = [value_symbol]\n"
            "                          name = \"m\"");
}

TEST(language_forge_parsers, value_precedence_assignments_reversed) {
  Source source(
      "--",
      LineIndexedUnicodeString(
          "a = b **= c %= d /= e *= f -= g += h >>= i <<= j ^= k |= l &= m"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = =\n"
            "  lhs = [value_symbol]\n"
            "    name = \"a\"\n"
            "  rhs = [value_binary]\n"
            "    operator = **=\n"
            "    lhs = [value_symbol]\n"
            "      name = \"b\"\n"
            "    rhs = [value_binary]\n"
            "      operator = %=\n"
            "      lhs = [value_symbol]\n"
            "        name = \"c\"\n"
            "      rhs = [value_binary]\n"
            "        operator = /=\n"
            "        lhs = [value_symbol]\n"
            "          name = \"d\"\n"
            "        rhs = [value_binary]\n"
            "          operator = *=\n"
            "          lhs = [value_symbol]\n"
            "            name = \"e\"\n"
            "          rhs = [value_binary]\n"
            "            operator = -=\n"
            "            lhs = [value_symbol]\n"
            "              name = \"f\"\n"
            "            rhs = [value_binary]\n"
            "              operator = +=\n"
            "              lhs = [value_symbol]\n"
            "                name = \"g\"\n"
            "              rhs = [value_binary]\n"
            "                operator = >>=\n"
            "                lhs = [value_symbol]\n"
            "                  name = \"h\"\n"
            "                rhs = [value_binary]\n"
            "                  operator = <<=\n"
            "                  lhs = [value_symbol]\n"
            "                    name = \"i\"\n"
            "                  rhs = [value_binary]\n"
            "                    operator = ^=\n"
            "                    lhs = [value_symbol]\n"
            "                      name = \"j\"\n"
            "                    rhs = [value_binary]\n"
            "                      operator = |=\n"
            "                      lhs = [value_symbol]\n"
            "                        name = \"k\"\n"
            "                      rhs = [value_binary]\n"
            "                        operator = &=\n"
            "                        lhs = [value_symbol]\n"
            "                          name = \"l\"\n"
            "                        rhs = [value_symbol]\n"
            "                          name = \"m\"");
}

TEST(language_forge_parsers, value_precedence_group_order) {
  Source source(
      "--", LineIndexedUnicodeString(
                "a = b || c && d == e | f & g << h + i * j ** *k.l() as i32"));

  MessageContext message_context;
  ForgeLexer lexer;

  std::vector<Token> tokens = lexer.lex(message_context, source);

  ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_binary]\n"
            "  operator = =\n"
            "  lhs = [value_symbol]\n"
            "    name = \"a\"\n"
            "  rhs = [value_cast]\n"
            "    value = [value_binary]\n"
            "      operator = ||\n"
            "      lhs = [value_symbol]\n"
            "        name = \"b\"\n"
            "      rhs = [value_binary]\n"
            "        operator = &&\n"
            "        lhs = [value_symbol]\n"
            "          name = \"c\"\n"
            "        rhs = [value_binary]\n"
            "          operator = ==\n"
            "          lhs = [value_symbol]\n"
            "            name = \"d\"\n"
            "          rhs = [value_binary]\n"
            "            operator = |\n"
            "            lhs = [value_symbol]\n"
            "              name = \"e\"\n"
            "            rhs = [value_binary]\n"
            "              operator = &\n"
            "              lhs = [value_symbol]\n"
            "                name = \"f\"\n"
            "              rhs = [value_binary]\n"
            "                operator = <<\n"
            "                lhs = [value_symbol]\n"
            "                  name = \"g\"\n"
            "                rhs = [value_binary]\n"
            "                  operator = +\n"
            "                  lhs = [value_symbol]\n"
            "                    name = \"h\"\n"
            "                  rhs = [value_binary]\n"
            "                    operator = *\n"
            "                    lhs = [value_symbol]\n"
            "                      name = \"i\"\n"
            "                    rhs = [value_binary]\n"
            "                      operator = **\n"
            "                      lhs = [value_symbol]\n"
            "                        name = \"j\"\n"
            "                      rhs = [value_unary]\n"
            "                        operator = *\n"
            "                        operand = [value_call]\n"
            "                          callee = [value_binary]\n"
            "                            operator = .\n"
            "                            lhs = [value_symbol]\n"
            "                              name = \"k\"\n"
            "                            rhs = [value_symbol]\n"
            "                              name = \"l\"\n"
            "                          args = []\n"
            "    type = [type_with_bit_width]\n"
            "      kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false");
}
