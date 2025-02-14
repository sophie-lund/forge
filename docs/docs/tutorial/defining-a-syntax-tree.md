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

# Defining a syntax tree

All of the code that is referenced here can be found in [`ExampleLanguage.cpp`](https://github.com/sophie-lund/forge/blob/main/test/ExampleLanguage.cpp), although it's broken up here to be a lot easier to follow than one big C++ file.

## Node kind enum

You'll need to begin by declaring the structure of your syntax tree, beginning with an enum of all of the kinds of nodes that can be found. It can look something like this:

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

You can see types, values, statements, and declarations in this list. There is also `TranslationUnit` which is the top level node that contains a list of declarations in the global scope. This is a pretty standard list for a simple programming language.

## Node base class

Next, you'll need to declare a base class for all of your nodes. This will be an abstract class but it will be critical for much of the implementation.

```cpp
#include <forge/syntax_tree/Node.hpp>

using namespace forge;

class ExampleNode : public Node<ExampleNode, ExampleNodeKind> {
 public:
  ExampleNode(ExampleNodeKind&& kind,
              std::optional<SourceRange>&& sourceRange)
      : Node(std::move(kind), std::move(sourceRange)) {}

  virtual ~ExampleNode() = 0;
};
```

`Node` is an abstract base class provided by Forge for all nodes in any programming language. All you need to do is provide your own constructor that takes in two arguments:

- `kind` - The kind of node that this is, taken from your enum declared above.
- `sourceRange` - An optional source range that points towards the original source code from which this syntax tree node was parsed. This is used for debugging and error messages.

## Category base classes

This is optional, but very helpful! A lot of times you want to specify the category of a node at compile time. For example, you have an addition operator and you want to pass in two nodes as operators.

- You can pass them in with type `ExampleNode`, but then you could have a syntax tree where a number is being added to a variable declaration.
- You can define an abstract base class `ExampleValue` from which all values inherit. Then you can have your addition operator take in two `ExampleValue` nodes, ensuring that they are both at least values.

This helps with clarity and gives a bit of compile time checking in a world where runtime checks are heavily relied upon.

Let's declare some:

```cpp
class ExampleType : public ExampleNode {
 public:
  ExampleType(ExampleNodeKind&& kind,
              std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleType() = 0;
};

ExampleType::~ExampleType() {}

class ExampleValue : public ExampleNode {
 public:
  ExampleValue(ExampleNodeKind&& kind,
               std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleValue() = 0;
};

ExampleValue::~ExampleValue() {}

class ExampleStatement : public ExampleNode {
 public:
  ExampleStatement(ExampleNodeKind&& kind,
                   std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleStatement() = 0;
};

ExampleStatement::~ExampleStatement() {}

class ExampleDeclaration : public ExampleNode {
 public:
  ExampleDeclaration(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleDeclaration() = 0;
};

ExampleDeclaration::~ExampleDeclaration() {}
```

## First node type

So far all we've declared are abstract base classes. Let's declare our first node type that can actually be used: a boolean type.

```cpp
class ExampleTypeBool : public ExampleType {
 public:
  ExampleTypeBool(std::optional<SourceRange>&& sourceRange)
      : ExampleType(ExampleNodeKind::TypeBool, std::move(sourceRange)) {}

 protected:
  virtual void onAccept(Pass<ExampleNode>&) const override {}

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleTypeBool>(
        std::optional<SourceRange>(sourceRange));
  }

  virtual bool onCompare(const ExampleNode&) const override { return true; }
};
```

There's a lot going on here! Let's break it down:

```cpp
virtual void onAccept(Pass<ExampleNode>&) const override {}
```

This method declares the child nodes of this node. See the [section on it](#onaccept-implementing-the-visitor-pattern) for more info.

Since there are no child nodes for `ExampleTypeBool`, we can leave it empty.

```cpp
virtual void onFormatDebug(
    DebugFormatter<ExampleNodeKind>&) const override {}
```

This method is used to print out the fields of the node for debugging. See the [section on it](#onformatdebug-printing-field-values) for more info.

Since there are no fields in this type, we can leave it empty.

```cpp
virtual std::shared_ptr<ExampleNode> onClone() const override {
  return std::make_shared<ExampleTypeBool>(
      std::optional<SourceRange>(sourceRange));
}
```

This method returns an exact copy of the current node. It should essentially be a constructor call. See [this section](#onclone-returning-an-identical-copy) for more details.

```cpp
virtual bool onCompare(const ExampleNode&) const override { return true; }
```

This method compares the current node with another node. It should compare all of the fields of the node. Since there are no fields in this type, we can simply return `true`. See [this section](#oncompare-deep-comparison-for-syntax-trees) for more details.

## A more complicated node type

Let's define a type for functions. Unlike `ExampleTypeBool` this node type will have fields and child nodes.

```cpp
#include <forge/syntax_tree/Cloners.hpp>
#include <forge/syntax_tree/Comparators.hpp>

using namespace forge;

class ExampleTypeFunction : public ExampleType {
 public:
  ExampleTypeFunction(std::optional<SourceRange>&& sourceRange,
                      std::shared_ptr<ExampleType>&& returnType,
                      std::vector<std::shared_ptr<ExampleType>>&& argTypes)
      : ExampleType(ExampleNodeKind::TypeFunction, std::move(sourceRange)),
        returnType(std::move(returnType)),
        argTypes(std::move(argTypes)) {}

  std::shared_ptr<ExampleType> returnType;
  std::vector<std::shared_ptr<ExampleType>> argTypes;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) const override {
    pass.visit(returnType);
    pass.visit(argTypes);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("returnType");
    formatter.node(returnType);

    formatter.fieldLabel("argTypes");
    formatter.nodeVector(argTypes);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleTypeFunction>(
        std::optional<SourceRange>(sourceRange),
        clone(returnType), clone(argTypes));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compare(
               returnType,
               static_cast<const ExampleTypeFunction&>(other).returnType) &&
           compare(
               argTypes,
               static_cast<const ExampleTypeFunction&>(other).argTypes);
  }
};
```

There's a lot more code here! Let's break it down:

```cpp
std::shared_ptr<ExampleType> returnType;
std::vector<std::shared_ptr<ExampleType>> argTypes;
```

The child nodes are all wrapped with `std::shared_ptr<...>`. This type of smart pointer makes tree operations much simpler and more readable, so it's required by a lot of Forge code.

```cpp
ExampleTypeFunction(std::optional<SourceRange>&& sourceRange,
                    std::shared_ptr<ExampleType>&& returnType,
                    std::vector<std::shared_ptr<ExampleType>>&& argTypes)
  : ExampleType(ExampleNodeKind::TypeFunction, std::move(sourceRange)),
    returnType(std::move(returnType)),
    argTypes(std::move(argTypes)) {}
```

Our constructor is straightforward in that it just accepts all of the field values. All of them are defined here with move semantics for efficiency.

```cpp
virtual void onAccept(Pass<ExampleNode>& pass) const override {
  pass.visit(returnType);
  pass.visit(argTypes);
}
```

You can see how we're using `pass.visit(...)` to essentially declare a list of child nodes. It works with a single node like `returnType` or a vector of nodes like `argTypes`.

Every child node must be visited in this method. This is how the visitor pattern is implemented. See [this section](#onaccept-implementing-the-visitor-pattern) for more details.

```cpp
virtual void onFormatDebug(
    DebugFormatter<ExampleNodeKind>& formatter) const override {
  formatter.fieldLabel("returnType");
  formatter.node(returnType);

  formatter.fieldLabel("argTypes");
  formatter.nodeVector(argTypes);
}
```

This method is similar to `onAccept` in that it goes through all of the child fields, but it _also_ goes through any non-node fields. There aren't any here, but we'll see how they can be used later on. See [this section](#onformatdebug-printing-field-values) for more details.

```cpp
virtual std::shared_ptr<ExampleNode> onClone() const override {
  return std::make_shared<ExampleTypeFunction>(
      std::optional<SourceRange>(sourceRange),
      clone(returnType), clone(argTypes));
}
```

Our clone method is getting a bit more complicated, but we have a helper function `clone(...)` to make things simpler. It can take in a single node or a vector of nodes and return a new instance of the same type with the same field values. See [this section](#onclone-returning-an-identical-copy) for more details.

```cpp
virtual bool onCompare(const ExampleNode& other) const override {
  return compare(
              returnType,
              static_cast<const ExampleTypeFunction&>(other).returnType) &&
          compare(
              argTypes,
              static_cast<const ExampleTypeFunction&>(other).argTypes);
}
```

The comparison method is also a lot more complicated. You'll notice the `static_cast` calls. It is safe to cast `other` to the current node type because the comparison already checks that the node kinds match before delegating to `onCompare`.

You'll notice another helper method `compare(...)`. Similar to `clone(...)` it can take in either two single nodes or two node vectors. It returns `true` if they match and `false` otherwise. See [this section](#oncompare-deep-comparison-for-syntax-trees) for more details.

## Node methods in detail

### `onAccept` - implementing the visitor pattern

This method is used part of the [visitor pattern](https://refactoring.guru/design-patterns/visitor). It is used when traversing the syntax tree and essentially provides a list of child nodes to the visitor.

The implementation of this method is simple: call `pass.visit(...)` for every child node or child node vector.

```cpp
virtual void onAccept(Pass<ExampleNode>& pass) const override {
  pass.visit(aSingleNode);
  pass.visit(aVectorOfNodes);

  // ...
}
```

### `onFormatDebug` - printing field values

This method is used to format the node for debugging. It's used when printing out the syntax tree for debugging purposes. This method is only used to print out the fields of the node.

```cpp
virtual void onFormatDebug(
    DebugFormatter<ExampleNodeKind>& formatter) const override {
  formatter.fieldLabel("anInteger");
  formatter.stream() << anInteger;

  formatter.fieldLabel("aString");
  formatter.string(aString);

  formatter.fieldLabel("anIntegerVector");
  formatter.vector(anIntegerVector, [](const int& value) {
    formatter.stream() << value;
  });

  formatter.fieldLabel("aSingleNode");
  formatter.node(aSingleNode);

  formatter.fieldLabel("aVectorOfNodes");
  formatter.nodeVector(aVectorOfNodes);

  // ...
}
```

Every field must have two function calls. One to `formatter.fieldLabel(...)` to print out the name of the field, and one to `formatter.*(...)` to print out the field value. These are the different helper methods that `formatter` provides:

- `formatter.string(...)` - prints out a string with quotes around it and escaped special characters.
- `formatter.vector(...)` - prints out a vector of values.
- `formatter.node(...)` - prints out a node or `null` if the `std::shared_ptr` is `nullptr`.
- `formatter.nodeVector(...)` - prints out a vector of nodes.
- `formatter.null()` - prints out `null` for use with pointers. This is not commonly used.

For other value types, like integers or booleans, you can simply do this:

```cpp
formatter.stream() << value;
```

Here is an example of printing out a vector of values with `formatter.vector(...)`:

```cpp
std::vector<int> values = {1, 2, 3};

formatter.vector(values, [](const int& value) {
  // This callback is called for every value in the vector.
  //
  // There is no need to specify any type of label - formatter.vector(...)
  // handles this for us
  formatter.stream() << value;
});
```

### `onClone` - returning an identical copy

One common operation that can be done on syntax trees is cloning them. This method must be overridden by every node type and simply returns a new instance of the same type with the same source range and same field values.

You can use the `clone` helper function which will clone a single node or a vector of nodes.

### `onCompare` - deep comparison for syntax trees

Another common operation for syntax trees is comparison. This method compares the field values of the current node `this` with another node `other`.

You can use the `compare` helper function which will compare two single nodes or two node vectors.

## Multiple node types with the exact same fields

This is a common use case for declaring node types for binary operators like `+` or `==`. They all have the same fields: a left hand side operand and a right hand side one. We do not have to duplicate these fields across every node type for a binary operator. We can declare a base class for binary operators and implement it multiple times.

We first declare our class:

```cpp
template <typename TSelf>
class ExampleValueBinary : public ExampleValue {
  // ...
};
```

We will need to pass in a `TSelf` type parameter so that when we clone the node, we can return an instance of the correct type. You'll see below.

We add in the fields:

```cpp hl_lines="4-10 14-15"
template <typename TSelf>
class ExampleValueBinary : public ExampleValue {
 public:
  ExampleValueBinary(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& sourceRange,
                     std::shared_ptr<ExampleValue>&& lhs,
                     std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValue(std::move(kind), std::move(sourceRange)),
        lhs(lhs),
        rhs(rhs) {}

  virtual ~ExampleValueBinary() = 0;

  std::shared_ptr<ExampleValue> lhs;
  std::shared_ptr<ExampleValue> rhs;
};

template <typename TSelf>
ExampleValueBinary<TSelf>::~ExampleValueBinary() {}
```

The `lhs` and `rhs` fields can now be used by any inheriting class. You'll notice we also made this abstract so that it cannot be declared on its own without a specific operator.

We can also override a few of the built in methods so that the code for them does not need to be duplicated:

```cpp hl_lines="18-43"
template <typename TSelf>
class ExampleValueBinary : public ExampleValue {
 public:
  ExampleValueBinary(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& sourceRange,
                     std::shared_ptr<ExampleValue>&& lhs,
                     std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValue(std::move(kind), std::move(sourceRange)),
        lhs(lhs),
        rhs(rhs) {}

  virtual ~ExampleValueBinary() = 0;

  std::shared_ptr<ExampleValue> lhs;
  std::shared_ptr<ExampleValue> rhs;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) const override {
    pass.visit(lhs);
    pass.visit(rhs);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("lhs");
    formatter.node(lhs);

    formatter.fieldLabel("rhs");
    formatter.node(rhs);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<TSelf>(
        std::optional<SourceRange>(sourceRange),
        clone(lhs), clone(rhs));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compare(
               lhs, static_cast<const ExampleValueBinary&>(other).lhs) &&
           compare(
               rhs, static_cast<const ExampleValueBinary&>(other).rhs);
  }
};

template <typename TSelf>
ExampleValueBinary<TSelf>::~ExampleValueBinary() {}
```

This is a lot of code, but now we can declare an addition operator by only doing this:

```cpp
class ExampleValueAdd : public ExampleValueBinary<ExampleValueAdd> {
 public:
  ExampleValueAdd(std::optional<SourceRange>&& sourceRange,
                  std::shared_ptr<ExampleValue>&& lhs,
                  std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueAdd, std::move(sourceRange),
                           std::move(lhs), std::move(rhs)) {}
};
```

And this can be applied to any binary operator.

!!! question "Why not use an enum instead of inheritance for binary operators?"

    This is a good question. There's pros and cons to either approach. I personally go with inheritance because I feel it makes the syntax tree more consistent and I can override custom methods differently. But then that can be achieved with enums as well.

    It's up to you - there's not an obvious right answer.

## Multiple node types with only some shared fields

There is also a common use case for sharing only some fields between node types for declarations. All declarations will have a name. There's no need to declare it in every declaration type when we can declare it once in the base class.

Let us extend our `ExampleDeclaration` class from [above](#category-base-classes) to include a `name` field:

```cpp
class ExampleDeclaration : public ExampleNode {
 public:
  ExampleDeclaration(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& sourceRange,
                     std::string&& name)
      : ExampleNode(std::move(kind), std::move(sourceRange)),
        name(std::move(name)) {}

  ~ExampleDeclaration() = 0;

  std::string name;
};

ExampleDeclaration::~ExampleDeclaration() {}
```

We can improve upon this though but partially implementing some of the overridable methods:

```cpp hl_lines="14-30"
class ExampleDeclaration : public ExampleNode {
 public:
  ExampleDeclaration(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& sourceRange,
                     std::string&& name)
      : ExampleNode(std::move(kind), std::move(sourceRange)),
        name(std::move(name)) {}

  ~ExampleDeclaration() = 0;

  std::string name;

 protected:
  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("name");
    formatter.string(name);

    onFormatDebugDeclaration(formatter);
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return name == static_cast<const ExampleDeclaration&>(other).name &&
           onCompareDeclaration(static_cast<const ExampleDeclaration&>(other));
  }

  virtual void onFormatDebugDeclaration(
      DebugFormatter<ExampleNodeKind>& formatter) const = 0;

  virtual bool onCompareDeclaration(const ExampleNode& other) const = 0;
};
```

We can use `onFormatDebug` to always print out the `name` field first and `onCompare` to always compare the `name` field first.

We declare new abstract methods `onFormatDebugDeclaration` and `onCompareDeclaration` to make it explicit that any inheriting classes can't override the behavior of the `name` field.

## Full syntax tree

See the full example in [`ExampleLanguage.cpp`](https://github.com/sophie-lund/forge/blob/main/test/ExampleLanguage.cpp). This will implement every node type that we've discussed above as well as all of the ones defined in the [`ExampleNodeKind`](#node-kind-enum) enum.
