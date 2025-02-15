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
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/visitors/handler.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>

namespace forge {
namespace {
class HandlerForEachDirectChild : public Handler {
 public:
  HandlerForEachDirectChild(std::function<void(const Node&)> on_direct_child)
      : _on_direct_child(on_direct_child) {}

 protected:
  typename Handler::Output on_enter(typename Handler::Input& input) override {
    // input.node()->for_each_direct_child(
    //     [this, &input](const Node& child) { _on_direct_child(input, child);
    //     });

    if (input.stack().empty()) {
      return typename Handler::Output();
    } else {
      return typename Handler::Output(
          HandlerOutputStatus::do_not_traverse_children);
    }
  }

  typename Handler::Output on_leave(typename Handler::Input&) override {
    return typename Handler::Output();
  }

 private:
  std::function<void(const Node&)> _on_direct_child;
};
}  // namespace

Node::Node(NodeKind kind, std::optional<SourceRange>&& source_range)
    : kind(kind), source_range(std::move(source_range)) {}

Node::~Node() {}

// void Node::for_each_direct_child(
//     std::function<void(const Node&)> on_direct_child) const {
//   Pass pass;
//   pass.add_handler(
//       std::make_unique<HandlerForEachDirectChild>(on_direct_child));

//   std::shared_ptr<Node> this_shared(const_cast<Node*>(this), [](Node*) {});

//   pass.visit(this_shared);
// }

bool Node::compare(const Node& other) const {
  if (kind != other.kind) {
    return false;
  }

  return on_compare(other);
}

std::shared_ptr<Node> Node::clone() const { return on_clone(); }

void Node::format_debug(DebugFormatter& formatter) const {
  formatter.node_label(kind);
  on_format_debug(formatter);
  formatter.unindent();
}

std::shared_ptr<Scope>* Node::on_get_scope_field_pointer() { return nullptr; }

ScopeFlags Node::on_get_scope_flags() const { return SCOPE_FLAG_NONE; }

void Node::on_resolve_symbol(std::shared_ptr<Node>) {}

std::optional<std::pair<SymbolMode, std::string>> Node::on_get_symbol() const {
  return std::nullopt;
}
}  // namespace forge
