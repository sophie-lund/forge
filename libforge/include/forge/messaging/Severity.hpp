// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <functional>
#include <ostream>

namespace sycamore::messaging {
/**
 * @brief A severity level for a message.
 */
class Severity {
 public:
  /**
   * @param value The value of the severity level - higher numbers mean more
   *              severe while lowers mean less so. Two severities should not
   *              have the same value.
   * @param name The name of the severity level as it should be printed out to
   *             the console.
   * @param formatColor A function that formats the console output to be the
   *                    color for the severity level.
   */
  Severity(uint32_t value, const char* name,
           std::function<void(std::ostream&)> formatColor);

  Severity(const Severity&) = delete;
  Severity(Severity&&) = delete;
  Severity& operator=(const Severity&) = delete;
  Severity& operator=(Severity&&) = delete;

  /**
   * @brief Formats the color of the severity level to the @p stream.
   */
  void formatColor(std::ostream& stream) const;

  /**
   * @brief Formats the name of the severity level to the @p stream.
   */
  void formatName(std::ostream& stream) const;

  /**
   * @brief Gets the numeric value of the severity level.
   */
  uint32_t value() const;

 private:
  const uint32_t value_;
  const char* name_;
  const std::function<void(std::ostream&)> formatColor_;
};

/**
 * @brief A severity level to use for suggestions to the user.
 */
extern const Severity SEVERITY_SUGGESTION;

/**
 * @brief A severity level to use for messages that indicate a potential fix to
 *        the user.
 */
extern const Severity SEVERITY_FIX;

/**
 * @brief A severity level to use for warnings to the user.
 */
extern const Severity SEVERITY_WARNING;

/**
 * @brief A severity level to use for errors.
 */
extern const Severity SEVERITY_ERROR;

/**
 * @brief A severity level to use for fatal errors which halt compilation.
 */
extern const Severity SEVERITY_FATAL_ERROR;
}  // namespace sycamore::messaging
