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

#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

#ifndef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
#error \
    "Google Test is not included and is required by this header - please include <gtest/gtest.h> before including this header"
#endif

// Used for intellisense in editors
#include <gtest/gtest.h>

namespace forge {
/**
 * @brief Runs automatic tests on a node class.
 *
 * @tparam TNode The type of node to test.
 * @param kind The expected kind for the node.
 * @param debug_formatter A debug formatter to use.
 * @param debug_formatter_stream The string stream that the debug formatter is
 * configured to use.
 * @param node An example of the node to be tested.
 */
template <typename TNode>
::testing::AssertionResult gtest_node_auto_assert(
    const NodeKind& kind, const DebugFormatter& debug_formatter,
    const std::stringstream& debug_formatter_stream,
    const std::shared_ptr<TNode>& node);
}  // namespace forge

#include "gtest_node_auto_assert.tpp"
