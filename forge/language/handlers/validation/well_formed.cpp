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
IHandler::Output WellFormedValidationHandler::on_enter(Input&) {
  return Output();
}

IHandler::Output WellFormedValidationHandler::on_leave(Input& input) {
  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_TYPE_BASIC) {
    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TYPE_WITH_BIT_WIDTH) {
    const TypeWithBitWidth& casted =
        static_cast<const TypeWithBitWidth&>(*input.node());

    if (casted.type_with_bit_width_kind == TypeWithBitWidthKind::signed_int ||
        casted.type_with_bit_width_kind == TypeWithBitWidthKind::unsigned_int) {
      if (casted.bit_width != 8 && casted.bit_width != 16 &&
          casted.bit_width != 32 && casted.bit_width != 64) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            std::format("invalid bit width for integer: {}", casted.bit_width))
            .child(std::nullopt, SEVERITY_NOTE, "valid are 8, 16, 32, and 64");
        return Output();
      }
    } else if (casted.type_with_bit_width_kind ==
               TypeWithBitWidthKind::float_) {
      if (casted.bit_width != 32 && casted.bit_width != 64) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            std::format("invalid bit width for float: {}", casted.bit_width))
            .child(std::nullopt, SEVERITY_NOTE, "valid are 32 and 64");
        return Output();
      }
    } else {
      abort();  // this should never happen
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TYPE_SYMBOL) {
    const TypeSymbol& casted = static_cast<const TypeSymbol&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TYPE_UNARY) {
    const TypeUnary& casted = static_cast<const TypeUnary&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted,
                                 "operand_type", casted.operand_type,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    } else if (casted.operand_type->kind == NODE_TYPE_FUNCTION) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "unary type cannot have function operand type");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TYPE_FUNCTION) {
    const TypeFunction& casted =
        static_cast<const TypeFunction&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "return_type",
                                 casted.return_type,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "arg_types", casted.arg_types,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_LITERAL_BOOL) {
    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_LITERAL_NUMBER) {
    const ValueLiteralNumber& casted =
        static_cast<const ValueLiteralNumber&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "type",
                                 casted.type,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_SYMBOL) {
    const ValueSymbol& casted = static_cast<const ValueSymbol&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_UNARY) {
    const ValueUnary& casted = static_cast<const ValueUnary&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "operand",
                                 casted.operand,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_BINARY) {
    const ValueBinary& casted = static_cast<const ValueBinary&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "lhs",
                                 casted.lhs,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_not_null(input.message_context(), casted, "rhs",
                                 casted.rhs,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (casted.operator_ == BinaryOperator::member_access) {
      if (casted.rhs->kind != NODE_VALUE_SYMBOL) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "member access operator must have a symbol on the right");
        return Output();
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_CAST) {
    const ValueCast& casted = static_cast<const ValueCast&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "value",
                                 casted.value,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_not_null(input.message_context(), casted, "type",
                                 casted.type,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_CALL) {
    const ValueCall& casted = static_cast<const ValueCall&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "callee",
                                 casted.callee,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "args", casted.args,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_BASIC) {
    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_VALUE) {
    const StatementValue& casted =
        static_cast<const StatementValue&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "value",
                                 casted.value,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_BLOCK) {
    const StatementBlock& casted =
        static_cast<const StatementBlock&>(*input.node());

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "statements", casted.statements,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_IF) {
    const StatementIf& casted = static_cast<const StatementIf&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "condition",
                                 casted.condition,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_not_null(input.message_context(), casted, "then",
                                 casted.then,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (casted.else_ != nullptr && casted.else_->kind != NODE_STATEMENT_BLOCK &&
        casted.else_->kind != NODE_STATEMENT_IF) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "if statement else block must be a block or another if");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_WHILE) {
    const StatementWhile& casted =
        static_cast<const StatementWhile&>(*input.node());

    if (!validate_child_not_null(input.message_context(), casted, "condition",
                                 casted.condition,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_not_null(input.message_context(), casted, "body",
                                 casted.body,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
    const DeclarationVariable& casted =
        static_cast<const DeclarationVariable&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_FUNCTION) {
    const DeclarationFunction& casted =
        static_cast<const DeclarationFunction&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "args", casted.args,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_STRUCTURED_TYPE) {
    const DeclarationStructuredType& casted =
        static_cast<const DeclarationStructuredType&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "members", casted.members,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "inherits", casted.inherits,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_TYPE_ALIAS) {
    const DeclarationTypeAlias& casted =
        static_cast<const DeclarationTypeAlias&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_not_null(input.message_context(), casted, "type",
                                 casted.type,
                                 message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_NAMESPACE) {
    const DeclarationNamespace& casted =
        static_cast<const DeclarationNamespace&>(*input.node());

    if (!validate_string_not_empty(
            input.message_context(), casted, "name", casted.name,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "members", casted.members,
            message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TRANSLATION_UNIT) {
    const TranslationUnit& casted =
        static_cast<const TranslationUnit&>(*input.node());

    if (!validate_child_vector_not_null(
            input.message_context(), casted, "declarations",
            casted.declarations, message_code_error_internal_not_well_formed)) {
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else {
    abort();  // this should never happen
  }

  // -----------------------------------------------------------------
}
}  // namespace forge
