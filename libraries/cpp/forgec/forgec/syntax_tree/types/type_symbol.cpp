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

#include <forgec/syntax_tree/types/type_symbol.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind TypeSymbol::NODE_KIND = NODE_TYPE_SYMBOL;

TypeSymbol::TypeSymbol(lt::SourceRange&& source_range, std::string&& name)
    : BaseType(NODE_KIND, std::move(source_range)), name(std::move(name)) {}

void TypeSymbol::on_accept(lt::IVisitor&) {}

void TypeSymbol::on_format_debug_type(lt::DebugFormatter& formatter) const {
  formatter.field_label("name");
  formatter.string(name);
}

std::shared_ptr<lt::BaseNode> TypeSymbol::on_clone_type() const {
  return std::make_shared<TypeSymbol>(lt::SourceRange(source_range),
                                      std::string(name));
}

bool TypeSymbol::on_compare_type(const lt::BaseNode& other) const {
  return name == static_cast<const TypeSymbol&>(other).name;
}

std::optional<std::string> TypeSymbol::on_get_referenced_symbol_name() const {
  return name;
}

void TypeSymbol::on_resolve_symbol(
    std::shared_ptr<lt::BaseNode> referenced_node) {
  referenced_declaration =
      std::static_pointer_cast<BaseDeclaration>(referenced_node);
}
}  // namespace forge
