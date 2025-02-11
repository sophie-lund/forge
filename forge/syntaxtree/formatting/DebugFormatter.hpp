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

#include <ostream>

namespace forge {
/**
 * @brief The default number of spaces to indent by when formatting syntax trees
 *        for debugging.
 */
constexpr uint32_t DEFAULT_INDENTATION_WIDTH_SPACES = 2;

/**
 * @brief A class for formatting syntax trees for debugging.
 *
 * @tparam TNodeKind The type of node kind enum. This should have an `<<`
 *                   operator defined for printing.
 */
template <typename TNodeKind>
class DebugFormatter {
 public:
  /**
   * @param stream The output stream to write to.
   * @param indentationWidthSpaces The number of spaces to indent by.
   * @param indentationInitialSpaces The number of spaces to start with.
   *
   * @note @p indentationWidthSpaces and @p indentationInitialSpaces are usually
   * set by the inheriting class.
   */
  DebugFormatter(
      std::ostream& stream,
      uint32_t indentationWidthSpaces = DEFAULT_INDENTATION_WIDTH_SPACES,
      uint32_t indentationInitialSpaces = 0);

  DebugFormatter(const DebugFormatter&) = delete;
  DebugFormatter(DebugFormatter&&) = delete;
  DebugFormatter& operator=(const DebugFormatter&) = delete;
  DebugFormatter& operator=(DebugFormatter&&) = delete;

  /**
   * @brief Emits a label for a node of kind @p kind.
   */
  void nodeLabel(const TNodeKind& kind);

  /**
   * @brief Emits a label for a field with name @p name.
   *
   * @tparam TName It can be anything streamable.
   */
  template <typename TName>
  void fieldLabel(const TName& name);

  /**
   * @brief Emits a null value.
   */
  void null();

  /**
   * @brief Emits a string value.
   *
   * @tparam TValue It can be anything streamable.
   */
  template <typename TValue>
  void string(const TValue& value);

  /**
   * @brief Emits a vector of values.
   *
   * @tparam TItem The type of item in the vector.
   * @tparam TItemFormatter A function that formats an item in the vector. It
   * must be a function which takes a single parameter of `const TItem&`
   * and returns @c void.
   *
   * @param value The vector of items to format.
   * @param itemFormatter The function to format each item in the vector.
   */
  template <typename TItem, typename TItemFormatter>
  void vector(const std::vector<TItem>& value, TItemFormatter itemFormatter);

  /**
   * @brief Gets a reference to the stream.
   */
  std::ostream& stream();

  /**
   * @brief Manually indents the output.
   *
   * @note This is automatically done by @a nodeLabel, @a fieldLabel, and @a
   * vector. You should basically never have to call this.
   */
  void indent();

  /**
   * @brief Manually unindents the output.
   *
   * @note This is automatically done by @a nodeLabel, @a fieldLabel, and @a
   * vector. You should basically never have to call this.
   */
  void unindent();

  /**
   * @brief Emits a node.
   *
   * @tparam TNode The type of node to emit.
   *
   * @param value The node to emit.
   */
  template <typename TNode>
  void node(const std::shared_ptr<TNode>& value);

  /**
   * @brief Emits a vector of nodes.
   *
   * @tparam TNode The type of node to emit.
   *
   * @param value The vector of nodes to emit.
   */
  template <typename TNode>
  void nodeVector(const std::vector<std::shared_ptr<TNode>>& value);

 private:
  std::reference_wrapper<std::ostream> stream_;
  uint32_t indentationLevel_;
  uint32_t indentationWidthSpaces_;
  uint32_t indentationInitialSpaces_;

  void formatIndentation();
};
}  // namespace forge

#include "DebugFormatter.tpp"
