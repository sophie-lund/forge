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

#include <forge/language/syntax_tree/types/type_structured.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind TypeStructured::NODE_KIND = NODE_TYPE_STRUCTURED;

TypeStructured::TypeStructured(
    std::optional<SourceRange>&& source_range,
    std::vector<std::shared_ptr<DeclarationVariable>>&& members)
    : BaseType(NODE_KIND, std::move(source_range)),
      members(std::move(members)) {}

void TypeStructured::on_accept(IVisitor& visitor) { visitor.visit(members); }

void TypeStructured::on_format_debug_type(DebugFormatter& formatter) const {
  formatter.field_label("members");
  formatter.node_vector(members);
}

bool TypeStructured::on_compare_type(const BaseNode& other) const {
  return compare_node_vectors(
      members, static_cast<const TypeStructured&>(other).members);
}

std::shared_ptr<BaseNode> TypeStructured::on_clone_type() const {
  return std::make_shared<TypeStructured>(
      std::optional<SourceRange>(source_range), clone_node_vector(members));
}
}  // namespace forge
