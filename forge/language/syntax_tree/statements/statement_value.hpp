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

#include <forge/language/syntax_tree/statements/base_statement.hpp>
#include <forge/language/syntax_tree/values/base_value.hpp>

namespace forge {
enum class StatementValueKind {
  execute,
  return_,
};

class StatementValue : public BaseStatement {
 public:
  StatementValue(std::optional<SourceRange>&& source_range,
                 StatementValueKind statement_value_kind,
                 std::shared_ptr<BaseValue>&& value);

  StatementValueKind statement_value_kind;
  std::shared_ptr<BaseValue> value;

 protected:
  virtual void on_accept(IVisitor&) final;

  virtual void on_format_debug(DebugFormatter&) const final;

  virtual std::shared_ptr<BaseNode> on_clone() const final;

  virtual bool on_compare(const BaseNode&) const final;
};
}  // namespace forge
