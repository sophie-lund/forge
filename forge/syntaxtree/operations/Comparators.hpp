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
 * @file Comparators.hpp
 *
 * @brief Contains helper functions for comparing syntax tree nodes.
 */

#pragma once

#include <forge/syntaxtree/domain/Node.hpp>

namespace forge::syntaxtree {
/**
 * @brief Compares two vectors of nodes.
 *
 * @tparam TNode The type of node to compare. Must inherit @a Node.
 *
 * @returns @c true if the vectors are equivalent and @c false otherwise.
 *
 * It checks to make sure that the vectors are the same length and that each
 * node is equivalent.
 *
 * @note @c nullptr nodes are considered equivalent.
 */
template <typename TNode>
bool compare(const std::vector<std::shared_ptr<TNode>>& lhs,
             const std::vector<std::shared_ptr<TNode>>& rhs);

/**
 * @brief Compares two single nodes.
 *
 * @tparam TNode The type of node to compare. Must inherit @a Node.
 *
 * @returns @c true if the nodes are equivalent and @c false otherwise.
 *
 * It checks to make sure that the nodes are equivalent.
 *
 * @note Nodes that are @c nullptr are considered equivalent to each other.
 */
template <typename TNode>
bool compare(const std::shared_ptr<TNode>& lhs,
             const std::shared_ptr<TNode>& rhs);
}  // namespace forge::syntaxtree

#include "Comparators.tpp"
