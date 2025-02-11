<!--
Copyright 2025 Sophie Lund

This file is part of Forge.

Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with Forge. If not, see
<https://www.gnu.org/licenses/>.
-->

# Well formed validation

Every syntax tree should ideally have a well formed validation which makes sure that the basic rules of the language are followed. This is a good way to check for things like:

- Variables not having empty strings for names
- Binary operations having non-null operands

This is not the place to check for things like:

- Symbols being defined before they are used
- Types being compatible

## Introduction to handlers

This is the first time we will be using handlers and passes in Forge.

- **Passes** are visitors which are used to traverse the syntax tree.
- **Handlers** are used to define hooks which are called when entering or leaving a syntax tree node during the traversal.

Why keep them separate? For optimization. You can have multiple handlers that are called in sequence for any given node defined in a pass. That way you can do multiple things with a single traversal of the tree. Most compilers will still need multiple passes for various reasons.

Let's define our first handler:

```cpp
#include <forge/syntaxtree/Node.hpp>

using namespace forge;

class WellFormedValidationHandler : public syntaxtree::Handler<ExampleNode> {
 protected:
  virtual void onEnter(
      messaging::MessageContext& messageContext,
      const std::vector<std::reference_wrapper<const ExampleNode>>& stack,
      const ExampleNode& node) override {
        // ...
  }

  virtual void onLeave(
      messaging::MessageContext& messageContext,
      const std::vector<std::reference_wrapper<const ExampleNode>>& stack,
      const ExampleNode& node) override {
        // ...
  }
};
```

Every handler has two methods to override: `onEnter` and `onLeave`. These are called when entering and leaving a node, respectively. They both always need to be declared, but can be left empty if there is nothing to do.

They both take in the same three arguments:

- `messageContext` - a context which can be used to emit error or warning messages.
- `stack` - a vector of references to the nodes in the current path from the root to the current node.
  - `stack[0]` will be the root node.
  - `stack.back()` will be the direct parent of `node`.
- `node` - the current node being visited.

Usually, they will contain switch statements like this:

```cpp hl_lines="5-17"
virtual void onLeave(
      messaging::MessageContext& messageContext,
      const std::vector<std::reference_wrapper<const ExampleNode>>& stack,
      const ExampleNode& node) override {
  switch (node.kind) {
    case ExampleNodeKind::ValueAdd:
      // ...

      break;

    // ...

    default:
      // ...

      break;
  }
}
```

Let's implement an example node below.

## Using a validation helper

We can do this by adding in a validation check in the `onLeave` method for `ValueSymbol` nodes:

```cpp hl_lines="10-17"
#include <forge/syntaxtree/Validators.hpp>

virtual void onLeave(
      messaging::MessageContext& messageContext,
      const std::vector<std::reference_wrapper<const ExampleNode>>& stack,
      const ExampleNode& node) override {
  switch (node.kind) {
    // ...

    case ExampleNodeKind::ValueSymbol:
      if (!syntaxtree::validateStringNonEmpty(
            messageContext, node, "name",
            static_cast<const ExampleValueSymbol&>(node).name)) {
        break;
      }

      break;

    // ...
  }
}
```

Here you can see the `syntaxtree::validateStringNonEmpty` helper function being used. It takes in four arguments:

- `messageContext` - which is just the value passed into the `onEnter` or `onLeave` method
- `node` - the current node being visited
- `fieldName` - the name of the field being validated. This is used for debugging purposes.
- `fieldValue` - the value of the field that we're validating

There are a number of validation helper methods which are all defined in [`Validators.hpp`](https://github.com/sophie-lund/forge/blob/main/include/forge/syntaxtree/Validators.hpp). You can use these to build up validation logic for all node types in your language.

## Full validator

See the full example in [`ExampleLanguage.cpp`](https://github.com/sophie-lund/forge/blob/main/test/ExampleLanguage.cpp).
