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

#include <forge/messaging/message_context.hpp>
#include <forge/parsing/domain/token_kind.hpp>

namespace forge {
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

/**
 * @brief Message code @c ESY004.
 */
Message& emit_syntax_error_unexpected_token(
    MessageContext& message_context, const SourceRange& range,
    std::initializer_list<const char*> expected);

/**
 * @brief Message code @c WSY001.
 */
template <typename TValue>
Message& emit_syntax_warning_number_literal_truncated(
    MessageContext& message_context, const SourceRange& range,
    const char* type_name, TValue before_truncation, TValue after_truncation);

/**
 * @brief Message code @c EIN001.
 */
Message& emit_internal_error_not_well_formed(MessageContext& message_context,
                                             const BaseNode& node,
                                             std::string&& text);
}  // namespace forge

#include "forge_message_emitters.tpp"
