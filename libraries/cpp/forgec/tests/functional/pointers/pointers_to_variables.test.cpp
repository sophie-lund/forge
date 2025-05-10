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

TEST(functional_pointers_pointers_to_variables, reassign_variable) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  let x: i32 = 0;\n"
                 "  let p: *i32 = &x;\n"
                 "  *p;\n"
                 "  return x;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f() {\n"
                                     "entry:\n"
                                     "  %x = alloca i32, align 4\n"
                                     "  store i32 0, ptr %x, align 4\n"
                                     "  %p = alloca ptr, align 8\n"
                                     "  %0 = load i32, ptr %x, align 4\n"
                                     "  %1 = inttoptr i32 %0 to ptr\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 10);
       }});
}
