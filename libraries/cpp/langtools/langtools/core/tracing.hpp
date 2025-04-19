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

#include <iostream>
#include <langtools/core/null_streambuf.hpp>

/**
 * The current name of the function.
 */
#define LT_FUNCTION_NAME ::lt::extract_function_name(__PRETTY_FUNCTION__)

namespace lt {
/**
 * @warning This is for internal use only.
 */
extern uint32_t _trace_indent_level;

/**
 * @brief Enables or disables tracing.
 *
 * This is @c false by default.
 */
extern bool trace_enabled;

/**
 * @brief Extract the function name from the pretty function string.
 *
 * Usually accessed by @c FORGE_FUNCTION_NAME.
 */
constexpr std::string_view extract_function_name(
    std::string_view pretty_function);

/**
 * @brief Indent the following trace output.
 *
 * @warning This is not thread-safe.
 */
void trace_indent();

/**
 * @brief Dedent the following trace output.
 *
 * @warning This is not thread-safe.
 */
void trace_dedent();

/**
 * @brief Get the stream to write trace messages to.
 */
[[nodiscard]]
std::ostream& trace_stream();

/**
 * @brief Print a trace message.
 *
 * @param name The name of the trace message.
 * @returns A stream that can be written to with the trace message.
 *
 * @warning This is not thread-safe.
 */
template <typename TName>
[[nodiscard]]
std::ostream& trace(TName name);

/**
 * @brief A trace scope that automatically handles indentation and dedentation.
 *
 * It indents when constructed and dedents when destructed.
 */
template <typename TName>
class TraceScope {
 public:
  /**
   * @brief Construct a trace scope.
   *
   * @param name The name to use for all traces with this scope.
   */
  TraceScope(TName name);

  ~TraceScope();

  /**
   * @brief Prints a trace message
   *
   * It is equivalent to calling `trace(name) << message` with the @c name
   * parameter passed into the constructor.
   */
  [[nodiscard]]
  std::ostream& trace();

  /**
   * @brief Shortcut to `trace_stream()`.
   */
  [[nodiscard]]
  std::ostream& stream();

 private:
  TName _name;
};
}  // namespace lt

#include "tracing.tpp"
