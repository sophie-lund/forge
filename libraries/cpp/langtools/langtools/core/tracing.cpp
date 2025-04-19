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

#include <langtools/core/tracing.hpp>

namespace lt {
uint32_t _trace_indent_level = 0;
bool trace_enabled = false;

void trace_indent() { _trace_indent_level++; }

void trace_dedent() {
  if (_trace_indent_level > 0) {
    _trace_indent_level--;
  }
}

std::ostream& trace_stream() {
  if (trace_enabled) {
    return std::cout;
  } else {
    return null_ostream;
  }
}
}  // namespace lt
