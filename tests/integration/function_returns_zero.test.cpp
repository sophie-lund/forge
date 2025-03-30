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

#include <forge/testing/integration_test_harness.hpp>

using namespace forge;

TEST(integration_function_returns_zero, harness) {
  runIntegrationTest({.source = "func f() -> i32 {\n"
                                "  return 0;\n"
                                "}\n",
                      .expected_syntax_tree_debug =
                          "[translation_unit]\n"
                          "  declarations = \n"
                          "    [0] = [declaration_function]\n"
                          "      name = \"f\"\n"
                          "      args = []\n"
                          "      return_type = [type_with_bit_width]\n"
                          "        kind = signed_int\n"
                          "        bit_width = 32\n"
                          "        is_const = false\n"
                          "      body = [statement_block]\n"
                          "        statements = \n"
                          "          [0] = [statement_value]\n"
                          "            kind = return\n"
                          "            value = [value_literal_number]\n"
                          "              type = [type_with_bit_width]\n"
                          "                kind = signed_int\n"
                          "                bit_width = 32\n"
                          "                is_const = false\n"
                          "              value = 0"});
}
