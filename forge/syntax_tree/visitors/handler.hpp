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

namespace forge {
class BaseNode;
class Pass;

enum class HandlerOutputStatus {
  continue_,
  do_not_traverse_children,
  halt_traversal,
};

/**
 * @brief An object that handles the traversal of a node within a pass.
 */
class IHandler {
  friend class Pass;

 public:
  class Input {
   public:
    Input(MessageContext& message_context,
          const std::vector<std::reference_wrapper<const BaseNode>>& stack,
          std::shared_ptr<BaseNode>& node);

    Input(const Input& other) = delete;
    Input(Input&& other) = delete;
    Input& operator=(const Input& other) = delete;
    Input& operator=(Input&& other) = delete;

    MessageContext& message_context();
    const std::vector<std::reference_wrapper<const BaseNode>>& stack();
    std::shared_ptr<BaseNode>& node();

   private:
    std::reference_wrapper<MessageContext> _message_context;
    std::reference_wrapper<
        const std::vector<std::reference_wrapper<const BaseNode>>>
        stack_;
    std::reference_wrapper<std::shared_ptr<BaseNode>> node_;
  };

  class Output {
   public:
    Output();
    explicit Output(HandlerOutputStatus status);
    explicit Output(std::shared_ptr<BaseNode>&& replacement);
    Output(HandlerOutputStatus status, std::shared_ptr<BaseNode>&& replacement);

    Output(const Output& other) = delete;
    Output(Output&& other) = default;
    Output& operator=(const Output& other) = delete;
    Output& operator=(Output&& other) = default;

    HandlerOutputStatus status() const;
    bool has_replacement() const;
    std::shared_ptr<BaseNode> take_replacement();

   private:
    HandlerOutputStatus status_;
    std::shared_ptr<BaseNode> replacement_;
  };

  IHandler() = default;

  virtual ~IHandler() = 0;

  IHandler(const IHandler& other) = delete;
  IHandler(IHandler&& other) = delete;
  IHandler& operator=(const IHandler& other) = delete;
  IHandler& operator=(IHandler&& other) = delete;

 protected:
  /**
   * @brief A hook that is called when the node is entered by the pass while
   * visiting.
   *
   * @param message_context The context for messages.
   * @param stack The stack of nodes that have been visited so far.
   * @param node The node that is being entered.
   */
  virtual Output on_enter(Input& input) = 0;

  /**
   * @brief A hook that is called when the node is left by the pass while
   * visiting.
   *
   * @param message_context The context for messages.
   * @param stack The stack of nodes that have been visited so far.
   * @param node The node that is being left.
   */
  virtual Output on_leave(Input& input) = 0;
};
}  // namespace forge
