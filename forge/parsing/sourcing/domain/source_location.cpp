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

#include <forge/parsing/sourcing/domain/source_location.hpp>

namespace forge {
SourceLocation::SourceLocation() : _source(nullptr) {}

SourceLocation::SourceLocation(const Source& source) : _source(&source) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line)
    : _source(&source), _line(line) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line,
                               uint32_t column)
    : _source(&source), _line(line), _column(column) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line,
                               uint32_t column, size_t offset)
    : _source(&source), _line(line), _column(column), _offset(offset) {}

const Source* SourceLocation::source() const { return _source; }

const std::optional<uint32_t>& SourceLocation::line() const { return _line; }

const std::optional<uint32_t>& SourceLocation::column() const {
  return _column;
}

const std::optional<size_t>& SourceLocation::offset() const { return _offset; }

bool SourceLocation::operator==(const SourceLocation& other) const {
  if (_source == nullptr) {
    if (other._source == nullptr) {
      return true;  // both have no source
    } else {
      return false;  // only 'other' has a source
    }
  } else {
    if (other._source == nullptr) {
      return false;  // only 'this' has a source
    } else {
      if (_offset.has_value()) {
        if (other._offset.has_value()) {
          return _offset.value() ==
                 other._offset
                     .value();  // both have offsets which can be compared
        } else {
          return false;  // only 'this' has an offset
        }
      } else {
        if (other._offset.has_value()) {
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
  if (_source == nullptr) {
    if (other._source == nullptr) {
      return false;  // both have no source
    } else {
      return true;  // locations with no source come first
    }
  } else {
    if (other._source == nullptr) {
      return false;  // locations with sources come after locations without
    } else {
      if (_offset.has_value()) {
        if (other._offset.has_value()) {
          return _offset.value() <
                 other._offset
                     .value();  // both have offsets which can be compared
        } else {
          return false;  // locations with offsets come after locations without
        }
      } else {
        if (other._offset.has_value()) {
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
}  // namespace forge
