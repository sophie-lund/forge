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

#include <forge/parsing/domain/source_location.hpp>

namespace forge {
SourceLocation::SourceLocation() : source(nullptr) {}

SourceLocation::SourceLocation(const Source& source) : source(&source) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line)
    : source(&source), line(line) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line,
                               uint32_t column)
    : source(&source), line(line), column(column) {}

SourceLocation::SourceLocation(const Source& source, uint32_t line,
                               uint32_t column, size_t offset)
    : source(&source), line(line), column(column), offset(offset) {}

bool SourceLocation::operator==(const SourceLocation& other) const {
  if (source == nullptr) {
    if (other.source == nullptr) {
      return true;  // both have no source
    } else {
      return false;  // only 'other' has a source
    }
  } else {
    if (other.source == nullptr) {
      return false;  // only 'this' has a source
    } else {
      if (offset.has_value()) {
        if (other.offset.has_value()) {
          return offset.value() ==
                 other.offset
                     .value();  // both have offsets which can be compared
        } else {
          return false;  // only 'this' has an offset
        }
      } else {
        if (other.offset.has_value()) {
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
  if (source == nullptr) {
    if (other.source == nullptr) {
      return false;  // both have no source
    } else {
      return true;  // locations with no source come first
    }
  } else {
    if (other.source == nullptr) {
      return false;  // locations with sources come after locations without
    } else {
      if (offset.has_value()) {
        if (other.offset.has_value()) {
          return offset.value() <
                 other.offset
                     .value();  // both have offsets which can be compared
        } else {
          return false;  // locations with offsets come after locations without
        }
      } else {
        if (other.offset.has_value()) {
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
