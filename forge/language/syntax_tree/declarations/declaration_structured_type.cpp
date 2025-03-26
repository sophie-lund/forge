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

#include <forge/language/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
DeclarationStructuredType::DeclarationStructuredType(
    std::optional<SourceRange>&& source_range, std::string&& name,
    StructuredTypeKind kind,
    std::vector<std::shared_ptr<BaseDeclaration>>&& members,
    std::vector<std::shared_ptr<TypeSymbol>>&& extends)
    : BaseDeclaration(NODE_DECLARATION_STRUCTURED_TYPE, std::move(source_range),
                      std::move(name)),
      kind(kind),
      members(std::move(members)),
      extends(std::move(extends)) {}

void DeclarationStructuredType::on_accept(IVisitor& visitor) {
  visitor.visit(members);
  visitor.visit(extends);
}

void DeclarationStructuredType::on_format_debug_declaration(
    DebugFormatter& formatter) const {
  formatter.field_label("kind");
  switch (kind) {
    case StructuredTypeKind::struct_:
      formatter.stream() << "struct";
      break;
    case StructuredTypeKind::interface:
      formatter.stream() << "interface";
      break;
  }

  formatter.field_label("members");
  formatter.node_vector(members);

  formatter.field_label("extends");
  formatter.node_vector(extends);
}

bool DeclarationStructuredType::on_compare_declaration(
    const BaseNode& other) const {
  return kind == static_cast<const DeclarationStructuredType&>(other).kind &&
         compare_node_vectors(
             members,
             static_cast<const DeclarationStructuredType&>(other).members) &&
         compare_node_vectors(
             extends,
             static_cast<const DeclarationStructuredType&>(other).extends);
}
}  // namespace forge
