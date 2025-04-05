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

#include <forge/language/syntax_tree/values/value_symbol.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
const NodeKind ValueSymbol::NODE_KIND = NODE_VALUE_SYMBOL;

ValueSymbol::ValueSymbol(std::optional<SourceRange>&& source_range,
                         std::string&& name)
    : BaseValue(NODE_KIND, std::move(source_range)), name(std::move(name)) {}

void ValueSymbol::on_accept(IVisitor&) {}

void ValueSymbol::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("name");
  formatter.string(name);
}

std::shared_ptr<BaseNode> ValueSymbol::on_clone() const {
  return std::make_shared<ValueSymbol>(std::optional<SourceRange>(source_range),
                                       std::string(name));
}

bool ValueSymbol::on_compare(const BaseNode& other) const {
  return name == static_cast<const ValueSymbol&>(other).name;
}

std::optional<std::string> ValueSymbol::on_get_referenced_symbol_name() const {
  return name;
}

void ValueSymbol::on_resolve_symbol(std::shared_ptr<BaseNode> referenced_node) {
  referenced_declaration =
      std::static_pointer_cast<BaseDeclaration>(referenced_node);
}
}  // namespace forge
