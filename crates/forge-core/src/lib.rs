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

// use crate::{
//     interpreter::Interpreter,
//     syntax_tree::{
//         OperatorBinary, Statement, StatementAssign, Value, ValueBinary, ValueBool, ValueI32,
//         ValueSymbol,
//     },
// };

#![feature(let_chains)]

mod interpreter;
mod lexer;
mod message;
mod sourcing;
mod syntax_tree;
mod token;

pub use lexer::*;
pub use message::*;
pub use sourcing::*;
pub use token::*;

// fn main() {
// let mut interpreter = Interpreter::new();

// interpreter.interpret_statement(&Statement::Assign(StatementAssign {
//     name: "x".to_owned(),
//     value: Value::I32(ValueI32 { value: 5 }),
// }));

// interpreter.interpret_statement(&Statement::If(syntax_tree::StatementIf {
//     condition: Value::Bool(ValueBool { value: true }),
//     then_branch: Box::new(Statement::Assign(StatementAssign {
//         name: "x".to_owned(),
//         value: Value::I32(ValueI32 { value: 7 }),
//     })),
//     else_branch: Some(Box::new(Statement::Assign(StatementAssign {
//         name: "x".to_owned(),
//         value: Value::I32(ValueI32 { value: 5 }),
//     }))),
// }));

// let result = interpreter.interpret_value(&Value::Binary(ValueBinary {
//     operator: OperatorBinary::Add,
//     left: Box::new(Value::Symbol(ValueSymbol {
//         name: "x".to_owned(),
//     })),
//     right: Box::new(Value::I32(ValueI32 { value: 10 })),
// }));

// println!("{:?}", result);
// }
