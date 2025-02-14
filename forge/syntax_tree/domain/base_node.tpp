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
namespace {
template <typename TBaseNode>
class HandlerForEachDirectChild : public Handler<TBaseNode> {
 public:
  HandlerForEachDirectChild(
      std::function<void(const TBaseNode&)> on_direct_child)
      : _on_direct_child(on_direct_child) {}

 protected:
  typename Handler<TBaseNode>::Output on_enter(
      typename Handler<TBaseNode>::Input& input) override {
    input.node().for_each_direct_child([this, &input](const TBaseNode& child) {
      _on_direct_child(input, child);
    });

    if (input.stack().empty()) {
      return typename Handler<TBaseNode>::Output();
    } else {
      return typename Handler<TBaseNode>::Output(
          HandlerOutputStatus::do_not_traverse_children);
    }
  }

  typename Handler<TBaseNode>::Output on_leave(
      typename Handler<TBaseNode>::Input&) override {
    return typename Handler<TBaseNode>::Output();
  }

 private:
  std::function<void(const TBaseNode&)> _on_direct_child;
};
}  // namespace

template <typename TBaseNode, typename TKind>
Node<TBaseNode, TKind>::Node(TKind&& kind,
                             std::optional<SourceRange>&& source_range)
    : kind(std::move(kind)), source_range(std::move(source_range)) {}

template <typename TBaseNode, typename TKind>
Node<TBaseNode, TKind>::~Node() {}

template <typename TBaseNode, typename TKind>
void Node<TBaseNode, TKind>::for_each_direct_child(
    std::function<void(const TBaseNode&)> on_direct_child) const {
  Pass<TBaseNode> pass;
  pass.add_handler(
      std::make_unique<HandlerForEachDirectChild<TBaseNode>>(on_direct_child));

  std::shared_ptr<TBaseNode> this_shared(this, [](TBaseNode*) {});

  pass.visit(this_shared);
}

template <typename TBaseNode, typename TKind>
bool Node<TBaseNode, TKind>::compare(const TBaseNode& other) const {
  if (kind != other.kind) {
    return false;
  }

  return on_compare(other);
}

template <typename TBaseNode, typename TKind>
std::shared_ptr<TBaseNode> Node<TBaseNode, TKind>::clone() const {
  return on_clone();
}

template <typename TBaseNode, typename TKind>
void Node<TBaseNode, TKind>::format_debug(
    DebugFormatter<TKind>& formatter) const {
  formatter.node_label(kind);
  on_format_debug(formatter);
  formatter.unindent();
}

template <typename TBaseNode, typename TKind>
std::shared_ptr<Scope<TBaseNode>>*
Node<TBaseNode, TKind>::on_get_scope_field_pointer() {
  return nullptr;
}

template <typename TBaseNode, typename TKind>
ScopeFlags Node<TBaseNode, TKind>::on_get_scope_flags() const {
  return SCOPE_FLAG_NONE;
}

template <typename TBaseNode, typename TKind>
void Node<TBaseNode, TKind>::on_resolve_symbol(std::shared_ptr<TBaseNode>) {}

template <typename TBaseNode, typename TKind>
std::optional<std::pair<SymbolMode, std::string>>
Node<TBaseNode, TKind>::on_get_symbol() const {
  return std::nullopt;
}
}  // namespace forge
