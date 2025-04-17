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

#include <langtools/parsing/domain/source_range.hpp>

using namespace lt;

TEST(parsing_domain_source_range, empty) {
  SourceRange range;

  ASSERT_FALSE(range);
}

TEST(parsing_domain_source_range, non_empty) {
  Source source("test.frg", LineIndexedUnicodeString(""));

  auto range = SourceRange(SourceLocation(source));

  ASSERT_TRUE(range);
}

TEST(parsing_domain_source_range, combine_source_ranges) {
  Source source("test.frg", LineIndexedUnicodeString(""));

  auto range0 = SourceRange(SourceLocation(source, 2, 3, 4),
                            SourceLocation(source, 5, 6, 7));
  auto range1 = SourceRange(SourceLocation(source, 3, 4, 5),
                            SourceLocation(source, 6, 7, 8));

  SourceRange result0 = combine_source_ranges(range0, range1);
  SourceRange result1 = combine_source_ranges(range1, range0);

  ASSERT_EQ(result0.start, SourceLocation(source, 2, 3, 4));
  ASSERT_EQ(result0.end, SourceLocation(source, 6, 7, 8));
  ASSERT_EQ(result1.start, SourceLocation(source, 2, 3, 4));
  ASSERT_EQ(result1.end, SourceLocation(source, 6, 7, 8));
}
