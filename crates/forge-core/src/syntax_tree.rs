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

pub type BitWidth = u32;

#[derive(Debug, Clone, PartialEq)]
pub struct NodeBase {}

#[derive(Debug, Clone, PartialEq)]
pub struct TypeInt {
    pub base: NodeBase,
    pub signed: bool,
    pub bit_width: BitWidth,
}

#[derive(Debug, Clone, PartialEq)]
pub struct TypeFloat {
    pub base: NodeBase,
    pub bit_width: BitWidth,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Node {
    TypeBool(NodeBase),
    TypeInt(TypeInt),
    TypeFloat(TypeFloat),
}

// #[derive(Debug, Clone, PartialEq)]
// pub struct ValueBool {
//     pub value: bool,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct ValueI32 {
//     pub value: i32,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct ValueSymbol {
//     pub name: String,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub enum OperatorUnary {
//     LogNot,
//     BitNot,
//     Neg,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub enum OperatorBinary {
//     LogAnd,
//     LogOr,
//     BitAnd,
//     BitOr,
//     BitXor,
//     BitShL,
//     BitShR,
//     Add,
//     Sub,
//     Mul,
//     Div,
//     Mod,
//     LT,
//     LE,
//     GT,
//     GE,
//     NE,
//     EQ,
//     Assign,
//     BitAndAssign,
//     BitOrAssign,
//     BitXorAssign,
//     BitShLAssign,
//     BitShRAssign,
//     AddAssign,
//     SubAssign,
//     MulAssign,
//     DivAssign,
//     ModAssign,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct ValueUnary {
//     pub operator: OperatorUnary,
//     pub value: Box<Value>,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct ValueBinary {
//     pub operator: OperatorBinary,
//     pub left: Box<Value>,
//     pub right: Box<Value>,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub enum Value {
//     Bool(ValueBool),
//     I32(ValueI32),
//     Symbol(ValueSymbol),
//     Unary(ValueUnary),
//     Binary(ValueBinary),
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct StatementValue {
//     pub value: Value,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct StatementAssign {
//     pub name: String,
//     pub value: Value,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub struct StatementIf {
//     pub condition: Value,
//     pub then_branch: Box<Statement>,
//     pub else_branch: Option<Box<Statement>>,
// }

// #[derive(Debug, Clone, PartialEq)]
// pub enum Statement {
//     Value(StatementValue),
//     Assign(StatementAssign),
//     If(StatementIf),
// }
