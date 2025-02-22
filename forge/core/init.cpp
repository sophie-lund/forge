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

#include <unicode/uclean.h>
#include <unicode/utypes.h>

#include <cassert>
#include <forge/core/init.hpp>

namespace forge {
namespace {
bool _is_initted = false;
}

bool is_initted() { return _is_initted; }

void init() {
  assert(!_is_initted && "has already been initialized once");

  UErrorCode status = U_ZERO_ERROR;
  u_init(&status);
  assert(!U_FAILURE(status) && "failed to initialize ICU");

  _is_initted = true;
}

void cleanup() {
  assert(_is_initted && "has not been initialized");

  u_cleanup();
}
}  // namespace forge
