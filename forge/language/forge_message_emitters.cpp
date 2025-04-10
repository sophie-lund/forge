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

  return message_context.emit(range, SEVERITY_ERROR,
                              message_code_error_unexpected_token,
                              "unexpected token, expected " + expected_str);
}

Message& emit_scope_error_member_shadows_inherited(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ESC003",
                              "member shadows inherited member with same name");
}

Message& emit_internal_error_not_well_formed(
    MessageContext& message_context, const std::shared_ptr<BaseNode>& node,
    std::string&& text) {
  FRG_ASSERT(node != nullptr, "node must not be null");

  return message_context.emit(node->source_range, SEVERITY_ERROR,
                              message_code_error_internal_not_well_formed,
                              std::move(text));
}

Message& emit_type_error_no_void_pointers(MessageContext& message_context,
                                          const SourceRange& range) {
  return message_context
      .emit(range, SEVERITY_ERROR, "ETY001", "void pointers are not allowed")
      .child(SourceRange(), SEVERITY_SUGGESTION, "use 'usize' instead");
}

Message& emit_type_error_no_function_pointers(MessageContext& message_context,
                                              const SourceRange& range) {
  return message_context
      .emit(range, SEVERITY_ERROR, "ETY002",
            "function pointers are not allowed")
      .child(SourceRange(), SEVERITY_SUGGESTION,
             "function types do not need to be pointers, just remove the '*'");
}

Message& emit_type_error_no_void_arguments(MessageContext& message_context,
                                           const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY003",
                              "function arguments cannot be of type 'void'");
}

Message& emit_type_error_unexpected_type(MessageContext& message_context,
                                         const SourceRange& range,
                                         const char* expected) {
  return message_context
      .emit(range, SEVERITY_ERROR, "ETY004", "unexpected type")
      .child(SourceRange(), SEVERITY_NOTE,
             std::format("expected {}", expected));
}

Message& emit_type_error_unable_to_implicitly_cast(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY005", "unable to cast")
      .child(SourceRange(), SEVERITY_SUGGESTION,
             "use 'as' to cast between types");
}

Message& emit_type_error_illegal_cast(MessageContext& message_context,
                                      const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY006",
                              "illegal cast between types");
}

Message& emit_type_error_incorrect_number_of_args(
    MessageContext& message_context, const SourceRange& range, size_t expected,
    size_t actual) {
  return message_context.emit(
      range, SEVERITY_ERROR, "ETY007",
      std::format("expected {} argument{}, but {} {} provided", expected,
                  expected == 1 ? "" : "s", actual,
                  actual == 1 ? "was" : "were"));
}

Message& emit_type_error_cannot_call_non_function(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY008",
                              "value is not a function and cannot be called");
}

Message& emit_type_error_non_void_function_must_return_value(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY009",
                              "non-void function must return a value");
}

Message& emit_type_error_void_function_cannot_return_value(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY010",
                              "void function cannot return a value");
}

Message& emit_type_error_no_member_with_name(MessageContext& message_context,
                                             const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY011",
                              "structured type has no member with name");
}

Message& emit_type_error_unable_to_resolve(MessageContext& message_context,
                                           const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY012",
                              "unable to resolve type");
}

Message& emit_type_error_namespace_used_as_value(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(range, SEVERITY_ERROR, "ETY013",
                              "namespace cannot be used as a value");
}

Message& emit_type_error_namespace_within_structured_type(
    MessageContext& message_context, const SourceRange& range) {
  return message_context.emit(
      range, SEVERITY_ERROR, "ETY014",
      "namespace cannot be declared within a structured type");
}
}  // namespace forge
