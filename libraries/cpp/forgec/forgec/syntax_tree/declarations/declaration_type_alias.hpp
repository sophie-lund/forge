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

#include <forgec/syntax_tree/declarations/base_declaration.hpp>
#include <forgec/syntax_tree/types/base_type.hpp>
#include <forgec/syntax_tree/values/base_value.hpp>

namespace forge {
class DeclarationTypeAlias : public BaseDeclaration {
 public:
  static const lt::NodeKind NODE_KIND;

  DeclarationTypeAlias(lt::SourceRange&& source_range, std::string&& name,
                       std::shared_ptr<BaseType>&& type,
                       bool is_explicit = false);

  std::shared_ptr<BaseType> type;
  bool is_explicit;

 protected:
  virtual void on_accept(lt::IVisitor& visitor) final;
  virtual void on_format_debug_declaration(
      lt::DebugFormatter& formatter) const final;
  virtual bool on_compare_declaration(const lt::BaseNode& other) const final;
  virtual std::shared_ptr<lt::BaseNode> on_clone() const final;
};
}  // namespace forge
