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

#include <forgec/syntax_tree/translation_unit.hpp>
#include <functional>
#include <langtools/codegen/jit_context.hpp>
#include <langtools/parsing/domain/token.hpp>
#include <optional>
#include <string>
#include <vector>

namespace forge {
/**
 * @brief The expected ending state of the functional test.
 *
 * States should start at @c finished_successfully and be ordered from furthest
 * to least far through the compilation process.
 */
enum class FunctionalTestOptionsState {
  // States furthest through compilation

  finished_successfully,
  errors_after_passes,
  unrecoverable_parsing_failure,

  // States that finished earliest in the compilation process
};

struct FunctionalTestOptions {
  std::string source;
  FunctionalTestOptionsState expected_state{
      FunctionalTestOptionsState::finished_successfully};
  std::optional<std::function<void(const std::vector<lt::Token>&)>> on_tokens;
  std::optional<std::function<void(const TranslationUnit&)>> on_syntax_tree;
  std::string expected_syntax_tree_debug;
  std::optional<std::function<void(const lt::JITContext&)>> on_jit_context;
  std::string expected_message_report;
  std::string expected_llvm_module_print;
};

void runFunctionalTest(FunctionalTestOptions&& options);
}  // namespace forge
