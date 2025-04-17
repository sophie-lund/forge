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

#include <forgec/syntax_tree/statements/statement_if.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind StatementIf::NODE_KIND = NODE_STATEMENT_IF;

StatementIf::StatementIf(lt::SourceRange&& source_range,
                         std::shared_ptr<BaseValue>&& condition,
                         std::shared_ptr<StatementBlock>&& then,
                         std::shared_ptr<BaseStatement>&& else_)
    : BaseStatement(NODE_KIND, std::move(source_range)),
      condition(std::move(condition)),
      then(std::move(then)),
      else_(std::move(else_)) {}

void StatementIf::on_accept(lt::IVisitor& visitor) {
  visitor.visit(condition);
  visitor.visit(then);
  visitor.visit(else_);
}

void StatementIf::on_format_debug(lt::DebugFormatter& formatter) const {
  formatter.field_label("condition");
  formatter.node(condition);

  formatter.field_label("then");
  formatter.node(then);

  formatter.field_label("else");
  formatter.node(else_);
}

std::shared_ptr<lt::BaseNode> StatementIf::on_clone() const {
  return std::make_shared<StatementIf>(lt::SourceRange(source_range),
                                       clone_node(condition), clone_node(then),
                                       clone_node(else_));
}

bool StatementIf::on_compare(const lt::BaseNode& other) const {
  return compare_nodes(condition,
                       static_cast<const StatementIf&>(other).condition) &&
         compare_nodes(then, static_cast<const StatementIf&>(other).then) &&
         compare_nodes(else_, static_cast<const StatementIf&>(other).else_);
}
}  // namespace forge
