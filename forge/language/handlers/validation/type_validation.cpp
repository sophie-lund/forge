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
#include <forge/language/handlers/validation/type_validation.hpp>
#include <forge/language/type_logic/get_casting_mode.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
IHandler::Output TypeValidationHandler::on_leave_type_unary(
    Input<TypeUnary>& input) {
  if (is_type_basic_with_kind(*input.node()->operand_type,
                              TypeBasicKind::void_)) {
    emit_type_error_no_void_pointers(input.message_context(),
                                     *input.node()->operand_type->source_range);
  } else if (input.node()->operand_type->kind == NODE_TYPE_FUNCTION) {
    emit_type_error_no_function_pointers(
        input.message_context(), *input.node()->operand_type->source_range);
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_type_function(
    Input<TypeFunction>& input) {
  for (const std::shared_ptr<BaseType>& arg_type : input.node()->arg_types) {
    if (arg_type->kind == NODE_TYPE_BASIC) {
      if (is_type_basic_with_kind(*arg_type, TypeBasicKind::void_)) {
        emit_type_error_no_void_arguments(input.message_context(),
                                          *arg_type->source_range);
      }
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_unary(
    Input<ValueUnary>& input) {
  switch (input.node()->operator_) {
    case UnaryOperator::bool_not:
      if (!is_type_basic_with_kind(*input.node()->operand->resolved_type,
                                   TypeBasicKind::bool_)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "bool");
      }
      break;
    case UnaryOperator::bit_not:
      if (input.node()->operand->resolved_type->kind !=
              NODE_TYPE_WITH_BIT_WIDTH ||
          static_cast<const TypeWithBitWidth&>(
              *input.node()->operand->resolved_type)
                  .type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "integer type");
      }
      break;
    case UnaryOperator::pos:
    case UnaryOperator::neg:
      if (input.node()->operand->resolved_type->kind !=
          NODE_TYPE_WITH_BIT_WIDTH) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "numeric type");
      }
      break;
    case UnaryOperator::deref:
      abort();  // TODO: implement this
      break;
    case UnaryOperator::getaddr:
      abort();  // TODO: implement this
      break;
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_binary(
    Input<ValueBinary>& input) {
  switch (input.node()->operator_) {
    // Boolean only
    case BinaryOperator::bool_and:
    case BinaryOperator::bool_or:
      if (!is_type_basic_with_kind(*input.node()->lhs->resolved_type,
                                   TypeBasicKind::bool_)) {
        emit_type_error_unexpected_type(
            input.message_context(), *input.node()->lhs->source_range, "bool");
      }

      if (!is_type_basic_with_kind(*input.node()->rhs->resolved_type,
                                   TypeBasicKind::bool_)) {
        emit_type_error_unexpected_type(
            input.message_context(), *input.node()->rhs->source_range, "bool");
      }

      break;

    // Integer only
    case BinaryOperator::bit_and:
    case BinaryOperator::bit_or:
    case BinaryOperator::bit_xor:
    case BinaryOperator::bit_shl:
    case BinaryOperator::bit_shr:
      if (!is_type_integer(*input.node()->lhs->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->lhs->source_range,
                                        "integer type");
      }

      if (!is_type_integer(*input.node()->rhs->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->rhs->source_range,
                                        "integer type");
      }

      break;

    // Numeric only
    case BinaryOperator::add:
    case BinaryOperator::sub:
    case BinaryOperator::mul:
    case BinaryOperator::exp:
    case BinaryOperator::div:
    case BinaryOperator::mod:
    case BinaryOperator::eq:
    case BinaryOperator::ne:
    case BinaryOperator::lt:
    case BinaryOperator::le:
    case BinaryOperator::gt:
    case BinaryOperator::ge:
      if (input.node()->lhs->resolved_type->kind != NODE_TYPE_WITH_BIT_WIDTH) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->lhs->source_range,
                                        "integer type");
      }

      if (input.node()->rhs->resolved_type->kind != NODE_TYPE_WITH_BIT_WIDTH) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->rhs->source_range,
                                        "integer type");
      }

      break;

    // Assignment
    case BinaryOperator::bit_and_assign:
    case BinaryOperator::bit_or_assign:
    case BinaryOperator::bit_xor_assign:
    case BinaryOperator::bit_shl_assign:
    case BinaryOperator::bit_shr_assign:
    case BinaryOperator::add_assign:
    case BinaryOperator::sub_assign:
    case BinaryOperator::mul_assign:
    case BinaryOperator::exp_assign:
    case BinaryOperator::div_assign:
    case BinaryOperator::mod_assign:
    case BinaryOperator::assign:
      abort();  // TODO: implement this
      break;

    // Member access
    case BinaryOperator::member_access:
      abort();  // TODO: implement this
      break;
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_call(
    Input<ValueCall>& input) {
  if (input.node()->callee->resolved_type->kind != NODE_TYPE_FUNCTION) {
    emit_type_error_cannot_call_non_function(
        input.message_context(), *input.node()->callee->source_range);
  }

  const TypeFunction& callee_type =
      static_cast<const TypeFunction&>(*input.node()->callee->resolved_type);

  if (input.node()->args.size() != callee_type.arg_types.size()) {
    emit_type_error_incorrect_number_of_args(
        input.message_context(), *input.node()->source_range,
        callee_type.arg_types.size(), input.node()->args.size());
    return Output();
  }

  for (size_t i = 0; i < input.node()->args.size(); i++) {
    if (get_casting_mode(input.node()->args[i]->resolved_type,
                         callee_type.arg_types[i]) != CastingMode::implicit) {
      emit_type_error_unable_to_implicitly_cast(
          input.message_context(), *input.node()->args[i]->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_cast(
    Input<ValueCast>& input) {
  if (get_casting_mode(input.node()->value->resolved_type,
                       input.node()->type) == CastingMode::illegal) {
    emit_type_error_illegal_cast(input.message_context(),
                                 *input.node()->source_range);
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_basic(
    Input<StatementBasic>& input) {
  if (input.node()->statement_basic_kind == StatementBasicKind::return_void) {
    const DeclarationFunction* current_function = get_current_function(input);

    if (current_function == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), *input.node(),
          "return statement cannot be used outside of the context of a "
          "function declaration");
      return Output();
    }

    if (!is_type_basic_with_kind(*current_function->return_type,
                                 TypeBasicKind::void_)) {
      emit_type_error_non_void_function_must_return_value(
          input.message_context(), *input.node()->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_value(
    Input<StatementValue>& input) {
  if (input.node()->statement_value_kind == StatementValueKind::return_) {
    const DeclarationFunction* current_function = get_current_function(input);

    if (current_function == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), *input.node(),
          "return statement cannot be used outside of the context of a "
          "function declaration");
      return Output();
    }

    if (is_type_basic_with_kind(*current_function->return_type,
                                TypeBasicKind::void_)) {
      emit_type_error_void_function_cannot_return_value(
          input.message_context(), *input.node()->source_range);
      return Output();
    }

    if (get_casting_mode(input.node()->value->resolved_type,
                         current_function->return_type) !=
        CastingMode::implicit) {
      emit_type_error_unable_to_implicitly_cast(
          input.message_context(), *input.node()->value->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_if(
    Input<StatementIf>& input) {
  if (is_type_basic_with_kind(*input.node()->condition->resolved_type,
                              TypeBasicKind::bool_)) {
    emit_type_error_unexpected_type(input.message_context(),
                                    *input.node()->condition->source_range,
                                    "bool");
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_while(
    Input<StatementWhile>& input) {
  if (is_type_basic_with_kind(*input.node()->condition->resolved_type,
                              TypeBasicKind::bool_)) {
    emit_type_error_unexpected_type(input.message_context(),
                                    *input.node()->condition->source_range,
                                    "bool");
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>& input) {
  if (is_type_basic_with_kind(*input.node()->type, TypeBasicKind::void_)) {
    emit_type_error_unexpected_type(input.message_context(),
                                    *input.node()->type->source_range,
                                    "non-void type");
  }

  if (input.node()->initial_value) {
    if (get_casting_mode(input.node()->initial_value->resolved_type,
                         input.node()->type) == CastingMode::illegal) {
      emit_type_error_illegal_cast(input.message_context(),
                                   *input.node()->initial_value->source_range);
    }
  }

  return Output();
}
}  // namespace forge
