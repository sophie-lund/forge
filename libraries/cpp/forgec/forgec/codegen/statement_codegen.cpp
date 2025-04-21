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

#include <forgec/codegen/statement_codegen.hpp>
#include <forgec/codegen/type_codegen.hpp>
#include <forgec/codegen/value_codegen.hpp>
#include <langtools/syntax_tree/operations/casting.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>

namespace forge {
CodegenStatementResult codegen_statement_basic(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementBasic>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  switch (node->statement_basic_kind) {
    case StatementBasicKind::continue_:
      LT_ASSERT(options.llvm_basic_block_loop_body != nullptr,
                "cannot codegen continue outside of loop");

      codegen_context.llvm_builder().CreateBr(
          options.llvm_basic_block_loop_body);

      return {.llvm_basic_block_end = nullptr};
    case StatementBasicKind::break_:
      LT_ASSERT(options.llvm_basic_block_after_loop != nullptr,
                "cannot codegen continue outside of loop");

      codegen_context.llvm_builder().CreateBr(
          options.llvm_basic_block_after_loop);

      return {.llvm_basic_block_end = nullptr};
    case StatementBasicKind::return_void:
      LT_ASSERT(options.llvm_basic_block_start != nullptr,
                "options.basic_block_start must be non-null");

      codegen_context.llvm_builder().CreateRetVoid();

      return {.llvm_basic_block_end = nullptr};
  }
}

CodegenStatementResult codegen_statement_value(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementValue>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(options.llvm_basic_block_start != nullptr,
            "options.basic_block_start must be non-null");

  switch (node->statement_value_kind) {
    case StatementValueKind::execute:
      codegen_value(codegen_context, node->value);

      return {.llvm_basic_block_end = options.llvm_basic_block_start};
    case StatementValueKind::return_: {
      LT_ASSERT(options.surrounding_function != nullptr,
                "options.surrounding_function must be non-null");

      LT_ASSERT(options.surrounding_function->resolved_type != nullptr,
                ""
                "surrounding function must have a resolved type");

      auto surrounding_function_type_casted = try_cast_node<TypeFunction>(
          options.surrounding_function->resolved_type);

      LT_ASSERT(surrounding_function_type_casted != nullptr,
                "surrounding function must be a function type");

      LT_ASSERT(surrounding_function_type_casted->return_type != nullptr,
                "surrounding function must have a resolved return type");

      codegen_context.llvm_builder().CreateRet(codegen_value_implicit_cast(
          codegen_context, node->value,
          surrounding_function_type_casted->return_type));

      return {.llvm_basic_block_end = nullptr};
    }
  }
}

CodegenStatementResult codegen_statement_declaration(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementDeclaration>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  auto declaration_variable =
      try_cast_node<DeclarationVariable>(node->declaration);
  LT_ASSERT(
      declaration_variable != nullptr,
      "cannot codegen declaration within a function unless it is a variable");
  LT_ASSERT(declaration_variable->type != nullptr,
            "cannot codegen variable "
            "declaration with null type");

  llvm::Type* llvm_type =
      codegen_type(codegen_context, declaration_variable->type);

  declaration_variable->llvm_value =
      codegen_context.llvm_builder().CreateAlloca(llvm_type, nullptr,
                                                  declaration_variable->name);

  if (declaration_variable->initial_value != nullptr) {
    codegen_context.llvm_builder().CreateStore(
        codegen_value_implicit_cast(codegen_context,
                                    declaration_variable->initial_value,
                                    declaration_variable->type),
        declaration_variable->llvm_value);
  }

  return {.llvm_basic_block_end = options.llvm_basic_block_start};
}

CodegenStatementResult codegen_statement_block(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementBlock>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");
  LT_ASSERT(options.llvm_basic_block_start != nullptr,
            "options.basic_block_start must be non-null");

  llvm::BasicBlock* llvm_basic_block_current = options.llvm_basic_block_start;

  for (const std::shared_ptr<BaseStatement>& statement : node->statements) {
    LT_ASSERT(statement != nullptr, "cannot codegen null statement in block");

    LT_ASSERT(llvm_basic_block_current != nullptr,
              "previous statement generated a termination instruction in the "
              "current basic block but there are more statements left to "
              "codegen in the current syntax tree block");

    CodegenStatementResult result = codegen_statement(
        codegen_context, statement,
        {
            .surrounding_function = options.surrounding_function,
            .llvm_surrounding_function = options.llvm_surrounding_function,
            .llvm_basic_block_start = llvm_basic_block_current,
            .llvm_basic_block_loop_body = options.llvm_basic_block_loop_body,
            .llvm_basic_block_after_loop = options.llvm_basic_block_after_loop,
        });

    llvm_basic_block_current = result.llvm_basic_block_end;
  }

  return {
      .llvm_basic_block_end = llvm_basic_block_current,
  };
}

CodegenStatementResult codegen_statement_if(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementIf>& node, CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  // Case 1: no else clause, then clause is unterminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then and after
  //   - Generate a conditional branch to the then block or after block in the
  //     current block
  //   - Generate the then block
  //   - Generate a jump to the after block at the end of the then block
  //   - Return the after block for continued codegen
  //
  // Case 2: no else clause, then clause is terminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //     return;
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then and after
  //   - Generate a conditional branch to the then block or after block in the
  //     current block
  //   - Generate the then block
  //   - Return the after block for continued codegen
  //
  // Case 3: else clause, then clause is unterminated, else clause is
  //         unterminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //   } else {
  //     // do other stuff
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then, else, and after
  //   - Generate a conditional branch to the then block or else block in the
  //     current block
  //   - Generate the then block
  //   - Generate a jump to the after block at the end of the then block
  //   - Generate the else block
  //   - Generate a jump to the after block at the end of the else block
  //   - Return the after block for continued codegen
  //
  // Case 4: else clause, then clause is unterminated, else clause is
  //         terminated
  // -------------------------------------------------------------------------
  //
  //   if (condition) {
  //     // do stuff
  //   } else {
  //     // do other stuff
  //     return;
  //   }
  //
  //   // do more stuff
  //
  // Codegen strategy:
  //   - Create basic blocks for then, else, and after
  //   - Generate a conditional branch to the then block or else block in the
  //     current block
  //   - Generate the then block
  //   - Generate a jump to the after block at the end of the then block
  //   - Generate the else block
  //   - Generate a jump to the after block at the end of the else block
  //   - Return the after block for continued codegen

  // Create basic blocks
  llvm::BasicBlock* llvm_basic_block_then =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "then",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_else =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "else",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_after =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "after",
                               options.llvm_surrounding_function);

  // Generate the conditional branch
  if (node->else_ == nullptr) {
    codegen_context.llvm_builder().CreateCondBr(
        codegen_value(codegen_context, node->condition), llvm_basic_block_then,
        llvm_basic_block_after);
  } else {
    codegen_context.llvm_builder().CreateCondBr(
        codegen_value(codegen_context, node->condition), llvm_basic_block_then,
        llvm_basic_block_else);
  }

  // Generate the then block
  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_then);

  CodegenStatementResult result_then = codegen_statement(
      codegen_context, node->then,
      {
          .surrounding_function = options.surrounding_function,
          .llvm_surrounding_function = options.llvm_surrounding_function,
          .llvm_basic_block_start = llvm_basic_block_then,
          .llvm_basic_block_loop_body = options.llvm_basic_block_loop_body,
          .llvm_basic_block_after_loop = options.llvm_basic_block_after_loop,
      });

  // Optionally generate a jump to the after block if the then block is not
  // terminated
  if (result_then.llvm_basic_block_end != nullptr &&
      result_then.llvm_basic_block_end->getTerminator() == nullptr) {
    codegen_context.llvm_builder().CreateBr(llvm_basic_block_after);
  }

  // Optionally generate the else block
  if (node->else_) {
    codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_else);

    CodegenStatementResult result_else = codegen_statement(
        codegen_context, node->else_,
        {
            .surrounding_function = options.surrounding_function,
            .llvm_surrounding_function = options.llvm_surrounding_function,
            .llvm_basic_block_start = llvm_basic_block_else,
            .llvm_basic_block_loop_body = options.llvm_basic_block_loop_body,
            .llvm_basic_block_after_loop = options.llvm_basic_block_after_loop,
        });

    // Optionally generate a jump to the after block if the else block is not
    // terminated
    if (result_else.llvm_basic_block_end != nullptr &&
        result_else.llvm_basic_block_end->getTerminator() == nullptr) {
      codegen_context.llvm_builder().CreateBr(llvm_basic_block_after);
    }
  }

  // Set the insert point to the after block
  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_after);

  // Clean up empty blocks
  if (llvm_basic_block_else->empty() &&
      llvm::pred_empty(llvm_basic_block_else)) {
    llvm_basic_block_else->eraseFromParent();
  }

  if (llvm_basic_block_after->empty() &&
      llvm::pred_empty(llvm_basic_block_after)) {
    llvm_basic_block_after->eraseFromParent();
  }

  // If all branches were terminated, return no basic block
  if (llvm::pred_empty(llvm_basic_block_after)) {
    return {
        .llvm_basic_block_end = nullptr,
    };
  }

  // Otherwise, return the after block
  return {
      .llvm_basic_block_end = llvm_basic_block_after,
  };
}

CodegenStatementResult codegen_statement_while(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementWhile>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  llvm::BasicBlock* llvm_basic_block_body =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "body",
                               options.llvm_surrounding_function);
  llvm::BasicBlock* llvm_basic_block_after =
      llvm::BasicBlock::Create(codegen_context.llvm_context(), "after",
                               options.llvm_surrounding_function);

  codegen_context.llvm_builder().CreateCondBr(
      codegen_value(codegen_context, node->condition), llvm_basic_block_body,
      llvm_basic_block_after);

  codegen_context.llvm_builder().SetInsertPoint(llvm_basic_block_body);

  CodegenStatementResult result_body = codegen_statement(
      codegen_context, node->body,
      {
          .surrounding_function = options.surrounding_function,
          .llvm_surrounding_function = options.llvm_surrounding_function,
          .llvm_basic_block_start = llvm_basic_block_body,
          .llvm_basic_block_loop_body = llvm_basic_block_body,
          .llvm_basic_block_after_loop = llvm_basic_block_after,
      });

  if (result_body.llvm_basic_block_end != nullptr &&
      result_body.llvm_basic_block_end->getTerminator() == nullptr) {
    codegen_context.llvm_builder().CreateCondBr(
        codegen_value(codegen_context, node->condition), llvm_basic_block_body,
        llvm_basic_block_after);
  }

  return {.llvm_basic_block_end = llvm_basic_block_after};
}

CodegenStatementResult codegen_statement(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<BaseStatement>& node,
    CodegenStatementOptions options) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  if (auto casted = try_cast_node<StatementBasic>(node); casted) {
    return codegen_statement_basic(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementValue>(node); casted) {
    return codegen_statement_value(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementDeclaration>(node); casted) {
    return codegen_statement_declaration(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementBlock>(node); casted) {
    return codegen_statement_block(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementIf>(node); casted) {
    return codegen_statement_if(codegen_context, casted, options);
  } else if (auto casted = try_cast_node<StatementWhile>(node); casted) {
    return codegen_statement_while(codegen_context, casted, options);
  } else {
    LT_ABORT("unknown statement kind");
  }
}
}  // namespace forge
