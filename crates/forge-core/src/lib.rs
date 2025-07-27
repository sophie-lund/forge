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
#![feature(iter_chain)]

mod ast;
mod lexer;
mod message;
mod parser;
mod sourcing;
mod token;

pub use ast::*;
pub use lexer::*;
pub use message::*;
pub use parser::*;
pub use sourcing::*;
pub use token::*;
