// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

#include <termcolor/termcolor.hpp>

namespace sycamore::syntaxtree {
template <typename TBaseNode, typename TKind>
class Node;

template <typename TNodeKind>
DebugFormatter<TNodeKind>::DebugFormatter(std::ostream& stream,
                                          uint32_t indentationWidthSpaces,
                                          uint32_t indentationInitialSpaces)
    : stream_(std::ref(stream)),
      indentationLevel_(0),
      indentationWidthSpaces_(indentationWidthSpaces),
      indentationInitialSpaces_(indentationInitialSpaces) {}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::nodeLabel(const TNodeKind& kind) {
  stream() << termcolor::grey << "[" << termcolor::bright_blue;
  onFormatNodeKind(kind);
  stream() << termcolor::grey << "]" << termcolor::reset;
  indent();
}

template <typename TNodeKind>
template <typename TName>
void DebugFormatter<TNodeKind>::fieldLabel(const TName& name) {
  stream() << std::endl;
  formatIndentation();
  stream() << termcolor::green << name << termcolor::grey << " = "
           << termcolor::reset;
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::null() {
  stream() << termcolor::red << "null" << termcolor::reset;
}

template <typename TNodeKind>
template <typename TValue>
void DebugFormatter<TNodeKind>::string(const TValue& value) {
  stream() << std::format("{:?}", value);
}

template <typename TNodeKind>
template <typename TItem, typename TItemFormatter>
void DebugFormatter<TNodeKind>::vector(const std::vector<TItem>& value,
                                       TItemFormatter itemFormatter) {
  if (value.empty()) {
    stream() << "[]";
    return;
  }

  indent();

  uint32_t index = 0;
  for (const auto& item : value) {
    stream() << std::endl;
    formatIndentation();
    stream() << termcolor::grey << "[" << index << "] = " << termcolor::reset;
    itemFormatter(item);

    index++;
  }

  unindent();
}

template <typename TNodeKind>
std::ostream& DebugFormatter<TNodeKind>::stream() {
  return stream_.get();
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::indent() {
  indentationLevel_++;
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::unindent() {
  if (indentationLevel_ > 0) {
    indentationLevel_--;
  }
}

template <typename TNodeKind>
template <typename TNode>
void DebugFormatter<TNodeKind>::node(const std::shared_ptr<TNode>& value) {
  if (value) {
    nodeLabel(value->kind);

    static_cast<const Node<typename TNode::BaseNode, TNodeKind>&>(*value)
        .onFormatDebug(*this);

    unindent();
  } else {
    null();
  }
}

template <typename TNodeKind>
template <typename TNode>
void DebugFormatter<TNodeKind>::nodeVector(
    const std::vector<std::shared_ptr<TNode>>& value) {
  vector(value, [&](const std::shared_ptr<TNode>& item) {
    if (item) {
      nodeLabel(item->kind);

      static_cast<const Node<typename TNode::BaseNode, TNodeKind>&>(*item)
          .onFormatDebug(*this);

      unindent();
    } else {
      null();
    }
  });
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::formatIndentation() {
  for (decltype(indentationInitialSpaces_) i = 0;
       i <
       indentationInitialSpaces_ + indentationLevel_ * indentationWidthSpaces_;
       i++) {
    stream_.get() << " ";
  }
}
}  // namespace sycamore::syntaxtree
