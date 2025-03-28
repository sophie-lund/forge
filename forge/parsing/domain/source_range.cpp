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

std::ostream& operator<<(std::ostream& stream,
                         const SourceRange& source_range) {
  stream << source_range.start;

  if (source_range.end.has_value()) {
    stream << " - " << source_range.end.value();
  }

  return stream;
}
}  // namespace forge
