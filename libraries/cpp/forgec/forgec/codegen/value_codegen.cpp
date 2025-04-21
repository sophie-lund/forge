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

#include <forgec/codegen/type_codegen.hpp>
#include <forgec/codegen/value_binary_codegen.hpp>
#include <forgec/codegen/value_codegen.hpp>
#include <forgec/logic/types/get_arithmetic_containing_type.hpp>
#include <forgec/logic/types/type_predicates.hpp>
#include <forgec/syntax_tree/declarations/declaration_function.hpp>
#include <forgec/syntax_tree/declarations/declaration_variable.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>

namespace forge {
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

llvm::Value* codegen_value_symbol(lt::CodegenContext& codegen_context,
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

    if (casted->llvm_value->getType()->isPointerTy()) {
      return codegen_context.llvm_builder().CreateLoad(
          codegen_type(codegen_context, casted->resolved_type),
          casted->llvm_value);
    } else {
      return casted->llvm_value;
    }
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
      return codegen_value_lvalue(codegen_context, node->operand);
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

llvm::Value* codegen_value_lvalue(lt::CodegenContext& codegen_context,
                                  const std::shared_ptr<BaseValue>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  // If the value is a symbol, then just return its referenced declaration's
  // codegen-ed LLVM value
  if (auto casted = try_cast_node<ValueSymbol>(node); casted) {
    LT_ASSERT(casted->referenced_declaration != nullptr,
              "cannot codegen symbol that has not been resolved");

    if (auto casted_declaration =
            try_cast_node<DeclarationVariable>(casted->referenced_declaration);
        casted_declaration) {
      LT_ASSERT(casted_declaration->llvm_value != nullptr,
                "cannot codegen reference to declaration variable with null "
                "LLVM value");
      return casted_declaration->llvm_value;
    } else {
      LT_ABORT(
          "cannot codegen L-value symbol that does not reference a variable");
    }
  }

  // If the value is a deref, then return the pointer value so it can be used
  // for storing
  else if (auto casted = try_cast_node<ValueUnary>(node);
           casted && casted->operator_ == UnaryOperator::deref) {
    return codegen_value(codegen_context, casted->operand);
  }

  // If the value is a member access, this isn't implemented yet
  else if (auto casted = try_cast_node<ValueBinary>(node);
           casted && casted->operator_ == BinaryOperator::member_access) {
    LT_TODO();
  }

  // Otherwise, the value is not an L-value
  else {
    LT_ABORT("node is not an L-value");
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

  // Check if the types are signed
  bool is_from_signed =
      get_integer_type_signedness(value->resolved_type).value_or(false);
  bool is_to_signed = get_integer_type_signedness(to).value_or(false);

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
    if (is_to_signed) {
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
}  // namespace forge
