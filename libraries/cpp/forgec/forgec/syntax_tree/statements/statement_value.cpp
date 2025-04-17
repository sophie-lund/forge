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

#include <forgec/syntax_tree/statements/statement_value.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind StatementValue::NODE_KIND = NODE_STATEMENT_VALUE;

StatementValue::StatementValue(lt::SourceRange&& source_range,
                               StatementValueKind statement_value_kind,
                               std::shared_ptr<BaseValue>&& value)
    : BaseStatement(NODE_KIND, std::move(source_range)),
      statement_value_kind(statement_value_kind),
      value(std::move(value)) {}

void StatementValue::on_accept(lt::IVisitor& visitor) { visitor.visit(value); }

void StatementValue::on_format_debug(lt::DebugFormatter& formatter) const {
  formatter.field_label("statement_value_kind");

  switch (statement_value_kind) {
    case StatementValueKind::execute:
      formatter.stream() << "execute";
      break;
    case StatementValueKind::return_:
      formatter.stream() << "return";
      break;
  }

  formatter.field_label("value");
  formatter.node(value);
}

std::shared_ptr<lt::BaseNode> StatementValue::on_clone() const {
  return std::make_shared<StatementValue>(
      lt::SourceRange(source_range), statement_value_kind, clone_node(value));
}

bool StatementValue::on_compare(const lt::BaseNode& other) const {
  return statement_value_kind ==
             static_cast<const StatementValue&>(other).statement_value_kind &&
         compare_nodes(value, static_cast<const StatementValue&>(other).value);
}
}  // namespace forge
