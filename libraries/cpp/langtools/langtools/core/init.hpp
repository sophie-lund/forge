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

#include <expected>

namespace lt {
enum class InitErrorType {
  already_initted,
  has_not_been_initted,
  unable_to_init_icu,
};

/**
 * @brief See if the global state of Forge is initialized.
 */
bool is_initted();

/**
 * @brief Do any global initialization that Forge needs.
 */
[[nodiscard]]
std::expected<void, InitErrorType> init();

/**
 * @brief Do any global cleanup that Forge needs.
 */
[[nodiscard]]
std::expected<void, InitErrorType> cleanup();
}  // namespace lt
