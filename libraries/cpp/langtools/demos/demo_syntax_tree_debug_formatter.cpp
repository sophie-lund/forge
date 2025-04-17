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

#include <iostream>
#include <langtools/syntax_tree/formatting/debug_formatter.hpp>

using namespace lt;

int main() {
  DebugFormatter formatter(std::cout);

  formatter.node_label(NodeKind("parent"));

  formatter.field_label("x");
  formatter.stream() << 42;

  formatter.field_label("y");
  formatter.string("asdf");

  formatter.field_label("z");
  formatter.vector(std::vector<int>({1, 2, 3}),
                   [&](int item) { formatter.stream() << item; });

  formatter.field_label("child");

  formatter.node_label(NodeKind("child"));

  formatter.field_label("x");
  formatter.null();

  std::cout << std::endl;

  return 0;
}
