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

#include <langtools/parsing/lexing/base_lexer.hpp>

namespace forge {
class ForgeLexer : public lt::BaseLexer {
 public:
  ForgeLexer();

  virtual void onLexOne(lt::LexerContext& context) final;
};

std::optional<lt::TokenKind> try_get_keyword_token_kind(
    const std::string& value);
}  // namespace forge
