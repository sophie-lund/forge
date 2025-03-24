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

#include <gtest/gtest.h>

#include <forge/core/execute_binary.hpp>

using namespace forge;

TEST(core_execute_binary, no_capture_success) {
  ExecuteBinaryInput input;
  input.binary = "echo";
  input.args = {"hello, world"};
  input.capture_stdout = false;
  input.capture_stderr = false;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_EQ(result->captured_stdout, "");
  ASSERT_EQ(result->captured_stderr, "");
}

TEST(core_execute_binary, no_capture_failure) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "echo 'hello, world' && exit 2"};
  input.capture_stdout = false;
  input.capture_stderr = false;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 2);
  ASSERT_FALSE(result->ok());
  ASSERT_EQ(result->captured_stdout, "");
  ASSERT_EQ(result->captured_stderr, "");
}

TEST(core_execute_binary, capture_stdout_not_stderr_success) {
  ExecuteBinaryInput input;
  input.binary = "echo";
  input.args = {"hello, world"};
  input.capture_stdout = true;
  input.capture_stderr = false;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_EQ(result->captured_stdout, "hello, world\n");
  ASSERT_EQ(result->captured_stderr, "");
}

TEST(core_execute_binary, capture_stdout_not_stderr_failure) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "echo 'hello, world' && exit 2"};
  input.capture_stdout = true;
  input.capture_stderr = false;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 2);
  ASSERT_FALSE(result->ok());
  ASSERT_EQ(result->captured_stdout, "hello, world\n");
  ASSERT_EQ(result->captured_stderr, "");
}

TEST(core_execute_binary, capture_stderr_not_stdout_success) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "echo 'hello, world' >&2"};
  input.capture_stdout = false;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_EQ(result->captured_stdout, "");
  ASSERT_EQ(result->captured_stderr, "hello, world\n");
}

TEST(core_execute_binary, capture_stderr_not_stdout_failure) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "echo 'hello, world' >&2 && exit 2"};
  input.capture_stdout = false;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 2);
  ASSERT_FALSE(result->ok());
  ASSERT_EQ(result->captured_stdout, "");
  ASSERT_EQ(result->captured_stderr, "hello, world\n");
}

TEST(core_execute_binary, capture_both_success) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "echo 'hello, world' && echo 'asdf' >&2"};
  input.capture_stdout = true;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_EQ(result->captured_stdout, "hello, world\n");
  ASSERT_EQ(result->captured_stderr, "asdf\n");
}

TEST(core_execute_binary, capture_both_failure) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "echo 'hello, world' && echo 'asdf' >&2 && exit 2"};
  input.capture_stdout = true;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 2);
  ASSERT_FALSE(result->ok());
  ASSERT_EQ(result->captured_stdout, "hello, world\n");
  ASSERT_EQ(result->captured_stderr, "asdf\n");
}

TEST(core_execute_binary, long_output_stdout) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "yes 'hello, world' | head -n 10000"};
  input.capture_stdout = true;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_GT(result->captured_stdout.size(), 0);
  ASSERT_EQ(result->captured_stderr.size(), 0);
}

TEST(core_execute_binary, long_output_stderr) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c", "yes 'hello, world' | head -n 10000 >&2"};
  input.capture_stdout = true;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_EQ(result->captured_stdout.size(), 0);
  ASSERT_GT(result->captured_stderr.size(), 0);
}

TEST(core_execute_binary, long_output_both) {
  ExecuteBinaryInput input;
  input.binary = "bash";
  input.args = {"-c",
                "yes 'hello, world' | head -n 10000; yes 'hello, world' | head "
                "-n 10000 >&2; yes 'hello, world' | head -n 10000; yes 'hello, "
                "world' | head -n 10000 >&2"};
  input.capture_stdout = true;
  input.capture_stderr = true;

  auto result = execute_binary(input);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->termination_method, TerminationMethod::exited);
  ASSERT_EQ(result->exit_status, 0);
  ASSERT_TRUE(result->ok());
  ASSERT_GT(result->captured_stdout.size(), 0);
  ASSERT_GT(result->captured_stderr.size(), 0);
}
