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

#include <forgec/parsing/forge_lexer.hpp>
#include <forgec/testing/random_syntax_tree_generator.hpp>
#include <langtools/core/assert.hpp>

namespace forge {
RandomSyntaxTreeGenerator::RandomSyntaxTreeGenerator()
    : RandomSyntaxTreeGenerator(std::nullopt) {}

RandomSyntaxTreeGenerator::RandomSyntaxTreeGenerator(
    std::optional<uint32_t> seed) {
  // Initialize default options
  require_well_formed = true;
  max_type_depth = 3;

  // Initialize seed
  if (!seed.has_value()) {
    std::random_device rd;
    _seed = rd();
  } else {
    _seed = *seed;
  }

  // Initialize engine and distribution
  engine.seed(_seed);
  distribution = std::uniform_real_distribution<double>(0.0, 1.0);
}

uint32_t RandomSyntaxTreeGenerator::seed() const { return _seed; }

std::shared_ptr<BaseType> RandomSyntaxTreeGenerator::generate_type(
    std::optional<uint32_t> max_depth) {
  uint32_t resolved_max_depth = max_depth.value_or(max_type_depth);

  double random_real_is_nullptr = get_random_real();
  double random_real_kind = get_random_real();

  // If we do not need to generate only well-formed types...
  if (!require_well_formed) {
    // There is a 10% chance that we will return a nullptr
    if (random_real_is_nullptr < 1.0 / 10.0) {
      return nullptr;
    }
  }

  // If we can have child nodes...
  if (resolved_max_depth > 0) {
    if (random_real_kind < 1.0 / 4.0) {
      return generate_type_basic();
    } else if (random_real_kind < 2.0 / 4.0) {
      return generate_type_with_bit_width();
    } else if (random_real_kind < 3.0 / 4.0) {
      return generate_type_symbol();
    } else {
      return generate_type_unary(resolved_max_depth - 1);
    }
  }

  // If we must only generate shallow types
  else {
    if (random_real_kind < 1.0 / 3.0) {
      return generate_type_basic();
    } else if (random_real_kind < 2.0 / 3.0) {
      return generate_type_with_bit_width();
    } else {
      return generate_type_symbol();
    }
  }
}

std::shared_ptr<TypeBasic> RandomSyntaxTreeGenerator::generate_type_basic() {
  double random_real_kind = get_random_real();

  TypeBasicKind type_basic_kind;

  if (random_real_kind < 1.0 / 4.0) {
    type_basic_kind = TypeBasicKind::bool_;
  } else if (random_real_kind < 2.0 / 4.0) {
    type_basic_kind = TypeBasicKind::void_;
  } else if (random_real_kind < 3.0 / 4.0) {
    type_basic_kind = TypeBasicKind::isize;
  } else {
    type_basic_kind = TypeBasicKind::usize;
  }

  return std::make_shared<TypeBasic>(lt::SourceRange(), type_basic_kind);
}

std::shared_ptr<TypeWithBitWidth>
RandomSyntaxTreeGenerator::generate_type_with_bit_width() {
  double random_real_kind = get_random_real();
  double random_real_bit_width = get_random_real();

  TypeWithBitWidthKind type_with_bit_width_kind;

  if (random_real_kind < 1.0 / 3.0) {
    type_with_bit_width_kind = TypeWithBitWidthKind::signed_int;
  } else if (random_real_kind < 2.0 / 3.0) {
    type_with_bit_width_kind = TypeWithBitWidthKind::unsigned_int;
  } else {
    type_with_bit_width_kind = TypeWithBitWidthKind::float_;
  }

  uint32_t bit_width;

  if (require_well_formed) {
    if (type_with_bit_width_kind == TypeWithBitWidthKind::signed_int ||
        type_with_bit_width_kind == TypeWithBitWidthKind::unsigned_int) {
      if (random_real_bit_width < 1.0 / 4.0) {
        bit_width = 8;
      } else if (random_real_bit_width < 2.0 / 4.0) {
        bit_width = 16;
      } else if (random_real_bit_width < 3.0 / 4.0) {
        bit_width = 32;
      } else {
        bit_width = 64;
      }
    } else if (type_with_bit_width_kind == TypeWithBitWidthKind::float_) {
      if (random_real_bit_width < 1.0 / 2.0) {
        bit_width = 32;
      } else {
        bit_width = 64;
      }
    } else {
      LT_ABORT("unsupported type with bit width kind");
    }
  } else {
    bit_width = (uint32_t)(random_real_bit_width * 200.0);
  }

  return std::make_shared<TypeWithBitWidth>(
      lt::SourceRange(), type_with_bit_width_kind, bit_width);
}

std::shared_ptr<TypeSymbol> RandomSyntaxTreeGenerator::generate_type_symbol() {
  std::string name = get_random_symbol_name();

  return std::make_shared<TypeSymbol>(lt::SourceRange(), std::move(name));
}

std::shared_ptr<TypeUnary> RandomSyntaxTreeGenerator::generate_type_unary(
    std::optional<uint32_t> max_depth) {
  std::shared_ptr<BaseType> operand_type = generate_type(max_depth);

  return std::make_shared<TypeUnary>(lt::SourceRange(), TypeUnaryKind::pointer,
                                     std::move(operand_type));
}

// std::shared_ptr<TypeFunction>
// RandomSyntaxTreeGenerator::generate_type_function(
//     std::optional<uint32_t> max_depth) {
//   double random_real_argument_count = get_random_real();

//   size_t argument_count = (size_t)(random_real_argument_count * 10.0);

//   std::vector<std::shared_ptr<BaseType>> arg_types;

//   for (size_t i = 0; i < argument_count; i++) {
//     std::shared_ptr<BaseType> arg_type = generate_type(max_depth);
//     arg_types.push_back(std::move(arg_type));
//   }

//   std::shared_ptr<BaseType> return_type = generate_type(max_depth);

//   return std::make_shared<TypeFunction>(
//       lt::SourceRange(), std::move(return_type), std::move(arg_types));
// }

double RandomSyntaxTreeGenerator::get_random_real() {
  return distribution(engine);
}

std::string RandomSyntaxTreeGenerator::get_random_symbol_name() {
  static std::string alphabet_first =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

  static std::string alphabet =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

  while (true) {
    double random_real_length = get_random_real();
    double random_real_char_first = get_random_real();

    std::string name;

    size_t length = 1 + (size_t)(random_real_length * 20.0);

    name += alphabet_first[(size_t)(random_real_char_first *
                                    alphabet_first.size()) %
                           alphabet_first.size()];

    for (size_t i = 1; i < length; i++) {
      double random_real_char = get_random_real();

      name += alphabet[(size_t)(random_real_char * alphabet.size()) %
                       alphabet.size()];
    }

    if (try_get_keyword_token_kind(name).has_value()) {
      continue;
    }

    return name;
  }
}
}  // namespace forge
