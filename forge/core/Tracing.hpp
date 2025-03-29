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

#include <forge/core/null_streambuf.hpp>
#include <iostream>

/**
 * The current name of the function.
 */
#define FORGE_FUNCTION_NAME ::forge::extract_function_name(__PRETTY_FUNCTION__)

namespace forge {
/**
 * @warning This is for internal use only.
 */
extern uint32_t _trace_indent_level;

/**
 * @warning This is for internal use only.
 */
extern bool _trace_enabled;

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
  std::ostream& trace();

  /**
   * @brief Shortcut to `trace_stream()`.
   */
  std::ostream& stream();

 private:
  TName _name;
};
}  // namespace forge

#include "tracing.tpp"
