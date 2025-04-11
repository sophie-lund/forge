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

#include <forge/parsing/domain/source_range.hpp>
#include <ostream>

namespace forge {
SourceRange::SourceRange(SourceLocation&& start) : start(std::move(start)) {}

SourceRange::SourceRange(SourceLocation&& start, SourceLocation&& end)
    : start(std::move(start)), end(std::move(end)) {}

SourceRange::operator bool() const { return start.source; }

std::ostream& operator<<(std::ostream& stream,
                         const SourceRange& source_range) {
  stream << source_range.start;

  if (source_range.end.has_value()) {
    stream << " - " << source_range.end.value();
  }

  return stream;
}

SourceRange combine_source_ranges(const SourceRange& first,
                                  const SourceRange& second) {
  SourceLocation start = std::min(first.start, second.start);

  std::optional<SourceLocation> end;

  if (first.end.has_value()) {
    if (second.end.has_value()) {
      end = std::max(first.end.value(), second.end.value());
    } else {
      end = first.end;
    }
  } else {
    if (second.end.has_value()) {
      end = second.end;
    } else {
      end = std::nullopt;
    }
  }

  if (end.has_value()) {
    return SourceRange(std::move(start), std::move(end.value()));
  } else {
    return SourceRange(std::move(start));
  }
}
}  // namespace forge
