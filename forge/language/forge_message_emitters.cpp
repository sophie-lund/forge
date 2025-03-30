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
#include <forge/syntax_tree/domain/base_node.hpp>
#include <numeric>

namespace forge {
Message& emit_syntax_error_unexpected_character(MessageContext& message_context,
                                                const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ESY001",
                              "unexpected character");
}

Message& emit_syntax_error_unclosed_block_comment(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ESY002",
                              "unclosed block comment");
}

Message& emit_syntax_error_invalid_number_literal(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ESY003",
                              "invalid number literal");
}

Message& emit_syntax_error_unexpected_token(
    MessageContext& message_context, const SourceRange& range,
    std::initializer_list<const char*> expected) {
  std::string expected_str =
      std::accumulate(expected.begin(), expected.end(), std::string(),
                      [](const std::string& a, const char* b) {
                        return a.empty() ? b : a + ", " + b;
                      });

  return message_context.emit(range, SEVERITY_ERROR, "ESY004",
                              "unexpected token, expected " + expected_str);
}

Message& emit_internal_error_not_well_formed(MessageContext& message_context,
                                             const BaseNode& node,
                                             std::string&& text) {
  return message_context.emit(node.source_range, SEVERITY_ERROR,
                              message_code_error_internal_not_well_formed,
                              std::move(text));
}
}  // namespace forge
