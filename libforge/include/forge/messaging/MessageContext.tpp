// Copyright 2025 Sophie Lund
//
// This file is part of Grove.
//
// Grove is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Grove is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Grove. If not, see <https://www.gnu.org/licenses/>.

namespace sycamore::messaging {
template <typename... TArgs>
void MessageContext::emit(TArgs&&... args) {
  messages_.emplace_back(std::forward<TArgs>(args)...);
}
}  // namespace sycamore::messaging
