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
class GTestNodeAutoAssertHandler : public IHandler {
 protected:
  virtual Output on_enter(Input<>&) final { return Output(); }

  virtual Output on_leave(Input<>&) final { return Output(); }
};

template <typename TNode>
::testing::AssertionResult gtest_node_auto_assert(
    const NodeKind& kind, const DebugFormatter& debug_formatter,
    const std::stringstream& debug_formatter_stream,
    const std::shared_ptr<TNode>& node) {
  if (!node) {
    return ::testing::AssertionFailure() << "provided node is null";
  }

  if (node->kind != kind) {
    return ::testing::AssertionFailure() << "node kind mismatch";
  }

  MessageContext message_context;
  Pass pass(message_context);
  pass.add_handler(std::make_unique<GTestNodeAutoAssertHandler>());

  // This is OK because we're sure that the handler doesn't actually change
  // anything
  pass.visit(const_cast<std::shared_ptr<TNode>&>(node));

  const_cast<std::stringstream&>(debug_formatter_stream).str("");
  const_cast<DebugFormatter&>(debug_formatter).node(node);

  auto original_debug_formatted =
      const_cast<std::stringstream&>(debug_formatter_stream).str();

  if (original_debug_formatted.empty()) {
    return ::testing::AssertionFailure()
           << "debug formatter did not output anything";
  }

  auto cloned = clone_node(node);

  if (!cloned) {
    return ::testing::AssertionFailure() << "clone(...) returned null";
  }

  const_cast<std::stringstream&>(debug_formatter_stream).str("");
  const_cast<DebugFormatter&>(debug_formatter).node(cloned);

  auto cloned_debug_formatted =
      const_cast<std::stringstream&>(debug_formatter_stream).str();

  if (cloned_debug_formatted.empty()) {
    return ::testing::AssertionFailure()
           << "debug formatter did not output anything for clone";
  }

  if (original_debug_formatted != cloned_debug_formatted) {
    return ::testing::AssertionFailure()
           << "debug formatter output for clone does not match "
              "original:\n\nOriginal:\n\n"
           << original_debug_formatted << "\n\nClone:\n\n"
           << cloned_debug_formatted;
  }

  if (!compare_nodes(node, cloned)) {
    return ::testing::AssertionFailure()
           << "node comparison returned false with clone";
  }

  return ::testing::AssertionSuccess();
}
}  // namespace forge
