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

#include <forgec/handlers/iforge_handler.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>

namespace forge {
lt::IHandler::Output IForgeHandler::on_enter(Input<>& input) {
  if (auto node_casted = try_cast_node<DeclarationFunction>(input.node());
      node_casted) {
    Input<DeclarationFunction> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_enter_declaration_function(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationNamespace>(input.node());
             node_casted) {
    Input<DeclarationNamespace> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_enter_declaration_namespace(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationStructuredType>(input.node());
             node_casted) {
    Input<DeclarationStructuredType> input_casted(input.message_context(),
                                                  input.stack(), node_casted);
    return on_enter_declaration_structured_type(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationTypeAlias>(input.node());
             node_casted) {
    Input<DeclarationTypeAlias> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_enter_declaration_type_alias(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationVariable>(input.node());
             node_casted) {
    Input<DeclarationVariable> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_enter_declaration_variable(input_casted);
  } else if (auto node_casted = try_cast_node<StatementBasic>(input.node());
             node_casted) {
    Input<StatementBasic> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_basic(input_casted);
  } else if (auto node_casted = try_cast_node<StatementBlock>(input.node());
             node_casted) {
    Input<StatementBlock> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_block(input_casted);
  } else if (auto node_casted = try_cast_node<StatementIf>(input.node());
             node_casted) {
    Input<StatementIf> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_enter_statement_if(input_casted);
  } else if (auto node_casted = try_cast_node<StatementValue>(input.node());
             node_casted) {
    Input<StatementValue> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_value(input_casted);
  } else if (auto node_casted = try_cast_node<StatementWhile>(input.node());
             node_casted) {
    Input<StatementWhile> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_statement_while(input_casted);
  } else if (auto node_casted = try_cast_node<TranslationUnit>(input.node());
             node_casted) {
    Input<TranslationUnit> input_casted(input.message_context(), input.stack(),
                                        node_casted);
    return on_enter_translation_unit(input_casted);
  } else if (auto node_casted = try_cast_node<TypeBasic>(input.node());
             node_casted) {
    Input<TypeBasic> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_type_basic(input_casted);
  } else if (auto node_casted = try_cast_node<TypeFunction>(input.node());
             node_casted) {
    Input<TypeFunction> input_casted(input.message_context(), input.stack(),
                                     node_casted);
    return on_enter_type_function(input_casted);
  } else if (auto node_casted = try_cast_node<TypeStructured>(input.node());
             node_casted) {
    Input<TypeStructured> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_enter_type_structured(input_casted);
  } else if (auto node_casted = try_cast_node<TypeSymbol>(input.node());
             node_casted) {
    Input<TypeSymbol> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_enter_type_symbol(input_casted);
  } else if (auto node_casted = try_cast_node<TypeUnary>(input.node());
             node_casted) {
    Input<TypeUnary> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_type_unary(input_casted);
  } else if (auto node_casted = try_cast_node<TypeWithBitWidth>(input.node());
             node_casted) {
    Input<TypeWithBitWidth> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_enter_type_with_bit_width(input_casted);
  } else if (auto node_casted = try_cast_node<ValueBinary>(input.node());
             node_casted) {
    Input<ValueBinary> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_enter_value_binary(input_casted);
  } else if (auto node_casted = try_cast_node<ValueCall>(input.node());
             node_casted) {
    Input<ValueCall> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_value_call(input_casted);
  } else if (auto node_casted = try_cast_node<ValueCast>(input.node());
             node_casted) {
    Input<ValueCast> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_enter_value_cast(input_casted);
  } else if (auto node_casted = try_cast_node<ValueLiteralBool>(input.node());
             node_casted) {
    Input<ValueLiteralBool> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_enter_value_literal_bool(input_casted);
  } else if (auto node_casted = try_cast_node<ValueLiteralNumber>(input.node());
             node_casted) {
    Input<ValueLiteralNumber> input_casted(input.message_context(),
                                           input.stack(), node_casted);
    return on_enter_value_literal_number(input_casted);
  } else if (auto node_casted = try_cast_node<ValueSymbol>(input.node());
             node_casted) {
    Input<ValueSymbol> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_enter_value_symbol(input_casted);
  } else if (auto node_casted = try_cast_node<ValueUnary>(input.node());
             node_casted) {
    Input<ValueUnary> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_enter_value_unary(input_casted);
  } else {
    LT_ABORT("unsupported node kind " << input.node()->kind.name());
  }
}

lt::IHandler::Output IForgeHandler::on_leave(Input<>& input) {
  if (auto node_casted = try_cast_node<DeclarationFunction>(input.node());
      node_casted) {
    Input<DeclarationFunction> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_leave_declaration_function(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationNamespace>(input.node());
             node_casted) {
    Input<DeclarationNamespace> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_leave_declaration_namespace(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationStructuredType>(input.node());
             node_casted) {
    Input<DeclarationStructuredType> input_casted(input.message_context(),
                                                  input.stack(), node_casted);
    return on_leave_declaration_structured_type(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationTypeAlias>(input.node());
             node_casted) {
    Input<DeclarationTypeAlias> input_casted(input.message_context(),
                                             input.stack(), node_casted);
    return on_leave_declaration_type_alias(input_casted);
  } else if (auto node_casted =
                 try_cast_node<DeclarationVariable>(input.node());
             node_casted) {
    Input<DeclarationVariable> input_casted(input.message_context(),
                                            input.stack(), node_casted);
    return on_leave_declaration_variable(input_casted);
  } else if (auto node_casted = try_cast_node<StatementBasic>(input.node());
             node_casted) {
    Input<StatementBasic> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_basic(input_casted);
  } else if (auto node_casted = try_cast_node<StatementBlock>(input.node());
             node_casted) {
    Input<StatementBlock> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_block(input_casted);
  } else if (auto node_casted = try_cast_node<StatementIf>(input.node());
             node_casted) {
    Input<StatementIf> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_leave_statement_if(input_casted);
  } else if (auto node_casted = try_cast_node<StatementValue>(input.node());
             node_casted) {
    Input<StatementValue> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_value(input_casted);
  } else if (auto node_casted = try_cast_node<StatementWhile>(input.node());
             node_casted) {
    Input<StatementWhile> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_statement_while(input_casted);
  } else if (auto node_casted = try_cast_node<TranslationUnit>(input.node());
             node_casted) {
    Input<TranslationUnit> input_casted(input.message_context(), input.stack(),
                                        node_casted);
    return on_leave_translation_unit(input_casted);
  } else if (auto node_casted = try_cast_node<TypeBasic>(input.node());
             node_casted) {
    Input<TypeBasic> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_type_basic(input_casted);
  } else if (auto node_casted = try_cast_node<TypeFunction>(input.node());
             node_casted) {
    Input<TypeFunction> input_casted(input.message_context(), input.stack(),
                                     node_casted);
    return on_leave_type_function(input_casted);
  } else if (auto node_casted = try_cast_node<TypeStructured>(input.node());
             node_casted) {
    Input<TypeStructured> input_casted(input.message_context(), input.stack(),
                                       node_casted);
    return on_leave_type_structured(input_casted);
  } else if (auto node_casted = try_cast_node<TypeSymbol>(input.node());
             node_casted) {
    Input<TypeSymbol> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_leave_type_symbol(input_casted);
  } else if (auto node_casted = try_cast_node<TypeUnary>(input.node());
             node_casted) {
    Input<TypeUnary> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_type_unary(input_casted);
  } else if (auto node_casted = try_cast_node<TypeWithBitWidth>(input.node());
             node_casted) {
    Input<TypeWithBitWidth> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_leave_type_with_bit_width(input_casted);
  } else if (auto node_casted = try_cast_node<ValueBinary>(input.node());
             node_casted) {
    Input<ValueBinary> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_leave_value_binary(input_casted);
  } else if (auto node_casted = try_cast_node<ValueCall>(input.node());
             node_casted) {
    Input<ValueCall> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_value_call(input_casted);
  } else if (auto node_casted = try_cast_node<ValueCast>(input.node());
             node_casted) {
    Input<ValueCast> input_casted(input.message_context(), input.stack(),
                                  node_casted);
    return on_leave_value_cast(input_casted);
  } else if (auto node_casted = try_cast_node<ValueLiteralBool>(input.node());
             node_casted) {
    Input<ValueLiteralBool> input_casted(input.message_context(), input.stack(),
                                         node_casted);
    return on_leave_value_literal_bool(input_casted);
  } else if (auto node_casted = try_cast_node<ValueLiteralNumber>(input.node());
             node_casted) {
    Input<ValueLiteralNumber> input_casted(input.message_context(),
                                           input.stack(), node_casted);
    return on_leave_value_literal_number(input_casted);
  } else if (auto node_casted = try_cast_node<ValueSymbol>(input.node());
             node_casted) {
    Input<ValueSymbol> input_casted(input.message_context(), input.stack(),
                                    node_casted);
    return on_leave_value_symbol(input_casted);
  } else if (auto node_casted = try_cast_node<ValueUnary>(input.node());
             node_casted) {
    Input<ValueUnary> input_casted(input.message_context(), input.stack(),
                                   node_casted);
    return on_leave_value_unary(input_casted);
  } else {
    LT_ABORT("unsupported node kind " << input.node()->kind.name());
  }
}

lt::IHandler::Output IForgeHandler::on_enter_type_basic(Input<TypeBasic>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_type_basic(Input<TypeBasic>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_type_with_bit_width(
    Input<TypeWithBitWidth>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_type_with_bit_width(
    Input<TypeWithBitWidth>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_type_symbol(Input<TypeSymbol>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_type_symbol(Input<TypeSymbol>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_type_unary(Input<TypeUnary>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_type_unary(Input<TypeUnary>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_type_function(
    Input<TypeFunction>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_type_function(
    Input<TypeFunction>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_type_structured(
    Input<TypeStructured>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_type_structured(
    Input<TypeStructured>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_literal_bool(
    Input<ValueLiteralBool>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_literal_bool(
    Input<ValueLiteralBool>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_literal_number(
    Input<ValueLiteralNumber>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_literal_number(
    Input<ValueLiteralNumber>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_symbol(Input<ValueSymbol>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_symbol(Input<ValueSymbol>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_unary(Input<ValueUnary>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_unary(Input<ValueUnary>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_binary(Input<ValueBinary>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_binary(Input<ValueBinary>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_call(Input<ValueCall>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_call(Input<ValueCall>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_value_cast(Input<ValueCast>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_value_cast(Input<ValueCast>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_statement_basic(
    Input<StatementBasic>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_statement_basic(
    Input<StatementBasic>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_statement_value(
    Input<StatementValue>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_statement_value(
    Input<StatementValue>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_statement_if(Input<StatementIf>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_statement_if(Input<StatementIf>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_statement_while(
    Input<StatementWhile>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_statement_while(
    Input<StatementWhile>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_statement_block(
    Input<StatementBlock>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_statement_block(
    Input<StatementBlock>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_declaration_variable(
    Input<DeclarationVariable>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_declaration_function(
    Input<DeclarationFunction>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_declaration_function(
    Input<DeclarationFunction>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_declaration_structured_type(
    Input<DeclarationStructuredType>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_declaration_structured_type(
    Input<DeclarationStructuredType>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_declaration_type_alias(
    Input<DeclarationTypeAlias>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_declaration_type_alias(
    Input<DeclarationTypeAlias>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_declaration_namespace(
    Input<DeclarationNamespace>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_declaration_namespace(
    Input<DeclarationNamespace>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_enter_translation_unit(
    Input<TranslationUnit>&) {
  return Output();
}

lt::IHandler::Output IForgeHandler::on_leave_translation_unit(
    Input<TranslationUnit>&) {
  return Output();
}
}  // namespace forge
