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

#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
TypeBasic::TypeBasic(std::optional<SourceRange>&& source_range,
                     TypeBasicKind kind)
    : BaseType(NODE_TYPE_BASIC, std::move(source_range)), kind(kind) {}

void TypeBasic::on_accept(IVisitor&) {}

void TypeBasic::on_format_debug_type(DebugFormatter& formatter) const {
  formatter.field_label("kind");
  switch (kind) {
    case TypeBasicKind::bool_:
      formatter.stream() << "bool";
    case TypeBasicKind::never:
      formatter.stream() << "never";
    case TypeBasicKind::null:
      formatter.stream() << "null";
    case TypeBasicKind::void_:
      formatter.stream() << "void";
    case TypeBasicKind::isize:
      formatter.stream() << "isize";
    case TypeBasicKind::usize:
      formatter.stream() << "usize";
  }
}

std::shared_ptr<BaseNode> TypeBasic::on_clone_type() const {
  return std::make_shared<TypeBasic>(std::optional<SourceRange>(source_range),
                                     kind);
}

bool TypeBasic::on_compare_type(const BaseNode& other) const {
  return kind == static_cast<const TypeBasic&>(other).kind;
}
}  // namespace forge
