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

#include <forgec/syntax_tree/types/base_type.hpp>
#include <langtools/messaging/message_context.hpp>
#include <langtools/parsing/domain/token_kind.hpp>

namespace forge {
// ---------------------------------------------------------------------------
// INTERNAL ERRORS
// ---------------------------------------------------------------------------

constexpr std::string message_code_error_internal_not_well_formed = "EIN001";
constexpr std::string message_code_error_internal_no_scope = "EIN002";

/**
 * @brief Message code @c EIN001.
 */
lt::Message& emit_internal_error_not_well_formed(
    lt::MessageContext& message_context,
    const std::shared_ptr<lt::BaseNode>& node, std::string&& text);

// ---------------------------------------------------------------------------
// SYNTAX ERRORS
// ---------------------------------------------------------------------------

/**
 * @brief Message code @c ESY001.
 */
lt::Message& emit_syntax_error_unexpected_character(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ESY002.
 */
lt::Message& emit_syntax_error_unclosed_block_comment(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ESY003.
 */
lt::Message& emit_syntax_error_invalid_number_literal(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

constexpr std::string message_code_error_unexpected_token = "ESY004";

/**
 * @brief Message code @c ESY004.
 */
lt::Message& emit_syntax_error_unexpected_token(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    std::initializer_list<const char*> expected);

// ---------------------------------------------------------------------------
// SYNTAX WARNINGS
// ---------------------------------------------------------------------------

/**
 * @brief Message code @c WSY001.
 */
template <typename TValue>
lt::Message& emit_syntax_warning_number_literal_truncated(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const char* type_name, TValue before_truncation, TValue after_truncation);

// ---------------------------------------------------------------------------
// SCOPE ERRORS
// ---------------------------------------------------------------------------

constexpr std::string message_code_error_scope_undeclared = "ESC001";
constexpr std::string message_code_error_scope_cannot_redeclare = "ESC002";

/**
 * @brief Message code @c ESC003.
 */
lt::Message& emit_scope_error_member_shadows_inherited(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

// ---------------------------------------------------------------------------
// TYPE ERRORS
// ---------------------------------------------------------------------------

/**
 * @brief Message code @c ETY001.
 */
lt::Message& emit_type_error_no_void_pointers(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY002.
 */
lt::Message& emit_type_error_no_function_pointers(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY003.
 */
lt::Message& emit_type_error_no_void_arguments(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY004.
 */
lt::Message& emit_type_error_unexpected_type(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const char* expected);

/**
 * @brief Message code @c ETY005.
 */
lt::Message& emit_type_error_unable_to_implicitly_cast(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const std::shared_ptr<BaseType>& from, const std::shared_ptr<BaseType>& to);

/**
 * @brief Message code @c ETY006.
 */
lt::Message& emit_type_error_illegal_cast(lt::MessageContext& message_context,
                                          const lt::SourceRange& source_range,
                                          const std::shared_ptr<BaseType>& from,
                                          const std::shared_ptr<BaseType>& to);

/**
 * @brief Message code @c ETY007.
 */
lt::Message& emit_type_error_incorrect_number_of_args(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    size_t expected, size_t actual);

/**
 * @brief Message code @c ETY008.
 */
lt::Message& emit_type_error_cannot_call_non_function(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const std::shared_ptr<BaseType>& type);

/**
 * @brief Message code @c ETY009.
 */
lt::Message& emit_type_error_non_void_function_must_return_value(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY010.
 */
lt::Message& emit_type_error_void_function_cannot_return_value(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY011.
 */
lt::Message& emit_type_error_no_member_with_name(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY012.
 */
lt::Message& emit_type_error_unable_to_resolve(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const char* reason);

/**
 * @brief Message code @c ETY013.
 */
lt::Message& emit_type_error_namespace_used_as_value(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);

/**
 * @brief Message code @c ETY014.
 */
lt::Message& emit_type_error_namespace_within_structured_type(
    lt::MessageContext& message_context, const lt::SourceRange& source_range);
}  // namespace forge

#include "forge_message_emitters.tpp"
