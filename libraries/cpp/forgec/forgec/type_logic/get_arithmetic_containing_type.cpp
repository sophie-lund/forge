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
#include <forgec/type_logic/get_arithmetic_containing_type.hpp>
#include <forgec/type_logic/type_predicates.hpp>
#include <langtools/core/assert.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>
#include <langtools/syntax_tree/operations/cloners.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>

namespace forge {
std::shared_ptr<BaseType> get_arithmetic_containing_type(
    const lt::CodegenContext &codegen_context,
    const std::shared_ptr<BaseType> &a, const std::shared_ptr<BaseType> &b) {
  LT_ASSERT(a != nullptr,
            "cannot get arithmetic containing type with null type nodes");
  LT_ASSERT(b != nullptr,
            "cannot get arithmetic containing type with null type nodes");

  // If the types are identical, no other logic is needed
  if (compare_nodes(a, b)) {
    return clone_node(a);
  }

  // If both types are numbers, find a containing number type
  if (is_type_number(a) && is_type_number(b)) {
    TypeWithBitWidthKind type_with_bit_width_kind =
        TypeWithBitWidthKind::unsigned_int;

    if (is_type_float(a) || is_type_float(b)) {
      type_with_bit_width_kind = TypeWithBitWidthKind::float_;
    } else if (get_integer_type_signedness(a).value_or(false) ||
               get_integer_type_signedness(b).value_or(false)) {
      type_with_bit_width_kind = TypeWithBitWidthKind::signed_int;
    }

    return std::make_shared<TypeWithBitWidth>(
        lt::SourceRange(), type_with_bit_width_kind,
        std::max(get_number_type_bit_width(codegen_context, a).value(),
                 get_number_type_bit_width(codegen_context, b).value()));
  }

  // No arithmetic containing type could be found
  return nullptr;
}
}  // namespace forge
