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

#include <termcolor/termcolor.hpp>

namespace forge {
template <typename TBaseNode, typename TKind>
class Node;

template <typename TNodeKind>
DebugFormatter<TNodeKind>::DebugFormatter(std::ostream& stream,
                                          uint32_t indentationWidthSpaces,
                                          uint32_t indentationInitialSpaces)
    : _stream(std::ref(stream)),
      _indentationLevel(0),
      _indentationWidthSpaces(indentationWidthSpaces),
      _indentationInitialSpaces(indentationInitialSpaces) {}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::nodeLabel(const TNodeKind& kind) {
  stream() << termcolor::grey << "[" << termcolor::bright_blue << kind
           << termcolor::grey << "]" << termcolor::reset;
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
  return _stream.get();
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::indent() {
  _indentationLevel++;
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::unindent() {
  if (_indentationLevel > 0) {
    _indentationLevel--;
  }
}

template <typename TNodeKind>
template <typename TNode>
void DebugFormatter<TNodeKind>::node(const std::shared_ptr<TNode>& value) {
  if (value) {
    static_cast<const Node<typename TNode::BaseNode, TNodeKind>&>(*value)
        .formatDebug(*this);
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
      static_cast<const Node<typename TNode::BaseNode, TNodeKind>&>(*item)
          .formatDebug(*this);
    } else {
      null();
    }
  });
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::formatIndentation() {
  for (decltype(_indentationInitialSpaces) i = 0;
       i <
       _indentationInitialSpaces + _indentationLevel * _indentationWidthSpaces;
       i++) {
    _stream.get() << " ";
  }
}
}  // namespace forge
