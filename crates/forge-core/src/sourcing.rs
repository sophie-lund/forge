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

use serde::Serialize;
use std::{
    fmt::{self, Debug, Display, Formatter},
    io,
    ops::Deref,
    time::{SystemTime, UNIX_EPOCH},
};
use thiserror::Error;
use unicode_segmentation::UnicodeSegmentation;

/// An error returned when reading graphemes from source code.
#[derive(Error, Debug)]
pub enum SourceError {
    /// Wrapper for [`io::Error`] to handle file reading errors.
    #[error("IO error: {0}")]
    IOError(#[from] io::Error),

    /// An error when reading graphemes at a location that is past the end of the source code.
    #[error("offset out of bounds - underlying source code may have changed")]
    OffsetOutOfBounds,

    /// An error when reading graphemes at a location that is not at a grapheme boundary, but in the
    /// middle of a grapheme.
    #[error("offset not at grapheme boundary - underlying source code may have changed")]
    OffsetNotAtGraphemeBoundary,

    /// An error when there are no more graphemes to read at the current offset.
    #[error("no more graphemes to read at offset - this should be handled by the caller")]
    NoMoreGraphemes,
}

/// A timestamp measured in the number of milliseconds since the UNIX epoch (January 1, 1970).
pub type TimestampMS = u128;

/// A loaded instance of source code.
pub struct Source {
    /// The timestamp when the source was loaded, in milliseconds since the UNIX epoch.
    pub load_timestamp_ms: TimestampMS,

    /// The path to the source file from which the source code was read.
    ///
    /// For string sources, this is often a placeholder like `"--"``.
    pub path: String,

    /// The content of the source code as a string.
    pub content: String,
}

impl Serialize for Source {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        serializer.serialize_str(&self.path)
    }
}

impl Source {
    /// Creates a new [`Source`] instance from a string.
    ///
    /// The path can be any nonempty string such as a placeholder like `"--"`.
    pub fn new_from_string(path: String, content: String) -> Result<Self, SourceError> {
        assert!(!path.is_empty(), "path cannot be empty");

        Ok(Self {
            load_timestamp_ms: get_load_timestamp_ms(),
            path,
            content,
        })
    }

    /// Loads a source from a file at the given path.
    pub fn load_from_file(path: String) -> Result<Self, SourceError> {
        assert!(!path.is_empty(), "path cannot be empty");

        let content = std::fs::read_to_string(&path)?;

        Ok(Self {
            load_timestamp_ms: get_load_timestamp_ms(),
            path,
            content,
        })
    }
}

/// Get the current timestamp in milliseconds since the UNIX epoch.
fn get_load_timestamp_ms() -> TimestampMS {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .expect("the current timestamp shouldn't be before the UNIX epoch")
        .as_millis()
}

/// A struct to hold ownership of multiple [`Source`] instances in order to simplify lifetimes.
///
/// # Returns
///
/// Adding a new source file/string will return a [`SourceRef`] that can be used to access the
/// source later.
///
/// # Examples
///
/// ```
/// # use forge_core::{SourceContext, SourceRef};
/// #
/// // Create a source context
/// let mut sctx = SourceContext::default();
///
/// // Add a string source
/// let test_ref = sctx.add_from_string(
///     "test.txt".to_owned(),
///     "hello, world\n".to_owned()
/// ).unwrap();
///
/// // You can use the reference to access the source
/// assert_eq!(test_ref.path, "test.txt");
/// ```
pub struct SourceContext {
    sources: Vec<Source>,
}

impl Default for SourceContext {
    fn default() -> Self {
        Self {
            sources: Vec::new(),
        }
    }
}

impl SourceContext {
    /// Add a new [`Source`] instance from a string and return a [`SourceRef`] to it.
    ///
    /// See [`Source::new_from_string`] for more details.
    pub fn add_from_string<'sctx>(
        &'sctx mut self,
        path: String,
        content: String,
    ) -> Result<SourceRef<'sctx>, SourceError> {
        // Take note of the current index
        let index = self.sources.len();

        // Create and push the new source instance
        self.sources.push(Source::new_from_string(path, content)?);

        // Return a reference to the new source
        Ok(SourceRef { ctx: self, index })
    }

    /// Add a new [`Source`] instance that is loaded from a file and return a [`SourceRef`] to it.
    ///
    /// See [`Source::load_from_file`] for more details.
    pub fn load_from_file<'sctx>(
        &'sctx mut self,
        path: String,
    ) -> Result<SourceRef<'sctx>, SourceError> {
        // Take note of the current index
        let index = self.sources.len();

        // Load and push the new source instance
        self.sources.push(Source::load_from_file(path)?);

        // Return a reference to the new source
        Ok(SourceRef { ctx: self, index })
    }
}

/// A reference to a single source file/string in a [`SourceContext`].
///
/// # Examples
///
/// ```
/// # use forge_core::{SourceContext, SourceRef};
/// #
/// // Create a source context
/// let mut sctx = SourceContext::default();
///
/// // Add a string source
/// let test_ref = sctx.add_from_string(
///     "test.txt".to_owned(),
///     "hello, world\n".to_owned()
/// ).unwrap();
///
/// // You can use the reference to access the source
/// assert_eq!(test_ref.path, "test.txt");
/// ```
///
/// # Comparison and ordering
///
/// Two [`SourceRef`] instances are considered equal if they have the same id in the source
/// context. Ids are assigned when sources are added to the context.
///
/// Their ids are used for ordering as well, so sources added first will always be earlier. This is
/// used for message ordering in compiler output.
#[derive(Clone, Copy)]
pub struct SourceRef<'sctx> {
    ctx: &'sctx SourceContext,
    index: usize,
}

impl PartialEq for SourceRef<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.index == other.index
    }
}

impl PartialOrd for SourceRef<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.index.partial_cmp(&other.index)
    }
}

impl Deref for SourceRef<'_> {
    type Target = Source;

    fn deref(&self) -> &Self::Target {
        &self.ctx.sources[self.index]
    }
}

impl Display for SourceRef<'_> {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        assert!(!self.path.is_empty(), "path cannot be empty");

        write!(f, "{}", self.path)
    }
}

impl Debug for SourceRef<'_> {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "<{}>", self.path)
    }
}

impl Serialize for SourceRef<'_> {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        self.deref().serialize(serializer)
    }
}

impl<'sctx> SourceRef<'sctx> {
    /// Return a new [`SourceLocation`] that refers to the first grapheme in the current referenced
    /// [`Source`].
    pub fn start(self) -> SourceLocation<'sctx> {
        SourceLocation {
            source: self,
            offset: 0,
            line: 1,
            column: 1,
        }
    }
}

/// A line number in source code, starting from 1.
pub type LineNumber = u32;

/// A column number in source code, starting from 1.
pub type ColumnNumber = u32;

/// The location of a grapheme in the source code, represented by a [`SourceRef`], an offset, and
/// line/column numbers.
///
/// # Ordering
///
/// [`SourceLocation`] instances are ordered by source reference id first (see [`SourceRef`]) and
/// byte offset within the source code second. This is used for message ordering in compiler output.
#[derive(Clone, Debug, PartialEq, Serialize)]
pub struct SourceLocation<'sctx> {
    /// A reference to the source code in which the grapheme is located.
    pub source: SourceRef<'sctx>,

    /// The offset in bytes from the start of the source code where the grapheme is located.
    pub offset: usize,

    /// The line number in the source code where the grapheme is located, starting from 1.
    pub line: LineNumber,

    /// The column number in the source code where the grapheme is located, starting from 1.
    pub column: ColumnNumber,
}

impl Display for SourceLocation<'_> {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "{}:{}:{}+{}",
            self.source, self.line, self.column, self.offset
        )
    }
}

impl PartialOrd for SourceLocation<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if let Some(ordering) = self.source.partial_cmp(&other.source)
            && ordering != std::cmp::Ordering::Equal
        {
            return Some(ordering);
        }

        self.offset.partial_cmp(&other.offset)
    }
}

impl<'sctx> SourceLocation<'sctx> {
    /// Peeks the next extended grapheme cluster from the source code starting from the given
    /// location.
    ///
    /// # Returns
    ///
    /// The string value of the next grapheme.
    ///
    /// # Errors
    ///
    /// Returns a [`SourceError`] if the offset is out of bounds or if there are no more graphemes
    /// to read.
    ///
    /// # Examples
    ///
    /// ```
    /// # use forge_core::{SourceContext, SourceRef, SourceLocation};
    /// #
    /// # let mut sctx = SourceContext::default();
    /// #
    /// # let test_ref = sctx.add_from_string(
    /// #     "test.txt".to_owned(),
    /// #     "hello, world\n".to_owned()
    /// # ).unwrap();
    /// #
    /// # let location = SourceLocation {
    /// #     source: test_ref,
    /// #     offset: 0,
    /// #     line: 1,
    /// #     column: 1,
    /// # };
    /// #
    /// // Where 'location' is the first character of the source code "hello, world"
    /// let grapheme = location.peek_next_grapheme().unwrap();
    ///
    /// assert_eq!(grapheme, "h");
    /// ```
    pub fn peek_next_grapheme(&self) -> Result<String, SourceError> {
        // Check bounds
        if self.offset > self.source.content.len() {
            return Err(SourceError::OffsetOutOfBounds);
        } else if self.offset == self.source.content.len() {
            return Err(SourceError::NoMoreGraphemes);
        }

        // Get the slice of the source code starting from the location offset
        let Some(slice) = self.source.content.get(self.offset..) else {
            return Err(SourceError::OffsetNotAtGraphemeBoundary);
        };

        // Read the next extended grapheme cluster
        let Some(grapheme) = slice.graphemes(true).next() else {
            return Err(SourceError::NoMoreGraphemes);
        };

        // Return results
        Ok(grapheme.to_owned())
    }

    /// Get the source location of the next grapheme in the source code.
    ///
    /// See [`SourceLocation::peek_next_grapheme`] for details.
    ///
    /// # Examples
    ///
    /// ```
    /// # use forge_core::{SourceContext, SourceRef, SourceLocation};
    /// #
    /// # let mut sctx = SourceContext::default();
    /// #
    /// # let test_ref = sctx.add_from_string(
    /// #     "test.txt".to_owned(),
    /// #     "hello, world\n".to_owned()
    /// # ).unwrap();
    /// #
    /// # let location = SourceLocation {
    /// #     source: test_ref,
    /// #     offset: 0,
    /// #     line: 1,
    /// #     column: 1,
    /// # };
    /// #
    /// // Where 'location' is the first character of the source code "hello, world"
    /// let next_location = location.get_next_location().unwrap();
    ///
    /// assert_eq!(next_location.offset, 1);
    /// assert_eq!(next_location.line, 1);
    /// assert_eq!(next_location.column, 2);
    /// ```
    pub fn get_next_location(&self) -> Result<SourceLocation<'sctx>, SourceError> {
        let grapheme = self.peek_next_grapheme()?;

        Ok(SourceLocation {
            source: self.source,
            offset: self.offset + grapheme.len(),
            line: self.line + if grapheme == "\n" { 1 } else { 0 },
            column: if grapheme == "\n" { 1 } else { self.column + 1 },
        })
    }

    /// Reads the next extended grapheme cluster from the source code and updates the current
    /// location.
    ///
    /// Internally, it uses [`SourceLocation::peek_next_grapheme`] and
    /// [`SourceLocation::get_next_location`] to update the current location.
    ///
    /// # Examples
    ///
    /// ```
    /// # use forge_core::{SourceContext, SourceRef, SourceLocation};
    /// #
    /// # let mut sctx = SourceContext::default();
    /// #
    /// # let test_ref = sctx.add_from_string(
    /// #     "test.txt".to_owned(),
    /// #     "hello, world\n".to_owned()
    /// # ).unwrap();
    /// #
    /// # let mut location = SourceLocation {
    /// #     source: test_ref,
    /// #     offset: 0,
    /// #     line: 1,
    /// #     column: 1,
    /// # };
    /// #
    /// // Where 'location' is the first character of the source code "hello, world"
    /// let grapheme = location.read_next_grapheme().unwrap();
    ///
    /// assert_eq!(grapheme, "h");
    ///
    /// assert_eq!(location.offset, 1);
    /// assert_eq!(location.line, 1);
    /// assert_eq!(location.column, 2);
    /// ```
    pub fn read_next_grapheme(&mut self) -> Result<String, SourceError> {
        let grapheme = self.peek_next_grapheme()?;

        *self = self.get_next_location()?;

        Ok(grapheme)
    }
}

/// A range of source code defined by a start location and a byte length.
///
/// # Ordering
///
/// They are ordered first by their start location, and then by their byte length. This is used for
/// message ordering in compiler output.
#[derive(Clone, Debug, PartialEq, Serialize)]
pub struct SourceRange<'sctx> {
    /// The location of the first grapheme of the range in the source code.
    #[serde(flatten)]
    pub first_location: SourceLocation<'sctx>,

    /// The number of bytes that this range occupies in the source code.
    #[serde(rename = "byteLength")]
    pub byte_length: usize,
}

impl Display for SourceRange<'_> {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "{}-{}", self.first_location, self.byte_length)
    }
}

impl PartialOrd for SourceRange<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if let Some(ordering) = self.first_location.partial_cmp(&other.first_location)
            && ordering != std::cmp::Ordering::Equal
        {
            return Some(ordering);
        }

        self.byte_length.partial_cmp(&other.byte_length)
    }
}

impl<'sctx> SourceRange<'sctx> {
    /// Creates a new source range from its components.
    pub fn new(first_location: SourceLocation<'sctx>, byte_length: usize) -> Self {
        Self {
            first_location,
            byte_length,
        }
    }

    /// Creates a new token from two source locations.
    pub fn new_from_locations(
        first_location: &SourceLocation<'sctx>,
        exclusive_end_location: &SourceLocation<'sctx>,
    ) -> Self {
        Self {
            first_location: first_location.clone(),
            byte_length: exclusive_end_location.offset - first_location.offset,
        }
    }

    /// Gets the source code content of the source range as a string.
    ///
    /// Returns an error if the range's location or byte length are invalid.
    pub fn content(&'sctx self) -> Result<&'sctx str, SourceError> {
        if self.first_location.offset + self.byte_length > self.first_location.source.content.len()
        {
            return Err(SourceError::OffsetOutOfBounds);
        }

        Ok(self
            .first_location
            .source
            .content
            .get(self.first_location.offset..self.first_location.offset + self.byte_length)
            .ok_or(SourceError::OffsetNotAtGraphemeBoundary)?)
    }

    /// Finds the location of the exclusive end grapheme in the source range using the first
    /// location and the byte length.
    ///
    /// *Warning:* This operation is `O(n)`.
    pub fn find_exclusive_end_location(&self) -> Result<SourceLocation<'sctx>, SourceError> {
        let mut exclusive_end_location = self.first_location.clone();

        for grapheme in self.content()?.graphemes(true) {
            exclusive_end_location.offset += grapheme.len();
            if grapheme == "\n" {
                exclusive_end_location.line += 1;
                exclusive_end_location.column = 1;
            } else {
                exclusive_end_location.column += 1;
            }
        }

        Ok(exclusive_end_location)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn source_location_display() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "hello, world\n".to_owned())
            .unwrap();

        assert_eq!(
            SourceLocation {
                source,
                offset: 10,
                line: 2,
                column: 5,
            }
            .to_string(),
            "test.frg:2:5+10".to_string(),
        );
    }

    #[test]
    fn peek_next_grapheme_empty() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "".to_owned())
            .unwrap();

        let location = source.start();

        assert!(matches!(
            location.peek_next_grapheme(),
            Err(SourceError::NoMoreGraphemes)
        ));
    }

    #[test]
    fn peek_next_grapheme_ascii() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "a".to_owned())
            .unwrap();

        let location = source.start();

        assert_eq!(location.peek_next_grapheme().unwrap(), "a");
    }

    #[test]
    fn peek_next_grapheme_unicode() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "﷽".to_owned())
            .unwrap();

        let location = source.start();

        assert_eq!(location.peek_next_grapheme().unwrap(), "﷽");
    }

    #[test]
    fn peek_next_grapheme_out_of_bounds() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "a".to_owned())
            .unwrap();

        let mut location = source.start();
        location.offset = 5;

        assert!(matches!(
            location.peek_next_grapheme(),
            Err(SourceError::OffsetOutOfBounds)
        ));
    }

    #[test]
    fn peek_next_grapheme_not_at_grapheme_boundary() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "﷽".to_owned())
            .unwrap();

        let mut location = source.start();
        location.offset = 1;

        assert!(matches!(
            location.peek_next_grapheme(),
            Err(SourceError::OffsetNotAtGraphemeBoundary)
        ));
    }

    #[test]
    fn peek_next_grapheme_between_grapheme_boundaries() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "﷽a".to_owned())
            .unwrap();

        let mut location = source.start();
        location.offset = 3;

        assert_eq!(location.peek_next_grapheme().unwrap(), "a");
    }

    #[test]
    fn get_next_location_empty() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "".to_owned())
            .unwrap();

        let location = source.start();

        assert!(matches!(
            location.get_next_location(),
            Err(SourceError::NoMoreGraphemes)
        ));
    }

    #[test]
    fn get_next_location_ascii() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "a".to_owned())
            .unwrap();

        let location = source.start();

        assert_eq!(location.get_next_location().unwrap(), SourceLocation {
            source,
            offset: 1,
            line: 1,
            column: 2,
        });
    }

    #[test]
    fn get_next_location_unicode() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "﷽".to_owned())
            .unwrap();

        let location = source.start();

        assert_eq!(location.get_next_location().unwrap(), SourceLocation {
            source,
            offset: 3,
            line: 1,
            column: 2,
        });
    }

    #[test]
    fn get_next_location_out_of_bounds() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "a".to_owned())
            .unwrap();

        let mut location = source.start();
        location.offset = 5;

        assert!(matches!(
            location.get_next_location(),
            Err(SourceError::OffsetOutOfBounds)
        ));
    }

    #[test]
    fn get_next_location_not_at_grapheme_boundary() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "﷽".to_owned())
            .unwrap();

        let mut location = source.start();
        location.offset = 1;

        assert!(matches!(
            location.get_next_location(),
            Err(SourceError::OffsetNotAtGraphemeBoundary)
        ));
    }

    #[test]
    fn get_next_location_between_grapheme_boundaries() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "﷽a".to_owned())
            .unwrap();

        let mut location = source.start();
        location.offset = 3;
        location.column = 2;

        assert_eq!(location.get_next_location().unwrap(), SourceLocation {
            source,
            offset: 4,
            line: 1,
            column: 3,
        });
    }

    #[test]
    fn source_range_content() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "hello, world\n".to_owned())
            .unwrap();

        // "hello"
        let range = SourceRange::new(source.start(), 5);

        assert_eq!(range.content().unwrap(), "hello");
    }

    #[test]
    fn source_range_first_and_last() {
        let mut sctx = SourceContext::default();

        let source = sctx
            .add_from_string("test.frg".to_owned(), "hello, world\n".to_owned())
            .unwrap();

        // ""
        let range = SourceRange::new_from_locations(&source.start(), &source.start());

        assert_eq!(range.byte_length, 0);
        assert_eq!(
            range.find_exclusive_end_location().unwrap(),
            SourceLocation {
                source,
                offset: 0,
                line: 1,
                column: 1,
            }
        );

        // "h"
        let range = SourceRange::new_from_locations(&source.start(), &SourceLocation {
            source,
            offset: 1,
            line: 1,
            column: 2,
        });

        assert_eq!(range.byte_length, 1);
        assert_eq!(
            range.find_exclusive_end_location().unwrap(),
            SourceLocation {
                source,
                offset: 1,
                line: 1,
                column: 2,
            }
        );
    }
}
