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
#include <forge/language/forge_formatters.hpp>
#include <forge/syntax_tree/operations/casting.hpp>

namespace forge {
FormattingOptions::FormattingOptions(std::ostream& stream)
    : stream(stream), indent_level(0), indent_tab_width(2) {}

void format_type_basic(FormattingOptions options,
                       const std::shared_ptr<TypeBasic>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");

  switch (node->type_basic_kind) {
    case TypeBasicKind::bool_:
      options.stream.get() << "bool";
      break;
    case TypeBasicKind::void_:
      options.stream.get() << "void";
      break;
    case TypeBasicKind::isize:
      options.stream.get() << "isize";
      break;
    case TypeBasicKind::usize:
      options.stream.get() << "usize";
      break;
  }
}

void format_type_with_bit_width(FormattingOptions options,
                                const std::shared_ptr<TypeWithBitWidth>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");

  switch (node->type_with_bit_width_kind) {
    case TypeWithBitWidthKind::signed_int:
      options.stream.get() << "i";
      break;
    case TypeWithBitWidthKind::unsigned_int:
      options.stream.get() << "u";
      break;
    case TypeWithBitWidthKind::float_:
      options.stream.get() << "f";
      break;
  }

  options.stream.get() << node->bit_width;
}

void format_type_symbol(FormattingOptions options,
                        const std::shared_ptr<TypeSymbol>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");
  FRG_ASSERT(!node->name.empty(), "cannot format type symbol with empty name");

  options.stream.get() << node->name;
}

void format_type_unary(FormattingOptions options,
                       const std::shared_ptr<TypeUnary>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");

  options.stream.get() << "*";

  format_type(options, node->operand_type);
}

void format_type_function(FormattingOptions,
                          const std::shared_ptr<TypeFunction>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");
}

void format_type_structured(FormattingOptions,
                            const std::shared_ptr<TypeStructured>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");

  FRG_TODO();
}

void format_type(FormattingOptions options,
                 const std::shared_ptr<BaseType>& node) {
  FRG_ASSERT(node != nullptr, "cannot format null node");

  if (node->is_const) {
    options.stream.get() << "const ";
  }

  if (auto casted = try_cast_node<TypeBasic>(node); casted) {
    format_type_basic(options, casted);
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(node); casted) {
    format_type_with_bit_width(options, casted);
  } else if (auto casted = try_cast_node<TypeSymbol>(node); casted) {
    format_type_symbol(options, casted);
  } else if (auto casted = try_cast_node<TypeFunction>(node); casted) {
    format_type_function(options, casted);
  } else if (auto casted = try_cast_node<TypeStructured>(node); casted) {
    format_type_structured(options, casted);
  }
}
}  // namespace forge
