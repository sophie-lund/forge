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

TEST(functional_control_flow_with_state_while, iterate_to_10) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  let x: i32 = 0;\n"
                               "  while x < 10 {\n"
                               "    x += 1;\n"
                               "  }\n"
                               "\n"
                               "  return x;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 10);
                     }});
}

TEST(functional_control_flow_with_state_while, iterate_to_zero) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  let x: i32 = 0;\n"
                               "  while x < 0 {\n"
                               "    x += 1;\n"
                               "  }\n"
                               "\n"
                               "  return x;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 0);
                     }});
}

TEST(functional_control_flow_with_state_while, iterate_to_zero_do_while) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  let x: i32 = 0;\n"
                               "  do {\n"
                               "    x += 1;\n"
                               "  } while x < 0;\n"
                               "\n"
                               "  return x;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 1);
                     }});
}

TEST(functional_control_flow_with_state_while,
     nested_iteration_all_variables_at_top) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  let count: i32 = 0;\n"
                               "  let i: i32 = 0;\n"
                               "  let j: i32 = 0;\n"
                               "\n"
                               "  while i < 10 {\n"
                               "    j = 0;\n"
                               "\n"
                               "    while j < 10 {\n"
                               "      count += 1;\n"
                               "      j += 1;\n"
                               "    }\n"
                               "\n"
                               "    i += 1;\n"
                               "  }\n"
                               ""
                               "\n"
                               "  return count;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 100);
                     }});
}

TEST(functional_control_flow_with_state_while,
     nested_iteration_variables_nested) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  let count: i32 = 0;\n"
                               "  let i: i32 = 0;\n"
                               "\n"
                               "  while i < 10 {\n"
                               "    let j: i32 = 0;\n"
                               "\n"
                               "    while j < 10 {\n"
                               "      count += 1;\n"
                               "      j += 1;\n"
                               "    }\n"
                               "\n"
                               "    i += 1;\n"
                               "  }\n"
                               ""
                               "\n"
                               "  return count;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 100);
                     }});
}
