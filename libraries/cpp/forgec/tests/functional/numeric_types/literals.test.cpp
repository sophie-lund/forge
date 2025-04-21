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

TEST(functional_numeric_types_literals, int_without_prefix_type) {
  runFunctionalTest({
      .source = "func f() -> u8 {\n"
                "  return 0;\n"
                "}\n",
      .expected_state = FunctionalTestOptionsState::errors_after_passes,
      .expected_message_report = "--:2:10 - error ETY005: unable to implicitly "
                                 "cast from type i32 to u8\n"
                                 "\n"
                                 "2  return 0;\n"
                                 "          ^ \n"
                                 "\n"
                                 "suggestion: use 'as' to cast between types\n"
                                 "\n"
                                 "1 error\n",
  });
}

TEST(functional_numeric_types_literals, int_without_prefix_max) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  return 2147483647;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 2147483647);
                     }});
}

TEST(functional_numeric_types_literals, int_without_prefix_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  return 2147483648;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i32\n"
           "\n"
           "2  return 2147483648;\n"
           "          ^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as 2147483648\n"
           "\n"
           "note: but got truncated to -2147483648\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), -2147483648);
       }});
}

TEST(functional_numeric_types_literals, int_without_prefix_min) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  return -2147483648;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), -2147483648);
                     }});
}

TEST(functional_numeric_types_literals, int_without_prefix_min_minus_one) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  return -2147483649;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i32\n"
           "\n"
           "2  return -2147483649;\n"
           "          ^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as -2147483649\n"
           "\n"
           "note: but got truncated to 2147483647\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 2147483647);
       }});
}

TEST(functional_numeric_types_literals, u8_max) {
  runFunctionalTest({.source = "func f() -> u8 {\n"
                               "  return 255u8;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<uint8_t (*)()>("f");

                       ASSERT_EQ(f(), 255);
                     }});
}

TEST(functional_numeric_types_literals, u8_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> u8 {\n"
                 "  return 256u8;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type u8\n"
           "\n"
           "2  return 256u8;\n"
           "          ^^^^^ \n"
           "\n"
           "note: was parsed as 256\n"
           "\n"
           "note: but got truncated to 0\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint8_t (*)()>("f");

         ASSERT_EQ(f(), 0);
       }});
}

TEST(functional_numeric_types_literals, u16_max) {
  runFunctionalTest({.source = "func f() -> u16 {\n"
                               "  return 65535u16;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<uint16_t (*)()>("f");

                       ASSERT_EQ(f(), 65535);
                     }});
}

TEST(functional_numeric_types_literals, u16_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> u16 {\n"
                 "  return 65536u16;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type u16\n"
           "\n"
           "2  return 65536u16;\n"
           "          ^^^^^^^^ \n"
           "\n"
           "note: was parsed as 65536\n"
           "\n"
           "note: but got truncated to 0\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint16_t (*)()>("f");

         ASSERT_EQ(f(), 0);
       }});
}

TEST(functional_numeric_types_literals, u32_max) {
  runFunctionalTest({.source = "func f() -> u32 {\n"
                               "  return 4294967295u32;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<uint32_t (*)()>("f");

                       ASSERT_EQ(f(), 4294967295);
                     }});
}

TEST(functional_numeric_types_literals, u32_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> u32 {\n"
                 "  return 4294967296u32;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type u32\n"
           "\n"
           "2  return 4294967296u32;\n"
           "          ^^^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as 4294967296\n"
           "\n"
           "note: but got truncated to 0\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint32_t (*)()>("f");

         ASSERT_EQ(f(), 0);
       }});
}

TEST(functional_numeric_types_literals, u64_max) {
  runFunctionalTest({.source = "func f() -> u64 {\n"
                               "  return 18446744073709551615u64;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<uint64_t (*)()>("f");

                       ASSERT_EQ(f(), 18446744073709551615LU);
                     }});
}

TEST(functional_numeric_types_literals, DISABLED_u64_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> u64 {\n"
                 "  return 18446744073709551616u64;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type u64\n"
           "\n"
           "2  return 18446744073709551616u64;\n"
           "          ^^^^^^^^^^^^^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as 18446744073709551616\n"
           "\n"
           "note: but got truncated to 0\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<uint64_t (*)()>("f");

         ASSERT_EQ(f(), 0);
       }});
}

TEST(functional_numeric_types_literals, i8_min) {
  runFunctionalTest({.source = "func f() -> i8 {\n"
                               "  return -128i8;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int8_t (*)()>("f");

                       ASSERT_EQ(f(), -128);
                     }});
}

TEST(functional_numeric_types_literals, i8_min_minus_one) {
  runFunctionalTest(
      {.source = "func f() -> i8 {\n"
                 "  return -129i8;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i8\n"
           "\n"
           "2  return -129i8;\n"
           "          ^^^^^^ \n"
           "\n"
           "note: was parsed as -129\n"
           "\n"
           "note: but got truncated to 127\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)()>("f");

         ASSERT_EQ(f(), 127);
       }});
}

TEST(functional_numeric_types_literals, i8_max) {
  runFunctionalTest({.source = "func f() -> i8 {\n"
                               "  return 127i8;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int8_t (*)()>("f");

                       ASSERT_EQ(f(), 127);
                     }});
}

TEST(functional_numeric_types_literals, i8_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> i8 {\n"
                 "  return 128i8;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i8\n"
           "\n"
           "2  return 128i8;\n"
           "          ^^^^^ \n"
           "\n"
           "note: was parsed as 128\n"
           "\n"
           "note: but got truncated to -128\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int8_t (*)()>("f");

         ASSERT_EQ(f(), -128);
       }});
}

TEST(functional_numeric_types_literals, i16_min) {
  runFunctionalTest({.source = "func f() -> i16 {\n"
                               "  return -32768i16;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int16_t (*)()>("f");

                       ASSERT_EQ(f(), -32768);
                     }});
}

TEST(functional_numeric_types_literals, i16_min_minus_one) {
  runFunctionalTest(
      {.source = "func f() -> i16 {\n"
                 "  return -32769i16;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i16\n"
           "\n"
           "2  return -32769i16;\n"
           "          ^^^^^^^^^ \n"
           "\n"
           "note: was parsed as -32769\n"
           "\n"
           "note: but got truncated to 32767\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)()>("f");

         ASSERT_EQ(f(), 32767);
       }});
}

TEST(functional_numeric_types_literals, i16_max) {
  runFunctionalTest({.source = "func f() -> i16 {\n"
                               "  return 32767i16;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int16_t (*)()>("f");

                       ASSERT_EQ(f(), 32767);
                     }});
}

TEST(functional_numeric_types_literals, i16_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> i16 {\n"
                 "  return 32768i16;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i16\n"
           "\n"
           "2  return 32768i16;\n"
           "          ^^^^^^^^ \n"
           "\n"
           "note: was parsed as 32768\n"
           "\n"
           "note: but got truncated to -32768\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int16_t (*)()>("f");

         ASSERT_EQ(f(), -32768);
       }});
}

TEST(functional_numeric_types_literals, i32_min) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  return -2147483648i32;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), -2147483648);
                     }});
}

TEST(functional_numeric_types_literals, i32_min_minus_one) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  return -2147483649i32;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i32\n"
           "\n"
           "2  return -2147483649i32;\n"
           "          ^^^^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as -2147483649\n"
           "\n"
           "note: but got truncated to 2147483647\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), 2147483647);
       }});
}

TEST(functional_numeric_types_literals, i32_max) {
  runFunctionalTest({.source = "func f() -> i32 {\n"
                               "  return 2147483647i32;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int32_t (*)()>("f");

                       ASSERT_EQ(f(), 2147483647);
                     }});
}

TEST(functional_numeric_types_literals, i32_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> i32 {\n"
                 "  return 2147483648i32;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i32\n"
           "\n"
           "2  return 2147483648i32;\n"
           "          ^^^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as 2147483648\n"
           "\n"
           "note: but got truncated to -2147483648\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int32_t (*)()>("f");

         ASSERT_EQ(f(), -2147483648);
       }});
}

TEST(functional_numeric_types_literals, DISABLED_i64_min) {
  runFunctionalTest({.source = "func f() -> i64 {\n"
                               "  return -9223372036854775808i64;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int64_t (*)()>("f");

                       ASSERT_EQ(f(), -9223372036854775808LU);
                     }});
}

TEST(functional_numeric_types_literals, DISABLED_i64_min_minus_one) {
  runFunctionalTest(
      {.source = "func f() -> i64 {\n"
                 "  return -9223372036854775809i64;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i64\n"
           "\n"
           "2  return -9223372036854775809i64;\n"
           "          ^^^^^^^^^^^^^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as -9223372036854775809\n"
           "\n"
           "note: but got truncated to 9223372036854775807\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)()>("f");

         ASSERT_EQ(f(), 9223372036854775807);
       }});
}

TEST(functional_numeric_types_literals, i64_max) {
  runFunctionalTest({.source = "func f() -> i64 {\n"
                               "  return 9223372036854775807i64;\n"
                               "}\n",
                     .on_jit_context = [](const lt::JITContext& jit_context) {
                       auto f =
                           jit_context.try_lookup_function<int64_t (*)()>("f");

                       ASSERT_EQ(f(), 9223372036854775807LU);
                     }});
}

TEST(functional_numeric_types_literals, DISABLED_i64_max_plus_one) {
  runFunctionalTest(
      {.source = "func f() -> i64 {\n"
                 "  return 9223372036854775808i64;\n"
                 "}\n",
       .expected_message_report =
           "--:2:10 - warning WSY001: literal value does not fit in type i64\n"
           "\n"
           "2  return 9223372036854775808i64;\n"
           "          ^^^^^^^^^^^^^^^^^^^^^^ \n"
           "\n"
           "note: was parsed as 9223372036854775808\n"
           "\n"
           "note: but got truncated to -9223372036854775808\n"
           "\n"
           "1 warning\n",
       .on_jit_context = [](const lt::JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<int64_t (*)()>("f");

         ASSERT_EQ(f(), -9223372036854775808LU);
       }});
}
