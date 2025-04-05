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
template <typename TNode>
IHandler::Input<TNode>::Input(
    MessageContext& message_context,
    const std::vector<std::shared_ptr<const BaseNode>>& stack,
    std::shared_ptr<TNode> node)
    : _message_context(message_context), stack_(stack), node_(node) {}

template <typename TNode>
MessageContext& IHandler::Input<TNode>::message_context() const {
  return _message_context.get();
}

template <typename TNode>
const std::vector<std::shared_ptr<const BaseNode>>&
IHandler::Input<TNode>::stack() const {
  return stack_.get();
}

template <typename TNode>
template <typename TNodeSurrounding>
std::shared_ptr<const TNodeSurrounding>
IHandler::Input<TNode>::try_get_directly_surrounding() const {
  for (auto i = stack().rbegin(); i != stack().rend(); i++) {
    if (auto node_casted = try_cast_node<const TNodeSurrounding>(*i);
        node_casted) {
      return node_casted;
    }
  }

  return nullptr;
}

template <typename TNode>
std::shared_ptr<TNode> IHandler::Input<TNode>::node() const {
  return node_;
}
}  // namespace forge
