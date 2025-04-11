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
const NodeKind TypeBasic::NODE_KIND = NODE_TYPE_BASIC;

TypeBasic::TypeBasic(SourceRange&& source_range, TypeBasicKind type_basic_kind)
    : BaseType(NODE_KIND, std::move(source_range)),
      type_basic_kind(type_basic_kind) {}

void TypeBasic::on_accept(IVisitor&) {}

void TypeBasic::on_format_debug_type(DebugFormatter& formatter) const {
  formatter.field_label("type_basic_kind");
  switch (type_basic_kind) {
    case TypeBasicKind::bool_:
      formatter.stream() << "bool";
      break;
    case TypeBasicKind::void_:
      formatter.stream() << "void";
      break;
    case TypeBasicKind::isize:
      formatter.stream() << "isize";
      break;
    case TypeBasicKind::usize:
      formatter.stream() << "usize";
      break;
  }
}

std::shared_ptr<BaseNode> TypeBasic::on_clone_type() const {
  return std::make_shared<TypeBasic>(SourceRange(source_range),
                                     type_basic_kind);
}

bool TypeBasic::on_compare_type(const BaseNode& other) const {
  return type_basic_kind ==
         static_cast<const TypeBasic&>(other).type_basic_kind;
}
}  // namespace forge
