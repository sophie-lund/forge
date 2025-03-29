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

#pragma once

#include <forge/parsing/domain/source_location.hpp>

namespace forge {
/**
 * @brief Points to a range within source code.
 */
class SourceRange {
 public:
  /**
   * @brief Construct a source range that points to nothing.
   *
   * This can be used for expressing errors that are not associated with a file.
   */
  SourceRange() = default;

  /**
   * @brief Construct a source range that points to a single location.
   *
   * This can be used for if the range is just one single location and not
   * spread across multiple.
   */
  explicit SourceRange(SourceLocation&& start);

  /**
   * @brief Construct a source range that points to the range between two
   *        locations.
   */
  SourceRange(SourceLocation&& start, SourceLocation&& end);

  /**
   * @brief The start of the range.
   */
  SourceLocation start;

  /**
   * @brief The end of the range.
   *
   * If this is @c std::nullopt then the range is just a single location.
   */
  std::optional<SourceLocation> end;
};

std::ostream& operator<<(std::ostream& stream, const SourceRange& source_range);
}  // namespace forge
