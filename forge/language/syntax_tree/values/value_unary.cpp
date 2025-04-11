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

#include <forge/language/syntax_tree/values/value_unary.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind ValueUnary::NODE_KIND = NODE_VALUE_UNARY;

ValueUnary::ValueUnary(SourceRange&& source_range, UnaryOperator operator_,
                       std::shared_ptr<BaseValue>&& operand)
    : BaseValue(NODE_KIND, std::move(source_range)),
      operator_(operator_),
      operand(std::move(operand)) {}

void ValueUnary::on_accept(IVisitor& visitor) { visitor.visit(operand); }

void ValueUnary::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("operator");

  switch (operator_) {
    case UnaryOperator::bool_not:
      formatter.stream() << "!";
      break;
    case UnaryOperator::bit_not:
      formatter.stream() << "~";
      break;
    case UnaryOperator::pos:
      formatter.stream() << "+";
      break;
    case UnaryOperator::neg:
      formatter.stream() << "-";
      break;
    case UnaryOperator::deref:
      formatter.stream() << "*";
      break;
    case UnaryOperator::getaddr:
      formatter.stream() << "&";
      break;
  }

  formatter.field_label("operand");
  formatter.node(operand);
}

std::shared_ptr<BaseNode> ValueUnary::on_clone() const {
  return std::make_shared<ValueUnary>(SourceRange(source_range), operator_,
                                      clone_node(operand));
}

bool ValueUnary::on_compare(const BaseNode& other) const {
  return operator_ == static_cast<const ValueUnary&>(other).operator_ &&
         compare_nodes(operand, static_cast<const ValueUnary&>(other).operand);
}
}  // namespace forge
