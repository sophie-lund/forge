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

// It's a no-op so we don't have to test it too much

TEST(functional_std_samples_limits, DISABLED_compile) {
  runFunctionalTest({
      .source = "// Copyright 2025 Sophie Lund\n"
                "//\n"
                "// This file is part of Forge.\n"
                "//\n"
                "// Forge is free software: you can redistribute it and/or "
                "modify it under the\n"
                "// terms of the GNU General Public License as published by "
                "the Free Software\n"
                "// Foundation, either version 3 of the License, or (at your "
                "option) any later\n"
                "// version.\n"
                "//\n"
                "// Forge is distributed in the hope that it will be useful, "
                "but WITHOUT ANY\n"
                "// WARRANTY; without even the implied warranty of "
                "MERCHANTABILITY or FITNESS FOR\n"
                "// A PARTICULAR PURPOSE. See the GNU General Public License "
                "for more details.\n"
                "//\n"
                "// You should have received a copy of the GNU General Public "
                "License along with\n"
                "// Forge. If not, see <https://www.gnu.org/licenses/>.\n"
                "\n"
                "const U8_MIN = 0u8;\n"
                "const U8_MAX = 0xffu8;\n"
                "\n"
                "const U16_MIN = 0u16;\n"
                "const U16_MAX = 0xffffu16;\n"
                "\n"
                "const U32_MIN = 0u32;\n"
                "const U32_MAX = 0xffffffffu32;\n"
                "\n"
                "const U64_MIN = 0u64;\n"
                "const U64_MAX = 0xffffffffffffffffu64;\n"
                "\n"
                "const I8_MIN = -128i8;\n"
                "const I8_MAX = 127i8;\n"
                "\n"
                "const I16_MIN = -32768i16;\n"
                "const I16_MAX = 32767i16;\n"
                "\n"
                "const I32_MIN = -2147483648i32;\n"
                "const I32_MAX = 2147483647i32;\n"
                "\n"
                "const I64_MIN = -9_223_372_036_854_775_808i64;\n"
                "const I64_MAX = 9_223_372_036_854_775_807i64;\n"
                "\n",
  });
}
