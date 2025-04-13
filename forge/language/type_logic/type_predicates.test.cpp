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

#include <gtest/gtest.h>

#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/type_logic/type_predicates.hpp>

using namespace forge;

TEST(language_type_logic_type_predicates, is_type_void_true) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::void_);
  ASSERT_TRUE(is_type_void(type));
}

TEST(language_type_logic_type_predicates, is_type_void_false_other_basic) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::isize);
  ASSERT_FALSE(is_type_void(type));
}

TEST(language_type_logic_type_predicates, is_type_void_false_other_kind) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_FALSE(is_type_void(type));
}

TEST(language_type_logic_type_predicates, is_type_bool_true) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
  ASSERT_TRUE(is_type_bool(type));
}

TEST(language_type_logic_type_predicates, is_type_bool_false_other_basic) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::isize);
  ASSERT_FALSE(is_type_bool(type));
}

TEST(language_type_logic_type_predicates, is_type_bool_false_other_kind) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_FALSE(is_type_bool(type));
}

TEST(language_type_logic_type_predicates, is_type_integer_true_isize) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::isize);
  ASSERT_TRUE(is_type_integer(type));
}

TEST(language_type_logic_type_predicates, is_type_integer_true_usize) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::usize);
  ASSERT_TRUE(is_type_integer(type));
}

TEST(language_type_logic_type_predicates, is_type_integer_false_other_basic) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
  ASSERT_FALSE(is_type_integer(type));
}

TEST(language_type_logic_type_predicates, is_type_integer_true_with_bit_width) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_TRUE(is_type_integer(type));
}

TEST(language_type_logic_type_predicates,
     is_type_integer_false_with_bit_width) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::float_, 32);
  ASSERT_FALSE(is_type_integer(type));
}

TEST(language_type_logic_type_predicates, is_type_integer_false_other_kind) {
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(is_type_integer(type));
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_true_isize) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::isize);
  ASSERT_TRUE(get_integer_type_signedness(type).has_value());
  ASSERT_TRUE(get_integer_type_signedness(type).value());
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_true_usize) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::usize);
  ASSERT_TRUE(get_integer_type_signedness(type).has_value());
  ASSERT_FALSE(get_integer_type_signedness(type).value());
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_false_other_basic) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
  ASSERT_FALSE(get_integer_type_signedness(type).has_value());
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_true_with_bit_width_signed) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_TRUE(get_integer_type_signedness(type).has_value());
  ASSERT_TRUE(get_integer_type_signedness(type).value());
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_true_with_bit_width_unsigned) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::unsigned_int, 32);
  ASSERT_TRUE(get_integer_type_signedness(type).has_value());
  ASSERT_FALSE(get_integer_type_signedness(type).value());
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_false_with_bit_width) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::float_, 32);
  ASSERT_FALSE(get_integer_type_signedness(type).has_value());
}

TEST(language_type_logic_type_predicates,
     get_integer_type_signedness_false_other_kind) {
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(get_integer_type_signedness(type).has_value());
}

TEST(language_type_logic_type_predicates, is_type_float_true_with_bit_width) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::float_, 32);
  ASSERT_TRUE(is_type_float(type));
}

TEST(language_type_logic_type_predicates, is_type_float_false_with_bit_width) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_FALSE(is_type_float(type));
}

TEST(language_type_logic_type_predicates, is_type_float_false_other_kind) {
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(is_type_float(type));
}

TEST(language_type_logic_type_predicates, is_type_number_true_isize) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::isize);
  ASSERT_TRUE(is_type_number(type));
}

TEST(language_type_logic_type_predicates, is_type_number_true_usize) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::usize);
  ASSERT_TRUE(is_type_number(type));
}

TEST(language_type_logic_type_predicates, is_type_number_false_other_basic) {
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
  ASSERT_FALSE(is_type_number(type));
}

TEST(language_type_logic_type_predicates,
     is_type_number_true_with_bit_width_int) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_TRUE(is_type_number(type));
}

TEST(language_type_logic_type_predicates,
     is_type_number_true_with_bit_width_float) {
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::float_, 32);
  ASSERT_TRUE(is_type_number(type));
}

TEST(language_type_logic_type_predicates, is_type_number_false_other_kind) {
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(is_type_number(type));
}

TEST(language_type_logic_type_predicates,
     get_number_type_bit_width_true_isize) {
  auto codegen_context = CodegenContext::create().value();
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::isize);
  ASSERT_TRUE(get_number_type_bit_width(codegen_context, type).has_value());
  ASSERT_EQ(get_number_type_bit_width(codegen_context, type).value(),
            sizeof(void*) * 8);
}

TEST(language_type_logic_type_predicates,
     get_number_type_bit_width_true_usize) {
  auto codegen_context = CodegenContext::create().value();
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::usize);
  ASSERT_TRUE(get_number_type_bit_width(codegen_context, type).has_value());
  ASSERT_EQ(get_number_type_bit_width(codegen_context, type).value(),
            sizeof(void*) * 8);
}

TEST(language_type_logic_type_predicates,
     get_number_type_bit_width_false_other_basic) {
  auto codegen_context = CodegenContext::create().value();
  auto type = std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
  ASSERT_FALSE(get_number_type_bit_width(codegen_context, type).has_value());
}

TEST(language_type_logic_type_predicates,
     get_number_type_bit_width_true_with_bit_width_int) {
  auto codegen_context = CodegenContext::create().value();
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  ASSERT_TRUE(get_number_type_bit_width(codegen_context, type).has_value());
  ASSERT_EQ(get_number_type_bit_width(codegen_context, type).value(), 32);
}

TEST(language_type_logic_type_predicates,
     get_number_type_bit_width_true_with_bit_width_float) {
  auto codegen_context = CodegenContext::create().value();
  auto type = std::make_shared<TypeWithBitWidth>(
      SourceRange(), TypeWithBitWidthKind::float_, 64);
  ASSERT_TRUE(get_number_type_bit_width(codegen_context, type).has_value());
  ASSERT_EQ(get_number_type_bit_width(codegen_context, type).value(), 64);
}

TEST(language_type_logic_type_predicates,
     get_number_type_bit_width_false_other_kind) {
  auto codegen_context = CodegenContext::create().value();
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(get_number_type_bit_width(codegen_context, type).has_value());
}

TEST(language_type_logic_type_predicates, is_type_pointer_true) {
  auto type = std::make_shared<TypeUnary>(
      SourceRange(), TypeUnaryKind::pointer,
      std::make_shared<TypeSymbol>(SourceRange(), "x"));
  ASSERT_TRUE(is_type_pointer(type));
}

TEST(language_type_logic_type_predicates, is_type_pointer_false) {
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(is_type_pointer(type));
}

TEST(language_type_logic_type_predicates,
     try_get_pointer_element_type_pointer) {
  auto type = std::make_shared<TypeUnary>(
      SourceRange(), TypeUnaryKind::pointer,
      std::make_shared<TypeSymbol>(SourceRange(), "x"));
  auto element_type = try_get_pointer_element_type(type);

  ASSERT_TRUE(element_type);
  ASSERT_EQ(element_type->kind, NODE_TYPE_SYMBOL);
}

TEST(language_type_logic_type_predicates,
     try_get_pointer_element_type_non_pointer) {
  auto type = std::make_shared<TypeSymbol>(SourceRange(), "x");
  ASSERT_FALSE(try_get_pointer_element_type(type));
}
