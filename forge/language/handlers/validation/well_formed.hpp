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

#include <forge/language/handlers/iforge_handler.hpp>

namespace forge {
class WellFormedValidationHandler : public IForgeHandler {
 protected:
  virtual Output on_leave_type_with_bit_width(
      Input<TypeWithBitWidth>& input) final;

  virtual Output on_leave_type_symbol(Input<TypeSymbol>& input) final;

  virtual Output on_leave_type_unary(Input<TypeUnary>& input) final;

  virtual Output on_leave_type_function(Input<TypeFunction>& input) final;

  virtual Output on_leave_type_structured(Input<TypeStructured>& input) final;

  virtual Output on_leave_value_literal_number(
      Input<ValueLiteralNumber>& input) final;

  virtual Output on_leave_value_symbol(Input<ValueSymbol>& input) final;

  virtual Output on_leave_value_unary(Input<ValueUnary>& input) final;

  virtual Output on_leave_value_binary(Input<ValueBinary>& input) final;

  virtual Output on_leave_value_call(Input<ValueCall>& input) final;

  virtual Output on_leave_value_cast(Input<ValueCast>& input) final;

  virtual Output on_leave_statement_value(Input<StatementValue>& input) final;

  virtual Output on_leave_statement_if(Input<StatementIf>& input) final;

  virtual Output on_leave_statement_while(Input<StatementWhile>& input) final;

  virtual Output on_leave_statement_block(Input<StatementBlock>& input) final;

  virtual Output on_leave_declaration_variable(
      Input<DeclarationVariable>& input) final;

  virtual Output on_leave_declaration_function(
      Input<DeclarationFunction>& input) final;

  virtual Output on_leave_declaration_structured_type(
      Input<DeclarationStructuredType>& input) final;

  virtual Output on_leave_declaration_type_alias(
      Input<DeclarationTypeAlias>& input) final;

  virtual Output on_leave_declaration_namespace(
      Input<DeclarationNamespace>& input) final;

  virtual Output on_leave_translation_unit(Input<TranslationUnit>& input) final;
};
}  // namespace forge
