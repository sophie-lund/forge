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
void MessageContext::emit(TArgs&&... args) {
  Message message(std::forward<TArgs>(args)...);

  if (_codes_enabled) {
    assert(message.code().has_value() &&
           "if message codes are enabled, they must be provided");
  } else {
    assert(!message.code().has_value() &&
           "message codes must be enabled in the message context for them to "
           "be used");
  }

  if (!_severity_prefixes.empty()) {
    assert(_codes_enabled &&
           "message codes must be enabled in the message context for severity "
           "prefixes to be used");

    auto iterator = _severity_prefixes.find(message.severity().value());

    assert(iterator != _severity_prefixes.end() &&
           "severity does not have prefix provided");

    assert(message.code().has_value() &&
           "if message codes are enabled, they must be provided");

    assert(message.code().value().starts_with(iterator->second) &&
           "message code must start with configured prefix");
  }

  _messages.push_back(std::move(message));
}
}  // namespace forge
