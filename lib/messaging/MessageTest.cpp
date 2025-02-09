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

#include <forge/messaging/Message.hpp>

using namespace forge::messaging;
using namespace forge::parsing;

TEST(Message, Construct) {
  Source source("--", LineIndexedString(""));
  Message message(SourceRange(SourceLocation(source), SourceLocation(source)),
                  SEVERITY_ERROR, "code", "text");
  ASSERT_EQ(message.severity().value(), SEVERITY_ERROR.value());
  ASSERT_EQ(message.code(), "code");
  ASSERT_EQ(message.text(), "text");
}
