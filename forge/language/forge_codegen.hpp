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

#include <forge/codegen/codegen_context.hpp>
#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/declarations/declaration_namespace.hpp>
#include <forge/language/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forge/language/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/language/syntax_tree/statements/statement_basic.hpp>
#include <forge/language/syntax_tree/statements/statement_block.hpp>
#include <forge/language/syntax_tree/statements/statement_if.hpp>
#include <forge/language/syntax_tree/statements/statement_value.hpp>
#include <forge/language/syntax_tree/statements/statement_while.hpp>
#include <forge/language/syntax_tree/translation_unit.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_function.hpp>
#include <forge/language/syntax_tree/types/type_structured.hpp>
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
#include <forge/messaging/message_context.hpp>

namespace forge {
llvm::Type* codegen_type_basic(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node);

llvm::Type* codegen_type_with_bit_width(
    CodegenContext& codegen_context,
    const std::shared_ptr<TypeWithBitWidth>& node);

llvm::Type* codegen_type_symbol(CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node);

llvm::Type* codegen_type_unary(CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node);

llvm::FunctionType* codegen_type_function(
    CodegenContext& codegen_context, const std::shared_ptr<TypeFunction>& node);

llvm::StructType* codegen_type_structured(
    CodegenContext& codegen_context,
    const std::shared_ptr<TypeStructured>& node);

llvm::Type* codegen_type(CodegenContext& codegen_context,
                         const std::shared_ptr<BaseType>& node);

llvm::Value* codegen_value_literal_bool(
    CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralBool>& node);

llvm::Value* codegen_value_literal_number(
    CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralNumber>& node);

llvm::Value* codegen_value_symbol(CodegenContext&,
                                  const std::shared_ptr<ValueSymbol>& node);

llvm::Value* codegen_value_unary(CodegenContext& codegen_context,
                                 const std::shared_ptr<ValueUnary>& node);

llvm::Value* codegen_value_binary(CodegenContext& codegen_context,
                                  const std::shared_ptr<ValueBinary>& node);

llvm::Value* codegen_value_call(CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCall>& node);

llvm::Value* codegen_value_cast(CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCast>& node);

llvm::Value* codegen_value(CodegenContext& codegen_context,
                           const std::shared_ptr<BaseValue>& node);

struct CodegenStatementOptions {
  llvm::Function* llvm_surrounding_function;
  llvm::BasicBlock* llvm_basic_block_start;
  llvm::BasicBlock* llvm_basic_block_loop_body;
  llvm::BasicBlock* llvm_basic_block_after_loop;
};

struct CodegenStatementResult {
  llvm::BasicBlock* llvm_basic_block_end;
};

CodegenStatementResult codegen_statement_basic(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementBasic>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_value(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementValue>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_block(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementBlock>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_if(
    CodegenContext& codegen_context, const std::shared_ptr<StatementIf>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement_while(
    CodegenContext& codegen_context,
    const std::shared_ptr<StatementWhile>& node,
    CodegenStatementOptions options);

CodegenStatementResult codegen_statement(
    CodegenContext& codegen_context, const std::shared_ptr<BaseStatement>& node,
    CodegenStatementOptions options);

void codegen_declaration_variable(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationVariable>& node);

void codegen_declaration_function(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationFunction>& node);

void codegen_declaration_type_alias(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationTypeAlias>& node);

void codegen_declaration_structured_type(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationStructuredType>& node);

void codegen_declaration_namespace(
    CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationNamespace>& node);

void codegen_declaration(CodegenContext& codegen_context,
                         const std::shared_ptr<BaseDeclaration>& node);

void codegen_translation_unit(CodegenContext& codegen_context,
                              const std::shared_ptr<TranslationUnit>& node);
}  // namespace forge
