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
  runFunctionalTest(
      {.source = "func f(a: u8) -> f32 {\n"
                 "  return a;\n"
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
  runFunctionalTest(
      {.source = "func f(a: u8) -> f64 {\n"
                 "  return a;\n"
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

TEST(functional_numeric_types_casting, u16_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u16) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u16 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u16_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i16 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(65535), 255);
       }});
}

TEST(functional_numeric_types_casting, u16_to_u16_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u16 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  ret i16 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  ret i16 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_u32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_u64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u16) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u16 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u16_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i16 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(128), -128);
         ASSERT_EQ(f(255), -1);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(65535), -1);
       }});
}

TEST(functional_numeric_types_casting, u16_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: u16) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u16 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u16_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  ret i16 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(32768), -32768);
         ASSERT_EQ(f(65535), -1);
       }});
}

TEST(functional_numeric_types_casting, u16_to_i32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i16 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(65535), 65535.0f);
       }});
}

TEST(functional_numeric_types_casting, u16_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i16 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(65535), 65535.0f);
       }});
}

TEST(functional_numeric_types_casting, u16_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i16 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(65535), 65535.0);
       }});
}

TEST(functional_numeric_types_casting, u16_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i16 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(65535), 65535.0);
       }});
}

TEST(functional_numeric_types_casting, u32_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u32) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u32 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u32_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(4294967295), 255);
       }});
}

TEST(functional_numeric_types_casting, u32_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: u32) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u32 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u32_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(4294967295), 65535);
       }});
}

TEST(functional_numeric_types_casting, u32_to_u32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_u64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u32) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u32 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u32_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(128), -128);
         ASSERT_EQ(f(255), -1);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, u32_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: u32) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u32 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u32_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(32768), -32768);
         ASSERT_EQ(f(65535), -1);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, u32_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: u32) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u32 to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u32_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, u32_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(4294967295), 4294967295.0f);
       }});
}

TEST(functional_numeric_types_casting, u32_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(4294967295), 4294967295.0f);
       }});
}

TEST(functional_numeric_types_casting, u32_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(4294967295), 4294967295.0);
       }});
}

TEST(functional_numeric_types_casting, u32_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(4294967295), 4294967295.0);
       }});
}

TEST(functional_numeric_types_casting, u64_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(18446744073709551615LU), 255);
       }});
}

TEST(functional_numeric_types_casting, u64_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(18446744073709551615LU), 65535);
       }});
}

TEST(functional_numeric_types_casting, u64_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
         ASSERT_EQ(f(4294967296), 0);
         ASSERT_EQ(f(18446744073709551615LU), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u64_to_u64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, u64_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, u64_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(128), -128);
         ASSERT_EQ(f(255), -1);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, u64_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(32768), -32768);
         ASSERT_EQ(f(65535), -1);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, u64_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
         ASSERT_EQ(f(4294967296), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, u64_to_i64_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> i64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to i64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808LU), -9223372036854775808LU);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, u64_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0f);
       }});
}

TEST(functional_numeric_types_casting, u64_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0f);
       }});
}

TEST(functional_numeric_types_casting, u64_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0);
       }});
}

TEST(functional_numeric_types_casting, u64_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0);
       }});
}

TEST(functional_numeric_types_casting, i8_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i8) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i8 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i8_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  ret i8 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), 128);
         ASSERT_EQ(f(-1), 255);
       }});
}

TEST(functional_numeric_types_casting, i8_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: i8) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i8 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i8_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), 65535 - 127);
         ASSERT_EQ(f(-1), 65535);
       }});
}

TEST(functional_numeric_types_casting, i8_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: i8) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i8 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i8_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), 4294967295 - 127);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i8_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: i8) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i8 to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i8_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), 18446744073709551615LU - 127);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i8_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i8 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  ret i8 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  ret i8 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i16_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i16 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i8 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127.0f);
         ASSERT_EQ(f(-128), -128.0f);
       }});
}

TEST(functional_numeric_types_casting, i8_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i8 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127.0f);
         ASSERT_EQ(f(-128), -128.0f);
       }});
}

TEST(functional_numeric_types_casting, i8_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i8 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(127), 127.0);
         ASSERT_EQ(f(-128), -128.0);
       }});
}

TEST(functional_numeric_types_casting, i8_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i8 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(127), 127.0);
         ASSERT_EQ(f(-128), -128.0);
       }});
}

TEST(functional_numeric_types_casting, i16_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i16 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 255);
         ASSERT_EQ(f(-32768), 0);
         ASSERT_EQ(f(-1), 255);
       }});
}

TEST(functional_numeric_types_casting, i16_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  ret i16 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), 65535 - 32767);
         ASSERT_EQ(f(-1), 65535);
       }});
}

TEST(functional_numeric_types_casting, i16_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), 4294967295 - 32767);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i16_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), 18446744073709551615LU - 32767);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i16 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
         ASSERT_EQ(f(32767), -1);
         ASSERT_EQ(f(-32768), 0);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i16_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i16 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  ret i16 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  ret i16 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i16 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767.0f);
         ASSERT_EQ(f(-32768), -32768.0f);
       }});
}

TEST(functional_numeric_types_casting, i16_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i16 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767.0f);
         ASSERT_EQ(f(-32768), -32768.0f);
       }});
}

TEST(functional_numeric_types_casting, i16_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i16 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767.0);
         ASSERT_EQ(f(-32768), -32768.0);
       }});
}

TEST(functional_numeric_types_casting, i16_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i16 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767.0);
         ASSERT_EQ(f(-32768), -32768.0);
       }});
}

TEST(functional_numeric_types_casting, i32_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 255);
         ASSERT_EQ(f(-2147483648), 0);
         ASSERT_EQ(f(-1), 255);
       }});
}

TEST(functional_numeric_types_casting, i32_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 65535);
         ASSERT_EQ(f(-2147483648), 0);
         ASSERT_EQ(f(-1), 65535);
       }});
}

TEST(functional_numeric_types_casting, i32_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 2147483648);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i32_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 18446744073709551615LU - 2147483647);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i32_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
         ASSERT_EQ(f(2147483647), -1);
         ASSERT_EQ(f(-2147483648), 0);
       }});
}

TEST(functional_numeric_types_casting, i32_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
         ASSERT_EQ(f(2147483647), -1);
         ASSERT_EQ(f(-2147483648), 0);
       }});
}

TEST(functional_numeric_types_casting, i32_to_i32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i32_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i32_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i32_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i32_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0f);
         ASSERT_EQ(f(-2147483648), -2147483648.0f);
       }});
}

TEST(functional_numeric_types_casting, i32_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0f);
         ASSERT_EQ(f(-2147483648), -2147483648.0f);
       }});
}

TEST(functional_numeric_types_casting, i32_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0);
         ASSERT_EQ(f(-2147483648), -2147483648.0);
       }});
}

TEST(functional_numeric_types_casting, i32_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0);
         ASSERT_EQ(f(-2147483648), -2147483648.0);
       }});
}

TEST(functional_numeric_types_casting, i64_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 255);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 255);
       }});
}

TEST(functional_numeric_types_casting, i64_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 65535);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 65535);
       }});
}

TEST(functional_numeric_types_casting, i64_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 4294967295);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i64_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), 9223372036854775808LU);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i64_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, i64_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, i64_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, i64_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, i64_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, i64_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0f);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0f);
       }});
}

TEST(functional_numeric_types_casting, i64_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0f);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0f);
       }});
}

TEST(functional_numeric_types_casting, i64_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0);
       }});
}

TEST(functional_numeric_types_casting, i64_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui float %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(255.0f), 255);
         ASSERT_EQ(f(255.5f), 255);
         ASSERT_EQ(f(256.0f), 0);
         ASSERT_EQ(f(256.5f), 0);
         ASSERT_EQ(f(-1.0f), 255);
         ASSERT_EQ(f(-1.5f), 255);
         ASSERT_EQ(f(-256.0f), 0);
         ASSERT_EQ(f(-256.5f), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui float %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(65535.0f), 65535);
         ASSERT_EQ(f(65535.5f), 65535);
         ASSERT_EQ(f(65536.0f), 0);
         ASSERT_EQ(f(65536.5f), 0);
         ASSERT_EQ(f(-1.0f), 65535);
         ASSERT_EQ(f(-1.5f), 65535);
         ASSERT_EQ(f(-65536.0f), 0);
         ASSERT_EQ(f(-65536.5f), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui float %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(4294967295.0f), 4294967295);
         ASSERT_EQ(f(4294967295.5f), 4294967295);
         ASSERT_EQ(f(4294967296.0f), 4294967295);
         ASSERT_EQ(f(4294967296.5f), 4294967295);
         ASSERT_EQ(f(-1.0f), 0);
         ASSERT_EQ(f(-1.5f), 0);
         ASSERT_EQ(f(-4294967296.0f), 0);
         ASSERT_EQ(f(-4294967296.5f), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui float %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(4294967295.0f), 4294967296);
         ASSERT_EQ(f(4294967295.5f), 4294967296);
         ASSERT_EQ(f(4294967296.0f), 4294967296);
         ASSERT_EQ(f(4294967296.5f), 4294967296);
         ASSERT_EQ(f(-1.0f), 0);
         ASSERT_EQ(f(-1.5f), 0);
         ASSERT_EQ(f(-4294967296.0f), 0);
         ASSERT_EQ(f(-4294967296.5f), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi float %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(-5.0f), -5);
         ASSERT_EQ(f(-5.5f), -5);
         ASSERT_EQ(f(127.0f), 127);
         ASSERT_EQ(f(127.5f), 127);
         ASSERT_EQ(f(128.0f), -128);
         ASSERT_EQ(f(128.5f), -128);
         ASSERT_EQ(f(-1.0f), -1);
         ASSERT_EQ(f(-1.5f), -1);
         ASSERT_EQ(f(-128.0f), -128);
         ASSERT_EQ(f(-128.5f), -128);
       }});
}

TEST(functional_numeric_types_casting, f32_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi float %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(-5.0f), -5);
         ASSERT_EQ(f(-5.5f), -5);
         ASSERT_EQ(f(32767.0f), 32767);
         ASSERT_EQ(f(32767.5f), 32767);
         ASSERT_EQ(f(32768.0f), -32768);
         ASSERT_EQ(f(32768.5f), -32768);
         ASSERT_EQ(f(-1.0f), -1);
         ASSERT_EQ(f(-1.5f), -1);
         ASSERT_EQ(f(-32768.0f), -32768);
         ASSERT_EQ(f(-32768.5f), -32768);
       }});
}

TEST(functional_numeric_types_casting, f32_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi float %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(-5.0f), -5);
         ASSERT_EQ(f(-5.5f), -5);
         ASSERT_EQ(f(2147483647.0f), 2147483647);
         ASSERT_EQ(f(2147483647.5f), 2147483647);
         ASSERT_EQ(f(2147483648.0f), 2147483647);
         ASSERT_EQ(f(2147483648.5f), 2147483647);
         ASSERT_EQ(f(-1.0f), -1);
         ASSERT_EQ(f(-1.5f), -1);
         ASSERT_EQ(f(-2147483648.0f), -2147483648);
         ASSERT_EQ(f(-2147483648.5f), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, f32_to_i64_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> i64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to i64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi float %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(-5.0f), -5);
         ASSERT_EQ(f(-5.5f), -5);
         ASSERT_EQ(f(9223372036854775807.0f), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775807.5f), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.0f), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.5f), 9223372036854775807LU);
         ASSERT_EQ(f(-1.0f), -1);
         ASSERT_EQ(f(-1.5f), -1);
         ASSERT_EQ(f(-9223372036854775808.0f), -9223372036854775808LU);
         ASSERT_EQ(f(-9223372036854775808.5f), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, f32_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(float %a) {\n"
                                     "entry:\n"
                                     "  ret float %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0.0f);
         ASSERT_EQ(f(5.0f), 5.0f);
         ASSERT_EQ(f(-5.0f), -5.0f);
       }});
}

TEST(functional_numeric_types_casting, f32_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(float %a) {\n"
                                     "entry:\n"
                                     "  ret float %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0.0f);
         ASSERT_EQ(f(5.0f), 5.0f);
         ASSERT_EQ(f(-5.0f), -5.0f);
       }});
}

TEST(functional_numeric_types_casting, f32_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fpext float %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0.0);
         ASSERT_EQ(f(5.0f), 5.0);
         ASSERT_EQ(f(-5.0f), -5.0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> f64 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fpext float %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0.0);
         ASSERT_EQ(f(5.0f), 5.0);
         ASSERT_EQ(f(-5.0f), -5.0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui double %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(255.0), 255);
         ASSERT_EQ(f(255.5), 255);
         ASSERT_EQ(f(256.0), 0);
         ASSERT_EQ(f(256.5), 0);
         ASSERT_EQ(f(-1.0), 255);
         ASSERT_EQ(f(-1.5), 255);
         ASSERT_EQ(f(-256.0), 0);
         ASSERT_EQ(f(-256.5), 0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui double %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(65535.0), 65535);
         ASSERT_EQ(f(65535.5), 65535);
         ASSERT_EQ(f(65536.0), 0);
         ASSERT_EQ(f(65536.5), 0);
         ASSERT_EQ(f(-1.0), 65535);
         ASSERT_EQ(f(-1.5), 65535);
         ASSERT_EQ(f(-65536.0), 0);
         ASSERT_EQ(f(-65536.5), 0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui double %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(4294967295.0), 4294967295);
         ASSERT_EQ(f(4294967295.5), 4294967295);
         ASSERT_EQ(f(4294967296.0), 4294967295);
         ASSERT_EQ(f(4294967296.5), 4294967295);
         ASSERT_EQ(f(-1.0), 0);
         ASSERT_EQ(f(-1.5), 0);
         ASSERT_EQ(f(-4294967296.0), 0);
         ASSERT_EQ(f(-4294967296.5), 0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui double %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(4294967295.0), 4294967295);
         ASSERT_EQ(f(4294967295.5), 4294967295);
         ASSERT_EQ(f(4294967296.0), 4294967296);
         ASSERT_EQ(f(4294967296.5), 4294967296);
         ASSERT_EQ(f(-1.0), 0);
         ASSERT_EQ(f(-1.5), 0);
         ASSERT_EQ(f(-4294967296.0), 0);
         ASSERT_EQ(f(-4294967296.5), 0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi double %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(-5.0), -5);
         ASSERT_EQ(f(-5.5), -5);
         ASSERT_EQ(f(127.0), 127);
         ASSERT_EQ(f(127.5), 127);
         ASSERT_EQ(f(128.0), -128);
         ASSERT_EQ(f(128.5), -128);
         ASSERT_EQ(f(-1.0), -1);
         ASSERT_EQ(f(-1.5), -1);
         ASSERT_EQ(f(-128.0), -128);
         ASSERT_EQ(f(-128.5), -128);
       }});
}

TEST(functional_numeric_types_casting, f64_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi double %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(-5.0), -5);
         ASSERT_EQ(f(-5.5), -5);
         ASSERT_EQ(f(32767.0), 32767);
         ASSERT_EQ(f(32767.5), 32767);
         ASSERT_EQ(f(32768.0), -32768);
         ASSERT_EQ(f(32768.5), -32768);
         ASSERT_EQ(f(-1.0), -1);
         ASSERT_EQ(f(-1.5), -1);
         ASSERT_EQ(f(-32768.0), -32768);
         ASSERT_EQ(f(-32768.5), -32768);
       }});
}

TEST(functional_numeric_types_casting, f64_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi double %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(-5.0), -5);
         ASSERT_EQ(f(-5.5), -5);
         ASSERT_EQ(f(2147483647.0), 2147483647);
         ASSERT_EQ(f(2147483647.5), 2147483647);
         ASSERT_EQ(f(2147483648.0), 2147483647);
         ASSERT_EQ(f(2147483648.5), 2147483647);
         ASSERT_EQ(f(-1.0), -1);
         ASSERT_EQ(f(-1.5), -1);
         ASSERT_EQ(f(-2147483648.0), -2147483648);
         ASSERT_EQ(f(-2147483648.5), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, f64_to_i64_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> i64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to i64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi double %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(-5.0), -5);
         ASSERT_EQ(f(-5.5), -5);
         ASSERT_EQ(f(9223372036854775807.0), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775807.5), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.0), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.5), 9223372036854775807LU);
         ASSERT_EQ(f(-1.0), -1);
         ASSERT_EQ(f(-1.5), -1);
         ASSERT_EQ(f(-9223372036854775808.0), -9223372036854775808LU);
         ASSERT_EQ(f(-9223372036854775808.5), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, f64_to_f32_implicit) {
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

TEST(functional_numeric_types_casting, f64_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptrunc double %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0.0f);
         ASSERT_EQ(f(5.0), 5.0f);
         ASSERT_EQ(f(-5.0), -5.0f);
       }});
}

TEST(functional_numeric_types_casting, f64_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(double %a) {\n"
                                     "entry:\n"
                                     "  ret double %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0.0);
         ASSERT_EQ(f(5.0), 5.0);
         ASSERT_EQ(f(-5.0), -5.0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(double %a) {\n"
                                     "entry:\n"
                                     "  ret double %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0.0);
         ASSERT_EQ(f(5.0), 5.0);
         ASSERT_EQ(f(-5.0), -5.0);
       }});
}

#if FRG_POINTER_BIT_WIDTH == 32
TEST(functional_numeric_types_casting, u8_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> usize {\n"
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

TEST(functional_numeric_types_casting, u8_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> usize {\n"
                 "  return a as usize;\n"
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

TEST(functional_numeric_types_casting, u8_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> isize {\n"
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

TEST(functional_numeric_types_casting, u8_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> isize {\n"
                 "  return a as isize;\n"
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

TEST(functional_numeric_types_casting, u16_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u32_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: u32) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u32 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u32_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, u64_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
         ASSERT_EQ(f(4294967296), 0);
         ASSERT_EQ(f(18446744073709551615LU), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u64_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
         ASSERT_EQ(f(4294967296), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, i8_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i8) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i8 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i8_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), 4294967295 - 127);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i8_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i16_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), 4294967295 - 32767);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i16_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i32_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 2147483648);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i32_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i32_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i64_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 4294967295);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, i64_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui float %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(4294967295.0f), 4294967295);
         ASSERT_EQ(f(4294967295.5f), 4294967295);
         ASSERT_EQ(f(4294967296.0f), 4294967295);
         ASSERT_EQ(f(4294967296.5f), 4294967295);
         ASSERT_EQ(f(-1.0f), 0);
         ASSERT_EQ(f(-1.5f), 0);
         ASSERT_EQ(f(-4294967296.0f), 0);
         ASSERT_EQ(f(-4294967296.5f), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi float %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(-5.0f), -5);
         ASSERT_EQ(f(-5.5f), -5);
         ASSERT_EQ(f(2147483647.0f), 2147483647);
         ASSERT_EQ(f(2147483647.5f), 2147483647);
         ASSERT_EQ(f(2147483648.0f), 2147483647);
         ASSERT_EQ(f(2147483648.5f), 2147483647);
         ASSERT_EQ(f(-1.0f), -1);
         ASSERT_EQ(f(-1.5f), -1);
         ASSERT_EQ(f(-2147483648.0f), -2147483648);
         ASSERT_EQ(f(-2147483648.5f), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, f64_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui double %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(4294967295.0), 4294967295);
         ASSERT_EQ(f(4294967295.5), 4294967295);
         ASSERT_EQ(f(4294967296.0), 4294967295);
         ASSERT_EQ(f(4294967296.5), 4294967295);
         ASSERT_EQ(f(-1.0), 0);
         ASSERT_EQ(f(-1.5), 0);
         ASSERT_EQ(f(-4294967296.0), 0);
         ASSERT_EQ(f(-4294967296.5), 0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi double %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(-5.0), -5);
         ASSERT_EQ(f(-5.5), -5);
         ASSERT_EQ(f(2147483647.0), 2147483647);
         ASSERT_EQ(f(2147483647.5), 2147483647);
         ASSERT_EQ(f(2147483648.0), 2147483647);
         ASSERT_EQ(f(2147483648.5), 2147483647);
         ASSERT_EQ(f(-1.0), -1);
         ASSERT_EQ(f(-1.5), -1);
         ASSERT_EQ(f(-2147483648.0), -2147483648);
         ASSERT_EQ(f(-2147483648.5), -2147483648);
       }});
}
#elif FRG_POINTER_BIT_WIDTH == 64
TEST(functional_numeric_types_casting, u8_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> usize {\n"
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

TEST(functional_numeric_types_casting, u8_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> usize {\n"
                 "  return a as usize;\n"
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

TEST(functional_numeric_types_casting, u8_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> isize {\n"
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

TEST(functional_numeric_types_casting, u8_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u8) -> isize {\n"
                 "  return a as isize;\n"
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

TEST(functional_numeric_types_casting, u16_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u16_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u16) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
       }});
}

TEST(functional_numeric_types_casting, u32_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u32_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u32) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, u64_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, u64_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, u64_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: u64) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type u64 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, u64_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: u64) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808LU), -9223372036854775808LU);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, i8_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i8) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i8 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i8_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), 18446744073709551615LU - 127);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i8_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i8_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i8) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i8 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i8 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int8_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
       }});
}

TEST(functional_numeric_types_casting, i16_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i16) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i16 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i16_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), 18446744073709551615LU - 32767);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i16_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i16_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i16) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i16 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i16 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int16_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
       }});
}

TEST(functional_numeric_types_casting, i32_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 18446744073709551615LU - 2147483647);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i32_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i32_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i32) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, i64_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: i64) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i64 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i64_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), 9223372036854775808LU);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, i64_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, i64_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: i64) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, f32_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui float %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(4294967295.0f), 4294967296);
         ASSERT_EQ(f(4294967295.5f), 4294967296);
         ASSERT_EQ(f(4294967296.0f), 4294967296);
         ASSERT_EQ(f(4294967296.5f), 4294967296);
         ASSERT_EQ(f(-1.0f), 0);
         ASSERT_EQ(f(-1.5f), 0);
         ASSERT_EQ(f(-4294967296.0f), 0);
         ASSERT_EQ(f(-4294967296.5f), 0);
       }});
}

TEST(functional_numeric_types_casting, f32_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f32) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f32 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f32_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f32) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(float %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi float %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(float)>("f");

         ASSERT_EQ(f(0.0f), 0);
         ASSERT_EQ(f(5.0f), 5);
         ASSERT_EQ(f(5.5f), 5);
         ASSERT_EQ(f(-5.0f), -5);
         ASSERT_EQ(f(-5.5f), -5);
         ASSERT_EQ(f(9223372036854775807.0f), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775807.5f), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.0f), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.5f), 9223372036854775807LU);
         ASSERT_EQ(f(-1.0f), -1);
         ASSERT_EQ(f(-1.5f), -1);
         ASSERT_EQ(f(-9223372036854775808.0f), -9223372036854775808LU);
         ASSERT_EQ(f(-9223372036854775808.5f), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, f64_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptoui double %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(4294967295.0), 4294967295);
         ASSERT_EQ(f(4294967295.5), 4294967295);
         ASSERT_EQ(f(4294967296.0), 4294967296);
         ASSERT_EQ(f(4294967296.5), 4294967296);
         ASSERT_EQ(f(-1.0), 0);
         ASSERT_EQ(f(-1.5), 0);
         ASSERT_EQ(f(-4294967296.0), 0);
         ASSERT_EQ(f(-4294967296.5), 0);
       }});
}

TEST(functional_numeric_types_casting, f64_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: f64) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type f64 to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, f64_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: f64) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(double %a) {\n"
                                     "entry:\n"
                                     "  %0 = fptosi double %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(double)>("f");

         ASSERT_EQ(f(0.0), 0);
         ASSERT_EQ(f(5.0), 5);
         ASSERT_EQ(f(5.5), 5);
         ASSERT_EQ(f(-5.0), -5);
         ASSERT_EQ(f(-5.5), -5);
         ASSERT_EQ(f(9223372036854775807.0), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775807.5), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.0), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808.5), 9223372036854775807LU);
         ASSERT_EQ(f(-1.0), -1);
         ASSERT_EQ(f(-1.5), -1);
         ASSERT_EQ(f(-9223372036854775808.0), -9223372036854775808LU);
         ASSERT_EQ(f(-9223372036854775808.5), -9223372036854775808LU);
       }});
}
#else
#error "Only 32 and 64 bit architectures are supported"
#endif

#if FRG_POINTER_BIT_WIDTH == 32
TEST(functional_numeric_types_casting, usize_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(4294967295), 255);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(4294967295), 65535);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(128), -128);
         ASSERT_EQ(f(255), -1);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(32768), -32768);
         ASSERT_EQ(f(65535), -1);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = zext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(4294967295), 4294967295.0f);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(4294967295), 4294967295.0f);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(4294967295), 4294967295.0);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(4294967295), 4294967295.0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 255);
         ASSERT_EQ(f(-2147483648), 0);
         ASSERT_EQ(f(-1), 255);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 65535);
         ASSERT_EQ(f(-2147483648), 0);
         ASSERT_EQ(f(-1), 65535);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 2147483648);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 18446744073709551615LU - 2147483647);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
         ASSERT_EQ(f(2147483647), -1);
         ASSERT_EQ(f(-2147483648), 0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i32 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
         ASSERT_EQ(f(2147483647), -1);
         ASSERT_EQ(f(-2147483648), 0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sext i32 %a to i64\n"
                                     "  ret i64 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0f);
         ASSERT_EQ(f(-2147483648), -2147483648.0f);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0f);
         ASSERT_EQ(f(-2147483648), -2147483648.0f);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0);
         ASSERT_EQ(f(-2147483648), -2147483648.0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i32 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647.0);
         ASSERT_EQ(f(-2147483648), -2147483648.0);
       }});
}
#elif FRG_POINTER_BIT_WIDTH == 64
TEST(functional_numeric_types_casting, usize_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(255), 255);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(18446744073709551615LU), 255);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(65535), 65535);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(18446744073709551615LU), 65535);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
         ASSERT_EQ(f(4294967296), 0);
         ASSERT_EQ(f(18446744073709551615LU), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, usize_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(128), -128);
         ASSERT_EQ(f(255), -1);
         ASSERT_EQ(f(256), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(32768), -32768);
         ASSERT_EQ(f(65535), -1);
         ASSERT_EQ(f(65536), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
         ASSERT_EQ(f(4294967296), 0);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_i64_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> i64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to i64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808LU), -9223372036854775808LU);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0f);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0f);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0f);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0);
       }});
}

TEST(functional_numeric_types_casting, usize_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = uitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0.0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615.0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u8_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u8 {\n"
                 "  return a as u8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 255);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 255);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u16_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u16 {\n"
                 "  return a as u16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 65535);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 65535);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u32_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u32 {\n"
                 "  return a as u32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 4294967295);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, isize_to_u64_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> u64 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to u64\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_u64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> u64 {\n"
                 "  return a as u64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), 9223372036854775808LU);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i8_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> i8 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to i8\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_i8_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i8 {\n"
                 "  return a as i8;\n"
                 "}\n",
       .expected_llvm_module_print = "define i8 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i8\n"
                                     "  ret i8 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(127), 127);
         ASSERT_EQ(f(-128), -128);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i16_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> i16 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to i16\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_i16_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i16 {\n"
                 "  return a as i16;\n"
                 "}\n",
       .expected_llvm_module_print = "define i16 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i16\n"
                                     "  ret i16 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(32767), 32767);
         ASSERT_EQ(f(-32768), -32768);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_i32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i32 {\n"
                 "  return a as i32;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = trunc i64 %a to i32\n"
                                     "  ret i32 %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
         ASSERT_EQ(f(9223372036854775807LU), -1);
         ASSERT_EQ(f(-9223372036854775808LU), 0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, isize_to_i64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> i64 {\n"
                 "  return a as i64;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f32_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f32 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0f);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0f);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f32_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f32 {\n"
                 "  return a as f32;\n"
                 "}\n",
       .expected_llvm_module_print = "define float @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to float\n"
                                     "  ret float %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<float (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0f);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0f);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f64_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f64 {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0);
       }});
}

TEST(functional_numeric_types_casting, isize_to_f64_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> f64 {\n"
                 "  return a as f64;\n"
                 "}\n",
       .expected_llvm_module_print = "define double @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  %0 = sitofp i64 %a to double\n"
                                     "  ret double %0\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<double (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807.0);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808.0);
       }});
}
#else
#error "Only 32 and 64 bit architectures are supported"
#endif

#if FRG_POINTER_BIT_WIDTH == 32
TEST(functional_numeric_types_casting, isize_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, isize_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), -2147483648);
       }});
}

TEST(functional_numeric_types_casting, isize_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(int32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(-2147483648), 2147483648);
         ASSERT_EQ(f(-1), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(2147483647), 2147483647);
         ASSERT_EQ(f(2147483648), -2147483648);
         ASSERT_EQ(f(4294967295), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}

TEST(functional_numeric_types_casting, usize_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i32 @f(i32 %a) {\n"
                                     "entry:\n"
                                     "  ret i32 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)(uint32_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(4294967295), 4294967295);
       }});
}
#elif FRG_POINTER_BIT_WIDTH == 64
TEST(functional_numeric_types_casting, isize_to_isize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> isize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, isize_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), -9223372036854775808LU);
       }});
}

TEST(functional_numeric_types_casting, isize_to_usize_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> usize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to usize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: isize) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(int64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(-9223372036854775808LU), 9223372036854775808LU);
         ASSERT_EQ(f(-1), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, usize_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: usize) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type usize to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, usize_to_isize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> isize {\n"
                 "  return a as isize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(9223372036854775807LU), 9223372036854775807LU);
         ASSERT_EQ(f(9223372036854775808LU), -9223372036854775808LU);
         ASSERT_EQ(f(18446744073709551615LU), -1);
       }});
}

TEST(functional_numeric_types_casting, usize_to_usize_implicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> usize {\n"
                 "  return a;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}

TEST(functional_numeric_types_casting, usize_to_usize_explicit) {
  runFunctionalTest(
      {.source = "func f(a: usize) -> usize {\n"
                 "  return a as usize;\n"
                 "}\n",
       .expected_llvm_module_print = "define i64 @f(i64 %a) {\n"
                                     "entry:\n"
                                     "  ret i64 %a\n"
                                     "}\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)(uint64_t)>("f");

         ASSERT_EQ(f(0), 0);
         ASSERT_EQ(f(18446744073709551615LU), 18446744073709551615LU);
       }});
}
#else
#error "Only 32 and 64 bit architectures are supported"
#endif

TEST(functional_numeric_types_casting, bool_to_i32_implicit) {
  runFunctionalTest({
      .source = "func f(a: bool) -> i32 {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type bool to i32\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, bool_to_isize_implicit) {
  runFunctionalTest({
      .source = "func f(a: bool) -> isize {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type bool to isize\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, i32_to_bool_implicit) {
  runFunctionalTest({
      .source = "func f(a: i32) -> bool {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to bool\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, isize_to_bool_implicit) {
  runFunctionalTest({
      .source = "func f(a: isize) -> bool {\n"
                "  return a;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type isize to bool\n"
                                 "\n"
                                 "2  return a;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_casting, bool_to_bool_implicit) {
  runFunctionalTest({.source = "func f(a: bool) -> bool {\n"
                               "  return a;\n"
                               "}\n",
                     .expected_llvm_module_print = "define i1 @f(i1 %a) {\n"
                                                   "entry:\n"
                                                   "  ret i1 %a\n"
                                                   "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<bool (*)(bool)>("f");

                       ASSERT_EQ(f(true), true);
                       ASSERT_EQ(f(false), false);
                     }});
}

TEST(functional_numeric_types_casting, bool_to_bool_explicit) {
  runFunctionalTest({.source = "func f(a: bool) -> bool {\n"
                               "  return a as bool;\n"
                               "}\n",
                     .expected_llvm_module_print = "define i1 @f(i1 %a) {\n"
                                                   "entry:\n"
                                                   "  ret i1 %a\n"
                                                   "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<bool (*)(bool)>("f");

                       ASSERT_EQ(f(true), true);
                       ASSERT_EQ(f(false), false);
                     }});
}
