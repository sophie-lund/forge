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

#include <forge/messaging/message.hpp>
#include <forge/syntax_tree/domain/node_kind.hpp>
#include <forge/syntax_tree/scope/scope.hpp>

namespace forge {
class Pass;
class DebugFormatter;
class SymbolResolutionHandler;

enum class SymbolMode { declares, references };

/**
 * @brief A base type for all nodes to implement as a common base class.
 */
class BaseNode {
 public:
  friend class Pass;
  friend class SymbolResolutionHandler;

  /**
   * @brief Construct a new `BaseNode` object with an optional source range.
   *
   * @param source_range The optional source range to store in the node. You
   * can pass it in as an implicit value or use `std::nullopt` to omit it.
   */
  BaseNode(NodeKind kind, std::optional<SourceRange>&& source_range);

  virtual ~BaseNode() = 0;

  BaseNode(const BaseNode& other) = delete;
  BaseNode(BaseNode&& other) = delete;
  BaseNode& operator=(const BaseNode& other) = delete;
  BaseNode& operator=(BaseNode&& other) = delete;

  /**
   * @brief An identifier for the kind of node.
   */
  const NodeKind kind;

  /**
   * @brief An optional source range associated with the node to trace it back
   *        to the source code.
   */
  const std::optional<SourceRange> source_range;

  void for_each_direct_child(
      std::function<void(const BaseNode&)> on_direct_child) const;

  bool compare(const BaseNode& other) const;

  std::shared_ptr<BaseNode> clone() const;

  void format_debug(DebugFormatter& formatter) const;

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
   * @brief Accepts a pass to visit the node.
   */
  virtual void on_accept(Pass& pass) = 0;

  /**
   * @brief Formats the current node for debugging.
   */
  virtual void on_format_debug(DebugFormatter& formatter) const = 0;

  /**
   * @brief Gets a pointer to the scope field.
   *
   * This must be overridden for the node to be able to have a scope.
   */
  virtual std::shared_ptr<Scope>* on_get_scope_field_pointer();

  /**
   * @brief Gets the flags for the scope.
   *
   * These are used to initialize the scope. See @a ScopeFlags for more details.
   */
  virtual ScopeFlags on_get_scope_flags() const;

  virtual void on_resolve_symbol(std::shared_ptr<BaseNode> referencedNode);

  virtual std::optional<std::pair<SymbolMode, std::string>> on_get_symbol()
      const;
};
}  // namespace forge
