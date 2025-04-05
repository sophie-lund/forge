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

#include <forge/language/syntax_tree/statements/statement_basic.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
const NodeKind StatementBasic::NODE_KIND = NODE_STATEMENT_BASIC;

StatementBasic::StatementBasic(std::optional<SourceRange>&& source_range,
                               StatementBasicKind statement_basic_kind)
    : BaseStatement(NODE_KIND, std::move(source_range)),
      statement_basic_kind(statement_basic_kind) {}

void StatementBasic::on_accept(IVisitor&) {}

void StatementBasic::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("statement_basic_kind");

  switch (statement_basic_kind) {
    case StatementBasicKind::continue_:
      formatter.stream() << "continue";
      break;
    case StatementBasicKind::break_:
      formatter.stream() << "break";
      break;
    case StatementBasicKind::return_void:
      formatter.stream() << "return_void";
      break;
  }
}

std::shared_ptr<BaseNode> StatementBasic::on_clone() const {
  return std::make_shared<StatementBasic>(
      std::optional<SourceRange>(source_range), statement_basic_kind);
}

bool StatementBasic::on_compare(const BaseNode& other) const {
  return statement_basic_kind ==
         static_cast<const StatementBasic&>(other).statement_basic_kind;
}
}  // namespace forge
