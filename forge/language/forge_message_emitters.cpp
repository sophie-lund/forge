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

#include <forge/language/forge_message_emitters.hpp>

namespace forge {
void emit_syntax_error_unexpected_character(MessageContext& message_context,
                                            const SourceRange& range) {
  message_context.emit(range, SEVERITY_ERROR, "ES001", "unexpected character");
}

void emit_syntax_error_unclosed_block_comment(MessageContext& message_context,
                                              const SourceRange& range) {
  message_context.emit(range, SEVERITY_ERROR, "ES002",
                       "unclosed block comment");
}

void emit_syntax_error_invalid_number_literal(MessageContext& message_context,
                                              const SourceRange& range) {
  message_context.emit(range, SEVERITY_ERROR, "ES003",
                       "invalid number literal");
}

void emit_syntax_error_unexpected_token(
    MessageContext& message_context, const SourceRange& range,
    std::initializer_list<const TokenKind*> expected) {
  std::string expected_str;

  for (const TokenKind* token_kind : expected) {
    if (!expected_str.empty()) {
      expected_str += ", ";
    }
    expected_str += token_kind->name;
  }

  message_context.emit(range, SEVERITY_ERROR, "ES004",
                       "unexpected token, expected " + expected_str);
}
}  // namespace forge
