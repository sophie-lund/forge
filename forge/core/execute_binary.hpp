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

#include <expected>
#include <string>
#include <vector>

namespace forge {
/**
 * @brief What type of error is returned by @a execute_binary.
 */
enum class ExecuteBinaryError {
  unable_to_create_pipes,
  unable_to_fork,
  unable_to_set_nonblocking,
  unable_to_read,
};

/**
 * @brief An input struct of options to pass to @a execute_binary.
 */
struct ExecuteBinaryInput {
  /**
   * @brief The path to the actual binary file to execute.
   *
   * This is resolved on the system path (e.g. the `$PATH` environment
   * variable).
   */
  std::string binary;

  /**
   * @brief The arguments to pass to the binary.
   */
  std::vector<std::string> args;

  /**
   * @brief Whether to capture the standard output and standard error of the
   * binary.
   *
   * @note This is @c false by default.
   */
  bool capture_stdout;

  /**
   * @brief Whether to capture the standard error of the binary.
   *
   * @note This is @c false by default.
   */
  bool capture_stderr;
};

/**
 * @brief How the process was terminated.
 */
enum class TerminationMethod {
  /**
   * @brief It exited on its own.
   *
   * Successful processes will be marked as @c exited.
   */
  exited,

  /**
   * @brief It was killed by a signal.
   */
  signaled,

  /**
   * @brief Only the @c exited and @c signaled cases are handled, so any other
   * cases are represented by @c unknown.
   *
   * See @a waitpid for more details on other cases.
   */
  unknown,
};

/**
 * @brief An output struct containing the result of executing a binary.
 */
struct ExecuteBinaryOutput {
  /**
   * @brief The standard output of the binary.
   *
   * If @c capture_stdout is @c false in the input options, then this will be an
   * empty string.
   */
  std::string captured_stdout;

  /**
   * @brief The standard error of the binary.
   *
   * If @c capture_stderr is @c false in the input options, then this will be an
   * empty string.
   */
  std::string captured_stderr;

  /**
   * @brief How the process was terminated.
   *
   * Successful processes will be marked as @c exited.
   */
  TerminationMethod termination_method;

  /**
   * @brief The exit status of the process.
   *
   * This is only valid if @c termination_method is @c exited. Successful
   * processes will have an exit status of @c 0.
   */
  int exit_status;

  /**
   * @brief The signal ID that killed the process.
   *
   * This is only valid if @c termination_method is @c signaled.
   */
  int signal_id;

  /**
   * @brief Whether the process was successful.
   *
   * This is @c true if the process exited with a status of @c 0.
   */
  bool ok() const;
};

/**
 * @brief Execute a binary with the given input options.
 */
std::expected<ExecuteBinaryOutput, ExecuteBinaryError> execute_binary(
    const ExecuteBinaryInput& input);
}  // namespace forge
