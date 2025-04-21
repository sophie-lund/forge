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

#include <forgec/handlers/validation/control_flow_validation.hpp>
#include <forgec/messages/forge_message_emitters.hpp>

namespace forge {
ControlFlowValidationHandler::ControlFlowValidationHandler()
    : IForgeHandler() {}

lt::IHandler::Output ControlFlowValidationHandler::on_leave_statement_basic(
    Input<StatementBasic>& input) {
  if (input.node()->statement_basic_kind == StatementBasicKind::continue_ ||
      input.node()->statement_basic_kind == StatementBasicKind::break_) {
    input.node()->terminates_block = true;
    input.node()->terminates_function = false;
  } else if (input.node()->statement_basic_kind ==
             StatementBasicKind::return_void) {
    input.node()->terminates_block = true;
    input.node()->terminates_function = true;
  } else {
    LT_ABORT("unexpected statement basic kind");
  }

  return Output();
}

lt::IHandler::Output ControlFlowValidationHandler::on_leave_statement_value(
    Input<StatementValue>& input) {
  if (input.node()->statement_value_kind == StatementValueKind::execute) {
    input.node()->terminates_block = false;
    input.node()->terminates_function = false;
  } else if (input.node()->statement_value_kind ==
             StatementValueKind::return_) {
    input.node()->terminates_block = true;
    input.node()->terminates_function = true;
  } else {
    LT_ABORT("unexpected statement value kind");
  }

  return Output();
}

lt::IHandler::Output
ControlFlowValidationHandler::on_leave_statement_declaration(
    Input<StatementDeclaration>& input) {
  input.node()->terminates_block = false;
  input.node()->terminates_function = false;

  return Output();
}

lt::IHandler::Output ControlFlowValidationHandler::on_leave_statement_block(
    Input<StatementBlock>& input) {
  input.node()->terminates_block = false;
  input.node()->terminates_function = false;

  for (const std::shared_ptr<BaseStatement>& statement :
       input.node()->statements) {
    LT_ASSERT(statement != nullptr, "statement in block must not be null");

    if (input.node()->terminates_block.value() ||
        input.node()->terminates_function.value()) {
      emit_control_flow_error_unreachable_statement(input.message_context(),
                                                    statement->source_range);
      break;
    }

    LT_ASSERT(statement->terminates_block.has_value(),
              "statement should have terminates_block resolved");
    LT_ASSERT(statement->terminates_function.has_value(),
              "statement should have terminates_function resolved");

    if (statement->terminates_block.value()) {
      input.node()->terminates_block = true;
    }

    if (statement->terminates_function.value()) {
      input.node()->terminates_function = true;
    }
  }

  return Output();
}

lt::IHandler::Output ControlFlowValidationHandler::on_leave_statement_if(
    Input<StatementIf>& input) {
  // If there is no else, then by definition neither the statement or block can
  // be considered terminated
  if (input.node()->else_ == nullptr) {
    input.node()->terminates_block = false;
    input.node()->terminates_function = false;
    return Output();
  }

  LT_ASSERT(input.node()->then != nullptr, "then clause must not be null");
  LT_ASSERT(input.node()->then->terminates_block.has_value(),
            "then clause should have terminates_block resolved");
  LT_ASSERT(input.node()->then->terminates_function.has_value(),
            "then clause should have terminates_function resolved");
  LT_ASSERT(input.node()->else_->terminates_block.has_value(),
            "else clause should have terminates_block resolved");
  LT_ASSERT(input.node()->else_->terminates_function.has_value(),
            "else clause should have terminates_function resolved");

  input.node()->terminates_block =
      input.node()->then->terminates_block.value() &&
      input.node()->else_->terminates_block.value();
  input.node()->terminates_function =
      input.node()->then->terminates_function.value() &&
      input.node()->else_->terminates_function.value();

  return Output();
}

lt::IHandler::Output ControlFlowValidationHandler::on_leave_statement_while(
    Input<StatementWhile>& input) {
  LT_ASSERT(input.node()->body != nullptr, "body must not be null");
  LT_ASSERT(input.node()->body->terminates_block.has_value(),
            "loop body should have terminates_block resolved");
  LT_ASSERT(input.node()->body->terminates_function.has_value(),
            "loop body should have terminates_function resolved");

  // If it is a while true loop without any termination, then assume it is
  // terminating since it cannot be left
  if (auto casted = try_cast_node<ValueLiteralBool>(input.node()->condition);
      casted->value && !input.node()->body->terminates_block.value()) {
    input.node()->terminates_block = true;
    input.node()->terminates_function = true;
    return Output();
  }

  input.node()->terminates_block = false;
  input.node()->terminates_function =
      input.node()->body->terminates_function.value();

  return Output();
}

lt::IHandler::Output
ControlFlowValidationHandler::on_leave_declaration_function(
    Input<DeclarationFunction>& input) {
  // This check only applies to functions with bodies
  if (input.node()->body == nullptr) {
    return Output();
  }

  LT_ASSERT(input.node()->body->terminates_block.has_value(),
            "function body should have terminates_block resolved");
  LT_ASSERT(input.node()->body->terminates_function.has_value(),
            "function body should have terminates_function resolved");

  if (!input.node()->body->terminates_function.value()) {
    emit_control_flow_error_function_does_not_always_return(
        input.message_context(), input.node()->source_range);
  }

  return Output();
}
}  // namespace forge
