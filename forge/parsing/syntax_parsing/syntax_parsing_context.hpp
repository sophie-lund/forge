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
class SyntaxParsingContext {
 public:
  SyntaxParsingContext(MessageContext& message_context,
                       const std::vector<Token>& tokens);

  SyntaxParsingContext(const SyntaxParsingContext&) = delete;
  SyntaxParsingContext(SyntaxParsingContext&&) = delete;
  SyntaxParsingContext& operator=(const SyntaxParsingContext&) = delete;
  SyntaxParsingContext& operator=(SyntaxParsingContext&&) = delete;

  /**
   * @brief Get the message context.
   */
  MessageContext& message_context();

  bool are_more_tokens() const;

  const Token& peek_next_token() const;
  const Token& read_next_token();

  int32_t save_cursor() const;
  void restore_cursor(int32_t value);

 private:
  std::reference_wrapper<MessageContext> _message_context;
  std::reference_wrapper<const std::vector<Token>> _tokens;
  int32_t _cursor;
};
}  // namespace forge
