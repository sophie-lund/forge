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

#include <forge/messaging/message_context.hpp>
#include <forge/syntax_tree/visitors/handler.hpp>

namespace forge {
/**
 * @brief A pass which visits nodes in a syntax tree.
 */
class Pass {
 public:
  /**
   * @param message_context A message context which is shared by all handlers.
   */
  Pass(MessageContext& message_context);

  Pass(const Pass& other) = delete;
  Pass(Pass&& other) = delete;
  Pass& operator=(const Pass& other) = delete;
  Pass& operator=(Pass&& other) = delete;

  /**
   * @brief Adds a new handler.
   *
   * Handlers are all run in order.
   */
  void add_handler(std::unique_ptr<Handler>&& handler);

  /**
   * @brief Visits a node and all of its children.
   */
  template <typename TNode>
  void visit(std::shared_ptr<TNode>& input);

  /**
   * @brief Visits a node vector and all of its children.
   */
  template <typename TNode>
  void visit(std::vector<std::shared_ptr<TNode>>& input);

 private:
  std::reference_wrapper<MessageContext> message_context_;
  std::vector<std::reference_wrapper<const BaseNode>> stack_;
  std::vector<std::unique_ptr<Handler>> handlers_;
};
}  // namespace forge

#include "pass.tpp"
