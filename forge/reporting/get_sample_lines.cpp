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

#include <forge/core/assert.hpp>
#include <forge/core/string_utilities.hpp>
#include <forge/core/unicode.hpp>
#include <forge/reporting/get_sample_lines.hpp>

namespace forge {
GetSampleLinesResult get_sample_lines(
    const LineIndexedUnicodeString& source_content, uint32_t line_number_first,
    uint32_t line_number_last) {
  FRG_ASSERT(line_number_first > 0, "line numbers must be positive");
  FRG_ASSERT(line_number_last > 0, "line numbers must be positive");
  FRG_ASSERT(line_number_last >= line_number_first,
             "last line number cannot come before first line number");

  GetSampleLinesResult result = {.deindented_chars = 0};
  uint32_t min_spaces_at_start = UINT32_MAX;

  // For each line number in the range
  for (uint32_t line_number = line_number_first;
       line_number <= line_number_last; line_number++) {
    // Get the line
    std::optional<std::u16string_view> line =
        source_content.try_get_line(line_number);
    if (!line.has_value()) {
      return GetSampleLinesResult{
          .deindented_chars = 0,
      };
    }

    // Convert tabs to spaces
    std::string line_converted = u16string_view_to_string(line.value());

    // Count the number of spaces at the start of the line
    uint32_t spaces_at_start = count_whitespace_chars_at_start(line_converted);

    // Update the minimum number of spaces at the start of any line
    if (spaces_at_start < min_spaces_at_start) {
      min_spaces_at_start = spaces_at_start;
    }

    result.lines.emplace_back(line_number, line_converted);
  }

  // Deindent the lines
  if (min_spaces_at_start != UINT32_MAX) {
    for (SampleLine& line : result.lines) {
      line.text = line.text.substr(min_spaces_at_start);
    }

    result.deindented_chars = min_spaces_at_start;
  }

  // Return the results
  return result;
}
}  // namespace forge
