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

#include <memory>
#include <vector>

namespace forge {
class BaseNode;

/**
 * @brief The different statuses that a visitor can use to alter the traversal
 * path.
 */
enum class VisitorStatus {
  /**
   * @brief The traversal should continue uninterrupted.
   */
  continue_,

  /**
   * @brief The traversal should not traverse the children of the current node,
   * but should continue down other branches of the node tree.
   */
  do_not_traverse_children,

  /**
   * @brief Traversal should stop here and not go over any other nodes.
   */
  halt_traversal,
};

/**
 * @brief An interface for visiting nodes in a syntax tree.
 */
class IVisitor {
 public:
  virtual ~IVisitor() = 0;

  /**
   * @brief Visits a node and all of its children.
   */
  template <typename TNode>
  void visit(std::shared_ptr<TNode>& input);

  /**
   * @brief Visits a node vector and all of its children.
   */
  template <typename TNode>
  void visit(std::vector<std::shared_ptr<TNode>>& input);

 protected:
  virtual VisitorStatus on_enter(std::shared_ptr<BaseNode>& node) = 0;
  virtual VisitorStatus on_leave(std::shared_ptr<BaseNode>& node) = 0;
  //   virtual void on_visit(std::shared_ptr<BaseNode>& node) = 0;
};
}  // namespace forge

#include "ivisitor.tpp"
