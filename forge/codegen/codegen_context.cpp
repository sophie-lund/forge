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

#include <llvm/MC/TargetRegistry.h>
#include <llvm/TargetParser/Host.h>

#include <forge/codegen/codegen_context.hpp>

namespace forge {
CodegenContext::CodegenContext() {
  _llvm_context = std::make_unique<llvm::LLVMContext>();
  _llvm_module = std::make_unique<llvm::Module>("main", *_llvm_context);
  _llvm_builder = std::make_unique<llvm::IRBuilder<>>(*_llvm_context);
}

CodegenContext::~CodegenContext() {
  _llvm_builder.reset();
  _llvm_module.reset();
  _llvm_context.reset();
}

llvm::LLVMContext& CodegenContext::llvm_context() { return *_llvm_context; }

llvm::Module& CodegenContext::llvm_module() { return *_llvm_module; }

llvm::IRBuilder<>& CodegenContext::llvm_builder() { return *_llvm_builder; }

std::expected<JITContext, JITContextError> CodegenContext::jit_compile() && {
  return JITContext::create(std::move(_llvm_context), std::move(_llvm_module));
}

std::expected<void, CodegenContextError> CodegenContext::write_object_file(
    const std::string& path) && {
  // Detect target architecture
  std::string target_triple = llvm::sys::getDefaultTargetTriple();

  std::expected<const llvm::Target*, CodegenContextError> target =
      get_target(target_triple);

  if (!target.has_value()) {
    return std::unexpected(target.error());
  }

  std::expected<llvm::TargetMachine*, CodegenContextError> target_machine =
      create_machine(target_triple, target.value());

  if (!target_machine.has_value()) {
    return std::unexpected(target_machine.error());
  }

  // Assign the target machine to the module
  _llvm_module->setDataLayout(target_machine.value()->createDataLayout());
  _llvm_module->setTargetTriple(target_triple);

  // Open the object file for writing
  std::error_code object_file_open_error_code;
  llvm::raw_fd_ostream object_file_ostream(path, object_file_open_error_code,
                                           llvm::sys::fs::OF_None);

  if (object_file_open_error_code) {
    return std::unexpected(
        CodegenContextError{CodegenContextErrorType::unable_to_open_object_file,
                            object_file_open_error_code.message()});
  }

  // Write the object file
  llvm::legacy::PassManager pass;
  if (target_machine.value()->addPassesToEmitFile(
          pass, object_file_ostream, nullptr,
          llvm::CodeGenFileType::ObjectFile)) {
    return std::unexpected(CodegenContextError{
        CodegenContextErrorType::target_does_not_support_object_files, ""});
  }

  pass.run(*_llvm_module);
  object_file_ostream.flush();

  return {};
}

std::expected<const llvm::Target*, CodegenContextError>
CodegenContext::get_target(const std::string& target_triple) {
  std::string error;

  const llvm::Target* target =
      llvm::TargetRegistry::lookupTarget(target_triple, error);

  if (!target) {
    return std::unexpected(CodegenContextError{
        CodegenContextErrorType::unable_to_find_target_triple, error});
  }

  return target;
}

std::expected<llvm::TargetMachine*, CodegenContextError>
CodegenContext::create_machine(const std::string& target_triple,
                               const llvm::Target* target) {
  llvm::TargetOptions target_options;

  llvm::TargetMachine* target_machine = target->createTargetMachine(
      target_triple, "generic", "", target_options, llvm::Reloc::PIC_);

  if (!target_machine) {
    return std::unexpected(CodegenContextError{
        CodegenContextErrorType::unable_to_create_target_machine, ""});
  }

  return target_machine;
}
}  // namespace forge
