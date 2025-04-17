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

namespace lt {
template <typename TNode, typename TName, typename TValue>
bool validate_equals(MessageContext& message_context,
                     const std::shared_ptr<TNode>& node,
                     const TName& field_name, const TValue& field_value,
                     const TValue& expected_value, std::string message_code) {
  if (!(field_value == expected_value)) {
    message_context.emit(node->source_range, SEVERITY_ERROR, message_code,
                         std::format("field {:?} must be equal to {:?}",
                                     field_name, expected_value));
    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_not_equals(MessageContext& message_context,
                         const std::shared_ptr<TNode>& node,
                         const TName& field_name, const TValue& field_value,
                         const TValue& expected_value,
                         std::string message_code) {
  if (field_value == expected_value) {
    message_context.emit(node->source_range, SEVERITY_ERROR, message_code,
                         std::format("field {:?} must not be equal to {:?}",
                                     field_name, expected_value));
    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_less_than(MessageContext& message_context,
                        const std::shared_ptr<TNode>& node,
                        const TName& field_name, const TValue& field_value,
                        const TValue& threshold, std::string message_code) {
  if (!(field_value < threshold)) {
    message_context.emit(node->source_range, SEVERITY_ERROR, message_code,
                         std::format("field {:?} must be less than {:?}",
                                     field_name, threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_less_than_or_equal_to(MessageContext& message_context,
                                    const std::shared_ptr<TNode>& node,
                                    const TName& field_name,
                                    const TValue& field_value,
                                    const TValue& threshold,
                                    std::string message_code) {
  if (!(field_value <= threshold)) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be less than or equal to {:?}", field_name,
                    threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_greater_than(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name, const TValue& field_value,
                           const TValue& threshold, std::string message_code) {
  if (!(field_value > threshold)) {
    message_context.emit(node->source_range, SEVERITY_ERROR, message_code,
                         std::format("field {:?} must be greater than {:?}",
                                     field_name, threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_greater_than_or_equal_to(MessageContext& message_context,
                                       const std::shared_ptr<TNode>& node,
                                       const TName& field_name,
                                       const TValue& field_value,
                                       const TValue& threshold,
                                       std::string message_code) {
  if (!(field_value >= threshold)) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be greater than or equal to {:?}",
                    field_name, threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_positive(MessageContext& message_context,
                       const std::shared_ptr<TNode>& node,
                       const TName& field_name, const TValue& field_value,
                       std::string message_code) {
  if (!(field_value > static_cast<TValue>(0))) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be positive", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_not_positive(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name, const TValue& field_value,
                           std::string message_code) {
  if (field_value > static_cast<TValue>(0)) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must not be positive", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_negative(MessageContext& message_context,
                       const std::shared_ptr<TNode>& node,
                       const TName& field_name, const TValue& field_value,
                       std::string message_code) {
  if (!(field_value < static_cast<TValue>(0))) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be negative", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validate_not_negative(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name, const TValue& field_value,
                           std::string message_code) {
  if (field_value < static_cast<TValue>(0)) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must not be negative", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName>
bool validate_string_not_empty(MessageContext& message_context,
                               const std::shared_ptr<TNode>& node,
                               const TName& field_name,
                               const std::string& field_value,
                               std::string message_code) {
  if (field_value.empty()) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be an empty string", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName>
bool validate_string_empty(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name,
                           const std::string& field_value,
                           std::string message_code) {
  if (!field_value.empty()) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be a non-empty string", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TChild>
bool validate_child_not_null(MessageContext& message_context,
                             const std::shared_ptr<TNode>& node,
                             const TName& field_name,
                             const std::shared_ptr<TChild>& child,
                             std::string message_code) {
  if (!child) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be a non-null child", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TChild>
bool validate_child_null(MessageContext& message_context,
                         const std::shared_ptr<TNode>& node,
                         const TName& field_name,
                         const std::shared_ptr<TChild>& child,
                         std::string message_code) {
  if (child) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be a null child", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TElement>
bool validate_vector_not_empty(MessageContext& message_context,
                               const std::shared_ptr<TNode>& node,
                               const TName& field_name,
                               const std::vector<TElement>& elements,
                               std::string message_code) {
  if (elements.empty()) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be a non-empty vector", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TElement>
bool validate_vector_empty(MessageContext& message_context,
                           const std::shared_ptr<TNode>& node,
                           const TName& field_name,
                           const std::vector<TElement>& elements,
                           std::string message_code) {
  if (!elements.empty()) {
    message_context.emit(
        node->source_range, SEVERITY_ERROR, message_code,
        std::format("field {:?} must be an empty vector", field_name));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TChild>
bool validate_child_vector_not_null(
    MessageContext& message_context, const std::shared_ptr<TNode>& node,
    const TName& field_name,
    const std::vector<std::shared_ptr<TChild>>& children,
    std::string message_code) {
  size_t index = 0;
  for (const auto& child : children) {
    if (!child) {
      message_context.emit(
          node->source_range, SEVERITY_ERROR, message_code,
          std::format(
              "all children in field {:?} must be non-null ({} is null)",
              field_name, index));
      return false;
    }

    index++;
  }

  return true;
}
}  // namespace lt
