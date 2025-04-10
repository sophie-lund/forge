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

#include <forge/core/tracing.hpp>
#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/scope/isymbol_resolving_node.hpp>
#include <forge/syntax_tree/scope/scope.hpp>
#include <forge/syntax_tree/visitors/ihandler.hpp>
#include <ranges>

namespace forge {
struct SymbolResolutionHandlerOptions {
  std::string message_code_undeclared;
  std::string message_code_redeclared;
  std::string message_code_no_scope;
};

/**
 * @brief A handler that automatically resolves symbols in the syntax tree.
 */
template <typename TNode>
class SymbolResolutionHandler : public IHandler {
 public:
  SymbolResolutionHandler(SymbolResolutionHandlerOptions&& options);

 protected:
  virtual Output on_enter(Input<>& input) final;
  virtual Output on_leave(Input<>& input) final;

 private:
  void handle_referenced_symbol(Input<>& input,
                                const std::shared_ptr<TNode>& input_casted,
                                const std::string& referenced_symbol_name);

  void handle_declared_symbol(Input<>& input,
                              const std::string& declared_symbol_name);

  const SymbolResolutionHandlerOptions options;
};
}  // namespace forge

#include "symbol_resolution_handler.tpp"