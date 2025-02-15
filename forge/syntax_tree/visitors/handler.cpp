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

#include <forge/syntax_tree/visitors/handler.hpp>

namespace forge {
Handler::Input::Input(
    MessageContext& message_context,
    const std::vector<std::reference_wrapper<const BaseNode>>& stack,
    std::shared_ptr<BaseNode>& node)
    : _message_context(message_context), stack_(stack), node_(node) {}

MessageContext& Handler::Input::message_context() {
  return _message_context.get();
}

const std::vector<std::reference_wrapper<const BaseNode>>&
Handler::Input::stack() {
  return stack_.get();
}

std::shared_ptr<BaseNode>& Handler::Input::node() { return node_.get(); }

Handler::Output::Output() : status_(HandlerOutputStatus::continue_) {}

Handler::Output::Output(HandlerOutputStatus status) : status_(status) {}

Handler::Output::Output(std::shared_ptr<BaseNode>&& replacement)
    : status_(HandlerOutputStatus::continue_),
      replacement_(std::move(replacement)) {}

Handler::Output::Output(HandlerOutputStatus status,
                        std::shared_ptr<BaseNode>&& replacement)
    : status_(status), replacement_(std::move(replacement)) {}

HandlerOutputStatus Handler::Output::status() const { return status_; }

bool Handler::Output::has_replacement() const {
  return replacement_ != nullptr;
}

std::shared_ptr<BaseNode> Handler::Output::take_replacement() {
  return std::move(replacement_);
}

Handler::~Handler() {}
}  // namespace forge
