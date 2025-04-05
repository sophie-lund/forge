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

#include <forge/language/syntax_tree/statements/statement_block.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind StatementBlock::NODE_KIND = NODE_STATEMENT_BLOCK;

StatementBlock::StatementBlock(
    std::optional<SourceRange>&& source_range,
    std::vector<std::shared_ptr<BaseStatement>>&& statements)
    : BaseStatement(NODE_KIND, std::move(source_range)),
      statements(std::move(statements)) {}

void StatementBlock::on_accept(IVisitor& visitor) { visitor.visit(statements); }

void StatementBlock::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("statements");
  formatter.node_vector(statements);
}

std::shared_ptr<BaseNode> StatementBlock::on_clone() const {
  return std::make_shared<StatementBlock>(
      std::optional<SourceRange>(source_range), clone_node_vector(statements));
}

bool StatementBlock::on_compare(const BaseNode& other) const {
  return compare_node_vectors(
      statements, static_cast<const StatementBlock&>(other).statements);
}

ScopeFlags StatementBlock::on_get_scope_flags() const {
  return SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE;
}

const Scope* StatementBlock::on_try_get_scope() const { return &_scope; }
}  // namespace forge
