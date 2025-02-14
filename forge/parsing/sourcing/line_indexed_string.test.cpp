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

#include <forge/parsing/sourcing/line_indexed_string.hpp>

using namespace forge;

TEST(parsing_sourcing_line_indexed_string, empty) {
  LineIndexedString line_indexed_string("");

  ASSERT_EQ(line_indexed_string.value(), "");
  ASSERT_EQ(line_indexed_string.line_count(), 0);
  ASSERT_EQ(line_indexed_string.try_get_line(1).second, false);
}

TEST(parsing_sourcing_line_indexed_string, one_line_no_newline) {
  LineIndexedString line_indexed_string("asdf");

  ASSERT_EQ(line_indexed_string.value(), "asdf");
  ASSERT_EQ(line_indexed_string.line_count(), 1);
  ASSERT_EQ(line_indexed_string.try_get_line(1).first, "asdf");
  ASSERT_EQ(line_indexed_string.try_get_line(1).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(2).second, false);
}

TEST(parsing_sourcing_line_indexed_string, one_line_with_newline) {
  LineIndexedString line_indexed_string("asdf\n");

  ASSERT_EQ(line_indexed_string.value(), "asdf\n");
  ASSERT_EQ(line_indexed_string.line_count(), 2);
  ASSERT_EQ(line_indexed_string.try_get_line(1).first, "asdf");
  ASSERT_EQ(line_indexed_string.try_get_line(1).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(2).first, "");
  ASSERT_EQ(line_indexed_string.try_get_line(2).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(3).second, false);
}

TEST(parsing_sourcing_line_indexed_string, many_lines) {
  LineIndexedString line_indexed_string("asdf\nlfsjh\n\nsdkjfh\n\nsdf");

  ASSERT_EQ(line_indexed_string.value(), "asdf\nlfsjh\n\nsdkjfh\n\nsdf");
  ASSERT_EQ(line_indexed_string.line_count(), 6);
  ASSERT_EQ(line_indexed_string.try_get_line(1).first, "asdf");
  ASSERT_EQ(line_indexed_string.try_get_line(1).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(2).first, "lfsjh");
  ASSERT_EQ(line_indexed_string.try_get_line(2).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(3).first, "");
  ASSERT_EQ(line_indexed_string.try_get_line(3).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(4).first, "sdkjfh");
  ASSERT_EQ(line_indexed_string.try_get_line(4).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(5).first, "");
  ASSERT_EQ(line_indexed_string.try_get_line(5).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(6).first, "sdf");
  ASSERT_EQ(line_indexed_string.try_get_line(6).second, true);
  ASSERT_EQ(line_indexed_string.try_get_line(7).second, false);
}
