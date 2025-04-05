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

#include <algorithm>
#include <forge/core/assert.hpp>
#include <forge/messaging/message_context.hpp>

namespace forge {
MessageContext::MessageContext()
    : _codes_enabled(false),
      _error_count(0),
      _warning_count(0),
      _max_line_number(0) {}

const std::vector<Message>& MessageContext::messages() const {
  return _messages;
}

std::vector<Message> MessageContext::messages_sorted() const {
  // Copy messages
  std::vector<Message> messages = _messages;

  // Sort them
  std::sort(messages.begin(), messages.end(),
            [](const Message& a, const Message& b) {
              // Higher severity messages should be printed first
              if (a.severity.get().value > b.severity.get().value) {
                return true;
              }

              size_t offset_a = 0, offset_b = 0;

              if (a.source_range.has_value() &&
                  a.source_range->start.offset.has_value()) {
                offset_a = a.source_range->start.offset.value();
              }

              if (b.source_range.has_value() &&
                  b.source_range->start.offset.has_value()) {
                offset_b = b.source_range->start.offset.value();
              }

              // If the severity is the same, sort by the offset within the file
              if (offset_a < offset_b) {
                return true;
              }

              return false;
            });

  // Return them
  return messages;
}

void MessageContext::enable_codes() { _codes_enabled = true; }

void MessageContext::require_severity_prefix(const Severity& severity,
                                             std::string&& prefix) {
  FRG_ASSERT(
      _codes_enabled,
      "message codes must be enabled in the message context for severity "
      "prefixes to be used");

  _severity_prefixes[severity.value] = std::move(prefix);
}

size_t MessageContext::error_count() const { return _error_count; }

size_t MessageContext::warning_count() const { return _warning_count; }

uint32_t MessageContext::max_line_number() const { return _max_line_number; }
}  // namespace forge
