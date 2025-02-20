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
#include <forge/syntax_tree/scope/isymbol_resolving_node.hpp>
#include <forge/syntax_tree/scope/symbol_resolution_handler.hpp>

using namespace forge;

// -----------------------------------------------------------------------------
// SYNTAX TREE
// -----------------------------------------------------------------------------

const NodeKind TYPE_BOOL = NodeKind("type_bool");
const NodeKind TYPE_INT = NodeKind("type_int");
const NodeKind TYPE_FUNCTION = NodeKind("type_function");
const NodeKind VALUE_BOOL = NodeKind("value_bool");
const NodeKind VALUE_INT = NodeKind("value_int");
const NodeKind VALUE_SYMBOL = NodeKind("value_symbol");
const NodeKind VALUE_ADD = NodeKind("value_add");
const NodeKind VALUE_NEG = NodeKind("value_neg");
const NodeKind VALUE_LT = NodeKind("value_lt");
const NodeKind VALUE_EQ = NodeKind("value_eq");
const NodeKind VALUE_CALL = NodeKind("value_call");
const NodeKind STATEMENT_IF = NodeKind("statement_if");
const NodeKind STATEMENT_WHILE = NodeKind("statement_while");
const NodeKind STATEMENT_CONTINUE = NodeKind("statement_continue");
const NodeKind STATEMENT_BREAK = NodeKind("statement_break");
const NodeKind STATEMENT_RETURN = NodeKind("statement_return");
const NodeKind STATEMENT_BLOCK = NodeKind("statement_block");
const NodeKind DECLARATION_VARIABLE = NodeKind("declaration_variable");
const NodeKind DECLARATION_FUNCTION = NodeKind("declaration_function");
const NodeKind TRANSLATION_UNIT = NodeKind("translation_unit");

class ExampleNode : public BaseNode, public ISymbolResolvingNode {
 public:
  ExampleNode(NodeKind kind, std::optional<SourceRange>&& source_range)
      : BaseNode(kind, std::move(source_range)) {}

  ~ExampleNode() = 0;
};

ExampleNode::~ExampleNode() {}

class ExampleType : public ExampleNode {
 public:
  ExampleType(NodeKind kind, std::optional<SourceRange>&& source_range)
      : ExampleNode(kind, std::move(source_range)) {}

  ~ExampleType() = 0;
};

ExampleType::~ExampleType() {}

class ExampleTypeBool : public ExampleType {
 public:
  ExampleTypeBool(std::optional<SourceRange>&& source_range)
      : ExampleType(TYPE_BOOL, std::move(source_range)) {}

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter&) const override {}

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleTypeBool>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const BaseNode&) const override { return true; }
};

class ExampleTypeInt : public ExampleType {
 public:
  ExampleTypeInt(std::optional<SourceRange>&& source_range)
      : ExampleType(TYPE_INT, std::move(source_range)) {}

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter&) const override {}

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleTypeInt>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const BaseNode&) const override { return true; }
};

class ExampleTypeFunction : public ExampleType {
 public:
  ExampleTypeFunction(std::optional<SourceRange>&& source_range,
                      std::shared_ptr<ExampleType>&& return_type,
                      std::vector<std::shared_ptr<ExampleType>>&& arg_types)
      : ExampleType(TYPE_FUNCTION, std::move(source_range)),
        return_type(std::move(return_type)),
        arg_types(std::move(arg_types)) {}

  std::shared_ptr<ExampleType> return_type;
  std::vector<std::shared_ptr<ExampleType>> arg_types;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(return_type);
    visitor.visit(arg_types);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("return_type");
    formatter.node(return_type);

    formatter.field_label("arg_types");
    formatter.node_vector(arg_types);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleTypeFunction>(
        std::optional<SourceRange>(source_range), clone_node(return_type),
        clone_node_vector(arg_types));
  }

  virtual bool on_compare(const BaseNode& other) const override {
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
  ExampleValue(NodeKind kind, std::optional<SourceRange>&& source_range)
      : ExampleNode(std::move(kind), std::move(source_range)) {}

  ~ExampleValue() = 0;

  std::shared_ptr<ExampleType> resolved_type;
};

ExampleValue::~ExampleValue() {}

class ExampleValueBool : public ExampleValue {
 public:
  ExampleValueBool(std::optional<SourceRange>&& source_range, bool value)
      : ExampleValue(VALUE_BOOL, std::move(source_range)), value(value) {}

  bool value;

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("value");
    formatter.stream() << (value ? "true" : "false");
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleValueBool>(
        std::optional<SourceRange>(source_range), value);
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return value == static_cast<const ExampleValueBool&>(other).value;
  }
};

class ExampleValueInt : public ExampleValue {
 public:
  ExampleValueInt(std::optional<SourceRange>&& source_range, int32_t value)
      : ExampleValue(VALUE_INT, std::move(source_range)), value(value) {}

  int32_t value;

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("value");
    formatter.stream() << value;
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleValueInt>(
        std::optional<SourceRange>(source_range), value);
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return value == static_cast<const ExampleValueInt&>(other).value;
  }
};

class ExampleDeclaration;

class ExampleValueSymbol : public ExampleValue {
 public:
  ExampleValueSymbol(std::optional<SourceRange>&& source_range,
                     std::string&& name)
      : ExampleValue(VALUE_SYMBOL, std::move(source_range)), name(name) {}

  std::string name;
  std::shared_ptr<ExampleDeclaration> referenced_declaration;

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("name");
    formatter.string(name);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleValueSymbol>(
        std::optional<SourceRange>(source_range), std::string(name));
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return name == static_cast<const ExampleValueSymbol&>(other).name;
  }

  virtual std::optional<std::string> on_get_referenced_symbol_name()
      const override {
    return name;
  }

  virtual void on_resolve_symbol(
      std::shared_ptr<BaseNode> referenced_node) override {
    referenced_declaration =
        std::static_pointer_cast<ExampleDeclaration>(referenced_node);
  }
};

template <typename TSelf>
class ExampleValueBinary : public ExampleValue {
 public:
  ExampleValueBinary(NodeKind kind, std::optional<SourceRange>&& source_range,
                     std::shared_ptr<ExampleValue>&& lhs,
                     std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValue(kind, std::move(source_range)), lhs(lhs), rhs(rhs) {}

  virtual ~ExampleValueBinary() = 0;

  std::shared_ptr<ExampleValue> lhs;
  std::shared_ptr<ExampleValue> rhs;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(lhs);
    visitor.visit(rhs);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("lhs");
    formatter.node(lhs);

    formatter.field_label("rhs");
    formatter.node(rhs);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<TSelf>(std::optional<SourceRange>(source_range),
                                   clone_node(lhs), clone_node(rhs));
  }

  virtual bool on_compare(const BaseNode& other) const override {
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
      : ExampleValueBinary(VALUE_ADD, std::move(source_range), std::move(lhs),
                           std::move(rhs)) {}
};

class ExampleValueLT : public ExampleValueBinary<ExampleValueLT> {
 public:
  ExampleValueLT(std::optional<SourceRange>&& source_range,
                 std::shared_ptr<ExampleValue>&& lhs,
                 std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(VALUE_LT, std::move(source_range), std::move(lhs),
                           std::move(rhs)) {}
};

class ExampleValueEQ : public ExampleValueBinary<ExampleValueEQ> {
 public:
  ExampleValueEQ(std::optional<SourceRange>&& source_range,
                 std::shared_ptr<ExampleValue>&& lhs,
                 std::shared_ptr<ExampleValue>&& rhs)
      : ExampleValueBinary(VALUE_EQ, std::move(source_range), std::move(lhs),
                           std::move(rhs)) {}
};

template <typename TSelf>
class ExampleValueUnary : public ExampleValue {
 public:
  ExampleValueUnary(NodeKind kind, std::optional<SourceRange>&& source_range,
                    std::shared_ptr<ExampleValue>&& operand)
      : ExampleValue(kind, std::move(source_range)), operand(operand) {}

  virtual ~ExampleValueUnary() = 0;

  std::shared_ptr<ExampleValue> operand;

 protected:
  virtual void on_accept(IVisitor& visitor) override { visitor.visit(operand); }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("operand");
    formatter.node(operand);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<TSelf>(std::optional<SourceRange>(source_range),
                                   clone_node(operand));
  }

  virtual bool on_compare(const BaseNode& other) const override {
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
      : ExampleValueUnary(VALUE_NEG, std::move(source_range),
                          std::move(operand)) {}
};

class ExampleValueCall : public ExampleValue {
 public:
  ExampleValueCall(std::optional<SourceRange>&& source_range,
                   std::shared_ptr<ExampleValue>&& callee,
                   std::vector<std::shared_ptr<ExampleValue>>&& args)
      : ExampleValue(VALUE_CALL, std::move(source_range)),
        callee(std::move(callee)),
        args(std::move(args)) {}

  std::shared_ptr<ExampleValue> callee;
  std::vector<std::shared_ptr<ExampleValue>> args;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(callee);
    visitor.visit(args);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("callee");
    formatter.node(callee);

    formatter.field_label("args");
    formatter.node_vector(args);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleValueCall>(
        std::optional<SourceRange>(source_range), clone_node(callee),
        clone_node_vector(args));
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return compare_nodes(callee,
                         static_cast<const ExampleValueCall&>(other).callee) &&
           compare_node_vectors(
               args, static_cast<const ExampleValueCall&>(other).args);
  }
};

class ExampleStatement : public ExampleNode {
 public:
  ExampleStatement(NodeKind kind, std::optional<SourceRange>&& source_range)
      : ExampleNode(kind, std::move(source_range)) {}

  ~ExampleStatement() = 0;
};

ExampleStatement::~ExampleStatement() {}

class ExampleStatementIf : public ExampleStatement {
 public:
  ExampleStatementIf(std::optional<SourceRange>&& source_range,
                     std::shared_ptr<ExampleValue>&& condition,
                     std::shared_ptr<ExampleStatement>&& then,
                     std::shared_ptr<ExampleStatement>&& else_)
      : ExampleStatement(STATEMENT_IF, std::move(source_range)),
        condition(std::move(condition)),
        then(std::move(then)),
        else_(std::move(else_)) {}

  std::shared_ptr<ExampleValue> condition;
  std::shared_ptr<ExampleStatement> then;
  std::shared_ptr<ExampleStatement> else_;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(condition);
    visitor.visit(then);
    visitor.visit(else_);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("condition");
    formatter.node(condition);

    formatter.field_label("then");
    formatter.node(then);

    formatter.field_label("else");
    formatter.node(else_);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleStatementIf>(
        std::optional<SourceRange>(source_range), clone_node(condition),
        clone_node(then), clone_node(else_));
  }

  virtual bool on_compare(const BaseNode& other) const override {
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
      : ExampleStatement(STATEMENT_WHILE, std::move(source_range)),
        condition(std::move(condition)),
        body(std::move(body)) {}

  std::shared_ptr<ExampleValue> condition;
  std::shared_ptr<ExampleStatement> body;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(condition);
    visitor.visit(body);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("condition");
    formatter.node(condition);

    formatter.field_label("body");
    formatter.node(body);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleStatementWhile>(
        std::optional<SourceRange>(source_range), clone_node(condition),
        clone_node(body));
  }

  virtual bool on_compare(const BaseNode& other) const override {
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
      : ExampleStatement(STATEMENT_CONTINUE, std::move(source_range)) {}

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter&) const override {}

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleStatementContinue>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const BaseNode&) const override { return true; }
};

class ExampleStatementBreak : public ExampleStatement {
 public:
  ExampleStatementBreak(std::optional<SourceRange>&& source_range)
      : ExampleStatement(STATEMENT_BREAK, std::move(source_range)) {}

 protected:
  virtual void on_accept(IVisitor&) override {}

  virtual void on_format_debug(DebugFormatter&) const override {}

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleStatementBreak>(
        std::optional<SourceRange>(source_range));
  }

  virtual bool on_compare(const BaseNode&) const override { return true; }
};

class ExampleStatementReturn : public ExampleStatement {
 public:
  ExampleStatementReturn(std::optional<SourceRange>&& source_range,
                         std::shared_ptr<ExampleValue>&& value)
      : ExampleStatement(STATEMENT_RETURN, std::move(source_range)),
        value(std::move(value)) {}

  std::shared_ptr<ExampleValue> value;

 protected:
  virtual void on_accept(IVisitor& visitor) override { visitor.visit(value); }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("value");
    formatter.node(value);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleStatementReturn>(
        std::optional<SourceRange>(source_range), clone_node(value));
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return compare_nodes(
        value, static_cast<const ExampleStatementReturn&>(other).value);
  }
};

class ExampleStatementBlock : public ExampleStatement {
 public:
  ExampleStatementBlock(
      std::optional<SourceRange>&& source_range,
      std::vector<std::shared_ptr<ExampleStatement>>&& statements)
      : ExampleStatement(STATEMENT_BLOCK, std::move(source_range)),
        statements(std::move(statements)) {}

  std::vector<std::shared_ptr<ExampleStatement>> statements;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(statements);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("statements");
    formatter.node_vector(statements);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleStatementBlock>(
        std::optional<SourceRange>(source_range),
        clone_node_vector(statements));
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return compare_node_vectors(
        statements,
        static_cast<const ExampleStatementBlock&>(other).statements);
  }

  virtual ScopeFlags on_get_scope_flags() const override {
    return SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE;
  }

  virtual const Scope* on_try_get_scope() const override { return &_scope; }

 private:
  Scope _scope;
};

class ExampleDeclaration : public ExampleNode {
 public:
  ExampleDeclaration(NodeKind kind, std::optional<SourceRange>&& source_range,
                     std::string&& name)
      : ExampleNode(kind, std::move(source_range)), name(std::move(name)) {}

  ~ExampleDeclaration() = 0;

  std::string name;

 protected:
  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("name");
    formatter.string(name);

    on_format_debug_declaration(formatter);
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return name == static_cast<const ExampleDeclaration&>(other).name &&
           on_compare_declaration(
               static_cast<const ExampleDeclaration&>(other));
  }

  virtual void on_format_debug_declaration(DebugFormatter& formatter) const = 0;

  virtual bool on_compare_declaration(const BaseNode& other) const = 0;

  virtual std::optional<std::string> on_get_declared_symbol_name()
      const override {
    return name;
  }

  virtual ScopeFlags on_get_scope_flags() const override {
    return SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE;
  }

  virtual const Scope* on_try_get_scope() const override { return &_scope; }

 private:
  Scope _scope;
};

ExampleDeclaration::~ExampleDeclaration() {}

class ExampleDeclarationVariable : public ExampleDeclaration {
 public:
  ExampleDeclarationVariable(std::optional<SourceRange>&& source_range,
                             std::string&& name,
                             std::shared_ptr<ExampleType>&& type,
                             std::shared_ptr<ExampleValue>&& value = nullptr)
      : ExampleDeclaration(DECLARATION_VARIABLE, std::move(source_range),
                           std::move(name)),
        type(std::move(type)),
        value(std::move(value)) {}

  std::shared_ptr<ExampleType> type;
  std::shared_ptr<ExampleValue> value;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(type);
    visitor.visit(value);
  }

  virtual void on_format_debug_declaration(
      DebugFormatter& formatter) const override {
    formatter.field_label("type");
    formatter.node(type);

    formatter.field_label("value");
    formatter.node(value);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleDeclarationVariable>(
        std::optional<SourceRange>(source_range), std::string(name),
        clone_node(type), clone_node(value));
  }

  virtual bool on_compare_declaration(const BaseNode& other) const override {
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
      : ExampleDeclaration(DECLARATION_FUNCTION, std::move(source_range),
                           std::move(name)),
        return_type(std::move(return_type)),
        args(std::move(args)),
        body(std::move(body)) {}

  std::shared_ptr<ExampleType> return_type;
  std::vector<std::shared_ptr<ExampleDeclarationVariable>> args;
  std::shared_ptr<ExampleStatementBlock> body;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(return_type);
    visitor.visit(args);
    visitor.visit(body);
  }

  virtual void on_format_debug_declaration(
      DebugFormatter& formatter) const override {
    formatter.field_label("return_type");
    formatter.node(return_type);

    formatter.field_label("args");
    formatter.node_vector(args);

    formatter.field_label("body");
    formatter.node(body);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleDeclarationFunction>(
        std::optional<SourceRange>(source_range), std::string(name),
        clone_node(return_type), clone_node_vector(args), clone_node(body));
  }

  virtual bool on_compare_declaration(const BaseNode& other) const override {
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
      : ExampleNode(TRANSLATION_UNIT, std::move(source_range)),
        declarations(std::move(declarations)) {}

  std::vector<std::shared_ptr<ExampleDeclaration>> declarations;

 protected:
  virtual void on_accept(IVisitor& visitor) override {
    visitor.visit(declarations);
  }

  virtual void on_format_debug(DebugFormatter& formatter) const override {
    formatter.field_label("declarations");
    formatter.node_vector(declarations);
  }

  virtual std::shared_ptr<BaseNode> on_clone() const override {
    return std::make_shared<ExampleTranslationUnit>(
        std::optional<SourceRange>(source_range),
        clone_node_vector(declarations));
  }

  virtual bool on_compare(const BaseNode& other) const override {
    return compare_node_vectors(
        declarations,
        static_cast<const ExampleTranslationUnit&>(other).declarations);
  }

  virtual ScopeFlags on_get_scope_flags() const override {
    return SCOPE_FLAG_ALLOW_SHADOWING_PARENT_SCOPE | SCOPE_FLAG_UNORDERED;
  }

  virtual const Scope* on_try_get_scope() const override { return &_scope; }

 private:
  Scope _scope;
};

// -----------------------------------------------------------------------------
// WELL FORMED VALIDATION HANDLER
// -----------------------------------------------------------------------------

class WellFormedValidationHandler : public IHandler {
 protected:
  virtual Output on_enter(Input&) override { return Output(); }

  virtual Output on_leave(Input& input) override {
    // -----------------------------------------------------------------

    if (input.node()->kind == TYPE_BOOL || input.node()->kind == TYPE_INT) {
      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == TYPE_FUNCTION) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "return_type",
              static_cast<const ExampleTypeFunction&>(*input.node())
                  .return_type)) {
        return Output();
      }

      if (static_cast<const ExampleTypeFunction&>(*input.node())
              .return_type->kind == TYPE_FUNCTION) {
        input.message_context().emit(
            static_cast<const ExampleTypeFunction&>(*input.node())
                .return_type->source_range,
            SEVERITY_ERROR, "???", "functions cannot return other functions");
      }

      if (!validate_child_vector_not_null(
              input.message_context(), *input.node(), "arg_types",
              static_cast<const ExampleTypeFunction&>(*input.node())
                  .arg_types)) {
        return Output();
      }

      for (const auto& arg_type :
           static_cast<const ExampleTypeFunction&>(*input.node()).arg_types) {
        if (arg_type->kind == TYPE_FUNCTION) {
          input.message_context().emit(arg_type->source_range, SEVERITY_ERROR,
                                       "???", "functions cannot be arguments");
        }
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == VALUE_BOOL ||
             input.node()->kind == VALUE_INT) {
      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == VALUE_SYMBOL) {
      if (!validate_string_not_empty(
              input.message_context(), *input.node(), "name",
              static_cast<const ExampleValueSymbol&>(*input.node()).name)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == VALUE_ADD ||
             input.node()->kind == VALUE_LT || input.node()->kind == VALUE_EQ) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "lhs",
              static_cast<const ExampleValueBinary<ExampleValue>&>(
                  *input.node())
                  .lhs)) {
        return Output();
      }

      if (!validate_child_not_null(
              input.message_context(), *input.node(), "rhs",
              static_cast<const ExampleValueBinary<ExampleValue>&>(
                  *input.node())
                  .rhs)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == VALUE_NEG) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "operand",
              static_cast<const ExampleValueUnary<ExampleValue>&>(*input.node())
                  .operand)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == VALUE_CALL) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "callee",
              static_cast<const ExampleValueCall&>(*input.node()).callee)) {
        return Output();
      }

      if (!validate_child_vector_not_null(
              input.message_context(), *input.node(), "args",
              static_cast<const ExampleValueCall&>(*input.node()).args)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == STATEMENT_IF) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "condition",
              static_cast<const ExampleStatementIf&>(*input.node())
                  .condition)) {
        return Output();
      }

      if (!validate_child_not_null(
              input.message_context(), *input.node(), "then",
              static_cast<const ExampleStatementIf&>(*input.node()).then)) {
        return Output();
      }

      if (!validate_child_not_null(
              input.message_context(), *input.node(), "else_",
              static_cast<const ExampleStatementIf&>(*input.node()).else_)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == STATEMENT_WHILE) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "condition",
              static_cast<const ExampleStatementWhile&>(*input.node())
                  .condition)) {
        return Output();
      }

      if (!validate_child_not_null(
              input.message_context(), *input.node(), "body",
              static_cast<const ExampleStatementWhile&>(*input.node()).body)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == STATEMENT_CONTINUE ||
             input.node()->kind == STATEMENT_BREAK) {
      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == STATEMENT_RETURN) {
      if (!validate_child_not_null(
              input.message_context(), *input.node(), "value",
              static_cast<const ExampleStatementReturn&>(*input.node())
                  .value)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == STATEMENT_BLOCK) {
      if (!validate_child_vector_not_null(
              input.message_context(), *input.node(), "statements",
              static_cast<const ExampleStatementBlock&>(*input.node())
                  .statements)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == DECLARATION_VARIABLE) {
      if (!on_leave_declaration(
              input.message_context(), input.stack(),
              static_cast<const ExampleDeclarationVariable&>(*input.node()))) {
        return Output();
      }

      if (!validate_child_not_null(
              input.message_context(), *input.node(), "type",
              static_cast<const ExampleDeclarationVariable&>(*input.node())
                  .type)) {
        return Output();
      }

      if (static_cast<const ExampleDeclarationVariable&>(*input.node())
              .type->kind == TYPE_FUNCTION) {
        input.message_context().emit(
            static_cast<const ExampleDeclarationVariable&>(*input.node())
                .type->source_range,
            SEVERITY_ERROR, "???", "variables cannot have function types");
      }

      // If this is a function argument declaration...
      if (!input.stack().empty() &&
          input.stack().back().get().kind == DECLARATION_FUNCTION) {
        if (!validate_child_null(
                input.message_context(), *input.node(), "value",
                static_cast<const ExampleDeclarationVariable&>(*input.node())
                    .value)) {
          return Output();
        }
      } else {
        if (!validate_child_not_null(
                input.message_context(), *input.node(), "value",
                static_cast<const ExampleDeclarationVariable&>(*input.node())
                    .value)) {
          return Output();
        }
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == DECLARATION_FUNCTION) {
      if (!on_leave_declaration(
              input.message_context(), input.stack(),
              static_cast<const ExampleDeclarationFunction&>(*input.node()))) {
        return Output();
      }

      if (!validate_child_not_null(
              input.message_context(), *input.node(), "return_type",
              static_cast<const ExampleDeclarationFunction&>(*input.node())
                  .return_type)) {
        return Output();
      }

      if (static_cast<const ExampleDeclarationFunction&>(*input.node())
              .return_type->kind == TYPE_FUNCTION) {
        input.message_context().emit(
            static_cast<const ExampleDeclarationFunction&>(*input.node())
                .return_type->source_range,
            SEVERITY_ERROR, "???", "functions cannot return function types");
      }

      if (!validate_child_vector_not_null(
              input.message_context(), *input.node(), "args",
              static_cast<const ExampleDeclarationFunction&>(*input.node())
                  .args)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else if (input.node()->kind == TRANSLATION_UNIT) {
      if (!validate_child_vector_not_null(
              input.message_context(), *input.node(), "declarations",
              static_cast<const ExampleTranslationUnit&>(*input.node())
                  .declarations)) {
        return Output();
      }

      return Output();
    }

    // -----------------------------------------------------------------

    else {
      input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                   "???", "unknown node kind");
      return Output();
    }

    // -----------------------------------------------------------------
  }

  bool on_leave_declaration(
      MessageContext& message_context,
      const std::vector<std::reference_wrapper<const BaseNode>>&,
      const ExampleDeclaration& node) {
    return validate_string_not_empty(
        message_context, node, "name",
        static_cast<const ExampleDeclarationVariable&>(node).name);
  }
};

// -----------------------------------------------------------------------------
// TYPE RESOLUTION HANDLER
// -----------------------------------------------------------------------------

class TypeResolutionHandler : public IHandler {
 protected:
  virtual Output on_enter(Input& input) override {
    if (input.node()->kind == VALUE_BOOL) {
      static_cast<ExampleValue&>(*input.node()).resolved_type =
          std::make_shared<ExampleTypeBool>(std::nullopt);
    } else if (input.node()->kind == VALUE_INT) {
      static_cast<ExampleValue&>(*input.node()).resolved_type =
          std::make_shared<ExampleTypeInt>(std::nullopt);
    } else if (input.node()->kind == VALUE_SYMBOL) {
      if (static_cast<ExampleValueSymbol&>(*input.node())
              .referenced_declaration != nullptr) {
        if (static_cast<ExampleValueSymbol&>(*input.node())
                .referenced_declaration->kind == DECLARATION_VARIABLE) {
          static_cast<ExampleValue&>(*input.node()).resolved_type =
              clone_node(static_cast<ExampleDeclarationVariable&>(
                             *static_cast<ExampleValueSymbol&>(*input.node())
                                  .referenced_declaration)
                             .type);
        } else if (static_cast<ExampleValueSymbol&>(*input.node())
                       .referenced_declaration->kind == DECLARATION_VARIABLE) {
          std::shared_ptr<ExampleType> return_type =
              clone_node(static_cast<ExampleDeclarationFunction&>(
                             *static_cast<ExampleValueSymbol&>(*input.node())
                                  .referenced_declaration)
                             .return_type);

          std::vector<std::shared_ptr<ExampleType>> arg_types;

          for (const std::shared_ptr<ExampleDeclarationVariable>& arg :
               static_cast<ExampleDeclarationFunction&>(
                   *static_cast<ExampleValueSymbol&>(*input.node())
                        .referenced_declaration)
                   .args) {
            if (arg == nullptr) {
              arg_types.push_back(nullptr);
            } else {
              arg_types.push_back(clone_node(arg->type));
            }
          }

          static_cast<ExampleValue&>(*input.node()).resolved_type =
              std::make_shared<ExampleTypeFunction>(
                  std::nullopt, std::move(return_type), std::move(arg_types));
        }
      }
    } else if (input.node()->kind == VALUE_ADD) {
      static_cast<ExampleValue&>(*input.node()).resolved_type =
          std::make_shared<ExampleTypeInt>(std::nullopt);
    } else if (input.node()->kind == VALUE_NEG) {
      static_cast<ExampleValue&>(*input.node()).resolved_type =
          std::make_shared<ExampleTypeInt>(std::nullopt);
    } else if (input.node()->kind == VALUE_LT) {
      static_cast<ExampleValue&>(*input.node()).resolved_type =
          std::make_shared<ExampleTypeBool>(std::nullopt);
    } else if (input.node()->kind == VALUE_EQ) {
      static_cast<ExampleValue&>(*input.node()).resolved_type =
          std::make_shared<ExampleTypeBool>(std::nullopt);
    } else if (input.node()->kind == VALUE_CALL) {
      if (static_cast<ExampleValueSymbol&>(*input.node())
              .referenced_declaration != nullptr) {
        static_cast<ExampleValue&>(*input.node()).resolved_type =
            clone_node(static_cast<ExampleDeclarationFunction&>(
                           *static_cast<ExampleValueSymbol&>(*input.node())
                                .referenced_declaration)
                           .return_type);
      }
    }

    return Output();
  }

  virtual Output on_leave(Input&) override { return Output(); }
};

// -----------------------------------------------------------------------------
// TYPE VALIDATION HANDLER
// -----------------------------------------------------------------------------

class TypeValidationHandler : public IHandler {
 protected:
  virtual Output on_enter(Input& input) override {
    if (input.node()->kind == VALUE_NEG) {
      if (static_cast<ExampleValueNeg&>(*input.node()).operand != nullptr &&
          static_cast<ExampleValueNeg&>(*input.node()).operand->resolved_type !=
              nullptr &&
          static_cast<ExampleValueNeg&>(*input.node())
                  .operand->resolved_type->kind != TYPE_INT) {
        input.message_context().emit(
            static_cast<ExampleValueNeg&>(*input.node()).operand->source_range,
            SEVERITY_ERROR, "???", "operator only supports integers");
      }
    } else if (input.node()->kind == VALUE_ADD ||
               input.node()->kind == VALUE_LT ||
               input.node()->kind == VALUE_EQ) {
      if (static_cast<ExampleValueAdd&>(*input.node()).lhs != nullptr &&
          static_cast<ExampleValueAdd&>(*input.node()).lhs->resolved_type !=
              nullptr &&
          static_cast<ExampleValueAdd&>(*input.node())
                  .lhs->resolved_type->kind != TYPE_INT) {
        input.message_context().emit(
            static_cast<ExampleValueAdd&>(*input.node()).lhs->source_range,
            SEVERITY_ERROR, "???", "operator only supports integers");
      }

      if (static_cast<ExampleValueAdd&>(*input.node()).rhs != nullptr &&
          static_cast<ExampleValueAdd&>(*input.node()).rhs->resolved_type !=
              nullptr &&
          static_cast<ExampleValueAdd&>(*input.node())
                  .rhs->resolved_type->kind != TYPE_INT) {
        input.message_context().emit(
            static_cast<ExampleValueAdd&>(*input.node()).rhs->source_range,
            SEVERITY_ERROR, "???", "operator only supports integers");
      }
    } else if (input.node()->kind == VALUE_CALL) {
      if (static_cast<ExampleValueCall&>(*input.node()).callee != nullptr &&
          static_cast<ExampleValueCall&>(*input.node()).callee->resolved_type !=
              nullptr &&
          static_cast<ExampleValueCall&>(*input.node())
                  .callee->resolved_type->kind != TYPE_FUNCTION) {
        input.message_context().emit(
            static_cast<ExampleValueCall&>(*input.node()).callee->source_range,
            SEVERITY_ERROR, "???", "callee must be a function");
      } else {
        const auto& function_type = static_cast<const ExampleTypeFunction&>(
            *static_cast<ExampleValueCall&>(*input.node())
                 .callee->resolved_type);

        if (function_type.arg_types.size() !=
            static_cast<ExampleValueCall&>(*input.node()).args.size()) {
          input.message_context().emit(
              static_cast<ExampleValueCall&>(*input.node()).source_range,
              SEVERITY_ERROR, "???", "incorrect number of arguments");
        } else {
          for (size_t i = 0; i < function_type.arg_types.size(); ++i) {
            if (static_cast<ExampleValueCall&>(*input.node())
                        .args[0]
                        ->resolved_type != nullptr &&
                !compare_nodes(function_type.arg_types[0],
                               static_cast<ExampleValueCall&>(*input.node())
                                   .args[0]
                                   ->resolved_type)) {
              input.message_context().emit(
                  static_cast<ExampleValueCall&>(*input.node())
                      .args[0]
                      ->source_range,
                  SEVERITY_ERROR, "???", "incorrect argument type");
            }
          }
        }
      }
    } else if (input.node()->kind == STATEMENT_IF) {
      if (static_cast<ExampleStatementIf&>(*input.node()).condition !=
              nullptr &&
          static_cast<ExampleStatementIf&>(*input.node())
                  .condition->resolved_type != nullptr &&
          static_cast<ExampleStatementIf&>(*input.node())
                  .condition->resolved_type->kind != TYPE_BOOL) {
        input.message_context().emit(
            static_cast<ExampleValueNeg&>(*input.node()).operand->source_range,
            SEVERITY_ERROR, "???", "condition must be boolean");
      }
    } else if (input.node()->kind == STATEMENT_WHILE) {
      if (static_cast<ExampleStatementWhile&>(*input.node()).condition !=
              nullptr &&
          static_cast<ExampleStatementWhile&>(*input.node())
                  .condition->resolved_type != nullptr &&
          static_cast<ExampleStatementWhile&>(*input.node())
                  .condition->resolved_type->kind != TYPE_BOOL) {
        input.message_context().emit(
            static_cast<ExampleValueNeg&>(*input.node()).operand->source_range,
            SEVERITY_ERROR, "???", "condition must be boolean");
      }
    } else if (input.node()->kind == STATEMENT_RETURN) {
      const ExampleDeclarationFunction* parent_function = nullptr;

      for (auto i = input.stack().rbegin(); i != input.stack().rend(); i++) {
        if (i->get().kind == DECLARATION_FUNCTION) {
          parent_function =
              &static_cast<const ExampleDeclarationFunction&>(i->get());
          break;
        }
      }

      if (parent_function == nullptr) {
        input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                     "???",
                                     "return outside "
                                     "of function");
      } else {
        if (static_cast<ExampleStatementReturn&>(*input.node()).value !=
                nullptr &&
            static_cast<ExampleStatementReturn&>(*input.node())
                    .value->resolved_type != nullptr &&
            !compare_nodes(parent_function->return_type,
                           static_cast<ExampleStatementReturn&>(*input.node())
                               .value->resolved_type)) {
          input.message_context().emit(
              static_cast<ExampleStatementReturn&>(*input.node())
                  .value->source_range,
              SEVERITY_ERROR, "???",
              "return type does not match function "
              "return type");
        }
      }
    }

    return Output();
  }

  virtual Output on_leave(Input&) override { return Output(); }
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
  DebugFormatter debug_formatter(debug_formatter_stream);

  EXPECT_TRUE((
      gtest_node_auto_assert(TYPE_BOOL, debug_formatter, debug_formatter_stream,
                             std::make_shared<ExampleTypeBool>(std::nullopt))));

  EXPECT_TRUE(
      (gtest_node_auto_assert(TYPE_INT, debug_formatter, debug_formatter_stream,
                              std::make_shared<ExampleTypeInt>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert(
      TYPE_FUNCTION, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleTypeFunction>(
          std::nullopt, std::make_shared<ExampleTypeInt>(std::nullopt),
          std::vector<std::shared_ptr<ExampleType>>{
              std::make_shared<ExampleTypeBool>(std::nullopt),
              std::make_shared<ExampleTypeInt>(std::nullopt)}))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_BOOL, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueBool>(std::nullopt, true))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_INT, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueInt>(std::nullopt, 5))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_SYMBOL, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueSymbol>(std::nullopt, "x"))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_ADD, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueAdd>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_NEG, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueNeg>(
          std::nullopt,
          std::make_shared<ExampleValueSymbol>(std::nullopt, "x")))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_LT, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueLT>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_EQ, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueEQ>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleValueSymbol>(std::nullopt, "y")))));

  EXPECT_TRUE((gtest_node_auto_assert(
      VALUE_CALL, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleValueCall>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "f"),
          std::vector<std::shared_ptr<ExampleValue>>(
              {std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
               std::make_shared<ExampleValueSymbol>(std::nullopt, "y")})))));

  EXPECT_TRUE((gtest_node_auto_assert(
      STATEMENT_IF, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementIf>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleStatementContinue>(std::nullopt),
          std::make_shared<ExampleStatementBreak>(std::nullopt)))));

  EXPECT_TRUE((gtest_node_auto_assert(
      STATEMENT_WHILE, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementWhile>(
          std::nullopt, std::make_shared<ExampleValueSymbol>(std::nullopt, "x"),
          std::make_shared<ExampleStatementContinue>(std::nullopt)))));

  EXPECT_TRUE((gtest_node_auto_assert(
      STATEMENT_CONTINUE, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementContinue>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert(
      STATEMENT_BREAK, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementBreak>(std::nullopt))));

  EXPECT_TRUE((gtest_node_auto_assert(
      STATEMENT_RETURN, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementReturn>(
          std::nullopt,
          std::make_shared<ExampleValueSymbol>(std::nullopt, "x")))));

  EXPECT_TRUE((gtest_node_auto_assert(
      STATEMENT_BLOCK, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleStatementBlock>(
          std::nullopt,
          std::vector<std::shared_ptr<ExampleStatement>>(
              {std::make_shared<ExampleStatementContinue>(std::nullopt),
               std::make_shared<ExampleStatementBreak>(std::nullopt)})))));

  EXPECT_TRUE((gtest_node_auto_assert(
      DECLARATION_VARIABLE, debug_formatter, debug_formatter_stream,
      std::make_shared<ExampleDeclarationVariable>(
          std::nullopt, "x", std::make_shared<ExampleTypeInt>(std::nullopt),
          std::make_shared<ExampleValueInt>(std::nullopt, 42)))));

  EXPECT_TRUE((gtest_node_auto_assert(
      DECLARATION_FUNCTION, debug_formatter, debug_formatter_stream,
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

  EXPECT_TRUE((gtest_node_auto_assert(
      TRANSLATION_UNIT, debug_formatter, debug_formatter_stream,
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
  DebugFormatter debug_formatter(stream);

  debug_formatter.node(tree);

  // clang-format off
  ASSERT_EQ(
    stream.str(),
    "[translation_unit]\n"
    "  declarations = \n"
    "    [0] = [declaration_variable]\n"
    "      name = \"x\"\n"
    "      type = [type_int]\n"
    "      value = [value_int]\n"
    "        value = 42\n"
    "    [1] = [declaration_variable]\n"
    "      name = \"y\"\n"
    "      type = [type_bool]\n"
    "      value = [value_bool]\n"
    "        value = true\n"
    "    [2] = [declaration_function]\n"
    "      name = \"add\"\n"
    "      return_type = [type_int]\n"
    "      args = \n"
    "        [0] = [declaration_variable]\n"
    "          name = \"x\"\n"
    "          type = [type_int]\n"
    "          value = null\n"
    "        [1] = [declaration_variable]\n"
    "          name = \"y\"\n"
    "          type = [type_int]\n"
    "          value = null\n"
    "      body = [statement_block]\n"
    "        statements = \n"
    "          [0] = [statement_return]\n"
    "            value = [value_add]\n"
    "              lhs = [value_symbol]\n"
    "                name = \"x\"\n"
    "              rhs = [value_symbol]\n"
    "                name = \"y\"\n"
    "    [3] = [declaration_function]\n"
    "      name = \"abs\"\n"
    "      return_type = [type_int]\n"
    "      args = \n"
    "        [0] = [declaration_variable]\n"
    "          name = \"x\"\n"
    "          type = [type_int]\n"
    "          value = null\n"
    "      body = [statement_block]\n"
    "        statements = \n"
    "          [0] = [statement_if]\n"
    "            condition = [value_lt]\n"
    "              lhs = [value_symbol]\n"
    "                name = \"x\"\n"
    "              rhs = [value_int]\n"
    "                value = 0\n"
    "            then = [statement_block]\n"
    "              statements = \n"
    "                [0] = [statement_return]\n"
    "                  value = [value_neg]\n"
    "                    operand = [value_symbol]\n"
    "                      name = \"x\"\n"
    "            else = [statement_block]\n"
    "              statements = \n"
    "                [0] = [statement_return]\n"
    "                  value = [value_symbol]\n"
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
  Pass pass(message_context);
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
  Pass pass(message_context);

  pass.add_handler(std::make_unique<SymbolResolutionHandler<ExampleNode>>());

  pass.visit(tree);

  ASSERT_EQ(message_context.messages().size(), 0);

  ASSERT_TRUE(std::static_pointer_cast<ExampleDeclarationFunction>(
                  tree->declarations[2])
                  ->try_get_scope()
                  ->get("x") != nullptr);
}

TEST(functional_example_language, type_resolution) {
  auto tree = make_simple_tree();

  MessageContext message_context;
  Pass pass(message_context);

  pass.add_handler(std::make_unique<SymbolResolutionHandler<ExampleNode>>());
  pass.add_handler(std::make_unique<TypeResolutionHandler>());

  pass.visit(tree);

  ASSERT_EQ(message_context.messages().size(), 0);
}
