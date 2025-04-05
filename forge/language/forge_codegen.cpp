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

#include <forge/language/forge_codegen.hpp>

namespace forge {
llvm::Type* codegen_type_basic(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node) {
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

llvm::Type* codegen_type_symbol(CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node) {
  return codegen_type(codegen_context,
                      node->referenced_declaration->resolved_type);
}

llvm::Type* codegen_type_unary(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node) {
  switch (node->type_unary_kind) {
    case TypeUnaryKind::pointer:
      return codegen_context.llvm_builder().getPtrTy();
  }
}

// llvm::Type* codegen_type_bool(MessageContext&, CodegenContext&
// codegen_context,
//                               const std::shared_ptr<ExampleTypeBool>&) {
//   return codegen_context.llvm_builder().getInt1Ty();
// }

// llvm::Type* codegen_type_int(MessageContext&, CodegenContext&
// codegen_context,
//                              const std::shared_ptr<ExampleTypeInt>&) {
//   return codegen_context.llvm_builder().getInt32Ty();
// }

// llvm::FunctionType* codegen_type_function(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleTypeFunction>& node) {
//   std::vector<llvm::Type*> llvm_arg_types;

//   for (const std::shared_ptr<ExampleType>& arg_type : node->arg_types) {
//     llvm_arg_types.push_back(
//         codegen_type(message_context, codegen_context, arg_type));
//   }

//   llvm::Type* llvm_return_type =
//       codegen_type(message_context, codegen_context, node->return_type);

//   return llvm::FunctionType::get(llvm_return_type, llvm_arg_types, false);
// }

// llvm::Type* codegen_type(MessageContext& message_context,
//                          CodegenContext& codegen_context,
//                          const std::shared_ptr<ExampleType>& node) {
//   if (node->kind == NODE_TYPE_BOOL) {
//     return codegen_type_bool(message_context, codegen_context,
//                              std::static_pointer_cast<ExampleTypeBool>(node));
//   } else if (node->kind == NODE_TYPE_INT) {
//     return codegen_type_int(message_context, codegen_context,
//                             std::static_pointer_cast<ExampleTypeInt>(node));
//   } else if (node->kind == NODE_TYPE_FUNCTION) {
//     return codegen_type_function(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleTypeFunction>(node));
//   } else {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "unknown type kind");
//     return nullptr;
//   }
// }

// llvm::Value* codegen_value(MessageContext& message_context,
//                            CodegenContext& codegen_context,
//                            const std::shared_ptr<ExampleValue>& node);

// llvm::Value* codegen_value_bool(MessageContext&,
//                                 CodegenContext& codegen_context,
//                                 const std::shared_ptr<ExampleValueBool>&
//                                 node) {
//   return llvm::ConstantInt::get(codegen_context.llvm_builder().getInt1Ty(),
//                                 llvm::APInt(1, node->value ? 1 : 0, false));
// }

// llvm::Value* codegen_value_int(MessageContext&, CodegenContext&
// codegen_context,
//                                const std::shared_ptr<ExampleValueInt>& node)
//                                {
//   return llvm::ConstantInt::get(codegen_context.llvm_builder().getInt32Ty(),
//                                 llvm::APInt(32, node->value, true));
// }

// llvm::Value* codegen_value_symbol(
//     MessageContext& message_context, CodegenContext&,
//     const std::shared_ptr<ExampleValueSymbol>& node) {
//   if (node->referenced_declaration == nullptr) {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "unresolved symbol");
//     return nullptr;
//   }

//   if (node->referenced_declaration->kind == NODE_DECLARATION_VARIABLE) {
//     return std::static_pointer_cast<ExampleDeclarationVariable>(
//                node->referenced_declaration)
//         ->llvm_value;
//   } else if (node->referenced_declaration->kind == NODE_DECLARATION_FUNCTION)
//   {
//     return std::static_pointer_cast<ExampleDeclarationFunction>(
//                node->referenced_declaration)
//         ->llvm_function;
//   } else {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "unknown declaration kind");
//     return nullptr;
//   }
// }

// llvm::Value* codegen_value_add(MessageContext& message_context,
//                                CodegenContext& codegen_context,
//                                const std::shared_ptr<ExampleValueAdd>& node)
//                                {
//   llvm::Value* llvm_lhs =
//       codegen_value(message_context, codegen_context, node->lhs);
//   llvm::Value* llvm_rhs =
//       codegen_value(message_context, codegen_context, node->rhs);

//   return codegen_context.llvm_builder().CreateAdd(llvm_lhs, llvm_rhs);
// }

// llvm::Value* codegen_value_lt(MessageContext& message_context,
//                               CodegenContext& codegen_context,
//                               const std::shared_ptr<ExampleValueLT>& node) {
//   llvm::Value* llvm_lhs =
//       codegen_value(message_context, codegen_context, node->lhs);
//   llvm::Value* llvm_rhs =
//       codegen_value(message_context, codegen_context, node->rhs);

//   return codegen_context.llvm_builder().CreateICmpSLT(llvm_lhs, llvm_rhs);
// }

// llvm::Value* codegen_value_eq(MessageContext& message_context,
//                               CodegenContext& codegen_context,
//                               const std::shared_ptr<ExampleValueEQ>& node) {
//   llvm::Value* llvm_lhs =
//       codegen_value(message_context, codegen_context, node->lhs);
//   llvm::Value* llvm_rhs =
//       codegen_value(message_context, codegen_context, node->rhs);

//   return codegen_context.llvm_builder().CreateICmpEQ(llvm_lhs, llvm_rhs);
// }

// llvm::Value* codegen_value_neg(MessageContext& message_context,
//                                CodegenContext& codegen_context,
//                                const std::shared_ptr<ExampleValueNeg>& node)
//                                {
//   llvm::Value* llvm_operand =
//       codegen_value(message_context, codegen_context, node->operand);

//   return codegen_context.llvm_builder().CreateNeg(llvm_operand);
// }

// llvm::Value* codegen_value_call(MessageContext& message_context,
//                                 CodegenContext& codegen_context,
//                                 const std::shared_ptr<ExampleValueCall>&
//                                 node) {
//   llvm::Function* llvm_callee = static_cast<llvm::Function*>(
//       codegen_value(message_context, codegen_context, node->callee));

//   std::vector<llvm::Value*> llvm_args;

//   for (const std::shared_ptr<ExampleValue>& arg : node->args) {
//     llvm_args.push_back(codegen_value(message_context, codegen_context,
//     arg));
//   }

//   return codegen_context.llvm_builder().CreateCall(llvm_callee, llvm_args);
// }

// llvm::Value* codegen_value(MessageContext& message_context,
//                            CodegenContext& codegen_context,
//                            const std::shared_ptr<ExampleValue>& node) {
//   if (node->kind == NODE_VALUE_BOOL) {
//     return codegen_value_bool(message_context, codegen_context,
//                               std::static_pointer_cast<ExampleValueBool>(node));
//   } else if (node->kind == NODE_VALUE_INT) {
//     return codegen_value_int(message_context, codegen_context,
//                              std::static_pointer_cast<ExampleValueInt>(node));
//   } else if (node->kind == NODE_VALUE_SYMBOL) {
//     return codegen_value_symbol(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleValueSymbol>(node));
//   } else if (node->kind == NODE_VALUE_ADD) {
//     return codegen_value_add(message_context, codegen_context,
//                              std::static_pointer_cast<ExampleValueAdd>(node));
//   } else if (node->kind == NODE_VALUE_LT) {
//     return codegen_value_lt(message_context, codegen_context,
//                             std::static_pointer_cast<ExampleValueLT>(node));
//   } else if (node->kind == NODE_VALUE_EQ) {
//     return codegen_value_eq(message_context, codegen_context,
//                             std::static_pointer_cast<ExampleValueEQ>(node));
//   } else if (node->kind == NODE_VALUE_NEG) {
//     return codegen_value_neg(message_context, codegen_context,
//                              std::static_pointer_cast<ExampleValueNeg>(node));
//   } else if (node->kind == NODE_VALUE_CALL) {
//     return codegen_value_call(message_context, codegen_context,
//                               std::static_pointer_cast<ExampleValueCall>(node));
//   } else {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "unknown value kind");
//     return nullptr;
//   }
// }

// llvm::BasicBlock* codegen_statement(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatement>& node,
//     llvm::Function* llvm_function, llvm::BasicBlock*
//     llvm_basic_block_current, llvm::BasicBlock* llvm_basic_block_loop_body,
//     llvm::BasicBlock* llvm_basic_block_after_loop);

// llvm::BasicBlock* codegen_statement_value(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementValue>& node, llvm::Function*,
//     llvm::BasicBlock* llvm_basic_block_current) {
//   codegen_value(message_context, codegen_context, node->value);
//   return llvm_basic_block_current;
// }

// llvm::BasicBlock* codegen_statement_if(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementIf>& node,
//     llvm::Function* llvm_function, llvm::BasicBlock*,
//     llvm::BasicBlock* llvm_basic_block_loop_body,
//     llvm::BasicBlock* llvm_basic_block_after_loop) {
//   llvm::BasicBlock* llvm_basic_block_then = llvm::BasicBlock::Create(
//       codegen_context.llvm_context(), "then", llvm_function);
//   llvm::BasicBlock* llvm_basic_block_else = llvm::BasicBlock::Create(
//       codegen_context.llvm_context(), "else", llvm_function);
//   llvm::BasicBlock* llvm_basic_block_merge = nullptr;

//   codegen_context.llvm_builder().CreateCondBr(
//       codegen_value(message_context, codegen_context, node->condition),
//       llvm_basic_block_then, llvm_basic_block_else);

//   codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_then);
//   llvm::BasicBlock* llvm_basic_block_after_then = codegen_statement(
//       message_context, codegen_context, node->then, llvm_function,
//       llvm_basic_block_then, llvm_basic_block_loop_body,
//       llvm_basic_block_after_loop);
//   if (llvm_basic_block_after_then != nullptr &&
//       llvm_basic_block_after_then->getTerminator() == nullptr) {
//     if (llvm_basic_block_merge == nullptr) {
//       llvm_basic_block_merge = llvm::BasicBlock::Create(
//           codegen_context.llvm_context(), "merge", llvm_function);
//     }

//     codegen_context.llvm_builder().CreateBr(llvm_basic_block_merge);
//   }

//   codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_else);
//   llvm::BasicBlock* llvm_basic_block_after_else = codegen_statement(
//       message_context, codegen_context, node->else_, llvm_function,
//       llvm_basic_block_else, llvm_basic_block_loop_body,
//       llvm_basic_block_after_loop);
//   if (llvm_basic_block_after_else != nullptr &&
//       llvm_basic_block_after_else->getTerminator() == nullptr) {
//     if (llvm_basic_block_merge == nullptr) {
//       llvm_basic_block_merge = llvm::BasicBlock::Create(
//           codegen_context.llvm_context(), "merge", llvm_function);
//     }

//     codegen_context.llvm_builder().CreateBr(llvm_basic_block_merge);
//   }

//   return llvm_basic_block_merge;
// }

// llvm::BasicBlock* codegen_statement_while(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementWhile>& node,
//     llvm::Function* llvm_function, llvm::BasicBlock*) {
//   llvm::BasicBlock* llvm_basic_block_body = llvm::BasicBlock::Create(
//       codegen_context.llvm_context(), "body", llvm_function);
//   llvm::BasicBlock* llvm_basic_block_after = llvm::BasicBlock::Create(
//       codegen_context.llvm_context(), "after", llvm_function);

//   codegen_context.llvm_builder().CreateCondBr(
//       codegen_value(message_context, codegen_context, node->condition),
//       llvm_basic_block_body, llvm_basic_block_after);

//   codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_body);
//   llvm::BasicBlock* llvm_basic_block_after_body = codegen_statement(
//       message_context, codegen_context, node->body, llvm_function,
//       llvm_basic_block_body, llvm_basic_block_body, llvm_basic_block_after);
//   if (llvm_basic_block_after_body != nullptr &&
//       llvm_basic_block_after_body->getTerminator() == nullptr) {
//     codegen_context.llvm_builder().CreateCondBr(
//         codegen_value(message_context, codegen_context, node->condition),
//         llvm_basic_block_body, llvm_basic_block_after);
//   }

//   return llvm_basic_block_after;
// }

// llvm::BasicBlock* codegen_statement_continue(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementContinue>& node, llvm::Function*,
//     llvm::BasicBlock* llvm_basic_block_current,
//     llvm::BasicBlock* llvm_basic_block_loop_body, llvm::BasicBlock*) {
//   if (llvm_basic_block_loop_body == nullptr) {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "continue outside of loop");
//     return llvm_basic_block_current;
//   }

//   codegen_context.llvm_builder().CreateBr(llvm_basic_block_loop_body);

//   return llvm_basic_block_loop_body;
// }

// llvm::BasicBlock* codegen_statement_break(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementBreak>& node, llvm::Function*,
//     llvm::BasicBlock* llvm_basic_block_current, llvm::BasicBlock*,
//     llvm::BasicBlock* llvm_basic_block_after_loop) {
//   if (llvm_basic_block_after_loop == nullptr) {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "break outside of loop");
//     return llvm_basic_block_current;
//   }

//   codegen_context.llvm_builder().CreateBr(llvm_basic_block_after_loop);

//   return llvm_basic_block_after_loop;
// }

// llvm::BasicBlock* codegen_statement_return(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementReturn>& node, llvm::Function*,
//     llvm::BasicBlock* llvm_basic_block_current, llvm::BasicBlock*,
//     llvm::BasicBlock*) {
//   codegen_context.llvm_builder().CreateRet(
//       codegen_value(message_context, codegen_context, node->value));

//   return llvm_basic_block_current;
// }

// llvm::BasicBlock* codegen_statement_block(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatementBlock>& node,
//     llvm::Function* llvm_function, llvm::BasicBlock*
//     llvm_basic_block_current, llvm::BasicBlock* llvm_basic_block_loop_body,
//     llvm::BasicBlock* llvm_basic_block_after_loop) {
//   for (const std::shared_ptr<ExampleStatement>& statement : node->statements)
//   {
//     llvm_basic_block_current = codegen_statement(
//         message_context, codegen_context, statement, llvm_function,
//         llvm_basic_block_current, llvm_basic_block_loop_body,
//         llvm_basic_block_after_loop);
//   }

//   return llvm_basic_block_current;
// }

// llvm::BasicBlock* codegen_statement(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleStatement>& node,
//     llvm::Function* llvm_function, llvm::BasicBlock*
//     llvm_basic_block_current, llvm::BasicBlock* llvm_basic_block_loop_body,
//     llvm::BasicBlock* llvm_basic_block_after_loop) {
//   if (node->kind == NODE_STATEMENT_VALUE) {
//     return codegen_statement_value(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementValue>(node), llvm_function,
//         llvm_basic_block_current);
//   } else if (node->kind == NODE_STATEMENT_IF) {
//     return codegen_statement_if(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementIf>(node), llvm_function,
//         llvm_basic_block_current, llvm_basic_block_loop_body,
//         llvm_basic_block_after_loop);
//   } else if (node->kind == NODE_STATEMENT_WHILE) {
//     return codegen_statement_while(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementWhile>(node), llvm_function,
//         llvm_basic_block_current);
//   } else if (node->kind == NODE_STATEMENT_CONTINUE) {
//     return codegen_statement_continue(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementContinue>(node),
//         llvm_function, llvm_basic_block_current, llvm_basic_block_loop_body,
//         llvm_basic_block_after_loop);
//   } else if (node->kind == NODE_STATEMENT_BREAK) {
//     return codegen_statement_break(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementBreak>(node), llvm_function,
//         llvm_basic_block_current, llvm_basic_block_loop_body,
//         llvm_basic_block_after_loop);
//   } else if (node->kind == NODE_STATEMENT_RETURN) {
//     return codegen_statement_return(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementReturn>(node),
//         llvm_function, llvm_basic_block_current, llvm_basic_block_loop_body,
//         llvm_basic_block_after_loop);
//   } else if (node->kind == NODE_STATEMENT_BLOCK) {
//     return codegen_statement_block(
//         message_context, codegen_context,
//         std::static_pointer_cast<ExampleStatementBlock>(node), llvm_function,
//         llvm_basic_block_current, llvm_basic_block_loop_body,
//         llvm_basic_block_after_loop);
//   } else {
//     message_context.emit(node->source_range, SEVERITY_ERROR,
//                          "unknown statement kind");
//     return llvm_basic_block_current;
//   }
// }

// void codegen_declaration_variable(
//     MessageContext&, CodegenContext&,
//     const std::shared_ptr<ExampleDeclarationVariable>&) {
//   // global variables are not supported by code generation
// }

// void codegen_declaration_function(
//     MessageContext& message_context, CodegenContext& codegen_context,
//     const std::shared_ptr<ExampleDeclarationFunction>& node) {
//   std::vector<llvm::Type*> llvm_arg_types;

//   for (const std::shared_ptr<ExampleDeclarationVariable>& arg : node->args) {
//     llvm_arg_types.push_back(
//         codegen_type(message_context, codegen_context, arg->type));
//   }

//   llvm::Type* llvm_return_type =
//       codegen_type(message_context, codegen_context, node->return_type);

//   llvm::FunctionType* llvm_function_type =
//       llvm::FunctionType::get(llvm_return_type, llvm_arg_types, false);

//   llvm::Function* llvm_function = llvm::Function::Create(
//       llvm_function_type, llvm::Function::ExternalLinkage, node->name,
//       codegen_context.llvm_module());

//   auto argument_iter = llvm_function->arg_begin();

//   for (const std::shared_ptr<ExampleDeclarationVariable>& arg : node->args) {
//     llvm::Argument* argument = argument_iter++;
//     argument->setName(arg->name);
//     arg->llvm_value = argument;
//   }

//   llvm::BasicBlock* llvm_basic_block_entry = llvm::BasicBlock::Create(
//       codegen_context.llvm_context(), "entry", llvm_function);
//   codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_entry);

//   codegen_statement_block(message_context, codegen_context, node->body,
//                           llvm_function, llvm_basic_block_entry, nullptr,
//                           nullptr);

//   // Verify the function
//   if (llvm::verifyFunction(*llvm_function, &llvm::errs())) {
//     llvm::errs() << "Function verification failed!\n";
//     FRG_ABORT();
//   }

//   node->llvm_function = llvm_function;
// }

// CodegenContext codegen_translation_unit(
//     MessageContext& message_context,
//     const std::shared_ptr<ExampleTranslationUnit>& node) {
//   CodegenContext codegen_context;

//   for (const std::shared_ptr<ExampleDeclaration>& declaration :
//        node->declarations) {
//     if (declaration->kind == NODE_DECLARATION_VARIABLE) {
//       codegen_declaration_variable(
//           message_context, codegen_context,
//           std::static_pointer_cast<ExampleDeclarationVariable>(declaration));
//     } else if (declaration->kind == NODE_DECLARATION_FUNCTION) {
//       codegen_declaration_function(
//           message_context, codegen_context,
//           std::static_pointer_cast<ExampleDeclarationFunction>(declaration));
//     } else {
//       message_context.emit(declaration->source_range, SEVERITY_ERROR,
//                            "unknown declaration kind");
//     }
//   }

//   return codegen_context;
// }
}  // namespace forge
