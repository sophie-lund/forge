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

TEST(functional_conditionals_is_zero, one_comparison_if_else) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  if a == 0 {\n"
                 "    return true;\n"
                 "  } else {\n"
                 "    return false;\n"
                 "  }\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(int32_t)>("f");

         ASSERT_EQ(f(0), true);
         ASSERT_EQ(f(1), false);
         ASSERT_EQ(f(-1), false);
       }});
}

TEST(functional_conditionals_is_zero, one_comparison_if_then) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  if a == 0 {\n"
                 "    return true;\n"
                 "  }\n"
                 "\n"
                 "  return false;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(int32_t)>("f");

         ASSERT_EQ(f(0), true);
         ASSERT_EQ(f(1), false);
         ASSERT_EQ(f(-1), false);
       }});
}

TEST(functional_conditionals_is_zero, one_comparison_if_else_tree_variant_0) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  if a < 0 {\n"
                 "    return false;\n"
                 "  } else if a > 0 {\n"
                 "    return false;\n"
                 "  } else {\n"
                 "    return true;\n"
                 "  }\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(int32_t)>("f");

         ASSERT_EQ(f(0), true);
         ASSERT_EQ(f(1), false);
         ASSERT_EQ(f(-1), false);
       }});
}

TEST(functional_conditionals_is_zero, one_comparison_if_else_tree_variant_1) {
  runFunctionalTest({
      .source = "func f(a: i32) -> bool {\n"
                "  if a < 0 {\n"
                "    return false;\n"
                "  } else if a > 0 {\n"
                "    return false;\n"
                "  } else if a == 0 {\n"
                "    return true;\n"
                "  }\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report =
          "--:1:6 - error ECF002: function does not return in all cases\n"
          "\n"
          "1  func f(a: i32) -> bool {\n"
          "        ^                  \n"
          "\n"
          "1 error\n",
  });
}

TEST(functional_conditionals_is_zero, one_comparison_if_else_tree_variant_2) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  if a < 0 {\n"
                 "    return false;\n"
                 "  } else if a > 0 {\n"
                 "    return false;\n"
                 "  }\n"
                 "\n"
                 "  return true;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(int32_t)>("f");

         ASSERT_EQ(f(0), true);
         ASSERT_EQ(f(1), false);
         ASSERT_EQ(f(-1), false);
       }});
}

TEST(functional_conditionals_is_zero, non_bool_condition) {
  runFunctionalTest({
      .source = "func f(a: i32) -> bool {\n"
                "  if a {\n"
                "    return true;\n"
                "  } else {\n"
                "    return false;\n"
                "  }\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:6 - error ETY004: unexpected type\n"
                                 "\n"
                                 "2  if a {\n"
                                 "      ^  \n"
                                 "\n"
                                 "note: expected bool\n"
                                 "\n"
                                 "1 error\n",
  });
}
