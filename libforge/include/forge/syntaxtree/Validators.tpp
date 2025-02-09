// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

namespace sycamore::syntaxtree {
template <typename TNode, typename TName, typename TValue>
bool validateEquals(messaging::MessageContext& messageContext,
                    const TNode& node, const TName& fieldName,
                    const TValue& fieldValue, const TValue& expectedValue) {
  if (!(fieldValue == expectedValue)) {
    messageContext.emit(node.sourceRange, messaging::SEVERITY_ERROR, "???",
                        std::format("field {:?} must be equal to {:?}",
                                    fieldName, expectedValue));
    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateNotEquals(messaging::MessageContext& messageContext,
                       const TNode& node, const TName& fieldName,
                       const TValue& fieldValue, const TValue& expectedValue) {
  if (fieldValue == expectedValue) {
    messageContext.emit(node.sourceRange, messaging::SEVERITY_ERROR, "???",
                        std::format("field {:?} must not be equal to {:?}",
                                    fieldName, expectedValue));
    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateLessThan(messaging::MessageContext& messageContext,
                      const TNode& node, const TName& fieldName,
                      const TValue& fieldValue, const TValue& threshold) {
  if (!(fieldValue < threshold)) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be less than {:?}", fieldName, threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateLessThanOrEqualTo(messaging::MessageContext& messageContext,
                               const TNode& node, const TName& fieldName,
                               const TValue& fieldValue,
                               const TValue& threshold) {
  if (!(fieldValue <= threshold)) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be less than or equal to {:?}", fieldName,
                    threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateGreaterThan(messaging::MessageContext& messageContext,
                         const TNode& node, const TName& fieldName,
                         const TValue& fieldValue, const TValue& threshold) {
  if (!(fieldValue > threshold)) {
    messageContext.emit(node.sourceRange, messaging::SEVERITY_ERROR, "???",
                        std::format("field {:?} must be greater than {:?}",
                                    fieldName, threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateGreaterThanOrEqualTo(messaging::MessageContext& messageContext,
                                  const TNode& node, const TName& fieldName,
                                  const TValue& fieldValue,
                                  const TValue& threshold) {
  if (!(fieldValue >= threshold)) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be greater than or equal to {:?}",
                    fieldName, threshold));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validatePositive(messaging::MessageContext& messageContext,
                      const TNode& node, const TName& fieldName,
                      const TValue& fieldValue) {
  if (!(fieldValue > static_cast<TValue>(0))) {
    messageContext.emit(node.sourceRange, messaging::SEVERITY_ERROR, "???",
                        std::format("field {:?} must be positive", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateNonPositive(messaging::MessageContext& messageContext,
                         const TNode& node, const TName& fieldName,
                         const TValue& fieldValue) {
  if (fieldValue > static_cast<TValue>(0)) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must not be positive", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateNegative(messaging::MessageContext& messageContext,
                      const TNode& node, const TName& fieldName,
                      const TValue& fieldValue) {
  if (!(fieldValue < static_cast<TValue>(0))) {
    messageContext.emit(node.sourceRange, messaging::SEVERITY_ERROR, "???",
                        std::format("field {:?} must be negative", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TValue>
bool validateNonNegative(messaging::MessageContext& messageContext,
                         const TNode& node, const TName& fieldName,
                         const TValue& fieldValue) {
  if (fieldValue < static_cast<TValue>(0)) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must not be negative", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName>
bool validateStringNonEmpty(messaging::MessageContext& messageContext,
                            const TNode& node, const TName& fieldName,
                            const std::string& fieldValue) {
  if (fieldValue.empty()) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be an empty string", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName>
bool validateStringEmpty(messaging::MessageContext& messageContext,
                         const TNode& node, const TName& fieldName,
                         const std::string& fieldValue) {
  if (!fieldValue.empty()) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be a non-empty string", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TChild>
bool validateChildNonNull(messaging::MessageContext& messageContext,
                          const TNode& node, const TName& fieldName,
                          const std::shared_ptr<TChild>& child) {
  if (!child) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be a non-null child", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TChild>
bool validateChildNull(messaging::MessageContext& messageContext,
                       const TNode& node, const TName& fieldName,
                       const std::shared_ptr<TChild>& child) {
  if (child) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be a null child", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TElement>
bool validateVectorNonEmpty(messaging::MessageContext& messageContext,
                            const TNode& node, const TName& fieldName,
                            const std::vector<TElement>& elements) {
  if (elements.empty()) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be a non-empty vector", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TElement>
bool validateVectorEmpty(messaging::MessageContext& messageContext,
                         const TNode& node, const TName& fieldName,
                         const std::vector<TElement>& elements) {
  if (!elements.empty()) {
    messageContext.emit(
        node.sourceRange, messaging::SEVERITY_ERROR, "???",
        std::format("field {:?} must be an empty vector", fieldName));

    return false;
  }

  return true;
}

template <typename TNode, typename TName, typename TChild>
bool validateChildVectorNonNull(
    messaging::MessageContext& messageContext, const TNode& node,
    const TName& fieldName,
    const std::vector<std::shared_ptr<TChild>>& children) {
  size_t index = 0;
  for (const auto& child : children) {
    if (!child) {
      messageContext.emit(
          node.sourceRange, messaging::SEVERITY_ERROR, "???",
          std::format(
              "all children in field {:?} must be non-null ({} is null)",
              fieldName, index));
      return false;
    }

    index++;
  }

  return true;
}
}  // namespace sycamore::syntaxtree
