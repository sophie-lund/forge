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

#include <langtools/messaging/message.hpp>
#include <langtools/syntax_tree/domain/node_kind.hpp>

namespace lt {
class IVisitor;
class DebugFormatter;

/**
 * @brief A base type for all nodes to implement as a common base class.
 *
 * This is essentially an interface with properties to store the node kind and
 * source range that the node spans.
 */
class BaseNode {
 public:
  /**
   * @brief Construct a new `BaseNode` object with an optional source range.
   *
   * @param kind The kind of node.
   * @param source_range The optional source range to store in the node. You
   * can pass it in as an implicit value or use `std::nullopt` to omit it.
   */
  BaseNode(NodeKind kind, SourceRange&& source_range);

  virtual ~BaseNode() = 0;

  BaseNode(const BaseNode& other) = delete;
  BaseNode(BaseNode&& other) = delete;
  BaseNode& operator=(const BaseNode& other) = delete;
  BaseNode& operator=(BaseNode&& other) = delete;

  /**
   * @brief An identifier for the kind of node.
   *
   * This is only set by the constructor.
   */
  const NodeKind kind;

  /**
   * @brief An optional source range associated with the node to trace it back
   *        to the source code.
   */
  const SourceRange source_range;

  /**
   * @brief A utility to iterate over each direct child of the node.
   *
   * @param on_direct_child The function to call for each direct child.
   *
   * This uses the visitor pattern with a shallow visitor.
   *
   */
  void for_each_direct_child(
      std::function<void(const BaseNode&)> on_direct_child) const;

  /**
   * @brief Compares the current node to another.
   *
   * @returns @c true if the nodes are equivalent and @c false otherwise.
   *
   * This is a deep comparison. It does not take into account whether the
   * current or other nodes are null nor the source ranges of the nodes. See
   * `langtools/syntax_tree/operations/comparators.hpp` for related helper
   * functions.
   */
  bool compare(const BaseNode& other) const;

  /**
   * @brief Clones the current node.
   *
   * @returns A new instance of the current node.
   *
   * This is a deep clone. It will duplicate the source range as well. It does
   * not take into account whether the current node is null or not. See
   * `langtools/syntax_tree/operations/cloners.hpp` for related helper
   * functions.
   */
  std::shared_ptr<BaseNode> clone() const;

  /**
   * @brief Accepts a visitor.
   *
   * See @c IVisitor for more details.
   */
  void accept(IVisitor& visitor);

  /**
   * @brief Formats the current node for debugging purposes.
   *
   * See @c DebugFormatter for more details.
   */
  void format_debug(DebugFormatter& formatter) const;

  void format_brief(std::ostream& stream) const;

 protected:
  /**
   * @brief Compares the current node with @p other.
   */
  virtual bool on_compare(const BaseNode& other) const = 0;

  /**
   * @brief Clones the current node.
   */
  virtual std::shared_ptr<BaseNode> on_clone() const = 0;

  /**
   * @brief Accepts a visitor.
   */
  virtual void on_accept(IVisitor& visitor) = 0;

  /**
   * @brief Formats the current node for debugging.
   */
  virtual void on_format_debug(DebugFormatter& formatter) const = 0;

  virtual void on_format_brief(std::ostream& stream) const;
};
}  // namespace lt
