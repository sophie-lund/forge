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

#include <forge/core/tracing.hpp>
#include <forge/core/unicode.hpp>
#include <forge/language/forge_message_emitters.hpp>
#include <forge/language/parsing/forge_parsers.hpp>
#include <forge/language/parsing/forge_token_kind.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/parsing/syntax_parsing/parser_fragments.hpp>

namespace forge {
namespace {
std::shared_ptr<TypeWithBitWidth> _strip_type_suffix_for_literal_number(
    std::string& value) {
  if (value.ends_with("i8")) {
    value = value.substr(0, value.size() - 2);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::signed_int, 8);
  } else if (value.ends_with("i16")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::signed_int, 16);
  } else if (value.ends_with("i32")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  } else if (value.ends_with("i64")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::signed_int, 64);
  } else if (value.ends_with("u8")) {
    value = value.substr(0, value.size() - 2);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::unsigned_int, 8);
  } else if (value.ends_with("u16")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::unsigned_int, 16);
  } else if (value.ends_with("u32")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::unsigned_int, 32);
  } else if (value.ends_with("u64")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::unsigned_int, 64);
  } else if (value.ends_with("f32")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(SourceRange(),
                                              TypeWithBitWidthKind::float_, 32);
  } else if (value.ends_with("f64")) {
    value = value.substr(0, value.size() - 3);

    return std::make_shared<TypeWithBitWidth>(SourceRange(),
                                              TypeWithBitWidthKind::float_, 64);
  } else if (value.contains(".")) {
    return std::make_shared<TypeWithBitWidth>(SourceRange(),
                                              TypeWithBitWidthKind::float_, 64);
  } else {
    return std::make_shared<TypeWithBitWidth>(
        SourceRange(), TypeWithBitWidthKind::signed_int, 32);
  }
}

int _strip_base_for_literal_number(std::string& value) {
  if (value.starts_with("0x") || value.starts_with("0X")) {
    value = value.substr(2);

    return 16;
  } else if (value.starts_with("0b") || value.starts_with("0B")) {
    value = value.substr(2);

    return 2;
  } else if (value.starts_with("0o") || value.starts_with("0O")) {
    value = value.substr(2);

    return 8;
  } else {
    return 10;
  }
}

template <typename TName>
TraceScope<TName> _parsing_trace_scope(ParsingContext& parsing_context,
                                       TName name) {
  TraceScope trace_scope(name);

  if (parsing_context.are_more_tokens()) {
    const Token& token = parsing_context.peek_next_token();
    trace_scope.trace() << "trying to parse from token(" << token.range.start
                        << "): " << u16string_view_to_string(token.value)
                        << std::endl;
  } else {
    trace_scope.trace() << "trying to parse at end of tokens" << std::endl;
  }

  return trace_scope;
}
}  // namespace

std::shared_ptr<TypeBasic> parse_type_basic_bool(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_BOOL);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: bool" << std::endl;

  return std::make_shared<TypeBasic>(SourceRange(result.value().range),
                                     TypeBasicKind::bool_);
}

std::shared_ptr<TypeBasic> parse_type_basic_void(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_VOID);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: void" << std::endl;

  return std::make_shared<TypeBasic>(SourceRange(result.value().range),
                                     TypeBasicKind::void_);
}

std::shared_ptr<TypeBasic> parse_type_basic_isize(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_ISIZE);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: isize" << std::endl;

  return std::make_shared<TypeBasic>(SourceRange(result.value().range),
                                     TypeBasicKind::isize);
}

std::shared_ptr<TypeBasic> parse_type_basic_usize(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_USIZE);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: usize" << std::endl;

  return std::make_shared<TypeBasic>(SourceRange(result.value().range),
                                     TypeBasicKind::usize);
}

std::shared_ptr<TypeBasic> parse_type_basic(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<TypeBasic>(parsing_context, {
                                                      parse_type_basic_bool,
                                                      parse_type_basic_void,
                                                      parse_type_basic_isize,
                                                      parse_type_basic_usize,
                                                  });
}

std::shared_ptr<TypeSymbol> parse_type_symbol(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type symbol" << std::endl;

  return std::make_shared<TypeSymbol>(
      SourceRange(result.value().range),
      u16string_view_to_string(result.value().value));
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i8(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_I8);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: i8" << std::endl;

  return std::make_shared<TypeWithBitWidth>(
      SourceRange(result.value().range), TypeWithBitWidthKind::signed_int, 8);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i16(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_I16);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: i16" << std::endl;

  return std::make_shared<TypeWithBitWidth>(
      SourceRange(result.value().range), TypeWithBitWidthKind::signed_int, 16);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i32(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_I32);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: i32" << std::endl;

  return std::make_shared<TypeWithBitWidth>(
      SourceRange(result.value().range), TypeWithBitWidthKind::signed_int, 32);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_i64(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_I64);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: i64" << std::endl;

  return std::make_shared<TypeWithBitWidth>(
      SourceRange(result.value().range), TypeWithBitWidthKind::signed_int, 64);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u8(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_U8);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: u8" << std::endl;

  return std::make_shared<TypeWithBitWidth>(
      SourceRange(result.value().range), TypeWithBitWidthKind::unsigned_int, 8);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u16(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_U16);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: u16" << std::endl;

  return std::make_shared<TypeWithBitWidth>(SourceRange(result.value().range),
                                            TypeWithBitWidthKind::unsigned_int,
                                            16);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u32(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_U32);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: u32" << std::endl;

  return std::make_shared<TypeWithBitWidth>(SourceRange(result.value().range),
                                            TypeWithBitWidthKind::unsigned_int,
                                            32);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_u64(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_U64);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: u64" << std::endl;

  return std::make_shared<TypeWithBitWidth>(SourceRange(result.value().range),
                                            TypeWithBitWidthKind::unsigned_int,
                                            64);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_f32(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_F32);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: f32" << std::endl;

  return std::make_shared<TypeWithBitWidth>(SourceRange(result.value().range),
                                            TypeWithBitWidthKind::float_, 32);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width_f64(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_F64);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type: f64" << std::endl;

  return std::make_shared<TypeWithBitWidth>(SourceRange(result.value().range),
                                            TypeWithBitWidthKind::float_, 64);
}

std::shared_ptr<TypeWithBitWidth> parse_type_with_bit_width(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<TypeWithBitWidth>(parsing_context,
                                        {
                                            parse_type_with_bit_width_i8,
                                            parse_type_with_bit_width_i16,
                                            parse_type_with_bit_width_i32,
                                            parse_type_with_bit_width_i64,
                                            parse_type_with_bit_width_u8,
                                            parse_type_with_bit_width_u16,
                                            parse_type_with_bit_width_u32,
                                            parse_type_with_bit_width_u64,
                                            parse_type_with_bit_width_f32,
                                            parse_type_with_bit_width_f64,
                                        });
}

std::shared_ptr<TypeFunction> parse_type_function(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseRepeatedBoundResult<BaseType>> result_args =
      parse_repeated_separated_bound<BaseType>(
          parsing_context, TOKEN_LPAREN, parse_type, TOKEN_COMMA, TOKEN_RPAREN,
          message_code_error_unexpected_token);

  if (!result_args.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_rarrow =
      parse_token_by_kind(parsing_context, TOKEN_RARROW);

  if (result_rarrow.has_value()) {
    std::shared_ptr<BaseType> result_type = parse_type(parsing_context);

    if (result_type == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"type"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    trace_scope.trace() << "parsed type function" << std::endl;

    return std::make_shared<TypeFunction>(
        combine_source_ranges(result_args->left_bound_token.range,
                              result_type->source_range),
        std::move(result_type), std::move(result_args->items));
  } else {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"->"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }
}

std::shared_ptr<TypeStructured> parse_type_structured(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseRepeatedBoundResult<BaseDeclaration>> result_members =
      parse_repeated_bound<BaseDeclaration>(
          parsing_context, TOKEN_LBRACE,
          [](ParsingContext& parsing_context) {
            return parse_declaration(parsing_context, false);
          },
          TOKEN_RBRACE, message_code_error_unexpected_token);
  if (!result_members.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed type structured" << std::endl;

  return std::make_shared<TypeStructured>(
      combine_source_ranges(result_members->left_bound_token.range,
                            result_members.value().items.back()->source_range),
      std::move(result_members.value().items));
}

std::shared_ptr<BaseType> parse_type_term(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<BaseType>(parsing_context, {
                                                     parse_type_basic,
                                                     parse_type_symbol,
                                                     parse_type_with_bit_width,
                                                     parse_type_function,
                                                     parse_type_structured,
                                                 });
}

std::shared_ptr<BaseType> parse_type_unary(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParsePrefixedResult<BaseType>> parse_prefixed_result =
      parse_prefixed<BaseType>(
          parsing_context, {&TOKEN_MUL, &TOKEN_EXP, &TOKEN_KW_CONST},
          parse_type_unary, message_code_error_unexpected_token);

  if (!parse_prefixed_result.has_value()) {
    return parse_type_term(parsing_context);
  }

  SourceRange source_range =
      combine_source_ranges(parse_prefixed_result->prefix_token.range,
                            parse_prefixed_result->child->source_range);

  if (parse_prefixed_result->prefix_token.kind == TOKEN_MUL) {
    trace_scope.trace() << "parsed type deref" << std::endl;

    return std::make_shared<TypeUnary>(std::move(source_range),
                                       TypeUnaryKind::pointer,
                                       std::move(parse_prefixed_result->child));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_EXP) {
    trace_scope.trace() << "parsed type double deref" << std::endl;

    SourceRange source_range_nested = source_range;
    source_range_nested.start.column.value()++;
    source_range_nested.start.offset.value()++;

    return std::make_shared<TypeUnary>(
        std::move(source_range), TypeUnaryKind::pointer,
        std::make_shared<TypeUnary>(std::move(source_range_nested),
                                    TypeUnaryKind::pointer,
                                    std::move(parse_prefixed_result->child)));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_KW_CONST) {
    trace_scope.trace() << "parsed type const" << std::endl;

    parse_prefixed_result->child->is_const = true;
    return parse_prefixed_result->child;
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseType> parse_type(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_type_unary(parsing_context);
}

std::shared_ptr<ValueLiteralBool> parse_value_literal_bool_true(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_TRUE);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed value: true" << std::endl;

  return std::make_shared<ValueLiteralBool>(SourceRange(result.value().range),
                                            true);
}

std::shared_ptr<ValueLiteralBool> parse_value_literal_bool_false(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_KW_FALSE);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed value: false" << std::endl;

  return std::make_shared<ValueLiteralBool>(SourceRange(result.value().range),
                                            false);
}

std::shared_ptr<ValueLiteralBool> parse_value_literal_bool(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<ValueLiteralBool>(parsing_context,
                                        {
                                            // true first, I'm an optimist :3
                                            parse_value_literal_bool_true,
                                            parse_value_literal_bool_false,
                                        });
}

// This code is getting replaced so kinda don't worry about it too much
std::shared_ptr<BaseValue> parse_value_literal_number(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  // Parse the token
  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_LITERAL_NUMBER);

  if (result.has_value()) {
    std::string converted = u16string_view_to_string(result.value().value);

    std::shared_ptr<TypeWithBitWidth> type =
        _strip_type_suffix_for_literal_number(converted);
    int base = _strip_base_for_literal_number(converted);

    std::size_t n_processed;

    int64_t parsed_i64;
    uint64_t parsed_u64;
    double parsed_f64;

    try {
      if (type->type_with_bit_width_kind == TypeWithBitWidthKind::signed_int) {
        parsed_i64 = std::stoll(converted, &n_processed, base);
      } else if (type->type_with_bit_width_kind ==
                 TypeWithBitWidthKind::unsigned_int) {
        parsed_u64 = std::stoull(converted, &n_processed, base);
      } else if (type->type_with_bit_width_kind ==
                 TypeWithBitWidthKind::float_) {
        parsed_f64 = std::stold(converted, &n_processed);
      } else {
        FRG_ABORT("unsupported kind");
      }
    } catch (std::exception) {
      emit_syntax_error_invalid_number_literal(
          parsing_context.message_context(), result.value().range);

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    if (n_processed != converted.size()) {
      emit_syntax_error_invalid_number_literal(
          parsing_context.message_context(), result.value().range);

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    trace_scope.trace() << "parsed value literal number" << std::endl;

    if (type->type_with_bit_width_kind == TypeWithBitWidthKind::signed_int) {
      if (type->bit_width == 8) {
        int8_t truncated = parsed_i64;

        if (truncated != parsed_i64) {
          emit_syntax_warning_number_literal_truncated<int64_t>(
              parsing_context.message_context(), result.value().range, "i8",
              parsed_i64, truncated);

          trace_scope.trace() << "failed with error" << std::endl;

          return nullptr;
        }

        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::signed_int, 8),
            (ValueLiteralNumberUnion){.i8 = truncated});
      } else if (type->bit_width == 16) {
        int16_t truncated = parsed_i64;

        if (truncated != parsed_i64) {
          emit_syntax_warning_number_literal_truncated<int64_t>(
              parsing_context.message_context(), result.value().range, "i16",
              parsed_i64, truncated);

          trace_scope.trace() << "failed with error" << std::endl;

          return nullptr;
        }

        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::signed_int, 16),
            (ValueLiteralNumberUnion){.i16 = truncated});
      } else if (type->bit_width == 32) {
        int32_t truncated = parsed_i64;

        if (truncated != parsed_i64) {
          emit_syntax_warning_number_literal_truncated<int64_t>(
              parsing_context.message_context(), result.value().range, "i32",
              parsed_i64, truncated);

          trace_scope.trace() << "failed with error" << std::endl;

          return nullptr;
        }

        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::signed_int, 32),
            (ValueLiteralNumberUnion){.i32 = truncated});
      } else {
        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::signed_int, 64),
            (ValueLiteralNumberUnion){.i64 = parsed_i64});
      }
    } else if (type->type_with_bit_width_kind ==
               TypeWithBitWidthKind::unsigned_int) {
      if (type->bit_width == 8) {
        uint8_t truncated = parsed_u64;

        if (truncated != parsed_u64) {
          emit_syntax_warning_number_literal_truncated<uint64_t>(
              parsing_context.message_context(), result.value().range, "u8",
              parsed_u64, truncated);

          trace_scope.trace() << "failed with error" << std::endl;

          return nullptr;
        }

        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::unsigned_int, 8),
            (ValueLiteralNumberUnion){.u8 = truncated});
      } else if (type->bit_width == 16) {
        uint16_t truncated = parsed_u64;

        if (truncated != parsed_u64) {
          emit_syntax_warning_number_literal_truncated<uint64_t>(
              parsing_context.message_context(), result.value().range, "u16",
              parsed_u64, truncated);

          trace_scope.trace() << "failed with error" << std::endl;

          return nullptr;
        }

        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::unsigned_int, 16),
            (ValueLiteralNumberUnion){.u16 = truncated});
      } else if (type->bit_width == 32) {
        uint32_t truncated = parsed_u64;

        if (truncated != parsed_u64) {
          emit_syntax_warning_number_literal_truncated<uint64_t>(
              parsing_context.message_context(), result.value().range, "u32",
              parsed_u64, truncated);

          trace_scope.trace() << "failed with error" << std::endl;

          return nullptr;
        }

        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::unsigned_int, 32),
            (ValueLiteralNumberUnion){.u32 = truncated});
      } else {
        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::unsigned_int, 64),
            (ValueLiteralNumberUnion){.u64 = parsed_u64});
      }
    } else if (type->type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
      if (type->bit_width == 32) {
        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::float_, 32),
            (ValueLiteralNumberUnion){.f32 = (float)parsed_f64});
      } else {
        return std::make_shared<ValueLiteralNumber>(
            SourceRange(result.value().range),
            std::make_shared<TypeWithBitWidth>(
                SourceRange(), TypeWithBitWidthKind::float_, 64),
            (ValueLiteralNumberUnion){.f64 = parsed_f64});
      }
    } else {
      FRG_ABORT("unsupported kind");
    }
  }

  trace_scope.trace() << "no match" << std::endl;

  return nullptr;
}

std::shared_ptr<ValueSymbol> parse_value_symbol(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed value symbol" << std::endl;

  return std::make_shared<ValueSymbol>(
      SourceRange(result.value().range),
      u16string_view_to_string(result.value().value));
}

std::shared_ptr<BaseValue> parse_value_parenthesis(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_bound<BaseValue>(parsing_context, TOKEN_LPAREN, parse_value,
                                TOKEN_RPAREN,
                                message_code_error_unexpected_token);
}

std::shared_ptr<BaseValue> parse_value_term(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<BaseValue>(parsing_context,
                                 {
                                     parse_value_literal_bool,
                                     parse_value_literal_number,
                                     parse_value_symbol,
                                     parse_value_parenthesis,
                                 });
}

std::shared_ptr<BaseValue> parse_value_member_access(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_term, {&TOKEN_DOT},
          parse_value_member_access, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  trace_scope.trace() << "parsed value operation: lhs.rhs" << std::endl;

  return std::make_shared<ValueBinary>(
      combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                            parse_binary_operation_result->rhs->source_range),
      BinaryOperator::member_access,
      std::move(parse_binary_operation_result->lhs),
      std::move(parse_binary_operation_result->rhs));
}

std::shared_ptr<BaseValue> parse_value_function_call(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::shared_ptr<BaseValue> callee =
      parse_optional<BaseValue>(parsing_context, parse_value_member_access);

  if (callee == nullptr) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<ParseRepeatedBoundResult<BaseValue>> args =
      parse_repeated_separated_bound<BaseValue>(
          parsing_context, TOKEN_LPAREN, parse_value, TOKEN_COMMA, TOKEN_RPAREN,
          message_code_error_unexpected_token);

  if (!args.has_value()) {
    return callee;
  }

  trace_scope.trace() << "parsed value function call" << std::endl;

  return std::make_shared<ValueCall>(
      combine_source_ranges(callee->source_range,
                            args->right_bound_token.range),
      std::move(callee), std::move(args.value().items));
}

std::shared_ptr<BaseValue> parse_value_unary(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParsePrefixedResult<BaseValue>> parse_prefixed_result =
      parse_prefixed<BaseValue>(parsing_context,
                                {&TOKEN_MUL, &TOKEN_BIT_AND, &TOKEN_SUB,
                                 &TOKEN_ADD, &TOKEN_BIT_NOT, &TOKEN_BOOL_NOT},
                                parse_value_unary,
                                message_code_error_unexpected_token);

  if (!parse_prefixed_result.has_value()) {
    return parse_value_function_call(parsing_context);
  }

  SourceRange source_range =
      combine_source_ranges(parse_prefixed_result->prefix_token.range,
                            parse_prefixed_result->child->source_range);

  if (parse_prefixed_result->prefix_token.kind == TOKEN_MUL) {
    trace_scope.trace() << "parsed value operation: *operand" << std::endl;

    return std::make_shared<ValueUnary>(
        std::move(source_range), UnaryOperator::deref,
        std::move(parse_prefixed_result->child));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_BIT_AND) {
    trace_scope.trace() << "parsed value operation: &operand" << std::endl;

    return std::make_shared<ValueUnary>(
        std::move(source_range), UnaryOperator::getaddr,
        std::move(parse_prefixed_result->child));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_SUB) {
    trace_scope.trace() << "parsed value operation: -operand" << std::endl;

    return std::make_shared<ValueUnary>(
        std::move(source_range), UnaryOperator::neg,
        std::move(parse_prefixed_result->child));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_ADD) {
    trace_scope.trace() << "parsed value operation: +operand" << std::endl;

    return std::make_shared<ValueUnary>(
        std::move(source_range), UnaryOperator::pos,
        std::move(parse_prefixed_result->child));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_BIT_NOT) {
    trace_scope.trace() << "parsed value operation: ~operand" << std::endl;

    return std::make_shared<ValueUnary>(
        std::move(source_range), UnaryOperator::bit_not,
        std::move(parse_prefixed_result->child));
  } else if (parse_prefixed_result->prefix_token.kind == TOKEN_BOOL_NOT) {
    trace_scope.trace() << "parsed value operation: !operand" << std::endl;

    return std::make_shared<ValueUnary>(
        std::move(source_range), UnaryOperator::bool_not,
        std::move(parse_prefixed_result->child));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value_exponentiation(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_unary, {&TOKEN_EXP},
          parse_value_exponentiation, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  trace_scope.trace() << "parsed value operation: lhs ** rhs" << std::endl;

  return std::make_shared<ValueBinary>(
      combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                            parse_binary_operation_result->rhs->source_range),
      BinaryOperator::exp, std::move(parse_binary_operation_result->lhs),
      std::move(parse_binary_operation_result->rhs));
}

std::shared_ptr<BaseValue> parse_value_multiplicative(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_exponentiation,
          {&TOKEN_MUL, &TOKEN_DIV, &TOKEN_MOD}, parse_value_multiplicative,
          message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  if (parse_binary_operation_result->operator_token->kind == TOKEN_MUL) {
    trace_scope.trace() << "parsed value operation: lhs * rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::mul, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_DIV) {
    trace_scope.trace() << "parsed value operation: lhs / rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::div, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_MOD) {
    trace_scope.trace() << "parsed value operation: lhs % rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::mod, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value_additive(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_multiplicative, {&TOKEN_ADD, &TOKEN_SUB},
          parse_value_additive, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  if (parse_binary_operation_result->operator_token->kind == TOKEN_ADD) {
    trace_scope.trace() << "parsed value operation: lhs + rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::add, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_SUB) {
    trace_scope.trace() << "parsed value operation: lhs - rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::sub, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value_bit_shifts(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_additive,
          {&TOKEN_BIT_SHL, &TOKEN_BIT_SHR}, parse_value_bit_shifts,
          message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  if (parse_binary_operation_result->operator_token->kind == TOKEN_BIT_SHL) {
    trace_scope.trace() << "parsed value operation: lhs << rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_shl, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_BIT_SHR) {
    trace_scope.trace() << "parsed value operation: lhs >> rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_shr, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value_binary_conjunctive(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_bit_shifts,
          {&TOKEN_BIT_AND, &TOKEN_BIT_XOR}, parse_value_binary_conjunctive,
          message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  if (parse_binary_operation_result->operator_token->kind == TOKEN_BIT_AND) {
    trace_scope.trace() << "parsed value operation: lhs & rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_and, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_BIT_XOR) {
    trace_scope.trace() << "parsed value operation: lhs ^ rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_xor, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value_binary_disjunctive(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_binary_conjunctive, {&TOKEN_BIT_OR},
          parse_value_binary_disjunctive, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  trace_scope.trace() << "parsed value operation: lhs | rhs" << std::endl;

  return std::make_shared<ValueBinary>(
      combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                            parse_binary_operation_result->rhs->source_range),
      BinaryOperator::bit_or, std::move(parse_binary_operation_result->lhs),
      std::move(parse_binary_operation_result->rhs));
}

std::shared_ptr<BaseValue> parse_value_comparative(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_binary_disjunctive,
          {&TOKEN_EQ, &TOKEN_NE, &TOKEN_LT, &TOKEN_LE, &TOKEN_GT, &TOKEN_GE},
          parse_value_comparative, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  if (parse_binary_operation_result->operator_token->kind == TOKEN_EQ) {
    trace_scope.trace() << "parsed value operation: lhs == rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::eq, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_NE) {
    trace_scope.trace() << "parsed value operation: lhs != rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::ne, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_LT) {
    trace_scope.trace() << "parsed value operation: lhs < rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::lt, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_LE) {
    trace_scope.trace() << "parsed value operation: lhs <= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::le, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_GT) {
    trace_scope.trace() << "parsed value operation: lhs > rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::gt, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind == TOKEN_GE) {
    trace_scope.trace() << "parsed value operation: lhs >= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::ge, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value_boolean_and(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_comparative, {&TOKEN_BOOL_AND},
          parse_value_boolean_and, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  trace_scope.trace() << "parsed value operation: lhs && rhs" << std::endl;

  return std::make_shared<ValueBinary>(
      combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                            parse_binary_operation_result->rhs->source_range),
      BinaryOperator::bool_and, std::move(parse_binary_operation_result->lhs),
      std::move(parse_binary_operation_result->rhs));
}

std::shared_ptr<BaseValue> parse_value_boolean_or(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_boolean_and, {&TOKEN_BOOL_OR},
          parse_value_boolean_or, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  trace_scope.trace() << "parsed value operation: lhs || rhs" << std::endl;

  return std::make_shared<ValueBinary>(
      combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                            parse_binary_operation_result->rhs->source_range),
      BinaryOperator::bool_or, std::move(parse_binary_operation_result->lhs),
      std::move(parse_binary_operation_result->rhs));
}

std::shared_ptr<BaseValue> parse_value_cast(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseNode>>
      parse_binary_operation_result = parse_binary_operation<
          BaseNode, std::function<std::shared_ptr<BaseNode>(ParsingContext&)>>(
          parsing_context,
          [](ParsingContext& parsing_context) -> std::shared_ptr<BaseNode> {
            return parse_value_boolean_or(parsing_context);
          },
          {&TOKEN_KW_AS},
          [](ParsingContext& parsing_context) -> std::shared_ptr<BaseNode> {
            return parse_type(parsing_context);
          },
          message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return std::static_pointer_cast<BaseValue>(
        parse_binary_operation_result->lhs);
  }

  trace_scope.trace() << "parsed value cast" << std::endl;

  return std::make_shared<ValueCast>(
      combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                            parse_binary_operation_result->rhs->source_range),
      std::static_pointer_cast<BaseValue>(
          std::move(parse_binary_operation_result->lhs)),
      std::static_pointer_cast<BaseType>(
          std::move(parse_binary_operation_result->rhs)));
}

std::shared_ptr<BaseValue> parse_value_assignments(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseBinaryOperationResult<BaseValue>>
      parse_binary_operation_result = parse_binary_operation<BaseValue>(
          parsing_context, parse_value_cast,
          {
              &TOKEN_BIT_AND_ASSIGN,
              &TOKEN_BIT_OR_ASSIGN,
              &TOKEN_BIT_XOR_ASSIGN,
              &TOKEN_BIT_SHL_ASSIGN,
              &TOKEN_BIT_SHR_ASSIGN,
              &TOKEN_ADD_ASSIGN,
              &TOKEN_SUB_ASSIGN,
              &TOKEN_MUL_ASSIGN,
              &TOKEN_EXP_ASSIGN,
              &TOKEN_DIV_ASSIGN,
              &TOKEN_MOD_ASSIGN,
              &TOKEN_ASSIGN,
          },
          parse_value_assignments, message_code_error_unexpected_token);

  if (!parse_binary_operation_result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!parse_binary_operation_result->operator_token.has_value()) {
    return parse_binary_operation_result->lhs;
  }

  if (parse_binary_operation_result->operator_token->kind ==
      TOKEN_BIT_AND_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs &= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_and_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_BIT_OR_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs |= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_or_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_BIT_XOR_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs ^= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_xor_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_BIT_SHL_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs <<= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_shl_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_BIT_SHR_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs >>= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::bit_shr_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_ADD_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs += rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::add_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_SUB_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs -= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::sub_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_MUL_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs *= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::mul_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_EXP_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs **= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::exp_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_DIV_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs /= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::div_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_MOD_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs %= rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::mod_assign,
        std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else if (parse_binary_operation_result->operator_token->kind ==
             TOKEN_ASSIGN) {
    trace_scope.trace() << "parsed value operation: lhs = rhs" << std::endl;

    return std::make_shared<ValueBinary>(
        combine_source_ranges(parse_binary_operation_result->lhs->source_range,
                              parse_binary_operation_result->rhs->source_range),
        BinaryOperator::assign, std::move(parse_binary_operation_result->lhs),
        std::move(parse_binary_operation_result->rhs));
  } else {
    FRG_ABORT("unsupported kind");
  }
}

std::shared_ptr<BaseValue> parse_value(ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_value_assignments(parsing_context);
}

std::shared_ptr<StatementBasic> parse_statement_continue(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_continue =
      parse_token_by_kind(parsing_context, TOKEN_KW_CONTINUE);
  if (!result_kw_continue.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_semicolon =
      parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);

  if (!result_semicolon.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       result_semicolon.value().range, {";"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed statement continue" << std::endl;

  return std::make_shared<StatementBasic>(
      combine_source_ranges(result_kw_continue.value().range,
                            result_semicolon.value().range),
      StatementBasicKind::continue_);
}

std::shared_ptr<StatementBasic> parse_statement_break(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_break =
      parse_token_by_kind(parsing_context, TOKEN_KW_BREAK);
  if (!result_kw_break.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_semicolon =
      parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);

  if (!result_semicolon.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       result_semicolon.value().range, {";"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed statement break" << std::endl;

  return std::make_shared<StatementBasic>(
      combine_source_ranges(result_kw_break.value().range,
                            result_semicolon.value().range),
      StatementBasicKind::break_);
}

std::shared_ptr<StatementValue> parse_statement_execute(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseSuffixedResult<BaseValue>> result =
      parse_suffixed<BaseValue>(parsing_context, parse_value,
                                {&TOKEN_SEMICOLON});

  if (!result.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  if (!result->suffix_token.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {";"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed statement value" << std::endl;

  return std::make_shared<StatementValue>(
      combine_source_ranges(result->child->source_range,
                            result->suffix_token->range),
      StatementValueKind::execute, std::move(result->child));
}

std::shared_ptr<BaseStatement> parse_statement_return(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_return =
      parse_token_by_kind(parsing_context, TOKEN_KW_RETURN);
  if (!result_kw_return.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_semicolon =
      parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);

  if (!result_semicolon.has_value()) {
    std::shared_ptr<BaseValue> result_value = parse_value(parsing_context);

    if (result_value == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"value"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    std::optional<Token> result_semicolon =
        parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);

    if (!result_semicolon.has_value()) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {";"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    trace_scope.trace() << "parsed statement return value" << std::endl;

    return std::make_shared<StatementValue>(
        combine_source_ranges(result_kw_return.value().range,
                              result_semicolon.value().range),
        StatementValueKind::return_, std::move(result_value));
  } else {
    trace_scope.trace() << "parsed statement return void" << std::endl;

    return std::make_shared<StatementBasic>(
        combine_source_ranges(result_kw_return.value().range,
                              result_semicolon.value().range),
        StatementBasicKind::return_void);
  }
}

std::shared_ptr<StatementBlock> parse_statement_block(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<ParseRepeatedBoundResult<BaseStatement>> statements =
      parse_repeated_separated_bound<BaseStatement>(
          parsing_context, TOKEN_LBRACE, parse_statement, TOKEN_COMMA,
          TOKEN_RBRACE, message_code_error_unexpected_token);

  if (!statements.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed statement block" << std::endl;

  return std::make_shared<StatementBlock>(
      combine_source_ranges(statements->left_bound_token.range,
                            statements->right_bound_token.range),
      std::move(statements.value().items));
}

std::shared_ptr<StatementIf> parse_statement_if(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_if =
      parse_token_by_kind(parsing_context, TOKEN_KW_IF);
  if (!result_kw_if.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::shared_ptr<BaseValue> condition = parse_value(parsing_context);
  if (condition == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"condition"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::shared_ptr<StatementBlock> then = parse_statement_block(parsing_context);
  if (then == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"then clause"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_kw_else =
      parse_token_by_kind(parsing_context, TOKEN_KW_ELSE);
  if (!result_kw_else.has_value()) {
    trace_scope.trace() << "parsed statement if with 1 clause" << std::endl;

    return std::make_shared<StatementIf>(
        combine_source_ranges(result_kw_if.value().range,
                              condition->source_range),
        std::move(condition), std::move(then), nullptr);
  }

  if (parsing_context.are_more_tokens() &&
      parsing_context.peek_next_token().kind == TOKEN_KW_IF) {
    std::shared_ptr<StatementIf> else_if = parse_statement_if(parsing_context);
    if (else_if == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"else if clause"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    trace_scope.trace() << "parsed statement if with else if clause"
                        << std::endl;

    return std::make_shared<StatementIf>(
        combine_source_ranges(result_kw_if.value().range,
                              condition->source_range),
        std::move(condition), std::move(then), std::move(else_if));
  }

  std::shared_ptr<StatementBlock> else_ =
      parse_statement_block(parsing_context);
  if (else_ == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"else clause"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed statement if with else clause" << std::endl;

  return std::make_shared<StatementIf>(
      combine_source_ranges(result_kw_if.value().range,
                            condition->source_range),
      std::move(condition), std::move(then), std::move(else_));
}

std::shared_ptr<StatementWhile> parse_statement_while(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_while =
      parse_token_by_kind(parsing_context, TOKEN_KW_WHILE);
  if (!result_kw_while.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::shared_ptr<BaseValue> condition = parse_value(parsing_context);
  if (condition == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"condition"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::shared_ptr<StatementBlock> body = parse_statement_block(parsing_context);
  if (body == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"body clause"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  return std::make_shared<StatementWhile>(
      combine_source_ranges(result_kw_while.value().range,
                            condition->source_range),
      std::move(condition), std::move(body));
}

std::shared_ptr<StatementWhile> parse_statement_do_while(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_do =
      parse_token_by_kind(parsing_context, TOKEN_KW_DO);
  if (!result_kw_do.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::shared_ptr<StatementBlock> body = parse_statement_block(parsing_context);
  if (body == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"body clause"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_kw_while =
      parse_token_by_kind(parsing_context, TOKEN_KW_WHILE);
  if (!result_kw_while.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"while"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::shared_ptr<BaseValue> condition = parse_value(parsing_context);
  if (condition == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"condition"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_semicolon =
      parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);
  if (!result_semicolon.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {";"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  auto statement = std::make_shared<StatementWhile>(
      combine_source_ranges(result_kw_while.value().range,
                            result_semicolon.value().range),
      std::move(condition), std::move(body));

  statement->is_do_while = true;

  return statement;
}

std::shared_ptr<BaseStatement> parse_statement(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<BaseStatement>(
      parsing_context,
      {parse_statement_continue, parse_statement_break, parse_statement_execute,
       parse_statement_return, parse_statement_block, parse_statement_if,
       parse_statement_while, parse_statement_do_while});
}

std::shared_ptr<DeclarationVariable> parse_declaration_variable(
    ParsingContext& parsing_context, bool with_keyword, bool with_semicolon) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  bool is_const = false;

  if (with_keyword) {
    if (!parsing_context.are_more_tokens()) {
      trace_scope.trace() << "no match" << std::endl;

      return nullptr;
    } else if (parsing_context.peek_next_token().kind == TOKEN_KW_CONST) {
      is_const = true;
      parsing_context.read_next_token();
    } else if (parsing_context.peek_next_token().kind == TOKEN_KW_LET) {
      parsing_context.read_next_token();
    } else {
      trace_scope.trace() << "no match" << std::endl;

      return nullptr;
    }
  }

  std::optional<Token> result_symbol =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result_symbol.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"symbol"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  auto declaration = std::make_shared<DeclarationVariable>(
      SourceRange(result_symbol.value().range),
      u16string_view_to_string(result_symbol.value().value), nullptr, nullptr);

  declaration->is_const = is_const;

  std::optional<Token> result_colon =
      parse_token_by_kind(parsing_context, TOKEN_COLON);
  if (result_colon.has_value()) {
    std::shared_ptr<BaseType> result_type = parse_type(parsing_context);
    if (result_type == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"type"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    declaration->type = std::move(result_type);
  }

  std::optional<Token> result_assign =
      parse_token_by_kind(parsing_context, TOKEN_ASSIGN);
  if (result_assign.has_value()) {
    std::shared_ptr<BaseValue> result_value = parse_value(parsing_context);
    if (result_value == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"value"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    declaration->initial_value = std::move(result_value);
  }

  if (with_semicolon) {
    std::optional<Token> result_semicolon =
        parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);
    if (!result_semicolon.has_value()) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {";"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }
  }

  trace_scope.trace() << "parsed declaration variable" << std::endl;

  return declaration;
}

std::shared_ptr<DeclarationFunction> parse_declaration_function(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_func =
      parse_token_by_kind(parsing_context, TOKEN_KW_FUNC);
  if (!result_kw_func.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_symbol =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result_symbol.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"symbol"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::optional<ParseRepeatedBoundResult<DeclarationVariable>> result_args =
      parse_repeated_separated_bound<DeclarationVariable>(
          parsing_context, TOKEN_LPAREN,
          [](ParsingContext& context) {
            return parse_declaration_variable(context, false, false);
          },
          TOKEN_COMMA, TOKEN_RPAREN, message_code_error_unexpected_token);

  if (!result_args.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"("});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  auto declaration = std::make_shared<DeclarationFunction>(
      SourceRange(result_symbol->range),
      u16string_view_to_string(result_symbol->value),
      std::move(result_args.value().items), nullptr, nullptr);

  std::optional<Token> result_rarrow =
      parse_token_by_kind(parsing_context, TOKEN_RARROW);
  if (result_rarrow.has_value()) {
    std::shared_ptr<BaseType> result_type = parse_type(parsing_context);
    if (result_type == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"type"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    declaration->return_type = std::move(result_type);
  }

  std::optional<Token> result_semicolon =
      parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);
  if (!result_semicolon.has_value()) {
    std::shared_ptr<StatementBlock> body =
        parse_statement_block(parsing_context);
    if (!body) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"function body"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    declaration->body = std::move(body);
  }

  trace_scope.trace() << "parsed declaration function" << std::endl;

  return declaration;
}

std::shared_ptr<DeclarationTypeAlias> parse_declaration_type_alias(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  bool is_explicit = false;

  std::optional<Token> result_kw_explicit =
      parse_token_by_kind(parsing_context, TOKEN_KW_EXPLICIT);
  if (result_kw_explicit.has_value()) {
    is_explicit = true;
  }

  std::optional<Token> result_kw_type =
      parse_token_by_kind(parsing_context, TOKEN_KW_TYPE);
  if (!result_kw_type.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_symbol =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result_symbol.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"symbol"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_assign =
      parse_token_by_kind(parsing_context, TOKEN_ASSIGN);
  if (!result_assign.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"="});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::shared_ptr<BaseType> result_type = parse_type(parsing_context);
  if (result_type == nullptr) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"type"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_semicolon =
      parse_token_by_kind(parsing_context, TOKEN_SEMICOLON);
  if (!result_semicolon.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {";"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  trace_scope.trace() << "parsed declaration type alias" << std::endl;

  return std::make_shared<DeclarationTypeAlias>(
      SourceRange(result_symbol.value().range),
      u16string_view_to_string(result_symbol->value), std::move(result_type),
      is_explicit);
}

std::shared_ptr<DeclarationStructuredType> parse_declaration_structured_type(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  StructuredTypeKind kind;

  if (!parsing_context.are_more_tokens()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  } else if (parsing_context.peek_next_token().kind == TOKEN_KW_STRUCT) {
    kind = StructuredTypeKind::struct_;
    parsing_context.read_next_token();
  } else if (parsing_context.peek_next_token().kind == TOKEN_KW_INTERFACE) {
    kind = StructuredTypeKind::interface;
    parsing_context.read_next_token();
  } else {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_symbol =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result_symbol.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"symbol"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  auto declaration = std::make_shared<DeclarationStructuredType>(
      SourceRange(result_symbol.value().range),
      u16string_view_to_string(result_symbol.value().value), kind,
      std::vector<std::shared_ptr<BaseDeclaration>>(),
      std::vector<std::shared_ptr<TypeSymbol>>());

  std::optional<Token> result_kw_inherits =
      parse_token_by_kind(parsing_context, TOKEN_KW_INHERITS);
  if (result_kw_inherits.has_value()) {
    while (parsing_context.are_more_tokens()) {
      std::shared_ptr<TypeSymbol> result_type =
          parse_type_symbol(parsing_context);

      if (result_type == nullptr) {
        emit_syntax_error_unexpected_token(
            parsing_context.message_context(),
            parsing_context.peek_next_token().range, {"type"});

        trace_scope.trace() << "failed with error" << std::endl;

        return nullptr;
      }

      declaration->inherits.push_back(std::move(result_type));

      if (parsing_context.are_more_tokens() &&
          parsing_context.peek_next_token().kind == TOKEN_COMMA) {
        parsing_context.read_next_token();
      } else {
        break;
      }
    }
  }

  std::optional<ParseRepeatedBoundResult<BaseDeclaration>> result_members =
      parse_repeated_bound<BaseDeclaration>(
          parsing_context, TOKEN_LBRACE,
          [](ParsingContext& parsing_context) {
            return parse_declaration(parsing_context, false);
          },
          TOKEN_RBRACE, message_code_error_unexpected_token);
  if (!result_members.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"{"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  declaration->members = std::move(result_members.value().items);

  trace_scope.trace() << "parsed declaration structured type" << std::endl;

  return declaration;
}

std::shared_ptr<DeclarationNamespace> parse_declaration_namespace(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  std::optional<Token> result_kw_namespace =
      parse_token_by_kind(parsing_context, TOKEN_KW_NAMESPACE);
  if (!result_kw_namespace.has_value()) {
    trace_scope.trace() << "no match" << std::endl;

    return nullptr;
  }

  std::optional<Token> result_symbol =
      parse_token_by_kind(parsing_context, TOKEN_SYMBOL);
  if (!result_symbol.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"symbol"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  auto declaration = std::make_shared<DeclarationNamespace>(
      SourceRange(result_symbol.value().range),
      u16string_view_to_string(result_symbol.value().value),
      std::vector<std::shared_ptr<BaseDeclaration>>());

  std::optional<ParseRepeatedBoundResult<BaseDeclaration>> result_members =
      parse_repeated_bound<BaseDeclaration>(
          parsing_context, TOKEN_LBRACE,
          [](ParsingContext& parsing_context) {
            return parse_declaration(parsing_context);
          },
          TOKEN_RBRACE, message_code_error_unexpected_token);
  if (!result_members.has_value()) {
    emit_syntax_error_unexpected_token(parsing_context.message_context(),
                                       parsing_context.peek_next_token().range,
                                       {"{"});

    trace_scope.trace() << "failed with error" << std::endl;

    return nullptr;
  }

  declaration->members = std::move(result_members.value().items);

  trace_scope.trace() << "parsed declaration namespace" << std::endl;

  return declaration;
}

std::shared_ptr<BaseDeclaration> parse_declaration(
    ParsingContext& parsing_context, bool with_variable_keyword) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  return parse_any_of<BaseDeclaration>(
      parsing_context,
      {
          [with_variable_keyword](ParsingContext& parsing_context) {
            return parse_declaration_variable(parsing_context,
                                              with_variable_keyword, true);
          },
          [](ParsingContext& parsing_context) {
            return parse_declaration_function(parsing_context);
          },
          [](ParsingContext& parsing_context) {
            return parse_declaration_type_alias(parsing_context);
          },
          [](ParsingContext& parsing_context) {
            return parse_declaration_structured_type(parsing_context);
          },
          [](ParsingContext& parsing_context) {
            return parse_declaration_namespace(parsing_context);
          },
      });
}

std::shared_ptr<TranslationUnit> parse_translation_unit(
    ParsingContext& parsing_context) {
  TraceScope trace_scope =
      _parsing_trace_scope(parsing_context, FRG_FUNCTION_NAME);

  auto translation_unit = std::make_shared<TranslationUnit>(
      SourceRange(), std::vector<std::shared_ptr<BaseDeclaration>>());

  while (parsing_context.are_more_tokens()) {
    std::shared_ptr<BaseDeclaration> declaration =
        parse_declaration(parsing_context);
    if (declaration == nullptr) {
      emit_syntax_error_unexpected_token(
          parsing_context.message_context(),
          parsing_context.peek_next_token().range, {"declaration"});

      trace_scope.trace() << "failed with error" << std::endl;

      return nullptr;
    }

    translation_unit->declarations.push_back(std::move(declaration));
  }

  return translation_unit;
}
}  // namespace forge
