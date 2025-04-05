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

#include <llvm/Support/TargetSelect.h>
#include <unicode/uclean.h>
#include <unicode/utypes.h>

#include <cassert>
#include <forge/core/init.hpp>

namespace forge {
namespace {
bool _is_initted = false;
}

bool is_initted() { return _is_initted; }

std::expected<void, InitErrorType> init() {
  if (_is_initted) {
    return std::unexpected(InitErrorType::already_initted);
  }

  UErrorCode status = U_ZERO_ERROR;
  u_init(&status);
  if (U_FAILURE(status)) {
    return std::unexpected(InitErrorType::unable_to_init_icu);
  }

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  _is_initted = true;

  return {};
}

std::expected<void, InitErrorType> cleanup() {
  if (!_is_initted) {
    return std::unexpected(InitErrorType::has_not_been_initted);
  }

  u_cleanup();

  return {};
}
}  // namespace forge
