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

#include <llvm/IR/Instructions.h>

#include <string>
#include <unordered_map>

namespace forge {
class FunctionCodegenContext {
 public:
  FunctionCodegenContext() = default;

  FunctionCodegenContext(const FunctionCodegenContext&) = delete;
  FunctionCodegenContext(FunctionCodegenContext&&) = delete;
  FunctionCodegenContext& operator=(const FunctionCodegenContext&) = delete;
  FunctionCodegenContext& operator=(FunctionCodegenContext&&) = delete;

  //   void declare_argument()

 private:
  std::unordered_map<std::string, llvm::AllocaInst*> named_values;
};
}  // namespace forge
