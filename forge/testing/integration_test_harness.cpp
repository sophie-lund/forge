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

#include <gtest/gtest.h>

#include <forge/language/forge_message_emitters.hpp>
#include <forge/language/handlers/validation/well_formed.hpp>
#include <forge/language/parsing/forge_lexer.hpp>
#include <forge/language/parsing/forge_parsers.hpp>
#include <forge/reporting/reporter.hpp>
#include <forge/syntax_tree/scope/symbol_resolution_handler.hpp>
#include <forge/syntax_tree/visitors/pass.hpp>
#include <forge/testing/integration_test_harness.hpp>

namespace forge {
void runIntegrationTest(IntegrationTestOptions&& options) {
  // Load source code
  Source source("--", LineIndexedUnicodeString(options.source.c_str()));

  // Set up context
  MessageContext message_context;
  message_context.enable_codes();

  // Lex tokens
  ForgeLexer lexer;
  std::vector<Token> tokens = lexer.lex(message_context, source);

  // Check tokens
  if (options.on_tokens) {
    options.on_tokens->operator()(tokens);
  }

  // Parse syntax tree
  ParsingContext parsing_context(message_context, tokens);
  std::shared_ptr<TranslationUnit> tree =
      parse_translation_unit(parsing_context);

  // Handle unrecoverable parse failure
  if (!tree) {
    if (options.expected_state ==
        IntegrationTestOptionsState::unrecoverable_parse_failure) {
    } else {
      report_messages(std::cerr, message_context);
      FAIL() << "parser returned null tree";
    }

    return;
  }

  // Check syntax tree
  if (!options.expected_syntax_tree_debug.empty()) {
    std::stringstream debug_format_stream;
    DebugFormatter formatter(debug_format_stream);
    tree->format_debug(formatter);

    EXPECT_EQ(options.expected_syntax_tree_debug, debug_format_stream.str());
  }

  if (options.on_syntax_tree) {
    options.on_syntax_tree->operator()(*tree);
  }

  // Run passes
  Pass pass_validation(message_context);
  pass_validation.add_handler(std::make_unique<WellFormedValidationHandler>());
  auto symbol_resolution_handler =
      std::make_unique<SymbolResolutionHandler<BaseForgeNode>>();
  symbol_resolution_handler->message_code_undeclared =
      message_code_error_scope_undeclared;
  symbol_resolution_handler->message_code_redeclared =
      message_code_error_scope_cannot_redeclare;
  symbol_resolution_handler->message_code_no_scope =
      message_code_error_internal_no_scope;

  pass_validation.add_handler(std::move(symbol_resolution_handler));
  pass_validation.visit(tree);

  // Check messages
  std::stringstream report_stream;
  report_messages(report_stream, message_context);

  if (options.expected_message_report != report_stream.str()) {
    report_messages(std::cerr, message_context);
    ASSERT_EQ(options.expected_message_report, report_stream.str());
  }
}
}  // namespace forge
