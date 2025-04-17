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

#include <langtools/parsing/syntax_parsing/parsing_context.hpp>

using namespace lt;

namespace {
const TokenKind TOKEN_SYMBOL = TokenKind("'symbol'");
const TokenKind TOKEN_COMMA = TokenKind(",");
}  // namespace

TEST(parsing_syntax_parsing_parsing_context, empty) {
  Source source("test.frg", LineIndexedUnicodeString(""));

  std::vector<Token> tokens;

  MessageContext message_context;
  ParsingContext parsing_context(message_context, tokens);

  ASSERT_FALSE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.save_cursor(), 0);
}

TEST(parsing_syntax_parsing_parsing_context, nonempty) {
  Source source("test.frg", LineIndexedUnicodeString(""));

  std::vector<Token> tokens = {
      Token(TOKEN_SYMBOL, SourceRange(), u"hello"),
      Token(TOKEN_COMMA, SourceRange(), u","),
      Token(TOKEN_SYMBOL, SourceRange(), u"world"),
  };

  MessageContext message_context;
  ParsingContext parsing_context(message_context, tokens);

  ASSERT_TRUE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.peek_next_token().kind, TOKEN_SYMBOL);
  ASSERT_EQ(parsing_context.peek_next_token().value, u"hello");
  ASSERT_EQ(parsing_context.save_cursor(), 0);
  ASSERT_EQ(parsing_context.read_next_token().value, u"hello");
  ASSERT_EQ(parsing_context.save_cursor(), 1);

  ASSERT_TRUE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.peek_next_token().kind, TOKEN_COMMA);
  ASSERT_EQ(parsing_context.peek_next_token().value, u",");
  ASSERT_EQ(parsing_context.save_cursor(), 1);
  ASSERT_EQ(parsing_context.read_next_token().value, u",");
  ASSERT_EQ(parsing_context.save_cursor(), 2);

  ASSERT_TRUE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.peek_next_token().kind, TOKEN_SYMBOL);
  ASSERT_EQ(parsing_context.peek_next_token().value, u"world");
  ASSERT_EQ(parsing_context.save_cursor(), 2);
  ASSERT_EQ(parsing_context.read_next_token().value, u"world");
  ASSERT_EQ(parsing_context.save_cursor(), 3);

  ASSERT_FALSE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.save_cursor(), 3);

  parsing_context.restore_cursor(1);

  ASSERT_TRUE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.peek_next_token().kind, TOKEN_COMMA);
  ASSERT_EQ(parsing_context.peek_next_token().value, u",");
  ASSERT_EQ(parsing_context.save_cursor(), 1);
  ASSERT_EQ(parsing_context.read_next_token().value, u",");
  ASSERT_EQ(parsing_context.save_cursor(), 2);

  ASSERT_TRUE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.peek_next_token().kind, TOKEN_SYMBOL);
  ASSERT_EQ(parsing_context.peek_next_token().value, u"world");
  ASSERT_EQ(parsing_context.save_cursor(), 2);
  ASSERT_EQ(parsing_context.read_next_token().value, u"world");
  ASSERT_EQ(parsing_context.save_cursor(), 3);

  ASSERT_FALSE(parsing_context.are_more_tokens());
  ASSERT_EQ(parsing_context.save_cursor(), 3);
}
