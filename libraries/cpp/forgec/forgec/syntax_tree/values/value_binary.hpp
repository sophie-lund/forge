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

#include <forgec/syntax_tree/values/base_value.hpp>

namespace forge {
enum class BinaryOperator {
  bool_and,
  bool_or,
  bit_and,
  bit_and_assign,
  bit_or,
  bit_or_assign,
  bit_xor,
  bit_xor_assign,
  bit_shl,
  bit_shl_assign,
  bit_shr,
  bit_shr_assign,
  add,
  add_assign,
  sub,
  sub_assign,
  mul,
  mul_assign,
  exp,
  exp_assign,
  div,
  div_assign,
  mod,
  mod_assign,
  assign,
  eq,
  ne,
  lt,
  le,
  gt,
  ge,
  member_access
};

bool is_binary_operator_comparison(BinaryOperator operator_);
std::optional<BinaryOperator> try_get_compound_assignment_base_operator(
    BinaryOperator operator_);

class ValueBinary : public BaseValue {
 public:
  static const lt::NodeKind NODE_KIND;

  ValueBinary(lt::SourceRange&& source_range, BinaryOperator operator_,
              std::shared_ptr<BaseValue>&& lhs,
              std::shared_ptr<BaseValue>&& rhs);

  BinaryOperator operator_;
  std::shared_ptr<BaseValue> lhs;
  std::shared_ptr<BaseValue> rhs;

 protected:
  virtual void on_accept(lt::IVisitor&) final;

  virtual void on_format_debug(lt::DebugFormatter&) const final;

  virtual std::shared_ptr<lt::BaseNode> on_clone() const final;

  virtual bool on_compare(const lt::BaseNode&) const final;
};
}  // namespace forge
