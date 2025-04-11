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

#include <forge/language/syntax_tree/declarations/declaration_function.hpp>
#include <forge/language/syntax_tree/declarations/declaration_namespace.hpp>
#include <forge/language/syntax_tree/declarations/declaration_structured_type.hpp>
#include <forge/language/syntax_tree/declarations/declaration_type_alias.hpp>
#include <forge/language/syntax_tree/declarations/declaration_variable.hpp>
#include <forge/language/syntax_tree/statements/statement_basic.hpp>
#include <forge/language/syntax_tree/statements/statement_block.hpp>
#include <forge/language/syntax_tree/statements/statement_if.hpp>
#include <forge/language/syntax_tree/statements/statement_value.hpp>
#include <forge/language/syntax_tree/statements/statement_while.hpp>
#include <forge/language/syntax_tree/translation_unit.hpp>
#include <forge/language/syntax_tree/types/type_basic.hpp>
#include <forge/language/syntax_tree/types/type_function.hpp>
#include <forge/language/syntax_tree/types/type_structured.hpp>
#include <forge/language/syntax_tree/types/type_symbol.hpp>
#include <forge/language/syntax_tree/types/type_unary.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>
#include <forge/language/syntax_tree/values/value_binary.hpp>
#include <forge/language/syntax_tree/values/value_call.hpp>
#include <forge/language/syntax_tree/values/value_cast.hpp>
#include <forge/language/syntax_tree/values/value_literal_bool.hpp>
#include <forge/language/syntax_tree/values/value_literal_number.hpp>
#include <forge/language/syntax_tree/values/value_symbol.hpp>
#include <forge/language/syntax_tree/values/value_unary.hpp>
#include <ostream>

namespace forge {
struct FormattingOptions {
  FormattingOptions(std::ostream& stream);

  std::reference_wrapper<std::ostream> stream;
  uint32_t indent_level;
  uint32_t indent_tab_width;
};

void format_type_basic(FormattingOptions options,
                       const std::shared_ptr<TypeBasic>& node);

void format_type_with_bit_width(FormattingOptions options,
                                const std::shared_ptr<TypeWithBitWidth>& node);

void format_type_symbol(FormattingOptions options,
                        const std::shared_ptr<TypeSymbol>& node);

void format_type_unary(FormattingOptions options,
                       const std::shared_ptr<TypeUnary>& node);

void format_type_function(FormattingOptions options,
                          const std::shared_ptr<TypeFunction>& node);

void format_type_structured(FormattingOptions options,
                            const std::shared_ptr<TypeStructured>& node);

void format_type(FormattingOptions options,
                 const std::shared_ptr<BaseType>& node);
}  // namespace forge
