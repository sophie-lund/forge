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

#include <langtools/parsing/lexing/lexer_context.hpp>

namespace lt {
/**
 * @brief A base class for lexers.
 */
class BaseLexer {
 public:
  BaseLexer() = default;

  virtual ~BaseLexer() = 0;

  BaseLexer(const BaseLexer&) = delete;
  BaseLexer(BaseLexer&&) = delete;
  BaseLexer& operator=(const BaseLexer&) = delete;
  BaseLexer& operator=(BaseLexer&&) = delete;

  /**
   * @brief Lex the source code.
   */
  std::vector<Token> lex(MessageContext& message_context, const Source& source);

 protected:
  /**
   * @brief Lex one token from the source code.
   */
  virtual void onLexOne(LexerContext& context) = 0;
};
}  // namespace lt
