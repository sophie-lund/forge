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

#include <forge/core/tracing.hpp>

namespace forge {
int _NullBuffer::overflow(int c) { return c; }

uint32_t _trace_indent_level = 0;

bool _trace_enabled = getenv("FORGE_TRACE") != nullptr &&
                      strcmp(getenv("FORGE_TRACE"), "true") == 0;

_NullBuffer _null_buffer;

std::ostream _null_ostream(&_null_buffer);
}  // namespace forge
