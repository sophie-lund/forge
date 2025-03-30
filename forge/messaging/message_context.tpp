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
  if (message.source_range.has_value()) {
    if (message.source_range->start.line.has_value() &&
        message.source_range->start.line.value() > _max_line_number) {
      _max_line_number = message.source_range->start.line.value();
    }

    if (message.source_range->end.has_value() &&
        message.source_range->end.value().line.has_value() &&
        message.source_range->end.value().line.value() > _max_line_number) {
      _max_line_number = message.source_range->end.value().line.value();
    }
  }

  // Check for message codes
  if (_codes_enabled) {
    assert(message.code.has_value() &&
           "if message codes are enabled, they must be provided");
  } else {
    assert(!message.code.has_value() &&
           "message codes must be enabled in the message context for them to "
           "be used");
  }

  // Check for severity prefixes
  if (!_severity_prefixes.empty()) {
    assert(_codes_enabled &&
           "message codes must be enabled in the message context for severity "
           "prefixes to be used");

    auto iterator = _severity_prefixes.find(message.severity.get().value);

    assert(iterator != _severity_prefixes.end() &&
           "severity does not have prefix provided");

    assert(message.code.has_value() &&
           "if message codes are enabled, they must be provided");

    assert(message.code.value().starts_with(iterator->second) &&
           "message code must start with configured prefix");
  }

  // Store the message
  _messages.push_back(std::move(message));

  // Return reference
  return _messages.back();
}
}  // namespace forge
