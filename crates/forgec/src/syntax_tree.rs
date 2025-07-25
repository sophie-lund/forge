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
