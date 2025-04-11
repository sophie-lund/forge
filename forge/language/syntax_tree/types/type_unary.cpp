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

#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind TypeUnary::NODE_KIND = NODE_TYPE_UNARY;

TypeUnary::TypeUnary(SourceRange&& source_range, TypeUnaryKind type_unary_kind,
                     std::shared_ptr<BaseType>&& operand_type)
    : BaseType(NODE_KIND, std::move(source_range)),
      type_unary_kind(type_unary_kind),
      operand_type(std::move(operand_type)) {}

void TypeUnary::on_accept(IVisitor& visitor) { visitor.visit(operand_type); }

void TypeUnary::on_format_debug_type(DebugFormatter& formatter) const {
  formatter.field_label("type_unary_kind");
  switch (type_unary_kind) {
    case TypeUnaryKind::pointer:
      formatter.stream() << "pointer";
      break;
  }

  formatter.field_label("operand_type");
  formatter.node(operand_type);
}

std::shared_ptr<BaseNode> TypeUnary::on_clone_type() const {
  return std::make_shared<TypeUnary>(SourceRange(source_range), type_unary_kind,
                                     clone_node(operand_type));
}

bool TypeUnary::on_compare_type(const BaseNode& other) const {
  return type_unary_kind ==
             static_cast<const TypeUnary&>(other).type_unary_kind &&
         compare_nodes(operand_type,
                       static_cast<const TypeUnary&>(other).operand_type);
}
}  // namespace forge
