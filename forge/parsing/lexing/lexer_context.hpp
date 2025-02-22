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

#include <forge/messaging/message_context.hpp>
#include <forge/parsing/domain/source_location.hpp>
#include <forge/parsing/domain/token.hpp>
#include <forge/parsing/domain/token_kind.hpp>
#include <forge/parsing/reading/grapheme_cluster_reader.hpp>
#include <string>

namespace forge {
class LexerContext {
 public:
  LexerContext(MessageContext& message_context, const Source& source);

  LexerContext(const LexerContext&) = delete;
  LexerContext(LexerContext&&) = delete;
  LexerContext& operator=(const LexerContext&) = delete;
  LexerContext& operator=(LexerContext&&) = delete;

  /**
   * @brief Get the message context.
   */
  MessageContext& message_context();

  bool are_more_grapheme_clusters() const;

  std::u16string_view peek_next_grapheme_cluster() const;

  std::u16string_view read_next_grapheme_cluster();

  const SourceLocation& current_location() const;
  SourceRange current_range() const;
  std::u16string_view current_value() const;

  void emit_token(const TokenKind& kind);
  void skip_token();

  std::vector<Token> take_tokens();

 private:
  std::reference_wrapper<MessageContext> _message_context;
  SourceLocation _current_location;
  GraphemeClusterReader _grapheme_cluster_reader;
  SourceLocation _token_start_location;
  std::vector<Token> _tokens;
};
}  // namespace forge
