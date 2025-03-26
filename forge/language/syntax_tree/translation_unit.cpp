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

#include <forge/language/syntax_tree/translation_unit.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
TranslationUnit::TranslationUnit(
    std::optional<SourceRange>&& source_range,
    std::vector<std::shared_ptr<BaseDeclaration>>&& members)
    : BaseForgeNode(NODE_TRANSLATION_UNIT, std::move(source_range)),
      members(std::move(members)) {}

void TranslationUnit::on_accept(IVisitor& visitor) { visitor.visit(members); }

void TranslationUnit::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("members");
  formatter.node_vector(members);
}

bool TranslationUnit::on_compare(const BaseNode& other) const {
  return compare_node_vectors(
      members, static_cast<const TranslationUnit&>(other).members);
}
}  // namespace forge
