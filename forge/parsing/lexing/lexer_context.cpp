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
#include <forge/parsing/lexing/lexer_context.hpp>

namespace forge {
LexerContext::LexerContext(const Source& source)
    : _current_location(source, 1, 1, 0),
      _grapheme_cluster_reader(source.content().value()) {}

bool LexerContext::are_more_grapheme_clusters() const {
  return _grapheme_cluster_reader.are_more();
}

std::optional<std::u16string_view> LexerContext::peek_next_grapheme_cluster()
    const {
  return _grapheme_cluster_reader.peek_next();
}

std::optional<std::u16string_view> LexerContext::read_next_grapheme_cluster() {
  assert(_current_location.source() != nullptr);
  assert(_current_location.line().has_value());
  assert(_current_location.column().has_value());
  assert(_current_location.offset().has_value());

  auto result = _grapheme_cluster_reader.read_next();

  if (!result.has_value()) {
    return result;
  }

  if (result.value() == u"\n") {
    _current_location = SourceLocation(*_current_location.source(),
                                       _current_location.line().value() + 1, 1,
                                       _grapheme_cluster_reader.offset());
  } else {
    _current_location = SourceLocation(*_current_location.source(),
                                       _current_location.line().value(),
                                       _current_location.column().value() + 1,
                                       _grapheme_cluster_reader.offset());
  }

  return result;
}

const SourceLocation& LexerContext::current_location() const {
  return _current_location;
}
}  // namespace forge
