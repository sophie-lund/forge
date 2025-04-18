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

#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>

#include <forgec/parsing/forge_lexer.hpp>

using namespace forge;

namespace {
void binary(std::string content) {
  lt::Source source("--", lt::LineIndexedUnicodeString(content.c_str()));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  lexer.lex(message_context, source);
}

void only_legal_chars(std::string content) {
  lt::Source source("--", lt::LineIndexedUnicodeString(content.c_str()));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  lexer.lex(message_context, source);
}

void only_legal_tokens(std::vector<std::string> token_content) {
  std::string content;

  for (const auto& i : token_content) {
    content += i;
  }

  lt::Source source("--", lt::LineIndexedUnicodeString(content.c_str()));

  lt::MessageContext message_context;
  ForgeLexer lexer;

  lexer.lex(message_context, source);

  EXPECT_TRUE(message_context.messages().empty());
}
}  // namespace

FUZZ_TEST(fuzz_lexer, binary);

FUZZ_TEST(fuzz_lexer, only_legal_chars)
    .WithDomains(fuzztest::StringOf(fuzztest::OneOf(
        fuzztest::InRange('a', 'z'), fuzztest::InRange('A', 'Z'),
        fuzztest::InRange('0', '9'),
        fuzztest::ElementOf({'!', '=', '&', '|',  '^', '~',  '+', '-',
                             '>', '*', '/', '\n', ' ', '\t', '%', '<',
                             '(', ')', '{', '}',  ',', ':',  ';', '.'}))));

FUZZ_TEST(fuzz_lexer, only_legal_tokens)
    .WithDomains(fuzztest::VectorOf(fuzztest::OneOf(
        fuzztest::StringOf(fuzztest::OneOf(fuzztest::InRange('a', 'z'),
                                           fuzztest::InRange('A', 'Z'),
                                           fuzztest::InRange('0', '9'))),
        fuzztest::ElementOf(
            {std::string("!"),   std::string("!="),  std::string("&"),
             std::string("&&"),  std::string("&="),  std::string("|"),
             std::string("||"),  std::string("|="),  std::string("^"),
             std::string("^="),  std::string("~"),   std::string("+"),
             std::string("+="),  std::string("-"),   std::string("-="),
             std::string("->"),  std::string("*"),   std::string("**"),
             std::string("**="), std::string("%"),   std::string("%="),
             std::string("="),   std::string("=="),  std::string("<"),
             std::string("<="),  std::string(">"),   std::string(">="),
             std::string("<<"),  std::string("<<="), std::string(">>"),
             std::string(">>="), std::string("("),   std::string(")"),
             std::string("{"),   std::string("}"),   std::string(","),
             std::string(":"),   std::string(";"),   std::string("."),
             std::string(" "),   std::string("\n"),  std::string("\t")}))));
