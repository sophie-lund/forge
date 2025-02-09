// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file GTestNodeAutoAssert.hpp
 *
 * @brief Helper methods for testing syntax trees with Google Test.
 */

#ifndef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
#error \
    "Google Test is not included and is required by this header - please include <gtest/gtest.h> before including this header"
#endif

// Used for intellisense in editors
#include <gtest/gtest.h>

namespace sycamore::syntaxtree {
/**
 * @brief Runs automatic tests on a node.
 */
template <typename TNode>
::testing::AssertionResult nodeAutoAssert(std::shared_ptr<TNode>&& node);
}  // namespace sycamore::syntaxtree

#include "GTestNodeAutoAssert.tpp"