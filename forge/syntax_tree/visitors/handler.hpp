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
template <typename TBaseNode>
class Pass;

enum class HandlerOutputStatus {
  Continue,
  DoNotTraverseChildren,
  HaltTraversal,
};

/**
 * @brief An object that handles the traversal of a node within a pass.
 */
template <typename TBaseNode>
class Handler {
  friend class Pass<TBaseNode>;

 public:
  class Input {
   public:
    Input(MessageContext& messageContext,
          const std::vector<std::reference_wrapper<const TBaseNode>>& stack,
          std::shared_ptr<TBaseNode>& node);

    Input(const Input& other) = delete;
    Input(Input&& other) = delete;
    Input& operator=(const Input& other) = delete;
    Input& operator=(Input&& other) = delete;

    MessageContext& messageContext();
    const std::vector<std::reference_wrapper<const TBaseNode>>& stack();
    std::shared_ptr<TBaseNode>& node();

   private:
    std::reference_wrapper<MessageContext> _messageContext;
    std::reference_wrapper<
        const std::vector<std::reference_wrapper<const TBaseNode>>>
        stack_;
    std::reference_wrapper<std::shared_ptr<TBaseNode>> node_;
  };

  class Output {
   public:
    Output();
    explicit Output(HandlerOutputStatus status);
    explicit Output(std::shared_ptr<TBaseNode>&& replacement);
    Output(HandlerOutputStatus status,
           std::shared_ptr<TBaseNode>&& replacement);

    Output(const Output& other) = delete;
    Output(Output&& other) = default;
    Output& operator=(const Output& other) = delete;
    Output& operator=(Output&& other) = default;

    HandlerOutputStatus status() const;
    bool hasReplacement() const;
    std::shared_ptr<TBaseNode> takeReplacement();

   private:
    HandlerOutputStatus status_;
    std::shared_ptr<TBaseNode> replacement_;
  };

  Handler() = default;

  virtual ~Handler() = 0;

  Handler(const Handler& other) = delete;
  Handler(Handler&& other) = delete;
  Handler& operator=(const Handler& other) = delete;
  Handler& operator=(Handler&& other) = delete;

 protected:
  /**
   * @brief A hook that is called when the node is entered by the pass while
   * visiting.
   *
   * @param messageContext The context for messages.
   * @param stack The stack of nodes that have been visited so far.
   * @param node The node that is being entered.
   */
  virtual Output onEnter(Input& input) = 0;

  /**
   * @brief A hook that is called when the node is left by the pass while
   * visiting.
   *
   * @param messageContext The context for messages.
   * @param stack The stack of nodes that have been visited so far.
   * @param node The node that is being left.
   */
  virtual Output onLeave(Input& input) = 0;
};
}  // namespace forge

#include "handler.tpp"
