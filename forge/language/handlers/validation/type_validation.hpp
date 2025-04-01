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

#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/syntax_tree/visitors/ihandler.hpp>

namespace forge {
class TypeValidationHandler : public IHandler {
 protected:
  virtual Output on_enter(Input& input) override;

  virtual Output on_leave(Input& input) override;

 private:
  static const DeclarationFunction* get_current_function(Input& input);
};
}  // namespace forge
