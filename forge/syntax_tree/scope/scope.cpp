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

#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/scope/scope.hpp>

namespace forge {
bool Scope::add(const std::string& key, std::shared_ptr<BaseNode> value) const {
  if (!value) {
    return false;
  }

  return const_cast<Scope*>(this)->_map.emplace(key, value).second;
}

bool Scope::remove(const std::string& key) const {
  return const_cast<Scope*>(this)->_map.erase(key) > 0;
}

std::shared_ptr<BaseNode> Scope::get(const std::string& key) const {
  auto iterator = const_cast<Scope*>(this)->_map.find(key);

  if (iterator == _map.end()) {
    return nullptr;
  } else {
    return iterator->second;
  }
}

std::ostream& operator<<(std::ostream& stream, const Scope& scope) {
  bool first = true;

  for (auto i = scope._map.begin(); i != scope._map.end(); i++) {
    if (first) {
      first = false;
    } else {
      stream << ", ";
    }

    stream << i->first << ": " << i->second->kind;
  }

  if (first) {
    stream << "empty";
  }

  return stream;
}
}  // namespace forge
