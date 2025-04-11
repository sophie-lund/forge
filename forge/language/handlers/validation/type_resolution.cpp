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

#include <forge/core/tracing.hpp>
#include <forge/language/forge_formatters.hpp>
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
#include <forge/language/type_logic/type_predicates.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>

namespace forge {
namespace {
template <typename TNodePointer>
void _trace_type_resolution(const TNodePointer& node_pointer) {
  if (node_pointer->resolved_type) {
    trace("TypeResolutionHandler") << "resolved type to: ";
    format_type(FormattingOptions(trace_stream()), node_pointer->resolved_type);
    trace_stream() << std::endl;
  } else {
    trace("TypeResolutionHandler")
        << "unable to resolve type - referenced declaration not resolved"
        << std::endl;
  }
}
}  // namespace

TypeResolutionHandler::TypeResolutionHandler(
    const CodegenContext& codegen_context)
    : IForgeHandler(), _codegen_context(codegen_context) {}

IHandler::Output TypeResolutionHandler::on_leave_value_literal_bool(
    Input<ValueLiteralBool>& input) {
  input.node()->resolved_type =
      std::make_shared<TypeBasic>(SourceRange(), TypeBasicKind::bool_);

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_literal_number(
    Input<ValueLiteralNumber>& input) {
  FRG_ASSERT(input.node()->type != nullptr,
             "value literal number must have a type - node is not well formed, "
             "was WellFormedValidationHandler run?");

  input.node()->resolved_type = clone_node(input.node()->type);

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_symbol(
    Input<ValueSymbol>& input) {
  if (input.node()->referenced_declaration) {
    input.node()->resolved_type =
        clone_node(input.node()->referenced_declaration->resolved_type);
  }

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_unary(
    Input<ValueUnary>& input) {
  FRG_ASSERT(input.node()->operand != nullptr,
             "operand is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

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
          is_type_pointer(input.node()->operand->resolved_type)) {
        input.node()->resolved_type = clone_node(
            try_get_pointer_element_type(input.node()->operand->resolved_type));
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

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_binary(
    Input<ValueBinary>& input) {
  FRG_ASSERT(input.node()->lhs != nullptr,
             "lhs is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

  FRG_ASSERT(input.node()->rhs != nullptr,
             "rhs is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

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
            _codegen_context.get(), input.node()->lhs->resolved_type,
            input.node()->rhs->resolved_type);
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
      if (auto lhs_type_casted =
              try_cast_node<TypeStructured>(input.node()->lhs->resolved_type);
          lhs_type_casted != nullptr) {
        auto rhs_casted = try_cast_node<ValueSymbol>(input.node()->rhs);

        FRG_ASSERT(rhs_casted != nullptr,
                   "rhs is not a value symbol - node is not well formed, was "
                   "WellFormedValidationHandler run?");

        for (const std::shared_ptr<BaseDeclaration>& member :
             lhs_type_casted->members) {
          if (member != nullptr && member->name == rhs_casted->name) {
            input.node()->resolved_type = clone_node(member->resolved_type);
            break;
          }
        }

        emit_type_error_no_member_with_name(input.message_context(),
                                            input.node()->rhs->source_range);
      } else {
        emit_type_error_unexpected_type(input.message_context(),
                                        input.node()->lhs->source_range,
                                        "structured type");
      }

      break;
  }

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_call(
    Input<ValueCall>& input) {
  FRG_ASSERT(input.node()->callee != nullptr,
             "callee is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

  if (input.node()->callee->resolved_type) {
    if (auto callee_type_casted =
            try_cast_node<TypeFunction>(input.node()->callee->resolved_type);
        callee_type_casted != nullptr) {
      input.node()->resolved_type = clone_node(callee_type_casted->return_type);
    }
  }

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_value_cast(
    Input<ValueCast>& input) {
  FRG_ASSERT(input.node()->type != nullptr,
             "type is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

  input.node()->resolved_type = clone_node(input.node()->type);

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_variable(
    Input<DeclarationVariable>& input) {
  input.node()->resolved_type = clone_node(input.node()->type);

  if (input.node()->resolved_type == nullptr && input.node()->initial_value &&
      input.node()->initial_value->resolved_type) {
    input.node()->resolved_type =
        clone_node(input.node()->initial_value->resolved_type);
  }

  if (input.node()->resolved_type == nullptr) {
    emit_type_error_unable_to_resolve(input.message_context(),
                                      input.node()->type->source_range);
  }

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_function(
    Input<DeclarationFunction>& input) {
  FRG_ASSERT(input.node()->return_type != nullptr,
             "return type is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

  std::shared_ptr<TypeFunction> resolved_type = std::make_shared<TypeFunction>(
      SourceRange(), clone_node(input.node()->return_type),
      std::vector<std::shared_ptr<BaseType>>());

  for (const std::shared_ptr<DeclarationVariable>& arg : input.node()->args) {
    FRG_ASSERT(arg != nullptr,
               "arg is null - node is not well formed, was "
               "WellFormedValidationHandler run?");

    auto arg_type = clone_node(arg->resolved_type);

    if (arg_type == nullptr) {
      emit_type_error_unable_to_resolve(input.message_context(),
                                        arg->source_range);
    }

    resolved_type->arg_types.push_back(std::move(arg_type));
  }

  input.node()->resolved_type = resolved_type;

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_type_alias(
    Input<DeclarationTypeAlias>& input) {
  FRG_ASSERT(input.node()->type != nullptr,
             "type is null - node is not well formed, was "
             "WellFormedValidationHandler run?");

  input.node()->resolved_type = clone_node(input.node()->type);

  _trace_type_resolution(input.node());

  return Output();
}

IHandler::Output TypeResolutionHandler::on_leave_declaration_structured_type(
    Input<DeclarationStructuredType>& input) {
  std::unordered_map<std::string, std::shared_ptr<BaseDeclaration>> members;

  for (const std::shared_ptr<TypeSymbol>& parent : input.node()->inherits) {
    if (auto parent_casted = try_cast_node<DeclarationStructuredType>(
            parent->referenced_declaration);
        parent_casted != nullptr) {
      if (auto parent_type_casted =
              try_cast_node<TypeStructured>(parent_casted->resolved_type);
          parent_type_casted != nullptr) {
        for (const std::shared_ptr<BaseDeclaration>& member :
             parent_type_casted->members) {
          FRG_ASSERT(member != nullptr,
                     "member is null - node is not well formed, was "
                     "WellFormedValidationHandler run?");

          if (!members.emplace(member->name, member).second) {
            emit_scope_error_member_shadows_inherited(input.message_context(),
                                                      member->source_range);
          }
        }
      }
    }
  }

  for (const std::shared_ptr<BaseDeclaration>& member : input.node()->members) {
    FRG_ASSERT(member != nullptr,
               "member is null - node is not well formed, was "
               "WellFormedValidationHandler run?");

    if (!members
             .emplace(member->name,
                      std::make_shared<DeclarationVariable>(
                          SourceRange(), std::string(member->name),
                          clone_node(member->resolved_type), nullptr))
             .second) {
      emit_scope_error_member_shadows_inherited(input.message_context(),
                                                member->source_range);
    }
  }

  auto resolved_type = std::make_shared<TypeStructured>(
      SourceRange(), std::vector<std::shared_ptr<BaseDeclaration>>());

  for (const auto& [name, member] : members) {
    if (member != nullptr) {
      resolved_type->members.push_back(clone_node(member));
    }
  }

  input.node()->resolved_type = resolved_type;

  _trace_type_resolution(input.node());

  return Output();
}
}  // namespace forge
