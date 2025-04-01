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

#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/type_logic/get_arithmetic_containing_type.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
std::shared_ptr<BaseType> get_arithmetic_containing_type(
    std::shared_ptr<BaseType> a, std::shared_ptr<BaseType> b) {
  assert(a != nullptr);
  assert(b != nullptr);

  if (compare_nodes(a, b)) {
    return clone_node(a);
  } else if (a->kind == NODE_TYPE_WITH_BIT_WIDTH &&
             b->kind == NODE_TYPE_WITH_BIT_WIDTH) {
    const TypeWithBitWidth& a_casted = static_cast<const TypeWithBitWidth&>(*a);
    const TypeWithBitWidth& b_casted = static_cast<const TypeWithBitWidth&>(*b);

    TypeWithBitWidthKind type_with_bit_width_kind =
        TypeWithBitWidthKind::unsigned_int;

    if (a_casted.type_with_bit_width_kind == TypeWithBitWidthKind::float_ ||
        b_casted.type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
      type_with_bit_width_kind = TypeWithBitWidthKind::float_;
    } else if (a_casted.type_with_bit_width_kind ==
                   TypeWithBitWidthKind::signed_int ||
               b_casted.type_with_bit_width_kind ==
                   TypeWithBitWidthKind::signed_int) {
      type_with_bit_width_kind = TypeWithBitWidthKind::signed_int;
    }

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), type_with_bit_width_kind,
        a_casted.bit_width > b_casted.bit_width ? a_casted.bit_width
                                                : b_casted.bit_width);
  } else {
    return nullptr;
  }
}
}  // namespace forge
