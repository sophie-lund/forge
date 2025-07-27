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

use crate::{
    BinaryOperator, BitWidth, DeclFn, DeclVar, Expr, ExprBinary, ExprBool, ExprCall, ExprFloat,
    ExprInt, ExprSymbol, ExprUnary, SourceRange, Stmt, StmtBlock, StmtBreak, StmtContinue,
    StmtExpr, StmtIf, StmtReturn, StmtWhile, Type, TypeBool, TypeFloat, TypeInt, TypeMissing,
    TypePointer, UnaryOperator,
};

impl<'sctx> TypeMissing<'sctx> {
    pub fn new() -> Self {
        Self { source_range: None }
    }
}

impl<'sctx> TypeBool<'sctx> {
    pub fn new() -> Self {
        Self { source_range: None }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>) -> Self {
        Self {
            source_range: Some(source_range),
        }
    }
}

impl<'sctx> TypeInt<'sctx> {
    pub fn new(bit_width: BitWidth, signed: bool) -> Self {
        Self {
            source_range: None,
            bit_width,
            signed,
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        bit_width: BitWidth,
        signed: bool,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            bit_width,
            signed,
        }
    }
}

impl<'sctx> TypeFloat<'sctx> {
    pub fn new(bit_width: BitWidth) -> Self {
        Self {
            source_range: None,
            bit_width,
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>, bit_width: BitWidth) -> Self {
        Self {
            source_range: Some(source_range),
            bit_width,
        }
    }
}

impl<'sctx> TypePointer<'sctx> {
    pub fn new(deref_type: impl Into<Type<'sctx>>) -> Self {
        Self {
            source_range: None,
            deref_type: Box::new(deref_type.into()),
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        deref_type: impl Into<Type<'sctx>>,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            deref_type: Box::new(deref_type.into()),
        }
    }
}

impl<'sctx> ExprBool<'sctx> {
    pub fn new(value: bool) -> Self {
        Self {
            source_range: None,
            value,
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>, value: bool) -> Self {
        Self {
            source_range: Some(source_range),
            value,
        }
    }
}

impl<'sctx> ExprInt<'sctx> {
    pub fn new_i8(value: i8) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_i16(value: i16) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_i32(value: i32) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_i64(value: i64) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_u8(value: u8) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_u16(value: u16) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_u32(value: u32) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_u64(value: u64) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_i8_from_source(source_range: SourceRange<'sctx>, value: i8) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_i16_from_source(source_range: SourceRange<'sctx>, value: i16) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_i32_from_source(source_range: SourceRange<'sctx>, value: i32) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_i64_from_source(source_range: SourceRange<'sctx>, value: i64) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_u8_from_source(source_range: SourceRange<'sctx>, value: u8) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_u16_from_source(source_range: SourceRange<'sctx>, value: u16) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_u32_from_source(source_range: SourceRange<'sctx>, value: u32) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_u64_from_source(source_range: SourceRange<'sctx>, value: u64) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }
}

impl<'sctx> ExprFloat<'sctx> {
    pub fn new_f32(value: f32) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_f64(value: f64) -> Self {
        Self {
            source_range: None,
            value: value.into(),
        }
    }

    pub fn new_f32_from_source(source_range: SourceRange<'sctx>, value: f32) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }

    pub fn new_f64_from_source(source_range: SourceRange<'sctx>, value: f64) -> Self {
        Self {
            source_range: Some(source_range),
            value: value.into(),
        }
    }
}

impl<'sctx> ExprSymbol<'sctx> {
    pub fn new(name: String) -> Self {
        assert!(!name.is_empty(), "Symbol name cannot be empty");

        Self {
            source_range: None,
            name,
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>, name: String) -> Self {
        assert!(!name.is_empty(), "Symbol name cannot be empty");

        Self {
            source_range: Some(source_range),
            name,
        }
    }
}

impl<'sctx> ExprUnary<'sctx> {
    pub fn new(operator: UnaryOperator, operand: impl Into<Expr<'sctx>>) -> Self {
        Self {
            source_range: None,
            operator,
            operand: Box::new(operand.into()),
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        operator: UnaryOperator,
        operand: impl Into<Expr<'sctx>>,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            operator,
            operand: Box::new(operand.into()),
        }
    }
}

impl<'sctx> ExprBinary<'sctx> {
    pub fn new(
        left: impl Into<Expr<'sctx>>,
        operator: BinaryOperator,
        right: impl Into<Expr<'sctx>>,
    ) -> Self {
        Self {
            source_range: None,
            left: Box::new(left.into()),
            operator,
            right: Box::new(right.into()),
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        left: impl Into<Expr<'sctx>>,
        operator: BinaryOperator,
        right: impl Into<Expr<'sctx>>,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            left: Box::new(left.into()),
            operator,
            right: Box::new(right.into()),
        }
    }
}

impl<'sctx> ExprCall<'sctx> {
    pub fn new(callee: impl Into<Expr<'sctx>>) -> Self {
        Self {
            source_range: None,
            callee: Box::new(callee.into()),
            args: Vec::new(),
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        callee: impl Into<Expr<'sctx>>,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            callee: Box::new(callee.into()),
            args: Vec::new(),
        }
    }

    pub fn with_appended_arg(mut self, arg: impl Into<Expr<'sctx>>) -> Self {
        self.args.push(arg.into());
        self
    }

    pub fn with_appended_args_iter<TExpr, TIterator>(mut self, args: TIterator) -> Self
    where
        TExpr: Into<Expr<'sctx>>,
        TIterator: Iterator<Item = TExpr>,
    {
        for arg in args {
            self.args.push(arg.into());
        }

        self
    }

    pub fn with_replaced_args_vec(mut self, args: Vec<Expr<'sctx>>) -> Self {
        self.args = args;
        self
    }
}

impl<'sctx> StmtExpr<'sctx> {
    pub fn new(expr: impl Into<Expr<'sctx>>) -> Self {
        Self {
            source_range: None,
            expr: Box::new(expr.into()),
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>, expr: impl Into<Expr<'sctx>>) -> Self {
        Self {
            source_range: Some(source_range),
            expr: Box::new(expr.into()),
        }
    }
}

impl<'sctx> StmtIf<'sctx> {
    pub fn new(condition: impl Into<Expr<'sctx>>, then: impl Into<Stmt<'sctx>>) -> Self {
        Self {
            source_range: None,
            condition: Box::new(condition.into()),
            then: Box::new(then.into()),
            r#else: None,
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        condition: impl Into<Expr<'sctx>>,
        then: impl Into<Stmt<'sctx>>,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            condition: Box::new(condition.into()),
            then: Box::new(then.into()),
            r#else: None,
        }
    }

    pub fn with_else(mut self, r#else: impl Into<Stmt<'sctx>>) -> Self {
        self.r#else = Some(Box::new(r#else.into()));
        self
    }
}

impl<'sctx> StmtWhile<'sctx> {
    pub fn new(condition: impl Into<Expr<'sctx>>, body: impl Into<Stmt<'sctx>>) -> Self {
        Self {
            source_range: None,
            condition: Box::new(condition.into()),
            body: Box::new(body.into()),
            is_do_while: false,
        }
    }

    pub fn new_from_source(
        source_range: SourceRange<'sctx>,
        condition: impl Into<Expr<'sctx>>,
        body: impl Into<Stmt<'sctx>>,
    ) -> Self {
        Self {
            source_range: Some(source_range),
            condition: Box::new(condition.into()),
            body: Box::new(body.into()),
            is_do_while: false,
        }
    }

    pub fn with_do_while_enabled(mut self) -> Self {
        self.is_do_while = true;
        self
    }
}

impl<'sctx> StmtReturn<'sctx> {
    pub fn new() -> Self {
        Self {
            source_range: None,
            value: None,
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>) -> Self {
        Self {
            source_range: Some(source_range),
            value: None,
        }
    }

    pub fn with_value(mut self, value: impl Into<Expr<'sctx>>) -> Self {
        self.value = Some(value.into());
        self
    }
}

impl<'sctx> StmtContinue<'sctx> {
    pub fn new() -> Self {
        Self { source_range: None }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>) -> Self {
        Self {
            source_range: Some(source_range),
        }
    }
}

impl<'sctx> StmtBreak<'sctx> {
    pub fn new() -> Self {
        Self { source_range: None }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>) -> Self {
        Self {
            source_range: Some(source_range),
        }
    }
}

impl<'sctx> StmtBlock<'sctx> {
    pub fn new() -> Self {
        Self {
            source_range: None,
            stmts: Vec::new(),
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>) -> Self {
        Self {
            source_range: Some(source_range),
            stmts: Vec::new(),
        }
    }

    pub fn with_appended_stmt(mut self, stmt: impl Into<Stmt<'sctx>>) -> Self {
        self.stmts.push(stmt.into());
        self
    }

    pub fn with_appended_stmts_iter<TStmt, TIterator>(mut self, stmts: TIterator) -> Self
    where
        TStmt: Into<Stmt<'sctx>>,
        TIterator: Iterator<Item = TStmt>,
    {
        for stmt in stmts {
            self.stmts.push(stmt.into());
        }

        self
    }

    pub fn with_replaced_stmts_vec(mut self, stmts: Vec<Stmt<'sctx>>) -> Self {
        self.stmts = stmts;
        self
    }
}

impl<'sctx> DeclVar<'sctx> {
    pub fn new(name: String) -> Self {
        assert!(!name.is_empty(), "Symbol name cannot be empty");

        Self {
            source_range: None,
            name,
            r#type: None,
            initial_value: None,
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>, name: String) -> Self {
        assert!(!name.is_empty(), "Symbol name cannot be empty");

        Self {
            source_range: Some(source_range),
            name,
            r#type: None,
            initial_value: None,
        }
    }

    pub fn with_type(mut self, r#type: impl Into<Type<'sctx>>) -> Self {
        self.r#type = Some(r#type.into());
        self
    }

    pub fn with_initial_value(mut self, initial_value: impl Into<Expr<'sctx>>) -> Self {
        self.initial_value = Some(initial_value.into());
        self
    }
}

impl<'sctx> DeclFn<'sctx> {
    pub fn new(name: String) -> Self {
        assert!(!name.is_empty(), "Symbol name cannot be empty");

        Self {
            source_range: None,
            name,
            args: Vec::new(),
            return_type: None,
            body: None,
        }
    }

    pub fn new_from_source(source_range: SourceRange<'sctx>, name: String) -> Self {
        assert!(!name.is_empty(), "Symbol name cannot be empty");

        Self {
            source_range: Some(source_range),
            name,
            args: Vec::new(),
            return_type: None,
            body: None,
        }
    }

    pub fn with_appended_arg(mut self, arg: impl Into<DeclVar<'sctx>>) -> Self {
        self.args.push(arg.into());
        self
    }

    pub fn with_appended_args_iter<TDeclVar, TIterator>(mut self, args: TIterator) -> Self
    where
        TDeclVar: Into<DeclVar<'sctx>>,
        TIterator: Iterator<Item = TDeclVar>,
    {
        for arg in args {
            self.args.push(arg.into());
        }

        self
    }

    pub fn with_replaced_args_vec(mut self, args: Vec<DeclVar<'sctx>>) -> Self {
        self.args = args;
        self
    }

    pub fn with_return_type(mut self, return_type: impl Into<Type<'sctx>>) -> Self {
        self.return_type = Some(return_type.into());
        self
    }

    pub fn with_body(mut self, body: impl Into<StmtBlock<'sctx>>) -> Self {
        self.body = Some(body.into());
        self
    }
}
