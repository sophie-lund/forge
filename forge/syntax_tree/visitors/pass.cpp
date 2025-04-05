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

#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>

namespace forge {
Pass::Pass(MessageContext& message_context)
    : message_context_(std::ref(message_context)) {}

void Pass::add_handler(std::unique_ptr<IHandler>&& handler) {
  handlers_.emplace_back(std::move(handler));
}

VisitorStatus Pass::on_enter(std::shared_ptr<BaseNode>& node) {
  trace_entering(*node);

  VisitorStatus on_enter_status = run_handlers_on_enter(node);

  stack_.emplace_back(node);

  return on_enter_status;
}

VisitorStatus Pass::on_leave(std::shared_ptr<BaseNode>& node) {
  trace_leaving(*node);

  stack_.pop_back();

  // Run the leave handlers
  VisitorStatus on_leave_status = run_handlers_on_leave(node);

  trace_dedent();

  return on_leave_status;
}

void Pass::trace_entering(const BaseNode& input) {
  trace("Pass") << "entering ";
  input.format_brief(trace_stream());
  trace_stream() << std::endl;
  trace_indent();
}

void Pass::trace_leaving(const BaseNode& input) {
  trace_dedent();
  trace("Pass") << "leaving ";
  input.format_brief(trace_stream());
  trace_stream() << std::endl;
  trace_indent();
}

VisitorStatus Pass::run_handlers_on_enter(std::shared_ptr<BaseNode>& input) {
  bool do_not_traverse_children = false;

  for (auto& handler : handlers_) {
    IHandler::Input input_wrapper(message_context_.get(), stack_, input);

    IHandler::Output output = handler->on_enter(input_wrapper);

    if (output.status() == VisitorStatus::do_not_traverse_children) {
      do_not_traverse_children = true;
    } else if (output.status() == VisitorStatus::halt_traversal) {
      return VisitorStatus::halt_traversal;
    }

    // If a replacement node is returned, swap it in
    if (output.has_replacement()) {
      input = output.take_replacement();
    }
  }

  if (do_not_traverse_children) {
    return VisitorStatus::do_not_traverse_children;
  } else {
    return VisitorStatus::continue_;
  }
}

VisitorStatus Pass::run_handlers_on_leave(std::shared_ptr<BaseNode>& input) {
  for (auto& handler : handlers_) {
    IHandler::Input input_wrapper(message_context_.get(), stack_, input);

    IHandler::Output output = handler->on_leave(input_wrapper);

    if (output.status() == VisitorStatus::halt_traversal) {
      return VisitorStatus::halt_traversal;
    }

    // If a replacement node is returned, swap it in
    if (output.has_replacement()) {
      input = output.take_replacement();
    }
  }

  return VisitorStatus::continue_;
}
}  // namespace forge
