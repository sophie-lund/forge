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

#include <forge/language/syntax_tree/types/base_type.hpp>
#include <forge/messaging/message_context.hpp>
#include <forge/parsing/domain/token_kind.hpp>

namespace forge {
// ---------------------------------------------------------------------------
// INTERNAL ERRORS
// ---------------------------------------------------------------------------

constexpr std::string message_code_error_internal_not_well_formed = "EIN001";
constexpr std::string message_code_error_internal_no_scope = "EIN002";

/**
 * @brief Message code @c EIN001.
 */
Message& emit_internal_error_not_well_formed(
    MessageContext& message_context, const std::shared_ptr<BaseNode>& node,
    std::string&& text);

// ---------------------------------------------------------------------------
// SYNTAX ERRORS
// ---------------------------------------------------------------------------

/**
 * @brief Message code @c ESY001.
 */
Message& emit_syntax_error_unexpected_character(MessageContext& message_context,
                                                const SourceRange& range);

/**
 * @brief Message code @c ESY002.
 */
Message& emit_syntax_error_unclosed_block_comment(
    MessageContext& message_context, const SourceRange& range);

/**
 * @brief Message code @c ESY003.
 */
Message& emit_syntax_error_invalid_number_literal(
    MessageContext& message_context, const SourceRange& range);

constexpr std::string message_code_error_unexpected_token = "ESY004";

/**
 * @brief Message code @c ESY004.
 */
Message& emit_syntax_error_unexpected_token(
    MessageContext& message_context, const SourceRange& range,
    std::initializer_list<const char*> expected);

// ---------------------------------------------------------------------------
// SYNTAX WARNINGS
// ---------------------------------------------------------------------------

/**
 * @brief Message code @c WSY001.
 */
template <typename TValue>
Message& emit_syntax_warning_number_literal_truncated(
    MessageContext& message_context, const SourceRange& range,
    const char* type_name, TValue before_truncation, TValue after_truncation);

// ---------------------------------------------------------------------------
// SCOPE ERRORS
// ---------------------------------------------------------------------------

constexpr std::string message_code_error_scope_undeclared = "ESC001";
constexpr std::string message_code_error_scope_cannot_redeclare = "ESC002";

/**
 * @brief Message code @c ESC003.
 */
Message& emit_scope_error_member_shadows_inherited(
    MessageContext& message_context, const SourceRange& range);

// ---------------------------------------------------------------------------
// TYPE ERRORS
// ---------------------------------------------------------------------------

/**
 * @brief Message code @c ETY001.
 */
Message& emit_type_error_no_void_pointers(MessageContext& message_context,
                                          const SourceRange& range);

/**
 * @brief Message code @c ETY002.
 */
Message& emit_type_error_no_function_pointers(MessageContext& message_context,
                                              const SourceRange& range);

/**
 * @brief Message code @c ETY003.
 */
Message& emit_type_error_no_void_arguments(MessageContext& message_context,
                                           const SourceRange& range);

/**
 * @brief Message code @c ETY004.
 */
Message& emit_type_error_unexpected_type(MessageContext& message_context,
                                         const SourceRange& range,
                                         const char* expected);

/**
 * @brief Message code @c ETY005.
 */
Message& emit_type_error_unable_to_implicitly_cast(
    MessageContext& message_context, const SourceRange& range,
    const std::shared_ptr<BaseType>& from, const std::shared_ptr<BaseType>& to);

/**
 * @brief Message code @c ETY006.
 */
Message& emit_type_error_illegal_cast(MessageContext& message_context,
                                      const SourceRange& range,
                                      const std::shared_ptr<BaseType>& from,
                                      const std::shared_ptr<BaseType>& to);

/**
 * @brief Message code @c ETY007.
 */
Message& emit_type_error_incorrect_number_of_args(
    MessageContext& message_context, const SourceRange& range, size_t expected,
    size_t actual);

/**
 * @brief Message code @c ETY008.
 */
Message& emit_type_error_cannot_call_non_function(
    MessageContext& message_context, const SourceRange& range,
    const std::shared_ptr<BaseType>& type);

/**
 * @brief Message code @c ETY009.
 */
Message& emit_type_error_non_void_function_must_return_value(
    MessageContext& message_context, const SourceRange& range);

/**
 * @brief Message code @c ETY010.
 */
Message& emit_type_error_void_function_cannot_return_value(
    MessageContext& message_context, const SourceRange& range);

/**
 * @brief Message code @c ETY011.
 */
Message& emit_type_error_no_member_with_name(MessageContext& message_context,
                                             const SourceRange& range);

/**
 * @brief Message code @c ETY012.
 */
Message& emit_type_error_unable_to_resolve(MessageContext& message_context,
                                           const SourceRange& range);

/**
 * @brief Message code @c ETY013.
 */
Message& emit_type_error_namespace_used_as_value(
    MessageContext& message_context, const SourceRange& range);

/**
 * @brief Message code @c ETY014.
 */
Message& emit_type_error_namespace_within_structured_type(
    MessageContext& message_context, const SourceRange& range);
}  // namespace forge

#include "forge_message_emitters.tpp"
