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

#include <forge/messaging/Message.hpp>
#include <forge/syntaxtree/DebugFormatter.hpp>
#include <forge/syntaxtree/Pass.hpp>
#include <forge/syntaxtree/Scope.hpp>

/**
 * @namespace forge::syntaxtree
 * @brief Base classes and helpers for declaring a set of classes to make up a
 *        syntax tree.
 */
namespace forge::syntaxtree {
template <typename TNode>
bool compare(const std::shared_ptr<TNode>& lhs,
             const std::shared_ptr<TNode>& rhs);

template <typename TNode>
std::shared_ptr<TNode> clone(const std::shared_ptr<TNode>& node);

template <typename TBaseNode>
class Pass;

template <typename TNodeKind>
class DebugFormatter;

template <typename TBaseNode>
class SymbolResolutionHandler;

enum class SymbolMode { Declares, References };

/**
 * @brief A base type for all nodes to implement as a common base class.
 */
template <typename TBaseNode, typename TKind>
class Node {
 public:
  using BaseNode = TBaseNode;
  using Kind = TKind;

  template <typename TNode>
  friend bool forge::syntaxtree::compare(const std::shared_ptr<TNode>& lhs,
                                            const std::shared_ptr<TNode>& rhs);

  template <typename TNode>
  friend std::shared_ptr<TNode> forge::syntaxtree::clone(
      const std::shared_ptr<TNode>& node);

  friend class Pass<TBaseNode>;

  friend class DebugFormatter<TKind>;

  friend class SymbolResolutionHandler<TBaseNode>;

  /**
   * @brief Construct a new Node object with an optional source range.
   *
   * @param sourceRange The optional source range to store in the node. You
   * can pass it in as an implicit value or use `std::nullopt` to omit it.
   */
  Node(TKind&& kind, std::optional<parsing::SourceRange>&& sourceRange);

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
  const std::optional<parsing::SourceRange> sourceRange;

  void forEachDirectChild(
      std::function<void(const TBaseNode&)> onDirectChild) const;

 protected:
  /**
   * @brief Compares the current node with @p other.
   */
  virtual bool onCompare(const TBaseNode& other) const = 0;

  /**
   * @brief Clones the current node.
   */
  virtual std::shared_ptr<TBaseNode> onClone() const = 0;

  /**
   * @brief Accepts a pass to visit the node.
   */
  virtual void onAccept(Pass<TBaseNode>& pass) = 0;

  /**
   * @brief Formats the current node for debugging.
   */
  virtual void onFormatDebug(DebugFormatter<TKind>& formatter) const = 0;

  /**
   * @brief Gets a pointer to the scope field.
   *
   * This must be overridden for the node to be able to have a scope.
   */
  virtual std::shared_ptr<Scope<TBaseNode>>* onGetScopeFieldPointer();

  /**
   * @brief Gets the flags for the scope.
   *
   * These are used to initialize the scope. See @a ScopeFlags for more details.
   */
  virtual ScopeFlags onGetScopeFlags() const;

  virtual void onResolveSymbol(std::shared_ptr<TBaseNode> referencedNode);

  virtual std::optional<std::pair<SymbolMode, std::string>> onGetSymbol() const;
};
}  // namespace forge::syntaxtree

#include "Node.tpp"
