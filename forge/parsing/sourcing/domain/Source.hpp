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

#include <forge/parsing/sourcing/LineIndexedString.hpp>

namespace forge {
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
  std::string _path;
  LineIndexedString _content;
};
}  // namespace forge
