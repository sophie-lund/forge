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

namespace forge {
template <typename TValue>
void emit_syntax_warning_number_literal_truncated(
    MessageContext& message_context, const SourceRange& range,
    const char* type_name, TValue before_truncation, TValue after_truncation) {
  message_context.emit(
      range, SEVERITY_ERROR, "WS001",
      std::format("literal value does not fit in type {} - was parsed as {} "
                  "but got truncated to {}",
                  type_name, before_truncation, after_truncation));
}
}  // namespace forge
