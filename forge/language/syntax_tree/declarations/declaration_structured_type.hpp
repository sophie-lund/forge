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

#include <llvm/IR/Value.h>

#include <forge/language/syntax_tree/declarations/base_declaration.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/language/syntax_tree/statements/statement_block.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/values/base_value.hpp>

namespace forge {
enum class StructuredTypeKind { struct_, interface };

class DeclarationStructuredType : public BaseDeclaration {
 public:
  static const NodeKind NODE_KIND;

  DeclarationStructuredType(
      std::optional<SourceRange>&& source_range, std::string&& name,
      StructuredTypeKind structured_type_kind,
      std::vector<std::shared_ptr<BaseDeclaration>>&& members,
      std::vector<std::shared_ptr<TypeSymbol>>&& inherits);

  StructuredTypeKind structured_type_kind;
  std::vector<std::shared_ptr<BaseDeclaration>> members;
  std::vector<std::shared_ptr<TypeSymbol>> inherits;

 protected:
  virtual void on_accept(IVisitor& visitor) final;
  virtual void on_format_debug_declaration(
      DebugFormatter& formatter) const final;
  virtual bool on_compare_declaration(const BaseNode& other) const final;
  virtual std::shared_ptr<BaseNode> on_clone() const final;
};
}  // namespace forge
