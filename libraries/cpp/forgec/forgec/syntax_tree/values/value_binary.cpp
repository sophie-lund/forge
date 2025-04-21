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

#include <forgec/syntax_tree/values/value_binary.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
bool is_binary_operator_comparison(BinaryOperator operator_) {
  return operator_ == BinaryOperator::eq || operator_ == BinaryOperator::ne ||
         operator_ == BinaryOperator::lt || operator_ == BinaryOperator::le ||
         operator_ == BinaryOperator::gt || operator_ == BinaryOperator::ge;
}

std::optional<BinaryOperator> try_get_compound_assignment_base_operator(
    BinaryOperator operator_) {
  switch (operator_) {
    case BinaryOperator::bit_and_assign:
      return BinaryOperator::bit_and;
    case BinaryOperator::bit_or_assign:
      return BinaryOperator::bit_or;
    case BinaryOperator::bit_xor_assign:
      return BinaryOperator::bit_xor;
    case BinaryOperator::bit_shl_assign:
      return BinaryOperator::bit_shl;
    case BinaryOperator::bit_shr_assign:
      return BinaryOperator::bit_shr;
    case BinaryOperator::add_assign:
      return BinaryOperator::add;
    case BinaryOperator::sub_assign:
      return BinaryOperator::sub;
    case BinaryOperator::mul_assign:
      return BinaryOperator::mul;
    case BinaryOperator::exp_assign:
      return BinaryOperator::exp;
    case BinaryOperator::div_assign:
      return BinaryOperator::div;
    case BinaryOperator::mod_assign:
      return BinaryOperator::mod;
    default:
      return std::nullopt;
  }
}

const lt::NodeKind ValueBinary::NODE_KIND = NODE_VALUE_BINARY;

ValueBinary::ValueBinary(lt::SourceRange&& source_range,
                         BinaryOperator operator_,
                         std::shared_ptr<BaseValue>&& lhs,
                         std::shared_ptr<BaseValue>&& rhs)
    : BaseValue(NODE_KIND, std::move(source_range)),
      operator_(operator_),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {}

void ValueBinary::on_accept(lt::IVisitor& visitor) {
  visitor.visit(lhs);
  visitor.visit(rhs);
}

void ValueBinary::on_format_debug(lt::DebugFormatter& formatter) const {
  formatter.field_label("operator");

  switch (operator_) {
    case BinaryOperator::bool_and:
      formatter.stream() << "&&";
      break;
    case BinaryOperator::bool_or:
      formatter.stream() << "||";
      break;
    case BinaryOperator::bit_and:
      formatter.stream() << "&";
      break;
    case BinaryOperator::bit_and_assign:
      formatter.stream() << "&=";
      break;
    case BinaryOperator::bit_or:
      formatter.stream() << "|";
      break;
    case BinaryOperator::bit_or_assign:
      formatter.stream() << "|=";
      break;
    case BinaryOperator::bit_xor:
      formatter.stream() << "^";
      break;
    case BinaryOperator::bit_xor_assign:
      formatter.stream() << "^=";
      break;
    case BinaryOperator::bit_shl:
      formatter.stream() << "<<";
      break;
    case BinaryOperator::bit_shl_assign:
      formatter.stream() << "<<=";
      break;
    case BinaryOperator::bit_shr:
      formatter.stream() << ">>";
      break;
    case BinaryOperator::bit_shr_assign:
      formatter.stream() << ">>=";
      break;
    case BinaryOperator::add:
      formatter.stream() << "+";
      break;
    case BinaryOperator::add_assign:
      formatter.stream() << "+=";
      break;
    case BinaryOperator::sub:
      formatter.stream() << "-";
      break;
    case BinaryOperator::sub_assign:
      formatter.stream() << "-=";
      break;
    case BinaryOperator::mul:
      formatter.stream() << "*";
      break;
    case BinaryOperator::mul_assign:
      formatter.stream() << "*=";
      break;
    case BinaryOperator::exp:
      formatter.stream() << "**";
      break;
    case BinaryOperator::exp_assign:
      formatter.stream() << "**=";
      break;
    case BinaryOperator::div:
      formatter.stream() << "/";
      break;
    case BinaryOperator::div_assign:
      formatter.stream() << "/=";
      break;
    case BinaryOperator::mod:
      formatter.stream() << "%";
      break;
    case BinaryOperator::mod_assign:
      formatter.stream() << "%=";
      break;
    case BinaryOperator::assign:
      formatter.stream() << "=";
      break;
    case BinaryOperator::eq:
      formatter.stream() << "==";
      break;
    case BinaryOperator::ne:
      formatter.stream() << "!=";
      break;
    case BinaryOperator::lt:
      formatter.stream() << "<";
      break;
    case BinaryOperator::le:
      formatter.stream() << "<=";
      break;
    case BinaryOperator::gt:
      formatter.stream() << ">";
      break;
    case BinaryOperator::ge:
      formatter.stream() << ">=";
      break;
    case BinaryOperator::member_access:
      formatter.stream() << ".";
      break;
  }

  formatter.field_label("lhs");
  formatter.node(lhs);

  formatter.field_label("rhs");
  formatter.node(rhs);
}

std::shared_ptr<lt::BaseNode> ValueBinary::on_clone() const {
  return std::make_shared<ValueBinary>(lt::SourceRange(source_range), operator_,
                                       clone_node(lhs), clone_node(rhs));
}

bool ValueBinary::on_compare(const lt::BaseNode& other) const {
  return operator_ == static_cast<const ValueBinary&>(other).operator_ &&
         compare_nodes(lhs, static_cast<const ValueBinary&>(other).lhs) &&
         compare_nodes(rhs, static_cast<const ValueBinary&>(other).rhs);
}
}  // namespace forge
