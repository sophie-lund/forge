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

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

#include <forge/codegen/jit_context.hpp>
#include <fstream>
#include <memory>

namespace forge {
/**
 * @brief What type of error is contained by @a CodegenContextError.
 */
enum class CodegenContextErrorType {
  unable_to_find_target_triple,
  unable_to_create_target_machine,
  unable_to_open_object_file,
  target_does_not_support_object_files,
};

/**
 * @brief An error type to use for @a CodegenContext.
 */
struct CodegenContextError {
  /**
   * @brief The type of error.
   */
  CodegenContextErrorType type;

  /**
   * @brief A message returned from LLVM.
   */
  std::string message;
};

/**
 * @brief A context for code generation.
 *
 * It contains LLVM objects that need to be in scope for code generation.
 */
class CodegenContext {
 public:
  CodegenContext();
  ~CodegenContext();

  CodegenContext(const CodegenContext&) = delete;
  CodegenContext(CodegenContext&&) = default;
  CodegenContext& operator=(const CodegenContext&) = delete;
  CodegenContext& operator=(CodegenContext&&) = default;

  /**
   * @brief Get the LLVM context.
   */
  llvm::LLVMContext& llvm_context();

  /**
   * @brief Get the current LLVM module that is being generated.
   */
  llvm::Module& llvm_module();

  /**
   * @brief Get the current LLVM builder that is being used.
   *
   * There is only one builder per context, so it gets pointed to different
   * basic blocks.
   */
  llvm::IRBuilder<>& llvm_builder();

  /**
   * @brief Converts the @a CodegenContext into a @a JITContext.
   *
   * This function call does the actual JIT compilation.
   *
   * @return An error if the JIT context could not be created.
   *
   * @note This will destroy the @a CodegenContext.
   */
  std::expected<JITContext, JITContextError> jit_compile() &&;

  /**
   * @brief Writes the current module to an object file.
   *
   * This function call does the actual object file writing.
   *
   * @param path The path to write the object file to. If this is a relative
   * path it will be relative to the current working directory.
   *
   * @return An error if the object file could not be written.
   *
   * @note This will destroy the @a CodegenContext.
   */
  std::expected<void, CodegenContextError> write_object_file(
      const std::string& path) &&;

 private:
  static std::expected<const llvm::Target*, CodegenContextError> get_target(
      const std::string& target_triple);

  static std::expected<llvm::TargetMachine*, CodegenContextError>
  create_machine(const std::string& target_triple, const llvm::Target* target);

  std::unique_ptr<llvm::LLVMContext> _llvm_context;
  std::unique_ptr<llvm::Module> _llvm_module;
  std::unique_ptr<llvm::IRBuilder<>> _llvm_builder;
};
}  // namespace forge
