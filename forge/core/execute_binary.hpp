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
enum class ExecuteBinaryError {
  unable_to_create_pipes,
  unable_to_fork,
  unable_to_set_nonblocking,
  unable_to_read,
};

struct ExecuteBinaryInput {
  std::string binary;
  std::vector<std::string> args;
  bool capture_stdout;
  bool capture_stderr;
};

enum class TerminationMethod {
  exited,
  signaled,
  unknown,
};

struct ExecuteBinaryOutput {
  std::string captured_stdout;
  std::string captured_stderr;
  TerminationMethod termination_method;
  int exit_status;
  int signal_id;

  bool ok() const;
};

std::expected<ExecuteBinaryOutput, ExecuteBinaryError> execute_binary(
    const ExecuteBinaryInput& input);
}  // namespace forge
