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

#include <forge/core/assert.hpp>
#include <forge/parsing/lexing/base_lexer.hpp>

namespace forge {
BaseLexer::~BaseLexer() {}

std::vector<Token> BaseLexer::lex(MessageContext& message_context,
                                  const Source& source) {
  LexerContext context(message_context, source);

  while (context.are_more_grapheme_clusters()) {
    FRG_ASSERT(context.current_location().offset.has_value(),
               "current location offset must not be null");

    auto before = context.current_location().offset.value();

    onLexOne(context);

    FRG_ASSERT(context.current_location().offset.has_value(),
               "current location offset must not be null");

    auto after = context.current_location().offset.value();

    FRG_ASSERT(before != after,
               "onLexOne must consume at least one grapheme cluster");
  }

  FRG_ASSERT(!context.are_more_grapheme_clusters(),
             "lexer did not consume all grapheme clusters - there is remaining "
             "unlexed source content");

  return std::move(context).take_tokens();
}
}  // namespace forge
