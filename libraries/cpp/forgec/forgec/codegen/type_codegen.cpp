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
#include <langtools/syntax_tree/operations/casting.hpp>

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
}  // namespace forge
