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

#include <forgec/syntax_tree/statements/statement_declaration.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind StatementDeclaration::NODE_KIND = NODE_STATEMENT_DECLARATION;

StatementDeclaration::StatementDeclaration(
    lt::SourceRange&& source_range,
    std::shared_ptr<BaseDeclaration>&& declaration)
    : BaseStatement(NODE_KIND, std::move(source_range)),
      declaration(std::move(declaration)) {}

void StatementDeclaration::on_accept(lt::IVisitor& visitor) {
  visitor.visit(declaration);
}

void StatementDeclaration::on_format_debug(
    lt::DebugFormatter& formatter) const {
  formatter.field_label("declaration");
  formatter.node(declaration);
}

std::shared_ptr<lt::BaseNode> StatementDeclaration::on_clone() const {
  return std::make_shared<StatementDeclaration>(lt::SourceRange(source_range),
                                                clone_node(declaration));
}

bool StatementDeclaration::on_compare(const lt::BaseNode& other) const {
  return compare_nodes(
      declaration, static_cast<const StatementDeclaration&>(other).declaration);
}
}  // namespace forge
