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
Pass<TBaseNode>::Pass(MessageContext& messageContext)
    : messageContext_(std::ref(messageContext)) {}

template <typename TBaseNode>
void Pass<TBaseNode>::addHandler(
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

  std::shared_ptr<TBaseNode> inputCasted =
      std::static_pointer_cast<TBaseNode>(input);

  bool doNotTraverseChildren = false;

  // Run the enter handlers
  for (auto& handler : handlers_) {
    typename Handler<TBaseNode>::Input inputWrapper(messageContext_.get(),
                                                    stack_, inputCasted);

    typename Handler<TBaseNode>::Output output = handler->onEnter(inputWrapper);

    if (output.status() == HandlerOutputStatus::DoNotTraverseChildren) {
      doNotTraverseChildren = true;
    } else if (output.status() == HandlerOutputStatus::HaltTraversal) {
      return;
    }

    // If a replacement node is returned, swap it in
    if (output.hasReplacement()) {
      inputCasted = output.takeReplacement();
    }
  }

  if (!doNotTraverseChildren) {
    // Update internal properties
    stack_.emplace_back(std::ref(*inputCasted));

    // Visit any children
    static_cast<Node<TBaseNode, typename TBaseNode::Kind>&>(*inputCasted)
        .onAccept(*this);

    // Update internal properties
    stack_.pop_back();
  }

  // Run the leave handlers
  for (auto& handler : handlers_) {
    typename Handler<TBaseNode>::Input inputWrapper(messageContext_.get(),
                                                    stack_, inputCasted);

    typename Handler<TBaseNode>::Output output = handler->onLeave(inputWrapper);

    if (output.status() == HandlerOutputStatus::HaltTraversal) {
      return;
    }

    // If a replacement node is returned, swap it in
    if (output.hasReplacement()) {
      inputCasted = std::static_pointer_cast<TNode>(output.takeReplacement());
    }
  }

  input = std::static_pointer_cast<TNode>(inputCasted);
}

template <typename TBaseNode>
template <typename TNode>
void Pass<TBaseNode>::visit(std::vector<std::shared_ptr<TNode>>& input) {
  for (auto& node : input) {
    visit(node);
  }
}
}  // namespace forge
