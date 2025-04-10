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
 * @file Validators.hpp
 *
 * @brief Contains helper functions for validating syntax tree nodes.
 */

#pragma once

#include <forge/messaging/message_context.hpp>

namespace forge {
/**
 * @brief Validates that a field is equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c ==
 *                operator.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 * @param expected_value The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_equals(MessageContext& message_context,
                     const std::shared_ptr<TNode>& node,
                     const TName& field_name, const TValue& field_value,
                     const TValue& expected_value, std::string message_code);

/**
 * @brief Validates that a field is not equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c ==
 *                operator.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 * @param expected_value The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_not_equals(MessageContext& message_context,
                         const std::shared_ptr<TNode>& node,
                         const TName& field_name, const TValue& field_value,
                         const TValue& expected_value,
                         std::string message_code);

/**
 * @brief Validates that a field is less than a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <
 *                operator.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_less_than(MessageContext& message_context,
                        const std::shared_ptr<TNode>& node,
                        const TName& field_name, const TValue& field_value,
                        const TValue& threshold, std::string message_code);

/**
 * @brief Validates that a field is less than or equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <=
 *                operator.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_less_than_or_equal_to(MessageContext& message_context,
                                    const std::shared_ptr<TNode>& node,
                                    const TName& field_name,
                                    const TValue& field_value,
                                    const TValue& threshold,
                                    std::string message_code);

/**
 * @brief Validates that a field is greater than a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >
 *                operator.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_greater_than(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name, const TValue& field_value,
                           const TValue& threshold, std::string message_code);

/**
 * @brief Validates that a field is greater than or equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >=
 *                operator.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_greater_than_or_equal_to(MessageContext& message_context,
                                       const std::shared_ptr<TNode>& node,
                                       const TName& field_name,
                                       const TValue& field_value,
                                       const TValue& threshold,
                                       std::string message_code);

/**
 * @brief Validates that a field is positive.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_positive(MessageContext& message_context,
                       const std::shared_ptr<TNode>& node,
                       const TName& field_name, const TValue& field_value,
                       std::string message_code);

/**
 * @brief Validates that a field is @c not positive.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_not_positive(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name, const TValue& field_value,
                           std::string message_code);

/**
 * @brief Validates that a field is negative.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_negative(MessageContext& message_context,
                       const std::shared_ptr<TNode>& node,
                       const TName& field_name, const TValue& field_value,
                       std::string message_code);

/**
 * @brief Validates that a field is @c not negative.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validate_not_negative(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name, const TValue& field_value,
                           std::string message_code);

/**
 * @brief Validates that a field is a non-empty string.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName>
bool validate_string_not_empty(MessageContext& message_context,
                               const std::shared_ptr<TNode>& node,
                               const TName& field_name,
                               const std::string& field_value,
                               std::string message_code);

/**
 * @brief Validates that a field is an empty string.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param field_value The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName>
bool validate_string_empty(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name,
                           const std::string& field_value,
                           std::string message_code);

/**
 * @brief Validates that a field is a non-null node child.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TChild The type of the child node.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param child The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TChild>
bool validate_child_not_null(MessageContext& message_context,
                             const std::shared_ptr<TNode>& node,
                             const TName& field_name,
                             const std::shared_ptr<TChild>& child,
                             std::string message_code);

/**
 * @brief Validates that a field is a null node child.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TChild The type of the child node.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param child The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TChild>
bool validate_child_null(MessageContext& message_context,
                         const std::shared_ptr<TNode>& node,
                         const TName& field_name,
                         const std::shared_ptr<TChild>& child,
                         std::string message_code);

/**
 * @brief Validates that a field is a non-empty vector.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TElement The type of an element of the vector.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param elements The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TElement>
bool validate_vector_not_empty(MessageContext& message_context,
                               const std::shared_ptr<TNode>& node,
                               const TName& field_name,
                               const std::vector<TElement>& elements,
                               std::string message_code);

/**
 * @brief Validates that a field is an empty vector.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TElement The type of an element of the vector.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param elements The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TElement>
bool validate_vector_empty(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name,
                           const std::vector<TElement>& elements,
                           std::string message_code);

/**
 * @brief Validates that a field is a vector of child nodes, all of which are
 *        non-null.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TChild The type of child node that is in the vector.
 *
 * @param message_context The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param field_name The name of the field that is being validated.
 * @param children The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TChild>
bool validate_child_vector_not_null(
    MessageContext& message_context, const std::shared_ptr<TNode>& node,
    const TName& field_name,
    const std::vector<std::shared_ptr<TChild>>& children,
    std::string message_code);
}  // namespace forge

#include "validators.tpp"
