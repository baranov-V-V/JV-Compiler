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
  
  void Visit(BinOpExpression* expression) override;
  void Visit(LogicOpExpression* expression) override;
  void Visit(CompareOpExpression* expression) override;
  void Visit(MathOpExpression* expression) override;
  void Visit(TrueExpression* expression) override;
  void Visit(FalseExpression* expression) override;
  void Visit(IdentifierExpression* expression) override;
  void Visit(IntegerExpression* expression) override;
  void Visit(NotExpression* expression) override;

  virtual void Visit(AssignmentStatement* statement) override;
  virtual void Visit(IfElseStatement* statement) override;
  virtual void Visit(IfStatement* statement) override;
  virtual void Visit(PrintStatement* statement) override;
  virtual void Visit(ReturnStatement* statement) override;
  virtual void Visit(WhileStatement* statement) override;
  virtual void Visit(StatementList* statement) override;
  virtual void Visit(LocalVariableStatement* statement) override;
  virtual void Visit(StatementListStatement* expression) override;
  
  virtual int Accept(AstNode* ast_node) override;
 private:
  SymbolTable<int> table;
  ProgramStack<int> stack;
};
