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

#include <forge/language/syntax_tree/declarations/base_declaration.hpp>
#include <forge/syntax_tree/visitors/ihandler.hpp>

namespace forge {
class WellFormedValidationHandler : public IHandler {
 protected:
  virtual Output on_enter(Input& input) override;

  virtual Output on_leave(Input& input) override;

  //   bool on_leave_declaration(
  //       MessageContext& message_context,
  //       const std::vector<std::reference_wrapper<const BaseNode>>&,
  //       const BaseDeclaration& node);
};
}  // namespace forge
