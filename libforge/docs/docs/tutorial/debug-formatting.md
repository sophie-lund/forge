<!--
Copyright 2025 Sophie Lund

This file is part of Grove.

Grove is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Grove is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with Grove. If not, see
<https://www.gnu.org/licenses/>.
-->

# Debug formatting

Wanting to print out a syntax tree for debugging is a very common use case. Sycamore provides a built-in way to do this. We've already seen in [Defining a syntax tree](./defining-a-syntax-tree.md) how to implement the [`onFormatDebug`](./defining-a-syntax-tree.md#onformatdebug-printing-field-values) method on all of our node types.

In order to actually print it out to the console, you need to use the `syntaxtree::DebugFormatter` class - but it's an abstract base class. You need to implement it for your specific syntax tree:

```cpp
#include <forge/syntaxtree/Node.hpp>

using namespace sycamore;

class ExampleDebugFormatter
    : public syntaxtree::DebugFormatter<ExampleNodeKind> {
 public:
  ExampleDebugFormatter(std::ostream& stream) : DebugFormatter(stream) {}

 protected:
  virtual void onFormatNodeKind(const ExampleNodeKind& kind) override {
    // ...
  }
};
```

Make sure to include the declaration for `ExampleNodeKind` from the [previous tutorial](./defining-a-syntax-tree.md).

## Formatting node kinds

So what do we put in `onFormatNodeKind`? Remember that our enum looks like this:

```cpp
enum class ExampleNodeKind {
  TypeBool,
  TypeInt,
  TypeFunction,
  ValueBool,
  ValueInt,
  ValueSymbol,
  ValueAdd,
  ValueNeg,
  ValueLT,
  ValueEQ,
  ValueCall,
  StatementIf,
  StatementWhile,
  StatementContinue,
  StatementBreak,
  StatementReturn,
  StatementBlock,
  DeclarationVariable,
  DeclarationFunction,
  TranslationUnit,
};
```

We just need to define a name for each of these values:

```cpp hl_lines="8-69"
class ExampleDebugFormatter
    : public syntaxtree::DebugFormatter<ExampleNodeKind> {
 public:
  ExampleDebugFormatter(std::ostream& stream) : DebugFormatter(stream) {}

 protected:
  virtual void onFormatNodeKind(const ExampleNodeKind& kind) override {
    switch (kind) {
      case ExampleNodeKind::TypeBool:
        stream() << "TypeBool";
        break;
      case ExampleNodeKind::TypeInt:
        stream() << "TypeInt";
        break;
      case ExampleNodeKind::TypeFunction:
        stream() << "TypeFunction";
        break;
      case ExampleNodeKind::ValueBool:
        stream() << "ValueBool";
        break;
      case ExampleNodeKind::ValueInt:
        stream() << "ValueInt";
        break;
      case ExampleNodeKind::ValueSymbol:
        stream() << "ValueSymbol";
        break;
      case ExampleNodeKind::ValueAdd:
        stream() << "ValueAdd";
        break;
      case ExampleNodeKind::ValueNeg:
        stream() << "ValueNeg";
        break;
      case ExampleNodeKind::ValueLT:
        stream() << "ValueLT";
        break;
      case ExampleNodeKind::ValueEQ:
        stream() << "ValueEQ";
        break;
      case ExampleNodeKind::ValueCall:
        stream() << "ValueCall";
        break;
      case ExampleNodeKind::StatementIf:
        stream() << "StatementIf";
        break;
      case ExampleNodeKind::StatementWhile:
        stream() << "StatementWhile";
        break;
      case ExampleNodeKind::StatementContinue:
        stream() << "StatementContinue";
        break;
      case ExampleNodeKind::StatementBreak:
        stream() << "StatementBreak";
        break;
      case ExampleNodeKind::StatementReturn:
        stream() << "StatementReturn";
        break;
      case ExampleNodeKind::StatementBlock:
        stream() << "StatementBlock";
        break;
      case ExampleNodeKind::DeclarationVariable:
        stream() << "DeclarationVariable";
        break;
      case ExampleNodeKind::DeclarationFunction:
        stream() << "DeclarationFunction";
        break;
      case ExampleNodeKind::TranslationUnit:
        stream() << "TranslationUnit";
        break;
    }
  }
};
```

It's long, but relatively straightforward.

## Printing it to `std::cout`

That's all we need to print out a syntax tree to the console. Here's an example of how to do it:

```cpp
#include <iostream>

// ...

int main() {
  // Instantiate a syntax tree
  auto node = std::make_shared<ExampleTranslationUnit>(
    // ...
  );

  // Create a debug formatter
  ExampleDebugFormatter debugFormatter(std::cout);

  // Actually print it
  debugFormatter.node(node);

  return 0;
}
```

This will print out something like this (with terminal colors that aren't present in this documentation):

```
[TranslationUnit]
  declarations =
    [0] = [DeclarationVariable]
      name = "x"
      type = [TypeInt]
      value = [ValueInt]
        value = 42
    [1] = [DeclarationFunction]
      name = "add"
      returnType = [TypeInt]
      args =
        [0] = [DeclarationVariable]
          name = "x"
          type = [TypeInt]
          value = null
        [1] = [DeclarationVariable]
          name = "y"
          type = [TypeInt]
          value = null
      body = [StatementBlock]
        statements =
          [0] = [StatementReturn]
            value = [ValueAdd]
              lhs = [ValueSymbol]
                name = "x"
              rhs = [ValueSymbol]
                name = "y"
```

See [`ExampleLanguage.cpp`](https://github.com/sophie-lund/grove/blob/500ba5f38016e436810528c84af5623e6c9ea6e5/projects/sycamore/v1/test/sycamore-syntaxtree/ExampleLanguage.cpp#L1467) for an example of how to do this for a complete syntax tree.
