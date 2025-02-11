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

#include <termcolor/termcolor.hpp>

namespace forge::core {
class _NullBuffer : public std::streambuf {
 public:
  int overflow(int c);
};

extern uint32_t _traceIndentLevel;
extern bool _traceEnabled;
extern _NullBuffer _nullBuffer;
extern std::ostream _nullOStream;

inline void traceIndent() { _traceIndentLevel++; }

inline void traceDedent() {
  if (_traceIndentLevel > 0) {
    _traceIndentLevel--;
  }
}

template <typename TName>
inline std::ostream& trace(TName name) {
  if (_traceEnabled) {
    for (uint32_t i = 0; i < _traceIndentLevel * 2; i++) {
      std::cout << " ";
    }

    std::cout << termcolor::grey << "[" << name << "] " << termcolor::reset;

    return std::cout;
  } else {
    return _nullOStream;
  }
}
}  // namespace forge::core
