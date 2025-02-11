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

using namespace forge::syntaxtree;
using namespace forge::messaging;
using namespace forge::parsing;

class MinimalNode : public Node<MinimalNode, int> {
 public:
  MinimalNode(std::optional<SourceRange>&& sourceRange)
      : Node(0, std::move(sourceRange)) {}
  ~MinimalNode() override = default;

  virtual void onFormatDebug(DebugFormatter<int>&) const override {}

 protected:
  virtual bool onCompare(const MinimalNode&) const override { return true; }

  virtual std::shared_ptr<MinimalNode> onClone() const override {
    return nullptr;
  }

  virtual void onAccept(Pass<MinimalNode>&) override {}
};

TEST(Node, ConstructWithOptionalSourceRange) {
  Source source("--", LineIndexedString(""));

  MinimalNode node((std::optional<const SourceRange>(
      SourceRange(SourceLocation(source), SourceLocation(source)))));

  ASSERT_TRUE(node.sourceRange.has_value());
}

TEST(Node, ConstructWithImplicitSourceRange) {
  Source source("--", LineIndexedString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));
  ASSERT_TRUE(node.sourceRange.has_value());
}

TEST(Node, ConstructWithNullSourceRange) {
  MinimalNode node(std::nullopt);
  ASSERT_FALSE(node.sourceRange.has_value());
}

TEST(Node, GetSourceRangeByDeref) {
  Source source("--", LineIndexedString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.sourceRange.has_value());
}

TEST(Node, GetSourceRangeByArrow) {
  Source source("--", LineIndexedString(""));

  MinimalNode node(
      (SourceRange(SourceLocation(source), SourceLocation(source))));

  ASSERT_TRUE(node.sourceRange.has_value());
}

class VisitableNode : public Node<VisitableNode, int> {
 public:
  VisitableNode(int&& kind)
      : Node(std::move(kind), std::nullopt), visitCount(0) {}

  virtual ~VisitableNode() = 0;

  int visitCount;
};

VisitableNode::~VisitableNode() {}

class VisitableNodeNoChildren : public VisitableNode {
 public:
  VisitableNodeNoChildren() : VisitableNode(0) {}

  virtual void onFormatDebug(DebugFormatter<int>&) const override {}

 protected:
  virtual bool onCompare(const VisitableNode&) const override { return true; }

  virtual std::shared_ptr<VisitableNode> onClone() const override {
    return nullptr;
  }

  void onAccept(Pass<VisitableNode>&) override { visitCount++; }
};

class VisitableNodeWithChildren : public VisitableNode {
 public:
  VisitableNodeWithChildren(std::shared_ptr<VisitableNode>&& child0,
                            std::shared_ptr<VisitableNode>&& child1)
      : VisitableNode(0),
        child0(std::move(child0)),
        child1(std::move(child1)) {}

  virtual void onFormatDebug(DebugFormatter<int>&) const override {}

  std::shared_ptr<VisitableNode> child0;
  std::shared_ptr<VisitableNode> child1;

 protected:
  virtual bool onCompare(const VisitableNode&) const override { return true; }

  virtual std::shared_ptr<VisitableNode> onClone() const override {
    return nullptr;
  }

  void onAccept(Pass<VisitableNode>& pass) override {
    visitCount++;

    pass.visit(child0);
    pass.visit(child1);
  }
};

class MinimalHandler : public Handler<VisitableNode> {
 public:
  MinimalHandler() : Handler(), enterCount(0), leaveCount(0) {}

  Output onEnter(Input& input) override {
    if (enterCount > 0) {
      EXPECT_GT(input.stack().size(), 0);
    }

    enterCount++;

    return Output();
  }

  Output onLeave(Input&) override {
    leaveCount++;

    return Output();
  }

  int enterCount;
  int leaveCount;
};

TEST(Node, Visit_NoChildren) {
  auto node = std::make_shared<VisitableNodeNoChildren>();

  MessageContext messageContext;

  Pass<VisitableNode> pass(messageContext);
  auto handler = std::make_unique<MinimalHandler>();
  auto handlerPointer = handler.get();
  pass.addHandler(std::move(handler));

  pass.visit(node);

  ASSERT_EQ(node->visitCount, 1);
  ASSERT_EQ(handlerPointer->enterCount, 1);
  ASSERT_EQ(handlerPointer->leaveCount, 1);
}

TEST(Node, Visit_WithChildren) {
  auto node = std::make_shared<VisitableNodeWithChildren>(
      std::make_shared<VisitableNodeNoChildren>(),
      std::make_shared<VisitableNodeNoChildren>());

  MessageContext messageContext;

  Pass<VisitableNode> pass(messageContext);
  auto handler = std::make_unique<MinimalHandler>();
  auto handlerPointer = handler.get();
  pass.addHandler(std::move(handler));

  pass.visit(node);

  ASSERT_EQ(node->visitCount, 1);
  ASSERT_EQ(node->child0->visitCount, 1);
  ASSERT_EQ(node->child1->visitCount, 1);
  ASSERT_EQ(handlerPointer->enterCount, 3);
  ASSERT_EQ(handlerPointer->leaveCount, 3);
}
