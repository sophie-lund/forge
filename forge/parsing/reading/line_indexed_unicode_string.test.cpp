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

#include <forge/parsing/reading/line_indexed_unicode_string.hpp>

using namespace forge;

TEST(parsing_reading_line_indexed_unicode_string, empty) {
  LineIndexedUnicodeString line_indexed_unicode_string("");

  ASSERT_EQ(line_indexed_unicode_string.value(), "");
  ASSERT_EQ(line_indexed_unicode_string.line_count(), 0);
  ASSERT_FALSE(line_indexed_unicode_string.try_get_line(1).has_value());
}

TEST(parsing_reading_line_indexed_unicode_string, one_line_no_newline) {
  LineIndexedUnicodeString line_indexed_unicode_string("asdf");

  ASSERT_EQ(line_indexed_unicode_string.value(), "asdf");
  ASSERT_EQ(line_indexed_unicode_string.line_count(), 1);
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(1).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(1).value(), u"asdf");
  ASSERT_FALSE(line_indexed_unicode_string.try_get_line(2).has_value());
}

TEST(parsing_reading_line_indexed_unicode_string, one_line_with_newline) {
  LineIndexedUnicodeString line_indexed_unicode_string("asdf\n");

  ASSERT_EQ(line_indexed_unicode_string.value(), "asdf\n");
  ASSERT_EQ(line_indexed_unicode_string.line_count(), 2);
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(1).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(1).value(), u"asdf");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(2).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(2).value(), u"");
  ASSERT_FALSE(line_indexed_unicode_string.try_get_line(3).has_value());
}

TEST(parsing_reading_line_indexed_unicode_string, many_lines) {
  LineIndexedUnicodeString line_indexed_unicode_string(
      "asdf\nlfsjh\n\nsdkjfh\n\nsdf");

  ASSERT_EQ(line_indexed_unicode_string.value(),
            "asdf\nlfsjh\n\nsdkjfh\n\nsdf");
  ASSERT_EQ(line_indexed_unicode_string.line_count(), 6);
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(1).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(1).value(), u"asdf");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(2).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(2).value(), u"lfsjh");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(3).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(3).value(), u"");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(4).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(4).value(), u"sdkjfh");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(5).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(5).value(), u"");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(6).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(6).value(), u"sdf");
  ASSERT_FALSE(line_indexed_unicode_string.try_get_line(7).has_value());
}

TEST(parsing_reading_line_indexed_unicode_string, real_world_example_0) {
  LineIndexedUnicodeString line_indexed_unicode_string(R"(
      
    i32 f() {
      return 0;
    }
  
  )");

  ASSERT_EQ(line_indexed_unicode_string.value(),
            R"(
      
    i32 f() {
      return 0;
    }
  
  )");

  ASSERT_EQ(line_indexed_unicode_string.line_count(), 7);
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(1).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(1).value(), u"");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(2).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(2).value(), u"      ");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(3).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(3).value(),
            u"    i32 f() {");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(4).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(4).value(),
            u"      return 0;");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(5).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(5).value(), u"    }");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(6).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(6).value(), u"  ");
  ASSERT_TRUE(line_indexed_unicode_string.try_get_line(7).has_value());
  ASSERT_EQ(line_indexed_unicode_string.try_get_line(7).value(), u"  ");
}