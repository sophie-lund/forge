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

#include <forge/syntax_tree/scope/isymbol_resolving_node.hpp>

namespace forge {
ISymbolResolvingNode::~ISymbolResolvingNode() {}

SymbolResolvingNodeFlags ISymbolResolvingNode::symbol_resolving_node_flags()
    const {
  return SYMBOL_RESOLVING_NODE_FLAG_NONE;
}

IDeclareSymbol* ISymbolResolvingNode::try_as_declare_symbol() {
  if (symbol_resolving_node_flags() &
      SYMBOL_RESOLVING_NODE_FLAG_DECLARES_SYMBOL) {
    return reinterpret_cast<IDeclareSymbol*>(this);
  } else {
    return nullptr;
  }
}

const IDeclareSymbol* ISymbolResolvingNode::try_as_declare_symbol() const {
  if (symbol_resolving_node_flags() &
      SYMBOL_RESOLVING_NODE_FLAG_DECLARES_SYMBOL) {
    return reinterpret_cast<const IDeclareSymbol*>(this);
  } else {
    return nullptr;
  }
}

IReferenceSymbol* ISymbolResolvingNode::try_as_reference_symbol() {
  if (symbol_resolving_node_flags() &
      SYMBOL_RESOLVING_NODE_FLAG_REFERENCES_SYMBOL) {
    return reinterpret_cast<IReferenceSymbol*>(this);
  } else {
    return nullptr;
  }
}

const IReferenceSymbol* ISymbolResolvingNode::try_as_reference_symbol() const {
  if (symbol_resolving_node_flags() &
      SYMBOL_RESOLVING_NODE_FLAG_REFERENCES_SYMBOL) {
    return reinterpret_cast<const IReferenceSymbol*>(this);
  } else {
    return nullptr;
  }
}

IScopeNode* ISymbolResolvingNode::try_as_scope_node() {
  if (symbol_resolving_node_flags() & SYMBOL_RESOLVING_NODE_FLAG_IS_SCOPE) {
    return reinterpret_cast<IScopeNode*>(this);
  } else {
    return nullptr;
  }
}

const IScopeNode* ISymbolResolvingNode::try_as_scope_node() const {
  if (symbol_resolving_node_flags() & SYMBOL_RESOLVING_NODE_FLAG_IS_SCOPE) {
    return reinterpret_cast<const IScopeNode*>(this);
  } else {
    return nullptr;
  }
}
}  // namespace forge
