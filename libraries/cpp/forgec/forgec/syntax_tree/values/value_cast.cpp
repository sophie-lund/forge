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

#include <forgec/syntax_tree/values/value_cast.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <langtools/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const lt::NodeKind ValueCast::NODE_KIND = NODE_VALUE_CAST;

ValueCast::ValueCast(lt::SourceRange&& source_range,
                     std::shared_ptr<BaseValue>&& value,
                     std::shared_ptr<BaseType>&& type)
    : BaseValue(NODE_KIND, std::move(source_range)),
      value(std::move(value)),
      type(std::move(type)) {}

void ValueCast::on_accept(lt::IVisitor& visitor) {
  visitor.visit(value);
  visitor.visit(type);
}

void ValueCast::on_format_debug(lt::DebugFormatter& formatter) const {
  formatter.field_label("value");
  formatter.node(value);

  formatter.field_label("type");
  formatter.node(type);
}

std::shared_ptr<lt::BaseNode> ValueCast::on_clone() const {
  return std::make_shared<ValueCast>(lt::SourceRange(source_range),
                                     clone_node(value), clone_node(type));
}

bool ValueCast::on_compare(const lt::BaseNode& other) const {
  return compare_nodes(value, static_cast<const ValueCast&>(other).value) &&
         compare_nodes(type, static_cast<const ValueCast&>(other).type);
}
}  // namespace forge
