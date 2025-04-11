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
#include <forge/codegen/codegen_context.hpp>
#include <forge/core/execute_binary.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace forge;

TEST(codegen_codegen_context, basic_jit) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int func()
  llvm::FunctionType *FuncType = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), false);
  llvm::Function *Func =
      llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "func",
                             codegen_context.llvm_module());

  // Create a basic block and set the insertion point
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "EntryBlock", Func);
  codegen_context.llvm_builder().SetInsertPoint(BB);

  // Add the return instruction
  codegen_context.llvm_builder().CreateRet(
      codegen_context.llvm_builder().getInt32(0));

  // Verify the function
  if (llvm::verifyFunction(*Func, &llvm::errs())) {
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
  auto func = jit_context->try_lookup_function<int (*)()>("func");

  if (!func) {
    llvm::errs()
        << "Error: JIT compilation failed, function pointer is null.\n";
    FAIL();
  }

  // Execute the function
  ASSERT_EQ(func(), 0);
}

TEST(codegen_codegen_context, basic_object_file) {
  // Create code generation context
  CodegenContext codegen_context = CodegenContext::create().value();

  // Define the function signature: int func()
  llvm::FunctionType *FuncType = llvm::FunctionType::get(
      codegen_context.llvm_builder().getInt32Ty(), false);
  llvm::Function *Func =
      llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "func",
                             codegen_context.llvm_module());

  // Create a basic block and set the insertion point
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(
      codegen_context.llvm_context(), "EntryBlock", Func);
  codegen_context.llvm_builder().SetInsertPoint(BB);

  // Add the return instruction
  codegen_context.llvm_builder().CreateRet(
      codegen_context.llvm_builder().getInt32(0));

  // Verify the function
  if (llvm::verifyFunction(*Func, &llvm::errs())) {
    llvm::errs() << "Function verification failed!\n";
    FAIL();
  }

  // Compile the module to an object file
  if (auto result =
          std::move(codegen_context)
              .write_object_file("codegen_context_basic_object_file.o");
      !result) {
    llvm::errs() << "Error: " << result.error().message << "\n";
    FAIL();
  }

  // Define some C code which calls the compiled code as a string
  const char *c_code = R"(#include <stdio.h>

    extern int func();  // Declared in the LLVM-generated object file

    int main() {
        printf("LLVM function returned: %d\n", func());
        return 0;
    })";

  // Open a file for writing
  std::ofstream c_code_file("codegen_context_basic_object_file_main.c");
  ASSERT_TRUE(c_code_file);

  // Write the C code to the file
  c_code_file << c_code;

  // Close the file
  c_code_file.close();

  // Compile and link the C code with the object file
  ExecuteBinaryInput compile_and_link_input;
  compile_and_link_input.binary = "gcc";
  compile_and_link_input.args = {"codegen_context_basic_object_file_main.c",
                                 "codegen_context_basic_object_file.o", "-o",
                                 "codegen_context_basic_object_file"};

  auto compile_and_link_output = execute_binary(compile_and_link_input);
  ASSERT_TRUE(compile_and_link_output.has_value());
  ASSERT_TRUE(compile_and_link_output->ok());

  // Execute the linked binary
  ExecuteBinaryInput execute_linked_binary_input;
  execute_linked_binary_input.binary = "./codegen_context_basic_object_file";
  execute_linked_binary_input.capture_stdout = true;
  execute_linked_binary_input.capture_stderr = true;

  auto execute_linked_binary_output =
      execute_binary(execute_linked_binary_input);
  ASSERT_TRUE(execute_linked_binary_output.has_value());
  ASSERT_TRUE(execute_linked_binary_output->ok());
  ASSERT_EQ(execute_linked_binary_output->captured_stdout,
            "LLVM function returned: 0\n");
  ASSERT_EQ(execute_linked_binary_output->captured_stderr, "");
}
