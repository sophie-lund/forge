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

// DEVELOPER NOTE
//
// This is implemented as a benchmark and not a fuzz test because Google's
// fuzztest isn't a great fit for this use case imo. But using their microbench
// library gives us some nice useability features.

#include <benchmark/benchmark.h>

#include <forgec/forge_codegen.hpp>
#include <forgec/forge_formatters.hpp>
#include <forgec/parsing/forge_lexer.hpp>
#include <forgec/parsing/forge_parsers.hpp>
#include <forgec/testing/random_syntax_tree_generator.hpp>
#include <langtools/core/init.hpp>
#include <langtools/reporting/reporter.hpp>
#include <langtools/syntax_tree/operations/comparators.hpp>
#include <sstream>

using namespace forge;

namespace {
void reflective_operations(benchmark::State& state) {
  if (!lt::is_initted()) {
    LT_ASSERT(lt::init().has_value(), "error when initializing Langtools");
  }

  auto codegen_context = lt::CodegenContext::create();

  LT_ASSERT(codegen_context, "error when creating codegen context: "
                                 << codegen_context.error().message);

  RandomSyntaxTreeGenerator generator;

  for (auto _ : state) {
    // Generate tree
    std::shared_ptr<BaseType> tree = generator.generate_type();

    LT_ASSERT(tree != nullptr, "generated tree was nullptr");

    // Format it
    std::stringstream format_stream;
    FormattingOptions formatting_options(format_stream);

    format_type(formatting_options, tree);

    format_stream.flush();

    std::string format_string = format_stream.str();

    // Check if the formatting was empty
    if (format_string.empty()) {
      std::cout << "ORIGINAL TREE:" << std::endl;
      lt::DebugFormatter formatter(std::cout);
      tree->format_debug(formatter);
      std::cout << std::endl << std::endl;

      LT_ABORT("tree was formatted to an empty string");
    }

    // Lex it
    lt::MessageContext message_context;

    lt::Source source("--",
                      lt::LineIndexedUnicodeString(format_string.c_str()));

    ForgeLexer lexer;
    std::vector<lt::Token> tokens = lexer.lex(message_context, source);

    // Check if there were any errors
    if (!message_context.messages().empty()) {
      std::cout << "ORIGINAL TREE:" << std::endl;
      lt::DebugFormatter formatter(std::cout);
      tree->format_debug(formatter);
      std::cout << std::endl << std::endl;

      std::cout << "FORMATTING OUTPUT:" << std::endl;
      std::cout << format_string << std::endl;

      std::cout << "MESSAGES:" << std::endl;
      report_messages(std::cout, message_context);

      LT_ABORT("lexer emitted errors");
    }

    // Check if there are no tokens
    if (tokens.empty()) {
      std::cout << "ORIGINAL TREE:" << std::endl;
      lt::DebugFormatter formatter(std::cout);
      tree->format_debug(formatter);
      std::cout << std::endl << std::endl;

      std::cout << "FORMATTING OUTPUT:" << std::endl;
      std::cout << format_string << std::endl;

      LT_ABORT("tree was lexed to an empty token vector");
    }

    // Parse it
    lt::ParsingContext parsing_context(message_context, tokens);

    std::shared_ptr<BaseType> tree_parsed = parse_type(parsing_context);

    // Check if there were any errors
    if (!message_context.messages().empty()) {
      std::cout << "ORIGINAL TREE:" << std::endl;
      lt::DebugFormatter formatter(std::cout);
      tree->format_debug(formatter);
      std::cout << std::endl << std::endl;

      std::cout << "FORMATTING OUTPUT:" << std::endl;
      std::cout << format_string << std::endl;

      std::cout << "MESSAGES:" << std::endl;
      report_messages(std::cout, message_context);

      LT_ABORT("lexer emitted errors");
    }

    // Check if the parsed tree is nullptr
    if (tree_parsed == nullptr) {
      std::cout << "ORIGINAL TREE:" << std::endl;
      lt::DebugFormatter formatter(std::cout);
      tree->format_debug(formatter);
      std::cout << std::endl << std::endl;

      std::cout << "FORMATTING OUTPUT:" << std::endl;
      std::cout << format_string << std::endl;

      LT_ABORT("tree was parsed to a nullptr");
    }

    // Compare parsed tree to original
    if (!lt::compare_nodes(tree, tree_parsed)) {
      std::cout << "ORIGINAL TREE:" << std::endl;
      lt::DebugFormatter formatter(std::cout);
      tree->format_debug(formatter);
      std::cout << std::endl << std::endl;

      std::cout << "PARSED TREE:" << std::endl;
      tree_parsed->format_debug(formatter);
      std::cout << std::endl << std::endl;

      std::cout << "FORMATTING OUTPUT:" << std::endl;
      std::cout << format_string << std::endl;

      LT_ABORT("parsed tree was not equal to original");
    }
  }

  if (lt::is_initted()) {
    LT_ASSERT(lt::cleanup().has_value(), "error when cleaning up Langtools");
  }
}
}  // namespace

BENCHMARK(reflective_operations);
