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

#ifdef LT_BUILD_TESTS

#include <gtest/gtest.h>

#include <forgec/forge_codegen.hpp>
#include <forgec/forge_message_emitters.hpp>
#include <forgec/handlers/validation/control_flow_validation.hpp>
#include <forgec/handlers/validation/type_resolution.hpp>
#include <forgec/handlers/validation/type_validation.hpp>
#include <forgec/handlers/validation/well_formed.hpp>
#include <forgec/parsing/forge_lexer.hpp>
#include <forgec/parsing/forge_parsers.hpp>
#include <forgec/testing/functional_test_harness.hpp>
#include <langtools/reporting/reporter.hpp>
#include <langtools/syntax_tree/scope/symbol_resolution_handler.hpp>
#include <langtools/syntax_tree/visitors/pass.hpp>

namespace forge {
namespace {
std::string _print_llvm_module(lt::CodegenContext& codegen_context) {
  std::string llvm_module_string;
  llvm::raw_string_ostream llvm_module_stream(llvm_module_string);
  codegen_context.llvm_module().print(llvm_module_stream, nullptr);
  llvm_module_stream.flush();

  std::stringstream result_stream;

  bool only_empty_so_far = true;

  std::istringstream llvm_module_stream_input(llvm_module_string);
  std::string line;
  while (std::getline(llvm_module_stream_input, line)) {
    if (line.starts_with("; ModuleID =")) {
      continue;
    } else if (line.starts_with("source_filename =")) {
      continue;
    } else if (line.starts_with("target datalayout =")) {
      continue;
    } else if (line.starts_with("target triple =")) {
      continue;
    } else if (line.empty() && only_empty_so_far) {
      continue;
    }

    result_stream << line << std::endl;
    only_empty_so_far = false;
  }

  return result_stream.str();
}
}  // namespace

void runFunctionalTest(FunctionalTestOptions&& options) {
  // Load source code
  lt::Source source("--", lt::LineIndexedUnicodeString(options.source.c_str()));

  // Create contexts
  lt::MessageContext message_context;

  auto codegen_context = lt::CodegenContext::create();

  ASSERT_TRUE(codegen_context);

  // Lex tokens
  ForgeLexer lexer;
  std::vector<lt::Token> tokens = lexer.lex(message_context, source);

  // Check tokens
  if (options.on_tokens) {
    options.on_tokens->operator()(tokens);
  }

  // Parse syntax tree
  lt::ParsingContext parsing_context(message_context, tokens);
  std::shared_ptr<TranslationUnit> tree =
      parse_translation_unit(parsing_context);

  // Handle unrecoverable parsing failure
  if (!tree) {
    if (options.expected_state <
        FunctionalTestOptionsState::unrecoverable_parsing_failure) {
      report_messages(std::cerr, message_context);
      FAIL() << "parser returned null tree - did you mean to set "
                "options.expected_state = "
                "FunctionalTestOptionsState::unrecoverable_parsing_failure?";
    }

    return;
  } else {
    if (options.expected_state ==
        FunctionalTestOptionsState::unrecoverable_parsing_failure) {
      FAIL() << "expected unrecoverable parsing failure, but parsing succeeded";
      return;
    }
  }

  // Check syntax tree
  if (!options.expected_syntax_tree_debug.empty()) {
    std::stringstream debug_format_stream;
    lt::DebugFormatter formatter(debug_format_stream);
    tree->format_debug(formatter);

    EXPECT_EQ(options.expected_syntax_tree_debug, debug_format_stream.str());
  }

  if (options.on_syntax_tree) {
    options.on_syntax_tree->operator()(*tree);
  }

  // Run passes
  lt::Pass pass_validation(message_context);
  pass_validation.add_handler(std::make_unique<WellFormedValidationHandler>());
  auto symbol_resolution_handler =
      std::make_unique<lt::SymbolResolutionHandler<BaseForgeNode>>(
          lt::SymbolResolutionHandlerOptions{
              .message_code_undeclared = message_code_error_scope_undeclared,
              .message_code_redeclared =
                  message_code_error_scope_cannot_redeclare,
              .message_code_no_scope = message_code_error_internal_no_scope,
          });
  pass_validation.add_handler(std::move(symbol_resolution_handler));
  pass_validation.add_handler(
      std::make_unique<TypeResolutionHandler>(*codegen_context));
  pass_validation.add_handler(
      std::make_unique<TypeValidationHandler>(*codegen_context));
  pass_validation.add_handler(std::make_unique<ControlFlowValidationHandler>());

  pass_validation.visit(tree);

  // Check messages
  std::stringstream report_stream;
  report_messages(report_stream, message_context);

  if (options.expected_message_report != report_stream.str()) {
    report_messages(std::cerr, message_context);
    ASSERT_EQ(options.expected_message_report, report_stream.str());
  }

  if (message_context.messages().empty()) {
    if (options.expected_state ==
        FunctionalTestOptionsState::errors_after_passes) {
      FAIL() << "expected errors after passes, but none were emitted";
      return;
    }
  } else {
    if (options.expected_state <
        FunctionalTestOptionsState::errors_after_passes) {
      report_messages(std::cerr, message_context);

      FAIL() << "unexpected errors after passes - did you mean to set "
                "options.expected_state = "
                "FunctionalTestOptionsState::errors_after_passes?";
    }

    return;
  }

  // Codegen
  codegen_translation_unit(*codegen_context, tree);

  if (!options.expected_llvm_module_print.empty()) {
    std::string llvm_module_string = _print_llvm_module(*codegen_context);

    ASSERT_EQ(options.expected_llvm_module_print, llvm_module_string);
  }

  auto jit_context = std::move(*codegen_context).jit_compile();

  ASSERT_TRUE(jit_context);

  if (options.on_jit_context) {
    options.on_jit_context->operator()(*jit_context);
  }
}
}  // namespace forge

#endif
