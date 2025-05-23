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

#include <forgec/handlers/iforge_handler.hpp>

namespace forge {
class ControlFlowValidationHandler : public IForgeHandler {
 public:
  ControlFlowValidationHandler();

 protected:
  virtual Output on_leave_statement_basic(Input<StatementBasic>& input) final;

  virtual Output on_leave_statement_value(Input<StatementValue>& input) final;

  virtual Output on_leave_statement_declaration(
      Input<StatementDeclaration>& input) final;

  virtual Output on_leave_statement_block(Input<StatementBlock>& input) final;

  virtual Output on_leave_statement_if(Input<StatementIf>& input) final;

  virtual Output on_leave_statement_while(Input<StatementWhile>& input) final;

  virtual Output on_leave_declaration_function(
      Input<DeclarationFunction>& input) final;
};
}  // namespace forge
