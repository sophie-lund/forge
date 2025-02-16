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

/**
 * The different statuses that a handler can return.
 */
enum class HandlerOutputStatus {
  /**
   * The traversal should continue uninterrupted.
   */
  continue_,

  /**
   * The traversal should not traverse the children of the current node, but
   * should continue down other branches of the node tree.
   */
  do_not_traverse_children,

  /**
   * Traversal should stop here and not go over any other nodes.
   */
  halt_traversal,
};

/**
 * @brief An interface that handles the traversal of a node within a pass.
 */
class IHandler {
  friend class Pass;

 public:
  /**
   * @brief A set of parameters to be passed into a handler as input.
   */
  class Input {
   public:
    /**
     * @brief Constructor.
     *
     * @param message_context The context used to emit messages from validation
     *                        and such.
     * @param stack The stack of parent nodes that have been visited so far. The
     *              item in the `0` index of the vector is the root node at the
     *              top of the tree. The item in the last index of the vector is
     *              the direct parent of the current node.
     * @param node The node that is being visited.
     */
    Input(MessageContext& message_context,
          const std::vector<std::reference_wrapper<const BaseNode>>& stack,
          std::shared_ptr<BaseNode>& node);

    Input(const Input& other) = delete;
    Input(Input&& other) = delete;
    Input& operator=(const Input& other) = delete;
    Input& operator=(Input&& other) = delete;

    /**
     * @brief Get the message context.
     */
    MessageContext& message_context();

    /**
     * @brief Get the stack of nodes.
     *
     * The item in the `0` index of the vector is the root node at the top of
     * the tree. The item in the last index of the vector is the direct parent
     * of the current node.
     */
    const std::vector<std::reference_wrapper<const BaseNode>>& stack();

    /**
     * @brief Get the node currently being visited.
     */
    std::shared_ptr<BaseNode>& node();

   private:
    std::reference_wrapper<MessageContext> _message_context;
    std::reference_wrapper<
        const std::vector<std::reference_wrapper<const BaseNode>>>
        stack_;
    std::reference_wrapper<std::shared_ptr<BaseNode>> node_;
  };

  /**
   * @brief A compound return type for handlers to provide as output.
   */
  class Output {
   public:
    /**
     * @brief Default constructor.
     *
     * This will create an output that does not replace the current node and
     * will continue traversal as normal. It is equivalent to
     * `Output(HandlerOutputStatus::continue_, nullptr)`.
     */
    Output();

    /**
     * @brief Constructor with a custom status but no replacement.
     *
     * This is equivalent to `Output(status, nullptr)`.
     */
    explicit Output(HandlerOutputStatus status);

    /**
     * @brief Constructor to replace the current node but continue traversal as
     * normal.
     *
     * It is equivalent to `Output(HandlerOutputStatus::continue_,
     * replacement)`.
     */
    explicit Output(std::shared_ptr<BaseNode>&& replacement);

    /**
     * @brief Full constructor.
     *
     * @param status The status returned by the handler which directs how
     *               traversal will continue.
     * @param replacement An optional node to use to replace the current one.
     *                    Leave this as `nullptr` to not replace the node.
     */
    Output(HandlerOutputStatus status, std::shared_ptr<BaseNode>&& replacement);

    Output(const Output& other) = delete;
    Output(Output&& other) = default;
    Output& operator=(const Output& other) = delete;
    Output& operator=(Output&& other) = default;

    /**
     * @brief Get the status.
     */
    HandlerOutputStatus status() const;

    /**
     * @brief Checks if the node is to be replaced.
     */
    bool has_replacement() const;

    /**
     * @brief Takes the replacement node and nulls-out the replacement field in
     * this output object.
     */
    std::shared_ptr<BaseNode> take_replacement();

   private:
    HandlerOutputStatus status_;
    std::shared_ptr<BaseNode> replacement_;
  };

  /**
   * @brief Default constructor.
   */
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
   * @param input The input for the handler.
   */
  virtual Output on_enter(Input& input) = 0;

  /**
   * @brief A hook that is called when the node is left by the pass while
   * visiting.
   *
   * @param input The input for the handler.
   */
  virtual Output on_leave(Input& input) = 0;
};
}  // namespace forge
