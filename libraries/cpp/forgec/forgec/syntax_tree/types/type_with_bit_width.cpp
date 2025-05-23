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

#include <forgec/syntax_tree/types/type_with_bit_width.hpp>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
const lt::NodeKind TypeWithBitWidth::NODE_KIND = NODE_TYPE_WITH_BIT_WIDTH;

TypeWithBitWidth::TypeWithBitWidth(
    lt::SourceRange&& source_range,
    TypeWithBitWidthKind type_with_bit_width_kind, uint32_t bit_width)
    : BaseType(NODE_KIND, std::move(source_range)),
      type_with_bit_width_kind(type_with_bit_width_kind),
      bit_width(bit_width) {}

void TypeWithBitWidth::on_accept(lt::IVisitor&) {}

void TypeWithBitWidth::on_format_debug_type(
    lt::DebugFormatter& formatter) const {
  formatter.field_label("type_with_bit_width_kind");
  switch (type_with_bit_width_kind) {
    case TypeWithBitWidthKind::signed_int:
      formatter.stream() << "signed_int";
      break;
    case TypeWithBitWidthKind::unsigned_int:
      formatter.stream() << "unsigned_int";
      break;
    case TypeWithBitWidthKind::float_:
      formatter.stream() << "float";
      break;
  }

  formatter.field_label("bit_width");
  formatter.stream() << bit_width;
}

std::shared_ptr<lt::BaseNode> TypeWithBitWidth::on_clone_type() const {
  return std::make_shared<TypeWithBitWidth>(
      lt::SourceRange(source_range), type_with_bit_width_kind, bit_width);
}

bool TypeWithBitWidth::on_compare_type(const lt::BaseNode& other) const {
  return type_with_bit_width_kind == static_cast<const TypeWithBitWidth&>(other)
                                         .type_with_bit_width_kind &&
         bit_width == static_cast<const TypeWithBitWidth&>(other).bit_width;
}
}  // namespace forge
