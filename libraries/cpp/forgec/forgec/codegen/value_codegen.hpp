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

#include <forgec/syntax_tree/values/value_call.hpp>
#include <forgec/syntax_tree/values/value_cast.hpp>
#include <forgec/syntax_tree/values/value_literal_bool.hpp>
#include <forgec/syntax_tree/values/value_literal_number.hpp>
#include <forgec/syntax_tree/values/value_symbol.hpp>
#include <forgec/syntax_tree/values/value_unary.hpp>
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/messaging/message_context.hpp>

namespace forge {
llvm::Value* codegen_value_literal_bool(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralBool>& node);

llvm::Value* codegen_value_literal_number(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralNumber>& node);

llvm::Value* codegen_value_symbol(lt::CodegenContext&,
                                  const std::shared_ptr<ValueSymbol>& node);

llvm::Value* codegen_value_unary(lt::CodegenContext& codegen_context,
                                 const std::shared_ptr<ValueUnary>& node);

llvm::Value* codegen_value_call(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCall>& node);

llvm::Value* codegen_value_cast(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCast>& node);

llvm::Value* codegen_value(lt::CodegenContext& codegen_context,
                           const std::shared_ptr<BaseValue>& node);

llvm::Value* codegen_value_lvalue(lt::CodegenContext& codegen_context,
                                  const std::shared_ptr<BaseValue>& node);

llvm::Value* codegen_value_implicit_cast(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<BaseValue>& value,
    const std::shared_ptr<BaseType>& to);
}  // namespace forge
