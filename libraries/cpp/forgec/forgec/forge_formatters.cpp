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

#include <forgec/forge_formatters.hpp>
#include <langtools/core/assert.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>

namespace forge {
FormattingOptions::FormattingOptions(std::ostream& stream)
    : stream(stream), indent_level(0), indent_tab_width(2) {}

void format_type_basic(FormattingOptions options,
                       const std::shared_ptr<TypeBasic>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");

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
    default:
      LT_ABORT("unsupported type basic kind");
  }
}

void format_type_with_bit_width(FormattingOptions options,
                                const std::shared_ptr<TypeWithBitWidth>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");

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
    default:
      LT_ABORT("unsupported type with bit width kind");
  }

  options.stream.get() << node->bit_width;
}

void format_type_symbol(FormattingOptions options,
                        const std::shared_ptr<TypeSymbol>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");
  LT_ASSERT(!node->name.empty(), "cannot format type symbol with empty name");

  options.stream.get() << node->name;
}

void format_type_unary(FormattingOptions options,
                       const std::shared_ptr<TypeUnary>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");

  options.stream.get() << "*";

  format_type(options, node->operand_type);
}

void format_type_function(FormattingOptions options,
                          const std::shared_ptr<TypeFunction>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");
  LT_ASSERT(node->return_type != nullptr,
            "cannot format type function with null return type");

  options.stream.get() << "(";

  for (size_t i = 0; i < node->arg_types.size(); ++i) {
    if (i > 0) {
      options.stream.get() << ", ";
    }

    format_type(options, node->arg_types[i]);
  }

  options.stream.get() << ") -> ";

  format_type(options, node->return_type);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void format_type_structured(FormattingOptions,
                            const std::shared_ptr<TypeStructured>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");

  LT_TODO();
}
#pragma clang diagnostic pop

void format_type(FormattingOptions options,
                 const std::shared_ptr<BaseType>& node) {
  LT_ASSERT(node != nullptr, "cannot format null node");

  if (node->is_const) {
    options.stream.get() << "const ";
  }

  if (auto casted = try_cast_node<TypeBasic>(node); casted) {
    format_type_basic(options, casted);
  } else if (auto casted = try_cast_node<TypeWithBitWidth>(node); casted) {
    format_type_with_bit_width(options, casted);
  } else if (auto casted = try_cast_node<TypeSymbol>(node); casted) {
    format_type_symbol(options, casted);
  } else if (auto casted = try_cast_node<TypeUnary>(node); casted) {
    format_type_unary(options, casted);
  } else if (auto casted = try_cast_node<TypeFunction>(node); casted) {
    format_type_function(options, casted);
  } else if (auto casted = try_cast_node<TypeStructured>(node); casted) {
    format_type_structured(options, casted);
  } else {
    LT_ABORT("unsupported type node kind: " << node->kind);
  }
}
}  // namespace forge
