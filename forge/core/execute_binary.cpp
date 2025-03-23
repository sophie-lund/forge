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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <forge/core/execute_binary.hpp>
#include <iostream>

namespace forge {
namespace {
std::vector<char *> _build_exec_args(const ExecuteBinaryInput &input) {
  std::vector<char *> results;

  results.push_back(const_cast<char *>(input.binary.c_str()));

  for (const std::string &arg : input.args) {
    results.push_back(const_cast<char *>(arg.c_str()));
  }

  results.push_back(nullptr);

  return results;
}

[[nodiscard]]
std::expected<void, ExecuteBinaryError> _set_nonblocking(int fileno) {
  int flags = fcntl(fileno, F_GETFL, 0);

  if (flags == -1) {
    return std::unexpected(ExecuteBinaryError::unable_to_set_nonblocking);
  }

  fcntl(fileno, F_SETFL, flags | O_NONBLOCK);

  return {};
}

[[nodiscard]]
std::expected<std::vector<std::string>, ExecuteBinaryError>
_read_strings_from_filenos(const std::vector<int> &filenos) {
  static std::array<char, 1024> buffer;

  std::vector<std::string> results(filenos.size());

  // While there are more bytes to read from the file
  while (true) {
    bool more_to_be_read = false;

    // Try to read from each file descriptor
    for (std::size_t i = 0; i < filenos.size(); ++i) {
      ssize_t bytes_read =
          read(filenos.at(i), buffer.data(), buffer.size() - 1);

      if (bytes_read == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        // No more to read for now, but there might be more later
        more_to_be_read = true;
        continue;
      } else if (bytes_read > 0) {
        // Null-terminate the buffer
        buffer.at(bytes_read) = '\0';

        // Append the buffer to the result
        results.at(i).append(buffer.data(), bytes_read);

        more_to_be_read = true;
      } else if (bytes_read == 0) {
        // No more to be read
        continue;
      } else {
        return std::unexpected(ExecuteBinaryError::unable_to_read);
      }
    }

    // If there is none left in either file, stop reading
    if (!more_to_be_read) {
      break;
    }
  }

  return results;
}

std::expected<std::tuple<std::string, std::string>, ExecuteBinaryError>
_read_strings_from_stdout_and_stderr(
    std::optional<std::array<int, 2>> fileno_stdout,
    std::optional<std::array<int, 2>> fileno_stderr) {
  std::vector<int> filenos;

  // Pack filenos vector
  if (fileno_stdout.has_value()) {
    // Close write end of the pipes to prevent blocking
    close(fileno_stdout.value().at(1));

    // Set the file read ends to be nonblocking
    if (auto result = _set_nonblocking(fileno_stdout.value().at(0)); !result) {
      return std::unexpected(result.error());
    }

    // Add the file descriptor to the list of file descriptors to read from
    filenos.push_back(fileno_stdout.value().at(0));
  }

  if (fileno_stderr.has_value()) {
    // Close write end of the pipes to prevent blocking
    close(fileno_stderr.value().at(1));

    // Set the file read ends to be nonblocking
    if (auto result = _set_nonblocking(fileno_stderr.value().at(0)); !result) {
      return std::unexpected(result.error());
    }

    // Add the file descriptor to the list of file descriptors to read from
    filenos.push_back(fileno_stderr.value().at(0));
  }

  // If neither is captured, don't do any reading
  if (filenos.empty()) {
    return {};
  }

  // Read captured output
  std::expected<std::vector<std::string>, ExecuteBinaryError> results =
      _read_strings_from_filenos(filenos);
  if (!results) {
    return std::unexpected(results.error());
  }

  std::string captured_stdout, captured_stderr;

  // Unpack results
  std::size_t result_index = 0;
  for (int fileno : filenos) {
    // Close read end of the pipes as they is no longer needed
    close(fileno);

    // Set the capture variable
    if (fileno_stdout.has_value() && fileno == fileno_stdout->at(0)) {
      captured_stdout = std::move(results->at(result_index++));
    } else if (fileno_stderr.has_value() && fileno == fileno_stderr->at(0)) {
      captured_stderr = std::move(results->at(result_index++));
    }
  }

  // Return results
  return std::make_tuple(std::move(captured_stdout),
                         std::move(captured_stderr));
}
}  // namespace

[[nodiscard]]
bool ExecuteBinaryOutput::ok() const {
  return termination_method == TerminationMethod::exited && exit_status == 0;
}

[[nodiscard]]
std::expected<ExecuteBinaryOutput, ExecuteBinaryError> execute_binary(
    const ExecuteBinaryInput &input) {
  // Prepare arguments for execvp
  std::vector<char *> exec_args = _build_exec_args(input);

  // Create IO redirect pipes
  std::array<int, 2> pipefd_stdout;
  if (input.capture_stdout) {
    if (pipe(pipefd_stdout.data()) == -1) {
      return std::unexpected(ExecuteBinaryError::unable_to_create_pipes);
    }
  }

  std::array<int, 2> pipefd_stderr;
  if (input.capture_stderr) {
    if (pipe(pipefd_stderr.data()) == -1) {
      return std::unexpected(ExecuteBinaryError::unable_to_create_pipes);
    }
  }

  // Fork process
  pid_t pid = fork();
  if (pid == -1) {
    return std::unexpected(ExecuteBinaryError::unable_to_fork);
  }

  // Child process
  if (pid == 0) {
    if (input.capture_stdout) {
      // Close read end of the pipe to prevent blocking
      close(pipefd_stdout[0]);

      // Redirect IO to the write end of the pipe
      dup2(pipefd_stdout[1], STDOUT_FILENO);

      // Close the write end of the pipe as it is no longer needed
      close(pipefd_stdout[1]);
    }

    if (input.capture_stderr) {
      // Close read end of the pipe to prevent blocking
      close(pipefd_stderr[0]);

      // Redirect IO to the write end of the pipe
      dup2(pipefd_stderr[1], STDERR_FILENO);

      // Close the write end of the pipe as it is no longer needed
      close(pipefd_stderr[1]);
    }

    // Execute the binary
    execvp(input.binary.data(), exec_args.data());

    // If execution reaches here there was an error
    std::cerr << "error: unable to execute '" << input.binary
              << "': " << std::strerror(errno) << std::endl;

    _exit(1);
  }

  // Parent process
  ExecuteBinaryOutput output;

  // Capture output
  auto read_result = _read_strings_from_stdout_and_stderr(
      input.capture_stdout ? std::optional(pipefd_stdout) : std::nullopt,
      input.capture_stderr ? std::optional(pipefd_stderr) : std::nullopt);

  if (!read_result) {
    return std::unexpected(read_result.error());
  }

  output.captured_stdout = std::move(std::get<0>(read_result.value()));
  output.captured_stderr = std::move(std::get<1>(read_result.value()));

  // Wait for child process to finish
  int status;
  waitpid(pid, &status, 0);

  // Unpack status
  if (WIFEXITED(status)) {
    output.termination_method = TerminationMethod::exited;
    output.exit_status = WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    output.termination_method = TerminationMethod::signaled;
    output.signal_id = WTERMSIG(status);
  } else {
    output.termination_method = TerminationMethod::unknown;
  }

  return output;
}
}  // namespace forge
