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

#include <langtools/core/assert.hpp>
#include <langtools/parsing/lexing/base_lexer.hpp>

namespace lt {
BaseLexer::~BaseLexer() {}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
std::vector<Token> BaseLexer::lex(MessageContext& message_context,
                                  const Source& source) {
  LexerContext context(message_context, source);

  while (context.are_more_grapheme_clusters()) {
    LT_ASSERT(context.current_location().offset.has_value(),
              "current location offset must not be null");

    auto before = context.current_location().offset.value();

    onLexOne(context);

    LT_ASSERT(context.current_location().offset.has_value(),
              "current location offset must not be null");

    auto after = context.current_location().offset.value();

    LT_ASSERT(before != after,
              "onLexOne must consume at least one grapheme cluster");
  }

  LT_ASSERT(!context.are_more_grapheme_clusters(),
            "lexer did not consume all grapheme clusters - there is remaining "
            "unlexed source content");

  return std::move(context).take_tokens();
}
#pragma clang diagnostic pop
}  // namespace lt
