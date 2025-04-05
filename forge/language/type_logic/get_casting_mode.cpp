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
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/type_logic/get_casting_mode.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
CastingMode get_casting_mode(const std::shared_ptr<BaseType>& from,
                             const std::shared_ptr<BaseType>& to) {
  FRG_ASSERT(from != nullptr, "from type must not be null");
  FRG_ASSERT(to != nullptr, "to type must not be null");

  // If the types are identical, no casting is needed
  if (compare_nodes(from, to)) {
    return CastingMode::implicit;
  }

  // If both the types are numeric
  if (from->kind == NODE_TYPE_WITH_BIT_WIDTH &&
      to->kind == NODE_TYPE_WITH_BIT_WIDTH) {
    const TypeWithBitWidth& from_casted =
        static_cast<const TypeWithBitWidth&>(*from);
    const TypeWithBitWidth& to_casted =
        static_cast<const TypeWithBitWidth&>(*to);

    // If both types are floats
    if (from_casted.type_with_bit_width_kind == TypeWithBitWidthKind::float_ &&
        to_casted.type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
      // If the bit width is not reduced, we can cast implicitly
      if (from_casted.bit_width <= to_casted.bit_width) {
        return CastingMode::implicit;
      }
    }

    // If both types are integers of the same signedness
    if ((from_casted.type_with_bit_width_kind ==
             TypeWithBitWidthKind::signed_int &&
         to_casted.type_with_bit_width_kind ==
             TypeWithBitWidthKind::signed_int) ||
        (from_casted.type_with_bit_width_kind ==
             TypeWithBitWidthKind::unsigned_int &&
         to_casted.type_with_bit_width_kind ==
             TypeWithBitWidthKind::unsigned_int)) {
      // If the bit width is not reduced, we can cast implicitly
      if (from_casted.bit_width <= to_casted.bit_width) {
        return CastingMode::implicit;
      }
    }

    // If we are casting from unsigned to signed
    if (from_casted.type_with_bit_width_kind ==
            TypeWithBitWidthKind::unsigned_int &&
        to_casted.type_with_bit_width_kind ==
            TypeWithBitWidthKind::signed_int) {
      // If the number of non-sign bits is not reduced, we can cast implicitly
      //
      // Note that this condition uses '<' instead of '<='
      if (from_casted.bit_width < to_casted.bit_width) {
        return CastingMode::implicit;
      }
    }

    // All numeric casts can be done explicitly
    return CastingMode::explicit_;
  }

  // Default to the cast being illegal
  return CastingMode::illegal;
}
}  // namespace forge
