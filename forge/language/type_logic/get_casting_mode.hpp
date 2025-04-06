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
#include <forge/language/syntax_tree/types/base_type.hpp>

namespace forge {
/**
 * @brief The casting mode for conversion between two types.
 */
enum class CastingMode {
  /**
   * @brief Conversion between these types is illegal.
   *
   * For example, you cannot cast from a @c void to an @c i32 no matter what.
   */
  illegal,

  /**
   * @brief Conversion between these types can be done implicitly.
   *
   * For example, values of type @c i32 can be implicitly and safely cast to
   * @c i64 without loss of precision.
   */
  implicit,

  /**
   * @brief Conversion between these types can be done, but must be done
   * explicitly.
   *
   * For example, values of type @c i64 can be cast to @c i32, but this
   * conversion may lose precision. Therefore, it must be done explicitly.
   */
  explicit_
};

/**
 * @brief Gets the mode required for converting between types @c from and @c to.
 */
CastingMode get_casting_mode(const CodegenContext& codegen_context,
                             const std::shared_ptr<BaseType>& from,
                             const std::shared_ptr<BaseType>& to);
}  // namespace forge
