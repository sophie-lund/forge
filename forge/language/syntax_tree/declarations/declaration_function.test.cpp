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

#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/values/value_literal_bool.hpp>
#include <forge/syntax_tree/domain/gtest_node_auto_assert.hpp>

using namespace forge;

TEST(language_syntax_tree_declarations_declaration_function, node_auto) {
  std::stringstream debug_formatter_stream;
  DebugFormatter debug_formatter(debug_formatter_stream);

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_DECLARATION_FUNCTION, debug_formatter, debug_formatter_stream,
      std::make_shared<DeclarationFunction>(
          SourceRange(), "f",
          std::vector<std::shared_ptr<DeclarationVariable>>(), nullptr,
          nullptr))));

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_DECLARATION_FUNCTION, debug_formatter, debug_formatter_stream,
      std::make_shared<DeclarationFunction>(
          SourceRange(), "f",
          std::vector<std::shared_ptr<DeclarationVariable>>{nullptr, nullptr},
          nullptr, nullptr))));

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_DECLARATION_FUNCTION, debug_formatter, debug_formatter_stream,
      std::make_shared<DeclarationFunction>(
          SourceRange(), "f",
          std::vector<std::shared_ptr<DeclarationVariable>>{
              std::make_shared<DeclarationVariable>(
                  SourceRange(), "a",
                  std::make_shared<TypeBasic>(SourceRange(),
                                              TypeBasicKind::bool_),
                  nullptr),
              std::make_shared<DeclarationVariable>(
                  SourceRange(), "b",
                  std::make_shared<TypeBasic>(SourceRange(),
                                              TypeBasicKind::bool_),
                  nullptr)},
          std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_),
          std::make_shared<StatementBlock>(
              SourceRange(),
              std::vector<std::shared_ptr<forge::BaseStatement>>())))));
}
