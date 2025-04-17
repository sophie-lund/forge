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

TEST(integration_pure_math_bit_not, simple_u8) {
  runIntegrationTest(
      {.source = "func f(a: u8) -> u8 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = unsigned_int\n"
           "            bit_width = 8\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = unsigned_int\n"
           "        bit_width = 8\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0xff);
         ASSERT_EQ(f(0xff), 0);
         ASSERT_EQ(f(1), 0xfe);
         ASSERT_EQ(f(10), 0xf5);
       }});
}

TEST(integration_pure_math_bit_not, simple_u16) {
  runIntegrationTest(
      {.source = "func f(a: u16) -> u16 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = unsigned_int\n"
           "            bit_width = 16\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = unsigned_int\n"
           "        bit_width = 16\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0xffff);
         ASSERT_EQ(f(0xffff), 0);
         ASSERT_EQ(f(1), 0xfffe);
         ASSERT_EQ(f(10), 0xfff5);
       }});
}

TEST(integration_pure_math_bit_not, simple_u32) {
  runIntegrationTest(
      {.source = "func f(a: u32) -> u32 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = unsigned_int\n"
           "            bit_width = 32\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = unsigned_int\n"
           "        bit_width = 32\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0xffffffff);
         ASSERT_EQ(f(0xffffffff), 0);
         ASSERT_EQ(f(1), ~1);
         ASSERT_EQ(f(1000), ~1000);
       }});
}

TEST(integration_pure_math_bit_not, simple_u64) {
  runIntegrationTest(
      {.source = "func f(a: u64) -> u64 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = unsigned_int\n"
           "            bit_width = 64\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = unsigned_int\n"
           "        bit_width = 64\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0xffffffffffffffff);
         ASSERT_EQ(f(0xffffffffffffffff), 0);
         ASSERT_EQ(f(1), ~1);
         ASSERT_EQ(f(1000), ~1000);
       }});
}

TEST(integration_pure_math_bit_not, simple_usize) {
  runIntegrationTest(
      {.source = "func f(a: usize) -> usize {\n"
                 "  return ~a;\n"
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
           "            type_basic_kind = usize\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_basic]\n"
           "        type_basic_kind = usize\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<size_t (*)(size_t)>("f");

         if (sizeof(size_t) == 8) {
           ASSERT_EQ(f(0), 0xffffffffffffffff);
           ASSERT_EQ(f(0xffffffffffffffff), 0);
           ASSERT_EQ(f(1), ~1);
           ASSERT_EQ(f(1000), ~1000);
         } else if (sizeof(size_t) == 4) {
           ASSERT_EQ(f(0), 0xffffffff);
           ASSERT_EQ(f(0xffffffff), 0);
           ASSERT_EQ(f(1), ~1);
           ASSERT_EQ(f(1000), ~1000);
         } else {
           FAIL() << "unsupported system bit width " << (sizeof(size_t) * 8);
         }
       }});
}

TEST(integration_pure_math_bit_not, simple_i8) {
  runIntegrationTest(
      {.source = "func f(a: i8) -> i8 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = signed_int\n"
           "            bit_width = 8\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = signed_int\n"
           "        bit_width = 8\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), -1);
         ASSERT_EQ(f(-1), 0);
         ASSERT_EQ(f(1), -2);
         ASSERT_EQ(f(10), -11);
       }});
}

TEST(integration_pure_math_bit_not, simple_i16) {
  runIntegrationTest(
      {.source = "func f(a: i16) -> i16 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = signed_int\n"
           "            bit_width = 16\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = signed_int\n"
           "        bit_width = 16\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), -1);
         ASSERT_EQ(f(-1), 0);
         ASSERT_EQ(f(1), -2);
         ASSERT_EQ(f(10), -11);
       }});
}

TEST(integration_pure_math_bit_not, simple_i32) {
  runIntegrationTest(
      {.source = "func f(a: i32) -> i32 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = signed_int\n"
           "            bit_width = 32\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = signed_int\n"
           "        bit_width = 32\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), -1);
         ASSERT_EQ(f(-1), 0);
         ASSERT_EQ(f(1), -2);
         ASSERT_EQ(f(10), -11);
       }});
}

TEST(integration_pure_math_bit_not, simple_i64) {
  runIntegrationTest(
      {.source = "func f(a: i64) -> i64 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_syntax_tree_debug =
           "[translation_unit]\n"
           "  declarations = \n"
           "    [0] = [declaration_function]\n"
           "      name = \"f\"\n"
           "      args = \n"
           "        [0] = [declaration_variable]\n"
           "          name = \"a\"\n"
           "          type = [type_with_bit_width]\n"
           "            type_with_bit_width_kind = signed_int\n"
           "            bit_width = 64\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_with_bit_width]\n"
           "        type_with_bit_width_kind = signed_int\n"
           "        bit_width = 64\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), -1);
         ASSERT_EQ(f(-1), 0);
         ASSERT_EQ(f(1), -2);
         ASSERT_EQ(f(10), -11);
       }});
}

TEST(integration_pure_math_bit_not, simple_isize) {
  runIntegrationTest(
      {.source = "func f(a: isize) -> isize {\n"
                 "  return ~a;\n"
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
           "            type_basic_kind = isize\n"
           "            is_const = false\n"
           "          initial_value = null\n"
           "          is_const = false\n"
           "      return_type = [type_basic]\n"
           "        type_basic_kind = isize\n"
           "        is_const = false\n"
           "      body = [statement_block]\n"
           "        statements = \n"
           "          [0] = [statement_value]\n"
           "            statement_value_kind = return\n"
           "            value = [value_unary]\n"
           "              operator = ~\n"
           "              operand = [value_symbol]\n"
           "                name = \"a\"",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<ssize_t (*)(ssize_t)>("f");

         ASSERT_EQ(f(0), -1);
         ASSERT_EQ(f(-1), 0);
         ASSERT_EQ(f(1), -2);
         ASSERT_EQ(f(10), -11);
       }});
}

TEST(integration_pure_math_bit_not, simple_bool) {
  runIntegrationTest(
      {.source = "func f(a: bool) -> bool {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_state = IntegrationTestOptionsState::errors_after_passes,
       .expected_message_report = "--:2:11 - error ETY004: unexpected type\n"
                                  "\n"
                                  "2  return ~a;\n"
                                  "           ^ \n"
                                  "\n"
                                  "note: expected integer type\n"
                                  "\n"
                                  "1 error\n"});
}

TEST(integration_pure_math_bit_not, simple_f32) {
  runIntegrationTest(
      {.source = "func f(a: f32) -> f32 {\n"
                 "  return ~a;\n"
                 "}\n",
       .expected_state = IntegrationTestOptionsState::errors_after_passes,
       .expected_message_report = "--:2:11 - error ETY004: unexpected type\n"
                                  "\n"
                                  "2  return ~a;\n"
                                  "           ^ \n"
                                  "\n"
                                  "note: expected integer type\n"
                                  "\n"
                                  "1 error\n"});
}
