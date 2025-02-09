// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace sycamore::parsing {
/**
 * @brief A string that is indexed by line for fast access.
 */
class LineIndexedString {
 public:
  /**
   * @note This constructor will index the lines in the string and may be slow
   *       if the string is very large.
   */
  explicit LineIndexedString(std::string&& value);

  LineIndexedString(const LineIndexedString& other) = delete;
  LineIndexedString(LineIndexedString&& other) = default;
  LineIndexedString& operator=(const LineIndexedString& other) = delete;
  LineIndexedString& operator=(LineIndexedString&& other) = default;

  /**
   * @brief Get the unindexed value of the string.
   */
  const std::string& value() const;

  /**
   * @brief Get the number of lines in the string.
   *
   * If the string is empty this will return @c 0. If there is not a single
   * newline present in the string this will return @c 1.
   */
  size_t lineCount() const;

  /**
   * @brief Try to get a line from the string.
   *
   * @param line The number of the line to get, starting at 1.
   *
   * @return A pair where the first element is the line and the second element
   *         is @c true if the line was found, otherwise @c false.
   */
  std::pair<std::string_view, bool> tryGetLine(size_t line) const;

 private:
  std::string value_;
  std::vector<size_t> lineIndices_;
};
}  // namespace sycamore::parsing
