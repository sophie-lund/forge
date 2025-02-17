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

namespace forge {
/**
 * @brief A handler that automatically resolves symbols in the syntax tree.
 */
template <typename TNode>
class SymbolResolutionHandler : public IHandler {
 protected:
  virtual Output on_enter(Input& input) override;
  virtual Output on_leave(Input&) override;
};
}  // namespace forge

#include "symbol_resolution_handler.tpp"