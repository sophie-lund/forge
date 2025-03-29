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

#pragma once

#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/declarations/declaration_namespace.hpp>
#include <forge/language/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forge/language/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/language/syntax_tree/statements/statement_basic.hpp>
#include <forge/language/syntax_tree/statements/statement_block.hpp>
#include <forge/language/syntax_tree/statements/statement_if.hpp>
#include <forge/language/syntax_tree/statements/statement_value.hpp>
#include <forge/language/syntax_tree/statements/statement_while.hpp>
#include <forge/language/syntax_tree/translation_unit.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/syntax_tree/values/value_binary.hpp>
#include <forge/language/syntax_tree/values/value_call.hpp>
#include <forge/language/syntax_tree/values/value_cast.hpp>
#include <forge/language/syntax_tree/values/value_literal_bool.hpp>
#include <forge/language/syntax_tree/values/value_literal_number.hpp>
#include <forge/language/syntax_tree/values/value_symbol.hpp>
#include <forge/language/syntax_tree/values/value_unary.hpp>
#include <forge/parsing/syntax_parsing/parsing_context.hpp>

namespace forge {
std::shared_ptr<TypeBasic> parse_type_basic_bool(
    ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic_void(
    ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic_isize(
    ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic_usize(
    ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic(ParsingContext& parsing_context);
std::shared_ptr<TypeSymbol> parse_type_symbol(ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i8(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i16(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i32(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i64(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u8(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u16(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u32(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u64(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_f32(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_f64(
    ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width(
    ParsingContext& parsing_context);
std::shared_ptr<BaseType> parse_type_term(ParsingContext& parsing_context);
std::shared_ptr<BaseType> parse_type_unary(ParsingContext& parsing_context);
std::shared_ptr<BaseType> parse_type(ParsingContext& parsing_context);
std::shared_ptr<ValueLiteralBool> parse_value_literal_bool_true(
    ParsingContext& parsing_context);
std::shared_ptr<ValueLiteralBool> parse_value_literal_bool_false(
    ParsingContext& parsing_context);
std::shared_ptr<ValueLiteralBool> parse_value_literal_bool(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_literal_number(
    ParsingContext& parsing_context);
std::shared_ptr<ValueSymbol> parse_value_symbol(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_parenthesis(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_term(ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_member_access(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_function_call(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_unary(ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_exponentiation(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_multiplicative(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_additive(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_bit_shifts(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_binary_conjunctive(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_binary_disjunctive(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_comparative(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_boolean_and(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_boolean_or(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_cast(ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_assignments(
    ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value(ParsingContext& parsing_context);
std::shared_ptr<StatementBasic> parse_statement_continue(
    ParsingContext& parsing_context);
std::shared_ptr<StatementBasic> parse_statement_break(
    ParsingContext& parsing_context);
std::shared_ptr<StatementValue> parse_statement_execute(
    ParsingContext& parsing_context);
std::shared_ptr<StatementBasic> parse_statement_return_void(
    ParsingContext& parsing_context);
std::shared_ptr<StatementValue> parse_statement_return_value(
    ParsingContext& parsing_context);
std::shared_ptr<StatementBlock> parse_statement_block(
    ParsingContext& parsing_context);
std::shared_ptr<StatementIf> parse_statement_if(
    ParsingContext& parsing_context);
std::shared_ptr<StatementWhile> parse_statement_while(
    ParsingContext& parsing_context);
std::shared_ptr<StatementWhile> parse_statement_do_while(
    ParsingContext& parsing_context);
std::shared_ptr<BaseStatement> parse_statement(ParsingContext& parsing_context);
std::shared_ptr<DeclarationVariable> parse_declaration_variable(
    ParsingContext& parsing_context, bool with_keyword = true,
    bool with_semicolon = true);
std::shared_ptr<DeclarationFunction> parse_declaration_function(
    ParsingContext& parsing_context);
std::shared_ptr<DeclarationTypeAlias> parse_declaration_type_alias(
    ParsingContext& parsing_context);
std::shared_ptr<DeclarationStructuredType> parse_structured_type(
    ParsingContext& parsing_context);
std::shared_ptr<DeclarationNamespace> parse_declaration_namespace(
    ParsingContext& parsing_context);
std::shared_ptr<BaseDeclaration> parse_declaration(
    ParsingContext& parsing_context, bool with_variable_keyword = true);
std::shared_ptr<TranslationUnit> parse_translation_unit(
    ParsingContext& parsing_context);
}  // namespace forge
