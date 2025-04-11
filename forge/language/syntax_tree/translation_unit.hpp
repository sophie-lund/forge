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

namespace forge {
class TranslationUnit : public BaseForgeNode {
 public:
  static const NodeKind NODE_KIND;

  TranslationUnit(SourceRange&& source_range,
                  std::vector<std::shared_ptr<BaseDeclaration>>&& declarations);

  std::vector<std::shared_ptr<BaseDeclaration>> declarations;

 protected:
  virtual void on_accept(IVisitor& visitor) final;
  virtual void on_format_debug(DebugFormatter& formatter) const final;
  virtual bool on_compare(const BaseNode& other) const final;
  virtual std::shared_ptr<BaseNode> on_clone() const final;
  virtual ScopeFlags on_get_scope_flags() const final;
  virtual const Scope* on_try_get_scope() const final;

 private:
  Scope _scope;
};
}  // namespace forge
