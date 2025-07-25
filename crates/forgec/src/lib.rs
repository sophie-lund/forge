// use crate::{
//     interpreter::Interpreter,
//     syntax_tree::{
//         OperatorBinary, Statement, StatementAssign, Value, ValueBinary, ValueBool, ValueI32,
//         ValueSymbol,
//     },
// };

mod interpreter;
mod lexer;
mod sourcing;
mod syntax_tree;
mod token;

pub use lexer::*;
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
