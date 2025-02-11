// Copyright 2025 Sophie Lund
//
// This file is part of Forge.
//
// Forge is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Forge is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Forge. If not, see <https://www.gnu.org/licenses/>.

#include <forge/parsing/sourcing/Domain.hpp>

namespace forge::parsing {
Source::Source(std::string&& path, LineIndexedString&& content)
    : path_(std::move(path)), content_(std::move(content)) {}

const std::string& Source::path() const { return path_; }

const LineIndexedString& Source::content() const { return content_; }

SourceLocation::SourceLocation() : source_(nullptr) {}

SourceLocation::SourceLocation(const Source& source) : source_(&source) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line)
    : source_(&source), line_(line) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line,
                               uint32_t column)
    : source_(&source), line_(line), column_(column) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line,
                               uint32_t column, size_t offset)
    : source_(&source), line_(line), column_(column), offset_(offset) {}

const Source* SourceLocation::source() const { return source_; }

const std::optional<uint32_t>& SourceLocation::line() const { return line_; }

const std::optional<uint32_t>& SourceLocation::column() const {
  return column_;
}

const std::optional<size_t>& SourceLocation::offset() const { return offset_; }

bool SourceLocation::operator==(const SourceLocation& other) const {
  if (source_ == nullptr) {
    if (other.source_ == nullptr) {
      return true;  // both have no source
    } else {
      return false;  // only 'other' has a source
    }
  } else {
    if (other.source_ == nullptr) {
      return false;  // only 'this' has a source
    } else {
      if (offset_.has_value()) {
        if (other.offset_.has_value()) {
          return offset_.value() ==
                 other.offset_
                     .value();  // both have offsets which can be compared
        } else {
          return false;  // only 'this' has an offset
        }
      } else {
        if (other.offset_.has_value()) {
          return false;  // only 'other' has an offset
        } else {
          return true;  // neither has an offset
        }
      }
    }
  }
}

bool SourceLocation::operator!=(const SourceLocation& other) const {
  return !operator==(other);
}

bool SourceLocation::operator<(const SourceLocation& other) const {
  if (source_ == nullptr) {
    if (other.source_ == nullptr) {
      return false;  // both have no source
    } else {
      return true;  // locations with no source come first
    }
  } else {
    if (other.source_ == nullptr) {
      return false;  // locations with sources come after locations without
    } else {
      if (offset_.has_value()) {
        if (other.offset_.has_value()) {
          return offset_.value() <
                 other.offset_
                     .value();  // both have offsets which can be compared
        } else {
          return false;  // locations with offsets come after locations without
        }
      } else {
        if (other.offset_.has_value()) {
          return true;  // locations without offsets come first
        } else {
          return false;  // neither has an offset
        }
      }
    }
  }
}

bool SourceLocation::operator<=(const SourceLocation& other) const {
  return operator<(other) || operator==(other);
}

bool SourceLocation::operator>(const SourceLocation& other) const {
  return (!operator<(other)) && (!operator==(other));
}

bool SourceLocation::operator>=(const SourceLocation& other) const {
  return !operator<(other);
}

SourceRange::SourceRange(SourceLocation&& first) : first_(std::move(first)) {}

SourceRange::SourceRange(SourceLocation&& first, SourceLocation&& last)
    : first_(std::move(first)), last_(std::move(last)) {}

const SourceLocation& SourceRange::first() const { return first_; }

const std::optional<SourceLocation>& SourceRange::last() const { return last_; }
}  // namespace forge::parsing
