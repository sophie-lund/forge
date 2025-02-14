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
#include <forge/syntaxtree/operations/Comparators.hpp>

using namespace forge;

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

TEST(Comparators, ChainedLogicalAnd) {
  ASSERT_TRUE(true && true && true);
  ASSERT_FALSE(false && true && true);
  ASSERT_FALSE(true && false && true);
  ASSERT_FALSE(true && true && false);
  ASSERT_FALSE(false && false && true);
  ASSERT_FALSE(false && true && false);
  ASSERT_FALSE(false && false && false);

  ASSERT_TRUE(true && true && true && true);
  ASSERT_FALSE(false && true && true && true);
  ASSERT_FALSE(true && false && true && true);
  ASSERT_FALSE(true && true && false && true);
  ASSERT_FALSE(true && true && true && false);
  ASSERT_FALSE(false && false && true && true);
  ASSERT_FALSE(false && true && false && true);
  ASSERT_FALSE(false && true && true && false);
  ASSERT_FALSE(false && false && false && true);
  ASSERT_FALSE(false && false && true && false);
  ASSERT_FALSE(false && false && false && false);
}

TEST(Comparators, Nodes_Null_Null) {
  ASSERT_TRUE(compareNodes(std::shared_ptr<TestNode>(nullptr),
                           std::shared_ptr<TestNode>(nullptr)));
}

TEST(Comparators, Nodes_Null_NonNull) {
  Source source("--", LineIndexedString(""));

  ASSERT_FALSE(compareNodes(
      std::shared_ptr<TestNode>(nullptr),
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source)))));
}

TEST(Comparators, Nodes_NonNull_Null) {
  Source source("--", LineIndexedString(""));

  ASSERT_FALSE(compareNodes(
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::shared_ptr<TestNode>(nullptr)));
}

TEST(Comparators, Nodes_NonNull_NonNull_Identical) {
  Source source("--", LineIndexedString(""));

  ASSERT_TRUE(compareNodes(
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source)))));
}

TEST(Comparators, Nodes_NonNull_NonNull_Different) {
  Source source("--", LineIndexedString(""));

  ASSERT_FALSE(compareNodes(
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "b", SourceRange(SourceLocation(source), SourceLocation(source)))));
}

TEST(Comparators, NodeVectors_DifferentLengths) {
  Source source("--", LineIndexedString(""));

  std::vector<std::shared_ptr<TestNode>> lhs = {
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "c", SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  std::vector<std::shared_ptr<TestNode>> rhs = {
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  ASSERT_FALSE(compareNodeVectors<TestNode>(lhs, rhs));
}

TEST(Comparators, NodeVectors_Identical) {
  Source source("--", LineIndexedString(""));

  std::vector<std::shared_ptr<TestNode>> lhs = {
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "c", SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  std::vector<std::shared_ptr<TestNode>> rhs = {
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "c", SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  ASSERT_TRUE(compareNodeVectors<TestNode>(lhs, rhs));
}

TEST(Comparators, NodeVectors_DifferentNodes) {
  Source source("--", LineIndexedString(""));

  std::vector<std::shared_ptr<TestNode>> lhs = {
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "c", SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  std::vector<std::shared_ptr<TestNode>> rhs = {
      std::make_shared<TestNode>(
          "a", SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          "d", SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  ASSERT_FALSE(compareNodeVectors<TestNode>(lhs, rhs));
}
