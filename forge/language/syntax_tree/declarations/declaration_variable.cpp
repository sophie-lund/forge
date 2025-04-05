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

#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind DeclarationVariable::NODE_KIND = NODE_DECLARATION_VARIABLE;

DeclarationVariable::DeclarationVariable(
    std::optional<SourceRange>&& source_range, std::string&& name,
    std::shared_ptr<BaseType>&& type,
    std::shared_ptr<BaseValue>&& initial_value)
    : BaseDeclaration(NODE_KIND, std::move(source_range), std::move(name)),
      type(std::move(type)),
      initial_value(std::move(initial_value)),
      is_const(false),
      llvm_value(nullptr) {}

void DeclarationVariable::on_accept(IVisitor& visitor) {
  visitor.visit(type);
  visitor.visit(initial_value);
}

void DeclarationVariable::on_format_debug_declaration(
    DebugFormatter& formatter) const {
  formatter.field_label("type");
  formatter.node(type);

  formatter.field_label("initial_value");
  formatter.node(initial_value);

  formatter.field_label("is_const");
  formatter.stream() << (is_const ? "true" : "false");
}

bool DeclarationVariable::on_compare_declaration(const BaseNode& other) const {
  return compare_nodes(type,
                       static_cast<const DeclarationVariable&>(other).type) &&
         compare_nodes(
             initial_value,
             static_cast<const DeclarationVariable&>(other).initial_value) &&
         is_const == static_cast<const DeclarationVariable&>(other).is_const;
}

std::shared_ptr<BaseNode> DeclarationVariable::on_clone() const {
  return std::make_shared<DeclarationVariable>(
      std::optional<SourceRange>(source_range), std::string(name),
      clone_node(type), clone_node(initial_value));
}
}  // namespace forge
