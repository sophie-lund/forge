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

#include <forgec/syntax_tree/declarations/base_declaration.hpp>
#include <forgec/syntax_tree/types/base_type.hpp>

namespace forge {
class TypeSymbol : public BaseType {
 public:
  static const lt::NodeKind NODE_KIND;

  TypeSymbol(lt::SourceRange&& source_range, std::string&& name);

  std::string name;
  std::shared_ptr<BaseDeclaration> referenced_declaration;

 protected:
  virtual void on_accept(lt::IVisitor&) final;

  virtual void on_format_debug_type(lt::DebugFormatter&) const final;

  virtual std::shared_ptr<lt::BaseNode> on_clone_type() const final;

  virtual bool on_compare_type(const lt::BaseNode&) const final;

  virtual std::optional<std::string> on_get_referenced_symbol_name()
      const final;

  virtual void on_resolve_symbol(
      std::shared_ptr<lt::BaseNode> referenced_node) final;
};
}  // namespace forge
