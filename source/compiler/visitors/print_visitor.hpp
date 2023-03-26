#pragma once

#include "visitor.hpp"
#include "compiler/ast/forward_declaration.hpp"

#include <filesystem>
#include <string>

class PrintVisitor: public Visitor {
 public:
  PrintVisitor() = default;
  virtual ~PrintVisitor() = default;

  virtual void Print(const std::filesystem::path& filename, Program* program) = 0;

  virtual void Visit(Program* program) = 0;
  virtual void Visit(MainClass* main_class) = 0;
  
  virtual void Visit(ClassDeclaration* class_declaration) = 0;
  virtual void Visit(ClassDeclarationList* class_declaration_list) = 0;
  virtual void Visit(DeclarationList* declaration_list) = 0;
  virtual void Visit(MethodDeclaration* method_declaration) = 0;
  virtual void Visit(VariableDeclaration* variable_declaration) = 0;

  virtual void Visit(LogicOpExpression* expression) = 0;
  virtual void Visit(CompareOpExpression* expression) = 0;
  virtual void Visit(MathOpExpression* expression) = 0;
  virtual void Visit(TrueExpression* expression) = 0;
  virtual void Visit(FalseExpression* expression) = 0;
  virtual void Visit(IdentifierExpression* expression) = 0;
  virtual void Visit(IntegerExpression* expression) = 0;
  virtual void Visit(NotExpression* expression) = 0;

  virtual void Visit(AssignmentStatement* statement) = 0;
  virtual void Visit(IfElseStatement* statement) = 0;
  virtual void Visit(IfStatement* statement) = 0;
  virtual void Visit(PrintStatement* statement) = 0;
  virtual void Visit(ReturnStatement* statement) = 0;
  virtual void Visit(WhileStatement* statement) = 0;
  virtual void Visit(StatementList* statement) = 0;
  virtual void Visit(LocalVariableStatement* statement) = 0;
  virtual void Visit(StatementListStatement* statement) = 0;
};
