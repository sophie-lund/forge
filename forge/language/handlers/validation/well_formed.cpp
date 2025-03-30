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

#include <forge/language/handlers/validation/well_formed.hpp>
#include <forge/language/syntax_tree/types/type_with_bit_width.hpp>

namespace forge {
IHandler::Output WellFormedValidationHandler::on_enter(Input&) {
  return Output();
}

IHandler::Output WellFormedValidationHandler::on_leave(Input& input) {
  // -----------------------------------------------------------------

  if (input.node()->kind == NODE_TYPE_BASIC) {
    return Output();
  }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_TYPE_WITH_BIT_WIDTH) {
  //   const TypeWithBitWidth& casted =
  //       static_cast<const TypeWithBitWidth&>(*input.node());

  //   if (casted.kind == TypeWithBitWidthKind::signed_int ||
  //       casted.kind == TypeWithBitWidthKind::unsigned_int) {
  //     if (casted.bit_width != 8 && casted.bit_width != 16 &&
  //         casted.bit_width != 32 && casted.bit_width != 64) {
  //       input.message_context().emit(
  //           static_cast<const ExampleTypeFunction&>(*input.node())
  //               .return_type->source_range,
  //           SEVERITY_ERROR, "invalid bit width for integer");
  //     }
  //   } else if (casted.kind == TypeWithBitWidthKind::float_) {
  //     if (casted.bit_width != 32 && casted.bit_width != 64) {
  //       input.message_context().emit(
  //           static_cast<const ExampleTypeFunction&>(*input.node())
  //               .return_type->source_range,
  //           SEVERITY_ERROR, "invalid bit width for float");
  //     }
  //   } else {
  //     abort();  // this should never happen
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_TYPE_SYMBOL) {
  //   if (!validate_string_not_empty(
  //           input.message_context(), *input.node(), "name",
  //           static_cast<const TypeSymbol&>(*input.node()).name)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_TYPE_UNARY) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "operand_type",
  //           static_cast<const TypeUnary&>(*input.node()).operand_type)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_TYPE_FUNCTION) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "return_type",
  //           static_cast<const ExampleTypeFunction&>(*input.node())
  //               .return_type)) {
  //     return Output();
  //   }

  //   if (!validate_child_vector_not_null(
  //           input.message_context(), *input.node(), "arg_types",
  //           static_cast<const
  //           ExampleTypeFunction&>(*input.node()).arg_types)) {
  //     return Output();
  //   }

  //   for (const auto& arg_type :
  //        static_cast<const ExampleTypeFunction&>(*input.node()).arg_types) {
  //     if (arg_type->kind == NODE_TYPE_FUNCTION) {
  //       input.message_context().emit(arg_type->source_range, SEVERITY_ERROR,
  //                                    "???", "functions cannot be arguments");
  //     }
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_VALUE_BOOL ||
  //          input.node()->kind == NODE_VALUE_INT) {
  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_VALUE_SYMBOL) {
  //   if (!validate_string_not_empty(
  //           input.message_context(), *input.node(), "name",
  //           static_cast<const ExampleValueSymbol&>(*input.node()).name)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_VALUE_ADD ||
  //          input.node()->kind == NODE_VALUE_LT ||
  //          input.node()->kind == NODE_VALUE_EQ) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "lhs",
  //           static_cast<const
  //           ExampleValueBinary<ExampleValue>&>(*input.node())
  //               .lhs)) {
  //     return Output();
  //   }

  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "rhs",
  //           static_cast<const
  //           ExampleValueBinary<ExampleValue>&>(*input.node())
  //               .rhs)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_VALUE_NEG) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "operand",
  //           static_cast<const
  //           ExampleValueUnary<ExampleValue>&>(*input.node())
  //               .operand)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_VALUE_CALL) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "callee",
  //           static_cast<const ExampleValueCall&>(*input.node()).callee)) {
  //     return Output();
  //   }

  //   if (!validate_child_vector_not_null(
  //           input.message_context(), *input.node(), "args",
  //           static_cast<const ExampleValueCall&>(*input.node()).args)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_STATEMENT_IF) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "condition",
  //           static_cast<const ExampleStatementIf&>(*input.node()).condition))
  //           {
  //     return Output();
  //   }

  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "then",
  //           static_cast<const ExampleStatementIf&>(*input.node()).then)) {
  //     return Output();
  //   }

  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "else_",
  //           static_cast<const ExampleStatementIf&>(*input.node()).else_)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_STATEMENT_WHILE) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "condition",
  //           static_cast<const ExampleStatementWhile&>(*input.node())
  //               .condition)) {
  //     return Output();
  //   }

  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "body",
  //           static_cast<const ExampleStatementWhile&>(*input.node()).body)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_STATEMENT_CONTINUE ||
  //          input.node()->kind == NODE_STATEMENT_BREAK) {
  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_STATEMENT_RETURN) {
  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "value",
  //           static_cast<const ExampleStatementReturn&>(*input.node()).value))
  //           {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_STATEMENT_BLOCK) {
  //   if (!validate_child_vector_not_null(
  //           input.message_context(), *input.node(), "statements",
  //           static_cast<const ExampleStatementBlock&>(*input.node())
  //               .statements)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_DECLARATION_VARIABLE) {
  //   if (!on_leave_declaration(
  //           input.message_context(), input.stack(),
  //           static_cast<const ExampleDeclarationVariable&>(*input.node()))) {
  //     return Output();
  //   }

  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "type",
  //           static_cast<const ExampleDeclarationVariable&>(*input.node())
  //               .type)) {
  //     return Output();
  //   }

  //   if (static_cast<const ExampleDeclarationVariable&>(*input.node())
  //           .type->kind == NODE_TYPE_FUNCTION) {
  //     input.message_context().emit(
  //         static_cast<const ExampleDeclarationVariable&>(*input.node())
  //             .type->source_range,
  //         SEVERITY_ERROR, "variables cannot have function types");
  //   }

  //   // If this is a function argument declaration...
  //   if (!input.stack().empty() &&
  //       input.stack().back().get().kind == NODE_DECLARATION_FUNCTION) {
  //     if (!validate_child_null(
  //             input.message_context(), *input.node(), "value",
  //             static_cast<const ExampleDeclarationVariable&>(*input.node())
  //                 .value)) {
  //       return Output();
  //     }
  //   } else {
  //     if (!validate_child_not_null(
  //             input.message_context(), *input.node(), "value",
  //             static_cast<const ExampleDeclarationVariable&>(*input.node())
  //                 .value)) {
  //       return Output();
  //     }
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_DECLARATION_FUNCTION) {
  //   if (!on_leave_declaration(
  //           input.message_context(), input.stack(),
  //           static_cast<const ExampleDeclarationFunction&>(*input.node()))) {
  //     return Output();
  //   }

  //   if (!validate_child_not_null(
  //           input.message_context(), *input.node(), "return_type",
  //           static_cast<const ExampleDeclarationFunction&>(*input.node())
  //               .return_type)) {
  //     return Output();
  //   }

  //   if (static_cast<const ExampleDeclarationFunction&>(*input.node())
  //           .return_type->kind == NODE_TYPE_FUNCTION) {
  //     input.message_context().emit(
  //         static_cast<const ExampleDeclarationFunction&>(*input.node())
  //             .return_type->source_range,
  //         SEVERITY_ERROR, "functions cannot return function types");
  //   }

  //   if (!validate_child_vector_not_null(
  //           input.message_context(), *input.node(), "args",
  //           static_cast<const ExampleDeclarationFunction&>(*input.node())
  //               .args)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  // else if (input.node()->kind == NODE_TRANSLATION_UNIT) {
  //   if (!validate_child_vector_not_null(
  //           input.message_context(), *input.node(), "declarations",
  //           static_cast<const ExampleTranslationUnit&>(*input.node())
  //               .declarations)) {
  //     return Output();
  //   }

  //   return Output();
  // }

  // // -----------------------------------------------------------------

  else {
    input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                 "???", "unknown node kind");
    return Output();
  }

  // -----------------------------------------------------------------
}

// bool WellFormedValidationHandler::on_leave_declaration(
//     MessageContext& message_context,
//     const std::vector<std::reference_wrapper<const BaseNode>>&,
//     const ExampleDeclaration& node) {
//   return validate_string_not_empty(
//       message_context, node, "name",
//       static_cast<const ExampleDeclarationVariable&>(node).name);
// }
}  // namespace forge
