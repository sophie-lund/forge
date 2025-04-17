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

#include <langtools/messaging/severity.hpp>
#include <langtools/parsing/domain/source_range.hpp>

namespace lt {
class BaseNode;

/**
 * @brief A message that gets emitted during compilation.
 */
// LCOV_EXCL_START
class Message {
  // LCOV_EXCL_STOP
 public:
  /**
   * @brief Full constructor.
   *
   * @param source_range The source range from which the message was emitted.
   * @param severity The severity of the message.
   * @param code A unique alphanumeric code to identify the message.
   * @param text The actual text of the message.
   */
  Message(SourceRange source_range, const Severity& severity, std::string code,
          std::string text);

  /**
   * @brief Emit a child message.
   *
   * @returns A reference to the original parent message so that you can chain
   * calls.
   */
  Message& child(SourceRange source_range, const Severity& severity,
                 std::string text);

  SourceRange source_range;
  std::reference_wrapper<const Severity> severity;
  std::optional<std::string> code;
  std::string text;
  std::vector<Message> children;

 private:
  /**
   * @brief Constructor without a specified code.
   *
   * @param source_range The source range from which the message was emitted.
   * @param severity The severity of the message.
   * @param text The actual text of the message.
   */
  Message(SourceRange source_range, const Severity& severity, std::string text);
};
}  // namespace lt
