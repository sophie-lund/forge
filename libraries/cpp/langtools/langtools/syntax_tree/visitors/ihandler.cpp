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

#include <langtools/syntax_tree/visitors/ihandler.hpp>

namespace lt {
IHandler::Output::Output() : status_(VisitorStatus::continue_) {}

IHandler::Output::Output(VisitorStatus status) : status_(status) {}

IHandler::Output::Output(std::shared_ptr<BaseNode>&& replacement)
    : status_(VisitorStatus::continue_), replacement_(std::move(replacement)) {}

IHandler::Output::Output(VisitorStatus status,
                         std::shared_ptr<BaseNode>&& replacement)
    : status_(status), replacement_(std::move(replacement)) {}

VisitorStatus IHandler::Output::status() const { return status_; }

bool IHandler::Output::has_replacement() const {
  return replacement_ != nullptr;
}

std::shared_ptr<BaseNode> IHandler::Output::take_replacement() {
  return std::move(replacement_);
}

IHandler::~IHandler() {}
}  // namespace lt
