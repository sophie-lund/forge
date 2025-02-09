// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

#include <gtest/gtest.h>

#include <forge/syntaxtree/DebugFormatter.hpp>

using namespace sycamore::syntaxtree;

class NodelessDebugFormatter : public DebugFormatter<std::string> {
 public:
  NodelessDebugFormatter(std::ostream& stream, uint32_t indentationWidthSpaces,
                         uint32_t indentationInitialSpaces)
      : DebugFormatter<std::string>(stream, indentationWidthSpaces,
                                    indentationInitialSpaces) {}

 protected:
  virtual void onFormatNodeKind(const std::string& kind) override {
    stream() << kind;
  }
};

TEST(DebugFormatter, FormatProperty_Integer) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 0);

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.stream() << 42;

  ASSERT_EQ(stream.str(), "[Test]\n  x = 42");
}

TEST(DebugFormatter, FormatProperty_IndentationStart) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 3);

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.stream() << 42;

  ASSERT_EQ(stream.str(), "[Test]\n     x = 42");
}

TEST(DebugFormatter, FormatProperty_TooManyUnindents) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 3);

  formatter.unindent();

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.stream() << 42;

  ASSERT_EQ(stream.str(), "[Test]\n     x = 42");
}

TEST(DebugFormatter, FormatProperty_Null) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 0);

  formatter.unindent();

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.null();

  ASSERT_EQ(stream.str(), "[Test]\n  x = null");
}

TEST(DebugFormatter, FormatProperty_String) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 0);

  formatter.unindent();

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.string("asdf");

  ASSERT_EQ(stream.str(), "[Test]\n  x = \"asdf\"");
}

TEST(DebugFormatter, FormatProperty_EmptyVector) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 0);

  formatter.unindent();

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.vector(std::vector<int>({}),
                   [&](int item) { formatter.stream() << item; });

  ASSERT_EQ(stream.str(), "[Test]\n  x = []");
}

TEST(DebugFormatter, FormatProperty_VectorWithOneItem) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 0);

  formatter.unindent();

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.vector(std::vector<int>({1}),
                   [&](int item) { formatter.stream() << item; });

  ASSERT_EQ(stream.str(), "[Test]\n  x = \n    [0] = 1");
}

TEST(DebugFormatter, FormatProperty_VectorWithTwoItems) {
  std::stringstream stream;
  NodelessDebugFormatter formatter(stream, 2, 0);

  formatter.unindent();

  formatter.nodeLabel("Test");
  formatter.fieldLabel("x");
  formatter.vector(std::vector<int>({1, 2}),
                   [&](int item) { formatter.stream() << item; });

  ASSERT_EQ(stream.str(), "[Test]\n  x = \n    [0] = 1\n    [1] = 2");
}
