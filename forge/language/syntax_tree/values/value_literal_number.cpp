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

#include <forge/core/assert.hpp>
#include <forge/language/syntax_tree/values/value_literal_number.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/visitors/ivisitor.hpp>

namespace forge {
const NodeKind ValueLiteralNumber::NODE_KIND = NODE_VALUE_LITERAL_NUMBER;

ValueLiteralNumber::ValueLiteralNumber(
    std::optional<SourceRange>&& source_range,
    std::shared_ptr<TypeWithBitWidth>&& type, ValueLiteralNumberUnion value)
    : BaseValue(NODE_KIND, std::move(source_range)),
      type(std::move(type)),
      value(value) {}

void ValueLiteralNumber::on_accept(IVisitor& visitor) { visitor.visit(type); }

void ValueLiteralNumber::on_format_debug(DebugFormatter& formatter) const {
  formatter.field_label("type");
  formatter.node(type);

  formatter.field_label("value");

  if (type) {
    if (type->type_with_bit_width_kind == TypeWithBitWidthKind::signed_int) {
      if (type->bit_width == 8) {
        formatter.stream() << value.i8;
      } else if (type->bit_width == 16) {
        formatter.stream() << value.i16;
      } else if (type->bit_width == 32) {
        formatter.stream() << value.i32;
      } else if (type->bit_width == 64) {
        formatter.stream() << value.i64;
      } else {
        FRG_ABORT("unsupported bit width: " << type->bit_width);
      }
    } else if (type->type_with_bit_width_kind ==
               TypeWithBitWidthKind::unsigned_int) {
      if (type->bit_width == 8) {
        formatter.stream() << value.u8;
      } else if (type->bit_width == 16) {
        formatter.stream() << value.u16;
      } else if (type->bit_width == 32) {
        formatter.stream() << value.u32;
      } else if (type->bit_width == 64) {
        formatter.stream() << value.u64;
      } else {
        FRG_ABORT("unsupported bit width: " << type->bit_width);
      }
    } else if (type->type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
      if (type->bit_width == 32) {
        formatter.stream() << value.f32;
      } else if (type->bit_width == 64) {
        formatter.stream() << value.f64;
      } else {
        FRG_ABORT("unsupported bit width: " << type->bit_width);
      }
    } else {
      FRG_ABORT("unsupported kind");
    }
  } else {
    formatter.stream() << "???";
  }
}

std::shared_ptr<BaseNode> ValueLiteralNumber::on_clone() const {
  return std::make_shared<ValueLiteralNumber>(
      std::optional<SourceRange>(source_range), clone_node(type), value);
}

bool ValueLiteralNumber::on_compare(const BaseNode& other) const {
  return compare_nodes(type,
                       static_cast<const ValueLiteralNumber&>(other).type) &&
         memcmp(&value, &static_cast<const ValueLiteralNumber&>(other).value,
                sizeof(value)) == 0;
}
}  // namespace forge
