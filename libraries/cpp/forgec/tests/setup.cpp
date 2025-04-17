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

#include <langtools/core/assert.hpp>
#include <langtools/core/init.hpp>

class GlobalEnvironment : public ::testing::Environment {
 public:
  void SetUp() override {
    if (!lt::init()) {
      LT_ABORT("unable to init Langtools");
    }
  }

  void TearDown() override {
    if (!lt::cleanup()) {
      LT_ABORT("unable to cleanup Langtools");
    }
  }
};

::testing::Environment* const global_env =
    ::testing::AddGlobalTestEnvironment(new GlobalEnvironment);
