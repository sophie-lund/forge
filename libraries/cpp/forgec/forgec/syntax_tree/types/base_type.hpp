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

#include <llvm/IR/Type.h>

#include <forgec/syntax_tree/base_forge_node.hpp>

namespace forge {
class BaseType : public BaseForgeNode {
 public:
  BaseType(lt::NodeKind kind, lt::SourceRange&& source_range);

  ~BaseType() = 0;

  llvm::Type* llvm_type;
  bool is_const;

 protected:
  virtual void on_format_debug(lt::DebugFormatter& formatter) const final;
  virtual bool on_compare(const lt::BaseNode& other) const final;
  virtual std::shared_ptr<lt::BaseNode> on_clone() const final;

  virtual void on_format_debug_type(lt::DebugFormatter& formatter) const = 0;
  virtual bool on_compare_type(const lt::BaseNode& other) const = 0;
  virtual std::shared_ptr<lt::BaseNode> on_clone_type() const = 0;
};
}  // namespace forge
