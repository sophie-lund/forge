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

use std::fmt::Display;

use serde::Serialize;
use sorted_vec::partial::SortedVec;

use crate::{SourceRange, SourceRef};

/// How severe a message is.
#[derive(Debug, Clone, PartialEq, Serialize)]
pub enum MessageSeverity {
    /// A note, often used as a child of another message.
    #[serde(rename = "note")]
    Note,

    /// A warning which will not prevent compilation but should be addressed.
    #[serde(rename = "warning")]
    Warning,

    /// An error which will prevent compilation, but not stop it early.
    #[serde(rename = "error")]
    Error,

    /// An error which prevents compilation from completing normally.
    #[serde(rename = "fatalError")]
    FatalError,

    /// An internal error, indicating a bug in the compiler.
    #[serde(rename = "internalError")]
    InternalError,
}

impl PartialOrd for MessageSeverity {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.as_i32().partial_cmp(&other.as_i32())
    }
}

impl Display for MessageSeverity {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let severity_str = match self {
            Self::Note => "note",
            Self::Warning => "warning",
            Self::Error => "error",
            Self::FatalError => "fatal error",
            Self::InternalError => "internal error",
        };
        write!(f, "{}", severity_str)
    }
}

impl MessageSeverity {
    /// Used to implement enum ordering only, that's why it's private.
    fn as_i32(&self) -> i32 {
        match self {
            Self::Note => 0,
            Self::Warning => 1,
            Self::Error => 2,
            Self::FatalError => 3,
            Self::InternalError => 4,
        }
    }
}

/// The origin of a message, indicating where it comes from in the source code.
#[derive(Debug, Clone, PartialEq, Serialize)]
#[serde(untagged)]
pub enum MessageOrigin<'sctx> {
    /// The message originates from a file as a whole.
    Source(SourceRef<'sctx>),

    /// The message originates from a range in the source code.
    Range(SourceRange<'sctx>),
}

impl<'sctx> From<SourceRef<'sctx>> for MessageOrigin<'sctx> {
    fn from(value: SourceRef<'sctx>) -> Self {
        Self::Source(value)
    }
}

impl<'sctx> From<SourceRange<'sctx>> for MessageOrigin<'sctx> {
    fn from(value: SourceRange<'sctx>) -> Self {
        Self::Range(value)
    }
}

impl PartialOrd for MessageOrigin<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if let Some(ordering) = self.source().partial_cmp(&other.source())
            && ordering != std::cmp::Ordering::Equal
        {
            return Some(ordering);
        }

        match (self, other) {
            (Self::Source(_), Self::Range(_)) => Some(std::cmp::Ordering::Less),
            (Self::Range(_), Self::Source(_)) => Some(std::cmp::Ordering::Greater),
            (Self::Range(left), Self::Range(right)) => left.partial_cmp(right),
            (Self::Source(left), Self::Source(right)) => left.partial_cmp(right),
        }
    }
}

impl Display for MessageOrigin<'_> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::Source(source) => write!(f, "{}", source),
            Self::Range(range) => write!(f, "{}", range),
        }
    }
}

impl<'sctx> MessageOrigin<'sctx> {
    pub fn source(&self) -> SourceRef<'sctx> {
        match self {
            Self::Source(source) => *source,
            Self::Range(range) => range.first_location.source,
        }
    }
}

/// A message that can be output by the compiler.
#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct Message<'sctx> {
    /// Where the message came from.
    pub origin: MessageOrigin<'sctx>,

    /// How severe the message is.
    pub severity: MessageSeverity,

    /// The text of the message.
    pub message: String,

    /// Any child messages that are related to this message and should be output immediately after
    /// it.
    pub children: Vec<Message<'sctx>>,
}

impl PartialOrd for Message<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if let Some(ordering) = self.severity.partial_cmp(&other.severity)
            && ordering != std::cmp::Ordering::Equal
        {
            return Some(ordering);
        }

        self.origin.partial_cmp(&other.origin)
    }
}

impl<'sctx> Message<'sctx> {
    /// Creates a new message
    ///
    /// See [`Message`] for details on the parameters.
    pub fn new(
        origin: impl Into<MessageOrigin<'sctx>>,
        severity: MessageSeverity,
        message: String,
    ) -> Self {
        assert!(!message.is_empty(), "message cannot be empty");

        Self {
            origin: origin.into(),
            severity,
            message,
            children: Vec::new(),
        }
    }
}

/// A trait for anything that can output messages from the compiler to the user.
///
/// # Example
///
/// ```
/// # use forge_core::{MessageBuffer, OutputMessage, MessageSeverity, lex, SourceContext};
/// #
/// # let mut sctx = SourceContext::default();
/// #
/// # let source = sctx.add_from_string("test.frg".to_owned(), "x".to_owned()).unwrap();
/// #
/// // Create a message buffer to collect messages - this struct implements `OutputMessage` and
/// // collects messages so they can be printed later.
/// let mut msg = MessageBuffer::default();
/// #
/// # let tokens = lex(source, &mut msg).unwrap();
/// #
/// # let token = tokens.first().unwrap();
///
/// // Output a message from a token's source range.
/// msg.output_message(
///   token.range.clone(),
///   MessageSeverity::Error,
///   "This is an error message".to_owned(),
/// );
/// ```
pub trait OutputMessage<'sctx> {
    /// Outputs a message to the user as a struct instance.
    fn output_message_full(&mut self, message: Message<'sctx>);

    /// Outputs a message to the user with the same parameters as [`Message::new`].
    fn output_message(
        &mut self,
        origin: impl Into<MessageOrigin<'sctx>>,
        severity: MessageSeverity,
        message: String,
    ) {
        self.output_message_full(Message::new(origin, severity, message));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct MessageBuffer<'sctx> {
    pub messages: SortedVec<Message<'sctx>>,
}

impl Default for MessageBuffer<'_> {
    fn default() -> Self {
        Self {
            messages: SortedVec::new(),
        }
    }
}

impl Display for MessageBuffer<'_> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for message in self.messages.iter() {
            writeln!(f, "{}: {}", message.severity.as_i32(), message.message)?;
            for child in &message.children {
                writeln!(f, "  - {}: {}", child.severity.as_i32(), child.message)?;
            }
        }

        Ok(())
    }
}

impl Serialize for MessageBuffer<'_> {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        self.messages.serialize(serializer)
    }
}

impl<'sctx> OutputMessage<'sctx> for MessageBuffer<'sctx> {
    fn output_message_full(&mut self, message: Message<'sctx>) {
        self.messages.insert(message);
    }
}
