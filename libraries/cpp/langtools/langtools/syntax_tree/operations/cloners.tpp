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

namespace lt {
template <typename TNode>
std::vector<std::shared_ptr<TNode>> clone_node_vector(
    const std::vector<std::shared_ptr<TNode>>& nodes) {
  std::vector<std::shared_ptr<TNode>> result;

  for (const auto& node : nodes) {
    result.push_back(clone_node(node));
  }

  return result;
}

template <typename TNode>
std::shared_ptr<TNode> clone_node(const std::shared_ptr<TNode>& node) {
  if (node) {
    return std::static_pointer_cast<TNode>(node->clone());
  } else {
    return nullptr;
  }
}
}  // namespace lt
