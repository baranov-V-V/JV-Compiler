#pragma once

#include "compiler/visitors/visitor.hpp"
#include "compiler/util/program_stack.hpp"
#include "compiler/util/symbol_table.hpp"
#include "compiler/util/visitor_helper.hpp"

#include <unordered_map>
#include <string>
#include <deque>

class Interpreter : public Visitor, public VisitorHelper<int> {
 public:
  Interpreter() = default;
  virtual ~Interpreter() override = default;
    
  void Run(Program* program);

  virtual void Visit(Program* program) override;
  virtual void Visit(MainClass* main_class) override;
  
  virtual void Visit(ClassDeclaration* class_declaration) override;
  virtual void Visit(ClassDeclarationList* class_declaration_list) override;
  virtual void Visit(DeclarationList* declaration_list) override;
  virtual void Visit(MethodDeclaration* method_declaration) override;
  virtual void Visit(VariableDeclaration* variable_declaration) override;

  void Visit(LogicOpExpression* expression) override;
  void Visit(CompareOpExpression* expression) override;
  void Visit(MathOpExpression* expression) override;
  void Visit(TrueExpression* expression) override;
  void Visit(FalseExpression* expression) override;
  void Visit(IdentifierExpression* expression) override;
  void Visit(IntegerExpression* expression) override;
  void Visit(NotExpression* expression) override;

  void Visit(AssignmentStatement* statement) override;
  void Visit(IfElseStatement* statement) override;
  void Visit(IfStatement* statement) override;
  void Visit(PrintStatement* statement) override;
  void Visit(ReturnStatement* statement) override;
  void Visit(WhileStatement* statement) override;
  void Visit(StatementList* statement) override;
  void Visit(LocalVariableStatement* statement) override;
  void Visit(StatementListStatement* expression) override;

  void Visit(ArrayIdxExpression *expression) override;

  void Visit(LengthExpression *expression) override;

  void Visit(MethodCallExpression *expression) override;

  void Visit(NewArrayExpression *expression) override;

  void Visit(NewClassExpression *expression) override;

  void Visit(ThisExpression *expression) override;

  void Visit(CommaExpressionList *program) override;

  void Visit(MethodCall *program) override;

  void Visit(AssertStatement *statement) override;

  void Visit(MethodCallStatement *statement) override;

  void Visit(ArrayLValue *statement) override;

  void Visit(FieldLValue *statement) override;

  void Visit(IdentifierLValue *statement) override;

  virtual int Accept(AstNode* ast_node) override;
 private:
  SymbolTable<std::string, int> table;
  ProgramStack<int> stack;
};
