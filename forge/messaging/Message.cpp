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

#include <forge/messaging/message.hpp>

namespace forge {
Message::Message(SourceRange source_range, const Severity& severity,
                 std::string code, std::string text)
    : source_range(source_range),
      severity(std::cref(severity)),
      code(std::optional(code)),
      text(text) {}

Message& Message::child(SourceRange source_range, const Severity& severity,
                        std::string text) {
  children.push_back(Message(source_range, severity, text));

  return *this;
}

Message::Message(SourceRange source_range, const Severity& severity,
                 std::string text)
    : source_range(source_range), severity(std::cref(severity)), text(text) {}
}  // namespace forge
