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

#include <forge/core/math_utilities.hpp>

using namespace forge;

TEST(core_math_utilities, count_digits_in_integer) {
  ASSERT_EQ(count_digits_in_integer(0), 1);
  ASSERT_EQ(count_digits_in_integer(1), 1);
  ASSERT_EQ(count_digits_in_integer(9), 1);
  ASSERT_EQ(count_digits_in_integer(10), 2);
  ASSERT_EQ(count_digits_in_integer(99), 2);
  ASSERT_EQ(count_digits_in_integer(100), 3);
  ASSERT_EQ(count_digits_in_integer(999), 3);
  ASSERT_EQ(count_digits_in_integer(1000), 4);
  ASSERT_EQ(count_digits_in_integer(9999), 4);
  ASSERT_EQ(count_digits_in_integer(10000), 5);
  ASSERT_EQ(count_digits_in_integer(99999), 5);
  ASSERT_EQ(count_digits_in_integer(100000), 6);
  ASSERT_EQ(count_digits_in_integer(999999), 6);
  ASSERT_EQ(count_digits_in_integer(-1), 1);
  ASSERT_EQ(count_digits_in_integer(-9), 1);
  ASSERT_EQ(count_digits_in_integer(-10), 2);
  ASSERT_EQ(count_digits_in_integer(-99), 2);
  ASSERT_EQ(count_digits_in_integer(-100), 3);
  ASSERT_EQ(count_digits_in_integer(-999), 3);
  ASSERT_EQ(count_digits_in_integer(-1000), 4);
  ASSERT_EQ(count_digits_in_integer(-9999), 4);
  ASSERT_EQ(count_digits_in_integer(-10000), 5);
  ASSERT_EQ(count_digits_in_integer(-99999), 5);
  ASSERT_EQ(count_digits_in_integer(-100000), 6);
  ASSERT_EQ(count_digits_in_integer(-999999), 6);
}
