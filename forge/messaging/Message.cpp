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

#include <forge/messaging/Message.hpp>

namespace forge {
Message::Message(const std::optional<SourceRange>& sourceRange,
                 const Severity& severity, std::string&& code,
                 std::string&& text)
    : _sourceRange(sourceRange),
      _severity(std::cref(severity)),
      _code(std::move(code)),
      _text(std::move(text)) {}

const std::optional<SourceRange>& Message::sourceRange() const {
  return _sourceRange;
}

const Severity& Message::severity() const { return _severity.get(); }

const std::string& Message::code() const { return _code; }

const std::string& Message::text() const { return _text; }
}  // namespace forge
