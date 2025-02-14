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

#include <forge/syntax_tree/formatting/debug_formatter.hpp>

using namespace forge;

TEST(syntax_tree_formatting_debug_formatter, format_property_integer) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 0);

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.stream() << 42;

  ASSERT_EQ(stream.str(), "[Test]\n  x = 42");
}

TEST(syntax_tree_formatting_debug_formatter,
     format_property_indentation_start) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 3);

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.stream() << 42;

  ASSERT_EQ(stream.str(), "[Test]\n     x = 42");
}

TEST(syntax_tree_formatting_debug_formatter,
     format_property_too_many_unindents) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 3);

  formatter.unindent();

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.stream() << 42;

  ASSERT_EQ(stream.str(), "[Test]\n     x = 42");
}

TEST(syntax_tree_formatting_debug_formatter, format_property_null) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 0);

  formatter.unindent();

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.null();

  ASSERT_EQ(stream.str(), "[Test]\n  x = null");
}

TEST(syntax_tree_formatting_debug_formatter, format_property_string) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 0);

  formatter.unindent();

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.string("asdf");

  ASSERT_EQ(stream.str(), "[Test]\n  x = \"asdf\"");
}

TEST(syntax_tree_formatting_debug_formatter, format_property_empty_vector) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 0);

  formatter.unindent();

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.vector(std::vector<int>({}),
                   [&](int item) { formatter.stream() << item; });

  ASSERT_EQ(stream.str(), "[Test]\n  x = []");
}

TEST(syntax_tree_formatting_debug_formatter,
     format_property_vector_with_one_item) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 0);

  formatter.unindent();

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.vector(std::vector<int>({1}),
                   [&](int item) { formatter.stream() << item; });

  ASSERT_EQ(stream.str(), "[Test]\n  x = \n    [0] = 1");
}

TEST(syntax_tree_formatting_debug_formatter,
     format_property_vector_with_two_items) {
  std::stringstream stream;
  DebugFormatter<std::string> formatter(stream, 2, 0);

  formatter.unindent();

  formatter.node_label("Test");
  formatter.field_label("x");
  formatter.vector(std::vector<int>({1, 2}),
                   [&](int item) { formatter.stream() << item; });

  ASSERT_EQ(stream.str(), "[Test]\n  x = \n    [0] = 1\n    [1] = 2");
}
