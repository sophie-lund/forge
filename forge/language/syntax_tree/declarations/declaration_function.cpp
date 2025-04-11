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

#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind DeclarationFunction::NODE_KIND = NODE_DECLARATION_FUNCTION;

DeclarationFunction::DeclarationFunction(
    SourceRange&& source_range, std::string&& name,
    std::vector<std::shared_ptr<DeclarationVariable>>&& args,
    std::shared_ptr<BaseType>&& return_type,
    std::shared_ptr<StatementBlock>&& body)
    : BaseDeclaration(NODE_KIND, std::move(source_range), std::move(name)),
      args(std::move(args)),
      return_type(std::move(return_type)),
      body(std::move(body)),
      llvm_function(nullptr) {}

void DeclarationFunction::on_accept(IVisitor& visitor) {
  visitor.visit(args);
  visitor.visit(return_type);
  visitor.visit(body);
}

void DeclarationFunction::on_format_debug_declaration(
    DebugFormatter& formatter) const {
  formatter.field_label("args");
  formatter.node_vector(args);

  formatter.field_label("return_type");
  formatter.node(return_type);

  formatter.field_label("body");
  formatter.node(body);
}

bool DeclarationFunction::on_compare_declaration(const BaseNode& other) const {
  return compare_node_vectors(
             args, static_cast<const DeclarationFunction&>(other).args) &&
         compare_nodes(
             return_type,
             static_cast<const DeclarationFunction&>(other).return_type) &&
         compare_nodes(body,
                       static_cast<const DeclarationFunction&>(other).body);
}

std::shared_ptr<BaseNode> DeclarationFunction::on_clone() const {
  return std::make_shared<DeclarationFunction>(
      SourceRange(source_range), std::string(name), clone_node_vector(args),
      clone_node(return_type), clone_node(body));
}
}  // namespace forge
