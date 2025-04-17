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
#include <ostream>
#include <string>
#include <unordered_map>

namespace lt {
class BaseNode;

/**
 * @brief A way to store symbols that follows most programming languages.
 *
 * The methods are all @c const, including those that mutate the scope, because
 * many handlers that will need to modify scope have a @c const reference to the
 * node they are visiting. This helps get around this problem without causing a
 * mess in the codebase.
 */
class Scope {
 public:
  Scope() = default;

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
  bool add(const std::string& key, std::shared_ptr<BaseNode> value) const;

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
  std::shared_ptr<BaseNode> get(const std::string& key) const;

 private:
  std::unordered_map<std::string, std::shared_ptr<BaseNode>> _map;
};
}  // namespace lt
