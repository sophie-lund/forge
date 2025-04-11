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

#include <forge/language/syntax_tree/values/value_call.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind ValueCall::NODE_KIND = NODE_VALUE_CALL;

ValueCall::ValueCall(SourceRange&& source_range,
                     std::shared_ptr<BaseValue>&& callee,
                     std::vector<std::shared_ptr<BaseValue>>&& args)
    : BaseValue(NODE_KIND, std::move(source_range)),
      callee(std::move(callee)),
      args(std::move(args)) {}

void ValueCall::on_accept(IVisitor& visitor) {
  visitor.visit(callee);
  visitor.visit(args);
}

void ValueCall::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("callee");
  formatter.node(callee);

  formatter.field_label("args");
  formatter.node_vector(args);
}

std::shared_ptr<BaseNode> ValueCall::on_clone() const {
  return std::make_shared<ValueCall>(
      SourceRange(source_range), clone_node(callee), clone_node_vector(args));
}

bool ValueCall::on_compare(const BaseNode& other) const {
  return compare_nodes(callee, static_cast<const ValueCall&>(other).callee) &&
         compare_node_vectors(args, static_cast<const ValueCall&>(other).args);
}
}  // namespace forge
