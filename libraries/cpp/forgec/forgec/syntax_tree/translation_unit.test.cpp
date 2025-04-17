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

#include <forgec/syntax_tree/declarations/declaration_variable.hpp>
#include <forgec/syntax_tree/translation_unit.hpp>
#include <forgec/syntax_tree/types/type_basic.hpp>
#include <langtools/syntax_tree/domain/gtest_node_auto_assert.hpp>

using namespace forge;

TEST(language_syntax_tree_translation_unit, node_auto) {
  std::stringstream debug_formatter_stream;
  lt::DebugFormatter debug_formatter(debug_formatter_stream);

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_TRANSLATION_UNIT, debug_formatter, debug_formatter_stream,
      std::make_shared<TranslationUnit>(
          lt::SourceRange(),
          std::vector<std::shared_ptr<BaseDeclaration>>()))));

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_TRANSLATION_UNIT, debug_formatter, debug_formatter_stream,
      std::make_shared<TranslationUnit>(
          lt::SourceRange(),
          std::vector<std::shared_ptr<BaseDeclaration>>{nullptr, nullptr}))));

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_TRANSLATION_UNIT, debug_formatter, debug_formatter_stream,
      std::make_shared<TranslationUnit>(
          lt::SourceRange(),
          std::vector<std::shared_ptr<BaseDeclaration>>{
              std::make_shared<DeclarationVariable>(
                  lt::SourceRange(), "b",
                  std::make_shared<TypeBasic>(lt::SourceRange(),
                                              TypeBasicKind::bool_),
                  nullptr),
              std::make_shared<DeclarationVariable>(
                  lt::SourceRange(), "b",
                  std::make_shared<TypeBasic>(lt::SourceRange(),
                                              TypeBasicKind::bool_),
                  nullptr)}))));
}
