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

#include <forgec/syntax_tree/types/type_basic.hpp>
#include <forgec/syntax_tree/types/type_function.hpp>
#include <forgec/syntax_tree/types/type_structured.hpp>
#include <forgec/syntax_tree/types/type_symbol.hpp>
#include <forgec/syntax_tree/types/type_unary.hpp>
#include <forgec/syntax_tree/types/type_with_bit_width.hpp>
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/messaging/message_context.hpp>

namespace forge {
llvm::Type* codegen_type_basic(lt::CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node);

llvm::Type* codegen_type_basic_for_casting(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeBasic>& node);

llvm::Type* codegen_type_with_bit_width(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeWithBitWidth>& node);

llvm::Type* codegen_type_symbol(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node);

llvm::Type* codegen_type_unary(lt::CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node);

llvm::FunctionType* codegen_type_function(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeFunction>& node);

llvm::StructType* codegen_type_structured(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeStructured>& node);

llvm::Type* codegen_type(lt::CodegenContext& codegen_context,
                         const std::shared_ptr<BaseType>& node);

llvm::Type* codegen_type_for_casting(lt::CodegenContext& codegen_context,
                                     const std::shared_ptr<BaseType>& node);
}  // namespace forge
