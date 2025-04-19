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

#include <forgec/formatting/forge_formatters.hpp>
#include <forgec/messages/forge_message_emitters.hpp>
#include <langtools/syntax_tree/domain/base_node.hpp>
#include <numeric>
#include <sstream>

/**
 * @def FRG_TYPE_NOTE_THRESHOLD
 *
 * @brief The minimum length for the string representation of a type for it to
 * be reported as a separate note instead of inline in the error message.
 */
#define FRG_TYPE_NOTE_THRESHOLD 15

namespace forge {
// LCOV_EXCL_START

lt::Message& emit_syntax_error_unexpected_character(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ESY001",
                              "unexpected character");
}

lt::Message& emit_syntax_error_unclosed_block_comment(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ESY002",
                              "unclosed block comment");
}

lt::Message& emit_syntax_error_invalid_number_literal(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ESY003",
                              "invalid number literal");
}

lt::Message& emit_syntax_error_unexpected_token(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    std::initializer_list<const char*> expected) {
  std::string expected_str =
      std::accumulate(expected.begin(), expected.end(), std::string(),
                      [](const std::string& a, const char* b) {
                        return a.empty() ? b : a + ", " + b;
                      });

  return message_context.emit(source_range, lt::SEVERITY_ERROR,
                              message_code_error_unexpected_token,
                              "unexpected token, expected " + expected_str);
}

lt::Message& emit_scope_error_member_shadows_inherited(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ESC003",
                              "member shadows inherited member with same name");
}

lt::Message& emit_internal_error_not_well_formed(
    lt::MessageContext& message_context,
    const std::shared_ptr<lt::BaseNode>& node, std::string&& text) {
  LT_ASSERT(node != nullptr, "node must not be null");

  return message_context.emit(node->source_range, lt::SEVERITY_ERROR,
                              message_code_error_internal_not_well_formed,
                              std::move(text));
}

lt::Message& emit_type_error_no_void_pointers(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context
      .emit(source_range, lt::SEVERITY_ERROR, "ETY001",
            "void pointers are not allowed")
      .child(lt::SourceRange(), lt::SEVERITY_SUGGESTION, "use 'usize' instead");
}

lt::Message& emit_type_error_no_function_pointers(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context
      .emit(source_range, lt::SEVERITY_ERROR, "ETY002",
            "function pointers are not allowed")
      .child(lt::SourceRange(), lt::SEVERITY_SUGGESTION,
             "function types do not need to be pointers, just remove the '*'");
}

lt::Message& emit_type_error_no_void_arguments(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ETY003",
                              "function arguments cannot be of type 'void'");
}

lt::Message& emit_type_error_unexpected_type(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const char* expected) {
  return message_context
      .emit(source_range, lt::SEVERITY_ERROR, "ETY004", "unexpected type")
      .child(lt::SourceRange(), lt::SEVERITY_NOTE,
             std::format("expected {}", expected));
}

lt::Message& emit_type_error_unable_to_implicitly_cast(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const std::shared_ptr<BaseType>& from,
    const std::shared_ptr<BaseType>& to) {
  std::stringstream from_stream;

  format_type(FormattingOptions(from_stream), from);

  std::stringstream to_stream;

  format_type(FormattingOptions(to_stream), to);

  auto from_string = from_stream.str();
  auto to_string = to_stream.str();

  if (from_string.size() < FRG_TYPE_NOTE_THRESHOLD &&
      to_string.size() < FRG_TYPE_NOTE_THRESHOLD) {
    return message_context
        .emit(source_range, lt::SEVERITY_ERROR, "ETY005",
              std::format("unable to implicitly cast from type {} to {}",
                          from_string, to_string))
        .child(lt::SourceRange(), lt::SEVERITY_SUGGESTION,
               "use 'as' to cast between types");
  } else {
    return message_context
        .emit(source_range, lt::SEVERITY_ERROR, "ETY005",
              "unable to implicitly cast")
        .child(lt::SourceRange(), lt::SEVERITY_NOTE,
               std::format("from type: {}", from_string))
        .child(lt::SourceRange(), lt::SEVERITY_NOTE,
               std::format("to type: {}", to_string))
        .child(lt::SourceRange(), lt::SEVERITY_SUGGESTION,
               "use 'as' to cast between types");
  }
}

lt::Message& emit_type_error_illegal_cast(lt::MessageContext& message_context,
                                          const lt::SourceRange& source_range,
                                          const std::shared_ptr<BaseType>& from,
                                          const std::shared_ptr<BaseType>& to) {
  std::stringstream from_stream;

  format_type(FormattingOptions(from_stream), from);

  std::stringstream to_stream;

  format_type(FormattingOptions(to_stream), to);

  auto from_string = from_stream.str();
  auto to_string = to_stream.str();

  if (from_string.size() < FRG_TYPE_NOTE_THRESHOLD &&
      to_string.size() < FRG_TYPE_NOTE_THRESHOLD) {
    return message_context.emit(source_range, lt::SEVERITY_ERROR, "ETY005",
                                std::format("unable to cast from type {} to {}",
                                            from_string, to_string));
  } else {
    return message_context
        .emit(source_range, lt::SEVERITY_ERROR, "ETY006", "unable to cast")
        .child(lt::SourceRange(), lt::SEVERITY_NOTE,
               std::format("from type: {}", from_string))
        .child(lt::SourceRange(), lt::SEVERITY_NOTE,
               std::format("to type: {}", to_string));
  }
}

lt::Message& emit_type_error_incorrect_number_of_args(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    size_t expected, size_t actual) {
  return message_context.emit(
      source_range, lt::SEVERITY_ERROR, "ETY007",
      std::format("expected {} argument{}, but {} {} provided", expected,
                  expected == 1 ? "" : "s", actual,
                  actual == 1 ? "was" : "were"));
}

lt::Message& emit_type_error_cannot_call_non_function(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const std::shared_ptr<BaseType>& type) {
  std::stringstream type_stream;

  format_type(FormattingOptions(type_stream), type);

  return message_context
      .emit(source_range, lt::SEVERITY_ERROR, "ETY008",
            "value is not a function and cannot be called")
      .child(lt::SourceRange(), lt::SEVERITY_NOTE,
             std::format("value type: {}", type_stream.str()));
}

lt::Message& emit_type_error_non_void_function_must_return_value(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ETY009",
                              "non-void function must return a value");
}

lt::Message& emit_type_error_void_function_cannot_return_value(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ETY010",
                              "void function cannot return a value");
}

lt::Message& emit_type_error_no_member_with_name(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ETY011",
                              "structured type has no member with name");
}

lt::Message& emit_type_error_unable_to_resolve(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const char* reason) {
  return message_context.emit(
      source_range, lt::SEVERITY_ERROR, "ETY012",
      std::format("unable to resolve type - {}", reason));
}

lt::Message& emit_type_error_namespace_used_as_value(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ETY013",
                              "namespace cannot be used as a value");
}

lt::Message& emit_type_error_namespace_within_structured_type(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(
      source_range, lt::SEVERITY_ERROR, "ETY014",
      "namespace cannot be declared within a structured type");
}

lt::Message& emit_control_flow_error_unreachable_statement(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ECF001",
                              "statement is unreachable");
}

lt::Message& emit_control_flow_error_function_does_not_always_return(
    lt::MessageContext& message_context, const lt::SourceRange& source_range) {
  return message_context.emit(source_range, lt::SEVERITY_ERROR, "ECF002",
                              "function does not return in all cases");
}

// LCOV_EXCL_STOP
}  // namespace forge
