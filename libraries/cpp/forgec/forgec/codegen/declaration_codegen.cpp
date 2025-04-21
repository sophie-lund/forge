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

#include <forgec/codegen/declaration_codegen.hpp>
#include <forgec/codegen/statement_codegen.hpp>
#include <forgec/codegen/type_codegen.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>

namespace forge {
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
}  // namespace forge
