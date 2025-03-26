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

#include <forge/language/syntax_tree/types/type_function.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
TypeFunction::TypeFunction(std::optional<SourceRange>&& source_range,
                           std::shared_ptr<BaseType>&& return_type,
                           std::vector<std::shared_ptr<BaseType>>&& arg_types)
    : BaseType(NODE_TYPE_FUNCTION, std::move(source_range)),
      return_type(std::move(return_type)),
      arg_types(std::move(arg_types)) {}

void TypeFunction::on_accept(IVisitor& visitor) {
  visitor.visit(return_type);
  visitor.visit(arg_types);
}

void TypeFunction::on_format_debug_type(DebugFormatter& formatter) const {
  formatter.field_label("return_type");
  formatter.node(return_type);

  formatter.field_label("arg_types");
  formatter.node_vector(arg_types);
}

std::shared_ptr<BaseNode> TypeFunction::on_clone_type() const {
  return std::make_shared<TypeFunction>(
      std::optional<SourceRange>(source_range), clone_node(return_type),
      clone_node_vector(arg_types));
}

bool TypeFunction::on_compare_type(const BaseNode& other) const {
  return compare_nodes(return_type,
                       static_cast<const TypeFunction&>(other).return_type) &&
         compare_node_vectors(
             arg_types, static_cast<const TypeFunction&>(other).arg_types);
}
}  // namespace forge
