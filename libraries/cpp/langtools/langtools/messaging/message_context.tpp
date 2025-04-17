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

namespace lt {
template <typename... TArgs>
Message& MessageContext::emit(TArgs&&... args) {
  // Create message
  Message message(std::forward<TArgs>(args)...);

  // Update severity counts
  if (message.severity.get().value >= SEVERITY_ERROR.value) {
    _error_count++;
  } else if (message.severity.get().value >= SEVERITY_WARNING.value) {
    _warning_count++;
  }

  // Update max line number
  if (message.source_range) {
    if (message.source_range.start.line.has_value() &&
        message.source_range.start.line.value() > _max_line_number) {
      _max_line_number = message.source_range.start.line.value();
    }

    if (message.source_range.end.has_value() &&
        message.source_range.end.value().line.has_value() &&
        message.source_range.end.value().line.value() > _max_line_number) {
      _max_line_number = message.source_range.end.value().line.value();
    }
  }

  // Store the message
  _messages.push_back(std::move(message));

  // Return reference
  return _messages.back();
}
}  // namespace lt
