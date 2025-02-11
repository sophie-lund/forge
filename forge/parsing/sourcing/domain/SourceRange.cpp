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

#include <forge/parsing/sourcing/domain/SourceRange.hpp>

namespace forge {
SourceRange::SourceRange(SourceLocation&& first) : first_(std::move(first)) {}

SourceRange::SourceRange(SourceLocation&& first, SourceLocation&& last)
    : first_(std::move(first)), last_(std::move(last)) {}

const SourceLocation& SourceRange::first() const { return first_; }

const std::optional<SourceLocation>& SourceRange::last() const { return last_; }
}  // namespace forge
