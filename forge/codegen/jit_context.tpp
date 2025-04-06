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

namespace forge {
template <typename TFunction, typename TName>
TFunction JITContext::try_lookup_function(const TName& name) const {
  llvm::ExitOnError exit_on_error;

  auto symbol = exit_on_error(_llvm_lljit->lookup(name));

  if (!symbol) {
    return nullptr;
  }

  return symbol.template toPtr<TFunction>();
}
}  // namespace forge
