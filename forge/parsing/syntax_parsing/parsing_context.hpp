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
#include <forge/parsing/domain/token.hpp>
#include <vector>

namespace forge {
/**
 * @brief A context that can be passed to functions that parse syntax.
 */
class ParsingContext {
 public:
  ParsingContext(MessageContext& message_context,
                 const std::vector<Token>& tokens);

  ParsingContext(const ParsingContext&) = delete;
  ParsingContext(ParsingContext&&) = delete;
  ParsingContext& operator=(const ParsingContext&) = delete;
  ParsingContext& operator=(ParsingContext&&) = delete;

  /**
   * @brief Get the message context.
   */
  MessageContext& message_context();

  /**
   * @brief Returns @c true if there are more tokens to be read.
   */
  bool are_more_tokens() const;

  /**
   * @brief Peek at the next token without consuming it.
   */
  const Token& peek_next_token() const;

  /**
   * @brief Read the next token and consume it.
   */
  const Token& read_next_token();

  /**
   * @brief Save the current cursor position in the token vector.
   */
  int32_t save_cursor() const;

  /**
   * @brief Restore the cursor position in the token vector.
   *
   * This causes a backtrack.
   */
  void restore_cursor(int32_t value);

 private:
  std::reference_wrapper<MessageContext> _message_context;
  std::reference_wrapper<const std::vector<Token>> _tokens;
  int32_t _cursor;
};
}  // namespace forge
