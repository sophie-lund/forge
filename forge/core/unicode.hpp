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

namespace forge {
std::string detectParsingLocaleName();
icu::Locale detectParsingLocale();
std::string detectMessageLocaleName();
icu::Locale detectMessageLocale();

bool is_symbol_start(char16_t value);
bool is_symbol_start(const std::u16string_view& value);
bool is_symbol_continue(char16_t value);
bool is_symbol_continue(const std::u16string_view& value);
}  // namespace forge
