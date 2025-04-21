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

TEST(functional_variable_math, return_variable) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  let x: i32 = 0;\n"
                 "  return x;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f() {\n"
                                     "entry:\n"
                                     "  %x = alloca i32, align 4\n"
                                     "  store i32 0, ptr %x, align 4\n"
                                     "  %0 = load i32, ptr %x, align 4\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 0);
       }});
}

TEST(functional_variable_math, return_variable_implicit_cast) {
  runFunctionalTest({.source = "func f() -> f32 {\n"
                               "  let x: f32 = 0u8;\n"
                               "  return x;\n"
                               "}\n",
                     .expected_llvm_module_print =
                         "define float @f() {\n"
                         "entry:\n"
                         "  %x = alloca float, align 4\n"
                         "  store float 0.000000e+00, ptr %x, align 4\n"
                         "  %0 = load float, ptr %x, align 4\n"
                         "  ret float %0\n"
                         "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<float (*)()>("f");

                       ASSERT_EQ(f(), 0.0f);
                     }});
}

TEST(functional_variable_math, return_variable_invalid_type) {
  runFunctionalTest({
      .source = "func f() -> i32 {\n"
                "  let x: i32 = 0.0;\n"
                "  return x;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:16 - error ETY005: unable to implicitly "
                                 "cast from type f64 to i32\n"
                                 "\n"
                                 "2  let x: i32 = 0.0;\n"
                                 "                ^^^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_variable_math, increment_once_from_zero) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  let x: i32 = 0;\n"
                 "  x += 1;\n"
                 "  return x;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f() {\n"
                                     "entry:\n"
                                     "  %x = alloca i32, align 4\n"
                                     "  store i32 0, ptr %x, align 4\n"
                                     "  %0 = load i32, ptr %x, align 4\n"
                                     "  %1 = add i32 %0, 1\n"
                                     "  store i32 %1, ptr %x, align 4\n"
                                     "  %2 = load i32, ptr %x, align 4\n"
                                     "  ret i32 %2\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 1);
       }});
}

TEST(functional_variable_math, increment_twice_from_zero) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  let x: i32 = 0;\n"
                 "  x += 1;\n"
                 "  x += 1;\n"
                 "  return x;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f() {\n"
                                     "entry:\n"
                                     "  %x = alloca i32, align 4\n"
                                     "  store i32 0, ptr %x, align 4\n"
                                     "  %0 = load i32, ptr %x, align 4\n"
                                     "  %1 = add i32 %0, 1\n"
                                     "  store i32 %1, ptr %x, align 4\n"
                                     "  %2 = load i32, ptr %x, align 4\n"
                                     "  %3 = add i32 %2, 1\n"
                                     "  store i32 %3, ptr %x, align 4\n"
                                     "  %4 = load i32, ptr %x, align 4\n"
                                     "  ret i32 %4\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 2);
       }});
}

TEST(functional_variable_math, add_5_to_variable_initialized_to_2) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  let x: i32 = 2;\n"
                 "  x += 5;\n"
                 "  return x;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f() {\n"
                                     "entry:\n"
                                     "  %x = alloca i32, align 4\n"
                                     "  store i32 2, ptr %x, align 4\n"
                                     "  %0 = load i32, ptr %x, align 4\n"
                                     "  %1 = add i32 %0, 5\n"
                                     "  store i32 %1, ptr %x, align 4\n"
                                     "  %2 = load i32, ptr %x, align 4\n"
                                     "  ret i32 %2\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 7);
       }});
}

TEST(functional_variable_math, add_two_variables) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  let x: i32 = 2;\n"
                 "  let y: i32 = 5;\n"
                 "  return x + y;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f() {\n"
                                     "entry:\n"
                                     "  %x = alloca i32, align 4\n"
                                     "  store i32 2, ptr %x, align 4\n"
                                     "  %y = alloca i32, align 4\n"
                                     "  store i32 5, ptr %y, align 4\n"
                                     "  %0 = load i32, ptr %x, align 4\n"
                                     "  %1 = load i32, ptr %y, align 4\n"
                                     "  %2 = add i32 %0, %1\n"
                                     "  ret i32 %2\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 7);
       }});
}
