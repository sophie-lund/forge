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

#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/scope/scope.hpp>
#include <forge/syntax_tree/visitors/handler.hpp>

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
class SymbolResolutionHandler : public IHandler {
 protected:
  virtual Output on_enter(Input& input) override;

  virtual Output on_leave(Input& input) override;

 private:
  //   void try_add_unordered_children(MessageContext& message_context,
  //                                NodeInfo& node_info);

  void try_add_symbol_to_scope(MessageContext& message_context,
                               const Scope* parent_scope,
                               const std::shared_ptr<BaseNode>& node);

  void try_resolve_symbol_in_scope(MessageContext& message_context,
                                   const Scope* parent_scope,
                                   std::shared_ptr<BaseNode>& node);

  const Scope* try_find_parent_scope(Input& input);
};
}  // namespace forge
