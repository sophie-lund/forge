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

#include <langtools/messaging/message.hpp>

using namespace lt;

TEST(messaging_message, construct) {
  Source source("--", LineIndexedUnicodeString(""));
  Message message(SourceRange(SourceLocation(source), SourceLocation(source)),
                  SEVERITY_ERROR, "code", "text");
  ASSERT_EQ(message.severity.get().value, SEVERITY_ERROR.value);
  ASSERT_EQ(message.code, "code");
  ASSERT_EQ(message.text, "text");
}

TEST(messaging_message, child) {
  Source source("--", LineIndexedUnicodeString(""));
  Message message =
      Message(SourceRange(SourceLocation(source), SourceLocation(source)),
              SEVERITY_ERROR, "code 1", "text 1")
          .child(SourceRange(SourceLocation(source), SourceLocation(source)),
                 SEVERITY_ERROR, "text 2")
          .child(SourceRange(SourceLocation(source), SourceLocation(source)),
                 SEVERITY_ERROR, "text 3");
  ASSERT_EQ(message.severity.get().value, SEVERITY_ERROR.value);
  ASSERT_EQ(message.code, "code 1");
  ASSERT_EQ(message.text, "text 1");
  ASSERT_EQ(message.children.size(), 2);
  ASSERT_EQ(message.children[0].severity.get().value, SEVERITY_ERROR.value);
  ASSERT_EQ(message.children[0].text, "text 2");
  ASSERT_EQ(message.children[1].severity.get().value, SEVERITY_ERROR.value);
  ASSERT_EQ(message.children[1].text, "text 3");
}
