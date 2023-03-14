#pragma once

#include "print_visitor.hpp"
#include "compiler/ast/forward_declaration.hpp"

#include <fstream>
#include <filesystem>
#include <string>

#include "fmt/os.h"

class GraphPrintVisitor : public PrintVisitor {
 public:
  GraphPrintVisitor() = default;
  virtual ~GraphPrintVisitor() override = default;

  virtual void Print(const std::filesystem::path& filename, Program* program) override;

  virtual void Visit(Program* program) override;
  virtual void Visit(MainClass* main_class) override;
  
  virtual void Visit(ClassDeclaration* class_declaration) override;
  virtual void Visit(ClassDeclarationList* class_declaration_list) override;
  virtual void Visit(DeclarationList* declaration_list) override;
  virtual void Visit(MethodDeclaration* method_declaration) override;
  virtual void Visit(VariableDeclaration* variable_declaration) override;
  
  virtual void Visit(BinOpExpression* expression) override;
  virtual void Visit(TrueExpression* expression) override;
  virtual void Visit(FalseExpression* expression) override;
  virtual void Visit(IdentifierExpression* expression) override;
  virtual void Visit(IntegerExpression* expression) override;
  virtual void Visit(NotExpression* expression) override;

  virtual void Visit(AssignmentStatement* statement) override;
  virtual void Visit(IfElseStatement* statement) override;
  virtual void Visit(IfStatement* statement) override;
  virtual void Visit(PrintStatement* statement) override;
  virtual void Visit(ReturnStatement* statement) override;
  virtual void Visit(WhileStatement* statement) override;
  virtual void Visit(StatementList* statement) override;
  virtual void Visit(LocalVariableStatement* statement) override;
  virtual void Visit(StatementListStatement* statement) override;

 private:
  fmt::ostream stream;
};