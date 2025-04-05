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
#include <forge/core/assert.hpp>
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
  Message& emit(TArgs&&... args);

  /**
   * @brief Get the messages emitted so far.
   *
   * This will return them in the order in which they were emitted.
   */
  const std::vector<Message>& messages() const;

  /**
   * @brief Gets the messages emitted so far, sorted by severity and location in
   * the source file.
   */
  [[nodiscard]]
  std::vector<Message> messages_sorted() const;

  /**
   * Enable the use of message codes that can be used to identify uniquely
   * message types.
   */
  void enable_codes();

  /**
   * @brief Require a severity prefix to be used for a message.
   *
   * For example, you can require that all error messages are prefixed with
   * `"E"`.
   */
  void require_severity_prefix(const Severity& severity, std::string&& prefix);

  /**
   * @brief Get the number of errors emitted so far.
   *
   * This is calculated by counting the number of messages with a severity
   * value greater than or equal than that of @c SEVERITY_ERROR.
   */
  size_t error_count() const;

  /**
   * @brief Get the number of warnings emitted so far.
   *
   * This is calculated by counting the number of messages with a severity
   * value greater than or equal than that of @c SEVERITY_WARNING but less than
   * that of @c SEVERITY_ERROR.
   */
  size_t warning_count() const;

  /**
   * @brief Get the maximum line number that is referenced by any message
   * emitted.
   *
   * This is used to calculate padding for message reporting. It will default to
   * @c 0 if no messages emitted have a line number they reference.
   */
  uint32_t max_line_number() const;

 private:
  std::vector<Message> _messages;
  bool _codes_enabled;
  std::unordered_map<uint32_t, std::string> _severity_prefixes;
  size_t _error_count;
  size_t _warning_count;
  uint32_t _max_line_number;
};
}  // namespace forge

#include "message_context.tpp"
