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

#include <forge/syntaxtree/domain/Node.hpp>
#include <forge/syntaxtree/scope/Scope.hpp>
#include <forge/syntaxtree/visitors/Handler.hpp>

namespace forge {
/**
 * @brief A handler that automatically resolves symbols in the syntax tree.
 *
 * This assumes that any nodes that have a scope contain a `Scope` property  and
 * any nodes that have a symbol contain both a string of that symbol and an
 * optional shared pointer to the node that the symbol references.
 *
 * @pre No preconditions must be met for this handler to work.
 *
 * @post The symbols will be resolved in the current node and all direct child
 *       nodes by the time any subsequent enter handlers are called.
 */
template <typename TBaseNode>
class SymbolResolutionHandler : public Handler<TBaseNode> {
 protected:
  virtual typename Handler<TBaseNode>::Output onEnter(
      typename Handler<TBaseNode>::Input& input) override;

  virtual typename Handler<TBaseNode>::Output onLeave(
      typename Handler<TBaseNode>::Input& input) override;

 private:
  //   void tryAddUnorderedChildren(MessageContext& messageContext,
  //                                NodeInfo& nodeInfo);

  void tryAddSymbolToScope(MessageContext& messageContext,
                           const Scope<TBaseNode>* parentScope,
                           const std::shared_ptr<TBaseNode>& node);

  void tryResolveSymbolInScope(MessageContext& messageContext,
                               const Scope<TBaseNode>* parentScope,
                               std::shared_ptr<TBaseNode>& node);

  const Scope<TBaseNode>* tryFindParentScope(
      typename Handler<TBaseNode>::Input& input);
};
}  // namespace forge

#include "SymbolResolutionHandler.tpp"
