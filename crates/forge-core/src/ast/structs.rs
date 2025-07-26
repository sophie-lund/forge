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

//! This module is where the structs for the abstract syntax tree (AST) are defined.
//!
//! They also implement various traits to provide shared functionality, but that's all done in
//! `impls.rs`. Only the [`Node`] trait is implement here. It's a marker trait that ensures all AST
//! nodes implement the necessary shared traits. This is just to make sure that no AST node's trait
//! implementations are missed.

use serde::Serialize;

use crate::{IsNode, SourceRange};

/// The width of a type in bits.
pub type BitWidth = u8;

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct TypeBool<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for TypeBool<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct TypeInt<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    #[serde(rename = "bitWidth")]
    pub bit_width: BitWidth,

    pub signed: bool,
}

impl<'ctx> IsNode<'ctx> for TypeInt<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct TypeFloat<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    #[serde(rename = "bitWidth")]
    pub bit_width: BitWidth,
}

impl<'ctx> IsNode<'ctx> for TypeFloat<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct TypePointer<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    #[serde(rename = "bitWidth")]
    pub deref_type: Box<Type<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for TypePointer<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
#[serde(tag = "type")]
pub enum Type<'sctx> {
    #[serde(rename = "typeBool")]
    Bool(TypeBool<'sctx>),

    #[serde(rename = "typeInt")]
    Int(TypeInt<'sctx>),

    #[serde(rename = "typeFloat")]
    Float(TypeFloat<'sctx>),

    #[serde(rename = "typePointer")]
    Pointer(TypePointer<'sctx>),
}

impl<'ctx> IsNode<'ctx> for Type<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprBool<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub value: bool,
}

impl<'ctx> IsNode<'ctx> for ExprBool<'ctx> {}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum IntValue {
    I8(i8),
    I16(i16),
    I32(i32),
    I64(i64),
    U8(u8),
    U16(u16),
    U32(u32),
    U64(u64),
}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprInt<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub value: IntValue,
}

impl<'ctx> IsNode<'ctx> for ExprInt<'ctx> {}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum FloatValue {
    F32(f32),
    F64(f64),
}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprFloat<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub value: FloatValue,
}

impl<'ctx> IsNode<'ctx> for ExprFloat<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprSymbol<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub name: String,
}

impl<'ctx> IsNode<'ctx> for ExprSymbol<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub enum UnaryOperator {
    #[serde(rename = "logNot")]
    LogNot,

    #[serde(rename = "bitNot")]
    BitNot,

    #[serde(rename = "neg")]
    Neg,
}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprUnary<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub operator: UnaryOperator,

    pub operand: Box<Expr<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for ExprUnary<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub enum BinaryOperator {
    #[serde(rename = "logAnd")]
    LogAnd,

    #[serde(rename = "logOr")]
    LogOr,

    #[serde(rename = "bitAnd")]
    BitAnd,

    #[serde(rename = "bitOr")]
    BitOr,

    #[serde(rename = "bitXor")]
    BitXor,

    #[serde(rename = "bitShL")]
    BitShL,

    #[serde(rename = "bitShR")]
    BitShR,

    #[serde(rename = "add")]
    Add,

    #[serde(rename = "sub")]
    Sub,

    #[serde(rename = "mul")]
    Mul,

    #[serde(rename = "div")]
    Div,

    #[serde(rename = "mod")]
    Mod,

    #[serde(rename = "lt")]
    LT,

    #[serde(rename = "le")]
    LE,

    #[serde(rename = "gt")]
    GT,

    #[serde(rename = "ge")]
    GE,

    #[serde(rename = "ne")]
    NE,

    #[serde(rename = "eq")]
    EQ,

    #[serde(rename = "assign")]
    Assign,

    #[serde(rename = "bitAndAssign")]
    BitAndAssign,

    #[serde(rename = "bitOrAssign")]
    BitOrAssign,

    #[serde(rename = "bitXorAssign")]
    BitXorAssign,

    #[serde(rename = "bitShLAssign")]
    BitShLAssign,

    #[serde(rename = "bitShRAssign")]
    BitShRAssign,

    #[serde(rename = "addAssign")]
    AddAssign,

    #[serde(rename = "subAssign")]
    SubAssign,

    #[serde(rename = "mulAssign")]
    MulAssign,

    #[serde(rename = "divAssign")]
    DivAssign,

    #[serde(rename = "modAssign")]
    ModAssign,
}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprBinary<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub operator: BinaryOperator,

    pub left: Box<Expr<'sctx>>,

    pub right: Box<Expr<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for ExprBinary<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct ExprCall<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub callee: Box<Expr<'sctx>>,

    pub args: Vec<Expr<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for ExprCall<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
#[serde(tag = "type")]
pub enum Expr<'sctx> {
    #[serde(rename = "exprBool")]
    Bool(ExprBool<'sctx>),

    #[serde(rename = "exprInt")]
    Int(ExprInt<'sctx>),

    #[serde(rename = "exprFloat")]
    Float(ExprFloat<'sctx>),

    #[serde(rename = "exprSymbol")]
    Symbol(ExprSymbol<'sctx>),

    #[serde(rename = "exprUnary")]
    Unary(ExprUnary<'sctx>),

    #[serde(rename = "exprBinary")]
    Binary(ExprBinary<'sctx>),

    #[serde(rename = "exprCall")]
    Call(ExprCall<'sctx>),
}

impl<'ctx> IsNode<'ctx> for Expr<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtExpr<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub expr: Box<Expr<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for StmtExpr<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtIf<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub condition: Box<Expr<'sctx>>,

    pub then: Box<Stmt<'sctx>>,

    #[serde(rename = "else")]
    pub r#else: Box<Stmt<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for StmtIf<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtWhile<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub condition: Box<Expr<'sctx>>,

    pub body: Box<Stmt<'sctx>>,

    #[serde(rename = "isDoWhile")]
    pub is_do_while: bool,
}

impl<'ctx> IsNode<'ctx> for StmtWhile<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtReturn<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub value: Box<Stmt<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for StmtReturn<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtContinue<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for StmtContinue<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtBreak<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for StmtBreak<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct StmtBlock<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub stmts: Vec<Stmt<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for StmtBlock<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
#[serde(tag = "type")]
pub enum Stmt<'sctx> {
    #[serde(rename = "stmtExpr")]
    Expr(StmtExpr<'sctx>),

    #[serde(rename = "stmtIf")]
    If(StmtIf<'sctx>),

    #[serde(rename = "stmtWhile")]
    While(StmtWhile<'sctx>),

    #[serde(rename = "stmtReturn")]
    Return(StmtReturn<'sctx>),

    #[serde(rename = "stmtContinue")]
    Continue(StmtContinue<'sctx>),

    #[serde(rename = "stmtBreak")]
    Break(StmtBreak<'sctx>),

    #[serde(rename = "stmtBlock")]
    Block(StmtBlock<'sctx>),
}

impl<'ctx> IsNode<'ctx> for Stmt<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct DeclVar<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub name: String,

    #[serde(rename = "type")]
    pub r#type: Option<Type<'sctx>>,

    #[serde(rename = "initialValue")]
    pub initial_value: Option<Expr<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for DeclVar<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct DeclFn<'sctx> {
    #[serde(rename = "sourceRange")]
    pub source_range: Option<SourceRange<'sctx>>,

    pub name: String,

    pub args: Vec<DeclVar<'sctx>>,

    #[serde(rename = "returnType")]
    pub return_type: Option<Type<'sctx>>,

    pub body: Option<StmtBlock<'sctx>>,
}

impl<'ctx> IsNode<'ctx> for DeclFn<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
#[serde(tag = "type")]
pub enum Decl<'sctx> {
    #[serde(rename = "declVar")]
    Var(DeclVar<'sctx>),

    #[serde(rename = "declFn")]
    Fn(DeclFn<'sctx>),
}

impl<'ctx> IsNode<'ctx> for Decl<'ctx> {}

#[derive(Debug, Clone, PartialEq, Serialize)]
#[serde(untagged)]
pub enum Node<'sctx> {
    Type(Type<'sctx>),
    Expr(Expr<'sctx>),
    Stmt(Stmt<'sctx>),
    Decl(Decl<'sctx>),
}

impl<'ctx> IsNode<'ctx> for Node<'ctx> {}

#[derive(Debug, PartialEq, Serialize)]
#[serde(untagged)]
pub enum NodeRef<'sctx, 'node> {
    Type(&'node Type<'sctx>),
    Expr(&'node Expr<'sctx>),
    StmtBlock(&'node StmtBlock<'sctx>),
    Stmt(&'node Stmt<'sctx>),
    DeclVar(&'node DeclVar<'sctx>),
    Decl(&'node Decl<'sctx>),
}

#[derive(Debug, PartialEq, Serialize)]
#[serde(untagged)]
pub enum NodeMut<'sctx, 'node> {
    Type(&'node mut Type<'sctx>),
    Expr(&'node mut Expr<'sctx>),
    StmtBlock(&'node mut StmtBlock<'sctx>),
    Stmt(&'node mut Stmt<'sctx>),
    DeclVar(&'node mut DeclVar<'sctx>),
    Decl(&'node mut Decl<'sctx>),
}
