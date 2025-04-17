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

#pragma once

#include <unicode/unistr.h>

#include <optional>
#include <vector>

namespace lt {
/**
 * @brief A string that is indexed by line for fast access.
 */
class LineIndexedUnicodeString {
 public:
  /**
   * @note This constructor will index the lines in the string and may be slow
   *       if the string is very large.
   */
  explicit LineIndexedUnicodeString(icu::UnicodeString&& value);

  LineIndexedUnicodeString(const LineIndexedUnicodeString& other) = delete;
  LineIndexedUnicodeString(LineIndexedUnicodeString&& other) = default;
  LineIndexedUnicodeString& operator=(const LineIndexedUnicodeString& other) =
      delete;
  LineIndexedUnicodeString& operator=(LineIndexedUnicodeString&& other) =
      default;

  /**
   * @brief Get the unindexed value of the string.
   */
  const icu::UnicodeString& value() const;

  /**
   * @brief Get the number of lines in the string.
   *
   * If the string is empty this will return @c 0. If there is not a single
   * newline present in the string this will return @c 1.
   */
  size_t line_count() const;

  /**
   * @brief Try to get a line from the string.
   *
   * @param line The number of the line to get, starting at 1.
   *
   * @return A pair where the first element is the line and the second element
   *         is @c true if the line was found, otherwise @c false.
   */
  std::optional<std::u16string_view> try_get_line(size_t line) const;

 private:
  icu::UnicodeString value_;
  std::vector<int32_t> line_indices_;
};
}  // namespace lt
