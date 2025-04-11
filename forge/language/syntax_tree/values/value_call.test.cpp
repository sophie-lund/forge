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

#include <forge/language/syntax_tree/values/value_call.hpp>
#include <forge/language/syntax_tree/values/value_literal_bool.hpp>
#include <forge/syntax_tree/domain/gtest_node_auto_assert.hpp>

using namespace forge;

TEST(language_syntax_tree_values_value_call, node_auto) {
  std::stringstream debug_formatter_stream;
  DebugFormatter debug_formatter(debug_formatter_stream);

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_VALUE_CALL, debug_formatter, debug_formatter_stream,
      std::make_shared<ValueCall>(SourceRange(), nullptr,
                                  std::vector<std::shared_ptr<BaseValue>>()))));

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_VALUE_CALL, debug_formatter, debug_formatter_stream,
      std::make_shared<ValueCall>(
          SourceRange(), nullptr,
          std::vector<std::shared_ptr<BaseValue>>{nullptr, nullptr}))));

  EXPECT_TRUE((gtest_node_auto_assert(
      NODE_VALUE_CALL, debug_formatter, debug_formatter_stream,
      std::make_shared<ValueCall>(
          SourceRange(),
          std::make_shared<ValueLiteralBool>(SourceRange(), true),
          std::vector<std::shared_ptr<BaseValue>>{
              std::make_shared<ValueLiteralBool>(SourceRange(), true),
              std::make_shared<ValueLiteralBool>(SourceRange(), true)}))));
}
