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

/**
 * @file type_predicates.hpp
 *
 * @brief Various predicates to check the conditions of a given type node.
 */

#pragma once

#include <forge/codegen/codegen_context.hpp>
#include <forge/language/syntax_tree/types/base_type.hpp>

namespace forge {
/**
 * @brief Check if @c type is @c void.
 */
bool is_type_void(const std::shared_ptr<BaseType>& type);

/**
 * @brief Check if @c type is @c bool.
 */
bool is_type_bool(const std::shared_ptr<BaseType>& type);

/**
 * @brief Check if @c type is an integer type.
 */
bool is_type_integer(const std::shared_ptr<BaseType>& type);

/**
 * @brief Gets the signedness of integer type @c type.
 *
 * @returns @c true if @c type is a signed integer, @c false if it is an
 * unsigned integer, and @c std::nullopt if it is not an integer at all.
 */
std::optional<bool> get_integer_type_signedness(
    const std::shared_ptr<BaseType>& type);

/**
 * @brief Check if @c type is a float type.
 */
bool is_type_float(const std::shared_ptr<BaseType>& type);

/**
 * @brief Check if @c type is a number type.
 */
bool is_type_number(const std::shared_ptr<BaseType>& type);

/**
 * @brief Gets the bit width of number type @c type.
 *
 * @param codegen_context The current code generation context, used to determine
 * the pointer width in bits for the target machine.
 *
 * @param type The type to check.
 *
 * @returns The number of bits or @c std::nullopt if @c type is not a number
 * type.
 */
std::optional<uint32_t> get_number_type_bit_width(
    const CodegenContext& codegen_context,
    const std::shared_ptr<BaseType>& type);

/**
 * @brief Check if @c type is a pointer type.
 */
bool is_type_pointer(const std::shared_ptr<BaseType>& type);

/**
 * @brief Gets the type pointed to by pointer type @c type.
 *
 * @returns @c nullptr if @c type is not a pointer type, otherwise the type
 * pointed to.
 *
 * @note If @c type is not well formed this may return @c nullptr even if
 * @c type is a pointer type.
 */
std::shared_ptr<BaseType> try_get_pointer_element_type(
    const std::shared_ptr<BaseType>& type);
}  // namespace forge
