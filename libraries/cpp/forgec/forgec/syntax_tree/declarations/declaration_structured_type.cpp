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

#include <forgec/syntax_tree/declarations/declaration_structured_type.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind DeclarationStructuredType::NODE_KIND =
    NODE_DECLARATION_STRUCTURED_TYPE;

DeclarationStructuredType::DeclarationStructuredType(
    lt::SourceRange&& source_range, std::string&& name,
    StructuredTypeKind structured_type_kind,
    std::vector<std::shared_ptr<BaseDeclaration>>&& members,
    std::vector<std::shared_ptr<TypeSymbol>>&& inherits)
    : BaseDeclaration(NODE_KIND, std::move(source_range), std::move(name)),
      structured_type_kind(structured_type_kind),
      members(std::move(members)),
      inherits(std::move(inherits)) {}

void DeclarationStructuredType::on_accept(lt::IVisitor& visitor) {
  visitor.visit(members);
  visitor.visit(inherits);
}

void DeclarationStructuredType::on_format_debug_declaration(
    lt::DebugFormatter& formatter) const {
  formatter.field_label("structured_type_kind");
  switch (structured_type_kind) {
    case StructuredTypeKind::struct_:
      formatter.stream() << "struct";
      break;
    case StructuredTypeKind::interface:
      formatter.stream() << "interface";
      break;
  }

  formatter.field_label("members");
  formatter.node_vector(members);

  formatter.field_label("inherits");
  formatter.node_vector(inherits);
}

bool DeclarationStructuredType::on_compare_declaration(
    const lt::BaseNode& other) const {
  return structured_type_kind ==
             static_cast<const DeclarationStructuredType&>(other)
                 .structured_type_kind &&
         compare_node_vectors(
             members,
             static_cast<const DeclarationStructuredType&>(other).members) &&
         compare_node_vectors(
             inherits,
             static_cast<const DeclarationStructuredType&>(other).inherits);
}

std::shared_ptr<lt::BaseNode> DeclarationStructuredType::on_clone() const {
  return std::make_shared<DeclarationStructuredType>(
      lt::SourceRange(source_range), std::string(name), structured_type_kind,
      clone_node_vector(members), clone_node_vector(inherits));
}
}  // namespace forge
