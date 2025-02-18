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

#include <forge/messaging/severity.hpp>
#include <forge/parsing/sourcing/domain/source_range.hpp>

namespace forge {
/**
 * @brief A message that gets emitted during compilation.
 */
class Message {
 public:
  /**
   * Full constructor.
   *
   * @param source_range The source range from which the message was emitted.
   * @param severity The severity of the message.
   * @param code A unique alphanumeric code to identify the message.
   * @param text The actual text of the message.
   */
  Message(const std::optional<SourceRange>& source_range,
          const Severity& severity, std::string&& code, std::string&& text);

  /**
   * Constructor without a specified code.
   *
   * @param source_range The source range from which the message was emitted.
   * @param severity The severity of the message.
   * @param text The actual text of the message.
   */
  Message(const std::optional<SourceRange>& source_range,
          const Severity& severity, std::string&& text);

  /**
   * @brief Gets the source range from which the message was emitted.
   */
  const std::optional<SourceRange>& source_range() const;

  /**
   * @brief Gets the severity of the message.
   */
  const Severity& severity() const;

  /**
   * @brief Gets a unique alphanumeric code to identify the message.
   */
  const std::optional<std::string>& code() const;

  /**
   * @brief Gets the actual text of the message.
   */
  const std::string& text() const;

 private:
  std::optional<SourceRange> _source_range;
  std::reference_wrapper<const Severity> _severity;
  std::optional<std::string> _code;
  std::string _text;
};
}  // namespace forge
