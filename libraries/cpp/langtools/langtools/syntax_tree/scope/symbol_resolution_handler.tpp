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

// Whenever the handler enters a given node, it needs to do two things:
//
// 1. If the node references a symbol, resolve it.
// 2. If the node declares a symbol, add it to the most direct parent scope.
//
// It does the tasks in this order so that a node cannot reference itself
// leading to circular shared pointer dependencies.
//
// 1. Symbol resolution algorithm
//
// -----------------------------------------------------------------------------
//
// - For each parent scope from most direct to top level:
//   - If the symbol is in the scope, resolve it and stop iterating.
// - If the symbol was not found in any scope, emit an error.
//
// 2. Symbol declaration algorithm
//
// -----------------------------------------------------------------------------
//
// - For each parent scope from most direct to top level:
//   - Take note of the most direct parent scope
//   - If the symbol is in the scope:
//     - If the scope allows shadowing within the scope, overwrite the existing
//       symbol and stop iterating.
//     - Otherwise, emit an error and stop iterating.
//   - If the scope does not allow shadowing within the scope, stop iterating.

namespace lt {
template <typename TNode>
SymbolResolutionHandler<TNode>::SymbolResolutionHandler(
    SymbolResolutionHandlerOptions&& options)
    : options(std::move(options)) {}

template <typename TNode>
IHandler::Output SymbolResolutionHandler<TNode>::on_enter(Input<>& input) {
  // Cast the input to a symbol resolving node
  auto input_casted = static_pointer_cast<TNode>(input.node());

  // If the node references a symbol...
  if (auto referenced_symbol_name = input_casted->get_referenced_symbol_name();
      referenced_symbol_name.has_value()) {
    handle_referenced_symbol(input, input_casted,
                             referenced_symbol_name.value());
  }

  // If the node declares a symbol...
  if (auto declared_symbol_name = input_casted->get_declared_symbol_name();
      declared_symbol_name.has_value()) {
    handle_declared_symbol(input, declared_symbol_name.value());
  }

  return Output();
}

template <typename TNode>
IHandler::Output SymbolResolutionHandler<TNode>::on_leave(Input<>&) {
  return Output();
}

template <typename TNode>
void SymbolResolutionHandler<TNode>::handle_referenced_symbol(
    Input<>& input, const std::shared_ptr<TNode>& input_casted,
    const std::string& referenced_symbol_name) {
  trace("SymbolResolutionHandler")
      << "node references symbol: " << referenced_symbol_name << std::endl;

  bool found = false;

  // For each parent scope from most direct to top level...
  for (auto i = input.stack().rbegin(); i != input.stack().rend(); i++) {
    auto parent_casted = static_pointer_cast<const TNode>(*i);

    const Scope* scope = parent_casted->try_get_scope();
    if (scope == nullptr) {
      continue;
    }

    // Try to resolve the symbol
    if (auto resolved_node = scope->get(referenced_symbol_name);
        resolved_node != nullptr) {
      trace("SymbolResolutionHandler")
          << "resolved to " << resolved_node->kind << std::endl;

      input_casted->resolve_symbol(resolved_node);
      found = true;
      break;
    }
  }

  // Error if the symbol could not be resolved
  if (!found) {
    input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                 std::string(options.message_code_undeclared),
                                 "use of undeclared symbol");
  }
}

template <typename TNode>
void SymbolResolutionHandler<TNode>::handle_declared_symbol(
    Input<>& input, const std::string& declared_symbol_name) {
  trace("SymbolResolutionHandler")
      << "node declares symbol: " << declared_symbol_name << std::endl;

  const Scope* most_direct_parent_scope = nullptr;
  std::shared_ptr<const BaseNode> most_direct_parent = nullptr;
  bool illegally_shadows = false;

  // For each parent scope from most direct to top level...
  for (auto i = input.stack().rbegin(); i != input.stack().rend(); i++) {
    auto parent_casted = static_pointer_cast<const TNode>(*i);

    const Scope* scope = parent_casted->try_get_scope();
    if (scope == nullptr) {
      continue;
    }

    // Take note of the most direct parent scope
    if (most_direct_parent_scope == nullptr) {
      most_direct_parent_scope = scope;
      most_direct_parent = parent_casted;
    }

    // If the current scope already declares this symbol...
    if (scope->get(declared_symbol_name) != nullptr) {
      // If it is not allowed, take note of the error and stop iterating
      if ((parent_casted->get_scope_flags() &
           SCOPE_FLAG_ALLOW_SHADOWING_WITHIN_SCOPE) == 0) {
        illegally_shadows = true;
        break;
      }
    }

    // If the scope allows shadowing parents, there's no more reason to
    // continue checking
    if ((parent_casted->get_scope_flags() &
         SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE) != 0) {
      break;
    }
  }

  if (illegally_shadows) {
    // If the symbol is already declared, emit an error
    input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                 std::string(options.message_code_redeclared),
                                 "redeclaration of existing symbol");
  } else if (most_direct_parent_scope != nullptr) {
    // If there is a parent scope, declare the symbol
    trace("SymbolResolutionHandler") << "declaring symbol in scope "
                                     << most_direct_parent->kind << std::endl;

    most_direct_parent_scope->add(declared_symbol_name, input.node());
  } else {
    // If there is no parent scope, emit an error
    input.message_context().emit(
        input.node()->source_range, SEVERITY_ERROR,
        std::string(options.message_code_no_scope),
        "no surrounding scope in which to declare/resolve symbol");
  }
}
}  // namespace lt
