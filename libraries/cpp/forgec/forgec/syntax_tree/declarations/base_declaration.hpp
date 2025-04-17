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

#include <forgec/syntax_tree/base_forge_node.hpp>
#include <forgec/syntax_tree/types/base_type.hpp>
#include <langtools/syntax_tree/scope/scope.hpp>

namespace forge {
class BaseDeclaration : public BaseForgeNode {
 public:
  BaseDeclaration(lt::NodeKind kind, lt::SourceRange&& source_range,
                  std::string&& name);

  ~BaseDeclaration() = 0;

  std::string name;
  std::shared_ptr<BaseType> resolved_type;

 protected:
  virtual void on_format_debug(lt::DebugFormatter& formatter) const final;
  virtual bool on_compare(const lt::BaseNode& other) const final;
  virtual std::optional<std::string> on_get_declared_symbol_name() const final;
  virtual const lt::Scope* on_try_get_scope() const final;

  virtual void on_format_debug_declaration(
      lt::DebugFormatter& formatter) const = 0;
  virtual bool on_compare_declaration(const lt::BaseNode& other) const = 0;

 private:
  lt::Scope _scope;
};
}  // namespace forge
