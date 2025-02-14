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

#include <forge/messaging/severity.hpp>
#include <termcolor/termcolor.hpp>

namespace forge {
Severity::Severity(uint32_t value, const char* name,
                   std::function<void(std::ostream&)> formatColor)
    : _value(value), _name(name), _formatColor(formatColor) {}

void Severity::formatColor(std::ostream& stream) const { _formatColor(stream); }

void Severity::formatName(std::ostream& stream) const { stream << _name; }

uint32_t Severity::value() const { return _value; }

const Severity SEVERITY_SUGGESTION(100, "suggestion", [](std::ostream& stream) {
  stream << termcolor::green;
});

const Severity SEVERITY_FIX(200, "fix", [](std::ostream& stream) {
  stream << termcolor::bright_blue;
});

const Severity SEVERITY_WARNING(300, "warning", [](std::ostream& stream) {
  stream << termcolor::yellow;
});

const Severity SEVERITY_ERROR(400, "error", [](std::ostream& stream) {
  stream << termcolor::red;
});

const Severity SEVERITY_FATAL_ERROR(500, "fatal error",
                                    [](std::ostream& stream) {
                                      stream << termcolor::bright_red;
                                    });
}  // namespace forge
