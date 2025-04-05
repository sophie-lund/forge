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
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/type_logic/type_predicates.hpp>

namespace forge {
bool is_type_void(const BaseType& type) {
  return type.kind == NODE_TYPE_BASIC &&
         static_cast<const TypeBasic&>(type).type_basic_kind ==
             TypeBasicKind::void_;
}

bool is_type_bool(const BaseType& type) {
  return type.kind == NODE_TYPE_BASIC &&
         static_cast<const TypeBasic&>(type).type_basic_kind ==
             TypeBasicKind::bool_;
}

bool is_type_integer(const BaseType& type) {
  if (type.kind == NODE_TYPE_BASIC) {
    return static_cast<const TypeBasic&>(type).type_basic_kind ==
               TypeBasicKind::isize ||
           static_cast<const TypeBasic&>(type).type_basic_kind ==
               TypeBasicKind::usize;
  } else if (type.kind == NODE_TYPE_WITH_BIT_WIDTH) {
    return static_cast<const TypeWithBitWidth&>(type)
                   .type_with_bit_width_kind ==
               TypeWithBitWidthKind::signed_int ||
           static_cast<const TypeWithBitWidth&>(type)
                   .type_with_bit_width_kind ==
               TypeWithBitWidthKind::unsigned_int;
  } else {
    return false;
  }
}

std::optional<bool> is_integer_type_signed(const BaseType& type) {
  if (type.kind == NODE_TYPE_BASIC) {
    if (static_cast<const TypeBasic&>(type).type_basic_kind ==
        TypeBasicKind::isize) {
      return true;
    } else if (static_cast<const TypeBasic&>(type).type_basic_kind ==
               TypeBasicKind::usize) {
      return false;
    } else {
      return std::nullopt;
    }
  } else if (type.kind == NODE_TYPE_WITH_BIT_WIDTH) {
    if (static_cast<const TypeWithBitWidth&>(type).type_with_bit_width_kind ==
        TypeWithBitWidthKind::signed_int) {
      return true;
    } else if (static_cast<const TypeWithBitWidth&>(type)
                   .type_with_bit_width_kind ==
               TypeWithBitWidthKind::unsigned_int) {
      return false;
    } else {
      return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}

bool is_type_float(const BaseType& type) {
  return type.kind == NODE_TYPE_WITH_BIT_WIDTH &&
         static_cast<const TypeWithBitWidth&>(type).type_with_bit_width_kind ==
             TypeWithBitWidthKind::float_;
}

bool is_type_pointer(const BaseType& type) {
  return type.kind == NODE_TYPE_UNARY &&
         static_cast<const TypeUnary&>(type).type_unary_kind ==
             TypeUnaryKind::pointer;
}

std::shared_ptr<BaseType> try_get_pointer_element_type(const BaseType& type) {
  if (type.kind == NODE_TYPE_UNARY &&
      static_cast<const TypeUnary&>(type).type_unary_kind ==
          TypeUnaryKind::pointer) {
    return static_cast<const TypeUnary&>(type).operand_type;
  } else {
    return nullptr;
  }
}
}  // namespace forge
