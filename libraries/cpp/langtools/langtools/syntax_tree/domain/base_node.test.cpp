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
#include <langtools/syntax_tree/domain/base_node.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/visitors/pass.hpp>

using namespace lt;

class MinimalNode : public BaseNode {
 public:
  MinimalNode(SourceRange&& source_range)
      : BaseNode(NodeKind("dummy"), std::move(source_range)) {}
  ~MinimalNode() override = default;

  virtual void on_format_debug(DebugFormatter&) const override {}

 protected:
  virtual bool on_compare(const BaseNode&) const override { return true; }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return nullptr;
  }

  virtual void on_accept(IVisitor&) override {}
};

TEST(syntax_tree_domain_base_node, construct_with_optional_source_range) {
  Source source("--", LineIndexedUnicodeString(""));

  MinimalNode node = MinimalNode(
      SourceRange(SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.source_range);
}

TEST(syntax_tree_domain_base_node, construct_with_implicit_source_range) {
  Source source("--", LineIndexedUnicodeString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));
  ASSERT_TRUE(node.source_range);
}

TEST(syntax_tree_domain_base_node, construct_with_null_source_range) {
  MinimalNode node = MinimalNode(SourceRange());
  ASSERT_FALSE(node.source_range);
}

TEST(syntax_tree_domain_base_node, construct_with_get_source_range_by_deref) {
  Source source("--", LineIndexedUnicodeString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.source_range);
}

TEST(syntax_tree_domain_base_node, construct_with_get_source_range_by_arrow) {
  Source source("--", LineIndexedUnicodeString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.source_range);
}

class VisitableNode : public BaseNode {
 public:
  VisitableNode(NodeKind&& kind)
      : BaseNode(std::move(kind), SourceRange()), visit_count(0) {}

  virtual ~VisitableNode() = 0;

  int visit_count;
  std::string id;
};

VisitableNode::~VisitableNode() {}

class VisitableNodeNoChildren : public VisitableNode {
 public:
  VisitableNodeNoChildren() : VisitableNode(NodeKind("dummy")) {}

  virtual void on_format_debug(DebugFormatter&) const override {}

 protected:
  virtual bool on_compare(const BaseNode&) const override { return true; }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return nullptr;
  }

  void on_accept(IVisitor&) override { visit_count++; }
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
  virtual bool on_compare(const BaseNode&) const override { return true; }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return nullptr;
  }

  void on_accept(IVisitor& pass) override {
    visit_count++;

    pass.visit(child0);
    pass.visit(child1);
  }
};

class MinimalHandler : public IHandler {
 public:
  MinimalHandler() : IHandler(), enter_count(0), leave_count(0) {}

  Output on_enter(Input<>& input) override {
    if (enter_count > 0) {
      EXPECT_GT(input.stack().size(), 0);
    }

    enter_count++;

    return Output();
  }

  Output on_leave(Input<>&) override {
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

TEST(syntax_tree_domain_base_node, direct_children) {
  auto node = std::make_shared<VisitableNodeWithChildren>(
      std::make_shared<VisitableNodeWithChildren>(
          std::make_shared<VisitableNodeNoChildren>(),
          std::make_shared<VisitableNodeNoChildren>()),
      std::make_shared<VisitableNodeNoChildren>());

  node->id = "parent";
  node->child0->id = "child0";
  node->child1->id = "child1";
  static_pointer_cast<VisitableNodeWithChildren>(node->child0)->child0->id =
      "child0.child0";
  static_pointer_cast<VisitableNodeWithChildren>(node->child0)->child1->id =
      "child0.child1";

  std::vector<std::string> ids_visited;

  node->for_each_direct_child([&ids_visited](const BaseNode& node) {
    ids_visited.push_back(static_cast<const VisitableNode&>(node).id);
  });

  ASSERT_EQ(ids_visited.size(), 2);
  ASSERT_EQ(ids_visited[0], "child0");
  ASSERT_EQ(ids_visited[1], "child1");

  ids_visited.clear();

  node->child0->for_each_direct_child([&ids_visited](const BaseNode& node) {
    ids_visited.push_back(static_cast<const VisitableNode&>(node).id);
  });

  ASSERT_EQ(ids_visited.size(), 2);
  ASSERT_EQ(ids_visited[0], "child0.child0");
  ASSERT_EQ(ids_visited[1], "child0.child1");

  ids_visited.clear();

  node->child1->for_each_direct_child([&ids_visited](const BaseNode& node) {
    ids_visited.push_back(static_cast<const VisitableNode&>(node).id);
  });

  ASSERT_EQ(ids_visited.size(), 0);
}

TEST(syntax_tree_domain_base_node, direct_children_with_null) {
  auto node = std::make_shared<VisitableNodeWithChildren>(
      nullptr, std::make_shared<VisitableNodeNoChildren>());

  node->id = "parent";
  node->child1->id = "child1";

  std::vector<std::string> ids_visited;

  node->for_each_direct_child([&ids_visited](const BaseNode& node) {
    ids_visited.push_back(static_cast<const VisitableNode&>(node).id);
  });

  ASSERT_EQ(ids_visited.size(), 1);
  ASSERT_EQ(ids_visited[0], "child1");
}
