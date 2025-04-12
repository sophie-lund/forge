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

#include <forge/codegen/jit_context.hpp>
#include <forge/language/syntax_tree/translation_unit.hpp>
#include <forge/parsing/domain/token.hpp>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace forge {
/**
 * @brief The expected ending state of the integration test.
 *
 * States should start at @c finished_successfully and be ordered from furthest
 * to least far through the compilation process.
 */
enum class IntegrationTestOptionsState {
  // States furthest through compilation

  finished_successfully,
  errors_after_passes,
  unrecoverable_parsing_failure,

  // States that finished earliest in the compilation process
};

struct IntegrationTestOptions {
  std::string source;
  IntegrationTestOptionsState expected_state{
      IntegrationTestOptionsState::finished_successfully};
  std::optional<std::function<void(const std::vector<Token>&)>> on_tokens;
  std::optional<std::function<void(const TranslationUnit&)>> on_syntax_tree;
  std::string expected_syntax_tree_debug;
  std::optional<std::function<void(const JITContext&)>> on_jit_context;
  std::string expected_message_report;
  std::string expected_llvm_module_print;
};

void runIntegrationTest(IntegrationTestOptions&& options);
}  // namespace forge
