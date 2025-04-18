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

namespace lt {
template <typename TName>
void DebugFormatter::field_label(const TName& name) {
  stream() << std::endl;
  format_indentation();
  stream() << termcolor::green << name << termcolor::bright_grey << " = "
           << termcolor::reset;
}

template <typename TValue>
void DebugFormatter::string(const TValue& value) {
  stream() << std::format("{:?}", value);
}

template <typename TItem, typename TItemFormatter>
void DebugFormatter::vector(const std::vector<TItem>& value,
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
    stream() << termcolor::bright_grey << "[" << index
             << "] = " << termcolor::reset;
    item_formatter(item);

    index++;
  }

  unindent();
}

template <typename TNode>
void DebugFormatter::node(const std::shared_ptr<TNode>& value) {
  if (value) {
    value->format_debug(*this);
  } else {
    null();
  }
}

template <typename TNode>
void DebugFormatter::node_vector(
    const std::vector<std::shared_ptr<TNode>>& value) {
  vector(value, [&](const std::shared_ptr<TNode>& item) {
    if (item) {
      item->format_debug(*this);
    } else {
      null();
    }
  });
}
}  // namespace lt
