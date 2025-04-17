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

#include <langtools/messaging/message_context.hpp>

using namespace lt;

TEST(messaging_message_context, emit_constructed) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(
      Message(SourceRange(SourceLocation(source), SourceLocation(source)),
              SEVERITY_ERROR, "code", "text"));

  ASSERT_EQ(message_context.messages().size(), 1);
}

TEST(messaging_message_context, emit_forwarded) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(
      SourceRange(SourceLocation(source), SourceLocation(source)),
      SEVERITY_ERROR, "code", "text");

  ASSERT_EQ(message_context.messages().size(), 1);
}

TEST(messaging_message_context, sorting_by_severity) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(
      SourceRange(SourceLocation(source), SourceLocation(source)),
      SEVERITY_WARNING, "code 1", "text 1");

  message_context.emit(
      SourceRange(SourceLocation(source), SourceLocation(source)),
      SEVERITY_ERROR, "code 2", "text 2");

  ASSERT_EQ(message_context.messages().size(), 2);
  ASSERT_EQ(message_context.messages()[0].text, "text 1");
  ASSERT_EQ(message_context.messages()[1].text, "text 2");

  std::vector<Message> sorted = message_context.messages_sorted();

  ASSERT_EQ(sorted.size(), 2);
  ASSERT_EQ(sorted[0].text, "text 2");
  ASSERT_EQ(sorted[1].text, "text 1");
}

TEST(messaging_message_context, sorting_by_offset) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 6)),
                       SEVERITY_ERROR, "code 1", "text 1");

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 5)),
                       SEVERITY_ERROR, "code 2", "text 2");

  ASSERT_EQ(message_context.messages().size(), 2);
  ASSERT_EQ(message_context.messages()[0].text, "text 1");
  ASSERT_EQ(message_context.messages()[1].text, "text 2");

  std::vector<Message> sorted = message_context.messages_sorted();

  ASSERT_EQ(sorted.size(), 2);
  ASSERT_EQ(sorted[0].text, "text 2");
  ASSERT_EQ(sorted[1].text, "text 1");
}

TEST(messaging_message_context, sorting_by_both_severity_and_offset) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 6)),
                       SEVERITY_ERROR, "code 1", "text 1");

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 6)),
                       SEVERITY_WARNING, "code 2", "text 2");

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 5)),
                       SEVERITY_ERROR, "code 3", "text 3");

  ASSERT_EQ(message_context.messages().size(), 3);
  ASSERT_EQ(message_context.messages()[0].text, "text 1");
  ASSERT_EQ(message_context.messages()[1].text, "text 2");
  ASSERT_EQ(message_context.messages()[2].text, "text 3");

  std::vector<Message> sorted = message_context.messages_sorted();

  ASSERT_EQ(sorted.size(), 3);
  ASSERT_EQ(sorted[0].text, "text 3");
  ASSERT_EQ(sorted[1].text, "text 1");
  ASSERT_EQ(sorted[2].text, "text 2");
}

TEST(messaging_message_context, counts) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 6)),
                       SEVERITY_ERROR, "code 1", "text 1");

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 6)),
                       SEVERITY_WARNING, "code 2", "text 2");

  message_context.emit(SourceRange(SourceLocation(source, 1, 1, 5)),
                       SEVERITY_ERROR, "code 3", "text 3");

  ASSERT_EQ(message_context.error_count(), 2);
  ASSERT_EQ(message_context.warning_count(), 1);
}

TEST(messaging_message_context, max_line_number_none) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(SourceRange(), SEVERITY_ERROR, "code 1", "text 1");

  message_context.emit(SourceRange(), SEVERITY_WARNING, "code 2", "text 2");

  ASSERT_EQ(message_context.max_line_number(), 0);
}

TEST(messaging_message_context, max_line_number_one) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(SourceRange(SourceLocation(source, 2)), SEVERITY_ERROR,
                       "code 1", "text 1");

  message_context.emit(SourceRange(), SEVERITY_WARNING, "code 2", "text 2");

  ASSERT_EQ(message_context.max_line_number(), 2);
}

TEST(messaging_message_context, max_line_number_max_of_two) {
  Source source("--", LineIndexedUnicodeString(""));

  MessageContext message_context;

  message_context.emit(SourceRange(SourceLocation(source, 3)), SEVERITY_ERROR,
                       "code 1", "text 1");

  message_context.emit(SourceRange(SourceLocation(source, 2)), SEVERITY_WARNING,
                       "code 2", "text 2");

  ASSERT_EQ(message_context.max_line_number(), 3);
}
