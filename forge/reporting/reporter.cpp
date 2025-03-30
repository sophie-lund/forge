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

#include <algorithm>
#include <forge/core/math_utilities.hpp>
#include <forge/core/unicode.hpp>
#include <forge/reporting/get_sample_lines.hpp>
#include <forge/reporting/reporter.hpp>
#include <termcolor/termcolor.hpp>

namespace forge {
namespace {
void _print_message_source_range(
    std::ostream& stream, const std::optional<SourceRange>& source_range) {
  if (source_range.has_value()) {
    stream << termcolor::bright_blue << source_range->start << termcolor::grey
           << " - " << termcolor::reset;
  }
}

void _print_message_sample(std::ostream& stream,
                           uint32_t max_line_number_digits,
                           const Message& message) {
  // If there is no sample, return early
  if (!message.source_range.has_value() ||
      message.source_range->start.source == nullptr) {
    stream << std::endl;
    return;
  }

  // Print an initial newline
  stream << std::endl;

  // Find the start and end line numbers
  SourceLocation start = message.source_range->start;
  SourceLocation end = message.source_range->end.value_or(start);

  if (!start.line.has_value()) {
    stream << std::endl;
    return;
  }

  uint32_t start_line = start.line.value();
  uint32_t end_line = end.line.value_or(start_line);

  // Get the sample lines
  GetSampleLinesResult sample_lines_result = get_sample_lines(
      message.source_range->start.source->content, start_line, end_line);

  // For each line
  for (const SampleLine& line : sample_lines_result.lines) {
    // Print the line number
    uint32_t line_number_digits = count_digits_in_integer(line.line_number);

    assert(line_number_digits <= max_line_number_digits);

    for (uint32_t i = line_number_digits; i < max_line_number_digits; i++) {
      stream << " ";
    }

    stream << termcolor::grey << line.line_number << "  " << termcolor::reset;

    // Print the line content
    uint32_t first_relevant_char_index =
        line.line_number == start_line
            ? start.column.value_or(1) - 1 -
                  sample_lines_result.deindented_chars
            : 0;
    uint32_t last_relevant_char_index =
        line.line_number == end_line
            ? end.column.value_or(line.text.size()) - 1 -
                  sample_lines_result.deindented_chars
            : line.text.size() - 1;

    for (uint32_t i = 0; i < line.text.size(); i++) {
      if (i == first_relevant_char_index) {
        stream << termcolor::bold;
        message.severity.get().format_color(stream);
      }

      if (line.text[i] == '\t') {
        stream << "  ";
      } else {
        stream << line.text[i];
      }

      if (i == last_relevant_char_index) {
        stream << termcolor::reset;
      }
    }

    stream << termcolor::reset << std::endl;

    // Print a caret line
    message.severity.get().format_color(stream);

    for (uint32_t i = 0; i < max_line_number_digits + 2; i++) {
      stream << " ";
    }

    for (uint32_t i = 0; i < line.text.size(); i++) {
      if (i >= first_relevant_char_index && i <= last_relevant_char_index) {
        stream << "^";
        if (line.text[i] == '\t') {
          stream << "^";
        }
      } else {
        stream << " ";
        if (line.text[i] == '\t') {
          stream << " ";
        }
      }
    }

    stream << termcolor::reset << std::endl;
  }

  // Print an additional newline
  stream << std::endl;
}

void _print_message(std::ostream& stream, const MessageContext& message_context,
                    const Message& message) {
  // Print source range (if available)
  _print_message_source_range(stream, message.source_range);

  // Print severity
  message.severity.get().format_color(stream);
  stream << termcolor::bold;
  message.severity.get().format_name(stream);

  // Print message code
  if (message.code.has_value()) {
    stream << termcolor::reset << termcolor::grey << " "
           << message.code.value();
  }

  // Print message text
  stream << ": " << termcolor::reset << termcolor::bright_white
         << termcolor::bold << message.text << termcolor::reset << std::endl;

  // Print sample lines
  _print_message_sample(
      stream, count_digits_in_integer(message_context.max_line_number()),
      message);

  // Print any children
  for (const auto& child : message.children) {
    _print_message(stream, message_context, child);
  }
}

void _print_message_context_severity_counts(
    std::ostream& stream, const MessageContext& message_context) {
  if (message_context.error_count() > 0) {
    stream << termcolor::red << message_context.error_count() << " error"
           << (message_context.error_count() == 1 ? "" : "s")
           << termcolor::reset;
  }

  if (message_context.error_count() > 0 &&
      message_context.warning_count() > 0) {
    stream << ", ";
  }

  if (message_context.warning_count() > 0) {
    stream << termcolor::yellow << message_context.warning_count() << " warning"
           << (message_context.warning_count() == 1 ? "" : "s")
           << termcolor::reset;
  }

  stream << std::endl;
}
}  // namespace

void report_messages(std::ostream& stream,
                     const MessageContext& message_context) {
  // Sort messages
  std::vector<Message> messages_sorted = message_context.messages_sorted();

  // Print each message
  for (const Message& message : messages_sorted) {
    _print_message(stream, message_context, message);
  }

  // Print summary
  _print_message_context_severity_counts(stream, message_context);
}
}  // namespace forge
