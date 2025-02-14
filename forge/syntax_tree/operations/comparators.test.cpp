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
#include <forge/syntax_tree/operations/comparators.hpp>

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

TEST(syntax_tree_operations_comparators, chained_logical_and) {
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

TEST(syntax_tree_operations_comparators, nodes_null_null) {
  ASSERT_TRUE(compare_nodes(std::shared_ptr<TestNode>(nullptr),
                            std::shared_ptr<TestNode>(nullptr)));
}

TEST(syntax_tree_operations_comparators, nodes_null_non_null) {
  Source source("--", LineIndexedString(""));

  ASSERT_FALSE(compare_nodes(
      std::shared_ptr<TestNode>(nullptr),
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source)))));
}

TEST(syntax_tree_operations_comparators, nodes_non_null_null) {
  Source source("--", LineIndexedString(""));

  ASSERT_FALSE(compare_nodes(
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::shared_ptr<TestNode>(nullptr)));
}

TEST(syntax_tree_operations_comparators, nodes_non_null_non_null_identical) {
  Source source("--", LineIndexedString(""));

  ASSERT_TRUE(compare_nodes(
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source)))));
}

TEST(syntax_tree_operations_comparators, nodes_non_null_non_null_different) {
  Source source("--", LineIndexedString(""));

  ASSERT_FALSE(compare_nodes(
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("b"),
          SourceRange(SourceLocation(source), SourceLocation(source)))));
}

TEST(syntax_tree_operations_comparators, node_vectors_different_lengths) {
  Source source("--", LineIndexedString(""));

  std::vector<std::shared_ptr<TestNode>> lhs = {
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("c"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  std::vector<std::shared_ptr<TestNode>> rhs = {
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  ASSERT_FALSE(compare_node_vectors<TestNode>(lhs, rhs));
}

TEST(syntax_tree_operations_comparators, node_vectors_identical) {
  Source source("--", LineIndexedString(""));

  std::vector<std::shared_ptr<TestNode>> lhs = {
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("c"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  std::vector<std::shared_ptr<TestNode>> rhs = {
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("c"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  ASSERT_TRUE(compare_node_vectors<TestNode>(lhs, rhs));
}

TEST(syntax_tree_operations_comparators, node_vectors_different_nodes) {
  Source source("--", LineIndexedString(""));

  std::vector<std::shared_ptr<TestNode>> lhs = {
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("c"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  std::vector<std::shared_ptr<TestNode>> rhs = {
      std::make_shared<TestNode>(
          NodeKind("a"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
      std::make_shared<TestNode>(
          NodeKind("d"),
          SourceRange(SourceLocation(source), SourceLocation(source))),
  };

  ASSERT_FALSE(compare_node_vectors<TestNode>(lhs, rhs));
}
