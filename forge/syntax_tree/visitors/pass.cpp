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

#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>

namespace forge {
Pass::Pass(MessageContext& message_context)
    : message_context_(std::ref(message_context)) {}

void Pass::add_handler(std::unique_ptr<IHandler>&& handler) {
  handlers_.emplace_back(std::move(handler));
}
}  // namespace forge
