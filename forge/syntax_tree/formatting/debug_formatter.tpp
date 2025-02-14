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
template <typename TName>
void DebugFormatter::field_label(const TName& name) {
  stream() << std::endl;
  format_indentation();
  stream() << termcolor::green << name << termcolor::grey << " = "
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
    stream() << termcolor::grey << "[" << index << "] = " << termcolor::reset;
    item_formatter(item);

    index++;
  }

  unindent();
}
}  // namespace forge
