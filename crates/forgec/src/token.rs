use crate::{SourceLocation, SourceRef};

pub enum TokenKind {
    KWBool,
    KWI8,
    KWI16,
    KWI32,
    KWI64,
    KWU8,
    KWU16,
    KWU32,
    KWU64,
    KWF32,
    KWF64,
}

pub struct Token<'ctx> {
    pub source: SourceRef<'ctx>,
    pub location: SourceLocation<'ctx>,
    pub length: usize,
    pub kind: TokenKind,
}
