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

#include <forge/reporting/get_sample_lines.hpp>

using namespace forge;

TEST(reporting_get_sample_lines, one_line) {
  LineIndexedUnicodeString source_content(
      "hello, world\n"
      "asdf\n");

  GetSampleLinesResult result = get_sample_lines(source_content, 1, 1);

  ASSERT_EQ(result.lines.size(), 1);
  ASSERT_EQ(result.lines[0].line_number, 1);
  ASSERT_EQ(result.lines[0].text, "hello, world");
  ASSERT_EQ(result.deindented_chars, 0);
}

TEST(reporting_get_sample_lines, two_lines) {
  LineIndexedUnicodeString source_content(
      "hello, world\n"
      "asdf\n");

  GetSampleLinesResult result = get_sample_lines(source_content, 1, 2);

  ASSERT_EQ(result.lines.size(), 2);
  ASSERT_EQ(result.lines[0].line_number, 1);
  ASSERT_EQ(result.lines[0].text, "hello, world");
  ASSERT_EQ(result.lines[1].line_number, 2);
  ASSERT_EQ(result.lines[1].text, "asdf");
  ASSERT_EQ(result.deindented_chars, 0);
}

TEST(reporting_get_sample_lines, dindent_one_line_spaces) {
  LineIndexedUnicodeString source_content(
      "  hello, world\n"
      "asdf\n");

  GetSampleLinesResult result = get_sample_lines(source_content, 1, 1);

  ASSERT_EQ(result.lines.size(), 1);
  ASSERT_EQ(result.lines[0].line_number, 1);
  ASSERT_EQ(result.lines[0].text, "hello, world");
  ASSERT_EQ(result.deindented_chars, 2);
}

TEST(reporting_get_sample_lines, dindent_two_lines_spaces) {
  LineIndexedUnicodeString source_content(
      "  hello, world\n"
      "asdf\n");

  GetSampleLinesResult result = get_sample_lines(source_content, 1, 2);

  ASSERT_EQ(result.lines.size(), 2);
  ASSERT_EQ(result.lines[0].line_number, 1);
  ASSERT_EQ(result.lines[0].text, "  hello, world");
  ASSERT_EQ(result.lines[1].line_number, 2);
  ASSERT_EQ(result.lines[1].text, "asdf");
  ASSERT_EQ(result.deindented_chars, 0);
}

TEST(reporting_get_sample_lines, dindent_one_line_tabs) {
  LineIndexedUnicodeString source_content(
      "\thello, world\n"
      "asdf\n");

  GetSampleLinesResult result = get_sample_lines(source_content, 1, 1);

  ASSERT_EQ(result.lines.size(), 1);
  ASSERT_EQ(result.lines[0].line_number, 1);
  ASSERT_EQ(result.lines[0].text, "hello, world");
  ASSERT_EQ(result.deindented_chars, 1);
}

TEST(reporting_get_sample_lines, dindent_two_lines_tabs) {
  LineIndexedUnicodeString source_content(
      "\thello, world\n"
      "asdf\n");

  GetSampleLinesResult result = get_sample_lines(source_content, 1, 2);

  ASSERT_EQ(result.lines.size(), 2);
  ASSERT_EQ(result.lines[0].line_number, 1);
  ASSERT_EQ(result.lines[0].text, "\thello, world");
  ASSERT_EQ(result.lines[1].line_number, 2);
  ASSERT_EQ(result.lines[1].text, "asdf");
  ASSERT_EQ(result.deindented_chars, 0);
}
