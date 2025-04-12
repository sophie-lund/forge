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

#include <llvm/IR/Verifier.h>

#include <forge/language/forge_codegen.hpp>
#include <forge/language/type_logic/type_predicates.hpp>
#include <forge/syntax_tree/operations/casting.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
llvm::Type* codegen_type_basic(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->type_basic_kind) {
    case TypeBasicKind::bool_:
      return codegen_context.llvm_builder().getInt1Ty();
    case TypeBasicKind::void_:
      return codegen_context.llvm_builder().getVoidTy();
    case TypeBasicKind::isize:
    case TypeBasicKind::usize:
      return codegen_context.llvm_builder().getIntPtrTy(
          codegen_context.llvm_module().getDataLayout());
  }
}

llvm::Type* codegen_type_basic_for_casting(
    CodegenContext& codegen_context, const std::shared_ptr<TypeBasic>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->type_basic_kind) {
    case TypeBasicKind::bool_:
      return codegen_context.llvm_builder().getInt1Ty();
    case TypeBasicKind::isize:
    case TypeBasicKind::usize:
      return codegen_context.llvm_builder().getIntPtrTy(
          codegen_context.llvm_module().getDataLayout());
    default:
      FRG_ABORT("unsupported type for casting");
  }
}

llvm::Type* codegen_type_with_bit_width(
    CodegenContext& codegen_context,
    const std::shared_ptr<TypeWithBitWidth>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->type_with_bit_width_kind) {
    case TypeWithBitWidthKind::signed_int:
    case TypeWithBitWidthKind::unsigned_int:
      if (node->bit_width == 8) {
        return codegen_context.llvm_builder().getInt8Ty();
      } else if (node->bit_width == 16) {
        return codegen_context.llvm_builder().getInt16Ty();
      } else if (node->bit_width == 32) {
        return codegen_context.llvm_builder().getInt32Ty();
      } else if (node->bit_width == 64) {
        return codegen_context.llvm_builder().getInt64Ty();
      } else {
        FRG_ABORT("unsupported integer bit width: " << node->bit_width);
      }
    case TypeWithBitWidthKind::float_:
      if (node->bit_width == 32) {
        return codegen_context.llvm_builder().getFloatTy();
      } else if (node->bit_width == 64) {
        return codegen_context.llvm_builder().getDoubleTy();
      } else {
        FRG_ABORT("unsupported float bit width: " << node->bit_width);
      }
  }
}

llvm::Type* codegen_type_symbol(CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  FRG_ASSERT(node->referenced_declaration != nullptr,
             "cannot codegen symbol that has not been resolved");

  FRG_ASSERT(
      node->referenced_declaration->resolved_type != nullptr,
      "cannot codegen symbol that references declaration with unresolved type");

  return codegen_type(codegen_context,
                      node->referenced_declaration->resolved_type);
}

llvm::Type* codegen_type_unary(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->type_unary_kind) {
    case TypeUnaryKind::pointer:
      return codegen_context.llvm_builder().getPtrTy();
  }
}

llvm::FunctionType* codegen_type_function(
    CodegenContext& codegen_context,
    const std::shared_ptr<TypeFunction>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  std::vector<llvm::Type*> llvm_arg_types;

  for (const std::shared_ptr<BaseType>& arg_type : node->arg_types) {
    FRG_ASSERT(arg_type != nullptr,
               "cannot codegen null argument type in function type");

    llvm_arg_types.push_back(codegen_type(codegen_context, arg_type));
  }

  FRG_ASSERT(node->return_type != nullptr,
             "cannot codegen null return type in function type");

  llvm::Type* llvm_return_type =
      codegen_type(codegen_context, node->return_type);

  return llvm::FunctionType::get(llvm_return_type, llvm_arg_types, false);
}

llvm::StructType* codegen_type_structured(
    CodegenContext& codegen_context,
    const std::shared_ptr<TypeStructured>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  std::vector<llvm::Type*> llvm_member_types;

  for (const std::shared_ptr<BaseDeclaration>& member : node->members) {
    FRG_ASSERT(member != nullptr,
               "cannot codegen null member type in structured type");

    llvm_member_types.push_back(
        codegen_type(codegen_context, member->resolved_type));
  }

  FRG_ASSERT(!llvm_member_types.empty(),
             "cannot codegen empty structured type");

  return llvm::StructType::create(codegen_context.llvm_module().getContext(),
                                  llvm_member_types);
}

llvm::Type* codegen_type(CodegenContext& codegen_context,
                         const std::shared_ptr<BaseType>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<TypeBasic>(node); casted) {
    return codegen_type_basic(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(node); casted) {
    return codegen_type_with_bit_width(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeSymbol>(node); casted) {
    return codegen_type_symbol(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeUnary>(node); casted) {
    return codegen_type_unary(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeFunction>(node); casted) {
    return codegen_type_function(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeStructured>(node); casted) {
    return codegen_type_structured(codegen_context, casted);
  } else {
    FRG_ABORT("unsupported type kind");
  }
}

llvm::Type* codegen_type_for_casting(CodegenContext& codegen_context,
                                     const std::shared_ptr<BaseType>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<TypeBasic>(node); casted) {
    return codegen_type_basic_for_casting(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(node); casted) {
    return codegen_type_with_bit_width(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeUnary>(node); casted) {
    return codegen_type_unary(codegen_context, casted);
  } else {
    FRG_ABORT("unsupported type kind for casting");
  }
}

llvm::Value* codegen_value_literal_bool(
    CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralBool>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  return codegen_context.llvm_builder().getInt1(node->value);
}

llvm::Value* codegen_value_literal_number(
    CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralNumber>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(node->type != nullptr,
             "cannot codegen literal number with null type");

  if (node->type->type_with_bit_width_kind ==
          TypeWithBitWidthKind::signed_int ||
      node->type->type_with_bit_width_kind ==
          TypeWithBitWidthKind::unsigned_int) {
    if (node->type->bit_width == 8) {
      return codegen_context.llvm_builder().getInt8(node->value.u8);
    } else if (node->type->bit_width == 16) {
      return codegen_context.llvm_builder().getInt16(node->value.u16);
    } else if (node->type->bit_width == 32) {
      return codegen_context.llvm_builder().getInt32(node->value.u32);
    } else if (node->type->bit_width == 64) {
      return codegen_context.llvm_builder().getInt64(node->value.u64);
    } else {
      FRG_ABORT("unsupported integer bit width: " << node->type->bit_width);
    }
  } else if (node->type->type_with_bit_width_kind ==
             TypeWithBitWidthKind::float_) {
    if (node->type->bit_width == 32) {
      return llvm::ConstantFP::get(codegen_context.llvm_builder().getFloatTy(),
                                   node->value.f32);
    } else if (node->type->bit_width == 64) {
      return llvm::ConstantFP::get(codegen_context.llvm_builder().getDoubleTy(),
                                   node->value.f64);
    } else {
      FRG_ABORT("unsupported float bit width: " << node->type->bit_width);
    }
  } else {
    FRG_ABORT("unsupported literal number type");
  }
}

llvm::Value* codegen_value_symbol(CodegenContext&,
                                  const std::shared_ptr<ValueSymbol>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  FRG_ASSERT(node->referenced_declaration != nullptr,
             "cannot codegen symbol that has not been resolved");

  if (auto casted =
          try_cast_node<DeclarationVariable>(node->referenced_declaration);
      casted) {
    FRG_ASSERT(casted->llvm_value != nullptr,
               "cannot codegen reference to declaration variable with null "
               "LLVM value");
    return casted->llvm_value;
  } else if (auto casted = try_cast_node<DeclarationFunction>(
                 node->referenced_declaration);
             casted) {
    FRG_TODO();
  } else {
    FRG_ABORT(
        "cannot codegen symbol that does not reference a variable or function");
  }
}

llvm::Value* codegen_value_unary(CodegenContext& codegen_context,
                                 const std::shared_ptr<ValueUnary>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(node->operand != nullptr,
             "cannot codegen unary operation with null operand");
  FRG_ASSERT(node->operand->resolved_type != nullptr,
             "cannot codegen unary operation with unresolved operand type");

  llvm::Value* llvm_operand = codegen_value_implicit_cast(
      codegen_context, node->operand, node->resolved_type);

  switch (node->operator_) {
    case UnaryOperator::bool_not:
      return codegen_context.llvm_builder().CreateXor(
          llvm_operand, codegen_context.llvm_builder().getInt1(true));
    case UnaryOperator::bit_not:
      return codegen_context.llvm_builder().CreateXor(
          llvm_operand,
          llvm::ConstantInt::get(llvm_operand->getType(), -1, true));
    case UnaryOperator::pos:
      return llvm_operand;
    case UnaryOperator::neg:
      if (llvm_operand->getType()->isFloatingPointTy()) {
        return codegen_context.llvm_builder().CreateFNeg(llvm_operand);
      } else {
        return codegen_context.llvm_builder().CreateNeg(llvm_operand);
      }
    case UnaryOperator::deref: {
      FRG_ASSERT(node->operand->resolved_type != nullptr,
                 "cannot codegen deref of value with unresolved type");

      std::shared_ptr<BaseType> element_type =
          try_get_pointer_element_type(node->operand->resolved_type);

      FRG_ASSERT(element_type != nullptr, "cannot deref non-pointer type");

      llvm::Type* llvm_type = codegen_type(codegen_context, element_type);

      return codegen_context.llvm_builder().CreateLoad(llvm_type, llvm_operand);
    }
    case UnaryOperator::getaddr:
      FRG_TODO();
  }
}

llvm::Value* codegen_value_binary(CodegenContext& codegen_context,
                                  const std::shared_ptr<ValueBinary>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(node->lhs != nullptr,
             "cannot codegen binary operation with null lhs");
  FRG_ASSERT(node->rhs != nullptr,
             "cannot codegen binary operation with null rhs");
  FRG_ASSERT(node->resolved_type != nullptr,
             "cannot codegen binary operation with unresolved type");

  llvm::Value* llvm_lhs = codegen_value_implicit_cast(
      codegen_context, node->lhs, node->resolved_type);
  llvm::Value* llvm_rhs = codegen_value_implicit_cast(
      codegen_context, node->rhs, node->resolved_type);

  switch (node->operator_) {
    case BinaryOperator::bool_and:
      return codegen_context.llvm_builder().CreateAnd(llvm_lhs, llvm_rhs);
    case BinaryOperator::bool_or:
      return codegen_context.llvm_builder().CreateOr(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_and:
      return codegen_context.llvm_builder().CreateAnd(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_and_assign:
      FRG_TODO();
    case BinaryOperator::bit_or:
      return codegen_context.llvm_builder().CreateOr(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_or_assign:
      FRG_TODO();
    case BinaryOperator::bit_xor:
      return codegen_context.llvm_builder().CreateXor(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_xor_assign:
      FRG_TODO();
    case BinaryOperator::bit_shl:
      return codegen_context.llvm_builder().CreateShl(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_shl_assign:
      FRG_TODO();
    case BinaryOperator::bit_shr:
      return codegen_context.llvm_builder().CreateLShr(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_shr_assign:
      FRG_TODO();
    case BinaryOperator::add:
      return codegen_context.llvm_builder().CreateAdd(llvm_lhs, llvm_rhs);
    case BinaryOperator::add_assign:
      FRG_TODO();
    case BinaryOperator::sub:
      return codegen_context.llvm_builder().CreateSub(llvm_lhs, llvm_rhs);
    case BinaryOperator::sub_assign:
      FRG_TODO();
    case BinaryOperator::mul:
      return codegen_context.llvm_builder().CreateMul(llvm_lhs, llvm_rhs);
    case BinaryOperator::mul_assign:
      FRG_TODO();
    case BinaryOperator::exp:
      FRG_TODO();
    case BinaryOperator::exp_assign:
      FRG_TODO();
    case BinaryOperator::div:
      FRG_TODO();
    case BinaryOperator::div_assign:
      FRG_TODO();
    case BinaryOperator::mod:
      return codegen_context.llvm_builder().CreateFRem(llvm_lhs, llvm_rhs);
    case BinaryOperator::mod_assign:
      FRG_TODO();
    case BinaryOperator::assign:
      FRG_TODO();
    case BinaryOperator::eq:
      FRG_TODO();
    case BinaryOperator::ne:
      FRG_TODO();
    case BinaryOperator::lt:
      FRG_TODO();
    case BinaryOperator::le:
      FRG_TODO();
    case BinaryOperator::gt:
      FRG_TODO();
    case BinaryOperator::ge:
      FRG_TODO();
    case BinaryOperator::member_access:
      FRG_TODO();
  }
}

llvm::Value* codegen_value_call(CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCall>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(node->callee != nullptr, "cannot codegen call with null callee");
  FRG_ASSERT(node->callee->resolved_type != nullptr,
             "cannot codegen call with unresolved callee type");

  auto callee_type_casted =
      try_cast_node<TypeFunction>(node->callee->resolved_type);

  FRG_ASSERT(callee_type_casted != nullptr,
             "cannot codegen call with callee that is not a function type");

  llvm::Value* llvm_callee = codegen_value(codegen_context, node->callee);

  auto* llvm_callee_function = llvm::dyn_cast<llvm::Function>(llvm_callee);

  FRG_ASSERT(llvm_callee_function != nullptr,
             "cannot codegen call with non-function callee");

  std::vector<llvm::Value*> llvm_args;

  FRG_ASSERT(callee_type_casted->arg_types.size() == node->args.size(),
             ""
             "cannot codegen call with different number of arguments than "
             "expected");

  for (size_t i = 0; i < callee_type_casted->arg_types.size(); i++) {
    const std::shared_ptr<BaseType>& arg_type =
        callee_type_casted->arg_types[i];
    const std::shared_ptr<BaseValue>& arg = node->args[i];

    FRG_ASSERT(arg != nullptr, "cannot codegen call with null argument");
    FRG_ASSERT(arg_type != nullptr,
               "cannot codegen call with null argument type");

    llvm_args.push_back(
        codegen_value_implicit_cast(codegen_context, arg, arg_type));
  }

  return codegen_context.llvm_builder().CreateCall(llvm_callee_function,
                                                   llvm_args);
}

llvm::Value* codegen_value_cast(CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCast>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(node->value != nullptr,
             "cannot codegen explicit cast with null value");
  FRG_ASSERT(node->type != nullptr,
             "cannot codegen explicit cast with null type");

  return codegen_value_implicit_cast(codegen_context, node->value, node->type);
}

llvm::Value* codegen_value(CodegenContext& codegen_context,
                           const std::shared_ptr<BaseValue>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<ValueLiteralBool>(node); casted) {
    return codegen_value_literal_bool(codegen_context, casted);
  } else if (auto casted = try_cast_node<ValueLiteralNumber>(node); casted) {
    return codegen_value_literal_number(codegen_context, casted);
  } else if (auto casted = try_cast_node<ValueSymbol>(node); casted) {
    return codegen_value_symbol(codegen_context, casted);
  } else if (auto casted = try_cast_node<ValueUnary>(node); casted) {
    return codegen_value_unary(codegen_context, casted);
  } else if (auto casted = try_cast_node<ValueBinary>(node); casted) {
    return codegen_value_binary(codegen_context, casted);
  } else if (auto casted = try_cast_node<ValueCall>(node); casted) {
    return codegen_value_call(codegen_context, casted);
  } else if (auto casted = try_cast_node<ValueCast>(node); casted) {
    return codegen_value_cast(codegen_context, casted);
  } else {
    FRG_ABORT("unknown value kind");
  }
}

llvm::Value* codegen_value_implicit_cast(
    CodegenContext& codegen_context, const std::shared_ptr<BaseValue>& value,
    const std::shared_ptr<BaseType>& to) {
  FRG_ASSERT(value != nullptr, "cannot codegen implicit cast with null value");
  FRG_ASSERT(to != nullptr, "cannot codegen implicit cast with null to type");
  FRG_ASSERT(value->resolved_type != nullptr,
             "cannot codegen implicit cast "
             "with unresolved value type");

  // Generate LLVM value
  llvm::Value* llvm_value = codegen_value(codegen_context, value);

  // Generate LLVM from and to types
  llvm::Type* llvm_type_from =
      codegen_type_for_casting(codegen_context, value->resolved_type);
  llvm::Type* llvm_type_to = codegen_type_for_casting(codegen_context, to);

  // Check if the to type is signed
  bool is_from_signed =
      get_integer_type_signedness(value->resolved_type).value_or(false);

  // If the types are identical, no need to cast
  if (llvm_type_from == llvm_type_to) {
    return llvm_value;
  }

  // Cast int -> int
  else if (llvm_type_from->isIntegerTy() && llvm_type_to->isIntegerTy()) {
    // If we are extending the number of bits
    if (llvm_type_from->getIntegerBitWidth() <
        llvm_type_to->getIntegerBitWidth()) {
      // Extend the number of bits
      if (is_from_signed) {
        return codegen_context.llvm_builder().CreateSExt(llvm_value,
                                                         llvm_type_to);
      } else {
        return codegen_context.llvm_builder().CreateZExt(llvm_value,
                                                         llvm_type_to);
      }
    } else {
      // Otherwise, truncate the number of bits
      return codegen_context.llvm_builder().CreateTrunc(llvm_value,
                                                        llvm_type_to);
    }
  }

  // Cast int -> float
  else if (llvm_type_from->isIntegerTy() && llvm_type_to->isFloatingPointTy()) {
    if (is_from_signed) {
      return codegen_context.llvm_builder().CreateSIToFP(llvm_value,
                                                         llvm_type_to);
    } else {
      return codegen_context.llvm_builder().CreateUIToFP(llvm_value,
                                                         llvm_type_to);
    }
  }

  // Cast float -> int
  else if (llvm_type_from->isFloatingPointTy() && llvm_type_to->isIntegerTy()) {
    if (is_from_signed) {
      return codegen_context.llvm_builder().CreateFPToSI(llvm_value,
                                                         llvm_type_to);
    } else {
      return codegen_context.llvm_builder().CreateFPToUI(llvm_value,
                                                         llvm_type_to);
    }
  }

  // Cast float -> float
  else if (llvm_type_from->isFloatingPointTy() &&
           llvm_type_to->isFloatingPointTy()) {
    // If we are extending the number of bits
    if (llvm_type_from->getPrimitiveSizeInBits() <
        llvm_type_to->getPrimitiveSizeInBits()) {
      return codegen_context.llvm_builder().CreateFPExt(llvm_value,
                                                        llvm_type_to);
    } else {
      // Otherwise, truncate the number of bits
      return codegen_context.llvm_builder().CreateFPTrunc(llvm_value,
                                                          llvm_type_to);
    }
  }

  // Cast pointer -> pointer
  else if (llvm_type_from->isPointerTy() && llvm_type_to->isPointerTy()) {
    return codegen_context.llvm_builder().CreateBitCast(llvm_value,
                                                        llvm_type_to);
  }

  // Cast pointer -> int
  else if (llvm_type_from->isPointerTy() && llvm_type_to->isIntegerTy()) {
    return codegen_context.llvm_builder().CreatePtrToInt(llvm_value,
                                                         llvm_type_to);
  }

  // Cast int -> pointer
  else if (llvm_type_from->isIntegerTy() && llvm_type_to->isPointerTy()) {
    return codegen_context.llvm_builder().CreateIntToPtr(llvm_value,
                                                         llvm_type_to);
  }

  // Unsupported cast
  else {
    FRG_ABORT("unsupported cast from " << llvm_type_from->getTypeID() << " to "
                                       << llvm_type_to->getTypeID());
  }
}

CodegenStatementResult codegen_statement_basic(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementBasic>& node,
    CodegenStatementOptions options) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->statement_basic_kind) {
    case StatementBasicKind::continue_:
      FRG_ASSERT(options.llvm_basic_block_loop_body != nullptr,
                 "cannot codegen continue outside of loop");

      codegen_context.llvm_builder().CreateBr(
          options.llvm_basic_block_loop_body);

      return {.llvm_basic_block_end = options.llvm_basic_block_loop_body};
    case StatementBasicKind::break_:
      FRG_ASSERT(options.llvm_basic_block_after_loop != nullptr,
                 "cannot codegen continue outside of loop");

      codegen_context.llvm_builder().CreateBr(
          options.llvm_basic_block_after_loop);

      return {.llvm_basic_block_end = options.llvm_basic_block_after_loop};
    case StatementBasicKind::return_void:
      FRG_ASSERT(options.llvm_basic_block_start != nullptr,
                 "options.basic_block_start must be non-null");

      codegen_context.llvm_builder().CreateRetVoid();

      return {.llvm_basic_block_end = nullptr};
  }
}

CodegenStatementResult codegen_statement_value(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementValue>& node,
    CodegenStatementOptions options) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(options.llvm_basic_block_start != nullptr,
             "options.basic_block_start must be non-null");

  switch (node->statement_value_kind) {
    case StatementValueKind::execute:
      codegen_value(codegen_context, node->value);

      return {.llvm_basic_block_end = options.llvm_basic_block_start};
    case StatementValueKind::return_: {
      FRG_ASSERT(options.surrounding_function != nullptr,
                 "options.surrounding_function must be non-null");

      FRG_ASSERT(options.surrounding_function->resolved_type != nullptr,
                 ""
                 "surrounding function must have a resolved type");

      auto surrounding_function_type_casted = try_cast_node<TypeFunction>(
          options.surrounding_function->resolved_type);

      FRG_ASSERT(surrounding_function_type_casted != nullptr,
                 "surrounding function must be a function type");

      FRG_ASSERT(surrounding_function_type_casted->return_type != nullptr,
                 "surrounding function must have a resolved return type");

      codegen_context.llvm_builder().CreateRet(codegen_value_implicit_cast(
          codegen_context, node->value,
          surrounding_function_type_casted->return_type));

      return {.llvm_basic_block_end = nullptr};
    }
  }
}

CodegenStatementResult codegen_statement_block(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementBlock>& node,
    CodegenStatementOptions options) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");
  FRG_ASSERT(options.llvm_basic_block_start != nullptr,
             "options.basic_block_start must be non-null");

  llvm::BasicBlock* llvm_basic_block_current = options.llvm_basic_block_start;

  for (const std::shared_ptr<BaseStatement>& statement : node->statements) {
    FRG_ASSERT(statement != nullptr, "cannot codegen null statement in block");

    FRG_ASSERT(llvm_basic_block_current != nullptr,
               "block has reached termination but there are more statements "
               "left to codegen");

    CodegenStatementResult result = codegen_statement(
        codegen_context, statement,
        {
            .surrounding_function = options.surrounding_function,
            .llvm_surrounding_function = options.llvm_surrounding_function,
            .llvm_basic_block_start = llvm_basic_block_current,
            .llvm_basic_block_loop_body = options.llvm_basic_block_loop_body,
            .llvm_basic_block_after_loop = options.llvm_basic_block_after_loop,
        });

    llvm_basic_block_current = result.llvm_basic_block_end;
  }

  return {
      .llvm_basic_block_end = llvm_basic_block_current,
  };
}

CodegenStatementResult codegen_statement_if(
    CodegenContext& codegen_context, const std::shared_ptr<StatementIf>& node,
    CodegenStatementOptions options) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  llvm::BasicBlock* llvm_basic_block_then =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "then",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_else =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "else",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_merge = nullptr;

  codegen_context.llvm_builder().CreateCondBr(
      codegen_value(codegen_context, node->condition), llvm_basic_block_then,
      llvm_basic_block_else);

  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_then);

  CodegenStatementResult result_then = codegen_statement(
      codegen_context, node->then,
      {
          .surrounding_function = options.surrounding_function,
          .llvm_surrounding_function = options.llvm_surrounding_function,
          .llvm_basic_block_start = llvm_basic_block_then,
          .llvm_basic_block_loop_body = options.llvm_basic_block_loop_body,
          .llvm_basic_block_after_loop = options.llvm_basic_block_after_loop,
      });

  if (result_then.llvm_basic_block_end != nullptr &&
      result_then.llvm_basic_block_end->getTerminator() == nullptr) {
    if (llvm_basic_block_merge == nullptr) {
      llvm_basic_block_merge =
          llvm::BasicBlock::Create(codegen_context.llvm_context(), "merge",
                                   options.llvm_surrounding_function);
    }

    codegen_context.llvm_builder().CreateBr(llvm_basic_block_merge);
  }

  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_else);

  CodegenStatementResult result_else = codegen_statement(
      codegen_context, node->else_,
      {
          .surrounding_function = options.surrounding_function,
          .llvm_surrounding_function = options.llvm_surrounding_function,
          .llvm_basic_block_start = llvm_basic_block_else,
          .llvm_basic_block_loop_body = options.llvm_basic_block_loop_body,
          .llvm_basic_block_after_loop = options.llvm_basic_block_after_loop,
      });

  if (result_else.llvm_basic_block_end != nullptr &&
      result_else.llvm_basic_block_end->getTerminator() == nullptr) {
    if (llvm_basic_block_merge == nullptr) {
      llvm_basic_block_merge =
          llvm::BasicBlock::Create(codegen_context.llvm_context(), "merge",
                                   options.llvm_surrounding_function);
    }

    codegen_context.llvm_builder().CreateBr(llvm_basic_block_merge);
  }

  return {
      .llvm_basic_block_end = llvm_basic_block_merge,
  };
}

CodegenStatementResult codegen_statement_while(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementWhile>& node,
    CodegenStatementOptions options) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  llvm::BasicBlock* llvm_basic_block_body =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "body",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_after =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "after",
                               options.llvm_surrounding_function);

  codegen_context.llvm_builder().CreateCondBr(
      codegen_value(codegen_context, node->condition), llvm_basic_block_body,
      llvm_basic_block_after);

  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_body);

  CodegenStatementResult result_body = codegen_statement(
      codegen_context, node->body,
      {
          .surrounding_function = options.surrounding_function,
          .llvm_surrounding_function = options.llvm_surrounding_function,
          .llvm_basic_block_start = llvm_basic_block_body,
          .llvm_basic_block_loop_body = llvm_basic_block_body,
          .llvm_basic_block_after_loop = llvm_basic_block_after,
      });

  if (result_body.llvm_basic_block_end != nullptr &&
      result_body.llvm_basic_block_end->getTerminator() == nullptr) {
    codegen_context.llvm_builder().CreateCondBr(
        codegen_value(codegen_context, node->condition), llvm_basic_block_body,
        llvm_basic_block_after);
  }

  return {.llvm_basic_block_end = llvm_basic_block_after};
}

CodegenStatementResult codegen_statement(
    CodegenContext& codegen_context, const std::shared_ptr<BaseStatement>& node,
    CodegenStatementOptions options) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<StatementBasic>(node); casted) {
    return codegen_statement_basic(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementValue>(node); casted) {
    return codegen_statement_value(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementBlock>(node); casted) {
    return codegen_statement_block(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementIf>(node); casted) {
    return codegen_statement_if(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementWhile>(node); casted) {
    return codegen_statement_while(codegen_context, casted, options);
  } else {
    FRG_ABORT("unknown statement kind");
  }
}

void codegen_declaration_variable(
    CodegenContext&, const std::shared_ptr<DeclarationVariable>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  FRG_TODO();
}

void codegen_declaration_function(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationFunction>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  std::vector<llvm::Type*> llvm_arg_types;

  for (const std::shared_ptr<DeclarationVariable>& arg : node->args) {
    FRG_ASSERT(arg != nullptr,
               "cannot codegen null argument in function declaration");

    llvm_arg_types.push_back(codegen_type(codegen_context, arg->type));
  }

  FRG_ASSERT(node->return_type != nullptr,
             "cannot codegen null return type in function declaration");

  llvm::Type* llvm_return_type =
      codegen_type(codegen_context, node->return_type);

  llvm::FunctionType* llvm_function_type =
      llvm::FunctionType::get(llvm_return_type, llvm_arg_types, false);

  llvm::Function* llvm_function = llvm::Function::Create(
      llvm_function_type, llvm::Function::ExternalLinkage, node->name,
      codegen_context.llvm_module());

  auto argument_iter = llvm_function->arg_begin();

  for (const std::shared_ptr<DeclarationVariable>& arg : node->args) {
    FRG_ASSERT(arg != nullptr,
               "cannot codegen null argument in function declaration");

    llvm::Argument* argument = argument_iter++;
    argument->setName(arg->name);
    arg->llvm_value = argument;
  }

  llvm::BasicBlock* llvm_basic_block_entry = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "entry", llvm_function);
  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_entry);

  codegen_statement_block(codegen_context, node->body,
                          {.surrounding_function = node,
                           .llvm_surrounding_function = llvm_function,
                           .llvm_basic_block_start = llvm_basic_block_entry,
                           .llvm_basic_block_loop_body = nullptr,
                           .llvm_basic_block_after_loop = nullptr});

  // Verify the function
  if (llvm::verifyFunction(*llvm_function, &llvm::errs())) {
    llvm::errs() << "\n\n";
    FRG_ABORT(
        "LLVM function verification failed - this should never happen and is "
        "due to an internal compiler bug");
  }

  node->llvm_function = llvm_function;
}

void codegen_declaration_type_alias(
    CodegenContext&, const std::shared_ptr<DeclarationTypeAlias>&) {
  // type aliases have no code to be generated, so we can skip them
}

void codegen_declaration_structured_type(
    CodegenContext&, const std::shared_ptr<DeclarationStructuredType>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  FRG_TODO();
}

void codegen_declaration_namespace(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationNamespace>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  for (const std::shared_ptr<BaseDeclaration>& member : node->members) {
    FRG_ASSERT(member != nullptr, "cannot codegen null member in namespace");

    codegen_declaration(codegen_context, member);
  }
}

void codegen_declaration(CodegenContext& codegen_context,
                         const std::shared_ptr<BaseDeclaration>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<DeclarationVariable>(node); casted) {
    codegen_declaration_variable(codegen_context, casted);
  } else if (auto casted = try_cast_node<DeclarationFunction>(node); casted) {
    codegen_declaration_function(codegen_context, casted);
  } else if (auto casted = try_cast_node<DeclarationTypeAlias>(node); casted) {
    codegen_declaration_type_alias(codegen_context, casted);
  } else if (auto casted = try_cast_node<DeclarationStructuredType>(node);
             casted) {
    codegen_declaration_structured_type(codegen_context, casted);
  } else if (auto casted = try_cast_node<DeclarationNamespace>(node); casted) {
    codegen_declaration_namespace(codegen_context, casted);
  } else {
    FRG_ABORT("unknown declaration kind");
  }
}

void codegen_translation_unit(CodegenContext& codegen_context,
                              const std::shared_ptr<TranslationUnit>& node) {
  FRG_ASSERT(node != nullptr, "cannot codegen null node");

  for (const std::shared_ptr<BaseDeclaration>& declaration :
       node->declarations) {
    FRG_ASSERT(declaration != nullptr,
               "cannot codegen null declaration in namespace");

    codegen_declaration(codegen_context, declaration);
  }
}
}  // namespace forge
