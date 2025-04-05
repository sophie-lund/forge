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

#include <forge/syntax_tree/domain/node_kind.hpp>

namespace forge {
// clang-format off

const NodeKind NODE_DECLARATION_FUNCTION        = NodeKind("declaration_function");
const NodeKind NODE_DECLARATION_NAMESPACE       = NodeKind("declaration_namespace");
const NodeKind NODE_DECLARATION_STRUCTURED_TYPE = NodeKind("declaration_structured_type");
const NodeKind NODE_DECLARATION_TYPE_ALIAS      = NodeKind("declaration_type_alias");
const NodeKind NODE_DECLARATION_VARIABLE        = NodeKind("declaration_variable");
const NodeKind NODE_STATEMENT_BASIC             = NodeKind("statement_basic");
const NodeKind NODE_STATEMENT_BLOCK             = NodeKind("statement_block");
const NodeKind NODE_STATEMENT_IF                = NodeKind("statement_if");
const NodeKind NODE_STATEMENT_VALUE             = NodeKind("statement_value");
const NodeKind NODE_STATEMENT_WHILE             = NodeKind("statement_while");
const NodeKind NODE_TRANSLATION_UNIT            = NodeKind("translation_unit");
const NodeKind NODE_TYPE_BASIC                  = NodeKind("type_basic");
const NodeKind NODE_TYPE_FUNCTION               = NodeKind("type_function");
const NodeKind NODE_TYPE_STRUCTURED             = NodeKind("type_structured");
const NodeKind NODE_TYPE_SYMBOL                 = NodeKind("type_symbol");
const NodeKind NODE_TYPE_UNARY                  = NodeKind("type_unary");
const NodeKind NODE_TYPE_WITH_BIT_WIDTH         = NodeKind("type_with_bit_width");
const NodeKind NODE_VALUE_BINARY                = NodeKind("value_binary");
const NodeKind NODE_VALUE_CALL                  = NodeKind("value_call");
const NodeKind NODE_VALUE_CAST                  = NodeKind("value_cast");
const NodeKind NODE_VALUE_LITERAL_BOOL          = NodeKind("value_literal_bool");
const NodeKind NODE_VALUE_LITERAL_NUMBER        = NodeKind("value_literal_number");
const NodeKind NODE_VALUE_SYMBOL                = NodeKind("value_symbol");
const NodeKind NODE_VALUE_UNARY                 = NodeKind("value_unary");

// clang-format on
}  // namespace forge
