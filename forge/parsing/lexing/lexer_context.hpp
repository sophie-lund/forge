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

#include <forge/parsing/reading/grapheme_cluster_reader.hpp>
#include <forge/parsing/sourcing/domain/source_location.hpp>
#include <optional>
#include <string>

namespace forge {
class LexerContext {
 public:
  LexerContext(const Source& source);

  LexerContext(const LexerContext&) = delete;
  LexerContext(LexerContext&&) = default;
  LexerContext& operator=(const LexerContext&) = delete;
  LexerContext& operator=(LexerContext&&) = default;

  bool are_more_grapheme_clusters() const;

  std::optional<std::u16string_view> peek_next_grapheme_cluster() const;

  std::optional<std::u16string_view> read_next_grapheme_cluster();

  const SourceLocation& current_location() const;

 private:
  SourceLocation _current_location;
  GraphemeClusterReader _grapheme_cluster_reader;
};
}  // namespace forge
