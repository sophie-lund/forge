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
#include <forge/language/type_logic/type_predicates.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
TypeValidationHandler::TypeValidationHandler(
    const CodegenContext& codegen_context)
    : IForgeHandler(), _codegen_context(codegen_context) {}

IHandler::Output TypeValidationHandler::on_leave_type_unary(
    Input<TypeUnary>& input) {
  if (input.node()->type_unary_kind == TypeUnaryKind::pointer) {
    if (is_type_void(input.node()->operand_type)) {
      emit_type_error_no_void_pointers(
          input.message_context(), *input.node()->operand_type->source_range);
    } else if (input.node()->operand_type->kind == NODE_TYPE_FUNCTION) {
      emit_type_error_no_function_pointers(
          input.message_context(), *input.node()->operand_type->source_range);
    }
  } else {
    FRG_ABORT("unexpected unary type kind");
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_type_function(
    Input<TypeFunction>& input) {
  for (const std::shared_ptr<BaseType>& arg_type : input.node()->arg_types) {
    if (arg_type->kind == NODE_TYPE_BASIC) {
      if (is_type_void(arg_type)) {
        emit_type_error_no_void_arguments(input.message_context(),
                                          *arg_type->source_range);
      }
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_symbol(
    Input<ValueSymbol>& input) {
  if (input.node()->referenced_declaration &&
      input.node()->referenced_declaration->kind ==
          NODE_DECLARATION_NAMESPACE) {
    emit_type_error_namespace_used_as_value(input.message_context(),
                                            *input.node()->source_range);
  } else if (input.node()->resolved_type &&
             is_type_void(input.node()->resolved_type)) {
    emit_type_error_unexpected_type(
        input.message_context(), *input.node()->source_range, "non-void type");
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_unary(
    Input<ValueUnary>& input) {
  FRG_ASSERT(input.node()->operand != nullptr,
             "operand must not be null - node is not well "
             "formed, was WellFormedValidationHandler run?");

  switch (input.node()->operator_) {
    case UnaryOperator::bool_not:
      if (!is_type_bool(input.node()->operand->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "bool");
      }

      break;
    case UnaryOperator::bit_not:
      if (input.node()->operand->resolved_type &&
          !is_type_integer(input.node()->operand->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "integer type");
      }

      break;
    case UnaryOperator::pos:
    case UnaryOperator::neg:
      if (input.node()->operand->resolved_type &&
          !is_type_number(input.node()->operand->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "numeric type");
      }

      break;
    case UnaryOperator::deref:
      if (input.node()->operand->resolved_type &&
          !is_type_pointer(input.node()->operand->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->operand->source_range,
                                        "pointer type");
      }

      break;
    case UnaryOperator::getaddr:
      if (input.node()->operand->kind == NODE_VALUE_SYMBOL) {
        // You can get the address of a symbol
        break;
      }

      if (auto operand_casted =
              try_cast_node<ValueBinary>(input.node()->operand);
          operand_casted) {
        if (operand_casted->operator_ == BinaryOperator::member_access) {
          // You can get the address of the result of a member access
          break;
        }
      }

      emit_type_error_unexpected_type(input.message_context(),
                                      *input.node()->operand->source_range,
                                      "l-value reference");

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
      if (!is_type_bool(input.node()->lhs->resolved_type)) {
        emit_type_error_unexpected_type(
            input.message_context(), *input.node()->lhs->source_range, "bool");
      }

      if (!is_type_bool(input.node()->rhs->resolved_type)) {
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
      if (!is_type_integer(input.node()->lhs->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->lhs->source_range,
                                        "integer type");
      }

      if (!is_type_integer(input.node()->rhs->resolved_type)) {
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
      if (!is_type_number(input.node()->lhs->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->lhs->source_range,
                                        "numeric type");
      }

      if (!is_type_number(input.node()->rhs->resolved_type)) {
        emit_type_error_unexpected_type(input.message_context(),
                                        *input.node()->rhs->source_range,
                                        "numeric type");
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
      if (input.node()->lhs->kind == NODE_VALUE_SYMBOL) {
        // You can get the address of a symbol
        break;
      }

      if (auto lhs_casted = try_cast_node<ValueBinary>(input.node()->lhs);
          lhs_casted) {
        if (lhs_casted->operator_ == BinaryOperator::member_access) {
          // You can get the address of the result of a member access
          break;
        }
      }

      emit_type_error_unexpected_type(input.message_context(),
                                      *input.node()->lhs->source_range,
                                      "l-value reference");

      break;

    // Member access
    case BinaryOperator::member_access:
      // The type resolution handler should have already checked this
      break;
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_call(
    Input<ValueCall>& input) {
  auto callee_type_casted =
      try_cast_node<TypeFunction>(input.node()->callee->resolved_type);

  if (!callee_type_casted) {
    emit_type_error_cannot_call_non_function(
        input.message_context(), *input.node()->callee->source_range);
  }

  if (input.node()->args.size() != callee_type_casted->arg_types.size()) {
    emit_type_error_incorrect_number_of_args(
        input.message_context(), *input.node()->source_range,
        callee_type_casted->arg_types.size(), input.node()->args.size());

    return Output();
  }

  for (size_t i = 0; i < input.node()->args.size(); i++) {
    if (get_casting_mode(
            _codegen_context.get(), input.node()->args[i]->resolved_type,
            callee_type_casted->arg_types[i]) != CastingMode::implicit) {
      emit_type_error_unable_to_implicitly_cast(
          input.message_context(), *input.node()->args[i]->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_value_cast(
    Input<ValueCast>& input) {
  if (get_casting_mode(_codegen_context.get(),
                       input.node()->value->resolved_type,
                       input.node()->type) == CastingMode::illegal) {
    emit_type_error_illegal_cast(input.message_context(),
                                 *input.node()->source_range);
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_basic(
    Input<StatementBasic>& input) {
  if (input.node()->statement_basic_kind == StatementBasicKind::return_void) {
    auto current_function =
        input.try_get_directly_surrounding<DeclarationFunction>();

    if (current_function == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), input.node(),
          "return statement cannot be used outside of the context of a "
          "function declaration");
      return Output();
    }

    if (!is_type_void(current_function->return_type)) {
      emit_type_error_non_void_function_must_return_value(
          input.message_context(), *input.node()->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_value(
    Input<StatementValue>& input) {
  if (input.node()->statement_value_kind == StatementValueKind::return_) {
    auto current_function =
        input.try_get_directly_surrounding<DeclarationFunction>();

    if (current_function == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), input.node(),
          "return statement cannot be used outside of the context of a "
          "function declaration");
      return Output();
    }

    if (is_type_void(current_function->return_type)) {
      emit_type_error_void_function_cannot_return_value(
          input.message_context(), *input.node()->source_range);
      return Output();
    }

    if (get_casting_mode(
            _codegen_context.get(), input.node()->value->resolved_type,
            current_function->return_type) != CastingMode::implicit) {
      emit_type_error_unable_to_implicitly_cast(
          input.message_context(), *input.node()->value->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_if(
    Input<StatementIf>& input) {
  if (is_type_bool(input.node()->condition->resolved_type)) {
    emit_type_error_unexpected_type(input.message_context(),
                                    *input.node()->condition->source_range,
                                    "bool");
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_statement_while(
    Input<StatementWhile>& input) {
  if (is_type_bool(input.node()->condition->resolved_type)) {
    emit_type_error_unexpected_type(input.message_context(),
                                    *input.node()->condition->source_range,
                                    "bool");
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>& input) {
  if (is_type_void(input.node()->type)) {
    emit_type_error_unexpected_type(input.message_context(),
                                    *input.node()->type->source_range,
                                    "non-void type");
  }

  if (input.node()->initial_value) {
    if (get_casting_mode(_codegen_context.get(),
                         input.node()->initial_value->resolved_type,
                         input.node()->type) != CastingMode::implicit) {
      emit_type_error_unable_to_implicitly_cast(
          input.message_context(), *input.node()->initial_value->source_range);
    }
  }

  return Output();
}

IHandler::Output TypeValidationHandler::on_leave_declaration_structured_type(
    Input<DeclarationStructuredType>& input) {
  for (const std::shared_ptr<BaseDeclaration>& member : input.node()->members) {
    FRG_ASSERT(member != nullptr,
               "member is null - node is not well formed, was "
               "WellFormedValidationHandler run?");

    if (member->kind == NODE_DECLARATION_NAMESPACE) {
      emit_type_error_namespace_within_structured_type(input.message_context(),
                                                       *member->source_range);
    }
  }

  return Output();
}
}  // namespace forge
