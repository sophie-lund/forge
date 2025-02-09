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

#include <unordered_map>

namespace forge::syntaxtree {
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
 * @brief A way to store symbols that follows most programming languages.
 *
 * The methods are all @c const, including those that mutate the scope, because
 * many handlers that will need to modify scope have a @c const reference to the
 * node they are visiting. This helps get around this problem without causing a
 * mess in the codebase.
 */
template <typename TBaseNode>
class Scope {
 public:
  /**
   * @param parent The parent scope, if any exists.
   * @param flags Flags to control the behavior of the scope.
   */
  Scope(std::shared_ptr<Scope<TBaseNode>> parent = nullptr,
        ScopeFlags flags = SCOPE_FLAG_NONE);

  Scope(const Scope& other) = delete;
  Scope(Scope&& other) = delete;
  Scope& operator=(const Scope& other) = delete;
  Scope& operator=(Scope&& other) = delete;

  /**
   * @brief Adds a new symbol to the scope.
   *
   * @param key The key to store the symbol under.
   * @param value The syntax tree to reference by the symbol.
   *
   * @returns @c true if the symbol can be safely declared by the rules of the
   *          scope, otherwise @c false.
   */
  bool add(const std::string& key, std::shared_ptr<TBaseNode> value) const;

  /**
   * @brief Removes a symbol to the scope.
   *
   * @param key The key to find the symbol under.
   *
   * @returns @c true if the symbol was successfully removed, @c false
   *          otherwise.
   */
  bool remove(const std::string& key) const;

  /**
   * @brief Gets the tree associated with the symbol.
   *
   * @param key The key to find the symbol under.
   *
   * @returns The tree associated with the symbol or @c nullptr if the symbol
   *          does not exist in this scope or any parent scope.
   */
  std::shared_ptr<TBaseNode> get(const std::string& key) const;

 private:
  std::shared_ptr<Scope<TBaseNode>> parent_;
  std::map<std::string, std::shared_ptr<TBaseNode>> map_;
  ScopeFlags flags_;
};
}  // namespace forge::syntaxtree

#include "Scope.tpp"
