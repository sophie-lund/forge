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
#include <forge/language/type_logic/get_arithmetic_containing_type.hpp>
#include <forge/syntax_tree/operations/casting.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
std::shared_ptr<BaseType> get_arithmetic_containing_type(
    const std::shared_ptr<BaseType> &a, const std::shared_ptr<BaseType> &b) {
  FRG_ASSERT(a != nullptr,
             "cannot get arithmetic containing type with null type nodes");
  FRG_ASSERT(b != nullptr,
             "cannot get arithmetic containing type with null type nodes");

  if (compare_nodes(a, b)) {
    return clone_node(a);
  } else if (auto a_casted = try_cast_node<TypeWithBitWidth>(a),
             b_casted = try_cast_node<TypeWithBitWidth>(b);
             a_casted && b_casted) {
    TypeWithBitWidthKind type_with_bit_width_kind =
        TypeWithBitWidthKind::unsigned_int;

    if (a_casted->type_with_bit_width_kind == TypeWithBitWidthKind::float_ ||
        b_casted->type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
      type_with_bit_width_kind = TypeWithBitWidthKind::float_;
    } else if (a_casted->type_with_bit_width_kind ==
                   TypeWithBitWidthKind::signed_int ||
               b_casted->type_with_bit_width_kind ==
                   TypeWithBitWidthKind::signed_int) {
      type_with_bit_width_kind = TypeWithBitWidthKind::signed_int;
    }

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), type_with_bit_width_kind,
        a_casted->bit_width > b_casted->bit_width ? a_casted->bit_width
                                                  : b_casted->bit_width);
  } else {
    return nullptr;
  }
}
}  // namespace forge
