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
#include <forge/parsing/domain/token_kind.hpp>

namespace forge {
TokenKind::TokenKind(const char* name) : name(name) { assert(name != nullptr); }

std::ostream& operator<<(std::ostream& stream, const TokenKind& node_kind) {
  stream << node_kind.name;
  return stream;
}

bool operator==(const TokenKind& lhs, const TokenKind& rhs) {
  return lhs.name == rhs.name;
}

bool operator!=(const TokenKind& lhs, const TokenKind& rhs) {
  return !operator==(lhs, rhs);
}
}  // namespace forge
