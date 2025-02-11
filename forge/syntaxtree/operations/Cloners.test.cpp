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

#include <forge/syntaxtree/domain/Node.hpp>
#include <forge/syntaxtree/operations/Cloners.hpp>

using namespace forge::syntaxtree;
using namespace forge::messaging;
using namespace forge::parsing;

class TestNode : public Node<TestNode, std::string> {
 public:
  TestNode(std::string&& kind, std::optional<SourceRange>&& sourceRange)
      : Node(std::move(kind), std::move(sourceRange)) {}

  virtual void onFormatDebug(DebugFormatter<std::string>&) const override {}

 protected:
  virtual bool onCompare(const TestNode&) const override { return true; }

  virtual std::shared_ptr<TestNode> onClone() const override {
    return std::make_shared<TestNode>(std::string(kind),
                                      std::optional<SourceRange>(sourceRange));
  }

  virtual void onAccept(Pass<TestNode>&) override {}
};

TEST(Cloners, CloneNode_Null) {
  auto cloned = clone<TestNode>(nullptr);
  ASSERT_FALSE(cloned);
}

TEST(Cloners, CloneNode_NonNull) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone<TestNode>(std::make_shared<TestNode>(
      "a", SourceRange(SourceLocation(source), SourceLocation(source))));
  ASSERT_TRUE(cloned);
  ASSERT_EQ(cloned->kind, "a");
}

TEST(Cloners, CloneNodeVector_Empty) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone<TestNode>(std::vector<std::shared_ptr<TestNode>>());
  ASSERT_TRUE(cloned.empty());
}

TEST(Cloners, CloneNodeVector_OneNull) {
  Source source("--", LineIndexedString(""));

  auto cloned =
      clone<TestNode>(std::vector<std::shared_ptr<TestNode>>({nullptr}));
  ASSERT_EQ(cloned.size(), 1);
  ASSERT_FALSE(cloned[0]);
}

TEST(Cloners, CloneNodeVector_OneNonNull) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone<TestNode>(
      std::vector<std::shared_ptr<TestNode>>({std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source)))}));
  ASSERT_EQ(cloned.size(), 1);
  ASSERT_TRUE(cloned[0]);
  ASSERT_EQ(cloned[0]->kind, "a");
}

TEST(Cloners, CloneNodeVector_ThreeNonNull) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone<TestNode>(std::vector<std::shared_ptr<TestNode>>(
      {std::make_shared<TestNode>(
           "a", SourceRange(SourceLocation(source), SourceLocation(source))),
       std::make_shared<TestNode>(
           "b", SourceRange(SourceLocation(source), SourceLocation(source))),
       std::make_shared<TestNode>(
           "c", SourceRange(SourceLocation(source), SourceLocation(source)))}));
  ASSERT_EQ(cloned.size(), 3);
  ASSERT_TRUE(cloned[0]);
  ASSERT_EQ(cloned[0]->kind, "a");
  ASSERT_TRUE(cloned[1]);
  ASSERT_EQ(cloned[1]->kind, "b");
  ASSERT_TRUE(cloned[2]);
  ASSERT_EQ(cloned[2]->kind, "c");
}
