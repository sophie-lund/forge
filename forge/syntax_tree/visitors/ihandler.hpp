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
#include <forge/syntax_tree/operations/casting.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
class BaseNode;
class Pass;

/**
 * @brief An interface that handles the traversal of a node within a pass.
 */
class IHandler {
  friend class Pass;

 public:
  /**
   * @brief A set of parameters to be passed into a handler as input.
   *
   * @tparam TNode The type of node that is being visited.
   */
  template <typename TNode = BaseNode>
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
          const std::vector<std::shared_ptr<const BaseNode>>& stack,
          std::shared_ptr<TNode> node);

    Input(const Input& other) = delete;
    Input(Input&& other) = delete;
    Input& operator=(const Input& other) = delete;
    Input& operator=(Input&& other) = delete;

    /**
     * @brief Get the message context.
     */
    MessageContext& message_context() const;

    /**
     * @brief Get the stack of nodes.
     *
     * The item in the `0` index of the vector is the root node at the top of
     * the tree. The item in the last index of the vector is the direct parent
     * of the current node.
     */
    const std::vector<std::shared_ptr<const BaseNode>>& stack() const;

    /**
     * @brief Get the most directly surrounding node of type
     * @c TNodeSurrounding.
     */
    template <typename TNodeSurrounding>
    std::shared_ptr<const TNodeSurrounding> try_get_directly_surrounding()
        const;

    /**
     * @brief Get the node currently being visited.
     */
    std::shared_ptr<TNode> node() const;

   private:
    std::reference_wrapper<MessageContext> _message_context;
    std::reference_wrapper<const std::vector<std::shared_ptr<const BaseNode>>>
        stack_;
    std::shared_ptr<TNode> node_;
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
     * `Output(VisitorStatus::continue_, nullptr)`.
     */
    Output();

    /**
     * @brief Constructor with a custom status but no replacement.
     *
     * This is equivalent to `Output(status, nullptr)`.
     */
    explicit Output(VisitorStatus status);

    /**
     * @brief Constructor to replace the current node but continue traversal as
     * normal.
     *
     * It is equivalent to `Output(VisitorStatus::continue_,
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
    Output(VisitorStatus status, std::shared_ptr<BaseNode>&& replacement);

    Output(const Output& other) = delete;
    Output(Output&& other) = delete;
    Output& operator=(const Output& other) = delete;
    Output& operator=(Output&& other) = delete;

    /**
     * @brief Get the status.
     */
    VisitorStatus status() const;

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
    VisitorStatus status_;
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
  virtual Output on_enter(Input<>& input) = 0;

  /**
   * @brief A hook that is called when the node is left by the pass while
   * visiting.
   *
   * @param input The input for the handler.
   */
  virtual Output on_leave(Input<>& input) = 0;
};
}  // namespace forge

#include "ihandler.tpp"
