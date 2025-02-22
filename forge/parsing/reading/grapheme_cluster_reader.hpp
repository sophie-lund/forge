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

#include <unicode/brkiter.h>
#include <unicode/unistr.h>

#include <memory>

namespace forge {
class GraphemeClusterReader {
 public:
  GraphemeClusterReader(const icu::UnicodeString& content);

  GraphemeClusterReader(const GraphemeClusterReader&) = delete;
  GraphemeClusterReader(GraphemeClusterReader&&) = delete;
  GraphemeClusterReader& operator=(const GraphemeClusterReader&) = delete;
  GraphemeClusterReader& operator=(GraphemeClusterReader&&) = delete;

  bool are_more() const;

  std::u16string_view peek_next() const;

  std::u16string_view read_next();

  size_t current_offset() const;

 private:
  std::reference_wrapper<const icu::UnicodeString> _content;
  std::unique_ptr<icu::BreakIterator> _break_iterator;
  int32_t _current_offset;
};
}  // namespace forge
