// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <forge/messaging/MessageContext.hpp>
#include <forge/syntaxtree/Handler.hpp>

namespace sycamore::syntaxtree {
/**
 * @brief A pass which visits nodes in a syntax tree.
 */
template <typename TBaseNode>
class Pass {
 public:
  /**
   * @param messageContext A message context which is shared by all handlers.
   */
  Pass(messaging::MessageContext& messageContext);

  Pass(const Pass& other) = delete;
  Pass(Pass&& other) = delete;
  Pass& operator=(const Pass& other) = delete;
  Pass& operator=(Pass&& other) = delete;

  /**
   * @brief Adds a new handler.
   *
   * Handlers are all run in order.
   */
  void addHandler(std::unique_ptr<Handler<TBaseNode>>&& handler);

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
  std::reference_wrapper<messaging::MessageContext> messageContext_;
  std::vector<std::reference_wrapper<const TBaseNode>> stack_;
  std::vector<std::unique_ptr<Handler<TBaseNode>>> handlers_;
};
}  // namespace sycamore::syntaxtree

#include "Pass.tpp"
