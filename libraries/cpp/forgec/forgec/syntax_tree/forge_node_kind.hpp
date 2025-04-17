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

#include <langtools/syntax_tree/domain/node_kind.hpp>

namespace forge {
// clang-format off

const lt::NodeKind NODE_DECLARATION_FUNCTION        = lt::NodeKind("declaration_function");
const lt::NodeKind NODE_DECLARATION_NAMESPACE       = lt::NodeKind("declaration_namespace");
const lt::NodeKind NODE_DECLARATION_STRUCTURED_TYPE = lt::NodeKind("declaration_structured_type");
const lt::NodeKind NODE_DECLARATION_TYPE_ALIAS      = lt::NodeKind("declaration_type_alias");
const lt::NodeKind NODE_DECLARATION_VARIABLE        = lt::NodeKind("declaration_variable");
const lt::NodeKind NODE_STATEMENT_BASIC             = lt::NodeKind("statement_basic");
const lt::NodeKind NODE_STATEMENT_BLOCK             = lt::NodeKind("statement_block");
const lt::NodeKind NODE_STATEMENT_IF                = lt::NodeKind("statement_if");
const lt::NodeKind NODE_STATEMENT_VALUE             = lt::NodeKind("statement_value");
const lt::NodeKind NODE_STATEMENT_WHILE             = lt::NodeKind("statement_while");
const lt::NodeKind NODE_TRANSLATION_UNIT            = lt::NodeKind("translation_unit");
const lt::NodeKind NODE_TYPE_BASIC                  = lt::NodeKind("type_basic");
const lt::NodeKind NODE_TYPE_FUNCTION               = lt::NodeKind("type_function");
const lt::NodeKind NODE_TYPE_STRUCTURED             = lt::NodeKind("type_structured");
const lt::NodeKind NODE_TYPE_SYMBOL                 = lt::NodeKind("type_symbol");
const lt::NodeKind NODE_TYPE_UNARY                  = lt::NodeKind("type_unary");
const lt::NodeKind NODE_TYPE_WITH_BIT_WIDTH         = lt::NodeKind("type_with_bit_width");
const lt::NodeKind NODE_VALUE_BINARY                = lt::NodeKind("value_binary");
const lt::NodeKind NODE_VALUE_CALL                  = lt::NodeKind("value_call");
const lt::NodeKind NODE_VALUE_CAST                  = lt::NodeKind("value_cast");
const lt::NodeKind NODE_VALUE_LITERAL_BOOL          = lt::NodeKind("value_literal_bool");
const lt::NodeKind NODE_VALUE_LITERAL_NUMBER        = lt::NodeKind("value_literal_number");
const lt::NodeKind NODE_VALUE_SYMBOL                = lt::NodeKind("value_symbol");
const lt::NodeKind NODE_VALUE_UNARY                 = lt::NodeKind("value_unary");

// clang-format on
}  // namespace forge
