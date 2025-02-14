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

#include <gtest/gtest.h>

#include <forge/syntax_tree/domain/base_node.hpp>
#include <forge/syntax_tree/domain/gtest_node_auto_assert.hpp>
#include <forge/syntax_tree/operations/cloners.hpp>
#include <forge/syntax_tree/operations/comparators.hpp>
#include <forge/syntax_tree/operations/validators.hpp>
#include <forge/syntax_tree/scope/symbol_resolution_handler.hpp>

using namespace forge;

// -----------------------------------------------------------------------------
// SYNTAX TREE
// -----------------------------------------------------------------------------

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

std::ostream& operator<<(std::ostream& stream, ExampleNodeKind kind) {
  switch (kind) {
    case ExampleNodeKind::TypeBool:
      stream << "TypeBool";
      break;
    case ExampleNodeKind::TypeInt:
      stream << "TypeInt";
      break;
    case ExampleNodeKind::TypeFunction:
      stream << "TypeFunction";
      break;
    case ExampleNodeKind::ValueBool:
      stream << "ValueBool";
      break;
    case ExampleNodeKind::ValueInt:
      stream << "ValueInt";
      break;
    case ExampleNodeKind::ValueSymbol:
      stream << "ValueSymbol";
      break;
    case ExampleNodeKind::ValueAdd:
      stream << "ValueAdd";
      break;
    case ExampleNodeKind::ValueNeg:
      stream << "ValueNeg";
      break;
    case ExampleNodeKind::ValueLT:
      stream << "ValueLT";
      break;
    case ExampleNodeKind::ValueEQ:
      stream << "ValueEQ";
      break;
    case ExampleNodeKind::ValueCall:
      stream << "ValueCall";
      break;
    case ExampleNodeKind::StatementIf:
      stream << "StatementIf";
      break;
    case ExampleNodeKind::StatementWhile:
      stream << "StatementWhile";
      break;
    case ExampleNodeKind::StatementContinue:
      stream << "StatementContinue";
      break;
    case ExampleNodeKind::StatementBreak:
      stream << "StatementBreak";
      break;
    case ExampleNodeKind::StatementReturn:
      stream << "StatementReturn";
      break;
    case ExampleNodeKind::StatementBlock:
      stream << "StatementBlock";
      break;
    case ExampleNodeKind::DeclarationVariable:
      stream << "DeclarationVariable";
      break;
    case ExampleNodeKind::DeclarationFunction:
      stream << "DeclarationFunction";
      break;
    case ExampleNodeKind::TranslationUnit:
      stream << "TranslationUnit";
      break;
  }

  return stream;
}

class ExampleNode : public Node<ExampleNode, ExampleNodeKind> {
 public:
  ExampleNode(ExampleNodeKind&& kind, std::optional<SourceRange>&& sourceRange)
      : Node(std::move(kind), std::move(sourceRange)) {}

  virtual ~ExampleNode() = 0;
};

ExampleNode::~ExampleNode() {}

class ExampleType : public ExampleNode {
 public:
  ExampleType(ExampleNodeKind&& kind, std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleType() = 0;
};

ExampleType::~ExampleType() {}

class ExampleTypeBool : public ExampleType {
 public:
  ExampleTypeBool(std::optional<SourceRange>&& sourceRange)
      : ExampleType(ExampleNodeKind::TypeBool, std::move(sourceRange)) {}

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleTypeBool>(
        std::optional<SourceRange>(sourceRange));
  }

  virtual bool onCompare(const ExampleNode&) const override { return true; }
};

class ExampleTypeInt : public ExampleType {
 public:
  ExampleTypeInt(std::optional<SourceRange>&& sourceRange)
      : ExampleType(ExampleNodeKind::TypeInt, std::move(sourceRange)) {}

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleTypeInt>(
        std::optional<SourceRange>(sourceRange));
  }

  virtual bool onCompare(const ExampleNode&) const override { return true; }
};

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
  virtual void onAccept(Pass<ExampleNode>& pass) override {
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
        std::optional<SourceRange>(sourceRange), cloneNode(returnType),
        cloneNodeVector(argTypes));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(
               returnType,
               static_cast<const ExampleTypeFunction&>(other).returnType) &&
           compareNodeVectors(
               argTypes,
               static_cast<const ExampleTypeFunction&>(other).argTypes);
  }
};

class ExampleValue : public ExampleNode {
 public:
  ExampleValue(ExampleNodeKind&& kind, std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleValue() = 0;
};

ExampleValue::~ExampleValue() {}

class ExampleValueBool : public ExampleValue {
 public:
  ExampleValueBool(std::optional<SourceRange>&& sourceRange, bool value)
      : ExampleValue(ExampleNodeKind::ValueBool, std::move(sourceRange)),
        value(value) {}

  bool value;

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("value");
    formatter.stream() << (value ? "true" : "false");
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleValueBool>(
        std::optional<SourceRange>(sourceRange), value);
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return value == static_cast<const ExampleValueBool&>(other).value;
  }
};

class ExampleValueInt : public ExampleValue {
 public:
  ExampleValueInt(std::optional<SourceRange>&& sourceRange, int32_t value)
      : ExampleValue(ExampleNodeKind::ValueInt, std::move(sourceRange)),
        value(value) {}

  int32_t value;

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("value");
    formatter.stream() << value;
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleValueInt>(
        std::optional<SourceRange>(sourceRange), value);
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return value == static_cast<const ExampleValueInt&>(other).value;
  }
};

class ExampleValueSymbol : public ExampleValue {
 public:
  ExampleValueSymbol(std::optional<SourceRange>&& sourceRange,
                     std::string&& name)
      : ExampleValue(ExampleNodeKind::ValueSymbol, std::move(sourceRange)),
        name(name) {}

  std::string name;

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("name");
    formatter.string(name);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleValueSymbol>(
        std::optional<SourceRange>(sourceRange), std::string(name));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return name == static_cast<const ExampleValueSymbol&>(other).name;
  }
};

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
  virtual void onAccept(Pass<ExampleNode>& pass) override {
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
    return std::make_shared<TSelf>(std::optional<SourceRange>(sourceRange),
                                   cloneNode(lhs), cloneNode(rhs));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(lhs,
                        static_cast<const ExampleValueBinary&>(other).lhs) &&
           compareNodes(rhs, static_cast<const ExampleValueBinary&>(other).rhs);
  }
};

template <typename TSelf>
ExampleValueBinary<TSelf>::~ExampleValueBinary() {}

class ExampleValueAdd : public ExampleValueBinary<ExampleValueAdd> {
 public:
  ExampleValueAdd(std::optional<SourceRange>&& sourceRange,
                  std::shared_ptr<ExampleValue>&& lhs,
                  std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueAdd, std::move(sourceRange),
                           std::move(lhs), std::move(rhs)) {}
};

class ExampleValueLT : public ExampleValueBinary<ExampleValueLT> {
 public:
  ExampleValueLT(std::optional<SourceRange>&& sourceRange,
                 std::shared_ptr<ExampleValue>&& lhs,
                 std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueLT, std::move(sourceRange),
                           std::move(lhs), std::move(rhs)) {}
};

class ExampleValueEQ : public ExampleValueBinary<ExampleValueEQ> {
 public:
  ExampleValueEQ(std::optional<SourceRange>&& sourceRange,
                 std::shared_ptr<ExampleValue>&& lhs,
                 std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueEQ, std::move(sourceRange),
                           std::move(lhs), std::move(rhs)) {}
};

template <typename TSelf>
class ExampleValueUnary : public ExampleValue {
 public:
  ExampleValueUnary(ExampleNodeKind&& kind,
                    std::optional<SourceRange>&& sourceRange,
                    std::shared_ptr<ExampleValue>&& operand)
      : ExampleValue(std::move(kind), std::move(sourceRange)),
        operand(operand) {}

  virtual ~ExampleValueUnary() = 0;

  std::shared_ptr<ExampleValue> operand;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(operand);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("operand");
    formatter.node(operand);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<TSelf>(std::optional<SourceRange>(sourceRange),
                                   cloneNode(operand));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(operand,
                        static_cast<const ExampleValueUnary&>(other).operand);
  }
};

template <typename TSelf>
ExampleValueUnary<TSelf>::~ExampleValueUnary() {}

class ExampleValueNeg : public ExampleValueUnary<ExampleValueNeg> {
 public:
  ExampleValueNeg(std::optional<SourceRange>&& sourceRange,
                  std::shared_ptr<ExampleValue>&& operand)
      : ExampleValueUnary(ExampleNodeKind::ValueNeg, std::move(sourceRange),
                          std::move(operand)) {}
};

class ExampleValueCall : public ExampleValue {
 public:
  ExampleValueCall(std::optional<SourceRange>&& sourceRange,
                   std::shared_ptr<ExampleValue>&& callee,
                   std::vector<std::shared_ptr<ExampleValue>>&& args)
      : ExampleValue(ExampleNodeKind::ValueCall, std::move(sourceRange)),
        callee(std::move(callee)),
        args(std::move(args)) {}

  std::shared_ptr<ExampleValue> callee;
  std::vector<std::shared_ptr<ExampleValue>> args;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(callee);
    pass.visit(args);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("callee");
    formatter.node(callee);

    formatter.fieldLabel("args");
    formatter.nodeVector(args);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleValueCall>(
        std::optional<SourceRange>(sourceRange), cloneNode(callee),
        cloneNodeVector(args));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(callee,
                        static_cast<const ExampleValueCall&>(other).callee) &&
           compareNodeVectors(args,
                              static_cast<const ExampleValueCall&>(other).args);
  }
};

class ExampleStatement : public ExampleNode {
 public:
  ExampleStatement(ExampleNodeKind&& kind,
                   std::optional<SourceRange>&& sourceRange)
      : ExampleNode(std::move(kind), std::move(sourceRange)) {}

  ~ExampleStatement() = 0;
};

ExampleStatement::~ExampleStatement() {}

class ExampleStatementIf : public ExampleStatement {
 public:
  ExampleStatementIf(std::optional<SourceRange>&& sourceRange,
                     std::shared_ptr<ExampleValue>&& condition,
                     std::shared_ptr<ExampleStatement>&& then,
                     std::shared_ptr<ExampleStatement>&& else_)
      : ExampleStatement(ExampleNodeKind::StatementIf, std::move(sourceRange)),
        condition(std::move(condition)),
        then(std::move(then)),
        else_(std::move(else_)) {}

  std::shared_ptr<ExampleValue> condition;
  std::shared_ptr<ExampleStatement> then;
  std::shared_ptr<ExampleStatement> else_;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(condition);
    pass.visit(then);
    pass.visit(else_);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("condition");
    formatter.node(condition);

    formatter.fieldLabel("then");
    formatter.node(then);

    formatter.fieldLabel("else");
    formatter.node(else_);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleStatementIf>(
        std::optional<SourceRange>(sourceRange), cloneNode(condition),
        cloneNode(then), cloneNode(else_));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(
               condition,
               static_cast<const ExampleStatementIf&>(other).condition) &&
           compareNodes(then,
                        static_cast<const ExampleStatementIf&>(other).then) &&
           compareNodes(else_,
                        static_cast<const ExampleStatementIf&>(other).else_);
  }
};

class ExampleStatementWhile : public ExampleStatement {
 public:
  ExampleStatementWhile(std::optional<SourceRange>&& sourceRange,
                        std::shared_ptr<ExampleValue>&& condition,
                        std::shared_ptr<ExampleStatement>&& body)
      : ExampleStatement(ExampleNodeKind::StatementWhile,
                         std::move(sourceRange)),
        condition(std::move(condition)),
        body(std::move(body)) {}

  std::shared_ptr<ExampleValue> condition;
  std::shared_ptr<ExampleStatement> body;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(condition);
    pass.visit(body);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("condition");
    formatter.node(condition);

    formatter.fieldLabel("body");
    formatter.node(body);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleStatementWhile>(
        std::optional<SourceRange>(sourceRange), cloneNode(condition),
        cloneNode(body));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(
               condition,
               static_cast<const ExampleStatementWhile&>(other).condition) &&
           compareNodes(body,
                        static_cast<const ExampleStatementWhile&>(other).body);
  }
};

class ExampleStatementContinue : public ExampleStatement {
 public:
  ExampleStatementContinue(std::optional<SourceRange>&& sourceRange)
      : ExampleStatement(ExampleNodeKind::StatementContinue,
                         std::move(sourceRange)) {}

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleStatementContinue>(
        std::optional<SourceRange>(sourceRange));
  }

  virtual bool onCompare(const ExampleNode&) const override { return true; }
};

class ExampleStatementBreak : public ExampleStatement {
 public:
  ExampleStatementBreak(std::optional<SourceRange>&& sourceRange)
      : ExampleStatement(ExampleNodeKind::StatementBreak,
                         std::move(sourceRange)) {}

 protected:
  virtual void onAccept(Pass<ExampleNode>&) override {}

  virtual void onFormatDebug(DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleStatementBreak>(
        std::optional<SourceRange>(sourceRange));
  }

  virtual bool onCompare(const ExampleNode&) const override { return true; }
};

class ExampleStatementReturn : public ExampleStatement {
 public:
  ExampleStatementReturn(std::optional<SourceRange>&& sourceRange,
                         std::shared_ptr<ExampleValue>&& value)
      : ExampleStatement(ExampleNodeKind::StatementReturn,
                         std::move(sourceRange)),
        value(std::move(value)) {}

  std::shared_ptr<ExampleValue> value;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override { pass.visit(value); }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("value");
    formatter.node(value);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleStatementReturn>(
        std::optional<SourceRange>(sourceRange), cloneNode(value));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodes(
        value, static_cast<const ExampleStatementReturn&>(other).value);
  }
};

class ExampleStatementBlock : public ExampleStatement {
 public:
  ExampleStatementBlock(
      std::optional<SourceRange>&& sourceRange,
      std::vector<std::shared_ptr<ExampleStatement>>&& statements)
      : ExampleStatement(ExampleNodeKind::StatementBlock,
                         std::move(sourceRange)),
        statements(std::move(statements)) {}

  std::vector<std::shared_ptr<ExampleStatement>> statements;
  std::shared_ptr<Scope<ExampleNode>> scope;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(statements);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("statements");
    formatter.nodeVector(statements);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleStatementBlock>(
        std::optional<SourceRange>(sourceRange), cloneNodeVector(statements));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodeVectors(
        statements,
        static_cast<const ExampleStatementBlock&>(other).statements);
  }
};

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

ExampleDeclaration::~ExampleDeclaration() {}

class ExampleDeclarationVariable : public ExampleDeclaration {
 public:
  ExampleDeclarationVariable(std::optional<SourceRange>&& sourceRange,
                             std::string&& name,
                             std::shared_ptr<ExampleType>&& type,
                             std::shared_ptr<ExampleValue>&& value = nullptr)
      : ExampleDeclaration(ExampleNodeKind::DeclarationVariable,
                           std::move(sourceRange), std::move(name)),
        type(std::move(type)),
        value(std::move(value)) {}

  std::shared_ptr<ExampleType> type;
  std::shared_ptr<ExampleValue> value;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(type);
    pass.visit(value);
  }

  virtual void onFormatDebugDeclaration(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("type");
    formatter.node(type);

    formatter.fieldLabel("value");
    formatter.node(value);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleDeclarationVariable>(
        std::optional<SourceRange>(sourceRange), std::string(name),
        cloneNode(type), cloneNode(value));
  }

  virtual bool onCompareDeclaration(const ExampleNode& other) const override {
    return compareNodes(
               type,
               static_cast<const ExampleDeclarationVariable&>(other).type) &&
           compareNodes(
               value,
               static_cast<const ExampleDeclarationVariable&>(other).value);
  }
};

class ExampleDeclarationFunction : public ExampleDeclaration {
 public:
  ExampleDeclarationFunction(
      std::optional<SourceRange>&& sourceRange, std::string&& name,
      std::shared_ptr<ExampleType>&& returnType,
      std::vector<std::shared_ptr<ExampleDeclarationVariable>>&& args,
      std::shared_ptr<ExampleStatementBlock>&& body = nullptr)
      : ExampleDeclaration(ExampleNodeKind::DeclarationFunction,
                           std::move(sourceRange), std::move(name)),
        returnType(std::move(returnType)),
        args(std::move(args)),
        body(std::move(body)) {}

  std::shared_ptr<ExampleType> returnType;
  std::vector<std::shared_ptr<ExampleDeclarationVariable>> args;
  std::shared_ptr<ExampleStatementBlock> body;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(returnType);
    pass.visit(args);
    pass.visit(body);
  }

  virtual void onFormatDebugDeclaration(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("returnType");
    formatter.node(returnType);

    formatter.fieldLabel("args");
    formatter.nodeVector(args);

    formatter.fieldLabel("body");
    formatter.node(body);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleDeclarationFunction>(
        std::optional<SourceRange>(sourceRange), std::string(name),
        cloneNode(returnType), cloneNodeVector(args), cloneNode(body));
  }

  virtual bool onCompareDeclaration(const ExampleNode& other) const override {
    return compareNodes(returnType,
                        static_cast<const ExampleDeclarationFunction&>(other)
                            .returnType) &&
           compareNodeVectors(
               args,
               static_cast<const ExampleDeclarationFunction&>(other).args) &&
           compareNodes(
               body,
               static_cast<const ExampleDeclarationFunction&>(other).body);
  }
};

class ExampleTranslationUnit : public ExampleNode {
 public:
  ExampleTranslationUnit(
      std::optional<SourceRange>&& sourceRange,
      std::vector<std::shared_ptr<ExampleDeclaration>>&& declarations)
      : ExampleNode(ExampleNodeKind::TranslationUnit, std::move(sourceRange)),
        declarations(std::move(declarations)) {}

  std::vector<std::shared_ptr<ExampleDeclaration>> declarations;
  std::shared_ptr<Scope<ExampleNode>> scope;

 protected:
  virtual void onAccept(Pass<ExampleNode>& pass) override {
    pass.visit(declarations);
  }

  virtual void onFormatDebug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.fieldLabel("declarations");
    formatter.nodeVector(declarations);
  }

  virtual std::shared_ptr<ExampleNode> onClone() const override {
    return std::make_shared<ExampleTranslationUnit>(
        std::optional<SourceRange>(sourceRange), cloneNodeVector(declarations));
  }

  virtual bool onCompare(const ExampleNode& other) const override {
    return compareNodeVectors(
        declarations,
        static_cast<const ExampleTranslationUnit&>(other).declarations);
  }
};

// -----------------------------------------------------------------------------
// WELL FORMED VALIDATION HANDLER
// -----------------------------------------------------------------------------

class WellFormedValidationHandler : public Handler<ExampleNode> {
 protected:
  virtual typename Handler<ExampleNode>::Output onEnter(
      typename Handler<ExampleNode>::Input&) override {
    return typename Handler<ExampleNode>::Output();
  }

  virtual typename Handler<ExampleNode>::Output onLeave(
      typename Handler<ExampleNode>::Input& input) override {
    switch (input.node()->kind) {
        // -----------------------------------------------------------------

      case ExampleNodeKind::TypeBool:
      case ExampleNodeKind::TypeInt:
        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::TypeFunction:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "returnType",
                static_cast<const ExampleTypeFunction&>(*input.node())
                    .returnType)) {
          break;
        }

        if (static_cast<const ExampleTypeFunction&>(*input.node())
                .returnType->kind == ExampleNodeKind::TypeFunction) {
          input.messageContext().emit(
              static_cast<const ExampleTypeFunction&>(*input.node())
                  .returnType->sourceRange,
              SEVERITY_ERROR, "???", "functions cannot return other functions");
        }

        if (!validateChildVectorNonNull(
                input.messageContext(), *input.node(), "argTypes",
                static_cast<const ExampleTypeFunction&>(*input.node())
                    .argTypes)) {
          break;
        }

        for (const auto& argType :
             static_cast<const ExampleTypeFunction&>(*input.node()).argTypes) {
          if (argType->kind == ExampleNodeKind::TypeFunction) {
            input.messageContext().emit(argType->sourceRange, SEVERITY_ERROR,
                                        "???", "functions cannot be arguments");
          }
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueBool:
      case ExampleNodeKind::ValueInt:
        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueSymbol:
        if (!validateStringNonEmpty(
                input.messageContext(), *input.node(), "name",
                static_cast<const ExampleValueSymbol&>(*input.node()).name)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueAdd:
      case ExampleNodeKind::ValueLT:
      case ExampleNodeKind::ValueEQ:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "lhs",
                static_cast<const ExampleValueBinary<ExampleValue>&>(
                    *input.node())
                    .lhs)) {
          break;
        }

        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "rhs",
                static_cast<const ExampleValueBinary<ExampleValue>&>(
                    *input.node())
                    .rhs)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueNeg:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "operand",
                static_cast<const ExampleValueUnary<ExampleValue>&>(
                    *input.node())
                    .operand)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueCall:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "callee",
                static_cast<const ExampleValueCall&>(*input.node()).callee)) {
          break;
        }

        if (!validateChildVectorNonNull(
                input.messageContext(), *input.node(), "args",
                static_cast<const ExampleValueCall&>(*input.node()).args)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementIf:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "condition",
                static_cast<const ExampleStatementIf&>(*input.node())
                    .condition)) {
          break;
        }

        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "then",
                static_cast<const ExampleStatementIf&>(*input.node()).then)) {
          break;
        }

        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "else_",
                static_cast<const ExampleStatementIf&>(*input.node()).else_)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementWhile:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "condition",
                static_cast<const ExampleStatementWhile&>(*input.node())
                    .condition)) {
          break;
        }

        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "body",
                static_cast<const ExampleStatementWhile&>(*input.node())
                    .body)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementContinue:
      case ExampleNodeKind::StatementBreak:
        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementReturn:
        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "value",
                static_cast<const ExampleStatementReturn&>(*input.node())
                    .value)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementBlock:
        if (!validateChildVectorNonNull(
                input.messageContext(), *input.node(), "statements",
                static_cast<const ExampleStatementBlock&>(*input.node())
                    .statements)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::DeclarationVariable:
        if (!onLeaveDeclaration(input.messageContext(), input.stack(),
                                static_cast<const ExampleDeclarationVariable&>(
                                    *input.node()))) {
          break;
        }

        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "type",
                static_cast<const ExampleDeclarationVariable&>(*input.node())
                    .type)) {
          break;
        }

        if (static_cast<const ExampleDeclarationVariable&>(*input.node())
                .type->kind == ExampleNodeKind::TypeFunction) {
          input.messageContext().emit(
              static_cast<const ExampleDeclarationVariable&>(*input.node())
                  .type->sourceRange,
              SEVERITY_ERROR, "???", "variables cannot have function types");
        }

        // If this is a function argument declaration...
        if (!input.stack().empty() &&
            input.stack().back().get().kind ==
                ExampleNodeKind::DeclarationFunction) {
          if (!validateChildNull(
                  input.messageContext(), *input.node(), "value",
                  static_cast<const ExampleDeclarationVariable&>(*input.node())
                      .value)) {
            break;
          }
        } else {
          if (!validateChildNonNull(
                  input.messageContext(), *input.node(), "value",
                  static_cast<const ExampleDeclarationVariable&>(*input.node())
                      .value)) {
            break;
          }
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::DeclarationFunction:
        if (!onLeaveDeclaration(input.messageContext(), input.stack(),
                                static_cast<const ExampleDeclarationFunction&>(
                                    *input.node()))) {
          break;
        }

        if (!validateChildNonNull(
                input.messageContext(), *input.node(), "returnType",
                static_cast<const ExampleDeclarationFunction&>(*input.node())
                    .returnType)) {
          break;
        }

        if (static_cast<const ExampleDeclarationFunction&>(*input.node())
                .returnType->kind == ExampleNodeKind::TypeFunction) {
          input.messageContext().emit(
              static_cast<const ExampleDeclarationFunction&>(*input.node())
                  .returnType->sourceRange,
              SEVERITY_ERROR, "???", "functions cannot return function types");
        }

        if (!validateChildVectorNonNull(
                input.messageContext(), *input.node(), "args",
                static_cast<const ExampleDeclarationFunction&>(*input.node())
                    .args)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::TranslationUnit:
        if (!validateChildVectorNonNull(
                input.messageContext(), *input.node(), "declarations",
                static_cast<const ExampleTranslationUnit&>(*input.node())
                    .declarations)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      default:
        input.messageContext().emit(input.node()->sourceRange, SEVERITY_ERROR,
                                    "???", "unknown node kind");
        break;

        // -----------------------------------------------------------------
    }

    return typename Handler<ExampleNode>::Output();
  }

  bool onLeaveDeclaration(
      MessageContext& messageContext,
      const std::vector<std::reference_wrapper<const ExampleNode>>&,
      const ExampleDeclaration& node) {
    return validateStringNonEmpty(
        messageContext, node, "name",
        static_cast<const ExampleDeclarationVariable&>(node).name);
  }
};

// -----------------------------------------------------------------------------
// TEST HELPERS
// -----------------------------------------------------------------------------

std::shared_ptr<ExampleTranslationUnit> makeSimpleTree() {
  // Pseudocode:
  //
  //   int x = 42;
  //   bool y = true;
  //
  //   int add(int x, int y) {
  //     return x + y;
  //   }
  //
  //   int abs(int x) {
  //     if (x < 0) {
  //       return -x;
  //     } else {
  //       return x;
  //     }
  //   }

  // clang-format off
  auto translationUnit = std::make_shared<ExampleTranslationUnit>(
    std::nullopt,
    std::vector<std::shared_ptr<ExampleDeclaration>>({
      // int x = 42;
      std::make_shared<ExampleDeclarationVariable>(
        std::nullopt,
        "x",
        std::make_shared<ExampleTypeInt>(std::nullopt),
        std::make_shared<ExampleValueInt>(std::nullopt, 42)
      ),

      // bool y = true;
      std::make_shared<ExampleDeclarationVariable>(
        std::nullopt,
        "y",
        std::make_shared<ExampleTypeBool>(std::nullopt),
        std::make_shared<ExampleValueBool>(std::nullopt, true)
      ),

      // int add(int x, int y) { ... }
      std::make_shared<ExampleDeclarationFunction>(
        std::nullopt,
        "add",
        std::make_shared<ExampleTypeInt>(std::nullopt),
        std::vector<std::shared_ptr<ExampleDeclarationVariable>>({
          // int x
          std::make_shared<ExampleDeclarationVariable>(
            std::nullopt,
            "x",
            std::make_shared<ExampleTypeInt>(std::nullopt)
          ),

          // int y
          std::make_shared<ExampleDeclarationVariable>(
            std::nullopt,
            "y",
            std::make_shared<ExampleTypeInt>(std::nullopt)
          )
        }),
        std::make_shared<ExampleStatementBlock>(
          std::nullopt,
          std::vector<std::shared_ptr<ExampleStatement>>({
            // return x + y;
            std::make_shared<ExampleStatementReturn>(
              std::nullopt,
              std::make_shared<ExampleValueAdd>(
                std::nullopt,
                std::make_shared<ExampleValueSymbol>(
                  std::nullopt,
                  "x"
                ),
                std::make_shared<ExampleValueSymbol>(
                  std::nullopt,
                  "y"
                )
              )
            )
          })
        )
      ),

      // int abs(int x) { ... }
      std::make_shared<ExampleDeclarationFunction>(
        std::nullopt,
        "abs",
        std::make_shared<ExampleTypeInt>(std::nullopt),
        std::vector<std::shared_ptr<ExampleDeclarationVariable>>({
          // int x
          std::make_shared<ExampleDeclarationVariable>(
            std::nullopt,
            "x",
            std::make_shared<ExampleTypeInt>(std::nullopt)
          )
        }),
        std::make_shared<ExampleStatementBlock>(
          std::nullopt,
          std::vector<std::shared_ptr<ExampleStatement>>({
            // if (x < 0) { ... } else { ... }
            std::make_shared<ExampleStatementIf>(
              std::nullopt,
              std::make_shared<ExampleValueLT>(
                std::nullopt,
                std::make_shared<ExampleValueSymbol>(
                  std::nullopt,
                  "x"
                ),
                std::make_shared<ExampleValueInt>(
                  std::nullopt,
                  0
                )
              ),
              std::make_shared<ExampleStatementBlock>(
                std::nullopt,
                std::vector<std::shared_ptr<ExampleStatement>>({
                  // return -x;
                  std::make_shared<ExampleStatementReturn>(
                    std::nullopt,
                    std::make_shared<ExampleValueNeg>(
                      std::nullopt,
                      std::make_shared<ExampleValueSymbol>(
                        std::nullopt,
                        "x"
                      )
                    )
                  )
                })
              ),
              std::make_shared<ExampleStatementBlock>(
                std::nullopt,
                std::vector<std::shared_ptr<ExampleStatement>>({
                  // return x;
                  std::make_shared<ExampleStatementReturn>(
                    std::nullopt,
                    std::make_shared<ExampleValueSymbol>(
                      std::nullopt,
                      "x"
                    )
                  )
                })
              )
            )
          })
        )
      )
    })
  );
  // clang-format on

  return translationUnit;
}

// -----------------------------------------------------------------------------
// TESTS
// -----------------------------------------------------------------------------

TEST(ExampleLanguage, NodeAuto) {
  std::stringstream debugFormatterStream;
  DebugFormatter<ExampleNodeKind> debugFormatter(debugFormatterStream);

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TypeBool, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleTypeBool>(std::nullopt))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TypeInt, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleTypeInt>(std::nullopt))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TypeFunction, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleTypeFunction>(
          std::nullopt, std::make_shared<ExampleTypeInt>(std::nullopt),
          std::vector<std::shared_ptr<ExampleType>>{
              std::make_shared<ExampleTypeBool>(std::nullopt),
              std::make_shared<ExampleTypeInt>(std::nullopt)}))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueBool, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueBool>(std::nullopt, true))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueInt, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueInt>(std::nullopt, 5))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueSymbol, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueSymbol>(std::nullopt, "x"))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueAdd, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueAdd>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueNeg, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueNeg>(
          std::nullopt,
          std::make_shared<ExampleValueSymbol>(std::nullopt, "x")))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueLT, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueLT>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueEQ, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueEQ>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueCall, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleValueCall>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "f"),
          std::vector<std::shared_ptr<ExampleValue>>(
              {std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
               std::make_shared<ExampleValueSymbol>(std::nullopt, "y")})))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementIf, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleStatementIf>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleStatementContinue>(std::nullopt),
          std::make_shared<ExampleStatementBreak>(std::nullopt)))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementWhile, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleStatementWhile>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleStatementContinue>(std::nullopt)))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementContinue, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleStatementContinue>(std::nullopt))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementBreak, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleStatementBreak>(std::nullopt))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementReturn, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleStatementReturn>(
          std::nullopt,
          std::make_shared<ExampleValueSymbol>(std::nullopt, "x")))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementBlock, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleStatementBlock>(
          std::nullopt,
          std::vector<std::shared_ptr<ExampleStatement>>(
              {std::make_shared<ExampleStatementContinue>(std::nullopt),
               std::make_shared<ExampleStatementBreak>(std::nullopt)})))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::DeclarationVariable, debugFormatter,
      debugFormatterStream,
      std::make_shared<ExampleDeclarationVariable>(
          std::nullopt, "x", std::make_shared<ExampleTypeInt>(std::nullopt),
          std::make_shared<ExampleValueInt>(std::nullopt, 42)))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::DeclarationFunction, debugFormatter,
      debugFormatterStream,
      std::make_shared<ExampleDeclarationFunction>(
          std::nullopt, "f", std::make_shared<ExampleTypeInt>(std::nullopt),
          std::vector<std::shared_ptr<ExampleDeclarationVariable>>(
              {std::make_shared<ExampleDeclarationVariable>(
                   std::nullopt, "x",
                   std::make_shared<ExampleTypeInt>(std::nullopt), nullptr),
               std::make_shared<ExampleDeclarationVariable>(
                   std::nullopt, "y",
                   std::make_shared<ExampleTypeInt>(std::nullopt), nullptr)}),
          std::make_shared<ExampleStatementBlock>(
              std::nullopt,
              std::vector<std::shared_ptr<ExampleStatement>>())))));

  EXPECT_TRUE((nodeAutoAssert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TranslationUnit, debugFormatter, debugFormatterStream,
      std::make_shared<ExampleTranslationUnit>(
          std::nullopt,
          std::vector<std::shared_ptr<ExampleDeclaration>>(
              {std::make_shared<ExampleDeclarationVariable>(
                   std::nullopt, "x",
                   std::make_shared<ExampleTypeInt>(std::nullopt),
                   std::make_shared<ExampleValueInt>(std::nullopt, 42)),
               std::make_shared<ExampleDeclarationVariable>(
                   std::nullopt, "y",
                   std::make_shared<ExampleTypeInt>(std::nullopt),
                   std::make_shared<ExampleValueInt>(std::nullopt, 43))})))));
}

TEST(ExampleLanguage, Construction) { makeSimpleTree(); }

TEST(ExampleLanguage, DebugFormatting) {
  std::stringstream stream;
  auto tree = makeSimpleTree();
  DebugFormatter<ExampleNodeKind> debugFormatter(stream);

  debugFormatter.node(tree);

  // clang-format off
  ASSERT_EQ(
    stream.str(),
    "[TranslationUnit]\n"
    "  declarations = \n"
    "    [0] = [DeclarationVariable]\n"
    "      name = \"x\"\n"
    "      type = [TypeInt]\n"
    "      value = [ValueInt]\n"
    "        value = 42\n"
    "    [1] = [DeclarationVariable]\n"
    "      name = \"y\"\n"
    "      type = [TypeBool]\n"
    "      value = [ValueBool]\n"
    "        value = true\n"
    "    [2] = [DeclarationFunction]\n"
    "      name = \"add\"\n"
    "      returnType = [TypeInt]\n"
    "      args = \n"
    "        [0] = [DeclarationVariable]\n"
    "          name = \"x\"\n"
    "          type = [TypeInt]\n"
    "          value = null\n"
    "        [1] = [DeclarationVariable]\n"
    "          name = \"y\"\n"
    "          type = [TypeInt]\n"
    "          value = null\n"
    "      body = [StatementBlock]\n"
    "        statements = \n"
    "          [0] = [StatementReturn]\n"
    "            value = [ValueAdd]\n"
    "              lhs = [ValueSymbol]\n"
    "                name = \"x\"\n"
    "              rhs = [ValueSymbol]\n"
    "                name = \"y\"\n"
    "    [3] = [DeclarationFunction]\n"
    "      name = \"abs\"\n"
    "      returnType = [TypeInt]\n"
    "      args = \n"
    "        [0] = [DeclarationVariable]\n"
    "          name = \"x\"\n"
    "          type = [TypeInt]\n"
    "          value = null\n"
    "      body = [StatementBlock]\n"
    "        statements = \n"
    "          [0] = [StatementIf]\n"
    "            condition = [ValueLT]\n"
    "              lhs = [ValueSymbol]\n"
    "                name = \"x\"\n"
    "              rhs = [ValueInt]\n"
    "                value = 0\n"
    "            then = [StatementBlock]\n"
    "              statements = \n"
    "                [0] = [StatementReturn]\n"
    "                  value = [ValueNeg]\n"
    "                    operand = [ValueSymbol]\n"
    "                      name = \"x\"\n"
    "            else = [StatementBlock]\n"
    "              statements = \n"
    "                [0] = [StatementReturn]\n"
    "                  value = [ValueSymbol]\n"
    "                    name = \"x\""
  );
  // clang-format on
}

TEST(ExampleLanguage, Comparison) {
  auto lhs = makeSimpleTree();
  auto rhs = makeSimpleTree();

  ASSERT_TRUE(compareNodes(lhs, rhs));

  rhs->declarations[0]->name = "z";

  ASSERT_FALSE(compareNodes(lhs, rhs));
}

TEST(ExampleLanguage, Clone) {
  auto original = makeSimpleTree();
  auto cloned =
      std::static_pointer_cast<ExampleTranslationUnit>(cloneNode(original));

  ASSERT_TRUE(compareNodes(original, cloned));

  cloned->declarations[0]->name = "z";

  ASSERT_FALSE(compareNodes(original, cloned));
}

TEST(ExampleLanguage, WellFormedValidationPass) {
  auto tree = makeSimpleTree();

  MessageContext messageContext;
  Pass<ExampleNode> pass(messageContext);
  pass.addHandler(std::make_unique<WellFormedValidationHandler>());

  pass.visit(tree);

  ASSERT_EQ(messageContext.messages().size(), 0);

  tree->declarations[0]->name = "";

  pass.visit(tree);

  ASSERT_GT(messageContext.messages().size(), 0);
}

TEST(ExampleLanguage, SymbolResolution) {
  auto tree = makeSimpleTree();

  MessageContext messageContext;
  Pass<ExampleNode> pass(messageContext);

  pass.addHandler(std::make_unique<SymbolResolutionHandler<ExampleNode>>());

  pass.visit(tree);

  ASSERT_EQ(messageContext.messages().size(), 0);

  ASSERT_TRUE(std::static_pointer_cast<ExampleDeclarationFunction>(
                  tree->declarations[2])
                  ->body->scope != nullptr);
  ASSERT_TRUE(std::static_pointer_cast<ExampleDeclarationFunction>(
                  tree->declarations[2])
                  ->body->scope->get("x") != nullptr);
}
