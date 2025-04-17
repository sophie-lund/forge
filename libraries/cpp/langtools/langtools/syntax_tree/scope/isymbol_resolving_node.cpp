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

#include <langtools/syntax_tree/scope/isymbol_resolving_node.hpp>

namespace lt {
ISymbolResolvingNode::~ISymbolResolvingNode() {}

// LCOV_EXCL_START

std::optional<std::string> ISymbolResolvingNode::get_declared_symbol_name()
    const {
  return on_get_declared_symbol_name();
}

std::optional<std::string> ISymbolResolvingNode::get_referenced_symbol_name()
    const {
  return on_get_referenced_symbol_name();
}

void ISymbolResolvingNode::resolve_symbol(
    std::shared_ptr<BaseNode> referenced_node) {
  on_resolve_symbol(referenced_node);
}

ScopeFlags ISymbolResolvingNode::get_scope_flags() const {
  return on_get_scope_flags();
}

const Scope* ISymbolResolvingNode::try_get_scope() const {
  return on_try_get_scope();
}

std::optional<std::string> ISymbolResolvingNode::on_get_declared_symbol_name()
    const {
  return std::nullopt;
}

std::optional<std::string> ISymbolResolvingNode::on_get_referenced_symbol_name()
    const {
  return std::nullopt;
}

void ISymbolResolvingNode::on_resolve_symbol(std::shared_ptr<BaseNode>) {
  // do nothing
}

ScopeFlags ISymbolResolvingNode::on_get_scope_flags() const {
  return SCOPE_FLAG_NONE;
}

const Scope* ISymbolResolvingNode::on_try_get_scope() const { return nullptr; }

// LCOV_EXCL_STOP
}  // namespace lt
