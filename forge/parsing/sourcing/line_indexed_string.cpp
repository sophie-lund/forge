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

#include <cassert>
#include <forge/parsing/sourcing/line_indexed_string.hpp>

namespace forge {
LineIndexedString::LineIndexedString(std::string&& value)
    : value_(std::move(value)) {
  if (!value_.empty()) {
    lineIndices_.push_back(0);
  }

  for (size_t i = 1; i < value_.size(); i++) {
    if (value_[i] == '\n') {
      lineIndices_.push_back(i + 1);
    }
  }
}

const std::string& LineIndexedString::value() const { return value_; }

size_t LineIndexedString::lineCount() const { return lineIndices_.size(); }

std::pair<std::string_view, bool> LineIndexedString::tryGetLine(
    size_t line) const {
  assert(line > 0 && "line number must be greater than 0");

  auto index = line - 1;

  if (index >= lineIndices_.size()) {
    return {std::string_view(), false};
  }

  size_t begin = lineIndices_[index];
  size_t end = index + 1 < lineIndices_.size() ? lineIndices_[index + 1] - 1
                                               : value_.size();

  return {std::string_view(value_).substr(begin, end - begin), true};
}
}  // namespace forge
