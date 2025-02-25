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

namespace forge {
template <typename TNode, typename TParser>
std::shared_ptr<TNode> parse_optional(SyntaxParsingContext& context,
                                      TParser parser) {
  int32_t cursor = context.save_cursor();

  std::shared_ptr<TNode> result = parser(context);

  if (result != nullptr) {
    return result;
  }

  context.restore_cursor(cursor);

  return nullptr;
}

template <typename TNode>
std::shared_ptr<TNode> parse_any_of(
    SyntaxParsingContext& context,
    std::initializer_list<
        std::function<std::shared_ptr<TNode>(SyntaxParsingContext&)>>
        parsers) {
  for (const std::function<std::shared_ptr<TNode>(SyntaxParsingContext&)>&
           parser : parsers) {
    std::shared_ptr<TNode> result = parse_optional<TNode>(context, parser);

    if (result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

template <typename TNode, typename TParser>
std::shared_ptr<TNode> parse_bound(SyntaxParsingContext& context,
                                   const TokenKind& left_bound_token_kind,
                                   TParser parser_child,
                                   const TokenKind& right_bound_token_kind) {
  std::optional<Token> left_bound_result =
      parse_token_by_kind(context, left_bound_token_kind);

  if (!left_bound_result.has_value()) {
    return nullptr;
  }

  std::shared_ptr<TNode> child_result = parser_child(context);

  if (child_result == nullptr) {
    context.message_context().emit(left_bound_result.value().range,
                                   SEVERITY_ERROR, "???");
    return nullptr;
  }

  std::optional<Token> right_bound_result =
      parse_token_by_kind(context, right_bound_token_kind);

  if (!right_bound_result.has_value()) {
    context.message_context().emit(child_result->source_range, SEVERITY_ERROR,
                                   "???");
    return nullptr;
  }

  return child_result;
}

template <typename TNode, typename TParser>
std::optional<ParsePrefixedResult<TNode>> parse_prefixed(
    SyntaxParsingContext& context,
    std::initializer_list<const TokenKind*> prefix_token_kinds,
    TParser parser_child) {
  for (const TokenKind* prefix_token_kind : prefix_token_kinds) {
    std::optional<Token> prefix_result =
        parse_token_by_kind(context, *prefix_token_kind);
    if (!prefix_result.has_value()) {
      continue;
    }

    std::shared_ptr<TNode> child_result = parser_child(context);
    if (child_result == nullptr) {
      context.message_context().emit(prefix_result.value().range,
                                     SEVERITY_ERROR, "???");
      return std::nullopt;
    }

    return ParsePrefixedResult<TNode>{prefix_result.value(), child_result};
  }

  return std::nullopt;
}

template <typename TNode, typename TParser>
std::optional<ParseSuffixedResult<TNode>> parse_suffixed(
    SyntaxParsingContext& context, TParser parser_child,
    std::initializer_list<const TokenKind*> suffix_token_kinds) {
  std::shared_ptr<TNode> child_result = parser_child(context);
  if (child_result == nullptr) {
    return std::nullopt;
  }

  for (const TokenKind* suffix_token_kind : suffix_token_kinds) {
    std::optional<Token> suffix_result =
        parse_token_by_kind(context, *suffix_token_kind);
    if (suffix_result.has_value()) {
      return ParseSuffixedResult<TNode>{child_result, suffix_result};
    }
  }

  return ParseSuffixedResult<TNode>{child_result, std::nullopt};
}

template <typename TNode, typename TParser>
std::optional<ParseBinaryOperationResult<TNode>> parse_binary_operation(
    SyntaxParsingContext& context, TParser parser_lhs,
    std::initializer_list<const TokenKind*> operator_token_kinds,
    TParser parser_rhs) {
  std::optional<ParseSuffixedResult<TNode>> suffixed_result =
      parse_suffixed<TNode>(context, parser_lhs, operator_token_kinds);

  if (!suffixed_result.has_value()) {
    return std::nullopt;
  }

  if (!suffixed_result.value().suffix_token.has_value()) {
    return ParseBinaryOperationResult<TNode>{suffixed_result.value().child,
                                             std::nullopt, nullptr};
  }

  std::shared_ptr<TNode> rhs_result =
      parse_optional<TNode>(context, parser_rhs);

  if (rhs_result == nullptr) {
    context.message_context().emit(
        suffixed_result.value().suffix_token.value().range, SEVERITY_ERROR,
        "operator requires right-hand side");
  }

  return ParseBinaryOperationResult<TNode>{
      std::move(suffixed_result.value().child),
      std::move(suffixed_result.value().suffix_token), std::move(rhs_result)};
}

template <typename TNode, typename TParser>
std::optional<std::vector<std::shared_ptr<TNode>>>
parse_repeated_separated_bound(SyntaxParsingContext& context,
                               const TokenKind& left_bound_token_kind,
                               TParser parser_item,
                               const TokenKind& separator_token_kind,
                               const TokenKind& right_bound_token_kind) {
  std::vector<std::shared_ptr<TNode>> results;

  std::optional<Token> left_bound_result =
      parse_token_by_kind(context, left_bound_token_kind);

  if (!left_bound_result.has_value()) {
    return std::nullopt;
  }

  while (context.are_more_tokens()) {
    if (context.peek_next_token().kind.get() == right_bound_token_kind) {
      break;
    } else if (context.peek_next_token().kind.get() == separator_token_kind) {
      context.message_context().emit(context.peek_next_token().range,
                                     SEVERITY_ERROR, "???");
      context.read_next_token();
    } else {
      std::shared_ptr<TNode> item_result = parser_item(context);

      if (item_result == nullptr) {
        context.message_context().emit(left_bound_result.value().range,
                                       SEVERITY_ERROR, "???");
        return std::nullopt;
      }

      results.push_back(std::move(item_result));

      if (context.peek_next_token().kind.get() == separator_token_kind) {
        context.read_next_token();
      }
    }
  }

  std::optional<Token> right_bound_result =
      parse_token_by_kind(context, right_bound_token_kind);

  if (!right_bound_result.has_value()) {
    context.message_context().emit(left_bound_result->range, SEVERITY_ERROR,
                                   "???");
    return std::nullopt;
  }

  return results;
}

template <typename TNode, typename TParser>
std::optional<std::vector<std::shared_ptr<TNode>>> parse_repeated_bound(
    SyntaxParsingContext& context, const TokenKind& left_bound_token_kind,
    TParser parser_item, const TokenKind& right_bound_token_kind) {
  std::vector<std::shared_ptr<TNode>> results;

  std::optional<Token> left_bound_result =
      parse_token_by_kind(context, left_bound_token_kind);

  if (!left_bound_result.has_value()) {
    return std::nullopt;
  }

  while (context.are_more_tokens()) {
    if (context.peek_next_token().kind.get() == right_bound_token_kind) {
      break;
    } else {
      std::shared_ptr<TNode> item_result = parser_item(context);

      if (item_result == nullptr) {
        context.message_context().emit(left_bound_result.value().range,
                                       SEVERITY_ERROR, "???");
        return std::nullopt;
      }

      results.push_back(std::move(item_result));
    }
  }

  std::optional<Token> right_bound_result =
      parse_token_by_kind(context, right_bound_token_kind);

  if (!right_bound_result.has_value()) {
    context.message_context().emit(left_bound_result->range, SEVERITY_ERROR,
                                   "???");
    return std::nullopt;
  }

  return results;
}
}  // namespace forge
