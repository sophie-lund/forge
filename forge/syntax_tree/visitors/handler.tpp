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
template <typename TBaseNode>
Handler<TBaseNode>::Input::Input(
    MessageContext& message_context,
    const std::vector<std::reference_wrapper<const TBaseNode>>& stack,
    std::shared_ptr<TBaseNode>& node)
    : _message_context(message_context), stack_(stack), node_(node) {}

template <typename TBaseNode>
MessageContext& Handler<TBaseNode>::Input::message_context() {
  return _message_context.get();
}

template <typename TBaseNode>
const std::vector<std::reference_wrapper<const TBaseNode>>&
Handler<TBaseNode>::Input::stack() {
  return stack_.get();
}

template <typename TBaseNode>
std::shared_ptr<TBaseNode>& Handler<TBaseNode>::Input::node() {
  return node_.get();
}

template <typename TBaseNode>
Handler<TBaseNode>::Output::Output()
    : status_(HandlerOutputStatus::continue_) {}

template <typename TBaseNode>
Handler<TBaseNode>::Output::Output(HandlerOutputStatus status)
    : status_(status) {}

template <typename TBaseNode>
Handler<TBaseNode>::Output::Output(std::shared_ptr<TBaseNode>&& replacement)
    : status_(HandlerOutputStatus::continue_),
      replacement_(std::move(replacement)) {}

template <typename TBaseNode>
Handler<TBaseNode>::Output::Output(HandlerOutputStatus status,
                                   std::shared_ptr<TBaseNode>&& replacement)
    : status_(status), replacement_(std::move(replacement)) {}

template <typename TBaseNode>
HandlerOutputStatus Handler<TBaseNode>::Output::status() const {
  return status_;
}

template <typename TBaseNode>
bool Handler<TBaseNode>::Output::has_replacement() const {
  return replacement_ != nullptr;
}

template <typename TBaseNode>
std::shared_ptr<TBaseNode> Handler<TBaseNode>::Output::take_replacement() {
  return std::move(replacement_);
}

template <typename TBaseNode>
Handler<TBaseNode>::~Handler() {}
}  // namespace forge
