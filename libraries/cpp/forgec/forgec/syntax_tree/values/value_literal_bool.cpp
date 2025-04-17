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

#include <forgec/syntax_tree/values/value_literal_bool.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
const lt::NodeKind ValueLiteralBool::NODE_KIND = NODE_VALUE_LITERAL_BOOL;

ValueLiteralBool::ValueLiteralBool(lt::SourceRange&& source_range, bool value)
    : BaseValue(NODE_KIND, std::move(source_range)), value(value) {}

void ValueLiteralBool::on_accept(lt::IVisitor&) {}

void ValueLiteralBool::on_format_debug(lt::DebugFormatter& formatter) const {
  formatter.field_label("value");
  formatter.stream() << (value ? "true" : "false");
}

std::shared_ptr<lt::BaseNode> ValueLiteralBool::on_clone() const {
  return std::make_shared<ValueLiteralBool>(lt::SourceRange(source_range),
                                            value);
}

bool ValueLiteralBool::on_compare(const lt::BaseNode& other) const {
  return value == static_cast<const ValueLiteralBool&>(other).value;
}
}  // namespace forge
