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

#include <forgec/testing/functional_test_harness.hpp>

using namespace forge;

TEST(functional_pure_math_identity_function, simple_bool) {
  runFunctionalTest({.source = "func f(a: bool) -> bool {\n"
                               "  return a;\n"
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
                         "            value = [value_symbol]\n"
                         "              name = \"a\"",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<bool (*)(bool)>("f");

                       ASSERT_EQ(f(true), true);
                       ASSERT_EQ(f(false), false);
                     }});
}

TEST(functional_pure_math_identity_function, simple_u8) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u8 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(0xff), 0xff);
         ASSERT_EQ(f(static_cast<uint8_t>(0x100)), 0x0);
       }});
}

TEST(functional_pure_math_identity_function, simple_u16) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u16 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(0xff), 0xff);
         ASSERT_EQ(f(0xffff), 0xffff);
         ASSERT_EQ(f(static_cast<uint16_t>(0x10000)), 0x0);
       }});
}

TEST(functional_pure_math_identity_function, simple_u32) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u32 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(0xff), 0xff);
         ASSERT_EQ(f(0xffff), 0xffff);
         ASSERT_EQ(f(0xffffffff), 0xffffffff);
         ASSERT_EQ(f(static_cast<uint32_t>(0x100000000)), 0x0);
       }});
}

TEST(functional_pure_math_identity_function, simple_u64) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(0xff), 0xff);
         ASSERT_EQ(f(0xffff), 0xffff);
         ASSERT_EQ(f(0xffffffff), 0xffffffff);
         ASSERT_EQ(f(0xffffffffffffffff), 0xffffffffffffffff);
       }});
}

TEST(functional_pure_math_identity_function, simple_i8) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i8 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(1), 1);
         ASSERT_EQ(f(-1), -1);
         ASSERT_EQ(f(INT8_MAX), INT8_MAX);
         ASSERT_EQ(f(INT8_MIN), INT8_MIN);
       }});
}

TEST(functional_pure_math_identity_function, simple_i16) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i16 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(1), 1);
         ASSERT_EQ(f(-1), -1);
         ASSERT_EQ(f(INT16_MAX), INT16_MAX);
         ASSERT_EQ(f(INT16_MIN), INT16_MIN);
       }});
}

TEST(functional_pure_math_identity_function, simple_i32) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(1), 1);
         ASSERT_EQ(f(-1), -1);
         ASSERT_EQ(f(INT32_MAX), INT32_MAX);
         ASSERT_EQ(f(INT32_MIN), INT32_MIN);
       }});
}

TEST(functional_pure_math_identity_function, simple_i64) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(1), 1);
         ASSERT_EQ(f(-1), -1);
         ASSERT_EQ(f(INT64_MAX), INT64_MAX);
         ASSERT_EQ(f(INT64_MIN), INT64_MIN);
       }});
}

TEST(functional_pure_math_identity_function, simple_f32) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0.0f);
         ASSERT_EQ(f(1.0f), 1.0f);
         ASSERT_EQ(f(-1.0f), -1.0f);
       }});
}

TEST(functional_pure_math_identity_function, simple_f64) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0.0);
         ASSERT_EQ(f(1.0), 1.0);
         ASSERT_EQ(f(-1.0), -1.0);
       }});
}

TEST(functional_pure_math_identity_function, implicitly_castable) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0.0);
         ASSERT_EQ(f(1.0f), 1.0);
         ASSERT_EQ(f(-1.0f), -1.0);
       }});
}

TEST(functional_pure_math_identity_function, explicitly_castable) {
  runFunctionalTest({
      .source = "func f(a: f64) -> f32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to f32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}
