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
#include <forge/core/unicode.hpp>
#include <forge/parsing/reading/grapheme_cluster_reader.hpp>

namespace forge {
GraphemeClusterReader::GraphemeClusterReader(const icu::UnicodeString& content)
    : _content(std::cref(content)), _current_offset(0) {
  UErrorCode status = U_ZERO_ERROR;
  icu::Locale locale = detect_parsing_locale();

  _break_iterator = std::unique_ptr<icu::BreakIterator>(
      icu::BreakIterator::createCharacterInstance(locale, status));

  FRG_ASSERT(!U_FAILURE(status), "failed to create break iterator");

  _break_iterator->setText(content);
  _break_iterator->first();
}

bool GraphemeClusterReader::are_more() const {
  FRG_ASSERT(_current_offset >= 0, "current offset must not be negative");

  return _current_offset < _content.get().length();
}

std::u16string_view GraphemeClusterReader::peek_next() const {
  FRG_ASSERT(_current_offset >= 0, "current offset must not be negative");

  int32_t original_current_offset = _current_offset;

  auto result = const_cast<GraphemeClusterReader*>(this)->read_next();

  const_cast<GraphemeClusterReader*>(this)->_current_offset =
      original_current_offset;

  return result;
}

std::u16string_view GraphemeClusterReader::read_next() {
  FRG_ASSERT(are_more(), "there are no more grapheme clusters to read");

  int32_t end = _break_iterator->following(_current_offset);

  FRG_ASSERT(end >= 0, "end offset must not be negative");
  FRG_ASSERT(end >= _current_offset,
             "end offset must not come before current offset");

  auto result = std::u16string_view(
      _content.get().getBuffer() + _current_offset, end - _current_offset);

  _current_offset = end;

  return result;
}

size_t GraphemeClusterReader::current_offset() const {
  FRG_ASSERT(_current_offset >= 0, "current offset must not be negative");

  return _current_offset;
}
}  // namespace forge
