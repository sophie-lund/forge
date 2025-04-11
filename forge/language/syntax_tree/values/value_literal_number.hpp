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
#include <forge/syntax_tree/formatting/debug_formatter.hpp>

namespace forge {
union ValueLiteralNumberUnion {
  int8_t i8;
  int16_t i16;
  int32_t i32;
  int64_t i64;
  uint8_t u8;
  uint16_t u16;
  uint32_t u32;
  uint64_t u64;
  float f32;
  double f64;
};

class ValueLiteralNumber : public BaseValue {
 public:
  static const NodeKind NODE_KIND;

  ValueLiteralNumber(SourceRange&& source_range,
                     std::shared_ptr<TypeWithBitWidth>&& type,
                     ValueLiteralNumberUnion value);

  std::shared_ptr<TypeWithBitWidth> type;
  ValueLiteralNumberUnion value;

 protected:
  virtual void on_accept(IVisitor&) final;

  virtual void on_format_debug(DebugFormatter&) const final;

  virtual std::shared_ptr<BaseNode> on_clone() const final;

  virtual bool on_compare(const BaseNode&) const final;
};
}  // namespace forge
