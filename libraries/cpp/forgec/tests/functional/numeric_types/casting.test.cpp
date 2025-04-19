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

TEST(functional_numeric_types_casting, u8_to_u8_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u8 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  ret i8 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  ret i8 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u16_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u16 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u8) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u8 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u8_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  ret i8 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(128), -128);
         ASSERT_EQ(f(255), -1);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i16_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i16 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
       }});
}

TEST(functional_numeric_types_casting, u8_to_f32_implicit) {
  runFunctionalTest({
      .source = "func f(a: u8) -> f32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u8 to f32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u8_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i8 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(255), 255.0f);
       }});
}

TEST(functional_numeric_types_casting, u8_to_f64_implicit) {
  runFunctionalTest({
      .source = "func f(a: u8) -> f64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u8 to f64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u8_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i8 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint8_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(255), 255.0);
       }});
}

// TODO: Continue these tests
