// Copyright 2025 Sophie Lund
//
// This file is part of Forge.
//
// Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with Forge. If not, see
// <https://www.gnu.org/licenses/>.

// use std::collections::HashMap;

// use crate::syntax_tree::{
//     OperatorBinary, OperatorUnary, Statement, StatementAssign, StatementIf, Value, ValueBinary,
//     ValueBool, ValueI32, ValueSymbol, ValueUnary,
// };

// pub struct Interpreter {
//     symbol_values: HashMap<String, Value>,
// }

// impl Interpreter {
//     pub fn new() -> Self {
//         Interpreter {
//             symbol_values: HashMap::new(),
//         }
//     }

//     pub fn interpret_value(&mut self, value: &Value) -> Value {
//         match value {
//             Value::Bool(_) => value.clone(),
//             Value::I32(_) => value.clone(),
//             Value::Symbol(ValueSymbol { name }) => self
//                 .symbol_values
//                 .get(name)
//                 .cloned()
//                 .unwrap_or_else(|| panic!("Symbol '{:?}' not found", name)),
//             Value::Unary(ValueUnary { operator, value }) => {
//                 let value_interpreted = self.interpret_value(value);

//                 match (operator, &value_interpreted) {
//                     (OperatorUnary::LogNot, Value::Bool(ValueBool { value: value_bool })) => {
//                         Value::Bool(ValueBool {
//                             value: !*value_bool,
//                         })
//                     }
//                     (OperatorUnary::BitNot, Value::I32(ValueI32 { value: value_i32 })) => {
//                         Value::I32(ValueI32 { value: !*value_i32 })
//                     }
//                     (OperatorUnary::Neg, Value::I32(ValueI32 { value: value_i32 })) => {
//                         Value::I32(ValueI32 { value: -*value_i32 })
//                     }
//                     _ => panic!(
//                         "Operator {:?} cannot be applied to value {:?}",
//                         operator, value_interpreted
//                     ),
//                 }
//             }
//             Value::Binary(ValueBinary {
//                 operator,
//                 left,
//                 right,
//             }) => {
//                 let left_interpreted = self.interpret_value(left);
//                 let right_interpreted = self.interpret_value(right);

//                 match (operator, &left_interpreted, &right_interpreted) {
//                     (
//                         OperatorBinary::LogAnd,
//                         Value::Bool(ValueBool { value: left_bool }),
//                         Value::Bool(ValueBool { value: right_bool }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_bool && *right_bool,
//                     }),
//                     (
//                         OperatorBinary::LogOr,
//                         Value::Bool(ValueBool { value: left_bool }),
//                         Value::Bool(ValueBool { value: right_bool }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_bool || *right_bool,
//                     }),
//                     (
//                         OperatorBinary::BitAnd,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 & *right_i32,
//                     }),
//                     (
//                         OperatorBinary::BitOr,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 | *right_i32,
//                     }),
//                     (
//                         OperatorBinary::BitXor,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 ^ *right_i32,
//                     }),
//                     (
//                         OperatorBinary::BitShL,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 << *right_i32,
//                     }),
//                     (
//                         OperatorBinary::BitShR,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 >> *right_i32,
//                     }),
//                     (
//                         OperatorBinary::Add,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 + *right_i32,
//                     }),
//                     (
//                         OperatorBinary::Sub,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 - *right_i32,
//                     }),
//                     (
//                         OperatorBinary::Mul,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 * *right_i32,
//                     }),
//                     (
//                         OperatorBinary::Div,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 / *right_i32,
//                     }),
//                     (
//                         OperatorBinary::Mod,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::I32(ValueI32 {
//                         value: *left_i32 % *right_i32,
//                     }),
//                     (
//                         OperatorBinary::LT,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_i32 < *right_i32,
//                     }),
//                     (
//                         OperatorBinary::LE,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_i32 <= *right_i32,
//                     }),
//                     (
//                         OperatorBinary::GT,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_i32 > *right_i32,
//                     }),
//                     (
//                         OperatorBinary::GE,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_i32 >= *right_i32,
//                     }),
//                     (
//                         OperatorBinary::NE,
//                         Value::Bool(ValueBool { value: left_bool }),
//                         Value::Bool(ValueBool { value: right_bool }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_bool != *right_bool,
//                     }),
//                     (
//                         OperatorBinary::NE,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_i32 != *right_i32,
//                     }),
//                     (
//                         OperatorBinary::EQ,
//                         Value::Bool(ValueBool { value: left_bool }),
//                         Value::Bool(ValueBool { value: right_bool }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_bool == *right_bool,
//                     }),
//                     (
//                         OperatorBinary::EQ,
//                         Value::I32(ValueI32 { value: left_i32 }),
//                         Value::I32(ValueI32 { value: right_i32 }),
//                     ) => Value::Bool(ValueBool {
//                         value: *left_i32 == *right_i32,
//                     }),
//                     _ => panic!(
//                         "Operator {:?} cannot be applied to values {:?} and {:?}",
//                         operator, left_interpreted, right_interpreted
//                     ),
//                 }
//             }
//         }
//     }

//     pub fn interpret_statement(&mut self, statement: &Statement) -> () {
//         match statement {
//             Statement::Value(_) => {}
//             Statement::Assign(StatementAssign { name, value }) => {
//                 let interpreted_value = self.interpret_value(value);

//                 self.symbol_values.insert(name.clone(), interpreted_value);
//             }
//             Statement::If(StatementIf {
//                 condition,
//                 then_branch,
//                 else_branch,
//             }) => {
//                 let interpreted_condition = self.interpret_value(condition);

//                 match interpreted_condition {
//                     Value::Bool(ValueBool { value: true }) => {
//                         self.interpret_statement(then_branch);
//                     }
//                     Value::Bool(ValueBool { value: false }) => {
//                         if let Some(else_branch) = else_branch {
//                             self.interpret_statement(else_branch);
//                         }
//                     }
//                     _ => panic!(
//                         "StatementIf.condition must be a ValueBool, not {:?}",
//                         interpreted_condition
//                     ),
//                 }
//             }
//         }
//     }
// }
