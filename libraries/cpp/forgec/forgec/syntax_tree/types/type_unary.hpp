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

#include <forgec/syntax_tree/types/base_type.hpp>

namespace forge {
enum class TypeUnaryKind {
  pointer,
};

class TypeUnary : public BaseType {
 public:
  static const lt::NodeKind NODE_KIND;

  TypeUnary(lt::SourceRange&& source_range, TypeUnaryKind type_unary_kind,
            std::shared_ptr<BaseType>&& operand_type);

  TypeUnaryKind type_unary_kind;
  std::shared_ptr<BaseType> operand_type;

 protected:
  virtual void on_accept(lt::IVisitor&) final;

  virtual void on_format_debug_type(lt::DebugFormatter&) const final;

  virtual std::shared_ptr<lt::BaseNode> on_clone_type() const final;

  virtual bool on_compare_type(const lt::BaseNode&) const final;
};
}  // namespace forge
