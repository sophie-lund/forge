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
#include <forgec/parsing/forge_parsers.hpp>
#include <forgec/parsing/forge_token_kind.hpp>
#include <langtools/core/string_utilities.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>

using namespace forge;

TEST(language_forge_parsers, type_bool) {
  lt::Source source("--", lt::LineIndexedUnicodeString("bool"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  type_basic_kind = bool\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_void) {
  lt::Source source("--", lt::LineIndexedUnicodeString("void"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  type_basic_kind = void\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_isize) {
  lt::Source source("--", lt::LineIndexedUnicodeString("isize"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  type_basic_kind = isize\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_usize) {
  lt::Source source("--", lt::LineIndexedUnicodeString("usize"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_basic]\n"
            "  type_basic_kind = usize\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_symbol) {
  lt::Source source("--", lt::LineIndexedUnicodeString("String"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_symbol]\n"
            "  name = \"String\"\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i8) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i8"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = signed_int\n"
            "  bit_width = 8\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i16) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i16"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = signed_int\n"
            "  bit_width = 16\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = signed_int\n"
            "  bit_width = 32\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_i64) {
  lt::Source source("--", lt::LineIndexedUnicodeString("i64"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = signed_int\n"
            "  bit_width = 64\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u8) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u8"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = unsigned_int\n"
            "  bit_width = 8\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u16) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u16"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = unsigned_int\n"
            "  bit_width = 16\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = unsigned_int\n"
            "  bit_width = 32\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_u64) {
  lt::Source source("--", lt::LineIndexedUnicodeString("u64"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = unsigned_int\n"
            "  bit_width = 64\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_f32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("f32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = float\n"
            "  bit_width = 32\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_f64) {
  lt::Source source("--", lt::LineIndexedUnicodeString("f64"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = float\n"
            "  bit_width = 64\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_const_i32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("const i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_with_bit_width]\n"
            "  type_with_bit_width_kind = signed_int\n"
            "  bit_width = 32\n"
            "  is_const = true");
}

TEST(language_forge_parsers, type_i32_pointer) {
  lt::Source source("--", lt::LineIndexedUnicodeString("*i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_pointer_to_const_i32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("*const i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = true\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_const_pointer_to_i32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("const *i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  is_const = true");
}

TEST(language_forge_parsers, type_const_pointer_to_const_i32) {
  lt::Source source("--", lt::LineIndexedUnicodeString("const *const i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = true\n"
            "  is_const = true");
}

TEST(language_forge_parsers, type_double_pointer_i32_with_space) {
  lt::Source source("--", lt::LineIndexedUnicodeString("* *i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_unary]\n"
            "    type_unary_kind = pointer\n"
            "    operand_type = [type_with_bit_width]\n"
            "      type_with_bit_width_kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_double_pointer_i32_without_space) {
  lt::Source source("--", lt::LineIndexedUnicodeString("**i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_unary]\n"
            "    type_unary_kind = pointer\n"
            "    operand_type = [type_with_bit_width]\n"
            "      type_with_bit_width_kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, type_triple_pointer_i32_without_space) {
  lt::Source source("--", lt::LineIndexedUnicodeString("***i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseType> tree = parse_type(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[type_unary]\n"
            "  type_unary_kind = pointer\n"
            "  operand_type = [type_unary]\n"
            "    type_unary_kind = pointer\n"
            "    operand_type = [type_unary]\n"
            "      type_unary_kind = pointer\n"
            "      operand_type = [type_with_bit_width]\n"
            "        type_with_bit_width_kind = signed_int\n"
            "        bit_width = 32\n"
            "        is_const = false\n"
            "      is_const = false\n"
            "    is_const = false\n"
            "  is_const = false");
}

TEST(language_forge_parsers, value_literal_bool_false) {
  lt::Source source("--", lt::LineIndexedUnicodeString("false"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_literal_bool]\n"
            "  value = false");
}

TEST(language_forge_parsers, value_literal_bool_true) {
  lt::Source source("--", lt::LineIndexedUnicodeString("true"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_literal_bool]\n"
            "  value = true");
}

TEST(language_forge_parsers, value_literal_number_0) {
  lt::Source source("--", lt::LineIndexedUnicodeString("0"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_literal_number]\n"
            "  type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  value = 0");
}

TEST(language_forge_parsers, value_symbol) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_symbol]\n"
            "  name = \"x\"");
}

TEST(language_forge_parsers, value_member_access) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x.y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("(x.y)"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("f()"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_call]\n"
            "  callee = [value_symbol]\n"
            "    name = \"f\"\n"
            "  args = []");
}

TEST(language_forge_parsers, value_function_call_one_arg) {
  lt::Source source("--", lt::LineIndexedUnicodeString("f(x)"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("f(x, y)"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("*x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = *\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_getaddr) {
  lt::Source source("--", lt::LineIndexedUnicodeString("&x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = &\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_neg) {
  lt::Source source("--", lt::LineIndexedUnicodeString("-x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = -\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_pos) {
  lt::Source source("--", lt::LineIndexedUnicodeString("+x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = +\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_bit_not) {
  lt::Source source("--", lt::LineIndexedUnicodeString("~x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = ~\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_bool_not) {
  lt::Source source("--", lt::LineIndexedUnicodeString("!x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_unary]\n"
            "  operator = !\n"
            "  operand = [value_symbol]\n"
            "    name = \"x\"");
}

TEST(language_forge_parsers, value_exp) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x ** y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x * y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x / y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x % y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x + y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x - y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x << y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x >> y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x & y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x ^ y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x | y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x == y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x != y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x < y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x <= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x > y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x >= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x && y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x || y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x as i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[value_cast]\n"
            "  value = [value_symbol]\n"
            "    name = \"x\"\n"
            "  type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false");
}

TEST(language_forge_parsers, value_bit_and_assign) {
  lt::Source source("--", lt::LineIndexedUnicodeString("x &= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x |= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x ^= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x <<= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x >>= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x += y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x -= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x *= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x **= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x /= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x %= y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x = y"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("*&-+~!x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("!~+-&*x"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x * y / z % w"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x % y / z * w"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x + y - z"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x - y + z"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x << y >> z"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x >> y << z"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x & y ^ z"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source("--", lt::LineIndexedUnicodeString("x ^ y & z"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source(
      "--", lt::LineIndexedUnicodeString("a == b != c < d <= e > f >= g"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source(
      "--", lt::LineIndexedUnicodeString("a != b == c > d >= e < f <= g"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source(
      "--",
      lt::LineIndexedUnicodeString(
          "a &= b |= c ^= d <<= e >>= f += g -= h *= i /= j %= k **= l = m"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source(
      "--",
      lt::LineIndexedUnicodeString(
          "a = b **= c %= d /= e *= f -= g += h >>= i <<= j ^= k |= l &= m"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
  lt::Source source(
      "--", lt::LineIndexedUnicodeString(
                "a = b || c && d == e | f & g << h + i * j ** *k.l() as i32"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseValue> tree = parse_value(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
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
            "      type_with_bit_width_kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false");
}

TEST(language_forge_parsers, statement_continue) {
  lt::Source source("--", lt::LineIndexedUnicodeString("continue;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_basic]\n"
            "  statement_basic_kind = continue");
}

TEST(language_forge_parsers, statement_break) {
  lt::Source source("--", lt::LineIndexedUnicodeString("break;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_basic]\n"
            "  statement_basic_kind = break");
}

TEST(language_forge_parsers, statement_execute) {
  lt::Source source("--", lt::LineIndexedUnicodeString("5;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_value]\n"
            "  statement_value_kind = execute\n"
            "  value = [value_literal_number]\n"
            "    type = [type_with_bit_width]\n"
            "      type_with_bit_width_kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    value = 5");
}

TEST(language_forge_parsers, statement_return_void) {
  lt::Source source("--", lt::LineIndexedUnicodeString("return;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_basic]\n"
            "  statement_basic_kind = return_void");
}

TEST(language_forge_parsers, statement_return_value) {
  lt::Source source("--", lt::LineIndexedUnicodeString("return 5;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_value]\n"
            "  statement_value_kind = return\n"
            "  value = [value_literal_number]\n"
            "    type = [type_with_bit_width]\n"
            "      type_with_bit_width_kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    value = 5");
}

TEST(language_forge_parsers, statement_block) {
  lt::Source source("--", lt::LineIndexedUnicodeString("{ continue; break; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_block]\n"
            "  statements = \n"
            "    [0] = [statement_basic]\n"
            "      statement_basic_kind = continue\n"
            "    [1] = [statement_basic]\n"
            "      statement_basic_kind = break");
}

TEST(language_forge_parsers, statement_if_then) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("if true { continue; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_if]\n"
            "  condition = [value_literal_bool]\n"
            "    value = true\n"
            "  then = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = continue\n"
            "  else = null");
}

TEST(language_forge_parsers, statement_if_then_else) {
  lt::Source source("--", lt::LineIndexedUnicodeString(
                              "if true { continue; } else { break; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_if]\n"
            "  condition = [value_literal_bool]\n"
            "    value = true\n"
            "  then = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = continue\n"
            "  else = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = break");
}

TEST(language_forge_parsers, statement_if_then_else_if) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString(
                        "if true { continue; } else if false { break; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_if]\n"
            "  condition = [value_literal_bool]\n"
            "    value = true\n"
            "  then = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = continue\n"
            "  else = [statement_if]\n"
            "    condition = [value_literal_bool]\n"
            "      value = false\n"
            "    then = [statement_block]\n"
            "      statements = \n"
            "        [0] = [statement_basic]\n"
            "          statement_basic_kind = break\n"
            "    else = null");
}

TEST(language_forge_parsers, statement_while) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("while true { continue; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_while]\n"
            "  condition = [value_literal_bool]\n"
            "    value = true\n"
            "  body = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = continue\n"
            "  is_do_while = false");
}

TEST(language_forge_parsers, statement_do_while) {
  lt::Source source(
      "--", lt::LineIndexedUnicodeString("do { continue; } while true;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseStatement> tree = parse_statement(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[statement_while]\n"
            "  condition = [value_literal_bool]\n"
            "    value = true\n"
            "  body = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = continue\n"
            "  is_do_while = true");
}

TEST(language_forge_parsers, declaration_variable_minimal) {
  lt::Source source("--", lt::LineIndexedUnicodeString("let x;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_variable]\n"
            "  name = \"x\"\n"
            "  type = null\n"
            "  initial_value = null\n"
            "  is_const = false");
}

TEST(language_forge_parsers, declaration_variable_const) {
  lt::Source source("--", lt::LineIndexedUnicodeString("const x;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_variable]\n"
            "  name = \"x\"\n"
            "  type = null\n"
            "  initial_value = null\n"
            "  is_const = true");
}

TEST(language_forge_parsers, declaration_variable_with_type) {
  lt::Source source("--", lt::LineIndexedUnicodeString("let x: i32;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_variable]\n"
            "  name = \"x\"\n"
            "  type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  initial_value = null\n"
            "  is_const = false");
}

TEST(language_forge_parsers, declaration_variable_with_initial_value) {
  lt::Source source("--", lt::LineIndexedUnicodeString("let x = 5;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_variable]\n"
            "  name = \"x\"\n"
            "  type = null\n"
            "  initial_value = [value_literal_number]\n"
            "    type = [type_with_bit_width]\n"
            "      type_with_bit_width_kind = signed_int\n"
            "      bit_width = 32\n"
            "      is_const = false\n"
            "    value = 5\n"
            "  is_const = false");
}

TEST(language_forge_parsers, declaration_function_minimal) {
  lt::Source source("--", lt::LineIndexedUnicodeString("func f() {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_function]\n"
            "  name = \"f\"\n"
            "  args = []\n"
            "  return_type = null\n"
            "  body = [statement_block]\n"
            "    statements = []");
}

TEST(language_forge_parsers, declaration_function_with_args) {
  lt::Source source("--", lt::LineIndexedUnicodeString("func f(x: i32, y) {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_function]\n"
            "  name = \"f\"\n"
            "  args = \n"
            "    [0] = [declaration_variable]\n"
            "      name = \"x\"\n"
            "      type = [type_with_bit_width]\n"
            "        type_with_bit_width_kind = signed_int\n"
            "        bit_width = 32\n"
            "        is_const = false\n"
            "      initial_value = null\n"
            "      is_const = false\n"
            "    [1] = [declaration_variable]\n"
            "      name = \"y\"\n"
            "      type = null\n"
            "      initial_value = null\n"
            "      is_const = false\n"
            "  return_type = null\n"
            "  body = [statement_block]\n"
            "    statements = []");
}

TEST(language_forge_parsers, declaration_function_with_return_type) {
  lt::Source source("--", lt::LineIndexedUnicodeString("func f() -> i32 {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_function]\n"
            "  name = \"f\"\n"
            "  args = []\n"
            "  return_type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  body = [statement_block]\n"
            "    statements = []");
}

TEST(language_forge_parsers, declaration_function_with_body) {
  lt::Source source("--", lt::LineIndexedUnicodeString("func f() { return; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_function]\n"
            "  name = \"f\"\n"
            "  args = []\n"
            "  return_type = null\n"
            "  body = [statement_block]\n"
            "    statements = \n"
            "      [0] = [statement_basic]\n"
            "        statement_basic_kind = return_void");
}

TEST(language_forge_parsers, declaration_type_alias) {
  lt::Source source("--", lt::LineIndexedUnicodeString("type T = i32;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_type_alias]\n"
            "  name = \"T\"\n"
            "  type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  is_explicit = false");
}

TEST(language_forge_parsers, declaration_type_alias_explicit) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("explicit type T = i32;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_type_alias]\n"
            "  name = \"T\"\n"
            "  type = [type_with_bit_width]\n"
            "    type_with_bit_width_kind = signed_int\n"
            "    bit_width = 32\n"
            "    is_const = false\n"
            "  is_explicit = true");
}

TEST(language_forge_parsers, declaration_struct_minimal) {
  lt::Source source("--", lt::LineIndexedUnicodeString("struct T {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = struct\n"
            "  members = []\n"
            "  inherits = []");
}

TEST(language_forge_parsers, declaration_struct_inherit_1) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("struct T inherits U {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = struct\n"
            "  members = []\n"
            "  inherits = \n"
            "    [0] = [type_symbol]\n"
            "      name = \"U\"\n"
            "      is_const = false");
}

TEST(language_forge_parsers, declaration_struct_inherit_2) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("struct T inherits U, V {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = struct\n"
            "  members = []\n"
            "  inherits = \n"
            "    [0] = [type_symbol]\n"
            "      name = \"U\"\n"
            "      is_const = false\n"
            "    [1] = [type_symbol]\n"
            "      name = \"V\"\n"
            "      is_const = false");
}

TEST(language_forge_parsers, declaration_struct_with_member) {
  lt::Source source("--", lt::LineIndexedUnicodeString("struct T { x: i32; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = struct\n"
            "  members = \n"
            "    [0] = [declaration_variable]\n"
            "      name = \"x\"\n"
            "      type = [type_with_bit_width]\n"
            "        type_with_bit_width_kind = signed_int\n"
            "        bit_width = 32\n"
            "        is_const = false\n"
            "      initial_value = null\n"
            "      is_const = false\n"
            "  inherits = []");
}

TEST(language_forge_parsers, declaration_interface_minimal) {
  lt::Source source("--", lt::LineIndexedUnicodeString("interface T {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = interface\n"
            "  members = []\n"
            "  inherits = []");
}

TEST(language_forge_parsers, declaration_interface_inherit_1) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("interface T inherits U {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = interface\n"
            "  members = []\n"
            "  inherits = \n"
            "    [0] = [type_symbol]\n"
            "      name = \"U\"\n"
            "      is_const = false");
}

TEST(language_forge_parsers, declaration_interface_inherit_2) {
  lt::Source source(
      "--", lt::LineIndexedUnicodeString("interface T inherits U, V {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = interface\n"
            "  members = []\n"
            "  inherits = \n"
            "    [0] = [type_symbol]\n"
            "      name = \"U\"\n"
            "      is_const = false\n"
            "    [1] = [type_symbol]\n"
            "      name = \"V\"\n"
            "      is_const = false");
}

TEST(language_forge_parsers, declaration_interface_with_member) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("interface T { x: i32; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_structured_type]\n"
            "  name = \"T\"\n"
            "  structured_type_kind = interface\n"
            "  members = \n"
            "    [0] = [declaration_variable]\n"
            "      name = \"x\"\n"
            "      type = [type_with_bit_width]\n"
            "        type_with_bit_width_kind = signed_int\n"
            "        bit_width = 32\n"
            "        is_const = false\n"
            "      initial_value = null\n"
            "      is_const = false\n"
            "  inherits = []");
}

TEST(language_forge_parsers, declaration_namespace_minimal) {
  lt::Source source("--", lt::LineIndexedUnicodeString("namespace n {}"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_namespace]\n"
            "  name = \"n\"\n"
            "  members = []");
}

TEST(language_forge_parsers, declaration_namespace_with_member) {
  lt::Source source("--",
                    lt::LineIndexedUnicodeString("namespace n { let x; }"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<BaseDeclaration> tree = parse_declaration(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[declaration_namespace]\n"
            "  name = \"n\"\n"
            "  members = \n"
            "    [0] = [declaration_variable]\n"
            "      name = \"x\"\n"
            "      type = null\n"
            "      initial_value = null\n"
            "      is_const = false");
}

TEST(language_forge_parsers, translation_unit_empty) {
  lt::Source source("--", lt::LineIndexedUnicodeString(""));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<TranslationUnit> tree =
      parse_translation_unit(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[translation_unit]\n"
            "  declarations = []");
}

TEST(language_forge_parsers, translation_unit_with_2_members) {
  lt::Source source("--", lt::LineIndexedUnicodeString("let x; let y;"));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  lt::ParsingContext parsing_context(message_context, tokens);

  std::shared_ptr<TranslationUnit> tree =
      parse_translation_unit(parsing_context);

  std::stringstream stream;
  lt::DebugFormatter formatter(stream);
  tree->format_debug(formatter);

  ASSERT_EQ(stream.str(),
            "[translation_unit]\n"
            "  declarations = \n"
            "    [0] = [declaration_variable]\n"
            "      name = \"x\"\n"
            "      type = null\n"
            "      initial_value = null\n"
            "      is_const = false\n"
            "    [1] = [declaration_variable]\n"
            "      name = \"y\"\n"
            "      type = null\n"
            "      initial_value = null\n"
            "      is_const = false");
}
