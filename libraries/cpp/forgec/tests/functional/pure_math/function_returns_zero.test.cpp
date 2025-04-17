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

#include <forgec/testing/integration_test_harness.hpp>

using namespace forge;

TEST(integration_pure_math_function_returns_zero, simple) {
  runIntegrationTest(
      {.source = "func f() -> i32 {\n"
                 "  return 0;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = []\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = signed_int\n"
           "        bit_width = 32\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_literal_number]\n"
           "              type = [type_with_bit_width]\n"
           "                type_with_bit_width_kind = signed_int\n"
           "                bit_width = 32\n"
           "                is_const = false\n"
           "              value = 0",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int (*)()>("f");

         ASSERT_EQ(f(), 0);
       }});
}

TEST(integration_pure_math_function_returns_zero, error_return_void) {
  runIntegrationTest({
      .source = "func f() -> i32 {\n"
                "  return;\n"
                "}\n",
      .expected_state = IntegrationTestOptionsState::errors_after_passes,
      .expected_syntax_tree_debug =
          "[translation_unit]\n"
          "  declarations = \n"
          "    [0] = [declaration_function]\n"
          "      name = \"f\"\n"
          "      args = []\n"
          "      return_type = [type_with_bit_width]\n"
          "        type_with_bit_width_kind = signed_int\n"
          "        bit_width = 32\n"
          "        is_const = false\n"
          "      body = [statement_block]\n"
          "        statements = \n"
          "          [0] = [statement_basic]\n"
          "            statement_basic_kind = return_void",
      .expected_message_report =
          "--:2:3 - error ETY009: non-void function must return a value\n"
          "\n"
          "2  return;\n"
          "   ^^^^^^^\n"
          "\n"
          "1 error\n",
  });
}

TEST(integration_pure_math_function_returns_zero, error_return_float) {
  runIntegrationTest({
      .source = "func f() -> i32 {\n"
                "  return 3.4;\n"
                "}\n",
      .expected_state = IntegrationTestOptionsState::errors_after_passes,
      .expected_syntax_tree_debug =
          "[translation_unit]\n"
          "  declarations = \n"
          "    [0] = [declaration_function]\n"
          "      name = \"f\"\n"
          "      args = []\n"
          "      return_type = [type_with_bit_width]\n"
          "        type_with_bit_width_kind = signed_int\n"
          "        bit_width = 32\n"
          "        is_const = false\n"
          "      body = [statement_block]\n"
          "        statements = \n"
          "          [0] = [statement_value]\n"
          "            statement_value_kind = return\n"
          "            value = [value_literal_number]\n"
          "              type = [type_with_bit_width]\n"
          "                type_with_bit_width_kind = float\n"
          "                bit_width = 64\n"
          "                is_const = false\n"
          "              value = 3.4",
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to i32\n"
                                 "\n"
                                 "2  return 3.4;\n"
                                 "          ^^^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(integration_pure_math_function_returns_zero, error_no_return_type) {
  runIntegrationTest({
      .source = "func f() {\n"
                "  return 0;\n"
                "}\n",
      .expected_state = IntegrationTestOptionsState::errors_after_passes,
      .expected_syntax_tree_debug =
          "[translation_unit]\n"
          "  declarations = \n"
          "    [0] = [declaration_function]\n"
          "      name = \"f\"\n"
          "      args = []\n"
          "      return_type = null\n"
          "      body = [statement_block]\n"
          "        statements = \n"
          "          [0] = [statement_value]\n"
          "            statement_value_kind = return\n"
          "            value = [value_literal_number]\n"
          "              type = [type_with_bit_width]\n"
          "                type_with_bit_width_kind = signed_int\n"
          "                bit_width = 32\n"
          "                is_const = false\n"
          "              value = 0",
      .expected_message_report = "--:1:6 - error ETY012: unable to resolve "
                                 "type - function return type is not provided\n"
                                 "\n"
                                 "1  func f() {\n"
                                 "        ^    \n"
                                 "\n"
                                 "1 error\n",
  });
}
