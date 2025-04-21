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
#include <forgec/syntax_tree/statements/base_statement.hpp>

namespace forge {
class StatementDeclaration : public BaseStatement {
 public:
  static const lt::NodeKind NODE_KIND;

  StatementDeclaration(lt::SourceRange&& source_range,
                       std::shared_ptr<BaseDeclaration>&& declaration);

  std::shared_ptr<BaseDeclaration> declaration;

 protected:
  virtual void on_accept(lt::IVisitor&) final;

  virtual void on_format_debug(lt::DebugFormatter&) const final;

  virtual std::shared_ptr<lt::BaseNode> on_clone() const final;

  virtual bool on_compare(const lt::BaseNode&) const final;
};
}  // namespace forge
