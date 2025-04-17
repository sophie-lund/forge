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

#include <langtools/syntax_tree/formatting/debug_formatter.hpp>

namespace lt {
DebugFormatter::DebugFormatter(std::ostream& stream,
                               uint32_t indentation_width_spaces,
                               uint32_t indentation_initial_spaces)
    : _stream(std::ref(stream)),
      _indentation_level(0),
      _indentation_width_spaces(indentation_width_spaces),
      _indentation_initial_spaces(indentation_initial_spaces) {}

void DebugFormatter::node_label(const NodeKind& kind) {
  stream() << termcolor::bright_grey << "[" << termcolor::bright_blue << kind
           << termcolor::bright_grey << "]" << termcolor::reset;
  indent();
}

void DebugFormatter::null() {
  stream() << termcolor::red << "null" << termcolor::reset;
}

std::ostream& DebugFormatter::stream() { return _stream.get(); }

void DebugFormatter::indent() { _indentation_level++; }

void DebugFormatter::unindent() {
  if (_indentation_level > 0) {
    _indentation_level--;
  }
}

void DebugFormatter::format_indentation() {
  for (decltype(_indentation_initial_spaces) i = 0;
       i < _indentation_initial_spaces +
               _indentation_level * _indentation_width_spaces;
       i++) {
    _stream.get() << " ";
  }
}
}  // namespace lt
