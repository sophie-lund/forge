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

#include <forge/messaging/Severity.hpp>
#include <forge/parsing/sourcing/domain/SourceRange.hpp>

namespace forge {
/**
 * @brief A message that gets emitted during compilation.
 */
class Message {
 public:
  /**
   * @param sourceRange The source range from which the message was emitted.
   * @param severity The severity of the message.
   * @param code A unique alphanumeric code to identify the message.
   * @param text The actual text of the message.
   */
  Message(const std::optional<SourceRange>& sourceRange,
          const Severity& severity, std::string&& code, std::string&& text);

  /**
   * @brief Gets the source range from which the message was emitted.
   */
  const std::optional<SourceRange>& sourceRange() const;

  /**
   * @brief Gets the severity of the message.
   */
  const Severity& severity() const;

  /**
   * @brief Gets a unique alphanumeric code to identify the message.
   */
  const std::string& code() const;

  /**
   * @brief Gets the actual text of the message.
   */
  const std::string& text() const;

 private:
  std::optional<SourceRange> sourceRange_;
  std::reference_wrapper<const Severity> severity_;
  std::string code_;
  std::string text_;
};
}  // namespace forge
