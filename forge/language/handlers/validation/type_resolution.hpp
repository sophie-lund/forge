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

#include <forge/codegen/codegen_context.hpp>
#include <forge/language/handlers/iforge_handler.hpp>

namespace forge {
class TypeResolutionHandler : public IForgeHandler {
 public:
  TypeResolutionHandler(const CodegenContext& codegen_context);

 protected:
  virtual Output on_leave_value_literal_bool(
      Input<ValueLiteralBool>& input) final;

  virtual Output on_leave_value_literal_number(
      Input<ValueLiteralNumber>& input) final;

  virtual Output on_leave_value_symbol(Input<ValueSymbol>& input) final;

  virtual Output on_leave_value_unary(Input<ValueUnary>& input) final;

  virtual Output on_leave_value_binary(Input<ValueBinary>& input) final;

  virtual Output on_leave_value_call(Input<ValueCall>& input) final;

  virtual Output on_leave_value_cast(Input<ValueCast>& input) final;

  virtual Output on_leave_declaration_variable(
      Input<DeclarationVariable>& input) final;

  virtual Output on_leave_declaration_function(
      Input<DeclarationFunction>& input) final;

  virtual Output on_leave_declaration_type_alias(
      Input<DeclarationTypeAlias>& input) final;

  virtual Output on_leave_declaration_structured_type(
      Input<DeclarationStructuredType>& input) final;

 private:
  std::reference_wrapper<const CodegenContext> _codegen_context;
};
}  // namespace forge
