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

#pragma once

#include <cassert>
#include <forge/messaging/message.hpp>
#include <unordered_map>

namespace forge {
/**
 * @brief A context to store messages that are emitted during compilation.
 *
 * An instance of this class is passed around to various parts of the compiler
 * to store messages that are emitted during compilation.
 */
class MessageContext {
 public:
  MessageContext();

  MessageContext(const MessageContext& other) = delete;
  MessageContext(MessageContext&& other) = delete;
  MessageContext& operator=(const MessageContext& other) = delete;
  MessageContext& operator=(MessageContext&& other) = delete;

  /**
   * @brief Emit a message.
   *
   * See @a Message's constructor for the parameters. You can also simply pass
   * in a constructed @a Message instance.
   */
  template <typename... TArgs>
  void emit(TArgs&&... args);

  /**
   * @brief Get the messages emitted so far.
   *
   * This will return them in the order in which they were emitted.
   */
  const std::vector<Message>& messages() const;

  void enable_codes();

  void require_severity_prefix(const Severity& severity, std::string&& prefix);

 private:
  std::vector<Message> _messages;
  bool _codes_enabled;
  std::unordered_map<uint32_t, std::string> _severity_prefixes;
};
}  // namespace forge

#include "message_context.tpp"
