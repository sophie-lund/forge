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
std::shared_ptr<TNode> parse_optional(ParsingContext& parsing_context,
                                      TParser parser) {
  int32_t cursor = parsing_context.save_cursor();

  std::shared_ptr<TNode> result = parser(parsing_context);

  if (result != nullptr) {
    return result;
  }

  parsing_context.restore_cursor(cursor);

  return nullptr;
}

template <typename TNode>
std::shared_ptr<TNode> parse_any_of(
    ParsingContext& parsing_context,
    std::initializer_list<
        std::function<std::shared_ptr<TNode>(ParsingContext&)>>
        parsers) {
  for (const std::function<std::shared_ptr<TNode>(ParsingContext&)>& parser :
       parsers) {
    std::shared_ptr<TNode> result =
        parse_optional<TNode>(parsing_context, parser);

    if (result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

template <typename TNode, typename TParser>
std::shared_ptr<TNode> parse_bound(ParsingContext& parsing_context,
                                   const TokenKind& left_bound_token_kind,
                                   TParser parser_child,
                                   const TokenKind& right_bound_token_kind,
                                   std::string message_code) {
  std::optional<Token> left_bound_result =
      parse_token_by_kind(parsing_context, left_bound_token_kind);

  if (!left_bound_result.has_value()) {
    return nullptr;
  }

  std::shared_ptr<TNode> child_result = parser_child(parsing_context);

  if (child_result == nullptr) {
    parsing_context.message_context().emit(
        left_bound_result.value().range, SEVERITY_ERROR,
        std::move(message_code),
        std::format("unexpected token after {}", left_bound_token_kind.name));
    return nullptr;
  }

  std::optional<Token> right_bound_result =
      parse_token_by_kind(parsing_context, right_bound_token_kind);

  if (!right_bound_result.has_value()) {
    parsing_context.message_context().emit(
        child_result->source_range, SEVERITY_ERROR, std::move(message_code),
        std::format("opening {} does not have matching closing {}",
                    left_bound_token_kind.name, right_bound_token_kind.name));
    return nullptr;
  }

  return child_result;
}

template <typename TNode, typename TParser>
std::optional<ParsePrefixedResult<TNode>> parse_prefixed(
    ParsingContext& parsing_context,
    std::initializer_list<const TokenKind*> prefix_token_kinds,
    const TParser parser_child, std::string message_code) {
  for (const TokenKind* prefix_token_kind : prefix_token_kinds) {
    std::optional<Token> prefix_result =
        parse_token_by_kind(parsing_context, *prefix_token_kind);
    if (!prefix_result.has_value()) {
      continue;
    }

    std::shared_ptr<TNode> child_result = parser_child(parsing_context);
    if (child_result == nullptr) {
      parsing_context.message_context().emit(
          prefix_result.value().range, SEVERITY_ERROR, std::move(message_code),
          std::format("unexpected token after {}",
                      prefix_result->kind.get().name));
      return std::nullopt;
    }

    return ParsePrefixedResult<TNode>{prefix_result.value(), child_result};
  }

  return std::nullopt;
}

template <typename TNode, typename TParser>
std::optional<ParseSuffixedResult<TNode>> parse_suffixed(
    ParsingContext& parsing_context, TParser parser_child,
    std::initializer_list<const TokenKind*> suffix_token_kinds) {
  std::shared_ptr<TNode> child_result = parser_child(parsing_context);
  if (child_result == nullptr) {
    return std::nullopt;
  }

  for (const TokenKind* suffix_token_kind : suffix_token_kinds) {
    std::optional<Token> suffix_result =
        parse_token_by_kind(parsing_context, *suffix_token_kind);
    if (suffix_result.has_value()) {
      return ParseSuffixedResult<TNode>{child_result, suffix_result};
    }
  }

  return ParseSuffixedResult<TNode>{child_result, std::nullopt};
}

template <typename TNode, typename TParser>
std::optional<ParseBinaryOperationResult<TNode>> parse_binary_operation(
    ParsingContext& parsing_context, TParser parser_lhs,
    std::initializer_list<const TokenKind*> operator_token_kinds,
    const TParser parser_rhs, std::string message_code) {
  std::optional<ParseSuffixedResult<TNode>> suffixed_result =
      parse_suffixed<TNode>(parsing_context, parser_lhs, operator_token_kinds);

  if (!suffixed_result.has_value()) {
    return std::nullopt;
  }

  if (!suffixed_result.value().suffix_token.has_value()) {
    return ParseBinaryOperationResult<TNode>{suffixed_result.value().child,
                                             std::nullopt, nullptr};
  }

  std::shared_ptr<TNode> rhs_result =
      parse_optional<TNode>(parsing_context, parser_rhs);

  if (rhs_result == nullptr) {
    parsing_context.message_context().emit(
        suffixed_result.value().suffix_token.value().range, SEVERITY_ERROR,
        std::move(message_code), "operator requires right-hand side");
  }

  return ParseBinaryOperationResult<TNode>{
      std::move(suffixed_result.value().child),
      std::move(suffixed_result.value().suffix_token), std::move(rhs_result)};
}

template <typename TNode, typename TParser>
std::optional<ParseRepeatedBoundResult<TNode>> parse_repeated_separated_bound(
    ParsingContext& parsing_context, const TokenKind& left_bound_token_kind,
    TParser parser_item, const TokenKind& separator_token_kind,
    const TokenKind& right_bound_token_kind, std::string message_code) {
  std::vector<std::shared_ptr<TNode>> items;

  std::optional<Token> left_bound_result =
      parse_token_by_kind(parsing_context, left_bound_token_kind);

  if (!left_bound_result.has_value()) {
    return std::nullopt;
  }

  while (parsing_context.are_more_tokens()) {
    if (parsing_context.peek_next_token().kind.get() ==
        right_bound_token_kind) {
      break;
    } else if (parsing_context.peek_next_token().kind.get() ==
               separator_token_kind) {
      parsing_context.message_context().emit(
          parsing_context.peek_next_token().range, SEVERITY_ERROR, message_code,
          std::format("unexpected token {}", separator_token_kind.name));
      parsing_context.read_next_token();
    } else {
      std::shared_ptr<TNode> item_result = parser_item(parsing_context);

      if (item_result == nullptr) {
        parsing_context.message_context().emit(left_bound_result.value().range,
                                               SEVERITY_ERROR, message_code,
                                               "unexpected token");
        return std::nullopt;
      }

      items.push_back(std::move(item_result));

      if (parsing_context.peek_next_token().kind.get() ==
          separator_token_kind) {
        parsing_context.read_next_token();
      }
    }
  }

  std::optional<Token> right_bound_result =
      parse_token_by_kind(parsing_context, right_bound_token_kind);

  if (!right_bound_result.has_value()) {
    parsing_context.message_context().emit(
        left_bound_result->range, SEVERITY_ERROR, std::move(message_code),
        std::format("opening {} expects matching closing {}",
                    left_bound_token_kind.name, right_bound_token_kind.name));
    return std::nullopt;
  }

  return ParseRepeatedBoundResult<TNode>{
      .left_bound_token = left_bound_result.value(),
      .items = std::move(items),
      .right_bound_token = right_bound_result.value(),
  };
}

template <typename TNode, typename TParser>
std::optional<ParseRepeatedBoundResult<TNode>> parse_repeated_bound(
    ParsingContext& parsing_context, const TokenKind& left_bound_token_kind,
    TParser parser_item, const TokenKind& right_bound_token_kind,
    std::string message_code) {
  std::vector<std::shared_ptr<TNode>> items;

  std::optional<Token> left_bound_result =
      parse_token_by_kind(parsing_context, left_bound_token_kind);

  if (!left_bound_result.has_value()) {
    return std::nullopt;
  }

  while (parsing_context.are_more_tokens()) {
    if (parsing_context.peek_next_token().kind.get() ==
        right_bound_token_kind) {
      break;
    } else {
      std::shared_ptr<TNode> item_result = parser_item(parsing_context);

      if (item_result == nullptr) {
        parsing_context.message_context().emit(
            left_bound_result.value().range, SEVERITY_ERROR,
            std::move(message_code), "unexpected token");
        return std::nullopt;
      }

      items.push_back(std::move(item_result));
    }
  }

  std::optional<Token> right_bound_result =
      parse_token_by_kind(parsing_context, right_bound_token_kind);

  if (!right_bound_result.has_value()) {
    parsing_context.message_context().emit(
        left_bound_result->range, SEVERITY_ERROR, std::move(message_code),
        std::format("opening {} expects matching closing {}",
                    left_bound_token_kind.name, right_bound_token_kind.name));
    return std::nullopt;
  }

  return ParseRepeatedBoundResult<TNode>{
      .left_bound_token = left_bound_result.value(),
      .items = std::move(items),
      .right_bound_token = right_bound_result.value(),
  };
}
}  // namespace forge
