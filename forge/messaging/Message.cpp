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
    : sourceRange_(sourceRange),
      severity_(std::cref(severity)),
      code_(std::move(code)),
      text_(std::move(text)) {}

const std::optional<SourceRange>& Message::sourceRange() const {
  return sourceRange_;
}

const Severity& Message::severity() const { return severity_.get(); }

const std::string& Message::code() const { return code_; }

const std::string& Message::text() const { return text_; }
}  // namespace forge
