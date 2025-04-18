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

#include <langtools/parsing/domain/source_range.hpp>
#include <langtools/parsing/domain/token_kind.hpp>

namespace lt {
/**
 * @brief A token of code which has been lexed.
 */
class Token {
 public:
  Token(const TokenKind& kind, SourceRange&& source_range,
        std::u16string_view&& value);

  /**
   * @brief The kind of token.
   */
  const TokenKind kind;

  /**
   * @brief The range of the token in the source code.
   */
  const SourceRange source_range;

  /**
   * @brief The string value of the token.
   */
  std::u16string_view value;
};
}  // namespace lt
