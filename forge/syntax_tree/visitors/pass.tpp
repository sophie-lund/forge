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

namespace forge {
template <typename TBaseNode, typename TKind>
class Node;

template <typename TBaseNode>
Pass<TBaseNode>::Pass(MessageContext& message_context)
    : message_context_(std::ref(message_context)) {}

template <typename TBaseNode>
void Pass<TBaseNode>::add_handler(
    std::unique_ptr<Handler<TBaseNode>>&& handler) {
  handlers_.emplace_back(std::move(handler));
}

template <typename TBaseNode>
template <typename TNode>
void Pass<TBaseNode>::visit(std::shared_ptr<TNode>& input) {
  // If the input node is null, then there is nothing to do
  if (!input) {
    return;
  }

  std::shared_ptr<TBaseNode> input_casted =
      std::static_pointer_cast<TBaseNode>(input);

  bool do_not_traverse_children = false;

  // Run the enter handlers
  for (auto& handler : handlers_) {
    typename Handler<TBaseNode>::Input input_wrapper(message_context_.get(),
                                                     stack_, input_casted);

    typename Handler<TBaseNode>::Output output =
        handler->on_enter(input_wrapper);

    if (output.status() == HandlerOutputStatus::do_not_traverse_children) {
      do_not_traverse_children = true;
    } else if (output.status() == HandlerOutputStatus::halt_traversal) {
      return;
    }

    // If a replacement node is returned, swap it in
    if (output.has_replacement()) {
      input_casted = output.take_replacement();
    }
  }

  if (!do_not_traverse_children) {
    // Update internal properties
    stack_.emplace_back(std::ref(*input_casted));

    // Visit any children
    static_cast<Node<TBaseNode, typename TBaseNode::Kind>&>(*input_casted)
        .on_accept(*this);

    // Update internal properties
    stack_.pop_back();
  }

  // Run the leave handlers
  for (auto& handler : handlers_) {
    typename Handler<TBaseNode>::Input input_wrapper(message_context_.get(),
                                                     stack_, input_casted);

    typename Handler<TBaseNode>::Output output =
        handler->on_leave(input_wrapper);

    if (output.status() == HandlerOutputStatus::halt_traversal) {
      return;
    }

    // If a replacement node is returned, swap it in
    if (output.has_replacement()) {
      input_casted = std::static_pointer_cast<TNode>(output.take_replacement());
    }
  }

  input = std::static_pointer_cast<TNode>(input_casted);
}

template <typename TBaseNode>
template <typename TNode>
void Pass<TBaseNode>::visit(std::vector<std::shared_ptr<TNode>>& input) {
  for (auto& node : input) {
    visit(node);
  }
}
}  // namespace forge
