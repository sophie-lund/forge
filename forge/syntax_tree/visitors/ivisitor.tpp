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

namespace forge {
template <typename TNode>
void IVisitor::visit(std::shared_ptr<TNode>& input) {
  // If the input node is null, then there is nothing to do
  if (!input) {
    return;
  }

  std::shared_ptr<BaseNode> input_casted =
      std::static_pointer_cast<BaseNode>(input);

  VisitorStatus on_enter_status = on_enter(input_casted);

  if (on_enter_status == VisitorStatus::halt_traversal) {
    return;
  } else if (on_enter_status != VisitorStatus::do_not_traverse_children) {
    // Visit any children
    static_cast<TNode&>(*input_casted).accept(*this);
  }

  VisitorStatus on_leave_status = on_leave(input_casted);

  if (on_leave_status == VisitorStatus::halt_traversal) {
    return;
  }

  input = std::static_pointer_cast<TNode>(input_casted);
}

template <typename TNode>
void IVisitor::visit(std::vector<std::shared_ptr<TNode>>& input) {
  for (auto& node : input) {
    visit(node);
  }
}
}  // namespace forge
