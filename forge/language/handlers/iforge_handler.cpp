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

#include <forge/language/handlers/iforge_handler.hpp>

namespace forge {
IHandler::Output IForgeHandler::on_enter(Input<>& input) {
  if (input.node()->kind == NODE_DECLARATION_FUNCTION) {
    std::shared_ptr<DeclarationFunction> node_casted =
        std::static_pointer_cast<DeclarationFunction>(input.node());
    Input<DeclarationFunction> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_enter_declaration_function(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_NAMESPACE) {
    std::shared_ptr<DeclarationNamespace> node_casted =
        std::static_pointer_cast<DeclarationNamespace>(input.node());
    Input<DeclarationNamespace> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_enter_declaration_namespace(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_STRUCTURED_TYPE) {
    std::shared_ptr<DeclarationStructuredType> node_casted =
        std::static_pointer_cast<DeclarationStructuredType>(input.node());
    Input<DeclarationStructuredType> input_casted(input.message_context(),
                                                  input.stack(), node_casted);
    return on_enter_declaration_structured_type(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_TYPE_ALIAS) {
    std::shared_ptr<DeclarationTypeAlias> node_casted =
        std::static_pointer_cast<DeclarationTypeAlias>(input.node());
    Input<DeclarationTypeAlias> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_enter_declaration_type_alias(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
    std::shared_ptr<DeclarationVariable> node_casted =
        std::static_pointer_cast<DeclarationVariable>(input.node());
    Input<DeclarationVariable> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_enter_declaration_variable(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_BASIC) {
    std::shared_ptr<StatementBasic> node_casted =
        std::static_pointer_cast<StatementBasic>(input.node());
    Input<StatementBasic> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_basic(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_BLOCK) {
    std::shared_ptr<StatementBlock> node_casted =
        std::static_pointer_cast<StatementBlock>(input.node());
    Input<StatementBlock> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_block(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_IF) {
    std::shared_ptr<StatementIf> node_casted =
        std::static_pointer_cast<StatementIf>(input.node());
    Input<StatementIf> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_enter_statement_if(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_VALUE) {
    std::shared_ptr<StatementValue> node_casted =
        std::static_pointer_cast<StatementValue>(input.node());
    Input<StatementValue> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_value(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_WHILE) {
    std::shared_ptr<StatementWhile> node_casted =
        std::static_pointer_cast<StatementWhile>(input.node());
    Input<StatementWhile> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_while(input_casted);
  } else if (input.node()->kind == NODE_TRANSLATION_UNIT) {
    std::shared_ptr<TranslationUnit> node_casted =
        std::static_pointer_cast<TranslationUnit>(input.node());
    Input<TranslationUnit> input_casted(input.message_context(), input.stack(),
                                        node_casted);
    return on_enter_translation_unit(input_casted);
  } else if (input.node()->kind == NODE_TYPE_BASIC) {
    std::shared_ptr<TypeBasic> node_casted =
        std::static_pointer_cast<TypeBasic>(input.node());
    Input<TypeBasic> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_type_basic(input_casted);
  } else if (input.node()->kind == NODE_TYPE_FUNCTION) {
    std::shared_ptr<TypeFunction> node_casted =
        std::static_pointer_cast<TypeFunction>(input.node());
    Input<TypeFunction> input_casted(input.message_context(), input.stack(),
                                     node_casted);
    return on_enter_type_function(input_casted);
  } else if (input.node()->kind == NODE_TYPE_STRUCTURED) {
    std::shared_ptr<TypeStructured> node_casted =
        std::static_pointer_cast<TypeStructured>(input.node());
    Input<TypeStructured> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_type_structured(input_casted);
  } else if (input.node()->kind == NODE_TYPE_SYMBOL) {
    std::shared_ptr<TypeSymbol> node_casted =
        std::static_pointer_cast<TypeSymbol>(input.node());
    Input<TypeSymbol> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_enter_type_symbol(input_casted);
  } else if (input.node()->kind == NODE_TYPE_UNARY) {
    std::shared_ptr<TypeUnary> node_casted =
        std::static_pointer_cast<TypeUnary>(input.node());
    Input<TypeUnary> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_type_unary(input_casted);
  } else if (input.node()->kind == NODE_TYPE_WITH_BIT_WIDTH) {
    std::shared_ptr<TypeWithBitWidth> node_casted =
        std::static_pointer_cast<TypeWithBitWidth>(input.node());
    Input<TypeWithBitWidth> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_enter_type_with_bit_width(input_casted);
  } else if (input.node()->kind == NODE_VALUE_BINARY) {
    std::shared_ptr<ValueBinary> node_casted =
        std::static_pointer_cast<ValueBinary>(input.node());
    Input<ValueBinary> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_enter_value_binary(input_casted);
  } else if (input.node()->kind == NODE_VALUE_CALL) {
    std::shared_ptr<ValueCall> node_casted =
        std::static_pointer_cast<ValueCall>(input.node());
    Input<ValueCall> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_value_call(input_casted);
  } else if (input.node()->kind == NODE_VALUE_CAST) {
    std::shared_ptr<ValueCast> node_casted =
        std::static_pointer_cast<ValueCast>(input.node());
    Input<ValueCast> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_value_cast(input_casted);
  } else if (input.node()->kind == NODE_VALUE_LITERAL_BOOL) {
    std::shared_ptr<ValueLiteralBool> node_casted =
        std::static_pointer_cast<ValueLiteralBool>(input.node());
    Input<ValueLiteralBool> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_enter_value_literal_bool(input_casted);
  } else if (input.node()->kind == NODE_VALUE_LITERAL_NUMBER) {
    std::shared_ptr<ValueLiteralNumber> node_casted =
        std::static_pointer_cast<ValueLiteralNumber>(input.node());
    Input<ValueLiteralNumber> input_casted(input.message_context(),
                                           input.stack(), node_casted);
    return on_enter_value_literal_number(input_casted);
  } else if (input.node()->kind == NODE_VALUE_SYMBOL) {
    std::shared_ptr<ValueSymbol> node_casted =
        std::static_pointer_cast<ValueSymbol>(input.node());
    Input<ValueSymbol> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_enter_value_symbol(input_casted);
  } else if (input.node()->kind == NODE_VALUE_UNARY) {
    std::shared_ptr<ValueUnary> node_casted =
        std::static_pointer_cast<ValueUnary>(input.node());
    Input<ValueUnary> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_enter_value_unary(input_casted);
  } else {
    abort();  // unsupported node kind
  }
}

IHandler::Output IForgeHandler::on_leave(Input<>& input) {
  if (input.node()->kind == NODE_DECLARATION_FUNCTION) {
    std::shared_ptr<DeclarationFunction> node_casted =
        std::static_pointer_cast<DeclarationFunction>(input.node());
    Input<DeclarationFunction> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_leave_declaration_function(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_NAMESPACE) {
    std::shared_ptr<DeclarationNamespace> node_casted =
        std::static_pointer_cast<DeclarationNamespace>(input.node());
    Input<DeclarationNamespace> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_leave_declaration_namespace(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_STRUCTURED_TYPE) {
    std::shared_ptr<DeclarationStructuredType> node_casted =
        std::static_pointer_cast<DeclarationStructuredType>(input.node());
    Input<DeclarationStructuredType> input_casted(input.message_context(),
                                                  input.stack(), node_casted);
    return on_leave_declaration_structured_type(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_TYPE_ALIAS) {
    std::shared_ptr<DeclarationTypeAlias> node_casted =
        std::static_pointer_cast<DeclarationTypeAlias>(input.node());
    Input<DeclarationTypeAlias> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_leave_declaration_type_alias(input_casted);
  } else if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
    std::shared_ptr<DeclarationVariable> node_casted =
        std::static_pointer_cast<DeclarationVariable>(input.node());
    Input<DeclarationVariable> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_leave_declaration_variable(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_BASIC) {
    std::shared_ptr<StatementBasic> node_casted =
        std::static_pointer_cast<StatementBasic>(input.node());
    Input<StatementBasic> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_basic(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_BLOCK) {
    std::shared_ptr<StatementBlock> node_casted =
        std::static_pointer_cast<StatementBlock>(input.node());
    Input<StatementBlock> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_block(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_IF) {
    std::shared_ptr<StatementIf> node_casted =
        std::static_pointer_cast<StatementIf>(input.node());
    Input<StatementIf> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_leave_statement_if(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_VALUE) {
    std::shared_ptr<StatementValue> node_casted =
        std::static_pointer_cast<StatementValue>(input.node());
    Input<StatementValue> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_value(input_casted);
  } else if (input.node()->kind == NODE_STATEMENT_WHILE) {
    std::shared_ptr<StatementWhile> node_casted =
        std::static_pointer_cast<StatementWhile>(input.node());
    Input<StatementWhile> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_while(input_casted);
  } else if (input.node()->kind == NODE_TRANSLATION_UNIT) {
    std::shared_ptr<TranslationUnit> node_casted =
        std::static_pointer_cast<TranslationUnit>(input.node());
    Input<TranslationUnit> input_casted(input.message_context(), input.stack(),
                                        node_casted);
    return on_leave_translation_unit(input_casted);
  } else if (input.node()->kind == NODE_TYPE_BASIC) {
    std::shared_ptr<TypeBasic> node_casted =
        std::static_pointer_cast<TypeBasic>(input.node());
    Input<TypeBasic> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_type_basic(input_casted);
  } else if (input.node()->kind == NODE_TYPE_FUNCTION) {
    std::shared_ptr<TypeFunction> node_casted =
        std::static_pointer_cast<TypeFunction>(input.node());
    Input<TypeFunction> input_casted(input.message_context(), input.stack(),
                                     node_casted);
    return on_leave_type_function(input_casted);
  } else if (input.node()->kind == NODE_TYPE_STRUCTURED) {
    std::shared_ptr<TypeStructured> node_casted =
        std::static_pointer_cast<TypeStructured>(input.node());
    Input<TypeStructured> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_type_structured(input_casted);
  } else if (input.node()->kind == NODE_TYPE_SYMBOL) {
    std::shared_ptr<TypeSymbol> node_casted =
        std::static_pointer_cast<TypeSymbol>(input.node());
    Input<TypeSymbol> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_leave_type_symbol(input_casted);
  } else if (input.node()->kind == NODE_TYPE_UNARY) {
    std::shared_ptr<TypeUnary> node_casted =
        std::static_pointer_cast<TypeUnary>(input.node());
    Input<TypeUnary> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_type_unary(input_casted);
  } else if (input.node()->kind == NODE_TYPE_WITH_BIT_WIDTH) {
    std::shared_ptr<TypeWithBitWidth> node_casted =
        std::static_pointer_cast<TypeWithBitWidth>(input.node());
    Input<TypeWithBitWidth> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_leave_type_with_bit_width(input_casted);
  } else if (input.node()->kind == NODE_VALUE_BINARY) {
    std::shared_ptr<ValueBinary> node_casted =
        std::static_pointer_cast<ValueBinary>(input.node());
    Input<ValueBinary> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_leave_value_binary(input_casted);
  } else if (input.node()->kind == NODE_VALUE_CALL) {
    std::shared_ptr<ValueCall> node_casted =
        std::static_pointer_cast<ValueCall>(input.node());
    Input<ValueCall> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_value_call(input_casted);
  } else if (input.node()->kind == NODE_VALUE_CAST) {
    std::shared_ptr<ValueCast> node_casted =
        std::static_pointer_cast<ValueCast>(input.node());
    Input<ValueCast> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_value_cast(input_casted);
  } else if (input.node()->kind == NODE_VALUE_LITERAL_BOOL) {
    std::shared_ptr<ValueLiteralBool> node_casted =
        std::static_pointer_cast<ValueLiteralBool>(input.node());
    Input<ValueLiteralBool> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_leave_value_literal_bool(input_casted);
  } else if (input.node()->kind == NODE_VALUE_LITERAL_NUMBER) {
    std::shared_ptr<ValueLiteralNumber> node_casted =
        std::static_pointer_cast<ValueLiteralNumber>(input.node());
    Input<ValueLiteralNumber> input_casted(input.message_context(),
                                           input.stack(), node_casted);
    return on_leave_value_literal_number(input_casted);
  } else if (input.node()->kind == NODE_VALUE_SYMBOL) {
    std::shared_ptr<ValueSymbol> node_casted =
        std::static_pointer_cast<ValueSymbol>(input.node());
    Input<ValueSymbol> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_leave_value_symbol(input_casted);
  } else if (input.node()->kind == NODE_VALUE_UNARY) {
    std::shared_ptr<ValueUnary> node_casted =
        std::static_pointer_cast<ValueUnary>(input.node());
    Input<ValueUnary> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_leave_value_unary(input_casted);
  } else {
    abort();  // unsupported node kind
  }
}

IHandler::Output IForgeHandler::on_enter_type_basic(Input<TypeBasic>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_type_basic(Input<TypeBasic>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_type_with_bit_width(
    Input<TypeWithBitWidth>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_type_with_bit_width(
    Input<TypeWithBitWidth>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_type_symbol(Input<TypeSymbol>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_type_symbol(Input<TypeSymbol>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_type_unary(Input<TypeUnary>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_type_unary(Input<TypeUnary>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_type_function(Input<TypeFunction>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_type_function(Input<TypeFunction>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_type_structured(
    Input<TypeStructured>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_type_structured(
    Input<TypeStructured>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_literal_bool(
    Input<ValueLiteralBool>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_literal_bool(
    Input<ValueLiteralBool>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_literal_number(
    Input<ValueLiteralNumber>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_literal_number(
    Input<ValueLiteralNumber>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_symbol(Input<ValueSymbol>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_symbol(Input<ValueSymbol>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_unary(Input<ValueUnary>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_unary(Input<ValueUnary>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_binary(Input<ValueBinary>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_binary(Input<ValueBinary>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_call(Input<ValueCall>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_call(Input<ValueCall>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_value_cast(Input<ValueCast>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_value_cast(Input<ValueCast>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_statement_basic(
    Input<StatementBasic>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_statement_basic(
    Input<StatementBasic>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_statement_value(
    Input<StatementValue>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_statement_value(
    Input<StatementValue>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_statement_if(Input<StatementIf>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_statement_if(Input<StatementIf>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_statement_while(
    Input<StatementWhile>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_statement_while(
    Input<StatementWhile>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_statement_block(
    Input<StatementBlock>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_statement_block(
    Input<StatementBlock>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_declaration_variable(
    Input<DeclarationVariable>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_declaration_function(
    Input<DeclarationFunction>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_declaration_function(
    Input<DeclarationFunction>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_declaration_structured_type(
    Input<DeclarationStructuredType>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_declaration_structured_type(
    Input<DeclarationStructuredType>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_declaration_type_alias(
    Input<DeclarationTypeAlias>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_declaration_type_alias(
    Input<DeclarationTypeAlias>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_declaration_namespace(
    Input<DeclarationNamespace>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_declaration_namespace(
    Input<DeclarationNamespace>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_enter_translation_unit(
    Input<TranslationUnit>&) {
  return Output();
}

IHandler::Output IForgeHandler::on_leave_translation_unit(
    Input<TranslationUnit>&) {
  return Output();
}
}  // namespace forge
