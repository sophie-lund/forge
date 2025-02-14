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

#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>

using namespace forge;

class TestNode : public Node {
 public:
  TestNode(NodeKind&& kind, std::optional<SourceRange>&& source_range)
      : Node(std::move(kind), std::move(source_range)) {}

  virtual void on_format_debug(DebugFormatter&) const override {}

 protected:
  virtual bool on_compare(const Node&) const override { return true; }

  virtual std::shared_ptr<Node> on_clone() const override {
    return std::make_shared<TestNode>(NodeKind(kind),
                                      std::optional<SourceRange>(source_range));
  }

  virtual void on_accept(Pass&) override {}
};

TEST(syntax_tree_operations_cloners, clone_node_null) {
  auto cloned = clone_node<TestNode>(nullptr);
  ASSERT_FALSE(cloned);
}

TEST(syntax_tree_operations_cloners, clone_node_non_null) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone_node<TestNode>(std::make_shared<TestNode>(
      NodeKind("a"),
      SourceRange(SourceLocation(source), SourceLocation(source))));
  ASSERT_TRUE(cloned);
  ASSERT_EQ(cloned->kind, NodeKind("a"));
}

TEST(syntax_tree_operations_cloners, clone_node_vector_empty) {
  Source source("--", LineIndexedString(""));

  auto cloned =
      clone_node_vector<TestNode>(std::vector<std::shared_ptr<TestNode>>());
  ASSERT_TRUE(cloned.empty());
}

TEST(syntax_tree_operations_cloners, clone_node_vector_one_null) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone_node_vector<TestNode>(
      std::vector<std::shared_ptr<TestNode>>({nullptr}));
  ASSERT_EQ(cloned.size(), 1);
  ASSERT_FALSE(cloned[0]);
}

TEST(syntax_tree_operations_cloners, clone_node_vector_one_non_null) {
  Source source("--", LineIndexedString(""));

  auto cloned = clone_node_vector<TestNode>(
      std::vector<std::shared_ptr<TestNode>>({std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source)))}));
  ASSERT_EQ(cloned.size(), 1);
  ASSERT_TRUE(cloned[0]);
  ASSERT_EQ(cloned[0]->kind, NodeKind("a"));
}

TEST(syntax_tree_operations_cloners, clone_node_vector_three_non_null) {
  Source source("--", LineIndexedString(""));

  auto cloned =
      clone_node_vector<TestNode>(std::vector<std::shared_ptr<TestNode>>(
          {std::make_shared<TestNode>(
               NodeKind("a"),
               SourceRange(SourceLocation(source), SourceLocation(source))),
           std::make_shared<TestNode>(
               NodeKind("b"),
               SourceRange(SourceLocation(source), SourceLocation(source))),
           std::make_shared<TestNode>(
               NodeKind("c"),
               SourceRange(SourceLocation(source), SourceLocation(source)))}));
  ASSERT_EQ(cloned.size(), 3);
  ASSERT_TRUE(cloned[0]);
  ASSERT_EQ(cloned[0]->kind, NodeKind("a"));
  ASSERT_TRUE(cloned[1]);
  ASSERT_EQ(cloned[1]->kind, NodeKind("b"));
  ASSERT_TRUE(cloned[2]);
  ASSERT_EQ(cloned[2]->kind, NodeKind("c"));
}
