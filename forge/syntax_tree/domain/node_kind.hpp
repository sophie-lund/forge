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

#include <ostream>

namespace forge {
/**
 * @brief A kind of a node.
 */
class NodeKind {
 public:
  /**
   * @param name The name of the node kind as it should be printed when
   * debugging.
   */
  explicit NodeKind(const char* name);

  /**
   * Get the name.
   */
  const char* name() const;

 private:
  const char* _name;
};

std::ostream& operator<<(std::ostream& stream, const NodeKind& node_kind);

bool operator==(const NodeKind& lhs, const NodeKind& rhs);
bool operator!=(const NodeKind& lhs, const NodeKind& rhs);
}  // namespace forge
