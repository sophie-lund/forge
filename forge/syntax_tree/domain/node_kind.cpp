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
#include <forge/syntax_tree/domain/node_kind.hpp>

namespace forge {
NodeKind::NodeKind(const char* name) : _name(name) { assert(name != nullptr); }

const char* NodeKind::name() const { return _name; }

std::ostream& operator<<(std::ostream& stream, const NodeKind& node_kind) {
  stream << node_kind.name();
  return stream;
}

bool operator==(const NodeKind& lhs, const NodeKind& rhs) {
  return lhs.name() == rhs.name();
}

bool operator!=(const NodeKind& lhs, const NodeKind& rhs) {
  return !operator==(lhs, rhs);
}
}  // namespace forge
