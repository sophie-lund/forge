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

#include <langtools/core/tracing.hpp>
#include <langtools/messaging/message_context.hpp>
#include <langtools/syntax_tree/visitors/ihandler.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace lt {
/**
 * @brief A pass which visits nodes in a syntax tree.
 */
class Pass : public IVisitor {
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
  void add_handler(std::unique_ptr<IHandler>&& handler);

 protected:
  virtual VisitorStatus on_enter(std::shared_ptr<BaseNode>& node) final;
  virtual VisitorStatus on_leave(std::shared_ptr<BaseNode>& node) final;

 private:
  static void trace_entering(const BaseNode& input);
  static void trace_leaving(const BaseNode& input);

  std::reference_wrapper<MessageContext> message_context_;
  std::vector<std::shared_ptr<const BaseNode>> stack_;
  std::vector<std::unique_ptr<IHandler>> handlers_;

  VisitorStatus run_handlers_on_enter(std::shared_ptr<BaseNode>& input);
  VisitorStatus run_handlers_on_leave(std::shared_ptr<BaseNode>& input);
};
}  // namespace lt
