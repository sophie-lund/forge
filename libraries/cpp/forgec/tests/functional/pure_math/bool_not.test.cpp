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

TEST(integration_pure_math_bool_not, simple) {
  runIntegrationTest(
      {.source = "func f(a: bool) -> bool {\n"
                 "  return !a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_basic]\n"
           "            type_basic_kind = bool\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_basic]\n"
           "        type_basic_kind = bool\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = !\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(bool)>("f");

         ASSERT_EQ(f(true), false);
         ASSERT_EQ(f(false), true);
       }});
}

TEST(integration_pure_math_bool_not, simple_i32) {
  runIntegrationTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  return !a;\n"
                 "}\n",
       .expected_state = IntegrationTestOptionsState::errors_after_passes,
       .expected_message_report = "--:2:11 - error ETY004: unexpected type\n"
                                  "\n"
                                  "2  return !a;\n"
                                  "           ^ \n"
                                  "\n"
                                  "note: expected bool\n"
                                  "\n"
                                  "1 error\n"});
}

TEST(integration_pure_math_bool_not, simple_f32) {
  runIntegrationTest(
      {.source = "func f(a: f32) -> bool {\n"
                 "  return !a;\n"
                 "}\n",
       .expected_state = IntegrationTestOptionsState::errors_after_passes,
       .expected_message_report = "--:2:11 - error ETY004: unexpected type\n"
                                  "\n"
                                  "2  return !a;\n"
                                  "           ^ \n"
                                  "\n"
                                  "note: expected bool\n"
                                  "\n"
                                  "1 error\n"});
}
