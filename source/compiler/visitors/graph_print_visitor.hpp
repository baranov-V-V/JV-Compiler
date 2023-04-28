#pragma once

#include "print_visitor.hpp"
#include "compiler/ast/forward_declaration.hpp"

#include "fmt/os.h"
#include "util/symbol.hpp"

#include <fstream>
#include <filesystem>
#include <string>

//TODO full rewrite class
class GraphPrintVisitor : public PrintVisitor {
 public:
  GraphPrintVisitor() = default;
  ~GraphPrintVisitor() override = default;

  void Print(const std::filesystem::path& filename, Program* program) override;

  void Visit(Program* program) override;
  void Visit(MainClass* main_class) override;
  
  void Visit(ClassDeclaration* class_declaration) override;
  void Visit(ClassDeclarationList* class_declaration_list) override;
  void Visit(DeclarationList* list) override;
  void Visit(MethodDeclaration* declaration) override;
  void Visit(VariableDeclaration* variable_declaration) override;

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
  void Visit(StatementListStatement* statement) override;

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
  template<typename NodeType = void*>
  void PrintNode(const std::string& name, NodeType node);

  template<typename FromType = void*, typename ToType = void*>
  void PrintEdge(FromType from, ToType to, const std::string& direction = "");

  template<class ListType>
  void PrintList(ListType* list, const std::string& name, const std::string& delimiter = ";");

  fmt::ostream* stream;

  int fict_node_no;
};