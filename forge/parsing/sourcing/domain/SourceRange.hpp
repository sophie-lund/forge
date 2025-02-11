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

#include <forge/parsing/sourcing/domain/SourceLocation.hpp>

/**
 * @namespace forge::parsing
 * @brief Code to support parsing syntax trees from text input.
 */
namespace forge::parsing {
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
  explicit SourceRange(SourceLocation&& first);

  /**
   * @brief Construct a source range that points to the range between two
   *        locations.
   */
  SourceRange(SourceLocation&& first, SourceLocation&& last);

  /**
   * @brief Get the location of the first character.
   */
  const SourceLocation& first() const;

  /**
   * @brief Get the location of the last character.
   *
   * This value is optional, so @c std::nullopt will be returned if the location
   * is not specified.
   */
  const std::optional<SourceLocation>& last() const;

 private:
  SourceLocation first_;
  std::optional<SourceLocation> last_;
};
}  // namespace forge::parsing
