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

#include <forgec/syntax_tree/statements/statement_block.hpp>
#include <forgec/syntax_tree/values/base_value.hpp>

namespace forge {
class StatementIf : public BaseStatement {
 public:
  static const lt::NodeKind NODE_KIND;

  StatementIf(lt::SourceRange&& source_range,
              std::shared_ptr<BaseValue>&& condition,
              std::shared_ptr<StatementBlock>&& then,
              std::shared_ptr<BaseStatement>&& else_);

  std::shared_ptr<BaseValue> condition;
  std::shared_ptr<StatementBlock> then;
  std::shared_ptr<BaseStatement> else_;

 protected:
  virtual void on_accept(lt::IVisitor&) final;

  virtual void on_format_debug(lt::DebugFormatter&) const final;

  virtual std::shared_ptr<lt::BaseNode> on_clone() const final;

  virtual bool on_compare(const lt::BaseNode&) const final;
};
}  // namespace forge
