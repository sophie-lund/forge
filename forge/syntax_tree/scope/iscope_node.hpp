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

class IScopeNode {
 public:
  virtual ~IScopeNode() = 0;

  virtual ScopeFlags scope_flags() const = 0;

  virtual const Scope& scope() const = 0;
};
}  // namespace forge
