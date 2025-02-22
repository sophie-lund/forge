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
#include <unicode/uclean.h>
#include <unicode/utypes.h>

#include <forge/core/init.hpp>
#include <forge/parsing/reading/grapheme_cluster_reader.hpp>

using namespace forge;

TEST(parsing_reading_grapheme_cluster_reader, empty) {
  icu::UnicodeString content = "";

  GraphemeClusterReader reader(content);

  ASSERT_FALSE(reader.are_more());
  ASSERT_FALSE(reader.peek_next().has_value());
  ASSERT_FALSE(reader.read_next().has_value());
}

TEST(parsing_reading_grapheme_cluster_reader, ascii_only) {
  icu::UnicodeString content = "asdf";

  GraphemeClusterReader reader(content);

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"a");
  ASSERT_EQ(reader.read_next().value(), u"a");

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"s");
  ASSERT_EQ(reader.read_next().value(), u"s");

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"d");
  ASSERT_EQ(reader.read_next().value(), u"d");

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"f");
  ASSERT_EQ(reader.read_next().value(), u"f");

  ASSERT_FALSE(reader.are_more());
  ASSERT_FALSE(reader.peek_next().has_value());
  ASSERT_FALSE(reader.read_next().has_value());
}

// This is fucking awful lol lol
TEST(parsing_reading_grapheme_cluster_reader, multiple_codepoint_clusters) {
  icu::UnicodeString content = "ax̧̡̬̘͓̖̲̻̻̲̠̪̻͓͙̜̂̓̊̔̀̀͗̑̀̅̀̂̚͘̕̚͘͢͜͠b";

  GraphemeClusterReader reader(content);

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"a");
  ASSERT_EQ(reader.read_next().value(), u"a");

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"x̧̡̬̘͓̖̲̻̻̲̠̪̻͓͙̜̂̓̊̔̀̀͗̑̀̅̀̂̚͘̕̚͘͢͜͠");
  ASSERT_EQ(reader.read_next().value(), u"x̧̡̬̘͓̖̲̻̻̲̠̪̻͓͙̜̂̓̊̔̀̀͗̑̀̅̀̂̚͘̕̚͘͢͜͠");

  ASSERT_TRUE(reader.are_more());
  ASSERT_TRUE(reader.peek_next().has_value());
  ASSERT_EQ(reader.peek_next().value(), u"b");
  ASSERT_EQ(reader.read_next().value(), u"b");

  ASSERT_FALSE(reader.are_more());
  ASSERT_FALSE(reader.peek_next().has_value());
  ASSERT_FALSE(reader.read_next().has_value());
}
