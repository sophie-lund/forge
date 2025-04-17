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

#include <forgec/syntax_tree/translation_unit.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind TranslationUnit::NODE_KIND = NODE_TRANSLATION_UNIT;

TranslationUnit::TranslationUnit(
    lt::SourceRange&& source_range,
    std::vector<std::shared_ptr<BaseDeclaration>>&& declarations)
    : BaseForgeNode(NODE_KIND, std::move(source_range)),
      declarations(std::move(declarations)) {}

void TranslationUnit::on_accept(lt::IVisitor& visitor) {
  visitor.visit(declarations);
}

void TranslationUnit::on_format_debug(lt::DebugFormatter& formatter) const {
  formatter.field_label("declarations");
  formatter.node_vector(declarations);
}

bool TranslationUnit::on_compare(const lt::BaseNode& other) const {
  return compare_node_vectors(
      declarations, static_cast<const TranslationUnit&>(other).declarations);
}

std::shared_ptr<lt::BaseNode> TranslationUnit::on_clone() const {
  return std::make_shared<TranslationUnit>(lt::SourceRange(source_range),
                                           clone_node_vector(declarations));
}

lt::ScopeFlags TranslationUnit::on_get_scope_flags() const {
  return lt::SCOPE_FLAG_UNORDERED;
}

const lt::Scope* TranslationUnit::on_try_get_scope() const { return &_scope; }
}  // namespace forge
