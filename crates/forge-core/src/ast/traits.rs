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

//! These are traits for shared functionality across the abstract syntax tree (AST) structs.
//!
//! These are implemented in `impls.rs` except [`Node`] which is implemented in `structs.rs` to
//! make it harder to forget to implement it for new AST structs.

use serde::Serialize;
use std::fmt::Debug;

use crate::{NodeMut, NodeRef, SourceRange};

/// A trait for node types that have a source range they originate from.
pub trait GetSourceRange<'sctx> {
    /// Returns the source range of the node.
    fn get_source_range(&self) -> Option<&SourceRange<'sctx>>;
}

pub trait IterChildren<'sctx> {
    fn iter_children<'node>(&'node self)
    -> Box<dyn Iterator<Item = NodeRef<'sctx, 'node>> + 'node>;

    fn iter_children_mut<'node>(
        &'node mut self,
    ) -> Box<dyn Iterator<Item = NodeMut<'sctx, 'node>> + 'node>;
}

/// A trait for node types to make sure they implement the necessary traits.
///
/// It's implemented for all abstract syntax tree (AST) structs to ensure they have the
/// necessary shared functionality in `structs.rs`. This is to make it harder to forget to implement
/// it for new AST structs.
pub trait IsNode<'sctx>:
    Debug + Clone + PartialEq + Serialize + GetSourceRange<'sctx> + IterChildren<'sctx>
{
}
