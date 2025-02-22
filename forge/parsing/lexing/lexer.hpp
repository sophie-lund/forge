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

#include <forge/parsing/lexing/lexer_context.hpp>

namespace forge {
class Lexer {
 public:
  Lexer() = default;

  virtual ~Lexer() = 0;

  Lexer(const Lexer&) = delete;
  Lexer(Lexer&&) = delete;
  Lexer& operator=(const Lexer&) = delete;
  Lexer& operator=(Lexer&&) = delete;

  std::vector<Token> lex(MessageContext& message_context, const Source& source);

 protected:
  virtual void onLexOne(LexerContext& context) = 0;
};
}  // namespace forge
