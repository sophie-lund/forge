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
#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/language/syntax_tree/statements/statement_basic.hpp>
#include <forge/language/syntax_tree/statements/statement_if.hpp>
#include <forge/language/syntax_tree/statements/statement_value.hpp>
#include <forge/language/syntax_tree/statements/statement_while.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_function.hpp>
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
#include <forge/language/type_logic/get_casting_mode.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
IHandler::Output TypeValidationHandler::on_enter(Input&) { return Output(); }

IHandler::Output TypeValidationHandler::on_leave(Input& input) {
  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_TYPE_UNARY) {
    const TypeUnary& casted = static_cast<const TypeUnary&>(*input.node());

    if (is_type_basic_with_kind(*casted.operand_type, TypeBasicKind::void_)) {
      emit_type_error_no_void_pointers(input.message_context(),
                                       *casted.operand_type->source_range);
    } else if (casted.operand_type->kind == NODE_TYPE_FUNCTION) {
      emit_type_error_no_function_pointers(input.message_context(),
                                           *casted.operand_type->source_range);
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TYPE_FUNCTION) {
    const TypeFunction& casted =
        static_cast<const TypeFunction&>(*input.node());

    for (const std::shared_ptr<BaseType>& arg_type : casted.arg_types) {
      if (arg_type->kind == NODE_TYPE_BASIC) {
        if (is_type_basic_with_kind(*arg_type, TypeBasicKind::void_)) {
          emit_type_error_no_void_arguments(input.message_context(),
                                            *arg_type->source_range);
        }
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_UNARY) {
    const ValueUnary& casted = static_cast<const ValueUnary&>(*input.node());

    switch (casted.operator_) {
      case UnaryOperator::bool_not:
        if (!is_type_basic_with_kind(*casted.operand->resolved_type,
                                     TypeBasicKind::bool_)) {
          emit_type_error_unexpected_type(
              input.message_context(), *casted.operand->source_range, "bool");
        }
        break;
      case UnaryOperator::bit_not:
        if (casted.operand->resolved_type->kind != NODE_TYPE_WITH_BIT_WIDTH ||
            static_cast<const TypeWithBitWidth&>(*casted.operand->resolved_type)
                    .type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.operand->source_range,
                                          "integer type");
        }
        break;
      case UnaryOperator::pos:
      case UnaryOperator::neg:
        if (casted.operand->resolved_type->kind != NODE_TYPE_WITH_BIT_WIDTH) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.operand->source_range,
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

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_BINARY) {
    const ValueBinary& casted = static_cast<const ValueBinary&>(*input.node());

    switch (casted.operator_) {
      // Boolean only
      case BinaryOperator::bool_and:
      case BinaryOperator::bool_or:
        if (!is_type_basic_with_kind(*casted.lhs->resolved_type,
                                     TypeBasicKind::bool_)) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.lhs->source_range, "bool");
        }

        if (!is_type_basic_with_kind(*casted.rhs->resolved_type,
                                     TypeBasicKind::bool_)) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.rhs->source_range, "bool");
        }

        break;

      // Integer only
      case BinaryOperator::bit_and:
      case BinaryOperator::bit_or:
      case BinaryOperator::bit_xor:
      case BinaryOperator::bit_shl:
      case BinaryOperator::bit_shr:
        if (!is_type_integer(*casted.lhs->resolved_type)) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.lhs->source_range,
                                          "integer type");
        }

        if (!is_type_integer(*casted.rhs->resolved_type)) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.rhs->source_range,
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
        if (casted.lhs->resolved_type->kind != NODE_TYPE_WITH_BIT_WIDTH) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.lhs->source_range,
                                          "integer type");
        }

        if (casted.rhs->resolved_type->kind != NODE_TYPE_WITH_BIT_WIDTH) {
          emit_type_error_unexpected_type(input.message_context(),
                                          *casted.rhs->source_range,
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

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_CAST) {
    const ValueCast& casted = static_cast<const ValueCast&>(*input.node());

    if (get_casting_mode(casted.value->resolved_type, casted.type) ==
        CastingMode::illegal) {
      emit_type_error_illegal_cast(input.message_context(),
                                   *casted.source_range);
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_CALL) {
    const ValueCall& casted = static_cast<const ValueCall&>(*input.node());

    if (casted.callee->resolved_type->kind != NODE_TYPE_FUNCTION) {
      emit_type_error_cannot_call_non_function(input.message_context(),
                                               *casted.callee->source_range);
    }

    const TypeFunction& callee_type =
        static_cast<const TypeFunction&>(*casted.callee->resolved_type);

    if (casted.args.size() != callee_type.arg_types.size()) {
      emit_type_error_incorrect_number_of_args(
          input.message_context(), *casted.source_range,
          callee_type.arg_types.size(), casted.args.size());
      return Output();
    }

    for (size_t i = 0; i < casted.args.size(); i++) {
      if (get_casting_mode(casted.args[i]->resolved_type,
                           callee_type.arg_types[i]) != CastingMode::implicit) {
        emit_type_error_unable_to_implicitly_cast(
            input.message_context(), *casted.args[i]->source_range);
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_BASIC) {
    const StatementBasic& casted =
        static_cast<const StatementBasic&>(*input.node());

    if (casted.statement_basic_kind == StatementBasicKind::return_void) {
      const DeclarationFunction* current_function = get_current_function(input);

      if (current_function == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "return statement cannot be used outside of the context of a "
            "function declaration");
        return Output();
      }

      if (!is_type_basic_with_kind(*current_function->return_type,
                                   TypeBasicKind::void_)) {
        emit_type_error_non_void_function_must_return_value(
            input.message_context(), *casted.source_range);
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_VALUE) {
    const StatementValue& casted =
        static_cast<const StatementValue&>(*input.node());

    if (casted.statement_value_kind == StatementValueKind::return_) {
      const DeclarationFunction* current_function = get_current_function(input);

      if (current_function == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "return statement cannot be used outside of the context of a "
            "function declaration");
        return Output();
      }

      if (is_type_basic_with_kind(*current_function->return_type,
                                  TypeBasicKind::void_)) {
        emit_type_error_void_function_cannot_return_value(
            input.message_context(), *casted.source_range);
        return Output();
      }

      if (get_casting_mode(casted.value->resolved_type,
                           current_function->return_type) !=
          CastingMode::implicit) {
        emit_type_error_unable_to_implicitly_cast(input.message_context(),
                                                  *casted.value->source_range);
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_IF) {
    const StatementIf& casted = static_cast<const StatementIf&>(*input.node());

    if (is_type_basic_with_kind(*casted.condition->resolved_type,
                                TypeBasicKind::bool_)) {
      emit_type_error_unexpected_type(input.message_context(),
                                      *casted.condition->source_range, "bool");
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_WHILE) {
    const StatementWhile& casted =
        static_cast<const StatementWhile&>(*input.node());

    if (is_type_basic_with_kind(*casted.condition->resolved_type,
                                TypeBasicKind::bool_)) {
      emit_type_error_unexpected_type(input.message_context(),
                                      *casted.condition->source_range, "bool");
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
    const DeclarationVariable& casted =
        static_cast<const DeclarationVariable&>(*input.node());

    if (is_type_basic_with_kind(*casted.type, TypeBasicKind::void_)) {
      emit_type_error_unexpected_type(
          input.message_context(), *casted.type->source_range, "non-void type");
    }

    if (casted.initial_value) {
      if (get_casting_mode(casted.initial_value->resolved_type, casted.type) ==
          CastingMode::illegal) {
        emit_type_error_illegal_cast(input.message_context(),
                                     *casted.initial_value->source_range);
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else {
    return Output();
  }

  // -----------------------------------------------------------------
}

const DeclarationFunction* TypeValidationHandler::get_current_function(
    Input& input) {
  for (auto i = input.stack().rbegin(); i != input.stack().rend(); i++) {
    if (i->get().kind == NODE_DECLARATION_FUNCTION) {
      return &static_cast<const DeclarationFunction&>(i->get());
    }
  }

  return nullptr;
}
}  // namespace forge
