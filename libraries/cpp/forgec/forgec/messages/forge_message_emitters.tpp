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
// LCOV_EXCL_START

template <typename TValue>
lt::Message& emit_syntax_warning_number_literal_truncated(
    lt::MessageContext& message_context, const lt::SourceRange& source_range,
    const char* type_name, TValue before_truncation, TValue after_truncation) {
  return message_context
      .emit(source_range, lt::SEVERITY_WARNING, "WSY001",
            std::format("literal value does not fit in type {}", type_name))
      .child(lt::SourceRange(), lt::SEVERITY_NOTE,
             std::format("was parsed as {}", before_truncation))
      .child(lt::SourceRange(), lt::SEVERITY_NOTE,
             std::format("but got truncated to {}", after_truncation));
}

// LCOV_EXCL_STOP
}  // namespace forge
