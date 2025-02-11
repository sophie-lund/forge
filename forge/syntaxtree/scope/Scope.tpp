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

namespace forge {
template <typename TBaseNode>
Scope<TBaseNode>::Scope(std::shared_ptr<Scope<TBaseNode>> parent,
                        ScopeFlags flags)
    : parent_(parent), flags_(flags) {}

template <typename TBaseNode>
bool Scope<TBaseNode>::add(const std::string& key,
                           std::shared_ptr<TBaseNode> value) const {
  if (!value) {
    return false;
  }

  if (parent_ && parent_->get(key) != nullptr &&
      (flags_ & SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE) == 0) {
    return false;
  }

  auto [iterator, inserted] =
      const_cast<Scope*>(this)->map_.emplace(key, value);

  if (!inserted && (flags_ & SCOPE_FLAG_ALLOW_SHADOWING_WITHIN_SCOPE) != 0) {
    iterator->second = value;
    inserted = true;
  }

  return inserted;
}

template <typename TBaseNode>
bool Scope<TBaseNode>::remove(const std::string& key) const {
  return const_cast<Scope*>(this)->map_.erase(key) > 0;
}

template <typename TBaseNode>
std::shared_ptr<TBaseNode> Scope<TBaseNode>::get(const std::string& key) const {
  return const_cast<Scope*>(this)->map_.at(key);
}
}  // namespace forge
