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

TEST(LineIndexedString, Empty) {
  LineIndexedString lineIndexedString("");

  ASSERT_EQ(lineIndexedString.value(), "");
  ASSERT_EQ(lineIndexedString.lineCount(), 0);
  ASSERT_EQ(lineIndexedString.tryGetLine(1).second, false);
}

TEST(LineIndexedString, OneLine_NoNewline) {
  LineIndexedString lineIndexedString("asdf");

  ASSERT_EQ(lineIndexedString.value(), "asdf");
  ASSERT_EQ(lineIndexedString.lineCount(), 1);
  ASSERT_EQ(lineIndexedString.tryGetLine(1).first, "asdf");
  ASSERT_EQ(lineIndexedString.tryGetLine(1).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(2).second, false);
}

TEST(LineIndexedString, OneLine_WithNewline) {
  LineIndexedString lineIndexedString("asdf\n");

  ASSERT_EQ(lineIndexedString.value(), "asdf\n");
  ASSERT_EQ(lineIndexedString.lineCount(), 2);
  ASSERT_EQ(lineIndexedString.tryGetLine(1).first, "asdf");
  ASSERT_EQ(lineIndexedString.tryGetLine(1).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(2).first, "");
  ASSERT_EQ(lineIndexedString.tryGetLine(2).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(3).second, false);
}

TEST(LineIndexedString, ManyLines) {
  LineIndexedString lineIndexedString("asdf\nlfsjh\n\nsdkjfh\n\nsdf");

  ASSERT_EQ(lineIndexedString.value(), "asdf\nlfsjh\n\nsdkjfh\n\nsdf");
  ASSERT_EQ(lineIndexedString.lineCount(), 6);
  ASSERT_EQ(lineIndexedString.tryGetLine(1).first, "asdf");
  ASSERT_EQ(lineIndexedString.tryGetLine(1).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(2).first, "lfsjh");
  ASSERT_EQ(lineIndexedString.tryGetLine(2).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(3).first, "");
  ASSERT_EQ(lineIndexedString.tryGetLine(3).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(4).first, "sdkjfh");
  ASSERT_EQ(lineIndexedString.tryGetLine(4).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(5).first, "");
  ASSERT_EQ(lineIndexedString.tryGetLine(5).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(6).first, "sdf");
  ASSERT_EQ(lineIndexedString.tryGetLine(6).second, true);
  ASSERT_EQ(lineIndexedString.tryGetLine(7).second, false);
}
