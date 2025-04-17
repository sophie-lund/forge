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

#include <gtest/gtest.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/core/execute_binary.hpp>
#include <sstream>

using namespace lt;

TEST(external_llvm, return_i32_0) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int function()
  llvm::FunctionType *function_type = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), false);
  llvm::Function *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                             "function", codegen_context.llvm_module());

  // Create a basic block and set the insertion point
  llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "entry", function);
  codegen_context.llvm_builder().SetInsertPoint(basic_block);

  // Add the return instruction
  codegen_context.llvm_builder().CreateRet(
      codegen_context.llvm_builder().getInt32(0));

  // Verify the function
  if (llvm::verifyFunction(*function, &llvm::errs())) {
    llvm::errs() << "Function verification failed!\n";
    FAIL();
  }

  // JIT compile the function
  auto jit_context = std::move(codegen_context).jit_compile();
  if (!jit_context) {
    llvm::errs() << "Error: " << jit_context.error().message << "\n";
    FAIL();
  }

  // Get a function pointer to the compiled code
  auto function_pointer =
      jit_context->try_lookup_function<int (*)()>("function");

  ASSERT_NE(function_pointer, nullptr);

  // Execute the function
  ASSERT_EQ(function_pointer(), 0);
}

TEST(external_llvm, sum_two_i32_args) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int function(int a, int b)
  std::vector<llvm::Type *> parameter_types = {
      codegen_context.llvm_builder().getInt32Ty(),
      codegen_context.llvm_builder().getInt32Ty()};
  llvm::FunctionType *function_type = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), parameter_types, false);
  llvm::Function *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                             "function", codegen_context.llvm_module());

  // Get the arguments
  auto argument_iter = function->arg_begin();

  llvm::Argument *argument_a = argument_iter++;
  argument_a->setName("a");

  llvm::Argument *argument_b = argument_iter;
  argument_b->setName("b");

  // Create a basic block and set the insertion point
  llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "entry", function);
  codegen_context.llvm_builder().SetInsertPoint(basic_block);

  // Add the return instruction
  codegen_context.llvm_builder().CreateRet(
      codegen_context.llvm_builder().CreateAdd(argument_a, argument_b));

  // Verify the function
  if (llvm::verifyFunction(*function, &llvm::errs())) {
    llvm::errs() << "Function verification failed!\n";
    FAIL();
  }

  // JIT compile the function
  auto jit_context = std::move(codegen_context).jit_compile();
  if (!jit_context) {
    llvm::errs() << "Error: " << jit_context.error().message << "\n";
    FAIL();
  }

  // Get a function pointer to the compiled code
  auto function_pointer =
      jit_context->try_lookup_function<int (*)(int, int)>("function");

  ASSERT_NE(function_pointer, nullptr);

  // Execute the function
  ASSERT_EQ(function_pointer(1, 2), 3);
}

TEST(external_llvm, max_two_i32_args_using_phi) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int function(int a, int b)
  std::vector<llvm::Type *> parameter_types = {
      codegen_context.llvm_builder().getInt32Ty(),
      codegen_context.llvm_builder().getInt32Ty()};
  llvm::FunctionType *function_type = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), parameter_types, false);
  llvm::Function *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                             "function", codegen_context.llvm_module());

  // Get the arguments
  auto argument_iter = function->arg_begin();

  llvm::Argument *argument_a = argument_iter++;
  argument_a->setName("a");

  llvm::Argument *argument_b = argument_iter;
  argument_b->setName("b");

  // Create the basic blocks
  llvm::BasicBlock *basic_block_entry = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "entry", function);
  llvm::BasicBlock *basic_block_then = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "then", function);
  llvm::BasicBlock *basic_block_else = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "else", function);
  llvm::BasicBlock *basic_block_merge = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "merge", function);

  // Emit the entry block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_entry);
  codegen_context.llvm_builder().CreateCondBr(
      codegen_context.llvm_builder().CreateICmpSGE(argument_a, argument_b),
      basic_block_then, basic_block_else);

  // Emit the then block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_then);
  codegen_context.llvm_builder().CreateBr(basic_block_merge);

  // Emit the else block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_else);
  codegen_context.llvm_builder().CreateBr(basic_block_merge);

  // Add the return instruction
  codegen_context.llvm_builder().SetInsertPoint(basic_block_merge);
  llvm::PHINode *phi = codegen_context.llvm_builder().CreatePHI(
      codegen_context.llvm_builder().getInt32Ty(), 2);
  phi->addIncoming(argument_a, basic_block_then);
  phi->addIncoming(argument_b, basic_block_else);
  codegen_context.llvm_builder().CreateRet(phi);

  // Verify the function
  if (llvm::verifyFunction(*function, &llvm::errs())) {
    llvm::errs() << "Function verification failed!\n";
    FAIL();
  }

  // JIT compile the function
  auto jit_context = std::move(codegen_context).jit_compile();
  if (!jit_context) {
    llvm::errs() << "Error: " << jit_context.error().message << "\n";
    FAIL();
  }

  // Get a function pointer to the compiled code
  auto function_pointer =
      jit_context->try_lookup_function<int (*)(int, int)>("function");

  ASSERT_NE(function_pointer, nullptr);

  // Execute the function
  ASSERT_EQ(function_pointer(1, 2), 2);
  ASSERT_EQ(function_pointer(2, 1), 2);
}

TEST(external_llvm, max_two_i32_args_without_phi) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int function(int a, int b)
  std::vector<llvm::Type *> parameter_types = {
      codegen_context.llvm_builder().getInt32Ty(),
      codegen_context.llvm_builder().getInt32Ty()};
  llvm::FunctionType *function_type = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), parameter_types, false);
  llvm::Function *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                             "function", codegen_context.llvm_module());

  // Get the arguments
  auto argument_iter = function->arg_begin();

  llvm::Argument *argument_a = argument_iter++;
  argument_a->setName("a");

  llvm::Argument *argument_b = argument_iter;
  argument_b->setName("b");

  // Create the basic blocks
  llvm::BasicBlock *basic_block_entry = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "entry", function);
  llvm::BasicBlock *basic_block_then = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "then", function);
  llvm::BasicBlock *basic_block_else = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "else", function);

  // Emit the entry block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_entry);
  codegen_context.llvm_builder().CreateCondBr(
      codegen_context.llvm_builder().CreateICmpSGE(argument_a, argument_b),
      basic_block_then, basic_block_else);

  // Emit the then block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_then);
  codegen_context.llvm_builder().CreateRet(argument_a);

  // Emit the else block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_else);
  codegen_context.llvm_builder().CreateRet(argument_b);

  // Verify the function
  if (llvm::verifyFunction(*function, &llvm::errs())) {
    llvm::errs() << "Function verification failed!\n";
    FAIL();
  }

  // JIT compile the function
  auto jit_context = std::move(codegen_context).jit_compile();
  if (!jit_context) {
    llvm::errs() << "Error: " << jit_context.error().message << "\n";
    FAIL();
  }

  // Get a function pointer to the compiled code
  auto function_pointer =
      jit_context->try_lookup_function<int (*)(int, int)>("function");

  ASSERT_NE(function_pointer, nullptr);

  // Execute the function
  ASSERT_EQ(function_pointer(1, 2), 2);
  ASSERT_EQ(function_pointer(2, 1), 2);
}

TEST(external_llvm, increment_twice) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int function()
  llvm::FunctionType *function_type = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), false);
  llvm::Function *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                             "function", codegen_context.llvm_module());

  // Create the basic blocks
  llvm::BasicBlock *basic_block_entry = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "entry", function);

  // Emit the entry block
  codegen_context.llvm_builder().SetInsertPoint(basic_block_entry);
  llvm::Value *i = codegen_context.llvm_builder().CreateAlloca(
      codegen_context.llvm_builder().getInt32Ty(), nullptr, "i");

  codegen_context.llvm_builder().CreateStore(
      codegen_context.llvm_builder().getInt32(0), i);

  codegen_context.llvm_builder().CreateStore(
      codegen_context.llvm_builder().CreateAdd(
          codegen_context.llvm_builder().CreateLoad(
              codegen_context.llvm_builder().getInt32Ty(), i),
          codegen_context.llvm_builder().getInt32(1)),
      i);

  codegen_context.llvm_builder().CreateStore(
      codegen_context.llvm_builder().CreateAdd(
          codegen_context.llvm_builder().CreateLoad(
              codegen_context.llvm_builder().getInt32Ty(), i),
          codegen_context.llvm_builder().getInt32(1)),
      i);

  codegen_context.llvm_builder().CreateRet(
      codegen_context.llvm_builder().CreateLoad(
          codegen_context.llvm_builder().getInt32Ty(), i));

  // Verify the function
  if (llvm::verifyFunction(*function, &llvm::errs())) {
    llvm::errs() << "Function verification failed!\n";
    FAIL();
  }

  // JIT compile the function
  auto jit_context = std::move(codegen_context).jit_compile();
  if (!jit_context) {
    llvm::errs() << "Error: " << jit_context.error().message << "\n";
    FAIL();
  }

  // Get a function pointer to the compiled code
  auto function_pointer =
      jit_context->try_lookup_function<int (*)()>("function");

  ASSERT_NE(function_pointer, nullptr);

  // Execute the function
  ASSERT_EQ(function_pointer(), 2);
}
