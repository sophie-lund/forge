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

#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>

namespace forge {
template <typename TBaseNode>
class GTestNodeAutoAssertHandler : public Handler<TBaseNode> {
 protected:
  virtual typename Handler<TBaseNode>::Output onEnter(
      typename Handler<TBaseNode>::Input&) override {
    return typename Handler<TBaseNode>::Output();
  }

  virtual typename Handler<TBaseNode>::Output onLeave(
      typename Handler<TBaseNode>::Input&) override {
    return typename Handler<TBaseNode>::Output();
  }
};

template <typename TNodeKind, typename TBaseNode>
::testing::AssertionResult nodeAutoAssert(
    const TNodeKind& kind, const DebugFormatter<TNodeKind>& debugFormatter,
    const std::stringstream& debugFormatterStream,
    const std::shared_ptr<TBaseNode>& node) {
  if (!node) {
    return ::testing::AssertionFailure() << "provided node is null";
  }

  if (node->kind != kind) {
    return ::testing::AssertionFailure() << "node kind mismatch";
  }

  MessageContext messageContext;
  Pass<TBaseNode> pass(messageContext);
  pass.addHandler(std::make_unique<GTestNodeAutoAssertHandler<TBaseNode>>());

  // This is OK because we're sure that the handler doesn't actually change
  // anything
  pass.visit(const_cast<std::shared_ptr<TBaseNode>&>(node));

  const_cast<std::stringstream&>(debugFormatterStream).str("");
  const_cast<DebugFormatter<TNodeKind>&>(debugFormatter).node(node);

  auto originalDebugFormatted =
      const_cast<std::stringstream&>(debugFormatterStream).str();

  if (originalDebugFormatted.empty()) {
    return ::testing::AssertionFailure()
           << "debug formatter did not output anything";
  }

  auto cloned = cloneNode(node);

  if (!cloned) {
    return ::testing::AssertionFailure() << "clone(...) returned null";
  }

  const_cast<std::stringstream&>(debugFormatterStream).str("");
  const_cast<DebugFormatter<TNodeKind>&>(debugFormatter).node(cloned);

  auto clonedDebugFormatted =
      const_cast<std::stringstream&>(debugFormatterStream).str();

  if (clonedDebugFormatted.empty()) {
    return ::testing::AssertionFailure()
           << "debug formatter did not output anything for clone";
  }

  if (originalDebugFormatted != clonedDebugFormatted) {
    return ::testing::AssertionFailure()
           << "debug formatter output for clone does not match "
              "original:\n\nOriginal:\n\n"
           << originalDebugFormatted << "\n\nClone:\n\n"
           << clonedDebugFormatted;
  }

  if (!compareNodes(node, cloned)) {
    return ::testing::AssertionFailure()
           << "node comparison returned false with clone";
  }

  return ::testing::AssertionSuccess();
}
}  // namespace forge
