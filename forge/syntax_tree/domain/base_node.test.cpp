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

#include <forge/messaging/message_context.hpp>
#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>

using namespace forge;

class MinimalNode : public Node {
 public:
  MinimalNode(std::optional<SourceRange>&& source_range)
      : Node(NodeKind("dummy"), std::move(source_range)) {}
  ~MinimalNode() override = default;

  virtual void on_format_debug(DebugFormatter&) const override {}

 protected:
  virtual bool on_compare(const Node&) const override { return true; }

  virtual std::shared_ptr<Node> on_clone() const override { return nullptr; }

  virtual void on_accept(Pass&) override {}
};

TEST(syntax_tree_domain_base_node, construct_with_optional_source_range) {
  Source source("--", LineIndexedString(""));

  MinimalNode node((std::optional<const SourceRange>(
      SourceRange(SourceLocation(source), SourceLocation(source)))));

  ASSERT_TRUE(node.source_range.has_value());
}

TEST(syntax_tree_domain_base_node, construct_with_implicit_source_range) {
  Source source("--", LineIndexedString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));
  ASSERT_TRUE(node.source_range.has_value());
}

TEST(syntax_tree_domain_base_node, construct_with_null_source_range) {
  MinimalNode node(std::nullopt);
  ASSERT_FALSE(node.source_range.has_value());
}

TEST(syntax_tree_domain_base_node, construct_with_get_source_range_by_deref) {
  Source source("--", LineIndexedString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.source_range.has_value());
}

TEST(syntax_tree_domain_base_node, construct_with_get_source_range_by_arrow) {
  Source source("--", LineIndexedString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.source_range.has_value());
}

class VisitableNode : public Node {
 public:
  VisitableNode(NodeKind&& kind)
      : Node(std::move(kind), std::nullopt), visit_count(0) {}

  virtual ~VisitableNode() = 0;

  int visit_count;
};

VisitableNode::~VisitableNode() {}

class VisitableNodeNoChildren : public VisitableNode {
 public:
  VisitableNodeNoChildren() : VisitableNode(NodeKind("dummy")) {}

  virtual void on_format_debug(DebugFormatter&) const override {}

 protected:
  virtual bool on_compare(const Node&) const override { return true; }

  virtual std::shared_ptr<Node> on_clone() const override { return nullptr; }

  void on_accept(Pass&) override { visit_count++; }
};

class VisitableNodeWithChildren : public VisitableNode {
 public:
  VisitableNodeWithChildren(std::shared_ptr<VisitableNode>&& child0,
                            std::shared_ptr<VisitableNode>&& child1)
      : VisitableNode(NodeKind("dummy")),
        child0(std::move(child0)),
        child1(std::move(child1)) {}

  virtual void on_format_debug(DebugFormatter&) const override {}

  std::shared_ptr<VisitableNode> child0;
  std::shared_ptr<VisitableNode> child1;

 protected:
  virtual bool on_compare(const Node&) const override { return true; }

  virtual std::shared_ptr<Node> on_clone() const override { return nullptr; }

  void on_accept(Pass& pass) override {
    visit_count++;

    pass.visit(child0);
    pass.visit(child1);
  }
};

class MinimalHandler : public Handler {
 public:
  MinimalHandler() : Handler(), enter_count(0), leave_count(0) {}

  Output on_enter(Input& input) override {
    if (enter_count > 0) {
      EXPECT_GT(input.stack().size(), 0);
    }

    enter_count++;

    return Output();
  }

  Output on_leave(Input&) override {
    leave_count++;

    return Output();
  }

  int enter_count;
  int leave_count;
};

TEST(syntax_tree_domain_base_node, visit_no_children) {
  auto node = std::make_shared<VisitableNodeNoChildren>();

  MessageContext message_context;

  Pass pass(message_context);
  auto handler = std::make_unique<MinimalHandler>();
  auto handler_pointer = handler.get();
  pass.add_handler(std::move(handler));

  pass.visit(node);

  ASSERT_EQ(node->visit_count, 1);
  ASSERT_EQ(handler_pointer->enter_count, 1);
  ASSERT_EQ(handler_pointer->leave_count, 1);
}

TEST(syntax_tree_domain_base_node, visit_with_children) {
  auto node = std::make_shared<VisitableNodeWithChildren>(
      std::make_shared<VisitableNodeNoChildren>(),
      std::make_shared<VisitableNodeNoChildren>());

  MessageContext message_context;

  Pass pass(message_context);
  auto handler = std::make_unique<MinimalHandler>();
  auto handler_pointer = handler.get();
  pass.add_handler(std::move(handler));

  pass.visit(node);

  ASSERT_EQ(node->visit_count, 1);
  ASSERT_EQ(node->child0->visit_count, 1);
  ASSERT_EQ(node->child1->visit_count, 1);
  ASSERT_EQ(handler_pointer->enter_count, 3);
  ASSERT_EQ(handler_pointer->leave_count, 3);
}
