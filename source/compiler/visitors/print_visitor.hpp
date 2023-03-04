#pragma once

#include "visitor.hpp"
#include "compiler/ast/forward_declaration.hpp"

#include <fstream>
#include <string>

/*
class PrintVisitor: public Visitor {
 public:
  PrintVisitor() = default;
  virtual ~PrintVisitor() override = default;

  enum class PrintType {
    PNG,
    DOT
  }

  void Print(const std::string& filename, PrintType type, Program* program);

  virtual Visit(ClassDeclarationList* class_declaration_list) override;
  virtual Visit(ClassDeclaration* class_declaration) override;
  virtual Visit(DeclarationList* declaration_list) override;
  virtual Visit(MethodDeclaration* method_declaration) override;
  virtual Visit(VariableDeclaration* variable_declarations) override;
  
  virtual Visit(BinOpExpression* bin_op) override;
  virtual Visit(TrueExpression* expression) override;
  virtual Visit(FalseExpression* expression) override;
  virtual Visit(FalseExpression* expression) override;
  virtual Visit(IdentifierExpression* expression) override;
  virtual Visit(IntegerExpression* expression) override;
  virtual Visit(NotExpression* expression) override;

  virtual Visit(MainClass* main_class) override;
  virtual Visit(Program* program) override;

  virtual Visit(AssignmentStatement* statement) override;
  virtual Visit(IfElseStatement* statement) override;
  virtual Visit(IfStatement* statement) override;
  virtual Visit(PrintStatement* statement) override;
  virtual Visit(ReturnStatement* statement) override;
  virtual Visit(WhileStatement* statement) override;
  virtual Visit(StatementList* statement) override;
};

*/