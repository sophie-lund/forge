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

#include <gtest/gtest.h>

#include <langtools/syntax_tree/scope/scope.hpp>

using namespace lt;

// TEST(syntax_tree_scope_scope, basic_operations_with_shadowing) {
//   Scope<int> scope(true);

//   ASSERT_FALSE(scope.contains("foo"));

//   ASSERT_TRUE(scope.add("foo", std::make_shared<int>(42)));
//   ASSERT_TRUE(scope.add("foo", std::make_shared<int>(43)));

//   ASSERT_TRUE(scope.contains("foo"));
//   ASSERT_EQ(scope.get("foo"), 43);

//   ASSERT_TRUE(scope.remove("foo"));
//   ASSERT_FALSE(scope.remove("foo"));
// }

// TEST(syntax_tree_scope_scope, basic_operations_without_shadowing) {
//   Scope<int> scope(false);

//   ASSERT_FALSE(scope.contains("foo"));

//   ASSERT_TRUE(scope.add("foo", std::make_shared<int>(42)));
//   ASSERT_FALSE(scope.add("foo", std::make_shared<int>(43)));

//   ASSERT_TRUE(scope.contains("foo"));
//   ASSERT_EQ(scope.get("foo"), 42);

//   ASSERT_TRUE(scope.remove("foo"));
//   ASSERT_FALSE(scope.remove("foo"));
// }
