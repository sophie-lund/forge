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
#include <forge/parsing/lexing/lexer.hpp>

namespace forge {
Lexer::~Lexer() {}

std::vector<Token> Lexer::lex(MessageContext& message_context,
                              const Source& source) {
  LexerContext context(message_context, source);

  while (context.are_more_grapheme_clusters()) {
    assert(context.current_location().offset.has_value());

    auto before = context.current_location().offset.value();

    onLexOne(context);

    assert(context.current_location().offset.has_value());

    auto after = context.current_location().offset.value();

    assert(before != after && "no characters were consumed by onLexOne");
  }

  return context.take_tokens();
}
}  // namespace forge
