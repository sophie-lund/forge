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
/**
 * @brief A context to be used for lexing.
 *
 * Lexing operates on grapheme clusters so that is reflected by this class. If
 * you don't want to look into the unicode standard, just think of grapheme
 * clusters as characters.
 */
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

  /**
   * @brief Returns @c true if there are more grapheme clusters to be read.
   */
  bool are_more_grapheme_clusters() const;

  /**
   * @brief Peek at the next grapheme cluster without consuming it.
   */
  std::u16string_view peek_next_grapheme_cluster() const;

  /**
   * @brief Read the next grapheme cluster and consumes it.
   */
  std::u16string_view read_next_grapheme_cluster();

  /**
   * @brief Get the current location in the source.
   */
  const SourceLocation& current_location() const;

  /**
   * @brief Get the current range of the token being lexed.
   */
  SourceRange current_range() const;

  /**
   * @brief Get the current value of the token being lexed.
   */
  std::u16string_view current_value() const;

  /**
   * @brief Emit a token of what has been read so far since the last call to @c
   * emit_token or @c skip_token.
   */
  void emit_token(const TokenKind& kind);

  /**
   * @brief Discards the grapheme clusters that have been read since the last
   * call to
   * @c emit_token or @c skip_token.
   */
  void skip_token();

  /**
   * @brief Take the tokens that have been emitted so far.
   */
  std::vector<Token> take_tokens() &&;

 private:
  std::reference_wrapper<MessageContext> _message_context;
  SourceLocation _current_location;
  GraphemeClusterReader _grapheme_cluster_reader;
  SourceLocation _token_start_location;
  std::vector<Token> _tokens;
};
}  // namespace forge
