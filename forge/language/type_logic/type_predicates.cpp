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
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/type_logic/type_predicates.hpp>
#include <forge/syntax_tree/operations/casting.hpp>

namespace forge {
bool is_type_void(const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  auto casted = try_cast_node<TypeBasic>(type);

  return casted && casted->type_basic_kind == TypeBasicKind::void_;
}

bool is_type_bool(const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  auto casted = try_cast_node<TypeBasic>(type);

  return casted && casted->type_basic_kind == TypeBasicKind::bool_;
}

bool is_type_integer(const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  if (auto casted = try_cast_node<TypeBasic>(type); casted) {
    return casted->type_basic_kind == TypeBasicKind::isize ||
           casted->type_basic_kind == TypeBasicKind::usize;
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(type); casted) {
    return casted->type_with_bit_width_kind ==
               TypeWithBitWidthKind::signed_int ||
           casted->type_with_bit_width_kind ==
               TypeWithBitWidthKind::unsigned_int;
  } else {
    return false;
  }
}

std::optional<bool> get_integer_type_signedness(
    const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  if (auto casted = try_cast_node<TypeBasic>(type); casted) {
    if (casted->type_basic_kind == TypeBasicKind::isize) {
      return true;
    } else if (casted->type_basic_kind == TypeBasicKind::usize) {
      return false;
    } else {
      return std::nullopt;
    }
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(type); casted) {
    if (casted->type_with_bit_width_kind == TypeWithBitWidthKind::signed_int) {
      return true;
    } else if (casted->type_with_bit_width_kind ==
               TypeWithBitWidthKind::unsigned_int) {
      return false;
    } else {
      return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}

bool is_type_float(const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  auto casted = try_cast_node<TypeWithBitWidth>(type);

  return casted &&
         casted->type_with_bit_width_kind == TypeWithBitWidthKind::float_;
}

bool is_type_number(const std::shared_ptr<BaseType>& type) {
  return is_type_integer(type) || is_type_float(type);
}

std::optional<uint32_t> get_number_type_bit_width(
    const CodegenContext& codegen_context,
    const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  if (auto casted = try_cast_node<TypeWithBitWidth>(type); casted) {
    return casted->bit_width;
  } else if (auto casted = try_cast_node<TypeBasic>(type); casted) {
    if (casted->type_basic_kind == TypeBasicKind::isize ||
        casted->type_basic_kind == TypeBasicKind::usize) {
      return codegen_context.get_target_machine_pointer_bit_width();
    } else {
      return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}

bool is_type_pointer(const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  auto casted = try_cast_node<TypeUnary>(type);

  return casted && casted->type_unary_kind == TypeUnaryKind::pointer;
}

std::shared_ptr<BaseType> try_get_pointer_element_type(
    const std::shared_ptr<BaseType>& type) {
  FRG_ASSERT(type != nullptr, "type must not be null");

  if (auto casted = try_cast_node<TypeUnary>(type); casted) {
    return casted->operand_type;
  } else {
    return nullptr;
  }
}
}  // namespace forge
