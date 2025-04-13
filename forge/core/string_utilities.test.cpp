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

using namespace forge;

TEST(core_string_utilities, trim) {
  ASSERT_EQ(trim(""), "");
  ASSERT_EQ(trim(" "), "");
  ASSERT_EQ(trim("\t"), "");
  ASSERT_EQ(trim("\n"), "");
  ASSERT_EQ(trim("a"), "a");
  ASSERT_EQ(trim(" a"), "a");
  ASSERT_EQ(trim("\ta"), "a");
  ASSERT_EQ(trim("\na"), "a");
  ASSERT_EQ(trim("a "), "a");
  ASSERT_EQ(trim("a\t"), "a");
  ASSERT_EQ(trim("a\n"), "a");
  ASSERT_EQ(trim(" \t\na \t\n"), "a");
  ASSERT_EQ(trim("a b"), "a b");
  ASSERT_EQ(trim("a\tb"), "a\tb");
  ASSERT_EQ(trim("a\nb"), "a\nb");
  ASSERT_EQ(trim(" \t\na b\n\t "), "a b");
}

TEST(core_string_utilities, count_whitespace_chars_at_start) {
  ASSERT_EQ(count_whitespace_chars_at_start(""), 0);
  ASSERT_EQ(count_whitespace_chars_at_start(" "), 1);
  ASSERT_EQ(count_whitespace_chars_at_start("\t"), 1);
  ASSERT_EQ(count_whitespace_chars_at_start("a"), 0);
  ASSERT_EQ(count_whitespace_chars_at_start(" a"), 1);
  ASSERT_EQ(count_whitespace_chars_at_start("\ta"), 1);
  ASSERT_EQ(count_whitespace_chars_at_start("a "), 0);
  ASSERT_EQ(count_whitespace_chars_at_start("a\t"), 0);
  ASSERT_EQ(count_whitespace_chars_at_start("a\n"), 0);
}
