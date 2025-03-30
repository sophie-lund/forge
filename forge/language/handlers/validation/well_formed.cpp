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

    if (casted.kind == TypeWithBitWidthKind::signed_int ||
        casted.kind == TypeWithBitWidthKind::unsigned_int) {
      if (casted.bit_width != 8 && casted.bit_width != 16 &&
          casted.bit_width != 32 && casted.bit_width != 64) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            std::format("invalid bit width for integer: {}", casted.bit_width))
            .child(std::nullopt, SEVERITY_NOTE, "valid are 8, 16, 32, and 64");
        return Output();
      }
    } else if (casted.kind == TypeWithBitWidthKind::float_) {
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

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(input.message_context(), casted,
                                          "type name cannot be empty");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TYPE_UNARY) {
    const TypeUnary& casted = static_cast<const TypeUnary&>(*input.node());

    if (casted.operand_type == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "unary type must have a non-null operand type");
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

    if (casted.return_type == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "function type must have a non-null return type");
      return Output();
    }

    for (const std::shared_ptr<BaseType>& arg_type : casted.arg_types) {
      if (arg_type == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "function type must have non-null argument types");
        return Output();
      }
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

    if (casted.type == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "number literal cannot have a null type");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_SYMBOL) {
    const ValueSymbol& casted = static_cast<const ValueSymbol&>(*input.node());

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "symbol literal cannot have an empty name");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_UNARY) {
    const ValueUnary& casted = static_cast<const ValueUnary&>(*input.node());

    if (casted.operand == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "unary value cannot have a null operand");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_BINARY) {
    const ValueBinary& casted = static_cast<const ValueBinary&>(*input.node());

    if (casted.lhs == nullptr) {
      emit_internal_error_not_well_formed(input.message_context(), casted,
                                          "unary value cannot have a null lhs");
      return Output();
    }

    if (casted.rhs == nullptr) {
      emit_internal_error_not_well_formed(input.message_context(), casted,
                                          "unary value cannot have a null rhs");
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

    if (casted.value == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "unary value cannot have a null value");
      return Output();
    }

    if (casted.type == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "unary value cannot have a null type");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_VALUE_CALL) {
    const ValueCall& casted = static_cast<const ValueCall&>(*input.node());

    if (casted.callee == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "call value cannot have a null callee");
      return Output();
    }

    for (const std::shared_ptr<BaseValue>& arg : casted.args) {
      if (arg == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "call value cannot have null arguments");
        return Output();
      }
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

    if (casted.value == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "value statement cannot have a null value");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_BLOCK) {
    const StatementBlock& casted =
        static_cast<const StatementBlock&>(*input.node());

    for (const std::shared_ptr<BaseStatement>& statement : casted.statements) {
      if (statement == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "statement block cannot have null statements");
        return Output();
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_STATEMENT_IF) {
    const StatementIf& casted = static_cast<const StatementIf&>(*input.node());

    if (casted.condition == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "if statement cannot have a null condition");
      return Output();
    }

    if (casted.then == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "if statement cannot have a null then block");
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

    if (casted.condition == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "while statement cannot have a null condition");
      return Output();
    }

    if (casted.body == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "while statement cannot have a null body");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
    const DeclarationVariable& casted =
        static_cast<const DeclarationVariable&>(*input.node());

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "variable declaration cannot have an empty name");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_FUNCTION) {
    const DeclarationFunction& casted =
        static_cast<const DeclarationFunction&>(*input.node());

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "variable declaration cannot have an empty name");
      return Output();
    }

    for (const std::shared_ptr<DeclarationVariable>& arg : casted.args) {
      if (arg == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "function declaration cannot have null arguments");
        return Output();
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_STRUCTURED_TYPE) {
    const DeclarationStructuredType& casted =
        static_cast<const DeclarationStructuredType&>(*input.node());

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "structured type declaration cannot have an empty name");
      return Output();
    }

    for (const std::shared_ptr<BaseDeclaration>& member : casted.members) {
      if (member == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "structured type declaration cannot have null members");
        return Output();
      }
    }

    for (const std::shared_ptr<TypeSymbol>& inherit : casted.inherits) {
      if (inherit == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "structured type declaration cannot have null inherits");
        return Output();
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_TYPE_ALIAS) {
    const DeclarationTypeAlias& casted =
        static_cast<const DeclarationTypeAlias&>(*input.node());

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "type alias declaration cannot have an empty name");
      return Output();
    }

    if (casted.type == nullptr) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "type alias declaration cannot have a null type");
      return Output();
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_DECLARATION_NAMESPACE) {
    const DeclarationNamespace& casted =
        static_cast<const DeclarationNamespace&>(*input.node());

    if (casted.name.empty()) {
      emit_internal_error_not_well_formed(
          input.message_context(), casted,
          "namespace declaration cannot have an empty name");
      return Output();
    }

    for (const std::shared_ptr<BaseDeclaration>& member : casted.members) {
      if (member == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "namespace declaration cannot have null members");
        return Output();
      }
    }

    return Output();
  }

  // -----------------------------------------------------------------

  else if (input.node()->kind == NODE_TRANSLATION_UNIT) {
    const TranslationUnit& casted =
        static_cast<const TranslationUnit&>(*input.node());

    for (const std::shared_ptr<BaseDeclaration>& declaration :
         casted.declarations) {
      if (declaration == nullptr) {
        emit_internal_error_not_well_formed(
            input.message_context(), casted,
            "translation unit cannot have null declarations");
        return Output();
      }
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
