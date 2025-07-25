use thiserror::Error;

use crate::{GraphemeError, SourceRef, Token};

#[derive(Error, Debug)]
pub enum LexingError {
    #[error("grapheme error: {0}")]
    GraphemeError(#[from] GraphemeError),
}

pub fn lex(source: SourceRef<'_>) -> Vec<Token<'_>> {
    let mut current = source.start();

    // loop {
    //     let Ok((grapheme, next_location))
    // }

    Vec::new()
}
