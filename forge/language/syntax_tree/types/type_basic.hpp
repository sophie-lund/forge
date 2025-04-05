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

#include <forge/language/syntax_tree/types/base_type.hpp>

namespace forge {
enum class TypeBasicKind { bool_, void_, isize, usize };

class TypeBasic : public BaseType {
 public:
  static const NodeKind NODE_KIND;

  TypeBasic(std::optional<SourceRange>&& source_range,
            TypeBasicKind type_basic_kind);

  TypeBasicKind type_basic_kind;

 protected:
  virtual void on_accept(IVisitor&) final;

  virtual void on_format_debug_type(DebugFormatter&) const final;

  virtual std::shared_ptr<BaseNode> on_clone_type() const final;

  virtual bool on_compare_type(const BaseNode&) const final;
};
}  // namespace forge
