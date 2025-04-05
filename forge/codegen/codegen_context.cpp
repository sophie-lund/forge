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
#include <forge/core/assert.hpp>

namespace forge {
std::expected<CodegenContext, CodegenContextError> CodegenContext::create(
    MessageContext& message_context, std::optional<std::string> target_triple) {
  CodegenContext result(message_context);

  result._llvm_context = std::make_unique<llvm::LLVMContext>();
  result._llvm_module =
      std::make_unique<llvm::Module>("main", *result._llvm_context);
  result._llvm_builder =
      std::make_unique<llvm::IRBuilder<>>(*result._llvm_context);

  // Detect target architecture
  if (!target_triple.has_value()) {
    target_triple = llvm::sys::getDefaultTargetTriple();
  } else {
    FRG_ASSERT(!target_triple->empty(),
               "the target triple cannot be an empty string");
  }

  std::expected<const llvm::Target*, CodegenContextError> target =
      get_target(target_triple.value());

  if (!target.has_value()) {
    return std::unexpected(target.error());
  } else {
    FRG_ASSERT(target.value() != nullptr, "the target cannot be null");
  }

  std::expected<llvm::TargetMachine*, CodegenContextError> target_machine =
      create_machine(target_triple.value(), target.value());

  if (!target_machine.has_value()) {
    return std::unexpected(target_machine.error());
  } else {
    FRG_ASSERT(target_machine.value() != nullptr,
               "the target machine cannot be null");
  }

  result._llvm_target_machine = target_machine.value();

  // Assign the target machine to the module
  result._llvm_module->setDataLayout(
      target_machine.value()->createDataLayout());
  result._llvm_module->setTargetTriple(target_triple.value());

  return result;
}

CodegenContext::CodegenContext(MessageContext& message_context)
    : _llvm_target_machine(nullptr),
      _message_context(std::ref(message_context)) {}

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
  if (_llvm_target_machine->addPassesToEmitFile(
          pass, object_file_ostream, nullptr,
          llvm::CodeGenFileType::ObjectFile)) {
    return std::unexpected(CodegenContextError{
        CodegenContextErrorType::target_does_not_support_object_files, ""});
  }

  pass.run(*_llvm_module);
  object_file_ostream.flush();

  return {};
}

MessageContext& CodegenContext::message_context() const {
  return _message_context.get();
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
