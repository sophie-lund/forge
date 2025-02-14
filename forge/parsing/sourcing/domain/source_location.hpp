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

#include <forge/parsing/sourcing/domain/source.hpp>
#include <optional>

namespace forge {
/**
 * @brief Points to a location of source code.
 */
class SourceLocation {
 public:
  /**
   * @brief Construct a source location that points to nothing.
   *
   * This can be used for expressing errors that are not associated with a file.
   */
  SourceLocation();

  /**
   * @brief Create a source location that points to a file, but not any specific
   *        character in that file.
   *
   * This can be used for expressing errors that are associated with a file, but
   * any specific part of that file.
   *
   * @param source The source file to point to.
   */
  explicit SourceLocation(const Source& source);

  /**
   * @brief Creates a source location that points to a line in a file but not
   *        any specific character in that line.
   *
   * This can be used for expressing errors that are associated with a line, but
   * not any specific character in that line.
   *
   * @param source The source file to point to.
   * @param line The line number starting with @c 1 to point to.
   */
  SourceLocation(const Source& source, uint32_t line);

  /**
   * @brief Creates a source location that points to a specific character in a
   *        file identified by line and column.
   *
   * @param source The source file to point to.
   * @param line The line number starting with @c 1 to point to.
   * @param column The column number starting with @c 1 to point to.
   */
  SourceLocation(const Source& source, uint32_t line, uint32_t column);

  /**
   * @brief Creates a source location that points to a specific character in a
   *        file identified by line, column, and offset.
   *
   * @param source The source file to point to.
   * @param line The line number starting with @c 1 to point to.
   * @param column The column number starting with @c 1 to point to.
   * @param offset The offset in bytes within the file to point to.
   */
  SourceLocation(const Source& source, uint32_t line, uint32_t column,
                 size_t offset);

  /**
   * @brief Gets the source file that this location points to.
   *
   * This value is optional, so @c nullptr will be returned if the source is not
   * specified.
   */
  const Source* source() const;

  /**
   * @brief Gets the line number starting with @c 1 within the file that this
   *        location points to.
   *
   * This value is optional, so @c std::nullopt will be returned if the line
   * is not specified.
   */
  const std::optional<uint32_t>& line() const;

  /**
   * @brief Gets the column number starting with @c 1 within the file that this
   *        location points to.
   *
   * This value is optional, so @c std::nullopt will be returned if the column
   * is not specified.
   */
  const std::optional<uint32_t>& column() const;

  /**
   * @brief Gets the offset in bytes within the file that this location points
   *        to.
   *
   * This value is optional, so @c std::nullopt will be returned if the offset
   * is not specified.
   */
  const std::optional<size_t>& offset() const;

  bool operator==(const SourceLocation& other) const;
  bool operator!=(const SourceLocation& other) const;
  bool operator<(const SourceLocation& other) const;
  bool operator<=(const SourceLocation& other) const;
  bool operator>(const SourceLocation& other) const;
  bool operator>=(const SourceLocation& other) const;

 private:
  const Source* _source;
  std::optional<uint32_t> _line;
  std::optional<uint32_t> _column;
  std::optional<size_t> _offset;
};
}  // namespace forge
