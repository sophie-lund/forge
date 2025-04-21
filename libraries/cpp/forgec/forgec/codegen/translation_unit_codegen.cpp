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

#include <forgec/codegen/declaration_codegen.hpp>
#include <forgec/codegen/translation_unit_codegen.hpp>

namespace forge {
void codegen_translation_unit(lt::CodegenContext& codegen_context,
                              const std::shared_ptr<TranslationUnit>& node) {
  LT_ASSERT(node != nullptr, "cannot codegen null node");

  for (const std::shared_ptr<BaseDeclaration>& declaration :
       node->declarations) {
    LT_ASSERT(declaration != nullptr,
              "cannot codegen null declaration in namespace");

    codegen_declaration(codegen_context, declaration);
  }
}
}  // namespace forge
