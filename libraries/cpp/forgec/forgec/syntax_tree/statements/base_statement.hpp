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

#include <forgec/syntax_tree/base_forge_node.hpp>

namespace forge {
class BaseStatement : public BaseForgeNode {
 public:
  BaseStatement(lt::NodeKind kind, lt::SourceRange&& source_range);

  ~BaseStatement() = 0;

  /**
   * @brief Whether this statement terminates the current block.
   *
   * This is always set to @c std::nullopt by default, but is set and used by
   * @c ControlFlowValidationHandler.
   */
  std::optional<bool> terminates_block;

  /**
   * @brief Whether this statement terminates the current function.
   *
   * This is always set to @c std::nullopt by default, but is set and used by
   * @c ControlFlowValidationHandler.
   */
  std::optional<bool> terminates_function;
};
}  // namespace forge
