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
    const std::vector<std::reference_wrapper<const BaseNode>>& stack,
    std::shared_ptr<TNode> node)
    : _message_context(message_context), stack_(stack), node_(node) {}

template <typename TNode>
MessageContext& IHandler::Input<TNode>::message_context() {
  return _message_context.get();
}

template <typename TNode>
const std::vector<std::reference_wrapper<const BaseNode>>&
IHandler::Input<TNode>::stack() {
  return stack_.get();
}

template <typename TNode>
std::shared_ptr<TNode> IHandler::Input<TNode>::node() {
  return node_;
}
}  // namespace forge
