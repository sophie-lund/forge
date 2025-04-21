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

TEST(functional_control_flow_with_state_if_with_variables, only_variables) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  let x: i32 = 0;\n"
                               "  let y: i32 = 5;\n"
                               "  if x < y {\n"
                               "    return 1;\n"
                               "  } else {\n"
                               "    return 2;\n"
                               "  }\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 1);
                     }});
}

TEST(functional_control_flow_with_state_if_with_variables,
     variable_with_argument) {
  runFunctionalTest(
      {.source = "func f(y: i32) -> i32 {\n"
                 "  let x: i32 = 0;\n"
                 "  if x < y {\n"
                 "    return 1;\n"
                 "  } else {\n"
                 "    return 2;\n"
                 "  }\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(5), 1);
         ASSERT_EQ(f(1), 1);
         ASSERT_EQ(f(0), 2);
         ASSERT_EQ(f(-5), 2);
       }});
}
