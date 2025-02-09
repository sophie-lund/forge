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

#include <iostream>
#include <forge/syntaxtree/DebugFormatter.hpp>

class DemoDebugFormatter
    : public sycamore::syntaxtree::DebugFormatter<std::string> {
 public:
  DemoDebugFormatter(std::ostream& stream)
      : sycamore::syntaxtree::DebugFormatter<std::string>(stream) {}

 protected:
  virtual void onFormatNodeKind(const std::string& kind) override {
    stream() << kind;
  }
};

int main() {
  DemoDebugFormatter formatter(std::cout);

  formatter.nodeLabel("Parent");

  formatter.fieldLabel("x");
  formatter.stream() << 42;

  formatter.fieldLabel("y");
  formatter.string("asdf");

  formatter.fieldLabel("z");
  formatter.vector(std::vector<int>({1, 2, 3}),
                   [&](int item) { formatter.stream() << item; });

  formatter.fieldLabel("child");

  formatter.nodeLabel("Child");

  formatter.fieldLabel("x");
  formatter.null();

  std::cout << std::endl;

  return 0;
}
