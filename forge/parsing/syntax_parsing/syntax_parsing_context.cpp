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

#include <forge/parsing/syntax_parsing/syntax_parsing_context.hpp>

namespace forge {
SyntaxParsingContext::SyntaxParsingContext(MessageContext& message_context,
                                           const std::vector<Token>& tokens)
    : _message_context(message_context), _tokens(tokens), _cursor(0) {}

MessageContext& SyntaxParsingContext::message_context() {
  return _message_context;
}

bool SyntaxParsingContext::are_more_tokens() const {
  return _cursor < static_cast<int32_t>(_tokens.get().size());
}

const Token& SyntaxParsingContext::peek_next_token() const {
  assert(_cursor < static_cast<int32_t>(_tokens.get().size()));
  return _tokens.get().at(_cursor);
}

const Token& SyntaxParsingContext::read_next_token() {
  assert(_cursor < static_cast<int32_t>(_tokens.get().size()));
  return _tokens.get().at(_cursor++);
}

int32_t SyntaxParsingContext::save_cursor() const { return _cursor; }

void SyntaxParsingContext::restore_cursor(int32_t value) {
  assert(value >= 0);
  assert(value < static_cast<int32_t>(_tokens.get().size()));

  _cursor = value;
}
}  // namespace forge
