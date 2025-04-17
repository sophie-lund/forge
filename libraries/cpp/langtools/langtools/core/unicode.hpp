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

#include <unicode/locid.h>

namespace lt {
/**
 * @brief Detect the locale's name to use for parsing.
 */
[[nodiscard]]
std::string detect_parsing_locale_name();

/**
 * @brief Detect the locale to use for parsing.
 */
[[nodiscard]]
icu::Locale detect_parsing_locale();

/**
 * @brief Detect the locale's name to use for messages.
 */
[[nodiscard]]
std::string detect_message_locale_name();

/**
 * @brief Detect the locale to use for messages.
 */
[[nodiscard]]
icu::Locale detect_message_locale();

/**
 * @brief Returns @c true if the character can be the start of a valid symbol.
 */
bool is_symbol_start(char16_t value);

/**
 * @brief Returns @c true if the character can be the start of a valid symbol.
 */
bool is_symbol_start(const std::u16string_view& value);

/**
 * @brief Returns @c true if the character can be a valid character within a
 * symbol.
 */
bool is_symbol_continue(char16_t value);

/**
 * @brief Returns @c true if the character can be a valid character within a
 * symbol.
 */
bool is_symbol_continue(const std::u16string_view& value);

/**
 * @brief Converts a @c std::u16string_view to a @c std::string using UTF-16 to
 * UTF-8 conversion.
 */
std::string u16string_view_to_string(const std::u16string_view& value);
}  // namespace lt
