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

#include <forgec/logic/types/get_casting_mode.hpp>
#include <forgec/logic/types/type_predicates.hpp>
#include <forgec/syntax_tree/types/type_with_bit_width.hpp>
#include <langtools/core/assert.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>

namespace forge {
CastingMode get_casting_mode(const lt::CodegenContext& codegen_context,
                             const std::shared_ptr<BaseType>& from,
                             const std::shared_ptr<BaseType>& to) {
  LT_ASSERT(from != nullptr, "from type must not be null");
  LT_ASSERT(to != nullptr, "to type must not be null");

  // If the types are identical, no casting is needed
  if (compare_nodes(from, to)) {
    return CastingMode::implicit;
  }

  // If both the types are numeric
  if (is_type_number(from) && is_type_number(to)) {
    // If both types are floats
    if (is_type_float(from) && is_type_float(to)) {
      // If the bit width is not reduced, we can cast implicitly
      if (get_number_type_bit_width(codegen_context, from) <=
          get_number_type_bit_width(codegen_context, to)) {
        return CastingMode::implicit;
      }
    }

    // If both types are integers of the same signedness
    if (is_type_integer(from) && is_type_integer(to) &&
        get_integer_type_signedness(from).value() ==
            get_integer_type_signedness(to).value()) {
      // If the bit width is not reduced, we can cast implicitly
      if (get_number_type_bit_width(codegen_context, from) <=
          get_number_type_bit_width(codegen_context, to)) {
        return CastingMode::implicit;
      }
    }

    // If we are casting from unsigned to signed
    if (is_type_integer(from) && is_type_integer(to) &&
        !get_integer_type_signedness(from).value() &&
        get_integer_type_signedness(to).value()) {
      // If the number of non-sign bits is not reduced, we can cast implicitly
      //
      // Note that this condition uses '<' instead of '<='
      if (get_number_type_bit_width(codegen_context, from) <
          get_number_type_bit_width(codegen_context, to)) {
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
