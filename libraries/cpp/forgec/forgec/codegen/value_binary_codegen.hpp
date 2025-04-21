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

#include <forgec/syntax_tree/values/value_binary.hpp>
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/messaging/message_context.hpp>

namespace forge {
std::shared_ptr<BaseType> get_value_binary_casted_operand_type(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueBinary>& node);

struct CodegenValueBinaryInfo {
  BinaryOperator operator_;

  std::shared_ptr<BaseType> casted_operand_type;
  bool are_casted_operands_float;
  bool are_casted_operands_signed;

  llvm::Value* llvm_lhs;
  llvm::Value* llvm_rhs;
};

CodegenValueBinaryInfo codegen_value_binary_info(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueBinary>& node);

llvm::Value* codegen_value_binary_non_assignment(
    lt::CodegenContext& codegen_context, const CodegenValueBinaryInfo& info);

llvm::Value* codegen_value_binary_assignment(
    lt::CodegenContext& codegen_context, const CodegenValueBinaryInfo& info);

llvm::Value* codegen_value_binary_compound_assignment(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueBinary>& node,
    const CodegenValueBinaryInfo& info);

llvm::Value* codegen_value_binary(lt::CodegenContext& codegen_context,
                                  const std::shared_ptr<ValueBinary>& node);
}  // namespace forge
