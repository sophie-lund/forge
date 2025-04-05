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

#pragma once

#include <forge/language/syntax_tree/types/base_type.hpp>

namespace forge {
bool is_type_void(const BaseType& type);
bool is_type_bool(const BaseType& type);
bool is_type_integer(const BaseType& type);
std::optional<bool> is_integer_type_signed(const BaseType& type);
bool is_type_float(const BaseType& type);
bool is_type_pointer(const BaseType& type);
std::shared_ptr<BaseType> try_get_pointer_element_type(const BaseType& type);
}  // namespace forge
