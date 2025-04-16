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

#include <forge/parsing/domain/source_location.hpp>

using namespace forge;

TEST(parsing_domain_source_location, empty) {
  SourceLocation location;

  ASSERT_FALSE(location);

  std::stringstream stream;
  stream << location;

  ASSERT_EQ(stream.str(), "--");
}

TEST(parsing_domain_source_location, with_source_only) {
  Source source("test.frg", LineIndexedUnicodeString(""));
  SourceLocation location(source);

  ASSERT_TRUE(location);

  std::stringstream stream;
  stream << location;

  ASSERT_EQ(stream.str(), "test.frg");
}

TEST(parsing_domain_source_location, with_source_line_only) {
  Source source("test.frg", LineIndexedUnicodeString(""));
  SourceLocation location(source, 2);

  ASSERT_TRUE(location);

  std::stringstream stream;
  stream << location;

  ASSERT_EQ(stream.str(), "test.frg:2");
}

TEST(parsing_domain_source_location, without_offset) {
  Source source("test.frg", LineIndexedUnicodeString(""));
  SourceLocation location(source, 2, 3);

  ASSERT_TRUE(location);

  std::stringstream stream;
  stream << location;

  ASSERT_EQ(stream.str(), "test.frg:2:3");
}

TEST(parsing_domain_source_location, full) {
  Source source("test.frg", LineIndexedUnicodeString(""));
  SourceLocation location(source, 2, 3, 4);

  ASSERT_TRUE(location);

  std::stringstream stream;
  stream << location;

  ASSERT_EQ(stream.str(), "test.frg:2:3");
}

TEST(parsing_domain_source_location, equal_and_not_equal) {
  Source source0("test.frg", LineIndexedUnicodeString(""));
  Source source1("test.frg", LineIndexedUnicodeString(""));

  ASSERT_EQ(SourceLocation(), SourceLocation());
  ASSERT_NE(SourceLocation(), SourceLocation(source0));
  ASSERT_NE(SourceLocation(source0), SourceLocation());
  ASSERT_NE(SourceLocation(source0), SourceLocation(source1));
  ASSERT_EQ(SourceLocation(source0), SourceLocation(source0));
  ASSERT_EQ(SourceLocation(source0, 2, 3, 4), SourceLocation(source0, 2, 3, 4));
  ASSERT_NE(SourceLocation(source0, 2, 3, 4), SourceLocation(source0, 2, 3, 5));
  ASSERT_EQ(SourceLocation(source0, 2, 3, 4), SourceLocation(source0, 2, 5, 4));
  ASSERT_EQ(SourceLocation(source0, 2, 3, 4), SourceLocation(source0, 5, 3, 4));
}

TEST(parsing_domain_source_location, less_than) {
  Source source0("test.frg", LineIndexedUnicodeString(""));
  Source source1("test.frg", LineIndexedUnicodeString(""));

  ASSERT_FALSE(SourceLocation() < SourceLocation());
  ASSERT_TRUE(SourceLocation() < SourceLocation(source0));
  ASSERT_FALSE(SourceLocation(source0) < SourceLocation());
  ASSERT_FALSE(SourceLocation(source0) < SourceLocation(source1));
  ASSERT_FALSE(SourceLocation(source0) < SourceLocation(source0));
  ASSERT_FALSE(SourceLocation(source0, 2, 3, 4) <
               SourceLocation(source0, 2, 3, 4));
  ASSERT_TRUE(SourceLocation(source0, 2, 3, 4) <
              SourceLocation(source0, 2, 3, 5));
  ASSERT_FALSE(SourceLocation(source0, 2, 3, 4) <
               SourceLocation(source0, 2, 5, 4));
  ASSERT_FALSE(SourceLocation(source0, 2, 3, 4) <
               SourceLocation(source0, 5, 3, 4));
}
