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

#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/syntax_tree/values/base_value.hpp>

namespace forge {
template <typename TValue>
class ValueLiteralNumeric : public BaseValue {
 public:
  ValueLiteralNumeric(std::optional<SourceRange>&& source_range, TValue value);

  std::shared_ptr<TypeWithBitWidth> type;
  TValue value;

 protected:
  virtual void on_accept(IVisitor&) final;

  virtual void on_format_debug(DebugFormatter&) const final;

  virtual std::shared_ptr<BaseNode> on_clone() const final;

  virtual bool on_compare(const BaseNode&) const final;
};

using ValueLiteralI8 = ValueLiteralNumeric<int8_t>;
using ValueLiteralI16 = ValueLiteralNumeric<int16_t>;
using ValueLiteralI32 = ValueLiteralNumeric<int32_t>;
using ValueLiteralI64 = ValueLiteralNumeric<int64_t>;
using ValueLiteralU8 = ValueLiteralNumeric<uint8_t>;
using ValueLiteralU16 = ValueLiteralNumeric<uint16_t>;
using ValueLiteralU32 = ValueLiteralNumeric<uint32_t>;
using ValueLiteralU64 = ValueLiteralNumeric<uint64_t>;

static_assert(sizeof(float) == 4);
using ValueLiteralF32 = ValueLiteralNumeric<float>;

static_assert(sizeof(double) == 8);
using ValueLiteralF64 = ValueLiteralNumeric<double>;
}  // namespace forge

#include "value_literal_numeric.tpp"
