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

namespace forge::syntaxtree {
template <typename TNode>
bool compare(const std::vector<std::shared_ptr<TNode>>& lhs,
             const std::vector<std::shared_ptr<TNode>>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (size_t i = 0; i < lhs.size(); i++) {
    if (!compare(lhs[i], rhs[i])) {
      return false;
    }
  }

  return true;
}

template <typename TNode>
bool compare(const std::shared_ptr<TNode>& lhs,
             const std::shared_ptr<TNode>& rhs) {
  if (lhs == nullptr) {
    if (rhs == nullptr) {
      return true;
    } else {
      return false;
    }
  } else {
    if (rhs == nullptr) {
      return false;
    } else {
      if (lhs->kind != rhs->kind) {
        return false;
      }

      return static_cast<
                 const Node<typename TNode::BaseNode, typename TNode::Kind>&>(
                 *lhs)
          .onCompare(*rhs);
    }
  }
}
}  // namespace forge::syntaxtree
