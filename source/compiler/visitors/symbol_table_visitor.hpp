#pragma once

#include "visitor.hpp"
#include "scope/symbol_layer_tree.hpp"
#include "scope/symbol_table.hpp"

class SymbolTableVisitor : public Visitor {
 public:
  SymbolTableVisitor();
  ~SymbolTableVisitor() override = default;

  SymbolTable ConstructSymbolTree(Program* program);

  void Visit(ClassDeclaration* class_declaration) override;
  void Visit(ClassDeclarationList* class_declaration_list) override;
  void Visit(DeclarationList* declaration_list) override;
  void Visit(MethodDeclaration* method_declaration) override;
  void Visit(VariableDeclaration* variable_declarations) override;
  void Visit(ArrayIdxExpression* expression) override;
  void Visit(TrueExpression* expression) override;
  void Visit(FalseExpression* expression) override;
  void Visit(CompareOpExpression* expression) override;
  void Visit(IdentifierExpression* expression) override;
  void Visit(IntegerExpression* expression) override;
  void Visit(LengthExpression* expression) override;
  void Visit(LogicOpExpression* expression) override;
  void Visit(MathOpExpression* expression) override;
  void Visit(MethodCallExpression* expression) override;
  void Visit(NewArrayExpression* expression) override;
  void Visit(NewClassExpression* expression) override;
  void Visit(NotExpression* expression) override;
  void Visit(ThisExpression* expression) override;
  void Visit(MainClass* main_class) override;
  void Visit(Program* program) override;
  void Visit(CommaExpressionList* program) override;
  void Visit(MethodCall* program) override;
  void Visit(AssertStatement* statement) override;
  void Visit(AssignmentStatement* statement) override;
  void Visit(IfElseStatement* statement) override;
  void Visit(IfStatement* statement) override;
  void Visit(LocalVariableStatement* statement) override;
  void Visit(MethodCallStatement* statement) override;
  void Visit(PrintStatement* statement) override;
  void Visit(ReturnStatement* statement) override;
  void Visit(StatementList* statement) override;
  void Visit(StatementListStatement* statement) override;
  void Visit(WhileStatement* statement) override;
  void Visit(ArrayLValue* statement) override;
  void Visit(FieldLValue* statement) override;
  void Visit(IdentifierLValue* statement) override;
  void Visit(FieldDeclaration* declaration) override;

 private:
  void ScopeGoUp();
  void ScopeGoDown();

  void VisitClassInfo(Program* program);
  void VisitClassInfo(MainClass* program);
  void VisitClassInfo(ClassDeclaration* class_declaration);
  void VisitClassInfo(ClassDeclarationList* class_declaration_list);
  void VisitClassInfo(FieldDeclaration* declaration);
  void VisitClassInfo(MethodDeclaration* method_declaration);
  void VisitClassInfo(DeclarationList* declaration_list);

  SymbolLayerTree::Iterator layer_iterator;

  SymbolLayerTree layer_tree;
  ClassTable class_table;
};
