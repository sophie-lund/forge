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

#include <forgec/syntax_tree/types/base_type.hpp>
#include <langtools/codegen/codegen_context.hpp>

namespace forge {
std::shared_ptr<BaseType> get_arithmetic_containing_type(
    const lt::CodegenContext &codegen_context,
    const std::shared_ptr<BaseType> &a, const std::shared_ptr<BaseType> &b);
}
