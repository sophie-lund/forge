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

#include <forge/codegen/codegen_context.hpp>

namespace forge {
CodegenContext::CodegenContext() {
  _llvm_context = std::make_unique<llvm::LLVMContext>();
  _llvm_builder = std::make_unique<llvm::IRBuilder<>>(*_llvm_context);
  _llvm_module = std::make_unique<llvm::Module>("main", *_llvm_context);
}

llvm::LLVMContext& CodegenContext::llvm_context() { return *_llvm_context; }

llvm::IRBuilder<>& CodegenContext::llvm_builder() { return *_llvm_builder; }

llvm::Module& CodegenContext::llvm_module() { return *_llvm_module; }
}  // namespace forge
