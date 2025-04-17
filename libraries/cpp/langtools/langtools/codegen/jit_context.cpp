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

#include <langtools/codegen/jit_context.hpp>

namespace lt {
std::expected<JITContext, JITContextError> JITContext::create(
    std::unique_ptr<llvm::LLVMContext>&& llvm_context,
    std::unique_ptr<llvm::Module>&& llvm_module) {
  JITContext jit_context;

  auto llvm_lljit_create_result = llvm::orc::LLJITBuilder().create();

  if (llvm_lljit_create_result) {
    jit_context._llvm_lljit = std::move(*llvm_lljit_create_result);
  } else {
    return std::unexpected(
        JITContextError{JITContextErrorType::unable_to_create_llvm_lljit,
                        llvm::toString(llvm_lljit_create_result.takeError())});
  }

  llvm::orc::ThreadSafeModule tsm(std::move(llvm_module),
                                  std::move(llvm_context));

  if (auto error = jit_context._llvm_lljit->addIRModule(std::move(tsm));
      error) {
    return std::unexpected(
        JITContextError{JITContextErrorType::unable_to_create_llvm_lljit,
                        llvm::toString(std::move(error))});
  }

  return jit_context;
}
}  // namespace lt
