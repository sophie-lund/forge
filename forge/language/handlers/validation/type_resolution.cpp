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
IHandler::Output TypeResolutionHandler::on_leave_value_literal_bool(
    Input<ValueLiteralBool>& input) {
  input.node()->resolved_type =
      std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_literal_number(
    Input<ValueLiteralNumber>& input) {
  input.node()->resolved_type = clone_node(input.node()->type);
  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_symbol(
    Input<ValueSymbol>& input) {
  if (input.node()->referenced_declaration) {
    input.node()->resolved_type =
        clone_node(input.node()->referenced_declaration->resolved_type);
  }

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_unary(
    Input<ValueUnary>& input) {
  switch (input.node()->operator_) {
    case UnaryOperator::bool_not:
      input.node()->resolved_type =
          std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);
      break;
    case UnaryOperator::bit_not:
    case UnaryOperator::pos:
    case UnaryOperator::neg:
      input.node()->resolved_type =
          clone_node(input.node()->operand->resolved_type);
      break;
    case UnaryOperator::deref:
      if (input.node()->operand->resolved_type &&
          is_type_unary_with_kind(*input.node()->operand->resolved_type,
                                  TypeUnaryKind::pointer)) {
        input.node()->resolved_type = clone_node(
            try_get_type_unary_operand(*input.node()->operand->resolved_type));
      }
      break;
    case UnaryOperator::getaddr:
      if (input.node()->operand->resolved_type) {
        input.node()->resolved_type = std::make_shared<TypeUnary>(
            SourceRange(), TypeUnaryKind::pointer,
            clone_node(input.node()->operand->resolved_type));
      }
      break;
  }

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_binary(
    Input<ValueBinary>& input) {
  switch (input.node()->operator_) {
    case BinaryOperator::bool_and:
    case BinaryOperator::bool_or:
    case BinaryOperator::eq:
    case BinaryOperator::ne:
    case BinaryOperator::lt:
    case BinaryOperator::le:
    case BinaryOperator::gt:
    case BinaryOperator::ge:
      input.node()->resolved_type =
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
      if (input.node()->lhs->resolved_type &&
          input.node()->rhs->resolved_type) {
        input.node()->resolved_type = get_arithmetic_containing_type(
            input.node()->lhs->resolved_type, input.node()->rhs->resolved_type);
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
      input.node()->resolved_type =
          clone_node(input.node()->lhs->resolved_type);
      break;
    case BinaryOperator::member_access:
      abort();  // TODO: implement this
      break;
  }

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_call(
    Input<ValueCall>& input) {
  if (input.node()->callee->resolved_type &&
      input.node()->callee->resolved_type->kind == NODE_TYPE_FUNCTION) {
    const TypeFunction& callee_type_casted =
        static_cast<const TypeFunction&>(*input.node()->callee->resolved_type);

    input.node()->resolved_type = clone_node(callee_type_casted.return_type);
  }

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_cast(
    Input<ValueCast>& input) {
  input.node()->resolved_type = clone_node(input.node()->type);

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>& input) {
  input.node()->resolved_type = clone_node(input.node()->type);

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_function(
    Input<DeclarationFunction>& input) {
  std::shared_ptr<TypeFunction> resolved_type = std::make_shared<TypeFunction>(
      SourceRange(), clone_node(input.node()->return_type),
      std::vector<std::shared_ptr<BaseType>>());

  for (const std::shared_ptr<DeclarationVariable>& arg : input.node()->args) {
    resolved_type->arg_types.push_back(clone_node(arg->resolved_type));
  }

  input.node()->resolved_type = resolved_type;

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_type_alias(
    Input<DeclarationTypeAlias>& input) {
  input.node()->resolved_type = clone_node(input.node()->type);
  return Output();
}
}  // namespace forge
