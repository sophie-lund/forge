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

#include <forge/core/string_utilities.hpp>

namespace forge {
std::string trim(const std::string& s) {
  auto start = std::find_if(s.begin(), s.end(),
                            [](unsigned char ch) { return !std::isspace(ch); });
  auto end = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
               return !std::isspace(ch);
             }).base();
  return (start < end) ? std::string(start, end) : std::string();
}

size_t count_whitespace_chars_at_start(const std::string& s) {
  size_t count = 0;

  for (const auto& c : s) {
    if (c == ' ' || c == '\t') {
      count++;
    } else {
      break;
    }
  }

  return count;
}
}  // namespace forge
