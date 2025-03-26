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
template <typename TValue>
ValueLiteralNumeric<TValue>::ValueLiteralNumeric(
    std::optional<SourceRange>&& source_range, TValue value)
    : BaseValue(NODE_VALUE_BOOL, std::move(source_range)), value(value) {}

template <typename TValue>
void ValueLiteralNumeric<TValue>::on_accept(IVisitor&) {}

template <typename TValue>
void ValueLiteralNumeric<TValue>::on_format_debug(
    DebugFormatter& formatter) const {
  formatter.field_label("value");
  formatter.stream() << value;
}

template <typename TValue>
std::shared_ptr<BaseNode> ValueLiteralNumeric<TValue>::on_clone() const {
  return std::make_shared<ValueLiteralNumeric<TValue>>(
      std::optional<SourceRange>(source_range), value);
}

template <typename TValue>
bool ValueLiteralNumeric<TValue>::on_compare(const BaseNode& other) const {
  return value == static_cast<const ValueLiteralNumeric<TValue>&>(other).value;
}
}  // namespace forge
