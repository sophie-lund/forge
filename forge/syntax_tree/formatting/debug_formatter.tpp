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
                                          uint32_t indentation_width_spaces,
                                          uint32_t indentation_initial_spaces)
    : _stream(std::ref(stream)),
      _indentation_level(0),
      _indentation_width_spaces(indentation_width_spaces),
      _indentation_initial_spaces(indentation_initial_spaces) {}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::node_label(const TNodeKind& kind) {
  stream() << termcolor::grey << "[" << termcolor::bright_blue << kind
           << termcolor::grey << "]" << termcolor::reset;
  indent();
}

template <typename TNodeKind>
template <typename TName>
void DebugFormatter<TNodeKind>::field_label(const TName& name) {
  stream() << std::endl;
  format_indentation();
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
                                       TItemFormatter item_formatter) {
  if (value.empty()) {
    stream() << "[]";
    return;
  }

  indent();

  uint32_t index = 0;
  for (const auto& item : value) {
    stream() << std::endl;
    format_indentation();
    stream() << termcolor::grey << "[" << index << "] = " << termcolor::reset;
    item_formatter(item);

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
  _indentation_level++;
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::unindent() {
  if (_indentation_level > 0) {
    _indentation_level--;
  }
}

template <typename TNodeKind>
template <typename TNode>
void DebugFormatter<TNodeKind>::node(const std::shared_ptr<TNode>& value) {
  if (value) {
    static_cast<const Node<typename TNode::BaseNode, TNodeKind>&>(*value)
        .format_debug(*this);
  } else {
    null();
  }
}

template <typename TNodeKind>
template <typename TNode>
void DebugFormatter<TNodeKind>::node_vector(
    const std::vector<std::shared_ptr<TNode>>& value) {
  vector(value, [&](const std::shared_ptr<TNode>& item) {
    if (item) {
      static_cast<const Node<typename TNode::BaseNode, TNodeKind>&>(*item)
          .format_debug(*this);
    } else {
      null();
    }
  });
}

template <typename TNodeKind>
void DebugFormatter<TNodeKind>::format_indentation() {
  for (decltype(_indentation_initial_spaces) i = 0;
       i < _indentation_initial_spaces +
               _indentation_level * _indentation_width_spaces;
       i++) {
    _stream.get() << " ";
  }
}
}  // namespace forge
