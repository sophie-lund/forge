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

TEST(functional_numeric_types_arithmetic, add_i8_to_i32) {
  runFunctionalTest(
      {.source = "func f(a: i8, b: i32) -> i32 {\n"
                 "  return a + b;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a, i32 %b) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  %1 = add i32 %0, %b\n"
                                     "  ret i32 %1\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f =
             jit_context.try_lookup_function<int32_t (*)(int8_t, int32_t)>("f");

         ASSERT_EQ(f(0, 0), 0);
         ASSERT_EQ(f(1, 2), 3);
       }});
}
