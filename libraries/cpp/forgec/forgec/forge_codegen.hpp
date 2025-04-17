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
#include <forgec/syntax_tree/declarations/declaration_namespace.hpp>
#include <forgec/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forgec/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forgec/syntax_tree/declarations/declaration_variable.hpp>
#include <forgec/syntax_tree/statements/statement_basic.hpp>
#include <forgec/syntax_tree/statements/statement_block.hpp>
#include <forgec/syntax_tree/statements/statement_if.hpp>
#include <forgec/syntax_tree/statements/statement_value.hpp>
#include <forgec/syntax_tree/statements/statement_while.hpp>
#include <forgec/syntax_tree/translation_unit.hpp>
#include <forgec/syntax_tree/types/type_basic.hpp>
#include <forgec/syntax_tree/types/type_function.hpp>
#include <forgec/syntax_tree/types/type_structured.hpp>
#include <forgec/syntax_tree/types/type_symbol.hpp>
#include <forgec/syntax_tree/types/type_unary.hpp>
#include <forgec/syntax_tree/types/type_with_bit_width.hpp>
#include <forgec/syntax_tree/values/value_binary.hpp>
#include <forgec/syntax_tree/values/value_call.hpp>
#include <forgec/syntax_tree/values/value_cast.hpp>
#include <forgec/syntax_tree/values/value_literal_bool.hpp>
#include <forgec/syntax_tree/values/value_literal_number.hpp>
#include <forgec/syntax_tree/values/value_symbol.hpp>
#include <forgec/syntax_tree/values/value_unary.hpp>
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/messaging/message_context.hpp>

namespace forge {
llvm::Type* codegen_type_basic(lt::CodegenContext& codegen_context,
                               const std::shared_ptr<TypeBasic>& node);

llvm::Type* codegen_type_basic_for_casting(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeBasic>& node);

llvm::Type* codegen_type_with_bit_width(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeWithBitWidth>& node);

llvm::Type* codegen_type_symbol(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<TypeSymbol>& node);

llvm::Type* codegen_type_unary(lt::CodegenContext& codegen_context,
                               const std::shared_ptr<TypeUnary>& node);

llvm::FunctionType* codegen_type_function(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeFunction>& node);

llvm::StructType* codegen_type_structured(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<TypeStructured>& node);

llvm::Type* codegen_type(lt::CodegenContext& codegen_context,
                         const std::shared_ptr<BaseType>& node);

llvm::Type* codegen_type_for_casting(lt::CodegenContext& codegen_context,
                                     const std::shared_ptr<BaseType>& node);

llvm::Value* codegen_value_literal_bool(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralBool>& node);

llvm::Value* codegen_value_literal_number(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<ValueLiteralNumber>& node);

llvm::Value* codegen_value_symbol(lt::CodegenContext&,
                                  const std::shared_ptr<ValueSymbol>& node);

llvm::Value* codegen_value_unary(lt::CodegenContext& codegen_context,
                                 const std::shared_ptr<ValueUnary>& node);

llvm::Value* codegen_value_binary(lt::CodegenContext& codegen_context,
                                  const std::shared_ptr<ValueBinary>& node);

llvm::Value* codegen_value_call(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCall>& node);

llvm::Value* codegen_value_cast(lt::CodegenContext& codegen_context,
                                const std::shared_ptr<ValueCast>& node);

llvm::Value* codegen_value(lt::CodegenContext& codegen_context,
                           const std::shared_ptr<BaseValue>& node);

llvm::Value* codegen_value_implicit_cast(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<BaseValue>& value,
    const std::shared_ptr<BaseType>& to);

struct CodegenStatementOptions {
  std::shared_ptr<DeclarationFunction> surrounding_function;
  llvm::Function* llvm_surrounding_function;
  llvm::BasicBlock* llvm_basic_block_start;
  llvm::BasicBlock* llvm_basic_block_loop_body;
  llvm::BasicBlock* llvm_basic_block_after_loop;
};

struct CodegenStatementResult {
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

void codegen_declaration_variable(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationVariable>& node);

void codegen_declaration_function(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationFunction>& node);

void codegen_declaration_type_alias(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationTypeAlias>& node);

void codegen_declaration_structured_type(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationStructuredType>& node);

void codegen_declaration_namespace(
    lt::CodegenContext& codegen_context,
    const std::shared_ptr<DeclarationNamespace>& node);

void codegen_declaration(lt::CodegenContext& codegen_context,
                         const std::shared_ptr<BaseDeclaration>& node);

void codegen_translation_unit(lt::CodegenContext& codegen_context,
                              const std::shared_ptr<TranslationUnit>& node);
}  // namespace forge
