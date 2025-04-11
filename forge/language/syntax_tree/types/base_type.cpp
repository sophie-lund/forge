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

#include <forge/language/syntax_tree/types/base_type.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
BaseType::BaseType(NodeKind kind, SourceRange&& source_range)
    : BaseForgeNode(kind, std::move(source_range)),
      llvm_type(nullptr),
      is_const(false) {}

BaseType::~BaseType() {}

void BaseType::on_format_debug(DebugFormatter& formatter) const {
  on_format_debug_type(formatter);

  formatter.field_label("is_const");
  formatter.stream() << (is_const ? "true" : "false");
}

bool BaseType::on_compare(const BaseNode& other) const {
  return is_const == static_cast<const BaseType&>(other).is_const &&
         on_compare_type(other);
}

std::shared_ptr<BaseNode> BaseType::on_clone() const {
  std::shared_ptr<BaseNode> clone = on_clone_type();

  static_cast<BaseType&>(*clone).is_const = is_const;

  return clone;
}
}  // namespace forge
