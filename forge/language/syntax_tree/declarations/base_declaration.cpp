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

#include <forge/language/syntax_tree/declarations/base_declaration.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
BaseDeclaration::BaseDeclaration(NodeKind kind, SourceRange&& source_range,
                                 std::string&& name)
    : BaseForgeNode(kind, std::move(source_range)), name(std::move(name)) {}

BaseDeclaration::~BaseDeclaration() {}

void BaseDeclaration::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("name");
  formatter.string(name);

  on_format_debug_declaration(formatter);
}

bool BaseDeclaration::on_compare(const BaseNode& other) const {
  return name == static_cast<const BaseDeclaration&>(other).name &&
         on_compare_declaration(static_cast<const BaseDeclaration&>(other));
}

std::optional<std::string> BaseDeclaration::on_get_declared_symbol_name()
    const {
  return name;
}

const Scope* BaseDeclaration::on_try_get_scope() const { return &_scope; }
}  // namespace forge
