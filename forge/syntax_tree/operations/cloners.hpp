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

/**
 * @file Cloners.hpp
 *
 * @brief Contains helper functions for cloning syntax tree nodes.
 */

#pragma once

#include <forge/syntax_tree/domain/base_node.hpp>

namespace forge {
/**
 * @brief Clones a vector of nodes.
 *
 * @tparam TNode The type of node to clone. Must inherit @a BaseNode.
 *
 * If any of the nodes are @c nullptr, they will still be cloned as @c nullptr.
 */
template <typename TNode>
std::vector<std::shared_ptr<TNode>> clone_node_vector(
    const std::vector<std::shared_ptr<TNode>>& nodes);

/**
 * @brief Clones a single node.
 *
 * @tparam TNode The type of node to clone. Must inherit @a BaseNode.
 *
 * @returns A clone of @p node or @c nullptr if @p node is @c nullptr.
 */
template <typename TNode>
std::shared_ptr<TNode> clone_node(const std::shared_ptr<TNode>& node);
}  // namespace forge

#include "cloners.tpp"
