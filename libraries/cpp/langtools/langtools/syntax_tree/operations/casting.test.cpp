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

#include <langtools/syntax_tree/domain/base_node.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>

using namespace lt;

namespace {
class TestNodeA : public BaseNode {
 public:
  static const NodeKind NODE_KIND;

  TestNodeA() : BaseNode(NODE_KIND, SourceRange()) {}
  ~TestNodeA() override = default;

 protected:
  virtual void on_format_debug(DebugFormatter&) const override {}

  virtual bool on_compare(const BaseNode&) const override { return true; }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return nullptr;
  }

  virtual void on_accept(IVisitor&) override {}
};

const NodeKind TestNodeA::NODE_KIND = NodeKind("a");

class TestNodeB : public BaseNode {
 public:
  static const NodeKind NODE_KIND;

  TestNodeB() : BaseNode(NODE_KIND, SourceRange()) {}
  ~TestNodeB() override = default;

 protected:
  virtual void on_format_debug(DebugFormatter&) const override {}

  virtual bool on_compare(const BaseNode&) const override { return true; }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return nullptr;
  }

  virtual void on_accept(IVisitor&) override {}
};

const NodeKind TestNodeB::NODE_KIND = NodeKind("b");
}  // namespace

TEST(syntax_tree_operations_casting, cast_null_to_null) {
  std::shared_ptr<BaseNode> node = nullptr;

  std::shared_ptr<TestNodeA> casted_node = try_cast_node<TestNodeA>(node);

  ASSERT_EQ(casted_node, nullptr);
}

TEST(syntax_tree_operations_casting, cast_success) {
  std::shared_ptr<BaseNode> node = std::make_shared<TestNodeA>();

  std::shared_ptr<TestNodeA> casted_node = try_cast_node<TestNodeA>(node);

  ASSERT_EQ(casted_node.get(), node.get());
}

TEST(syntax_tree_operations_casting, cast_failure) {
  std::shared_ptr<BaseNode> node = std::make_shared<TestNodeA>();

  std::shared_ptr<TestNodeB> casted_node = try_cast_node<TestNodeB>(node);

  ASSERT_EQ(casted_node, nullptr);
}
