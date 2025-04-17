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

#include <langtools/parsing/reading/line_indexed_unicode_string.hpp>

namespace lt {
struct SampleLine {
  uint32_t line_number;
  std::string text;
};

struct GetSampleLinesResult {
  std::vector<SampleLine> lines;
  uint32_t deindented_chars;
};

/**
 * @brief Extract sample lines from a source file for reporting messages.
 *
 * It will also deindent the lines to make them easier to read.
 *
 * @param source_content The source content to extract lines from.
 * @param line_number_first The first line number to extract.
 * @param line_number_last The last line number to extract.
 */
GetSampleLinesResult get_sample_lines(
    const LineIndexedUnicodeString& source_content, uint32_t line_number_first,
    uint32_t line_number_last);
}  // namespace lt
