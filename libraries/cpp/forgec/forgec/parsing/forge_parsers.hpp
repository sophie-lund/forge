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

#include <forgec/syntax_tree/declarations/declaration_function.hpp>
#include <forgec/syntax_tree/declarations/declaration_namespace.hpp>
#include <forgec/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forgec/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forgec/syntax_tree/declarations/declaration_variable.hpp>
#include <forgec/syntax_tree/statements/statement_basic.hpp>
#include <forgec/syntax_tree/statements/statement_block.hpp>
#include <forgec/syntax_tree/statements/statement_if.hpp>
#include <forgec/syntax_tree/statements/statement_value.hpp>
#include <forgec/syntax_tree/statements/statement_while.hpp>
#include <forgec/syntax_tree/translation_unit.hpp>
#include <forgec/syntax_tree/types/type_basic.hpp>
#include <forgec/syntax_tree/types/type_function.hpp>
#include <forgec/syntax_tree/types/type_structured.hpp>
#include <forgec/syntax_tree/types/type_symbol.hpp>
#include <forgec/syntax_tree/types/type_with_bit_width.hpp>
#include <forgec/syntax_tree/values/value_binary.hpp>
#include <forgec/syntax_tree/values/value_call.hpp>
#include <forgec/syntax_tree/values/value_cast.hpp>
#include <forgec/syntax_tree/values/value_literal_bool.hpp>
#include <forgec/syntax_tree/values/value_literal_number.hpp>
#include <forgec/syntax_tree/values/value_symbol.hpp>
#include <forgec/syntax_tree/values/value_unary.hpp>
#include <langtools/parsing/syntax_parsing/parsing_context.hpp>

namespace forge {
std::shared_ptr<TypeBasic> parse_type_basic_bool(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic_void(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic_isize(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic_usize(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeBasic> parse_type_basic(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeSymbol> parse_type_symbol(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i8(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i16(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i32(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i64(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u8(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u16(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u32(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u64(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_f32(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_f64(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeFunction> parse_type_function(
    lt::ParsingContext& parsing_context);
std::shared_ptr<TypeStructured> parse_type_structured(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseType> parse_type_term(lt::ParsingContext& parsing_context);
std::shared_ptr<BaseType> parse_type_unary(lt::ParsingContext& parsing_context);
std::shared_ptr<BaseType> parse_type(lt::ParsingContext& parsing_context);
std::shared_ptr<ValueLiteralBool> parse_value_literal_bool_true(
    lt::ParsingContext& parsing_context);
std::shared_ptr<ValueLiteralBool> parse_value_literal_bool_false(
    lt::ParsingContext& parsing_context);
std::shared_ptr<ValueLiteralBool> parse_value_literal_bool(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_literal_number(
    lt::ParsingContext& parsing_context);
std::shared_ptr<ValueSymbol> parse_value_symbol(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_parenthesis(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_term(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_member_access(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_function_call(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_unary(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_exponentiation(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_multiplicative(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_additive(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_bit_shifts(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_binary_conjunctive(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_binary_disjunctive(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_comparative(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_boolean_and(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_boolean_or(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_cast(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value_assignments(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseValue> parse_value(lt::ParsingContext& parsing_context);
std::shared_ptr<StatementBasic> parse_statement_continue(
    lt::ParsingContext& parsing_context);
std::shared_ptr<StatementBasic> parse_statement_break(
    lt::ParsingContext& parsing_context);
std::shared_ptr<StatementValue> parse_statement_execute(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseStatement> parse_statement_return(
    lt::ParsingContext& parsing_context);
std::shared_ptr<StatementBlock> parse_statement_block(
    lt::ParsingContext& parsing_context);
std::shared_ptr<StatementIf> parse_statement_if(
    lt::ParsingContext& parsing_context);
std::shared_ptr<StatementWhile> parse_statement_while(
    lt::ParsingContext& parsing_context);
std::shared_ptr<StatementWhile> parse_statement_do_while(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseStatement> parse_statement(
    lt::ParsingContext& parsing_context);
std::shared_ptr<DeclarationVariable> parse_declaration_variable(
    lt::ParsingContext& parsing_context, bool with_keyword = true,
    bool with_semicolon = true);
std::shared_ptr<DeclarationFunction> parse_declaration_function(
    lt::ParsingContext& parsing_context);
std::shared_ptr<DeclarationTypeAlias> parse_declaration_type_alias(
    lt::ParsingContext& parsing_context);
std::shared_ptr<DeclarationStructuredType> parse_declaration_structured_type(
    lt::ParsingContext& parsing_context);
std::shared_ptr<DeclarationNamespace> parse_declaration_namespace(
    lt::ParsingContext& parsing_context);
std::shared_ptr<BaseDeclaration> parse_declaration(
    lt::ParsingContext& parsing_context, bool with_variable_keyword = true);
std::shared_ptr<TranslationUnit> parse_translation_unit(
    lt::ParsingContext& parsing_context);
}  // namespace forge
