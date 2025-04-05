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
#include <forge/language/syntax_tree/types/type_function.hpp>
#include <forge/language/syntax_tree/types/type_structured.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/syntax_tree/values/value_binary.hpp>
#include <forge/language/syntax_tree/values/value_call.hpp>
#include <forge/language/syntax_tree/values/value_cast.hpp>
#include <forge/language/syntax_tree/values/value_literal_bool.hpp>
#include <forge/language/syntax_tree/values/value_literal_number.hpp>
#include <forge/language/syntax_tree/values/value_symbol.hpp>
#include <forge/language/syntax_tree/values/value_unary.hpp>
#include <forge/syntax_tree/visitors/ihandler.hpp>

namespace forge {
/**
 * @brief A handler interface that provides a method for each node type in the
 * Forge syntax tree.
 */
class IForgeHandler : public IHandler {
 protected:
  virtual Output on_enter(Input<>& input) final;

  virtual Output on_leave(Input<>& input) final;

  virtual Output on_enter_type_basic(Input<TypeBasic>& input);

  virtual Output on_leave_type_basic(Input<TypeBasic>& input);

  virtual Output on_enter_type_with_bit_width(Input<TypeWithBitWidth>& input);

  virtual Output on_leave_type_with_bit_width(Input<TypeWithBitWidth>& input);

  virtual Output on_enter_type_symbol(Input<TypeSymbol>& input);

  virtual Output on_leave_type_symbol(Input<TypeSymbol>& input);

  virtual Output on_enter_type_unary(Input<TypeUnary>& input);

  virtual Output on_leave_type_unary(Input<TypeUnary>& input);

  virtual Output on_enter_type_function(Input<TypeFunction>& input);

  virtual Output on_leave_type_function(Input<TypeFunction>& input);

  virtual Output on_enter_type_structured(Input<TypeStructured>& input);

  virtual Output on_leave_type_structured(Input<TypeStructured>& input);

  virtual Output on_enter_value_literal_bool(Input<ValueLiteralBool>& input);

  virtual Output on_leave_value_literal_bool(Input<ValueLiteralBool>& input);

  virtual Output on_enter_value_literal_number(
      Input<ValueLiteralNumber>& input);

  virtual Output on_leave_value_literal_number(
      Input<ValueLiteralNumber>& input);

  virtual Output on_enter_value_symbol(Input<ValueSymbol>& input);

  virtual Output on_leave_value_symbol(Input<ValueSymbol>& input);

  virtual Output on_enter_value_unary(Input<ValueUnary>& input);

  virtual Output on_leave_value_unary(Input<ValueUnary>& input);

  virtual Output on_enter_value_binary(Input<ValueBinary>& input);

  virtual Output on_leave_value_binary(Input<ValueBinary>& input);

  virtual Output on_enter_value_call(Input<ValueCall>& input);

  virtual Output on_leave_value_call(Input<ValueCall>& input);

  virtual Output on_enter_value_cast(Input<ValueCast>& input);

  virtual Output on_leave_value_cast(Input<ValueCast>& input);

  virtual Output on_enter_statement_basic(Input<StatementBasic>& input);

  virtual Output on_leave_statement_basic(Input<StatementBasic>& input);

  virtual Output on_enter_statement_value(Input<StatementValue>& input);

  virtual Output on_leave_statement_value(Input<StatementValue>& input);

  virtual Output on_enter_statement_if(Input<StatementIf>& input);

  virtual Output on_leave_statement_if(Input<StatementIf>& input);

  virtual Output on_enter_statement_while(Input<StatementWhile>& input);

  virtual Output on_leave_statement_while(Input<StatementWhile>& input);

  virtual Output on_enter_statement_block(Input<StatementBlock>& input);

  virtual Output on_leave_statement_block(Input<StatementBlock>& input);

  virtual Output on_enter_declaration_variable(
      Input<DeclarationVariable>& input);

  virtual Output on_leave_declaration_variable(
      Input<DeclarationVariable>& input);

  virtual Output on_enter_declaration_function(
      Input<DeclarationFunction>& input);

  virtual Output on_leave_declaration_function(
      Input<DeclarationFunction>& input);

  virtual Output on_enter_declaration_structured_type(
      Input<DeclarationStructuredType>& input);

  virtual Output on_leave_declaration_structured_type(
      Input<DeclarationStructuredType>& input);

  virtual Output on_enter_declaration_type_alias(
      Input<DeclarationTypeAlias>& input);

  virtual Output on_leave_declaration_type_alias(
      Input<DeclarationTypeAlias>& input);

  virtual Output on_enter_declaration_namespace(
      Input<DeclarationNamespace>& input);

  virtual Output on_leave_declaration_namespace(
      Input<DeclarationNamespace>& input);

  virtual Output on_enter_translation_unit(Input<TranslationUnit>& input);

  virtual Output on_leave_translation_unit(Input<TranslationUnit>& input);

 protected:
  template <typename TInput>
  static const DeclarationFunction* get_current_function(TInput& input);
};
}  // namespace forge

#include "iforge_handler.tpp"
