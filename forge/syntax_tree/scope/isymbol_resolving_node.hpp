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

#include <memory>
#include <optional>
#include <string>

namespace forge {
class BaseNode;
class Scope;

/**
 * @brief Flags to be passed to @a Scope.
 */
using ScopeFlags = uint32_t;

/**
 * @brief No flags.
 */
constexpr ScopeFlags SCOPE_FLAG_NONE = 0;

/**
 * @brief Allow symbols to shadow symbols declared in parent scopes.
 *
 * For example:
 *
 * @code{.c}
 * int x = 0;
 *
 * if (x == 0) {
 *   int x = 1; // this shadows the parent declaration
 * }
 * @endcode
 *
 * With this flag the above code would be allowed. Otherwise, it would cause a
 * duplicate symbol error.
 */
constexpr ScopeFlags SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE = 1;

/**
 * @brief Allow symbols to shadow symbols declared in the same scope.
 *
 * @note This doesn't automatically allow shadowing in parent scopes. Use
 * @a SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE for that. They are independent.
 *
 * For example:
 *
 * @code{.c}
 * int x = 0;
 *
 * int x = 1; // this shadows the first declaration
 * @endcode
 *
 * With this flag the above code would be allowed. Otherwise, it would cause a
 * duplicate symbol error.
 */
constexpr ScopeFlags SCOPE_FLAG_ALLOW_SHADOWING_WITHIN_SCOPE = 1 << 1;

/**
 * @brief Declarations within this scope can reference declarations that come
 *        after them.
 *
 * For example:
 *
 * @code{.c}
 * int y = x;
 *
 * int x = 1;
 * @endcode
 *
 * With this flag the above code would be allowed. Otherwise, it would cause an
 * undeclared symbol error.
 */
constexpr ScopeFlags SCOPE_FLAG_UNORDERED = 1 << 2;

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
   * @brief If this node declares a symbol, get its name.
   *
   * Calls @c on_get_declared_symbol_name internally.
   */
  std::optional<std::string> get_declared_symbol_name() const;

  /**
   * @brief If this node references a symbol, get its name.
   *
   * Calls @c on_get_referenced_symbol_name internally.
   */
  std::optional<std::string> get_referenced_symbol_name() const;

  /**
   * @brief Resolve a symbol reference. If this node does not reference a symbol
   * this will not do anything.
   *
   * Calls @c on_resolve_symbol internally.
   */
  void resolve_symbol(std::shared_ptr<BaseNode> referenced_node);

  /**
   * @brief Get the scope flags for this node.
   *
   * Calls @c on_get_scope_flags internally.
   */
  ScopeFlags get_scope_flags() const;

  /**
   * @brief If this node has a scope, get it.
   *
   * Calls @c on_try_get_scope internally.
   */
  const Scope* try_get_scope() const;

 protected:
  virtual std::optional<std::string> on_get_declared_symbol_name() const;

  virtual std::optional<std::string> on_get_referenced_symbol_name() const;

  virtual void on_resolve_symbol(std::shared_ptr<BaseNode> referenced_node);

  virtual ScopeFlags on_get_scope_flags() const;

  virtual const Scope* on_try_get_scope() const;
};
}  // namespace forge
