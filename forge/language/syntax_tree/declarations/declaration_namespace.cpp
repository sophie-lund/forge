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

#include <forge/language/syntax_tree/declarations/declaration_namespace.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
DeclarationNamespace::DeclarationNamespace(
    std::optional<SourceRange>&& source_range, std::string&& name,
    std::vector<std::shared_ptr<BaseDeclaration>>&& members)
    : BaseDeclaration(NODE_DECLARATION_NAMESPACE, std::move(source_range),
                      std::move(name)),
      members(std::move(members)) {}

void DeclarationNamespace::on_accept(IVisitor& visitor) {
  visitor.visit(members);
}

void DeclarationNamespace::on_format_debug_declaration(
    DebugFormatter& formatter) const {
  formatter.field_label("members");
  formatter.node_vector(members);
}

bool DeclarationNamespace::on_compare_declaration(const BaseNode& other) const {
  return compare_node_vectors(
      members, static_cast<const DeclarationNamespace&>(other).members);
}
}  // namespace forge
