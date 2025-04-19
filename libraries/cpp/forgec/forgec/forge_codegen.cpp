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

#include <forgec/forge_codegen.hpp>
#include <forgec/type_logic/get_arithmetic_containing_type.hpp>
#include <forgec/type_logic/type_predicates.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>

namespace forge {
llvm::Type* codegen_type_basic(lt::CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeBasic>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->type_basic_kind) {
    case TypeBasicKind::bool_:
      return codegen_context.llvm_builder().getInt1Ty();
    case TypeBasicKind::isize:
    case TypeBasicKind::usize:
      return codegen_context.llvm_builder().getIntPtrTy(
          codegen_context.llvm_module().getDataLayout());
    default:
      LT_ABORT("unsupported type for casting");
  }
}

llvm::Type* codegen_type_with_bit_width(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeWithBitWidth>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
        LT_ABORT("unsupported integer bit width: " << node->bit_width);
      }
    case TypeWithBitWidthKind::float_:
      if (node->bit_width == 32) {
        return codegen_context.llvm_builder().getFloatTy();
      } else if (node->bit_width == 64) {
        return codegen_context.llvm_builder().getDoubleTy();
      } else {
        LT_ABORT("unsupported float bit width: " << node->bit_width);
      }
  }
}

llvm::Type* codegen_type_symbol(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  LT_ASSERT(node->referenced_declaration != nullptr,
            "cannot codegen symbol that has not been resolved");

  LT_ASSERT(
      node->referenced_declaration->resolved_type != nullptr,
      "cannot codegen symbol that references declaration with unresolved type");

  return codegen_type(codegen_context,
                      node->referenced_declaration->resolved_type);
}

llvm::Type* codegen_type_unary(lt::CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->type_unary_kind) {
    case TypeUnaryKind::pointer:
      return codegen_context.llvm_builder().getPtrTy();
  }
}

llvm::FunctionType* codegen_type_function(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeFunction>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  std::vector<llvm::Type*> llvm_arg_types;

  for (const std::shared_ptr<BaseType>& arg_type : node->arg_types) {
    LT_ASSERT(arg_type != nullptr,
              "cannot codegen null argument type in function type");

    llvm_arg_types.push_back(codegen_type(codegen_context, arg_type));
  }

  LT_ASSERT(node->return_type != nullptr,
            "cannot codegen null return type in function type");

  llvm::Type* llvm_return_type =
      codegen_type(codegen_context, node->return_type);

  return llvm::FunctionType::get(llvm_return_type, llvm_arg_types, false);
}

llvm::StructType* codegen_type_structured(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeStructured>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  std::vector<llvm::Type*> llvm_member_types;

  for (const std::shared_ptr<BaseDeclaration>& member : node->members) {
    LT_ASSERT(member != nullptr,
              "cannot codegen null member type in structured type");

    llvm_member_types.push_back(
        codegen_type(codegen_context, member->resolved_type));
  }

  LT_ASSERT(!llvm_member_types.empty(), "cannot codegen empty structured type");

  return llvm::StructType::create(codegen_context.llvm_module().getContext(),
                                  llvm_member_types);
}

llvm::Type* codegen_type(lt::CodegenContext& codegen_context,
                         const std::shared_ptr<BaseType>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
    LT_ABORT("unsupported type kind");
  }
}

llvm::Type* codegen_type_for_casting(lt::CodegenContext& codegen_context,
                                     const std::shared_ptr<BaseType>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<TypeBasic>(node); casted) {
    return codegen_type_basic_for_casting(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(node); casted) {
    return codegen_type_with_bit_width(codegen_context, casted);
  } else if (auto casted = try_cast_node<TypeUnary>(node); casted) {
    return codegen_type_unary(codegen_context, casted);
  } else {
    LT_ABORT("unsupported type kind for casting");
  }
}

llvm::Value* codegen_value_literal_bool(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralBool>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  return codegen_context.llvm_builder().getInt1(node->value);
}

llvm::Value* codegen_value_literal_number(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralNumber>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(node->type != nullptr,
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
      LT_ABORT("unsupported integer bit width: " << node->type->bit_width);
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
      LT_ABORT("unsupported float bit width: " << node->type->bit_width);
    }
  } else {
    LT_ABORT("unsupported literal number type");
  }
}

llvm::Value* codegen_value_symbol(lt::CodegenContext&,
                                  const std::shared_ptr<ValueSymbol>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  LT_ASSERT(node->referenced_declaration != nullptr,
            "cannot codegen symbol that has not been resolved");

  if (auto casted =
          try_cast_node<DeclarationVariable>(node->referenced_declaration);
      casted) {
    LT_ASSERT(casted->llvm_value != nullptr,
              "cannot codegen reference to declaration variable with null "
              "LLVM value");
    return casted->llvm_value;
  } else if (auto casted = try_cast_node<DeclarationFunction>(
                 node->referenced_declaration);
             casted) {
    LT_TODO();
  } else {
    LT_ABORT(
        "cannot codegen symbol that does not reference a variable or function");
  }
}

llvm::Value* codegen_value_unary(lt::CodegenContext& codegen_context,
                                 const std::shared_ptr<ValueUnary>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(node->operand != nullptr,
            "cannot codegen unary operation with null operand");
  LT_ASSERT(node->operand->resolved_type != nullptr,
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
      LT_ASSERT(node->operand->resolved_type != nullptr,
                "cannot codegen deref of value with unresolved type");

      std::shared_ptr<BaseType> element_type =
          try_get_pointer_element_type(node->operand->resolved_type);

      LT_ASSERT(element_type != nullptr, "cannot deref non-pointer type");

      llvm::Type* llvm_type = codegen_type(codegen_context, element_type);

      return codegen_context.llvm_builder().CreateLoad(llvm_type, llvm_operand);
    }
    case UnaryOperator::getaddr:
      LT_TODO();
  }
}

llvm::Value* codegen_value_binary(lt::CodegenContext& codegen_context,
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

  std::shared_ptr<BaseType> comparison_type = node->resolved_type;

  // Comparisons cannot be implicitly casted to i1 before comparing, so we
  // calculate the arithmetic containing type on the fly
  if (is_binary_operator_comparison(node->operator_)) {
    comparison_type = get_arithmetic_containing_type(
        codegen_context, node->lhs->resolved_type, node->rhs->resolved_type);
  }

  llvm::Value* llvm_lhs =
      codegen_value_implicit_cast(codegen_context, node->lhs, comparison_type);
  llvm::Value* llvm_rhs =
      codegen_value_implicit_cast(codegen_context, node->rhs, comparison_type);
  bool is_float = is_type_float(comparison_type);
  bool is_signed = get_integer_type_signedness(comparison_type).value_or(false);

  switch (node->operator_) {
    case BinaryOperator::bool_and:
      return codegen_context.llvm_builder().CreateAnd(llvm_lhs, llvm_rhs);
    case BinaryOperator::bool_or:
      return codegen_context.llvm_builder().CreateOr(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_and:
      return codegen_context.llvm_builder().CreateAnd(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_and_assign:
      LT_TODO();
    case BinaryOperator::bit_or:
      return codegen_context.llvm_builder().CreateOr(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_or_assign:
      LT_TODO();
    case BinaryOperator::bit_xor:
      return codegen_context.llvm_builder().CreateXor(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_xor_assign:
      LT_TODO();
    case BinaryOperator::bit_shl:
      return codegen_context.llvm_builder().CreateShl(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_shl_assign:
      LT_TODO();
    case BinaryOperator::bit_shr:
      return codegen_context.llvm_builder().CreateLShr(llvm_lhs, llvm_rhs);
    case BinaryOperator::bit_shr_assign:
      LT_TODO();
    case BinaryOperator::add:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFAdd(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateAdd(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::add_assign:
      LT_TODO();
    case BinaryOperator::sub:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFSub(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateSub(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::sub_assign:
      LT_TODO();
    case BinaryOperator::mul:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFMul(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateMul(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::mul_assign:
      LT_TODO();
    case BinaryOperator::exp:
      LT_TODO();
    case BinaryOperator::exp_assign:
      LT_TODO();
    case BinaryOperator::div:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFDiv(llvm_lhs, llvm_rhs);
      } else if (is_signed) {
        return codegen_context.llvm_builder().CreateSDiv(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateUDiv(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::div_assign:
      LT_TODO();
    case BinaryOperator::mod:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFRem(llvm_lhs, llvm_rhs);
      } else if (is_signed) {
        return codegen_context.llvm_builder().CreateSRem(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateURem(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::mod_assign:
      LT_TODO();
    case BinaryOperator::assign:
      LT_TODO();
    case BinaryOperator::eq:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFCmpOEQ(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpEQ(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::ne:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFCmpONE(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpNE(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::lt:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFCmpOLT(llvm_lhs, llvm_rhs);
      } else if (is_signed) {
        return codegen_context.llvm_builder().CreateICmpSLT(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpULT(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::le:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFCmpOLE(llvm_lhs, llvm_rhs);
      } else if (is_signed) {
        return codegen_context.llvm_builder().CreateICmpSLE(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpULE(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::gt:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFCmpOGT(llvm_lhs, llvm_rhs);
      } else if (is_signed) {
        return codegen_context.llvm_builder().CreateICmpSGT(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpUGT(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::ge:
      if (is_float) {
        return codegen_context.llvm_builder().CreateFCmpOGE(llvm_lhs, llvm_rhs);
      } else if (is_signed) {
        return codegen_context.llvm_builder().CreateICmpSGE(llvm_lhs, llvm_rhs);
      } else {
        return codegen_context.llvm_builder().CreateICmpUGE(llvm_lhs, llvm_rhs);
      }
    case BinaryOperator::member_access:
      LT_TODO();
  }
}

llvm::Value* codegen_value_call(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCall>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(node->callee != nullptr, "cannot codegen call with null callee");
  LT_ASSERT(node->callee->resolved_type != nullptr,
            "cannot codegen call with unresolved callee type");

  auto callee_type_casted =
      try_cast_node<TypeFunction>(node->callee->resolved_type);

  LT_ASSERT(callee_type_casted != nullptr,
            "cannot codegen call with callee that is not a function type");

  llvm::Value* llvm_callee = codegen_value(codegen_context, node->callee);

  auto* llvm_callee_function = llvm::dyn_cast<llvm::Function>(llvm_callee);

  LT_ASSERT(llvm_callee_function != nullptr,
            "cannot codegen call with non-function callee");

  std::vector<llvm::Value*> llvm_args;

  LT_ASSERT(callee_type_casted->arg_types.size() == node->args.size(),
            ""
            "cannot codegen call with different number of arguments than "
            "expected");

  for (size_t i = 0; i < callee_type_casted->arg_types.size(); i++) {
    const std::shared_ptr<BaseType>& arg_type =
        callee_type_casted->arg_types[i];
    const std::shared_ptr<BaseValue>& arg = node->args[i];

    LT_ASSERT(arg != nullptr, "cannot codegen call with null argument");
    LT_ASSERT(arg_type != nullptr,
              "cannot codegen call with null argument type");

    llvm_args.push_back(
        codegen_value_implicit_cast(codegen_context, arg, arg_type));
  }

  return codegen_context.llvm_builder().CreateCall(llvm_callee_function,
                                                   llvm_args);
}

llvm::Value* codegen_value_cast(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCast>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(node->value != nullptr,
            "cannot codegen explicit cast with null value");
  LT_ASSERT(node->type != nullptr,
            "cannot codegen explicit cast with null type");

  return codegen_value_implicit_cast(codegen_context, node->value, node->type);
}

llvm::Value* codegen_value(lt::CodegenContext& codegen_context,
                           const std::shared_ptr<BaseValue>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
    LT_ABORT("unknown value kind");
  }
}

llvm::Value* codegen_value_implicit_cast(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<BaseValue>& value,
    const std::shared_ptr<BaseType>& to) {
  LT_ASSERT(value != nullptr, "cannot codegen implicit cast with null value");
  LT_ASSERT(to != nullptr, "cannot codegen implicit cast with null to type");
  LT_ASSERT(value->resolved_type != nullptr,
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
    LT_ABORT("unsupported cast from " << llvm_type_from->getTypeID() << " to "
                                      << llvm_type_to->getTypeID());
  }
}

CodegenStatementResult codegen_statement_basic(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementBasic>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->statement_basic_kind) {
    case StatementBasicKind::continue_:
      LT_ASSERT(options.llvm_basic_block_loop_body != nullptr,
                "cannot codegen continue outside of loop");

      codegen_context.llvm_builder().CreateBr(
          options.llvm_basic_block_loop_body);

      return {.llvm_basic_block_end = nullptr};
    case StatementBasicKind::break_:
      LT_ASSERT(options.llvm_basic_block_after_loop != nullptr,
                "cannot codegen continue outside of loop");

      codegen_context.llvm_builder().CreateBr(
          options.llvm_basic_block_after_loop);

      return {.llvm_basic_block_end = nullptr};
    case StatementBasicKind::return_void:
      LT_ASSERT(options.llvm_basic_block_start != nullptr,
                "options.basic_block_start must be non-null");

      codegen_context.llvm_builder().CreateRetVoid();

      return {.llvm_basic_block_end = nullptr};
  }
}

CodegenStatementResult codegen_statement_value(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementValue>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(options.llvm_basic_block_start != nullptr,
            "options.basic_block_start must be non-null");

  switch (node->statement_value_kind) {
    case StatementValueKind::execute:
      codegen_value(codegen_context, node->value);

      return {.llvm_basic_block_end = options.llvm_basic_block_start};
    case StatementValueKind::return_: {
      LT_ASSERT(options.surrounding_function != nullptr,
                "options.surrounding_function must be non-null");

      LT_ASSERT(options.surrounding_function->resolved_type != nullptr,
                ""
                "surrounding function must have a resolved type");

      auto surrounding_function_type_casted = try_cast_node<TypeFunction>(
          options.surrounding_function->resolved_type);

      LT_ASSERT(surrounding_function_type_casted != nullptr,
                "surrounding function must be a function type");

      LT_ASSERT(surrounding_function_type_casted->return_type != nullptr,
                "surrounding function must have a resolved return type");

      codegen_context.llvm_builder().CreateRet(codegen_value_implicit_cast(
          codegen_context, node->value,
          surrounding_function_type_casted->return_type));

      return {.llvm_basic_block_end = nullptr};
    }
  }
}

CodegenStatementResult codegen_statement_block(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementBlock>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(options.llvm_basic_block_start != nullptr,
            "options.basic_block_start must be non-null");

  llvm::BasicBlock* llvm_basic_block_current = options.llvm_basic_block_start;

  for (const std::shared_ptr<BaseStatement>& statement : node->statements) {
    LT_ASSERT(statement != nullptr, "cannot codegen null statement in block");

    LT_ASSERT(llvm_basic_block_current != nullptr,
              "previous statement generated a termination instruction in the "
              "current basic block but there are more statements left to "
              "codegen in the current syntax tree block");

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
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementIf>& node, CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  // Case 1: no else clause, then clause is unterminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then and after
  //   - Generate a conditional branch to the then block or after block in the
  //     current block
  //   - Generate the then block
  //   - Generate a jump to the after block at the end of the then block
  //   - Return the after block for continued codegen
  //
  // Case 2: no else clause, then clause is terminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //     return;
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then and after
  //   - Generate a conditional branch to the then block or after block in the
  //     current block
  //   - Generate the then block
  //   - Return the after block for continued codegen
  //
  // Case 3: else clause, then clause is unterminated, else clause is
  //         unterminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //   } else {
  //     // do other stuff
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then, else, and after
  //   - Generate a conditional branch to the then block or else block in the
  //     current block
  //   - Generate the then block
  //   - Generate a jump to the after block at the end of the then block
  //   - Generate the else block
  //   - Generate a jump to the after block at the end of the else block
  //   - Return the after block for continued codegen
  //
  // Case 4: else clause, then clause is unterminated, else clause is
  //         terminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //   } else {
  //     // do other stuff
  //     return;
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then, else, and after
  //   - Generate a conditional branch to the then block or else block in the
  //     current block
  //   - Generate the then block
  //   - Generate a jump to the after block at the end of the then block
  //   - Generate the else block
  //   - Generate a jump to the after block at the end of the else block
  //   - Return the after block for continued codegen

  // Create basic blocks
  llvm::BasicBlock* llvm_basic_block_then =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "then",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_else =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "else",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_after =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "after",
                               options.llvm_surrounding_function);

  // Generate the conditional branch
  if (node->else_ == nullptr) {
    codegen_context.llvm_builder().CreateCondBr(
        codegen_value(codegen_context, node->condition), llvm_basic_block_then,
        llvm_basic_block_after);
  } else {
    codegen_context.llvm_builder().CreateCondBr(
        codegen_value(codegen_context, node->condition), llvm_basic_block_then,
        llvm_basic_block_else);
  }

  // Generate the then block
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

  // Optionally generate a jump to the after block if the then block is not
  // terminated
  if (result_then.llvm_basic_block_end != nullptr &&
      result_then.llvm_basic_block_end->getTerminator() == nullptr) {
    codegen_context.llvm_builder().CreateBr(llvm_basic_block_after);
  }

  // Optionally generate the else block
  if (node->else_) {
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

    // Optionally generate a jump to the after block if the else block is not
    // terminated
    if (result_else.llvm_basic_block_end != nullptr &&
        result_else.llvm_basic_block_end->getTerminator() == nullptr) {
      codegen_context.llvm_builder().CreateBr(llvm_basic_block_after);
    }
  }

  // Set the insert point to the after block
  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_after);

  // Clean up empty blocks
  if (llvm_basic_block_else->empty() &&
      llvm::pred_empty(llvm_basic_block_else)) {
    llvm_basic_block_else->eraseFromParent();
  }

  if (llvm_basic_block_after->empty() &&
      llvm::pred_empty(llvm_basic_block_after)) {
    llvm_basic_block_after->eraseFromParent();
  }

  // If all branches were terminated, return no basic block
  if (llvm::pred_empty(llvm_basic_block_after)) {
    return {
        .llvm_basic_block_end = nullptr,
    };
  }

  // Otherwise, return the after block
  return {
      .llvm_basic_block_end = llvm_basic_block_after,
  };
}

CodegenStatementResult codegen_statement_while(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementWhile>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<BaseStatement>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
    LT_ABORT("unknown statement kind");
  }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void codegen_declaration_variable(
    lt::CodegenContext&, const std::shared_ptr<DeclarationVariable>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  LT_TODO();
}
#pragma clang diagnostic pop

void codegen_declaration_function(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationFunction>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  std::vector<llvm::Type*> llvm_arg_types;

  for (const std::shared_ptr<DeclarationVariable>& arg : node->args) {
    LT_ASSERT(arg != nullptr,
              "cannot codegen null argument in function declaration");

    llvm_arg_types.push_back(codegen_type(codegen_context, arg->type));
  }

  LT_ASSERT(node->return_type != nullptr,
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
    LT_ASSERT(arg != nullptr,
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
    llvm::errs() << "\n\nFunction IR:\n\n";
    llvm_function->print(llvm::errs());
    llvm::errs() << "\n\n";
    LT_ABORT(
        "LLVM function verification failed - this should never happen and is "
        "due to an internal compiler bug");
  }

  node->llvm_function = llvm_function;
}

void codegen_declaration_type_alias(
    lt::CodegenContext&, const std::shared_ptr<DeclarationTypeAlias>&) {
  // type aliases have no code to be generated, so we can skip them
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void codegen_declaration_structured_type(
    lt::CodegenContext&,
    const std::shared_ptr<DeclarationStructuredType>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  LT_TODO();
}
#pragma clang diagnostic pop

void codegen_declaration_namespace(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationNamespace>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  for (const std::shared_ptr<BaseDeclaration>& member : node->members) {
    LT_ASSERT(member != nullptr, "cannot codegen null member in namespace");

    codegen_declaration(codegen_context, member);
  }
}

void codegen_declaration(lt::CodegenContext& codegen_context,
                         const std::shared_ptr<BaseDeclaration>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

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
    LT_ABORT("unknown declaration kind");
  }
}

void codegen_translation_unit(lt::CodegenContext& codegen_context,
                              const std::shared_ptr<TranslationUnit>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  for (const std::shared_ptr<BaseDeclaration>& declaration :
       node->declarations) {
    LT_ASSERT(declaration != nullptr,
              "cannot codegen null declaration in namespace");

    codegen_declaration(codegen_context, declaration);
  }
}
}  // namespace forge
