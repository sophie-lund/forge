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
#include <langtools/messaging/message_context.hpp>
#include <langtools/reporting/reporter.hpp>

using namespace lt;

int main() {
  Source source("test.frg",
                LineIndexedUnicodeString("func main() {\n"
                                         "  return 0;\n"
                                         "}\n"
                                         "\n"
                                         "func f() {\n"
                                         "  print(\"hello, world\");\n"
                                         "}\n"));

  MessageContext message_context;

  message_context.emit(SourceRange(), SEVERITY_ERROR, "EI001",
                       "unable to open file 'test.frg'");

  message_context
      .emit(SourceRange(SourceLocation(source, 5, 1),
                        SourceLocation(source, 7, 1)),
            SEVERITY_WARNING, "WC001", "function 'f' has complexity 10")
      .child(SourceRange(), SEVERITY_NOTE, "max recommended is 7");

  message_context.emit(
      SourceRange(SourceLocation(source, 6, 3), SourceLocation(source, 6, 7)),
      SEVERITY_ERROR, "ER001", "use of undefined symbol 'print'");

  report_messages(std::cerr, message_context);

  return 0;
}
