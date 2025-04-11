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

#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/syntax_tree/operations/casting.hpp>

using namespace forge;

TEST(syntax_tree_operations_casting, cast_null_to_null) {
  std::shared_ptr<BaseNode> node = nullptr;

  std::shared_ptr<TypeBasic> casted_node = try_cast_node<TypeBasic>(node);

  ASSERT_EQ(casted_node, nullptr);
}

TEST(syntax_tree_operations_casting, cast_success) {
  std::shared_ptr<BaseNode> node =
      std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);

  std::shared_ptr<TypeBasic> casted_node = try_cast_node<TypeBasic>(node);

  ASSERT_EQ(casted_node.get(), node.get());
}

TEST(syntax_tree_operations_casting, cast_failure) {
  std::shared_ptr<BaseNode> node =
      std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);

  std::shared_ptr<TypeSymbol> casted_node = try_cast_node<TypeSymbol>(node);

  ASSERT_EQ(casted_node, nullptr);
}
