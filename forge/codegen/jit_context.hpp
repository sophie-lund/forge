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

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <expected>
#include <memory>

namespace forge {
enum class JITContextErrorType {
  unable_to_create_llvm_lljit,
};

struct JITContextError {
  JITContextErrorType type;
  std::string message;
};

class JITContext {
 public:
  static std::expected<JITContext, JITContextError> create(
      std::unique_ptr<llvm::LLVMContext>&& llvm_context,
      std::unique_ptr<llvm::Module>&& llvm_module);

  template <typename TFunction, typename TName>
  TFunction try_lookup_function(const TName& name);

 private:
  std::unique_ptr<llvm::orc::LLJIT> _llvm_lljit;
};
}  // namespace forge

#include "jit_context.tpp"
