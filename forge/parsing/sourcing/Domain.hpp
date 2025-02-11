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

/**
 * @file Domain.hpp
 *
 * @brief Contains domain objects for parsing source code.
 */

#pragma once

#include <optional>
#include <forge/parsing/sourcing/LineIndexedString.hpp>

/**
 * @namespace forge::parsing
 * @brief Code to support parsing syntax trees from text input.
 */
namespace forge::parsing {
/**
 * @brief A source file.
 */
class Source {
 public:
  /**
   * @param path The path to the source file.
   * @param content The content of the source file.
   */
  Source(std::string&& path, LineIndexedString&& content);

  Source(const Source& other) = delete;
  Source(Source&& other) = default;
  Source& operator=(const Source& other) = delete;
  Source& operator=(Source&& other) = default;

  /**
   * @brief Gets the path to the source file.
   */
  const std::string& path() const;

  /**
   * @brief Gets the content of the source file.
   */
  const LineIndexedString& content() const;

 private:
  std::string path_;
  LineIndexedString content_;
};

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
  const Source* source_;
  std::optional<uint32_t> line_;
  std::optional<uint32_t> column_;
  std::optional<size_t> offset_;
};

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
