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

#include <termcolor/termcolor.hpp>

namespace lt {
constexpr std::string_view extract_function_name(
    std::string_view pretty_function) {
  if (size_t last_colon = pretty_function.rfind("::");
      last_colon != std::string_view::npos) {
    pretty_function = pretty_function.substr(last_colon + 2);
  }

  if (size_t first_parenthesis = pretty_function.find("(");
      first_parenthesis != std::string_view::npos) {
    pretty_function = pretty_function.substr(0, first_parenthesis);
  }

  return pretty_function;
}

template <typename TName>
inline std::ostream& trace(TName name) {
  if (_trace_enabled) {
    for (uint32_t i = 0; i < _trace_indent_level * 2; i++) {
      trace_stream() << " ";
    }

    trace_stream() << termcolor::bright_grey << "[" << name << "] "
                   << termcolor::reset;
  }

  return trace_stream();
}

template <typename TName>
TraceScope<TName>::TraceScope(TName name) : _name(name) {
  trace_indent();
}

template <typename TName>
TraceScope<TName>::~TraceScope() {
  trace_dedent();
}

template <typename TName>
std::ostream& TraceScope<TName>::trace() {
  return ::lt::trace(_name);
}

template <typename TName>
std::ostream& TraceScope<TName>::stream() {
  return trace_stream();
}
}  // namespace lt
