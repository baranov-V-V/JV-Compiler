#pragma once

#include "compiler/ast/forward_declaration.hpp"

class Visitor {
 public:
  Visitor() = default;
  virtual ~Visitor() = default;

  virtual void Visit(ClassDeclaration* class_declaration) = 0;
  virtual void Visit(ClassDeclarationList* class_declaration_list) = 0;
  virtual void Visit(DeclarationList* declaration_list) = 0;
  virtual void Visit(MethodDeclaration* method_declaration) = 0;
  virtual void Visit(VariableDeclaration* variable_declarations) = 0;

  virtual void Visit(ArrayIdxExpression* expression) = 0;
  virtual void Visit(TrueExpression* expression) = 0;
  virtual void Visit(FalseExpression* expression) = 0;
  virtual void Visit(CompareOpExpression* expression) = 0;
  virtual void Visit(IdentifierExpression* expression) = 0;
  virtual void Visit(IntegerExpression* expression) = 0;
  virtual void Visit(LengthExpression* expression) = 0;
  virtual void Visit(LogicOpExpression* expression) = 0;
  virtual void Visit(MathOpExpression* expression) = 0;
  virtual void Visit(MethodCallExpression* expression) = 0;
  virtual void Visit(NewArrayExpression* expression) = 0;
  virtual void Visit(NewClassExpression* expression) = 0;
  virtual void Visit(NotExpression* expression) = 0;
  virtual void Visit(ThisExpression* expression) = 0;

  virtual void Visit(MainClass* main_class) = 0;
  virtual void Visit(Program* program) = 0;

  virtual void Visit(CommaExpressionList* program) = 0;
  virtual void Visit(MethodCall* program) = 0;

  virtual void Visit(AssertStatement* statement) = 0;
  virtual void Visit(AssignmentStatement* statement) = 0;
  virtual void Visit(IfElseStatement* statement) = 0;
  virtual void Visit(IfStatement* statement) = 0;
  virtual void Visit(LocalVariableStatement* statement) = 0;
  virtual void Visit(MethodCallStatement* statement) = 0;
  virtual void Visit(PrintStatement* statement) = 0;
  virtual void Visit(ReturnStatement* statement) = 0;
  virtual void Visit(StatementList* statement) = 0;
  virtual void Visit(StatementListStatement* statement) = 0;
  virtual void Visit(WhileStatement* statement) = 0;

  virtual void Visit(ArrayLValue* statement) = 0;
  virtual void Visit(FieldLValue* statement) = 0;
  virtual void Visit(IdentifierLValue* statement) = 0;
};
