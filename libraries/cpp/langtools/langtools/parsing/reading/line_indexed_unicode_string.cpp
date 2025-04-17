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

#include <langtools/core/assert.hpp>
#include <langtools/parsing/reading/line_indexed_unicode_string.hpp>

namespace lt {
LineIndexedUnicodeString::LineIndexedUnicodeString(icu::UnicodeString&& value)
    : value_(std::move(value)) {
  if (!value_.isEmpty()) {
    line_indices_.push_back(0);
  }

  for (int32_t i = 0; i < value_.length(); i++) {
    if (value_[i] == '\n') {
      line_indices_.push_back(i + 1);
    }
  }
}

const icu::UnicodeString& LineIndexedUnicodeString::value() const {
  return value_;
}

size_t LineIndexedUnicodeString::line_count() const {
  return line_indices_.size();
}

std::optional<std::u16string_view> LineIndexedUnicodeString::try_get_line(
    size_t line) const {
  LT_ASSERT(line > 0, "line number must be positive");

  auto index = line - 1;

  if (index >= line_indices_.size()) {
    return std::nullopt;
  }

  int32_t begin = line_indices_[index];
  int32_t end = index + 1 < line_indices_.size() ? line_indices_[index + 1] - 1
                                                 : value_.length();

  // return std::make_pair(begin, end);
  return std::u16string_view(value_.getBuffer() + begin, end - begin);
}
}  // namespace lt
