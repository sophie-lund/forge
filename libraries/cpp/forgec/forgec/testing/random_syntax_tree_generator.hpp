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

#include <forgec/syntax_tree/declarations/declaration_function.hpp>
#include <forgec/syntax_tree/declarations/declaration_namespace.hpp>
#include <forgec/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forgec/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forgec/syntax_tree/declarations/declaration_variable.hpp>
#include <forgec/syntax_tree/statements/statement_basic.hpp>
#include <forgec/syntax_tree/statements/statement_block.hpp>
#include <forgec/syntax_tree/statements/statement_if.hpp>
#include <forgec/syntax_tree/statements/statement_value.hpp>
#include <forgec/syntax_tree/statements/statement_while.hpp>
#include <forgec/syntax_tree/translation_unit.hpp>
#include <forgec/syntax_tree/types/type_basic.hpp>
#include <forgec/syntax_tree/types/type_function.hpp>
#include <forgec/syntax_tree/types/type_structured.hpp>
#include <forgec/syntax_tree/types/type_symbol.hpp>
#include <forgec/syntax_tree/types/type_unary.hpp>
#include <forgec/syntax_tree/types/type_with_bit_width.hpp>
#include <forgec/syntax_tree/values/value_binary.hpp>
#include <forgec/syntax_tree/values/value_call.hpp>
#include <forgec/syntax_tree/values/value_cast.hpp>
#include <forgec/syntax_tree/values/value_literal_bool.hpp>
#include <forgec/syntax_tree/values/value_literal_number.hpp>
#include <forgec/syntax_tree/values/value_symbol.hpp>
#include <forgec/syntax_tree/values/value_unary.hpp>
#include <optional>
#include <random>

namespace forge {
class RandomSyntaxTreeGenerator {
 public:
  /**
   * @brief Constructor that uses a random seed.
   */
  RandomSyntaxTreeGenerator();

  /**
   * @brief Constructor that uses a fixed seed.
   */
  RandomSyntaxTreeGenerator(std::optional<uint32_t> seed);

  uint32_t seed() const;

  std::shared_ptr<BaseType> generate_type(
      std::optional<uint32_t> max_depth = std::nullopt);

  std::shared_ptr<TypeBasic> generate_type_basic();

  std::shared_ptr<TypeWithBitWidth> generate_type_with_bit_width();

  std::shared_ptr<TypeSymbol> generate_type_symbol();

  std::shared_ptr<TypeUnary> generate_type_unary(
      std::optional<uint32_t> max_depth = std::nullopt);

  //   std::shared_ptr<TypeFunction> generate_type_function(
  //       std::optional<uint32_t> max_depth = std::nullopt);

  bool require_well_formed;
  uint32_t max_type_depth;

 private:
  uint32_t _seed;
  std::mt19937 engine;
  std::uniform_real_distribution<double> distribution;

  double get_random_real();
  std::string get_random_symbol_name();
};
}  // namespace forge
