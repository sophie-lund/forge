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

#include <cassert>
#include <forge/core/unicode.hpp>

namespace forge {
std::string detectParsingLocaleName() {
  const char* locale = getenv("LC_ALL");
  if (locale != nullptr) {
    return locale;
  }

  locale = getenv("LC_CTYPE");
  if (locale != nullptr) {
    return locale;
  }

  locale = getenv("LANG");
  if (locale != nullptr) {
    return locale;
  }

  return "C";
}

icu::Locale detectParsingLocale() {
  icu::Locale locale = icu::Locale(detectParsingLocaleName().c_str());

  assert(!locale.isBogus() && "failed to load parsing locale");

  return locale;
}

std::string detectMessageLocaleName() {
  const char* locale = getenv("LC_ALL");
  if (locale != nullptr) {
    return locale;
  }

  locale = getenv("LC_MESSAGES");
  if (locale != nullptr) {
    return locale;
  }

  locale = getenv("LANG");
  if (locale != nullptr) {
    return locale;
  }

  return "C";
}

icu::Locale detectMessageLocale() {
  return icu::Locale(detectMessageLocaleName().c_str());
}

bool is_symbol_start(char16_t value) {
  if (value == u'_' || (value >= u'a' && value <= u'z') ||
      (value >= u'A' && value <= u'Z')) {
    return true;
  } else if (value < 0x80) {
    return false;
  } else {
    // Just assume all unicode characters are fit to be part of symbols
    return true;
  }
}

bool is_symbol_start(const std::u16string_view& value) {
  if (value.empty()) {
    return false;
  } else {
    return is_symbol_start(value[0]);
  }
}

bool is_symbol_continue(char16_t value) {
  if (is_symbol_start(value) || (value >= u'0' && value <= u'9')) {
    return true;
  } else {
    return false;
  }
}

bool is_symbol_continue(const std::u16string_view& value) {
  if (value.empty()) {
    return false;
  } else {
    return is_symbol_continue(value[0]);
  }
}

std::string u16string_view_to_string(const std::u16string_view& value) {
  icu::UnicodeString ustr(reinterpret_cast<const UChar*>(value.data()),
                          value.size());
  std::string result;
  ustr.toUTF8String(result);
  return result;
}
}  // namespace forge
