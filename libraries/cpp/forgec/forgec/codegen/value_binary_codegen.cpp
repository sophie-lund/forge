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

#include <forgec/codegen/value_binary_codegen.hpp>
#include <forgec/codegen/value_codegen.hpp>
#include <forgec/logic/types/get_arithmetic_containing_type.hpp>
#include <forgec/logic/types/type_predicates.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>

namespace forge {
std::shared_ptr<BaseType> get_value_binary_casted_operand_type(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueBinary>& node) {
  // Comparisons cannot be implicitly casted to i1 before comparing, so we
  // calculate the arithmetic containing type on the fly
  if (is_binary_operator_comparison(node->operator_)) {
    return get_arithmetic_containing_type(
        codegen_context, node->lhs->resolved_type, node->rhs->resolved_type);
  }

  return node->resolved_type;
}

CodegenValueBinaryInfo codegen_value_binary_info(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueBinary>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(node->lhs != nullptr,
            "cannot codegen binary operation with null lhs");
  LT_ASSERT(
      node->lhs->resolved_type != nullptr,
      "cannot codegen binary operation with lhs that has unresolved type");
  LT_ASSERT(node->rhs != nullptr,
            "cannot codegen binary operation with null rhs");
  LT_ASSERT(
      node->rhs->resolved_type != nullptr,
      "cannot codegen binary operation with rhs that has unresolved type");
  LT_ASSERT(node->resolved_type != nullptr,
            "cannot codegen binary operation with unresolved type");

  CodegenValueBinaryInfo info;

  info.operator_ = node->operator_;

  info.casted_operand_type =
      get_value_binary_casted_operand_type(codegen_context, node);

  info.are_casted_operands_float = is_type_float(info.casted_operand_type);
  info.are_casted_operands_signed =
      get_integer_type_signedness(info.casted_operand_type).value_or(false);

  if (node->operator_ == BinaryOperator::assign ||
      try_get_compound_assignment_base_operator(node->operator_).has_value()) {
    info.llvm_lhs = codegen_value_lvalue(codegen_context, node->lhs);
  } else {
    info.llvm_lhs = codegen_value_implicit_cast(codegen_context, node->lhs,
                                                info.casted_operand_type);
  }
  info.llvm_rhs = codegen_value_implicit_cast(codegen_context, node->rhs,
                                              info.casted_operand_type);

  return info;
}

llvm::Value* codegen_value_binary_non_assignment(
    lt::CodegenContext& codegen_context, const CodegenValueBinaryInfo& info) {
  switch (info.operator_) {
    case BinaryOperator::bool_and:
      return codegen_context.llvm_builder().CreateAnd(info.llvm_lhs,
                                                      info.llvm_rhs);
    case BinaryOperator::bool_or:
      return codegen_context.llvm_builder().CreateOr(info.llvm_lhs,
                                                     info.llvm_rhs);
    case BinaryOperator::bit_and:
      return codegen_context.llvm_builder().CreateAnd(info.llvm_lhs,
                                                      info.llvm_rhs);
    case BinaryOperator::bit_and_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::bit_or:
      return codegen_context.llvm_builder().CreateOr(info.llvm_lhs,
                                                     info.llvm_rhs);
    case BinaryOperator::bit_or_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::bit_xor:
      return codegen_context.llvm_builder().CreateXor(info.llvm_lhs,
                                                      info.llvm_rhs);
    case BinaryOperator::bit_xor_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::bit_shl:
      return codegen_context.llvm_builder().CreateShl(info.llvm_lhs,
                                                      info.llvm_rhs);
    case BinaryOperator::bit_shl_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::bit_shr:
      return codegen_context.llvm_builder().CreateLShr(info.llvm_lhs,
                                                       info.llvm_rhs);
    case BinaryOperator::bit_shr_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::add:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFAdd(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateAdd(info.llvm_lhs,
                                                        info.llvm_rhs);
      }
    case BinaryOperator::add_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::sub:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFSub(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateSub(info.llvm_lhs,
                                                        info.llvm_rhs);
      }
    case BinaryOperator::sub_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::mul:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFMul(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateMul(info.llvm_lhs,
                                                        info.llvm_rhs);
      }
    case BinaryOperator::mul_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::exp:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::exp_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::div:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFDiv(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else if (info.are_casted_operands_signed) {
        return codegen_context.llvm_builder().CreateSDiv(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateUDiv(info.llvm_lhs,
                                                         info.llvm_rhs);
      }
    case BinaryOperator::div_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::mod:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFRem(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else if (info.are_casted_operands_signed) {
        return codegen_context.llvm_builder().CreateSRem(info.llvm_lhs,
                                                         info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateURem(info.llvm_lhs,
                                                         info.llvm_rhs);
      }
    case BinaryOperator::mod_assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::assign:
      LT_ABORT("function does not support compound assignment");
    case BinaryOperator::eq:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFCmpOEQ(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpEQ(info.llvm_lhs,
                                                           info.llvm_rhs);
      }
    case BinaryOperator::ne:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFCmpONE(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpNE(info.llvm_lhs,
                                                           info.llvm_rhs);
      }
    case BinaryOperator::lt:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFCmpOLT(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else if (info.are_casted_operands_signed) {
        return codegen_context.llvm_builder().CreateICmpSLT(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpULT(info.llvm_lhs,
                                                            info.llvm_rhs);
      }
    case BinaryOperator::le:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFCmpOLE(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else if (info.are_casted_operands_signed) {
        return codegen_context.llvm_builder().CreateICmpSLE(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpULE(info.llvm_lhs,
                                                            info.llvm_rhs);
      }
    case BinaryOperator::gt:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFCmpOGT(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else if (info.are_casted_operands_signed) {
        return codegen_context.llvm_builder().CreateICmpSGT(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpUGT(info.llvm_lhs,
                                                            info.llvm_rhs);
      }
    case BinaryOperator::ge:
      if (info.are_casted_operands_float) {
        return codegen_context.llvm_builder().CreateFCmpOGE(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else if (info.are_casted_operands_signed) {
        return codegen_context.llvm_builder().CreateICmpSGE(info.llvm_lhs,
                                                            info.llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpUGE(info.llvm_lhs,
                                                            info.llvm_rhs);
      }
    case BinaryOperator::member_access:
      LT_TODO();
  }
}

llvm::Value* codegen_value_binary_assignment(
    lt::CodegenContext& codegen_context, const CodegenValueBinaryInfo& info) {
  LT_ASSERT(info.operator_ == BinaryOperator::assign,
            "function only support '=' operator");

  // Yes, LHS and RHS are supposed to be reversed like this
  return codegen_context.llvm_builder().CreateStore(info.llvm_rhs,
                                                    info.llvm_lhs);
}

llvm::Value* codegen_value_binary_compound_assignment(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueBinary>& node,
    const CodegenValueBinaryInfo& info) {
  std::optional<BinaryOperator> base_operator =
      try_get_compound_assignment_base_operator(info.operator_);

  LT_ASSERT(base_operator.has_value(),
            "function only support compound assignment operators");

  CodegenValueBinaryInfo base_info = info;
  base_info.operator_ = base_operator.value();
  base_info.llvm_lhs = codegen_value_implicit_cast(codegen_context, node->lhs,
                                                   info.casted_operand_type);

  CodegenValueBinaryInfo assignment_info;
  assignment_info.operator_ = BinaryOperator::assign;
  assignment_info.llvm_lhs = info.llvm_lhs;
  assignment_info.llvm_rhs =
      codegen_value_binary_non_assignment(codegen_context, base_info);

  return codegen_value_binary_assignment(codegen_context, assignment_info);
}

llvm::Value* codegen_value_binary(lt::CodegenContext& codegen_context,
                                  const std::shared_ptr<ValueBinary>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  CodegenValueBinaryInfo info =
      codegen_value_binary_info(codegen_context, node);

  if (try_get_compound_assignment_base_operator(node->operator_).has_value()) {
    return codegen_value_binary_compound_assignment(codegen_context, node,
                                                    info);
  } else if (node->operator_ == BinaryOperator::assign) {
    return codegen_value_binary_assignment(codegen_context, info);
  } else {
    return codegen_value_binary_non_assignment(codegen_context, info);
  }
}
}  // namespace forge
