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

//! This module contains trait implementations for all of the abstract syntax tree (AST) structs.
//!
//! The implementations for the [`Node`] trait are kept in `structs.rs` to make it harder to forget
//! to implement it for new AST structs.

use std::iter;

use serde::Serialize;

use crate::{
    Decl, DeclFn, DeclVar, Expr, ExprBinary, ExprBool, ExprCall, ExprFloat, ExprInt, ExprSymbol,
    ExprUnary, FloatValue, GetSourceRange, IntValue, IterChildren, NodeMut, NodeRef, SourceRange,
    Stmt, StmtBlock, StmtBreak, StmtContinue, StmtExpr, StmtIf, StmtReturn, StmtWhile, Type,
    TypeBool, TypeFloat, TypeInt, TypeMissing, TypePointer,
};

#[allow(unused_imports)] // this is needed for rustdoc
use crate::Node;

impl PartialEq for TypeMissing<'_> {
    fn eq(&self, _: &Self) -> bool {
        true
    }
}

impl<'sctx> GetSourceRange<'sctx> for TypeMissing<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for TypeMissing<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for TypeBool<'_> {
    fn eq(&self, _: &Self) -> bool {
        true
    }
}

impl<'sctx> GetSourceRange<'sctx> for TypeBool<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for TypeBool<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for TypeInt<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.bit_width == other.bit_width && self.signed == other.signed
    }
}

impl<'sctx> GetSourceRange<'sctx> for TypeInt<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for TypeInt<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for TypeFloat<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.bit_width == other.bit_width
    }
}

impl<'sctx> GetSourceRange<'sctx> for TypeFloat<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for TypeFloat<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for TypePointer<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.deref_type == other.deref_type
    }
}

impl<'sctx> GetSourceRange<'sctx> for TypePointer<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for TypePointer<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::once(self.deref_type.as_ref().into()))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::once(self.deref_type.as_mut().into()))
    }
}

impl<'sctx> GetSourceRange<'sctx> for Type<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        match self {
            Type::Missing(t) => t.get_source_range(),
            Type::Bool(t) => t.get_source_range(),
            Type::Int(t) => t.get_source_range(),
            Type::Float(t) => t.get_source_range(),
            Type::Pointer(t) => t.get_source_range(),
        }
    }
}

impl<'sctx> IterChildren<'sctx> for Type<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match self {
            Type::Missing(t) => t.iter_children(),
            Type::Bool(t) => t.iter_children(),
            Type::Int(t) => t.iter_children(),
            Type::Float(t) => t.iter_children(),
            Type::Pointer(t) => t.iter_children(),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match self {
            Type::Missing(t) => t.iter_children_mut(),
            Type::Bool(t) => t.iter_children_mut(),
            Type::Int(t) => t.iter_children_mut(),
            Type::Float(t) => t.iter_children_mut(),
            Type::Pointer(t) => t.iter_children_mut(),
        }
    }
}

impl PartialEq for ExprBool<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprBool<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprBool<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl Serialize for IntValue {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        match self {
            IntValue::I8(value) => serializer.serialize_i8(*value),
            IntValue::I16(value) => serializer.serialize_i16(*value),
            IntValue::I32(value) => serializer.serialize_i32(*value),
            IntValue::I64(value) => serializer.serialize_i64(*value),
            IntValue::U8(value) => serializer.serialize_u8(*value),
            IntValue::U16(value) => serializer.serialize_u16(*value),
            IntValue::U32(value) => serializer.serialize_u32(*value),
            IntValue::U64(value) => serializer.serialize_u64(*value),
        }
    }
}

impl PartialEq for ExprInt<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprInt<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprInt<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl Serialize for FloatValue {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        match self {
            FloatValue::F32(value) => serializer.serialize_f32(*value),
            FloatValue::F64(value) => serializer.serialize_f64(*value),
        }
    }
}

impl PartialEq for ExprFloat<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprFloat<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprFloat<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for ExprSymbol<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprSymbol<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprSymbol<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for ExprUnary<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.operator == other.operator && self.operand == other.operand
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprUnary<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprUnary<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::once(self.operand.as_ref().into()))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::once(self.operand.as_mut().into()))
    }
}

impl PartialEq for ExprBinary<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.operator == other.operator && self.left == other.left && self.right == other.right
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprBinary<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprBinary<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::chain(
            iter::once(self.left.as_ref().into()),
            iter::once(self.right.as_ref().into()),
        ))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::chain(
            iter::once(self.left.as_mut().into()),
            iter::once(self.right.as_mut().into()),
        ))
    }
}

impl PartialEq for ExprCall<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.callee == other.callee && self.args == other.args
    }
}

impl<'sctx> GetSourceRange<'sctx> for ExprCall<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for ExprCall<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::chain(
            iter::once(self.callee.as_ref().into()),
            self.args.iter().map(|arg| arg.into()),
        ))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::chain(
            iter::once(self.callee.as_mut().into()),
            self.args.iter_mut().map(|arg| arg.into()),
        ))
    }
}

impl<'sctx> GetSourceRange<'sctx> for Expr<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        match self {
            Expr::Bool(e) => e.get_source_range(),
            Expr::Int(e) => e.get_source_range(),
            Expr::Float(e) => e.get_source_range(),
            Expr::Symbol(e) => e.get_source_range(),
            Expr::Unary(e) => e.get_source_range(),
            Expr::Binary(e) => e.get_source_range(),
            Expr::Call(e) => e.get_source_range(),
        }
    }
}

impl<'sctx> IterChildren<'sctx> for Expr<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match self {
            Expr::Bool(e) => e.iter_children(),
            Expr::Int(e) => e.iter_children(),
            Expr::Float(e) => e.iter_children(),
            Expr::Symbol(e) => e.iter_children(),
            Expr::Unary(e) => e.iter_children(),
            Expr::Binary(e) => e.iter_children(),
            Expr::Call(e) => e.iter_children(),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match self {
            Expr::Bool(e) => e.iter_children_mut(),
            Expr::Int(e) => e.iter_children_mut(),
            Expr::Float(e) => e.iter_children_mut(),
            Expr::Symbol(e) => e.iter_children_mut(),
            Expr::Unary(e) => e.iter_children_mut(),
            Expr::Binary(e) => e.iter_children_mut(),
            Expr::Call(e) => e.iter_children_mut(),
        }
    }
}

impl PartialEq for StmtExpr<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.expr == other.expr
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtExpr<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for StmtExpr<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::once(self.expr.as_ref().into()))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::once(self.expr.as_mut().into()))
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtIf<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl PartialEq for StmtIf<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.condition == other.condition && self.then == other.then && self.r#else == other.r#else
    }
}

impl<'sctx> IterChildren<'sctx> for StmtIf<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match &self.r#else {
            Some(r#else) => Box::new(iter::chain(
                iter::once(self.condition.as_ref().into()),
                Box::new(iter::chain(
                    iter::once(self.then.as_ref().into()),
                    iter::once(r#else.as_ref().into()),
                )),
            )),
            None => Box::new(iter::chain(
                iter::once(self.condition.as_ref().into()),
                iter::once(self.then.as_ref().into()),
            )),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match &mut self.r#else {
            Some(r#else) => Box::new(iter::chain(
                iter::once(self.condition.as_mut().into()),
                Box::new(iter::chain(
                    iter::once(self.then.as_mut().into()),
                    iter::once(r#else.as_mut().into()),
                )),
            )),
            None => Box::new(iter::chain(
                iter::once(self.condition.as_mut().into()),
                iter::once(self.then.as_mut().into()),
            )),
        }
    }
}

impl PartialEq for StmtWhile<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.condition == other.condition
            && self.body == other.body
            && self.is_do_while == other.is_do_while
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtWhile<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for StmtWhile<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::chain(
            iter::once(self.condition.as_ref().into()),
            iter::once(self.body.as_ref().into()),
        ))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::chain(
            iter::once(self.condition.as_mut().into()),
            iter::once(self.body.as_mut().into()),
        ))
    }
}

impl PartialEq for StmtReturn<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtReturn<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for StmtReturn<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match &self.value {
            Some(value) => Box::new(iter::once(value.into())),
            None => Box::new(iter::empty()),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match &mut self.value {
            Some(value) => Box::new(iter::once(value.into())),
            None => Box::new(iter::empty()),
        }
    }
}

impl PartialEq for StmtContinue<'_> {
    fn eq(&self, _: &Self) -> bool {
        true
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtContinue<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for StmtContinue<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for StmtBreak<'_> {
    fn eq(&self, _: &Self) -> bool {
        true
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtBreak<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for StmtBreak<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(iter::empty())
    }
}

impl PartialEq for StmtBlock<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.stmts == other.stmts
    }
}

impl<'sctx> GetSourceRange<'sctx> for StmtBlock<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for StmtBlock<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        Box::new(self.stmts.iter().map(|arg| arg.into()))
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        Box::new(self.stmts.iter_mut().map(|arg| arg.into()))
    }
}

impl<'sctx> GetSourceRange<'sctx> for Stmt<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        match self {
            Stmt::Expr(s) => s.get_source_range(),
            Stmt::If(s) => s.get_source_range(),
            Stmt::While(s) => s.get_source_range(),
            Stmt::Return(s) => s.get_source_range(),
            Stmt::Continue(s) => s.get_source_range(),
            Stmt::Break(s) => s.get_source_range(),
            Stmt::Block(s) => s.get_source_range(),
        }
    }
}

impl<'sctx> IterChildren<'sctx> for Stmt<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match self {
            Stmt::Expr(s) => s.iter_children(),
            Stmt::If(s) => s.iter_children(),
            Stmt::While(s) => s.iter_children(),
            Stmt::Return(s) => s.iter_children(),
            Stmt::Continue(s) => s.iter_children(),
            Stmt::Break(s) => s.iter_children(),
            Stmt::Block(s) => s.iter_children(),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match self {
            Stmt::Expr(s) => s.iter_children_mut(),
            Stmt::If(s) => s.iter_children_mut(),
            Stmt::While(s) => s.iter_children_mut(),
            Stmt::Return(s) => s.iter_children_mut(),
            Stmt::Continue(s) => s.iter_children_mut(),
            Stmt::Break(s) => s.iter_children_mut(),
            Stmt::Block(s) => s.iter_children_mut(),
        }
    }
}

impl PartialEq for DeclVar<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
            && self.r#type == other.r#type
            && self.initial_value == other.initial_value
    }
}

impl<'sctx> GetSourceRange<'sctx> for DeclVar<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for DeclVar<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match (self.r#type.as_ref(), self.initial_value.as_ref()) {
            (Some(r#type), Some(initial_value)) => Box::new(iter::chain(
                iter::once(r#type.into()),
                iter::once(initial_value.into()),
            )),
            (Some(r#type), None) => Box::new(iter::once(r#type.into())),
            (None, Some(initial_value)) => Box::new(iter::once(initial_value.into())),
            (None, None) => Box::new(iter::empty()),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match (self.r#type.as_mut(), self.initial_value.as_mut()) {
            (Some(r#type), Some(initial_value)) => Box::new(iter::chain(
                iter::once(r#type.into()),
                iter::once(initial_value.into()),
            )),
            (Some(r#type), None) => Box::new(iter::once(r#type.into())),
            (None, Some(initial_value)) => Box::new(iter::once(initial_value.into())),
            (None, None) => Box::new(iter::empty()),
        }
    }
}

impl PartialEq for DeclFn<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
            && self.args == other.args
            && self.return_type == other.return_type
            && self.body == other.body
    }
}

impl<'sctx> GetSourceRange<'sctx> for DeclFn<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        self.source_range.as_ref()
    }
}

impl<'sctx> IterChildren<'sctx> for DeclFn<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match (self.return_type.as_ref(), self.body.as_ref()) {
            (Some(return_type), Some(body)) => Box::new(iter::chain(
                self.args.iter().map(|arg| arg.into()),
                iter::chain(iter::once(return_type.into()), iter::once(body.into())),
            )),
            (Some(return_type), None) => Box::new(iter::chain(
                self.args.iter().map(|arg| arg.into()),
                iter::once(return_type.into()),
            )),
            (None, Some(body)) => Box::new(iter::chain(
                self.args.iter().map(|arg| arg.into()),
                iter::once(body.into()),
            )),
            (None, None) => Box::new(self.args.iter().map(|arg| arg.into())),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match (self.return_type.as_mut(), self.body.as_mut()) {
            (Some(return_type), Some(body)) => Box::new(iter::chain(
                self.args.iter_mut().map(|arg| arg.into()),
                iter::chain(iter::once(return_type.into()), iter::once(body.into())),
            )),
            (Some(return_type), None) => Box::new(iter::chain(
                self.args.iter_mut().map(|arg| arg.into()),
                iter::once(return_type.into()),
            )),
            (None, Some(body)) => Box::new(iter::chain(
                self.args.iter_mut().map(|arg| arg.into()),
                iter::once(body.into()),
            )),
            (None, None) => Box::new(self.args.iter_mut().map(|arg| arg.into())),
        }
    }
}

impl<'sctx> GetSourceRange<'sctx> for Decl<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        match self {
            Decl::Var(s) => s.get_source_range(),
            Decl::Fn(s) => s.get_source_range(),
        }
    }
}

impl<'sctx> IterChildren<'sctx> for Decl<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match self {
            Decl::Var(s) => s.iter_children(),
            Decl::Fn(s) => s.iter_children(),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match self {
            Decl::Var(s) => s.iter_children_mut(),
            Decl::Fn(s) => s.iter_children_mut(),
        }
    }
}

impl<'sctx> Decl<'sctx> {
    pub fn name(&self) -> &str {
        match self {
            Decl::Var(var) => &var.name,
            Decl::Fn(func) => &func.name,
        }
    }
}

impl<'sctx> GetSourceRange<'sctx> for Node<'sctx> {
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>> {
        match self {
            Node::Type(n) => n.get_source_range(),
            Node::Expr(n) => n.get_source_range(),
            Node::Stmt(n) => n.get_source_range(),
            Node::Decl(n) => n.get_source_range(),
        }
    }
}

impl<'sctx> IterChildren<'sctx> for Node<'sctx> {
    fn iter_children<'node>(
        &'node self,
    ) -> Box<dyn Iterator<Item = super::NodeRef<'sctx, 'node>> + 'node> {
        match self {
            Node::Type(n) => n.iter_children(),
            Node::Expr(n) => n.iter_children(),
            Node::Stmt(n) => n.iter_children(),
            Node::Decl(n) => n.iter_children(),
        }
    }

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = super::NodeMut<'sctx, 'node>> + 'node> {
        match self {
            Node::Type(n) => n.iter_children_mut(),
            Node::Expr(n) => n.iter_children_mut(),
            Node::Stmt(n) => n.iter_children_mut(),
            Node::Decl(n) => n.iter_children_mut(),
        }
    }
}

impl<'sctx, 'node> From<&'node Type<'sctx>> for NodeRef<'sctx, 'node> {
    fn from(value: &'node Type<'sctx>) -> Self {
        Self::Type(value)
    }
}

impl<'sctx, 'node> From<&'node Expr<'sctx>> for NodeRef<'sctx, 'node> {
    fn from(value: &'node Expr<'sctx>) -> Self {
        Self::Expr(value)
    }
}

impl<'sctx, 'node> From<&'node StmtBlock<'sctx>> for NodeRef<'sctx, 'node> {
    fn from(value: &'node StmtBlock<'sctx>) -> Self {
        Self::StmtBlock(value)
    }
}

impl<'sctx, 'node> From<&'node Stmt<'sctx>> for NodeRef<'sctx, 'node> {
    fn from(value: &'node Stmt<'sctx>) -> Self {
        Self::Stmt(value)
    }
}

impl<'sctx, 'node> From<&'node DeclVar<'sctx>> for NodeRef<'sctx, 'node> {
    fn from(value: &'node DeclVar<'sctx>) -> Self {
        Self::DeclVar(value)
    }
}

impl<'sctx, 'node> From<&'node Decl<'sctx>> for NodeRef<'sctx, 'node> {
    fn from(value: &'node Decl<'sctx>) -> Self {
        Self::Decl(value)
    }
}

impl<'sctx, 'node> From<&'node mut Type<'sctx>> for NodeMut<'sctx, 'node> {
    fn from(value: &'node mut Type<'sctx>) -> Self {
        Self::Type(value)
    }
}

impl<'sctx, 'node> From<&'node mut Expr<'sctx>> for NodeMut<'sctx, 'node> {
    fn from(value: &'node mut Expr<'sctx>) -> Self {
        Self::Expr(value)
    }
}

impl<'sctx, 'node> From<&'node mut StmtBlock<'sctx>> for NodeMut<'sctx, 'node> {
    fn from(value: &'node mut StmtBlock<'sctx>) -> Self {
        Self::StmtBlock(value)
    }
}

impl<'sctx, 'node> From<&'node mut Stmt<'sctx>> for NodeMut<'sctx, 'node> {
    fn from(value: &'node mut Stmt<'sctx>) -> Self {
        Self::Stmt(value)
    }
}

impl<'sctx, 'node> From<&'node mut DeclVar<'sctx>> for NodeMut<'sctx, 'node> {
    fn from(value: &'node mut DeclVar<'sctx>) -> Self {
        Self::DeclVar(value)
    }
}

impl<'sctx, 'node> From<&'node mut Decl<'sctx>> for NodeMut<'sctx, 'node> {
    fn from(value: &'node mut Decl<'sctx>) -> Self {
        Self::Decl(value)
    }
}
