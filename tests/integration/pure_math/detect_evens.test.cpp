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

#include <forge/testing/integration_test_harness.hpp>

using namespace forge;

// Taken from https://softwareengineering.stackexchange.com/a/17414

TEST(integration_pure_math_detect_evens, readable) {
  runIntegrationTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  return a % 2 == 0;\n"
                 "}\n",
       .on_jit_context = [](const JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(int32_t)>("f");

         ASSERT_EQ(f(0), true);
         ASSERT_EQ(f(1), false);
         ASSERT_EQ(f(2), true);
         ASSERT_EQ(f(3), false);
       }});
}

TEST(integration_pure_math_detect_evens, with_bit_and) {
  runIntegrationTest(
      {.source = "func f(a: i32) -> bool {\n"
                 "  return a & 1 == 0;\n"
                 "}\n",
       .on_jit_context = [](const JITContext& jit_context) {
         auto f = jit_context.try_lookup_function<bool (*)(int32_t)>("f");

         ASSERT_EQ(f(0), true);
         ASSERT_EQ(f(1), false);
         ASSERT_EQ(f(2), true);
         ASSERT_EQ(f(3), false);
       }});
}
