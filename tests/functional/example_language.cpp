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
  ExampleNode(ExampleNodeKind&& kind, std::optional<SourceRange>&& source_range)
      : Node(std::move(kind), std::move(source_range)) {}

  virtual ~ExampleNode() = 0;
};

ExampleNode::~ExampleNode() {}

class ExampleType : public ExampleNode {
 public:
  ExampleType(ExampleNodeKind&& kind, std::optional<SourceRange>&& source_range)
      : ExampleNode(std::move(kind), std::move(source_range)) {}

  ~ExampleType() = 0;
};

ExampleType::~ExampleType() {}

class ExampleTypeBool : public ExampleType {
 public:
  ExampleTypeBool(std::optional<SourceRange>&& source_range)
      : ExampleType(ExampleNodeKind::TypeBool, std::move(source_range)) {}

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleTypeBool>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const ExampleNode&) const override { return true; }
};

class ExampleTypeInt : public ExampleType {
 public:
  ExampleTypeInt(std::optional<SourceRange>&& source_range)
      : ExampleType(ExampleNodeKind::TypeInt, std::move(source_range)) {}

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleTypeInt>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const ExampleNode&) const override { return true; }
};

class ExampleTypeFunction : public ExampleType {
 public:
  ExampleTypeFunction(std::optional<SourceRange>&& source_range,
                      std::shared_ptr<ExampleType>&& return_type,
                      std::vector<std::shared_ptr<ExampleType>>&& arg_types)
      : ExampleType(ExampleNodeKind::TypeFunction, std::move(source_range)),
        return_type(std::move(return_type)),
        arg_types(std::move(arg_types)) {}

  std::shared_ptr<ExampleType> return_type;
  std::vector<std::shared_ptr<ExampleType>> arg_types;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(return_type);
    pass.visit(arg_types);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("return_type");
    formatter.node(return_type);

    formatter.field_label("arg_types");
    formatter.node_vector(arg_types);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleTypeFunction>(
        std::optional<SourceRange>(source_range), clone_node(return_type),
        clone_node_vector(arg_types));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(
               return_type,
               static_cast<const ExampleTypeFunction&>(other).return_type) &&
           compare_node_vectors(
               arg_types,
               static_cast<const ExampleTypeFunction&>(other).arg_types);
  }
};

class ExampleValue : public ExampleNode {
 public:
  ExampleValue(ExampleNodeKind&& kind,
               std::optional<SourceRange>&& source_range)
      : ExampleNode(std::move(kind), std::move(source_range)) {}

  ~ExampleValue() = 0;
};

ExampleValue::~ExampleValue() {}

class ExampleValueBool : public ExampleValue {
 public:
  ExampleValueBool(std::optional<SourceRange>&& source_range, bool value)
      : ExampleValue(ExampleNodeKind::ValueBool, std::move(source_range)),
        value(value) {}

  bool value;

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("value");
    formatter.stream() << (value ? "true" : "false");
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleValueBool>(
        std::optional<SourceRange>(source_range), value);
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return value == static_cast<const ExampleValueBool&>(other).value;
  }
};

class ExampleValueInt : public ExampleValue {
 public:
  ExampleValueInt(std::optional<SourceRange>&& source_range, int32_t value)
      : ExampleValue(ExampleNodeKind::ValueInt, std::move(source_range)),
        value(value) {}

  int32_t value;

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("value");
    formatter.stream() << value;
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleValueInt>(
        std::optional<SourceRange>(source_range), value);
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return value == static_cast<const ExampleValueInt&>(other).value;
  }
};

class ExampleValueSymbol : public ExampleValue {
 public:
  ExampleValueSymbol(std::optional<SourceRange>&& source_range,
                     std::string&& name)
      : ExampleValue(ExampleNodeKind::ValueSymbol, std::move(source_range)),
        name(name) {}

  std::string name;

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("name");
    formatter.string(name);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleValueSymbol>(
        std::optional<SourceRange>(source_range), std::string(name));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return name == static_cast<const ExampleValueSymbol&>(other).name;
  }
};

template <typename TSelf>
class ExampleValueBinary : public ExampleValue {
 public:
  ExampleValueBinary(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& source_range,
                     std::shared_ptr<ExampleValue>&& lhs,
                     std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValue(std::move(kind), std::move(source_range)),
        lhs(lhs),
        rhs(rhs) {}

  virtual ~ExampleValueBinary() = 0;

  std::shared_ptr<ExampleValue> lhs;
  std::shared_ptr<ExampleValue> rhs;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(lhs);
    pass.visit(rhs);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("lhs");
    formatter.node(lhs);

    formatter.field_label("rhs");
    formatter.node(rhs);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<TSelf>(std::optional<SourceRange>(source_range),
                                   clone_node(lhs), clone_node(rhs));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(lhs,
                         static_cast<const ExampleValueBinary&>(other).lhs) &&
           compare_nodes(rhs,
                         static_cast<const ExampleValueBinary&>(other).rhs);
  }
};

template <typename TSelf>
ExampleValueBinary<TSelf>::~ExampleValueBinary() {}

class ExampleValueAdd : public ExampleValueBinary<ExampleValueAdd> {
 public:
  ExampleValueAdd(std::optional<SourceRange>&& source_range,
                  std::shared_ptr<ExampleValue>&& lhs,
                  std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueAdd, std::move(source_range),
                           std::move(lhs), std::move(rhs)) {}
};

class ExampleValueLT : public ExampleValueBinary<ExampleValueLT> {
 public:
  ExampleValueLT(std::optional<SourceRange>&& source_range,
                 std::shared_ptr<ExampleValue>&& lhs,
                 std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueLT, std::move(source_range),
                           std::move(lhs), std::move(rhs)) {}
};

class ExampleValueEQ : public ExampleValueBinary<ExampleValueEQ> {
 public:
  ExampleValueEQ(std::optional<SourceRange>&& source_range,
                 std::shared_ptr<ExampleValue>&& lhs,
                 std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(ExampleNodeKind::ValueEQ, std::move(source_range),
                           std::move(lhs), std::move(rhs)) {}
};

template <typename TSelf>
class ExampleValueUnary : public ExampleValue {
 public:
  ExampleValueUnary(ExampleNodeKind&& kind,
                    std::optional<SourceRange>&& source_range,
                    std::shared_ptr<ExampleValue>&& operand)
      : ExampleValue(std::move(kind), std::move(source_range)),
        operand(operand) {}

  virtual ~ExampleValueUnary() = 0;

  std::shared_ptr<ExampleValue> operand;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(operand);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("operand");
    formatter.node(operand);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<TSelf>(std::optional<SourceRange>(source_range),
                                   clone_node(operand));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(operand,
                         static_cast<const ExampleValueUnary&>(other).operand);
  }
};

template <typename TSelf>
ExampleValueUnary<TSelf>::~ExampleValueUnary() {}

class ExampleValueNeg : public ExampleValueUnary<ExampleValueNeg> {
 public:
  ExampleValueNeg(std::optional<SourceRange>&& source_range,
                  std::shared_ptr<ExampleValue>&& operand)
      : ExampleValueUnary(ExampleNodeKind::ValueNeg, std::move(source_range),
                          std::move(operand)) {}
};

class ExampleValueCall : public ExampleValue {
 public:
  ExampleValueCall(std::optional<SourceRange>&& source_range,
                   std::shared_ptr<ExampleValue>&& callee,
                   std::vector<std::shared_ptr<ExampleValue>>&& args)
      : ExampleValue(ExampleNodeKind::ValueCall, std::move(source_range)),
        callee(std::move(callee)),
        args(std::move(args)) {}

  std::shared_ptr<ExampleValue> callee;
  std::vector<std::shared_ptr<ExampleValue>> args;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(callee);
    pass.visit(args);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("callee");
    formatter.node(callee);

    formatter.field_label("args");
    formatter.node_vector(args);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleValueCall>(
        std::optional<SourceRange>(source_range), clone_node(callee),
        clone_node_vector(args));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(callee,
                         static_cast<const ExampleValueCall&>(other).callee) &&
           compare_node_vectors(
               args, static_cast<const ExampleValueCall&>(other).args);
  }
};

class ExampleStatement : public ExampleNode {
 public:
  ExampleStatement(ExampleNodeKind&& kind,
                   std::optional<SourceRange>&& source_range)
      : ExampleNode(std::move(kind), std::move(source_range)) {}

  ~ExampleStatement() = 0;
};

ExampleStatement::~ExampleStatement() {}

class ExampleStatementIf : public ExampleStatement {
 public:
  ExampleStatementIf(std::optional<SourceRange>&& source_range,
                     std::shared_ptr<ExampleValue>&& condition,
                     std::shared_ptr<ExampleStatement>&& then,
                     std::shared_ptr<ExampleStatement>&& else_)
      : ExampleStatement(ExampleNodeKind::StatementIf, std::move(source_range)),
        condition(std::move(condition)),
        then(std::move(then)),
        else_(std::move(else_)) {}

  std::shared_ptr<ExampleValue> condition;
  std::shared_ptr<ExampleStatement> then;
  std::shared_ptr<ExampleStatement> else_;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(condition);
    pass.visit(then);
    pass.visit(else_);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("condition");
    formatter.node(condition);

    formatter.field_label("then");
    formatter.node(then);

    formatter.field_label("else");
    formatter.node(else_);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleStatementIf>(
        std::optional<SourceRange>(source_range), clone_node(condition),
        clone_node(then), clone_node(else_));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(
               condition,
               static_cast<const ExampleStatementIf&>(other).condition) &&
           compare_nodes(then,
                         static_cast<const ExampleStatementIf&>(other).then) &&
           compare_nodes(else_,
                         static_cast<const ExampleStatementIf&>(other).else_);
  }
};

class ExampleStatementWhile : public ExampleStatement {
 public:
  ExampleStatementWhile(std::optional<SourceRange>&& source_range,
                        std::shared_ptr<ExampleValue>&& condition,
                        std::shared_ptr<ExampleStatement>&& body)
      : ExampleStatement(ExampleNodeKind::StatementWhile,
                         std::move(source_range)),
        condition(std::move(condition)),
        body(std::move(body)) {}

  std::shared_ptr<ExampleValue> condition;
  std::shared_ptr<ExampleStatement> body;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(condition);
    pass.visit(body);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("condition");
    formatter.node(condition);

    formatter.field_label("body");
    formatter.node(body);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleStatementWhile>(
        std::optional<SourceRange>(source_range), clone_node(condition),
        clone_node(body));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(
               condition,
               static_cast<const ExampleStatementWhile&>(other).condition) &&
           compare_nodes(body,
                         static_cast<const ExampleStatementWhile&>(other).body);
  }
};

class ExampleStatementContinue : public ExampleStatement {
 public:
  ExampleStatementContinue(std::optional<SourceRange>&& source_range)
      : ExampleStatement(ExampleNodeKind::StatementContinue,
                         std::move(source_range)) {}

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleStatementContinue>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const ExampleNode&) const override { return true; }
};

class ExampleStatementBreak : public ExampleStatement {
 public:
  ExampleStatementBreak(std::optional<SourceRange>&& source_range)
      : ExampleStatement(ExampleNodeKind::StatementBreak,
                         std::move(source_range)) {}

 protected:
  virtual void on_accept(Pass<ExampleNode>&) override {}

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>&) const override {}

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleStatementBreak>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const ExampleNode&) const override { return true; }
};

class ExampleStatementReturn : public ExampleStatement {
 public:
  ExampleStatementReturn(std::optional<SourceRange>&& source_range,
                         std::shared_ptr<ExampleValue>&& value)
      : ExampleStatement(ExampleNodeKind::StatementReturn,
                         std::move(source_range)),
        value(std::move(value)) {}

  std::shared_ptr<ExampleValue> value;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(value);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("value");
    formatter.node(value);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleStatementReturn>(
        std::optional<SourceRange>(source_range), clone_node(value));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_nodes(
        value, static_cast<const ExampleStatementReturn&>(other).value);
  }
};

class ExampleStatementBlock : public ExampleStatement {
 public:
  ExampleStatementBlock(
      std::optional<SourceRange>&& source_range,
      std::vector<std::shared_ptr<ExampleStatement>>&& statements)
      : ExampleStatement(ExampleNodeKind::StatementBlock,
                         std::move(source_range)),
        statements(std::move(statements)) {}

  std::vector<std::shared_ptr<ExampleStatement>> statements;
  std::shared_ptr<Scope<ExampleNode>> scope;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(statements);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("statements");
    formatter.node_vector(statements);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleStatementBlock>(
        std::optional<SourceRange>(source_range),
        clone_node_vector(statements));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_node_vectors(
        statements,
        static_cast<const ExampleStatementBlock&>(other).statements);
  }
};

class ExampleDeclaration : public ExampleNode {
 public:
  ExampleDeclaration(ExampleNodeKind&& kind,
                     std::optional<SourceRange>&& source_range,
                     std::string&& name)
      : ExampleNode(std::move(kind), std::move(source_range)),
        name(std::move(name)) {}

  ~ExampleDeclaration() = 0;

  std::string name;

 protected:
  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("name");
    formatter.string(name);

    on_format_debug_declaration(formatter);
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return name == static_cast<const ExampleDeclaration&>(other).name &&
           on_compare_declaration(
               static_cast<const ExampleDeclaration&>(other));
  }

  virtual void on_format_debug_declaration(
      DebugFormatter<ExampleNodeKind>& formatter) const = 0;

  virtual bool on_compare_declaration(const ExampleNode& other) const = 0;
};

ExampleDeclaration::~ExampleDeclaration() {}

class ExampleDeclarationVariable : public ExampleDeclaration {
 public:
  ExampleDeclarationVariable(std::optional<SourceRange>&& source_range,
                             std::string&& name,
                             std::shared_ptr<ExampleType>&& type,
                             std::shared_ptr<ExampleValue>&& value = nullptr)
      : ExampleDeclaration(ExampleNodeKind::DeclarationVariable,
                           std::move(source_range), std::move(name)),
        type(std::move(type)),
        value(std::move(value)) {}

  std::shared_ptr<ExampleType> type;
  std::shared_ptr<ExampleValue> value;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(type);
    pass.visit(value);
  }

  virtual void on_format_debug_declaration(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("type");
    formatter.node(type);

    formatter.field_label("value");
    formatter.node(value);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleDeclarationVariable>(
        std::optional<SourceRange>(source_range), std::string(name),
        clone_node(type), clone_node(value));
  }

  virtual bool on_compare_declaration(const ExampleNode& other) const override {
    return compare_nodes(
               type,
               static_cast<const ExampleDeclarationVariable&>(other).type) &&
           compare_nodes(
               value,
               static_cast<const ExampleDeclarationVariable&>(other).value);
  }
};

class ExampleDeclarationFunction : public ExampleDeclaration {
 public:
  ExampleDeclarationFunction(
      std::optional<SourceRange>&& source_range, std::string&& name,
      std::shared_ptr<ExampleType>&& return_type,
      std::vector<std::shared_ptr<ExampleDeclarationVariable>>&& args,
      std::shared_ptr<ExampleStatementBlock>&& body = nullptr)
      : ExampleDeclaration(ExampleNodeKind::DeclarationFunction,
                           std::move(source_range), std::move(name)),
        return_type(std::move(return_type)),
        args(std::move(args)),
        body(std::move(body)) {}

  std::shared_ptr<ExampleType> return_type;
  std::vector<std::shared_ptr<ExampleDeclarationVariable>> args;
  std::shared_ptr<ExampleStatementBlock> body;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(return_type);
    pass.visit(args);
    pass.visit(body);
  }

  virtual void on_format_debug_declaration(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("return_type");
    formatter.node(return_type);

    formatter.field_label("args");
    formatter.node_vector(args);

    formatter.field_label("body");
    formatter.node(body);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleDeclarationFunction>(
        std::optional<SourceRange>(source_range), std::string(name),
        clone_node(return_type), clone_node_vector(args), clone_node(body));
  }

  virtual bool on_compare_declaration(const ExampleNode& other) const override {
    return compare_nodes(return_type,
                         static_cast<const ExampleDeclarationFunction&>(other)
                             .return_type) &&
           compare_node_vectors(
               args,
               static_cast<const ExampleDeclarationFunction&>(other).args) &&
           compare_nodes(
               body,
               static_cast<const ExampleDeclarationFunction&>(other).body);
  }
};

class ExampleTranslationUnit : public ExampleNode {
 public:
  ExampleTranslationUnit(
      std::optional<SourceRange>&& source_range,
      std::vector<std::shared_ptr<ExampleDeclaration>>&& declarations)
      : ExampleNode(ExampleNodeKind::TranslationUnit, std::move(source_range)),
        declarations(std::move(declarations)) {}

  std::vector<std::shared_ptr<ExampleDeclaration>> declarations;
  std::shared_ptr<Scope<ExampleNode>> scope;

 protected:
  virtual void on_accept(Pass<ExampleNode>& pass) override {
    pass.visit(declarations);
  }

  virtual void on_format_debug(
      DebugFormatter<ExampleNodeKind>& formatter) const override {
    formatter.field_label("declarations");
    formatter.node_vector(declarations);
  }

  virtual std::shared_ptr<ExampleNode> on_clone() const override {
    return std::make_shared<ExampleTranslationUnit>(
        std::optional<SourceRange>(source_range),
        clone_node_vector(declarations));
  }

  virtual bool on_compare(const ExampleNode& other) const override {
    return compare_node_vectors(
        declarations,
        static_cast<const ExampleTranslationUnit&>(other).declarations);
  }
};

// -----------------------------------------------------------------------------
// WELL FORMED VALIDATION HANDLER
// -----------------------------------------------------------------------------

class WellFormedValidationHandler : public Handler<ExampleNode> {
 protected:
  virtual typename Handler<ExampleNode>::Output on_enter(
      typename Handler<ExampleNode>::Input&) override {
    return typename Handler<ExampleNode>::Output();
  }

  virtual typename Handler<ExampleNode>::Output on_leave(
      typename Handler<ExampleNode>::Input& input) override {
    switch (input.node()->kind) {
        // -----------------------------------------------------------------

      case ExampleNodeKind::TypeBool:
      case ExampleNodeKind::TypeInt:
        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::TypeFunction:
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "return_type",
                static_cast<const ExampleTypeFunction&>(*input.node())
                    .return_type)) {
          break;
        }

        if (static_cast<const ExampleTypeFunction&>(*input.node())
                .return_type->kind == ExampleNodeKind::TypeFunction) {
          input.message_context().emit(
              static_cast<const ExampleTypeFunction&>(*input.node())
                  .return_type->source_range,
              SEVERITY_ERROR, "???", "functions cannot return other functions");
        }

        if (!validate_child_vector_not_null(
                input.message_context(), *input.node(), "arg_types",
                static_cast<const ExampleTypeFunction&>(*input.node())
                    .arg_types)) {
          break;
        }

        for (const auto& arg_type :
             static_cast<const ExampleTypeFunction&>(*input.node()).arg_types) {
          if (arg_type->kind == ExampleNodeKind::TypeFunction) {
            input.message_context().emit(arg_type->source_range, SEVERITY_ERROR,
                                         "???",
                                         "functions cannot be arguments");
          }
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueBool:
      case ExampleNodeKind::ValueInt:
        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueSymbol:
        if (!validate_string_not_empty(
                input.message_context(), *input.node(), "name",
                static_cast<const ExampleValueSymbol&>(*input.node()).name)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueAdd:
      case ExampleNodeKind::ValueLT:
      case ExampleNodeKind::ValueEQ:
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "lhs",
                static_cast<const ExampleValueBinary<ExampleValue>&>(
                    *input.node())
                    .lhs)) {
          break;
        }

        if (!validate_child_not_null(
                input.message_context(), *input.node(), "rhs",
                static_cast<const ExampleValueBinary<ExampleValue>&>(
                    *input.node())
                    .rhs)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueNeg:
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "operand",
                static_cast<const ExampleValueUnary<ExampleValue>&>(
                    *input.node())
                    .operand)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::ValueCall:
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "callee",
                static_cast<const ExampleValueCall&>(*input.node()).callee)) {
          break;
        }

        if (!validate_child_vector_not_null(
                input.message_context(), *input.node(), "args",
                static_cast<const ExampleValueCall&>(*input.node()).args)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementIf:
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "condition",
                static_cast<const ExampleStatementIf&>(*input.node())
                    .condition)) {
          break;
        }

        if (!validate_child_not_null(
                input.message_context(), *input.node(), "then",
                static_cast<const ExampleStatementIf&>(*input.node()).then)) {
          break;
        }

        if (!validate_child_not_null(
                input.message_context(), *input.node(), "else_",
                static_cast<const ExampleStatementIf&>(*input.node()).else_)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementWhile:
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "condition",
                static_cast<const ExampleStatementWhile&>(*input.node())
                    .condition)) {
          break;
        }

        if (!validate_child_not_null(
                input.message_context(), *input.node(), "body",
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
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "value",
                static_cast<const ExampleStatementReturn&>(*input.node())
                    .value)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::StatementBlock:
        if (!validate_child_vector_not_null(
                input.message_context(), *input.node(), "statements",
                static_cast<const ExampleStatementBlock&>(*input.node())
                    .statements)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::DeclarationVariable:
        if (!on_leave_declaration(
                input.message_context(), input.stack(),
                static_cast<const ExampleDeclarationVariable&>(
                    *input.node()))) {
          break;
        }

        if (!validate_child_not_null(
                input.message_context(), *input.node(), "type",
                static_cast<const ExampleDeclarationVariable&>(*input.node())
                    .type)) {
          break;
        }

        if (static_cast<const ExampleDeclarationVariable&>(*input.node())
                .type->kind == ExampleNodeKind::TypeFunction) {
          input.message_context().emit(
              static_cast<const ExampleDeclarationVariable&>(*input.node())
                  .type->source_range,
              SEVERITY_ERROR, "???", "variables cannot have function types");
        }

        // If this is a function argument declaration...
        if (!input.stack().empty() &&
            input.stack().back().get().kind ==
                ExampleNodeKind::DeclarationFunction) {
          if (!validate_child_null(
                  input.message_context(), *input.node(), "value",
                  static_cast<const ExampleDeclarationVariable&>(*input.node())
                      .value)) {
            break;
          }
        } else {
          if (!validate_child_not_null(
                  input.message_context(), *input.node(), "value",
                  static_cast<const ExampleDeclarationVariable&>(*input.node())
                      .value)) {
            break;
          }
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::DeclarationFunction:
        if (!on_leave_declaration(
                input.message_context(), input.stack(),
                static_cast<const ExampleDeclarationFunction&>(
                    *input.node()))) {
          break;
        }

        if (!validate_child_not_null(
                input.message_context(), *input.node(), "return_type",
                static_cast<const ExampleDeclarationFunction&>(*input.node())
                    .return_type)) {
          break;
        }

        if (static_cast<const ExampleDeclarationFunction&>(*input.node())
                .return_type->kind == ExampleNodeKind::TypeFunction) {
          input.message_context().emit(
              static_cast<const ExampleDeclarationFunction&>(*input.node())
                  .return_type->source_range,
              SEVERITY_ERROR, "???", "functions cannot return function types");
        }

        if (!validate_child_vector_not_null(
                input.message_context(), *input.node(), "args",
                static_cast<const ExampleDeclarationFunction&>(*input.node())
                    .args)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      case ExampleNodeKind::TranslationUnit:
        if (!validate_child_vector_not_null(
                input.message_context(), *input.node(), "declarations",
                static_cast<const ExampleTranslationUnit&>(*input.node())
                    .declarations)) {
          break;
        }

        break;

        // -----------------------------------------------------------------

      default:
        input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                     "???", "unknown node kind");
        break;

        // -----------------------------------------------------------------
    }

    return typename Handler<ExampleNode>::Output();
  }

  bool on_leave_declaration(
      MessageContext& message_context,
      const std::vector<std::reference_wrapper<const ExampleNode>>&,
      const ExampleDeclaration& node) {
    return validate_string_not_empty(
        message_context, node, "name",
        static_cast<const ExampleDeclarationVariable&>(node).name);
  }
};

// -----------------------------------------------------------------------------
// TEST HELPERS
// -----------------------------------------------------------------------------

std::shared_ptr<ExampleTranslationUnit> make_simple_tree() {
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
  auto translation_unit = std::make_shared<ExampleTranslationUnit>(
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

  return translation_unit;
}

// -----------------------------------------------------------------------------
// TESTS
// -----------------------------------------------------------------------------

TEST(functional_example_language, node_auto) {
  std::stringstream debug_formatter_stream;
  DebugFormatter<ExampleNodeKind> debug_formatter(debug_formatter_stream);

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TypeBool, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleTypeBool>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TypeInt, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleTypeInt>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TypeFunction, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleTypeFunction>(
          std::nullopt, std::make_shared<ExampleTypeInt>(std::nullopt),
          std::vector<std::shared_ptr<ExampleType>>{
              std::make_shared<ExampleTypeBool>(std::nullopt),
              std::make_shared<ExampleTypeInt>(std::nullopt)}))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueBool, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueBool>(std::nullopt, true))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueInt, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueInt>(std::nullopt, 5))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueSymbol, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueSymbol>(std::nullopt, "x"))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueAdd, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueAdd>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueNeg, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueNeg>(
          std::nullopt,
          std::make_shared<ExampleValueSymbol>(std::nullopt, "x")))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueLT, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueLT>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueEQ, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueEQ>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::ValueCall, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueCall>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "f"),
          std::vector<std::shared_ptr<ExampleValue>>(
              {std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
               std::make_shared<ExampleValueSymbol>(std::nullopt, "y")})))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementIf, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementIf>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleStatementContinue>(std::nullopt),
          std::make_shared<ExampleStatementBreak>(std::nullopt)))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementWhile, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementWhile>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleStatementContinue>(std::nullopt)))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementContinue, debug_formatter,
      debug_formatter_stream,
      std::make_shared<ExampleStatementContinue>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementBreak, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementBreak>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementReturn, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementReturn>(
          std::nullopt,
          std::make_shared<ExampleValueSymbol>(std::nullopt, "x")))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::StatementBlock, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementBlock>(
          std::nullopt,
          std::vector<std::shared_ptr<ExampleStatement>>(
              {std::make_shared<ExampleStatementContinue>(std::nullopt),
               std::make_shared<ExampleStatementBreak>(std::nullopt)})))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::DeclarationVariable, debug_formatter,
      debug_formatter_stream,
      std::make_shared<ExampleDeclarationVariable>(
          std::nullopt, "x", std::make_shared<ExampleTypeInt>(std::nullopt),
          std::make_shared<ExampleValueInt>(std::nullopt, 42)))));

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::DeclarationFunction, debug_formatter,
      debug_formatter_stream,
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

  EXPECT_TRUE((gtest_node_auto_assert<ExampleNodeKind, ExampleNode>(
      ExampleNodeKind::TranslationUnit, debug_formatter, debug_formatter_stream,
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

TEST(functional_example_language, construction) { make_simple_tree(); }

TEST(functional_example_language, debug_formatting) {
  std::stringstream stream;
  auto tree = make_simple_tree();
  DebugFormatter<ExampleNodeKind> debug_formatter(stream);

  debug_formatter.node(tree);

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
    "      return_type = [TypeInt]\n"
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
    "      return_type = [TypeInt]\n"
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

TEST(functional_example_language, comparison) {
  auto lhs = make_simple_tree();
  auto rhs = make_simple_tree();

  ASSERT_TRUE(compare_nodes(lhs, rhs));

  rhs->declarations[0]->name = "z";

  ASSERT_FALSE(compare_nodes(lhs, rhs));
}

TEST(functional_example_language, clone) {
  auto original = make_simple_tree();
  auto cloned =
      std::static_pointer_cast<ExampleTranslationUnit>(clone_node(original));

  ASSERT_TRUE(compare_nodes(original, cloned));

  cloned->declarations[0]->name = "z";

  ASSERT_FALSE(compare_nodes(original, cloned));
}

TEST(functional_example_language, well_formed_validation_pass) {
  auto tree = make_simple_tree();

  MessageContext message_context;
  Pass<ExampleNode> pass(message_context);
  pass.add_handler(std::make_unique<WellFormedValidationHandler>());

  pass.visit(tree);

  ASSERT_EQ(message_context.messages().size(), 0);

  tree->declarations[0]->name = "";

  pass.visit(tree);

  ASSERT_GT(message_context.messages().size(), 0);
}

TEST(functional_example_language, symbol_resolution) {
  auto tree = make_simple_tree();

  MessageContext message_context;
  Pass<ExampleNode> pass(message_context);

  pass.add_handler(std::make_unique<SymbolResolutionHandler<ExampleNode>>());

  pass.visit(tree);

  ASSERT_EQ(message_context.messages().size(), 0);

  ASSERT_TRUE(std::static_pointer_cast<ExampleDeclarationFunction>(
                  tree->declarations[2])
                  ->body->scope != nullptr);
  ASSERT_TRUE(std::static_pointer_cast<ExampleDeclarationFunction>(
                  tree->declarations[2])
                  ->body->scope->get("x") != nullptr);
}
