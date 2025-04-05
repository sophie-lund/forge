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

#include <forge/language/forge_message_emitters.hpp>
#include <forge/language/handlers/validation/well_formed.hpp>
#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/declarations/declaration_namespace.hpp>
#include <forge/language/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forge/language/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/language/syntax_tree/statements/statement_block.hpp>
#include <forge/language/syntax_tree/statements/statement_if.hpp>
#include <forge/language/syntax_tree/statements/statement_value.hpp>
#include <forge/language/syntax_tree/statements/statement_while.hpp>
#include <forge/language/syntax_tree/translation_unit.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_function.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/syntax_tree/values/value_binary.hpp>
#include <forge/language/syntax_tree/values/value_call.hpp>
#include <forge/language/syntax_tree/values/value_cast.hpp>
#include <forge/language/syntax_tree/values/value_literal_number.hpp>
#include <forge/language/syntax_tree/values/value_symbol.hpp>
#include <forge/language/syntax_tree/values/value_unary.hpp>
#include <forge/syntax_tree/operations/validators.hpp>

namespace forge {
IHandler::Output WellFormedValidationHandler::on_leave_type_with_bit_width(
    Input<TypeWithBitWidth>& input) {
  // If the type is an integer
  if (input.node()->type_with_bit_width_kind ==
          TypeWithBitWidthKind::signed_int ||
      input.node()->type_with_bit_width_kind ==
          TypeWithBitWidthKind::unsigned_int) {
    // Make sure the bit width is one that is supported
    if (input.node()->bit_width != 8 && input.node()->bit_width != 16 &&
        input.node()->bit_width != 32 && input.node()->bit_width != 64) {
      emit_internal_error_not_well_formed(
          input.message_context(), *input.node(),
          std::format("invalid bit width for integer: {}",
                      input.node()->bit_width))
          .child(std::nullopt, SEVERITY_NOTE, "valid are 8, 16, 32, and 64");
      return Output(VisitorStatus::halt_traversal);
    }
  }

  // If the type is a float
  else if (input.node()->type_with_bit_width_kind ==
           TypeWithBitWidthKind::float_) {
    // Make sure the bit width is one that is supported
    if (input.node()->bit_width != 32 && input.node()->bit_width != 64) {
      emit_internal_error_not_well_formed(
          input.message_context(), *input.node(),
          std::format("invalid bit width for float: {}",
                      input.node()->bit_width))
          .child(std::nullopt, SEVERITY_NOTE, "valid are 32 and 64");
      return Output(VisitorStatus::halt_traversal);
    }
  }

  // Otherwise
  else {
    FRG_ABORT("unsupported kind");
  }

  return Output();
}

IHandler::Output WellFormedValidationHandler::on_leave_type_symbol(
    Input<TypeSymbol>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output();
}

IHandler::Output WellFormedValidationHandler::on_leave_type_unary(
    Input<TypeUnary>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(),
                               "operand_type", input.node()->operand_type,
                               message_code_error_internal_not_well_formed)) {
  } else if (input.node()->operand_type->kind == NODE_TYPE_FUNCTION) {
    emit_internal_error_not_well_formed(
        input.message_context(), *input.node(),
        "unary type cannot have function operand type");
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_type_function(
    Input<TypeFunction>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(),
                               "return_type", input.node()->return_type,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "arg_types",
          input.node()->arg_types,
          message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_type_structured(
    Input<TypeStructured>& input) {
  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "members",
          input.node()->members, message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  for (const std::shared_ptr<DeclarationVariable>& member :
       input.node()->members) {
    if (!validate_child_not_null(input.message_context(), *input.node(), "type",
                                 member->type,
                                 message_code_error_internal_not_well_formed)) {
      return Output(VisitorStatus::halt_traversal);
    }

    if (!validate_child_null(input.message_context(), *input.node(),
                             "initial_value", member->initial_value,
                             message_code_error_internal_not_well_formed)) {
      return Output(VisitorStatus::halt_traversal);
    }
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_value_literal_number(
    Input<ValueLiteralNumber>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(), "type",
                               input.node()->type,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_value_symbol(
    Input<ValueSymbol>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_value_unary(
    Input<ValueUnary>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(),
                               "operand", input.node()->operand,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_value_binary(
    Input<ValueBinary>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(), "lhs",
                               input.node()->lhs,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_not_null(input.message_context(), *input.node(), "rhs",
                               input.node()->rhs,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (input.node()->operator_ == BinaryOperator::member_access) {
    if (input.node()->rhs->kind != NODE_VALUE_SYMBOL) {
      emit_internal_error_not_well_formed(
          input.message_context(), *input.node(),
          "member access operator must have a symbol on the right");
      return Output(VisitorStatus::halt_traversal);
    }
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_value_call(
    Input<ValueCall>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(), "callee",
                               input.node()->callee,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "args", input.node()->args,
          message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_value_cast(
    Input<ValueCast>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(), "value",
                               input.node()->value,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_not_null(input.message_context(), *input.node(), "type",
                               input.node()->type,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_statement_value(
    Input<StatementValue>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(), "value",
                               input.node()->value,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_statement_if(
    Input<StatementIf>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(),
                               "condition", input.node()->condition,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_not_null(input.message_context(), *input.node(), "then",
                               input.node()->then,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (input.node()->else_ != nullptr &&
      input.node()->else_->kind != NODE_STATEMENT_BLOCK &&
      input.node()->else_->kind != NODE_STATEMENT_IF) {
    emit_internal_error_not_well_formed(
        input.message_context(), *input.node(),
        "if statement else block must be a block or another if");
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_statement_while(
    Input<StatementWhile>& input) {
  if (!validate_child_not_null(input.message_context(), *input.node(),
                               "condition", input.node()->condition,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_not_null(input.message_context(), *input.node(), "body",
                               input.node()->body,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_statement_block(
    Input<StatementBlock>& input) {
  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "statements",
          input.node()->statements,
          message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_declaration_function(
    Input<DeclarationFunction>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "args", input.node()->args,
          message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output
WellFormedValidationHandler::on_leave_declaration_structured_type(
    Input<DeclarationStructuredType>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "members",
          input.node()->members, message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "inherits",
          input.node()->inherits,
          message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_declaration_type_alias(
    Input<DeclarationTypeAlias>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_not_null(input.message_context(), *input.node(), "type",
                               input.node()->type,
                               message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_declaration_namespace(
    Input<DeclarationNamespace>& input) {
  if (!validate_string_not_empty(input.message_context(), *input.node(), "name",
                                 input.node()->name,
                                 message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "members",
          input.node()->members, message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}

IHandler::Output WellFormedValidationHandler::on_leave_translation_unit(
    Input<TranslationUnit>& input) {
  if (!validate_child_vector_not_null(
          input.message_context(), *input.node(), "declarations",
          input.node()->declarations,
          message_code_error_internal_not_well_formed)) {
    return Output(VisitorStatus::halt_traversal);
  }

  return Output(VisitorStatus::halt_traversal);
}
}  // namespace forge
