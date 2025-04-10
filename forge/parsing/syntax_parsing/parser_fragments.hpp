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

#include <forge/parsing/syntax_parsing/parsing_context.hpp>

namespace forge {
/**
 * @brief Tries to parse a single token by kind.
 *
 * @param parsing_context The parser context to use.
 * @param token_kind The expected token kind to accept.
 * @returns The token if it was successfully parsed, or `std::nullopt` if it was
 * not.
 */
std::optional<Token> parse_token_by_kind(ParsingContext& parsing_context,
                                         const TokenKind& token_kind);

/**
 * @brief Tries to parse with the provided parser.
 *
 * @tparam TNode The type of node to be returned.
 * @tparam TParser The type of the parser function. It must be of the form
 * `std::shared_ptr<TNode>(ParsingContext&)`.
 * @param parsing_context The parser context to use.
 * @param parser The parser function to try.
 * @returns The result of the first parser that successfully parses or
 * `std::nullopt` if the parser does not work. It will reset the parser state
 * after the failed attempt.
 */
template <typename TNode, typename TParser>
std::shared_ptr<TNode> parse_optional(ParsingContext& parsing_context,
                                      TParser parser);

/**
 * @brief Tries to parse with any of the provided parsers.
 *
 * @tparam TNode The type of node to be returned.
 * @param parsing_context The parser context to use.
 * @param parsers The list of parser functions to try.
 * @returns The result of the first parser that successfully parses or
 * `std::nullopt` if none of the parsers work. It will reset the parser state
 * before every attempt.
 *
 * @par Equivalent EBNF
 *
 * @code{.unparsed}
 *   parse_any_of(...) ::= parsers[0] | parsers[1] | ... | parsers[N];
 * @endcode
 */
template <typename TNode>
std::shared_ptr<TNode> parse_any_of(
    ParsingContext& parsing_context,
    std::initializer_list<
        std::function<std::shared_ptr<TNode>(ParsingContext&)>>
        parsers);

/**
 * @brief Parses a child node that is bound by left and right tokens.
 *
 * @tparam TNode The type of node to be returned.
 * @tparam TParser The type of the parser function. It must be of the form
 * `std::shared_ptr<TNode>(ParsingContext&)`.
 * @param parsing_context The parser context to use.
 * @param left_bound_token_kind The token kind of the left bound.
 * @param parser_child The parser function to parse the child node.
 * @param right_bound_token_kind The token kind of the right bound.
 * @returns The result of the parser if it was successful, or `std::nullopt` if
 *          it was not.
 *
 * @par Equivalent EBNF
 *
 * @code{.unparsed}
 *   parse_bound(...) ::= left_bound_token_kind
 *                        parser_child
 *                        right_bound_token_kind;
 * @endcode
 */
template <typename TNode, typename TParser>
std::shared_ptr<TNode> parse_bound(ParsingContext& parsing_context,
                                   const TokenKind& left_bound_token_kind,
                                   TParser parser_child,
                                   const TokenKind& right_bound_token_kind,
                                   std::string message_code);

/**
 * @brief A result object that can be returned by @c parse_prefixed.
 *
 * @tparam TNode The type of node to be returned.
 */
template <typename TNode>
struct ParsePrefixedResult {
  /**
   * @brief The token that was used as a prefix.
   */
  Token prefix_token;

  /**
   * @brief The child node that was parsed.
   */
  std::shared_ptr<TNode> child;
};

/**
 * @brief Parses a child node that is prefixed by one of the provided token
 *        kinds.
 *
 * @tparam TNode The type of node to be returned.
 * @tparam TParser The type of the parser function. It must be of the form
 * `std::shared_ptr<TNode>(ParsingContext&)`.
 * @param parsing_context The parser context to use.
 * @param prefix_token_kinds The list of token kinds that can be used as a
 *                           prefix.
 * @param parser_child The parser function to parse the child node.
 * @returns The result of the parser if it was successful, or `std::nullopt` if
 *          it was not.
 *
 * @par Equivalent EBNF
 *
 * @code{.unparsed}
 *   parse_prefixed(...) ::= prefix_tokens_kinds[0] parser_child
 *                         | prefix_tokens_kinds[1] parser_child
 *                         | ...
 *                         | prefix_tokens_kinds[N] parser_child;
 * @endcode
 */
template <typename TNode, typename TParser>
std::optional<ParsePrefixedResult<TNode>> parse_prefixed(
    ParsingContext& parsing_context,
    std::initializer_list<const TokenKind*> prefix_token_kinds,
    TParser parser_child, std::string message_code);

/**
 * @brief A result object that can be returned by @c parse_suffixed.
 *
 * @tparam TNode The type of node to be returned.
 */
template <typename TNode>
struct ParseSuffixedResult {
  /**
   * @brief The child node that was parsed.
   */
  std::shared_ptr<TNode> child;

  /**
   * @brief The token that was used as a suffix.
   *
   * If this is `std::nullopt`, that means that none of the suffixes were
   * included but the child was still parsed.
   */
  std::optional<Token> suffix_token;
};

/**
 * @brief Parses a child node that is suffixed by one of the provided token
 *        kinds.
 *
 * @tparam TNode The type of node to be returned.
 * @tparam TParser The type of the parser function. It must be of the form
 * `std::shared_ptr<TNode>(ParsingContext&)`.
 * @param parsing_context The parser context to use.
 * @param parser_child The parser function to parse the child node.
 * @param suffix_token_kinds The list of token kinds that can be used as a
 *                           suffix.
 * @returns The result of the parser if it was successful, or `std::nullopt` if
 *          it was not.
 *
 * It will also attempt to run the child parser without the suffix and return it
 * if that is an option.
 *
 * @par Equivalent EBNF
 *
 * @code{.unparsed}
 *   parse_suffixed(...) ::= parser_child suffix_tokens_kinds[0]
 *                         | parser_child suffix_tokens_kinds[1]
 *                         | ...
 *                         | parser_child suffix_tokens_kinds[N]
 *                         | parser_child;
 * @endcode
 */
template <typename TNode, typename TParser>
std::optional<ParseSuffixedResult<TNode>> parse_suffixed(
    ParsingContext& parsing_context, TParser parser_child,
    std::initializer_list<const TokenKind*> suffix_token_kinds);

/**
 * @brief A result object that can be returned by @c parse_suffixed.
 *
 * @tparam TNode The type of node to be returned.
 */
template <typename TNode>
struct ParseBinaryOperationResult {
  /**
   * @brief The left-hand side node that was parsed.
   */
  std::shared_ptr<TNode> lhs;

  /**
   * @brief The token that was used as an operator.
   *
   * If this is `std::nullopt`, that means that none of the operators were
   * used but the left-hand side was still parsed.
   */
  std::optional<Token> operator_token;

  /**
   * @brief The right-hand side node that was parsed.
   *
   * This will be `nullptr` if the right-hand side was not successfully parsed.
   */
  std::shared_ptr<TNode> rhs;
};

/**
 * @brief Parses a binary operation.
 *
 * @tparam TNode The type of node to be returned.
 * @tparam TParser The type of the parser functions. They must be of the form
 * `std::shared_ptr<TNode>(ParsingContext&)`.
 * @param parsing_context The parser context to use.
 * @param parser_lhs The parser function to parse the left-hand side node.
 * @param operator_token_kinds The list of token kinds that can be used as an
 *                             operator.
 * @param parser_rhs The parser function to parse the right-hand side node.
 * @returns The result of the parser if it was successful, or `std::nullopt` if
 *          it was not.
 *
 * It will also attempt to run the lhs parser without an operator and return it
 * if that is an option.
 *
 * @par Equivalent EBNF
 *
 * @code{.unparsed}
 *   parse_binary_operation ::= parser_lhs operator_tokens_kinds[0] parser_rhs
 *                            | parser_lhs operator_tokens_kinds[1] parser_rhs
 *                            | ...
 *                            | parser_lhs operator_tokens_kinds[N] parser_rhs
 *                            | parser_lhs;
 * @endcode
 */
template <typename TNode, typename TParser>
std::optional<ParseBinaryOperationResult<TNode>> parse_binary_operation(
    ParsingContext& parsing_context, TParser parser_lhs,
    std::initializer_list<const TokenKind*> operator_token_kinds,
    TParser parser_rhs, std::string message_code);

template <typename TNode, typename TParser>
std::optional<std::vector<std::shared_ptr<TNode>>>
parse_repeated_separated_bound(ParsingContext& parsing_context,
                               const TokenKind& left_bound_token_kind,
                               TParser parser_item,
                               const TokenKind& separator_token_kind,
                               const TokenKind& right_bound_token_kind,
                               std::string message_code);

template <typename TNode, typename TParser>
std::optional<std::vector<std::shared_ptr<TNode>>> parse_repeated_bound(
    ParsingContext& parsing_context, const TokenKind& left_bound_token_kind,
    TParser parser_item, const TokenKind& right_bound_token_kind,
    std::string message_code);
}  // namespace forge

#include "parser_fragments.tpp"
