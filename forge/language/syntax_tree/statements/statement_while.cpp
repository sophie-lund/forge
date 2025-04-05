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

#include <forge/language/syntax_tree/statements/statement_while.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind StatementWhile::NODE_KIND = NODE_STATEMENT_WHILE;

StatementWhile::StatementWhile(std::optional<SourceRange>&& source_range,
                               std::shared_ptr<BaseValue>&& condition,
                               std::shared_ptr<StatementBlock>&& body)
    : BaseStatement(NODE_KIND, std::move(source_range)),
      condition(std::move(condition)),
      body(std::move(body)) {}

void StatementWhile::on_accept(IVisitor& visitor) {
  visitor.visit(condition);
  visitor.visit(body);
}

void StatementWhile::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("condition");
  formatter.node(condition);

  formatter.field_label("body");
  formatter.node(body);

  formatter.field_label("is_do_while");
  formatter.stream() << (is_do_while ? "true" : "false");
}

std::shared_ptr<BaseNode> StatementWhile::on_clone() const {
  auto clone =
      std::make_shared<StatementWhile>(std::optional<SourceRange>(source_range),
                                       clone_node(condition), clone_node(body));

  clone->is_do_while = is_do_while;

  return clone;
}

bool StatementWhile::on_compare(const BaseNode& other) const {
  return compare_nodes(condition,
                       static_cast<const StatementWhile&>(other).condition) &&
         compare_nodes(body, static_cast<const StatementWhile&>(other).body) &&
         is_do_while == static_cast<const StatementWhile&>(other).is_do_while;
}
}  // namespace forge
