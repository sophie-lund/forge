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
#include <forge/language/handlers/validation/type_resolution.hpp>
#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
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
#include <forge/language/type_logic/get_arithmetic_containing_type.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
IHandler::Output TypeResolutionHandler::on_enter(Input&) { return Output(); }

IHandler::Output TypeResolutionHandler::on_leave(Input& input) {
  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_LITERAL_BOOL) {
    ValueLiteralBool& casted = static_cast<ValueLiteralBool&>(*input.node());

    casted.resolved_type =
        std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_LITERAL_NUMBER) {
    ValueLiteralNumber& casted =
        static_cast<ValueLiteralNumber&>(*input.node());

    casted.resolved_type = clone_node(casted.type);

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_SYMBOL) {
    ValueSymbol& casted = static_cast<ValueSymbol&>(*input.node());

    if (casted.referenced_declaration) {
      casted.resolved_type =
          clone_node(casted.referenced_declaration->resolved_type);
    }

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_UNARY) {
    ValueUnary& casted = static_cast<ValueUnary&>(*input.node());

    switch (casted.operator_) {
      case UnaryOperator::bool_not:
        casted.resolved_type =
            std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
        break;
      case UnaryOperator::bit_not:
      case UnaryOperator::pos:
      case UnaryOperator::neg:
        casted.resolved_type = clone_node(casted.operand->resolved_type);
        break;
      case UnaryOperator::deref:
        if (casted.operand->resolved_type &&
            is_type_unary_with_kind(*casted.operand->resolved_type,
                                    TypeUnaryKind::pointer)) {
          casted.resolved_type = clone_node(
              try_get_type_unary_operand(*casted.operand->resolved_type));
        }
        break;
      case UnaryOperator::getaddr:
        if (casted.operand->resolved_type) {
          casted.resolved_type = std::make_shared<TypeUnary>(
              SourceRange(), TypeUnaryKind::pointer,
              clone_node(casted.operand->resolved_type));
        }
        break;
    }

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_BINARY) {
    ValueBinary& casted = static_cast<ValueBinary&>(*input.node());

    switch (casted.operator_) {
      case BinaryOperator::bool_and:
      case BinaryOperator::bool_or:
      case BinaryOperator::eq:
      case BinaryOperator::ne:
      case BinaryOperator::lt:
      case BinaryOperator::le:
      case BinaryOperator::gt:
      case BinaryOperator::ge:
        casted.resolved_type =
            std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
        break;
      case BinaryOperator::bit_and:
      case BinaryOperator::bit_or:
      case BinaryOperator::bit_xor:
      case BinaryOperator::add:
      case BinaryOperator::sub:
      case BinaryOperator::mul:
      case BinaryOperator::div:
      case BinaryOperator::mod:
        if (casted.lhs->resolved_type && casted.rhs->resolved_type) {
          casted.resolved_type = get_arithmetic_containing_type(
              casted.lhs->resolved_type, casted.rhs->resolved_type);
        }
        break;
      case BinaryOperator::bit_and_assign:
      case BinaryOperator::bit_or_assign:
      case BinaryOperator::bit_xor_assign:
      case BinaryOperator::bit_shl:
      case BinaryOperator::bit_shl_assign:
      case BinaryOperator::bit_shr:
      case BinaryOperator::bit_shr_assign:
      case BinaryOperator::add_assign:
      case BinaryOperator::sub_assign:
      case BinaryOperator::mul_assign:
      case BinaryOperator::exp:
      case BinaryOperator::exp_assign:
      case BinaryOperator::div_assign:
      case BinaryOperator::mod_assign:
      case BinaryOperator::assign:
        casted.resolved_type = clone_node(casted.lhs->resolved_type);
        break;
      case BinaryOperator::member_access:
        abort();  // TODO: implement this
        break;
    }

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_CAST) {
    ValueCast& casted = static_cast<ValueCast&>(*input.node());

    casted.resolved_type = clone_node(casted.type);

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_VALUE_CALL) {
    ValueCall& casted = static_cast<ValueCall&>(*input.node());

    if (casted.callee->resolved_type &&
        casted.callee->resolved_type->kind == NODE_TYPE_FUNCTION) {
      const TypeFunction& callee_type_casted =
          static_cast<const TypeFunction&>(*casted.callee->resolved_type);

      casted.resolved_type = clone_node(callee_type_casted.return_type);
    }

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
    DeclarationVariable& casted =
        static_cast<DeclarationVariable&>(*input.node());

    casted.resolved_type = clone_node(casted.type);

    return Output();
  }

  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_DECLARATION_FUNCTION) {
    DeclarationFunction& casted =
        static_cast<DeclarationFunction&>(*input.node());

    std::shared_ptr<TypeFunction> resolved_type =
        std::make_shared<TypeFunction>(
            SourceRange(), clone_node(casted.return_type),
            std::vector<std::shared_ptr<BaseType>>());

    for (const std::shared_ptr<DeclarationVariable>& arg : casted.args) {
      resolved_type->arg_types.push_back(clone_node(arg->resolved_type));
    }

    casted.resolved_type = resolved_type;

    return Output();
  }

  // -----------------------------------------------------------------

  else {
    return Output();
  }

  // -----------------------------------------------------------------
}
}  // namespace forge
