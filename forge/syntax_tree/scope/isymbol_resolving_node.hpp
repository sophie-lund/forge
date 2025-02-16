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

#include <cstdint>

namespace forge {
class IDeclareSymbol;
class IReferenceSymbol;
class IScopeNode;

/**
 * @brief Flags to be provided by @c ISymbolResolvingNode.
 */
using SymbolResolvingNodeFlags = uint32_t;

/**
 * @brief No flags.
 */
constexpr SymbolResolvingNodeFlags SYMBOL_RESOLVING_NODE_FLAG_NONE = 0;

/**
 * @brief The current node is declaring a symbol.
 */
constexpr SymbolResolvingNodeFlags SYMBOL_RESOLVING_NODE_FLAG_DECLARES_SYMBOL =
    1;

/**
 * @brief The current node is referencing a symbol.
 */
constexpr SymbolResolvingNodeFlags
    SYMBOL_RESOLVING_NODE_FLAG_REFERENCES_SYMBOL = 1 << 1;

/**
 * @brief The current node is a scope in itself.
 */
constexpr SymbolResolvingNodeFlags SYMBOL_RESOLVING_NODE_FLAG_IS_SCOPE = 1 << 2;

/**
 * @brief An interface for nodes that have symbol resolution logic.
 *
 * Languages that use node resolution must have all of their nodes implement
 * this interface.
 */
class ISymbolResolvingNode {
 public:
  virtual ~ISymbolResolvingNode() = 0;

  /**
   * @brief Gets the flags for the symbol resolving node.
   *
   * This must be implemented by all implementing classes. The results of this
   * will decide the behavior of the other `try_as_*` methods in this interface.
   *
   * By default, this will return @c SYMBOL_RESOLVING_NODE_FLAG_NONE.
   */
  virtual SymbolResolvingNodeFlags symbol_resolving_node_flags() const;

  /**
   * @brief Tries to cast the current node to a @c IDeclareSymbol.
   *
   * @returns The current node casted to the interface if the
   * @c SYMBOL_RESOLVING_NODE_FLAG_DECLARES_SYMBOL flag is set, otherwise
   * @c nullptr.
   */
  IDeclareSymbol* try_as_declare_symbol();

  /**
   * @brief Tries to cast the current node to a @c IDeclareSymbol.
   *
   * @returns The current node casted to the interface if the
   * @c SYMBOL_RESOLVING_NODE_FLAG_DECLARES_SYMBOL flag is set, otherwise
   * @c nullptr.
   */
  const IDeclareSymbol* try_as_declare_symbol() const;

  /**
   * @brief Tries to cast the current node to a @c IReferenceSymbol.
   *
   * @returns The current node casted to the interface if the
   * @c SYMBOL_RESOLVING_NODE_FLAG_REFERENCES_SYMBOL flag is set, otherwise
   * @c nullptr.
   */
  IReferenceSymbol* try_as_reference_symbol();

  /**
   * @brief Tries to cast the current node to a @c IReferenceSymbol.
   *
   * @returns The current node casted to the interface if the
   * @c SYMBOL_RESOLVING_NODE_FLAG_REFERENCES_SYMBOL flag is set, otherwise
   * @c nullptr.
   */
  const IReferenceSymbol* try_as_reference_symbol() const;

  /**
   * @brief Tries to cast the current node to a @c IScopeNode.
   *
   * @returns The current node casted to the interface if the
   * @c SYMBOL_RESOLVING_NODE_FLAG_IS_SCOPE flag is set, otherwise
   * @c nullptr.
   */
  IScopeNode* try_as_scope_node();

  /**
   * @brief Tries to cast the current node to a @c IScopeNode.
   *
   * @returns The current node casted to the interface if the
   * @c SYMBOL_RESOLVING_NODE_FLAG_IS_SCOPE flag is set, otherwise
   * @c nullptr.
   */
  const IScopeNode* try_as_scope_node() const;
};
}  // namespace forge
