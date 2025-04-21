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
#include <langtools/codegen/codegen_context.hpp>
#include <langtools/messaging/message_context.hpp>

namespace forge {
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
}  // namespace forge
