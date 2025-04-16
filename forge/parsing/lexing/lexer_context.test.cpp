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

#include <forge/language/parsing/forge_token_kind.hpp>
#include <forge/parsing/lexing/lexer_context.hpp>

using namespace forge;

TEST(parsing_lexing_lexer_context, empty) {
  Source source("test.frg", LineIndexedUnicodeString(""));

  MessageContext message_context;
  LexerContext lexer_context(message_context, source);

  ASSERT_FALSE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_value(), u"");
  lexer_context.skip_token();

  std::vector<Token> tokens = std::move(lexer_context).take_tokens();

  ASSERT_EQ(tokens.size(), 0);
}

TEST(parsing_lexing_lexer_context, nonempty) {
  Source source("test.frg", LineIndexedUnicodeString("hello, world"));

  MessageContext message_context;
  LexerContext lexer_context(message_context, source);

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_value(), u"");

  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"h");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"h");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"e");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"e");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"l");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"l");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"l");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"l");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"o");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"o");

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(lexer_context.current_value(), u"hello");

  lexer_context.emit_token(TOKEN_SYMBOL);

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(lexer_context.current_value(), u"");

  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u",");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u",");

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(lexer_context.current_value(), u",");

  lexer_context.emit_token(TOKEN_COMMA);

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(lexer_context.current_value(), u"");

  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u" ");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u" ");

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(lexer_context.current_value(), u" ");

  lexer_context.skip_token();

  ASSERT_EQ(lexer_context.current_location(), SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(lexer_context.current_range().end, SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(lexer_context.current_value(), u"");

  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"w");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"w");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"o");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"o");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"r");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"r");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"l");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"l");
  ASSERT_TRUE(lexer_context.are_more_grapheme_clusters());
  ASSERT_EQ(lexer_context.peek_next_grapheme_cluster(), u"d");
  ASSERT_EQ(lexer_context.read_next_grapheme_cluster(), u"d");

  ASSERT_FALSE(lexer_context.are_more_grapheme_clusters());

  ASSERT_EQ(lexer_context.current_location(),
            SourceLocation(source, 1, 13, 12));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(lexer_context.current_range().end,
            SourceLocation(source, 1, 13, 12));
  ASSERT_EQ(lexer_context.current_value(), u"world");

  lexer_context.emit_token(TOKEN_SYMBOL);

  ASSERT_EQ(lexer_context.current_location(),
            SourceLocation(source, 1, 13, 12));
  ASSERT_EQ(lexer_context.current_range().start,
            SourceLocation(source, 1, 13, 12));
  ASSERT_EQ(lexer_context.current_range().end,
            SourceLocation(source, 1, 13, 12));
  ASSERT_EQ(lexer_context.current_value(), u"");

  std::vector<Token> tokens = std::move(lexer_context).take_tokens();

  ASSERT_EQ(tokens.size(), 3);
  ASSERT_EQ(tokens[0].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[0].source_range.start, SourceLocation(source, 1, 1, 0));
  ASSERT_EQ(tokens[0].source_range.end.value(),
            SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(tokens[0].value, u"hello");
  ASSERT_EQ(tokens[1].kind, TOKEN_COMMA);
  ASSERT_EQ(tokens[1].source_range.start, SourceLocation(source, 1, 6, 5));
  ASSERT_EQ(tokens[1].source_range.end.value(),
            SourceLocation(source, 1, 7, 6));
  ASSERT_EQ(tokens[1].value, u",");
  ASSERT_EQ(tokens[2].kind, TOKEN_SYMBOL);
  ASSERT_EQ(tokens[2].source_range.start, SourceLocation(source, 1, 8, 7));
  ASSERT_EQ(tokens[2].source_range.end.value(),
            SourceLocation(source, 1, 13, 12));
  ASSERT_EQ(tokens[2].value, u"world");
}
