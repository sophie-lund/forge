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

TEST(functional_pure_math_eq, simple_i32_with_i32) {
  runFunctionalTest(
      {.source = "func f(a: i32, b: i32) -> bool {\n"
                 "  return a == b;\n"
                 "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f =
             jit_context.try_lookup_function<bool (*)(int32_t, int32_t)>("f");

         ASSERT_EQ(f(0, 0), true);
         ASSERT_EQ(f(1, 0), false);
         ASSERT_EQ(f(0, 1), false);
         ASSERT_EQ(f(1, 1), true);
         ASSERT_EQ(f(-1, 1), false);
         ASSERT_EQ(f(1, -1), false);
         ASSERT_EQ(f(-1, -1), true);
       }});
}

TEST(functional_pure_math_eq, simple_f32_with_f32) {
  runFunctionalTest(
      {.source = "func f(a: f32, b: f32) -> bool {\n"
                 "  return a == b;\n"
                 "}\n",
       .expected_llvm_module_print = "define i1 @f(float %a, float %b) {\n"
                                     "entry:\n"
                                     "  %0 = fcmp oeq float %a, %b\n"
                                     "  ret i1 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(float, float)>("f");

         ASSERT_EQ(f(0.0f, 0.0f), true);
         ASSERT_EQ(f(1.0f, 0.0f), false);
         ASSERT_EQ(f(0.0f, 1.0f), false);
         ASSERT_EQ(f(1.0f, 1.0f), true);
         ASSERT_EQ(f(-1.0f, 1.0f), false);
         ASSERT_EQ(f(1.0f, -1.0f), false);
         ASSERT_EQ(f(-1.0f, -1.0f), true);
       }});
}
