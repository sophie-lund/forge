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

#pragma once

#include <forgec/syntax_tree/declarations/declaration_function.hpp>
#include <forgec/syntax_tree/statements/statement_basic.hpp>
#include <forgec/syntax_tree/statements/statement_block.hpp>
#include <forgec/syntax_tree/statements/statement_declaration.hpp>
#include <forgec/syntax_tree/statements/statement_if.hpp>
#include <forgec/syntax_tree/statements/statement_value.hpp>
#include <forgec/syntax_tree/statements/statement_while.hpp>
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/messaging/message_context.hpp>

namespace forge {
/**
 * @brief Options to pass in to statement generators in order to facilitate
 * control flow codegen.
 */
struct CodegenStatementOptions {
  /**
   * @brief The current syntax tree function in which we are generating code.
   *
   * This will always be non-null.
   */
  std::shared_ptr<DeclarationFunction> surrounding_function;

  /**
   * @brief The current LLVM function in which we are generating code.
   *
   * This will always be non-null.
   */
  llvm::Function* llvm_surrounding_function;

  /**
   * @brief The current LLVM basic block in which we are generating code at the
   * start of the statement.
   *
   * This is equivalent to the current basic block the LLVM builder is inserting
   * into.
   *
   * This will always be non-null.
   */
  llvm::BasicBlock* llvm_basic_block_start;

  /**
   * @brief The LLVM basic block that is represents the surrounding loop body.
   *
   * This will only be non-null if the current statement is within a loop body.
   * This is used for @c continue statements.
   */
  llvm::BasicBlock* llvm_basic_block_loop_body;

  /**
   * @brief The LLVM basic block that is comes right after the surrounding loop.
   *
   * This will only be non-null if the current statement is within a loop body.
   * This is used for @c break statements.
   */
  llvm::BasicBlock* llvm_basic_block_after_loop;
};

/**
 * @brief The result of codegenning a statement.
 *
 * This is used to facilitate control flow codegen.
 */
struct CodegenStatementResult {
  /**
   * @brief The LLVM basic block that is the end of the statement.
   *
   * This is equivalent to the basic block the LLVM builder is inserting into
   * after generating the statement.
   *
   * @warning This may be null if the statement terminates the current basic
   * block.
   */
  llvm::BasicBlock* llvm_basic_block_end;
};

CodegenStatementResult codegen_statement_basic(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementBasic>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_value(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementValue>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_declaration(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementDeclaration>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_block(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementBlock>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_if(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementIf>& node, CodegenStatementOptions options);

CodegenStatementResult codegen_statement_while(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<StatementWhile>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<BaseStatement>& node,
    CodegenStatementOptions options);
}  // namespace forge
