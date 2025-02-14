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
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/scope/scope.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>

namespace forge {
template <typename TBaseNode>
class Pass;

template <typename TNodeKind>
class DebugFormatter;

template <typename TBaseNode>
class SymbolResolutionHandler;

enum class SymbolMode { declares, references };

/**
 * @brief A base type for all nodes to implement as a common base class.
 */
template <typename TBaseNode, typename TKind>
class Node {
 public:
  using BaseNode = TBaseNode;
  using Kind = TKind;

  friend class Pass<TBaseNode>;

  friend class SymbolResolutionHandler<TBaseNode>;

  /**
   * @brief Construct a new Node object with an optional source range.
   *
   * @param source_range The optional source range to store in the node. You
   * can pass it in as an implicit value or use `std::nullopt` to omit it.
   */
  Node(TKind&& kind, std::optional<SourceRange>&& source_range);

  virtual ~Node() = 0;

  Node(const Node& other) = delete;
  Node(Node&& other) = delete;
  Node& operator=(const Node& other) = delete;
  Node& operator=(Node&& other) = delete;

  /**
   * @brief An identifier for the kind of node.
   */
  const TKind kind;

  /**
   * @brief An optional source range associated with the node to trace it back
   *        to the source code.
   */
  const std::optional<SourceRange> source_range;

  void for_each_direct_child(
      std::function<void(const TBaseNode&)> on_direct_child) const;

  bool compare(const TBaseNode& other) const;

  std::shared_ptr<TBaseNode> clone() const;

  void format_debug(DebugFormatter<TKind>& formatter) const;

 protected:
  /**
   * @brief Compares the current node with @p other.
   */
  virtual bool on_compare(const TBaseNode& other) const = 0;

  /**
   * @brief Clones the current node.
   */
  virtual std::shared_ptr<TBaseNode> on_clone() const = 0;

  /**
   * @brief Accepts a pass to visit the node.
   */
  virtual void on_accept(Pass<TBaseNode>& pass) = 0;

  /**
   * @brief Formats the current node for debugging.
   */
  virtual void on_format_debug(DebugFormatter<TKind>& formatter) const = 0;

  /**
   * @brief Gets a pointer to the scope field.
   *
   * This must be overridden for the node to be able to have a scope.
   */
  virtual std::shared_ptr<Scope<TBaseNode>>* on_get_scope_field_pointer();

  /**
   * @brief Gets the flags for the scope.
   *
   * These are used to initialize the scope. See @a ScopeFlags for more details.
   */
  virtual ScopeFlags on_get_scope_flags() const;

  virtual void on_resolve_symbol(std::shared_ptr<TBaseNode> referencedNode);

  virtual std::optional<std::pair<SymbolMode, std::string>> on_get_symbol()
      const;
};
}  // namespace forge

#include "base_node.tpp"
