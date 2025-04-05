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

#include <forge/codegen/codegen_context.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_function.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/messaging/message_context.hpp>

namespace forge {
llvm::Type* codegen_type_basic(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node);

llvm::Type* codegen_type_symbol(CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node);

llvm::Type* codegen_type_unary(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node);

llvm::Type* codegen_type(CodegenContext& codegen_context,
                         const std::shared_ptr<BaseType>& node);
}  // namespace forge
