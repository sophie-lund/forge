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
#include <forge/parsing/syntax_parsing/parsing_context.hpp>

namespace forge {
ParsingContext::ParsingContext(MessageContext& message_context,
                               const std::vector<Token>& tokens)
    : _message_context(message_context), _tokens(tokens), _cursor(0) {}

MessageContext& ParsingContext::message_context() { return _message_context; }

bool ParsingContext::are_more_tokens() const {
  return _cursor < static_cast<int32_t>(_tokens.get().size());
}

const Token& ParsingContext::peek_next_token() const {
  FRG_ASSERT(_cursor < static_cast<int32_t>(_tokens.get().size()),
             "cursor cannot overflow token vector");
  return _tokens.get().at(_cursor);
}

const Token& ParsingContext::read_next_token() {
  FRG_ASSERT(_cursor < static_cast<int32_t>(_tokens.get().size()),
             "cursor cannot overflow token vector");
  return _tokens.get().at(_cursor++);
}

int32_t ParsingContext::save_cursor() const { return _cursor; }

void ParsingContext::restore_cursor(int32_t value) {
  FRG_ASSERT(value >= 0, "cursor cannot be negative");
  FRG_ASSERT(value < static_cast<int32_t>(_tokens.get().size()),
             "cursor cannot overflow token vector");

  _cursor = value;
}
}  // namespace forge
