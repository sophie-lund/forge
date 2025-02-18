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

#include <forge/messaging/message_context.hpp>

namespace forge {
MessageContext::MessageContext() : _codes_enabled(false) {}

const std::vector<Message>& MessageContext::messages() const {
  return _messages;
}

void MessageContext::enable_codes() { _codes_enabled = true; }

void MessageContext::require_severity_prefix(const Severity& severity,
                                             std::string&& prefix) {
  assert(_codes_enabled &&
         "message codes must be enabled in the message context for severity "
         "prefixes to be used");

  _severity_prefixes[severity.value()] = std::move(prefix);
}
}  // namespace forge
