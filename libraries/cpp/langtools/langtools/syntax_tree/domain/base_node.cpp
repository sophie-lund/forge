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

#include <langtools/syntax_tree/domain/base_node.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/visitors/ihandler.hpp>
#include <langtools/syntax_tree/visitors/pass.hpp>

namespace lt {
namespace {
class VisitorForEachDirectChild : public IVisitor {
 public:
  VisitorForEachDirectChild(
      std::function<void(const BaseNode&)> on_direct_child)
      : _on_direct_child(on_direct_child), _depth(0) {}

 protected:
  virtual VisitorStatus on_enter(std::shared_ptr<BaseNode>& node) final {
    if (_depth == 0) {
      _depth++;
      return VisitorStatus::continue_;
    } else if (_depth == 1) {
      _on_direct_child(*node);
      _depth++;
      return VisitorStatus::do_not_traverse_children;
    } else {
      // LCOV_EXCL_START
      LT_ABORT("invalid depth in visitor direct child visitor: " << _depth);
      // LCOV_EXCL_STOP
    }
  }

  virtual VisitorStatus on_leave(std::shared_ptr<BaseNode>&) final {
    _depth--;

    return VisitorStatus::continue_;
  }

 private:
  std::function<void(const BaseNode&)> _on_direct_child;
  int32_t _depth;
};
}  // namespace

BaseNode::BaseNode(NodeKind kind, SourceRange&& source_range)
    : kind(kind), source_range(std::move(source_range)) {}

BaseNode::~BaseNode() {}

void BaseNode::for_each_direct_child(
    std::function<void(const BaseNode&)> on_direct_child) const {
  VisitorForEachDirectChild visitor(on_direct_child);

  std::shared_ptr<BaseNode> this_shared(const_cast<BaseNode*>(this),
                                        [](BaseNode*) {});

  visitor.visit(this_shared);
}

bool BaseNode::compare(const BaseNode& other) const {
  if (kind != other.kind) {
    return false;
  }

  return on_compare(other);
}

std::shared_ptr<BaseNode> BaseNode::clone() const { return on_clone(); }

void BaseNode::accept(IVisitor& visitor) { on_accept(visitor); }

void BaseNode::format_debug(DebugFormatter& formatter) const {
  formatter.node_label(kind);
  on_format_debug(formatter);
  formatter.unindent();
}

void BaseNode::format_brief(std::ostream& stream) const {
  on_format_brief(stream);
}

void BaseNode::on_format_brief(std::ostream& stream) const { stream << kind; }
}  // namespace lt
