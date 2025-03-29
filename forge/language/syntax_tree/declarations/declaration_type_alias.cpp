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

#include <forge/language/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
DeclarationTypeAlias::DeclarationTypeAlias(
    std::optional<SourceRange>&& source_range, std::string&& name,
    std::shared_ptr<BaseType>&& type, bool is_explicit)
    : BaseDeclaration(NODE_DECLARATION_TYPE_ALIAS, std::move(source_range),
                      std::move(name)),
      type(std::move(type)),
      is_explicit(is_explicit) {}

void DeclarationTypeAlias::on_accept(IVisitor& visitor) { visitor.visit(type); }

void DeclarationTypeAlias::on_format_debug_declaration(
    DebugFormatter& formatter) const {
  formatter.field_label("type");
  formatter.node(type);

  formatter.field_label("is_explicit");
  formatter.stream() << (is_explicit ? "true" : "false");
}

bool DeclarationTypeAlias::on_compare_declaration(const BaseNode& other) const {
  return compare_nodes(type,
                       static_cast<const DeclarationTypeAlias&>(other).type) &&
         is_explicit ==
             static_cast<const DeclarationTypeAlias&>(other).is_explicit;
}

std::shared_ptr<BaseNode> DeclarationTypeAlias::on_clone() const {
  return std::make_shared<DeclarationTypeAlias>(
      std::optional<SourceRange>(source_range), std::string(name),
      clone_node(type), is_explicit);
}
}  // namespace forge
