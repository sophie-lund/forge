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

#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/type_logic/type_predicates.hpp>

using namespace forge;

TEST(language_type_logic_type_predicates, is_type_void) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::void_);
  ASSERT_TRUE(is_type_void(type));
}
