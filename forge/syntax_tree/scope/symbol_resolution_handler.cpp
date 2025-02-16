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

#include <forge/core/tracing.hpp>
#include <forge/syntax_tree/scope/ideclare_symbol.hpp>
#include <forge/syntax_tree/scope/ireference_symbol.hpp>
#include <forge/syntax_tree/scope/iscope_node.hpp>
#include <forge/syntax_tree/scope/isymbol_resolving_node.hpp>
#include <forge/syntax_tree/scope/symbol_resolution_handler.hpp>

// Whenever the handler enters a given node, it needs to do two things:
//
// 1. If the node references a symbol, resolve it.
// 2. If the node declares a symbol, add it to the most direct parent scope.
//
// It does the tasks in this order so that a node cannot reference itself
// leading to circular shared pointer dependencies.
//
// 1. Symbol resolution algorithm
// -----------------------------------------------------------------------------
//
// - For each parent scope from most direct to top level:
//   - If the symbol is in the scope, resolve it and stop iterating.
// - If the symbol was not found in any scope, emit an error.
//
// 2. Symbol declaration algorithm
// -----------------------------------------------------------------------------
//
// - For each parent scope from most direct to top level:
//   - Take note of the most direct parent scope
//   - If the symbol is in the scope:
//     - If the scope allows shadowing within the scope, overwrite the existing
//       symbol and stop iterating.
//     - Otherwise, emit an error and stop iterating.
//   - If the scope does not allow shadowing within the scope, stop iterating.

namespace forge {
IHandler::Output SymbolResolutionHandler::on_enter(Input& input) {
  // Cast the input to a symbol resolving node
  auto input_casted =
      reinterpret_cast<ISymbolResolvingNode*>(input.node().get());

  // If the node references a symbol...
  IReferenceSymbol* reference_symbol = input_casted->try_as_reference_symbol();
  if (reference_symbol != nullptr) {
    bool found = false;

    // For each parent scope from most direct to top level...
    for (auto i = input.stack().rbegin(); i != input.stack().rend(); i++) {
      auto parent_casted =
          reinterpret_cast<const ISymbolResolvingNode*>(&i->get());

      const IScopeNode* scope_node = parent_casted->try_as_scope_node();
      if (scope_node == nullptr) {
        continue;
      }

      // Try to resolve the symbol
      std::shared_ptr<BaseNode> resolved_node =
          scope_node->scope().get(reference_symbol->referenced_symbol_name());

      // Stop if the symbol is resolved
      if (resolved_node != nullptr) {
        reference_symbol->resolve_symbol(resolved_node);
        found = true;
        break;
      }
    }

    // Error if the symbol could not be resolved
    if (!found) {
      input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                   "???", "use of undeclared symbol");
    }
  }

  // If the node declares a symbol...
  IDeclareSymbol* declare_symbol = input_casted->try_as_declare_symbol();
  if (declare_symbol != nullptr) {
    const IScopeNode* most_direct_parent_scope_node = nullptr;
    bool illegally_shadows = false;

    // For each parent scope from most direct to top level...
    for (auto i = input.stack().rbegin(); i != input.stack().rend(); i++) {
      auto parent_casted =
          reinterpret_cast<const ISymbolResolvingNode*>(&i->get());

      const IScopeNode* scope_node = parent_casted->try_as_scope_node();
      if (scope_node == nullptr) {
        continue;
      }

      // Take note of the most direct parent scope
      if (most_direct_parent_scope_node == nullptr) {
        most_direct_parent_scope_node = scope_node;
      }

      // If the current scope already declares this symbol...
      if (scope_node->scope().get(declare_symbol->declared_symbol_name()) !=
          nullptr) {
        // If it is not allowed, take note of the error and stop iterating
        if ((scope_node->scope_flags() &
             SCOPE_FLAG_ALLOW_SHADOWING_WITHIN_SCOPE) == 0) {
          illegally_shadows = true;
          break;
        }
      }

      // If the scope allows shadowing parents, there's no more reason to
      // continue checking
      if ((scope_node->scope_flags() &
           SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE) != 0) {
        break;
      }
    }

    if (illegally_shadows) {
      // If the symbol is already declared, emit an error
      input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                   "???", "redeclaration of existing symbol");
    } else if (most_direct_parent_scope_node != nullptr) {
      // If there is a parent scope, declare the symbol
      most_direct_parent_scope_node->scope().add(
          declare_symbol->declared_symbol_name(), input.node());
    } else {
      // If there is no parent scope, emit an error
      input.message_context().emit(
          input.node()->source_range, SEVERITY_ERROR, "???",
          "no surrounding scope in which to declare/resolve symbol");
    }
  }

  return Output();
}

IHandler::Output SymbolResolutionHandler::on_leave(Input&) { return Output(); }
}  // namespace forge
