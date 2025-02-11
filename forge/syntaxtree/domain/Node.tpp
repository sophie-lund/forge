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
  HandlerForEachDirectChild(std::function<void(const TBaseNode&)> onDirectChild)
      : onDirectChild_(onDirectChild) {}

 protected:
  typename Handler<TBaseNode>::Output onEnter(
      typename Handler<TBaseNode>::Input& input) override {
    input.node().forEachDirectChild([this, &input](const TBaseNode& child) {
      onDirectChild_(input, child);
    });

    if (input.stack().empty()) {
      return typename Handler<TBaseNode>::Output();
    } else {
      return typename Handler<TBaseNode>::Output(
          HandlerOutputStatus::DoNotTraverseChildren);
    }
  }

  typename Handler<TBaseNode>::Output onLeave(
      typename Handler<TBaseNode>::Input&) override {
    return typename Handler<TBaseNode>::Output();
  }

 private:
  std::function<void(const TBaseNode&)> onDirectChild_;
};
}  // namespace

template <typename TBaseNode, typename TKind>
Node<TBaseNode, TKind>::Node(TKind&& kind,
                             std::optional<SourceRange>&& sourceRange)
    : kind(std::move(kind)), sourceRange(std::move(sourceRange)) {}

template <typename TBaseNode, typename TKind>
Node<TBaseNode, TKind>::~Node() {}

template <typename TBaseNode, typename TKind>
void Node<TBaseNode, TKind>::forEachDirectChild(
    std::function<void(const TBaseNode&)> onDirectChild) const {
  Pass<TBaseNode> pass;
  pass.addHandler(
      std::make_unique<HandlerForEachDirectChild<TBaseNode>>(onDirectChild));

  std::shared_ptr<TBaseNode> thisShared(this, [](TBaseNode*) {});

  pass.visit(thisShared);
}

template <typename TBaseNode, typename TKind>
std::shared_ptr<Scope<TBaseNode>>*
Node<TBaseNode, TKind>::onGetScopeFieldPointer() {
  return nullptr;
}

template <typename TBaseNode, typename TKind>
ScopeFlags Node<TBaseNode, TKind>::onGetScopeFlags() const {
  return SCOPE_FLAG_NONE;
}

template <typename TBaseNode, typename TKind>
void Node<TBaseNode, TKind>::onResolveSymbol(std::shared_ptr<TBaseNode>) {}

template <typename TBaseNode, typename TKind>
std::optional<std::pair<SymbolMode, std::string>>
Node<TBaseNode, TKind>::onGetSymbol() const {
  return std::nullopt;
}
}  // namespace forge
