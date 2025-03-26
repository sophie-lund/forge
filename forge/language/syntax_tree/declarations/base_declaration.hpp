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

#include <forge/language/syntax_tree/base_forge_node.hpp>
#include <forge/syntax_tree/scope/scope.hpp>

namespace forge {
class BaseDeclaration : public BaseForgeNode {
 public:
  BaseDeclaration(NodeKind kind, std::optional<SourceRange>&& source_range,
                  std::string&& name);

  ~BaseDeclaration() = 0;

  std::string name;

 protected:
  virtual void on_format_debug(DebugFormatter& formatter) const final;
  virtual bool on_compare(const BaseNode& other) const final;
  virtual std::optional<std::string> on_get_declared_symbol_name() const final;
  virtual const Scope* on_try_get_scope() const final;

  virtual void on_format_debug_declaration(DebugFormatter& formatter) const = 0;
  virtual bool on_compare_declaration(const BaseNode& other) const = 0;

 private:
  Scope _scope;
};
}  // namespace forge
