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
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 * @param expectedValue The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateEquals(MessageContext& messageContext, const TNode& node,
                    const TName& fieldName, const TValue& fieldValue,
                    const TValue& expectedValue);

/**
 * @brief Validates that a field is not equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c ==
 *                operator.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 * @param expectedValue The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateNotEquals(MessageContext& messageContext, const TNode& node,
                       const TName& fieldName, const TValue& fieldValue,
                       const TValue& expectedValue);

/**
 * @brief Validates that a field is less than a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <
 *                operator.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateLessThan(MessageContext& messageContext, const TNode& node,
                      const TName& fieldName, const TValue& fieldValue,
                      const TValue& threshold);

/**
 * @brief Validates that a field is less than or equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <=
 *                operator.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateLessThanOrEqualTo(MessageContext& messageContext,
                               const TNode& node, const TName& fieldName,
                               const TValue& fieldValue,
                               const TValue& threshold);

/**
 * @brief Validates that a field is greater than a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >
 *                operator.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateGreaterThan(MessageContext& messageContext, const TNode& node,
                         const TName& fieldName, const TValue& fieldValue,
                         const TValue& threshold);

/**
 * @brief Validates that a field is greater than or equal to a value.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >=
 *                operator.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 * @param threshold The value that the field should be compared against.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateGreaterThanOrEqualTo(MessageContext& messageContext,
                                  const TNode& node, const TName& fieldName,
                                  const TValue& fieldValue,
                                  const TValue& threshold);

/**
 * @brief Validates that a field is positive.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validatePositive(MessageContext& messageContext, const TNode& node,
                      const TName& fieldName, const TValue& fieldValue);

/**
 * @brief Validates that a field is @c not positive.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c >
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateNonPositive(MessageContext& messageContext, const TNode& node,
                         const TName& fieldName, const TValue& fieldValue);

/**
 * @brief Validates that a field is negative.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateNegative(MessageContext& messageContext, const TNode& node,
                      const TName& fieldName, const TValue& fieldValue);

/**
 * @brief Validates that a field is @c not negative.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TValue The type of the field value. This must implement the @c <
 *                operator. @c (int)0 must be statically castable to @p TValue.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TValue>
bool validateNonNegative(MessageContext& messageContext, const TNode& node,
                         const TName& fieldName, const TValue& fieldValue);

/**
 * @brief Validates that a field is a non-empty string.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName>
bool validateStringNonEmpty(MessageContext& messageContext, const TNode& node,
                            const TName& fieldName,
                            const std::string& fieldValue);

/**
 * @brief Validates that a field is an empty string.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param fieldValue The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName>
bool validateStringEmpty(MessageContext& messageContext, const TNode& node,
                         const TName& fieldName, const std::string& fieldValue);

/**
 * @brief Validates that a field is a non-null node child.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TChild The type of the child node.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param child The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TChild>
bool validateChildNonNull(MessageContext& messageContext, const TNode& node,
                          const TName& fieldName,
                          const std::shared_ptr<TChild>& child);

/**
 * @brief Validates that a field is a null node child.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TChild The type of the child node.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param child The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TChild>
bool validateChildNull(MessageContext& messageContext, const TNode& node,
                       const TName& fieldName,
                       const std::shared_ptr<TChild>& child);

/**
 * @brief Validates that a field is a non-empty vector.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TElement The type of an element of the vector.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param elements The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TElement>
bool validateVectorNonEmpty(MessageContext& messageContext, const TNode& node,
                            const TName& fieldName,
                            const std::vector<TElement>& elements);

/**
 * @brief Validates that a field is an empty vector.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TElement The type of an element of the vector.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param elements The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TElement>
bool validateVectorEmpty(MessageContext& messageContext, const TNode& node,
                         const TName& fieldName,
                         const std::vector<TElement>& elements);

/**
 * @brief Validates that a field is a vector of child nodes, all of which are
 *        non-null.
 *
 * @tparam TNode The type of the node that is currently being validated.
 * @tparam TName The type of the field name. This is usually `const char*`.
 * @tparam TChild The type of child node that is in the vector.
 *
 * @param messageContext The message context to emit an error message to if the
 *                       condition is not met.
 * @param node The node that is currently being validated.
 * @param fieldName The name of the field that is being validated.
 * @param children The value of the field that is being validated.
 *
 * @returns @c true if the condition is met and @c false otherwise.
 */
template <typename TNode, typename TName, typename TChild>
bool validateChildVectorNonNull(
    MessageContext& messageContext, const TNode& node, const TName& fieldName,
    const std::vector<std::shared_ptr<TChild>>& children);
}  // namespace forge

#include "validators.tpp"
