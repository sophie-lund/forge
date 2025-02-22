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
}  // namespace forge
