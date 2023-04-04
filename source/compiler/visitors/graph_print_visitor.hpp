#pragma once

#include "print_visitor.hpp"
#include "compiler/ast/forward_declaration.hpp"

#include "fmt/os.h"

#include <fstream>
#include <filesystem>
#include <string>

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
  virtual void Visit(StatementListStatement* statement) override;

  void Visit(FieldDeclaration* declaration) override;

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

private:
  fmt::ostream* stream;

  void MakeFictListNodes(int count);
  int fict_node_no;
};