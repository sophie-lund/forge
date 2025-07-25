use std::{
    fmt::{self, Display, Formatter},
    io,
    ops::Deref,
    time::{SystemTime, UNIX_EPOCH},
};
use thiserror::Error;
use unicode_segmentation::UnicodeSegmentation;

pub type TimestampMS = u128;

/// Source code is ephemeral. It may be edited by a developer at any time. The only part of the
/// language API that is guaranteed to have a stable version of the source code is the parser.
///
/// A [`Source`] instance represents one loaded instance of the source code.
pub struct Source {
    pub load_timestamp_ms: TimestampMS,
    pub path: String,
    pub content: String,
}

impl Source {
    pub fn new_from_string(path: String, content: String) -> Self {
        Self {
            load_timestamp_ms: get_load_timestamp_ms(),
            path,
            content,
        }
    }

    pub fn load_from_file(path: String) -> io::Result<Self> {
        let content = std::fs::read_to_string(&path)?;
        Ok(Self {
            load_timestamp_ms: get_load_timestamp_ms(),
            path,
            content,
        })
    }
}

fn get_load_timestamp_ms() -> TimestampMS {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .expect("the current timestamp shouldn't be before the UNIX epoch")
        .as_millis()
}

/// A struct to hold ownership of multiple [`Source`] instances in order to simplify lifetimes.
///
/// Adding a new source file/string will return a [`SourceRef`] that can be used to access the
/// source later.
///
/// # Examples
///
/// ```
/// # use toy_language::{SourceContext, SourceRef};
/// #
/// // Create a source context
/// let mut sctx = SourceContext::new();
///
/// // Add a string source
/// let test_ref = sctx.add_from_string(
///     "test.txt".to_owned(),
///     "hello, world\n".to_owned()
/// );
///
/// // You can use the reference to access the source
/// assert_eq!(test_ref.path, "test.txt");
/// ```

pub struct SourceContext {
    sources: Vec<Source>,
}

impl SourceContext {
    pub fn new() -> Self {
        Self {
            sources: Vec::new(),
        }
    }

    pub fn add_from_string<'ctx>(&'ctx mut self, path: String, content: String) -> SourceRef<'ctx> {
        let index = self.sources.len();

        self.sources.push(Source::new_from_string(path, content));

        SourceRef { ctx: self, index }
    }

    pub fn add_from_file<'ctx>(&'ctx mut self, path: String) -> io::Result<SourceRef<'ctx>> {
        let index = self.sources.len();

        self.sources.push(Source::load_from_file(path)?);

        Ok(SourceRef { ctx: self, index })
    }
}

/// A reference to a single source file/string in a [`SourceContext`].
///
/// # Examples
///
/// ```
/// # use toy_language::{SourceContext, SourceRef};
/// #
/// // Create a source context
/// let mut sctx = SourceContext::new();
///
/// // Add a string source
/// let test_ref = sctx.add_from_string(
///     "test.txt".to_owned(),
///     "hello, world\n".to_owned()
/// );
///
/// // You can use the reference to access the source
/// assert_eq!(test_ref.path, "test.txt");
/// ```
#[derive(Clone, Copy)]
pub struct SourceRef<'ctx> {
    ctx: &'ctx SourceContext,
    index: usize,
}

impl PartialEq for SourceRef<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.index == other.index
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
        write!(f, "{:?}", self.path)
    }
}

impl<'ctx> SourceRef<'ctx> {
    pub fn start(self) -> SourceLocation<'ctx> {
        SourceLocation {
            source: self,
            offset: 0,
            line: 1,
            col: 1,
        }
    }
}

/// A line number in source code, starting from 1.
pub type LineNumber = u32;

/// A column number in source code, starting from 1.
pub type ColumnNumber = u32;

#[derive(Error, Debug)]
pub enum GraphemeError {
    #[error("offset out of bounds")]
    OffsetOutOfBounds,

    #[error("no more graphemes to read at offset")]
    NoMoreGraphemes,
}

#[derive(Clone, PartialEq)]
pub struct SourceLocation<'ctx> {
    pub source: SourceRef<'ctx>,
    pub offset: usize,
    pub line: LineNumber,
    pub col: ColumnNumber,
}

impl Display for SourceLocation<'_> {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "{}:{}:{}+{}",
            self.source, self.line, self.col, self.offset
        )
    }
}

impl<'ctx> SourceLocation<'ctx> {
    /// Peeks the next extended grapheme cluster from the source code starting from the given location.
    ///
    /// # Returns
    ///
    /// Returns a tuple containing the string value of the extended grapheme cluster and the new source
    /// location for the next character after the grapheme.
    ///
    /// # Errors
    ///
    /// Returns a [`GraphemeError`] if the offset is out of bounds or if there are no more graphemes to
    /// read.
    ///
    /// # Examples
    ///
    /// ```
    /// # use toy_language::{SourceContext, SourceRef, SourceLocation, peek_next_grapheme};
    /// #
    /// # let mut sctx = SourceContext::new();
    /// #
    /// # let test_ref = sctx.add_from_string(
    /// #     "test.txt".to_owned(),
    /// #     "hello, world\n".to_owned()
    /// # );
    /// #
    /// # let location = SourceLocation {
    /// #     source: test_ref,
    /// #     offset: 0,
    /// #     line: 1,
    /// #     col: 1,
    /// # };
    /// #
    /// // Where 'location' is the first character of the source code "hello, world"
    /// let (grapheme, next_location) = peek_next_grapheme(location).unwrap();
    ///
    /// assert_eq!(grapheme, "h");
    /// assert_eq!(next_location.offset, 1);
    /// assert_eq!(next_location.line, 1);
    /// assert_eq!(next_location.col, 2);
    /// ```
    pub fn peek_next_grapheme(&self) -> Result<String, GraphemeError> {
        // Get the slice of the source code starting from the location offset
        let Some(slice) = self.source.content.get(self.offset..) else {
            return Err(GraphemeError::OffsetOutOfBounds);
        };

        // Read the next extended grapheme cluster
        let Some(grapheme) = slice.graphemes(true).next() else {
            return Err(GraphemeError::NoMoreGraphemes);
        };

        // Calculate the new location
        let new_location = SourceLocation {
            source: self.source,
            offset: self.offset + grapheme.len(),
            line: self.line + if grapheme == "\n" { 1 } else { 0 },
            col: if grapheme == "\n" { 1 } else { self.col + 1 },
        };

        // Return results
        Ok(grapheme.to_owned())
    }
}
