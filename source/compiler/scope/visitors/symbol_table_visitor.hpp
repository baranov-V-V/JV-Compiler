#pragma once

#include "visitors/visitor.hpp"
#include "scope/tables/symbol_layer_tree.hpp"
#include "visitors/empty_visitor.hpp"
#include "util/visitor_helper.hpp"
#include "util/program_stack.hpp"
#include "types/util/naive_type_converter.hpp"
#include "scope/tables/class_table.hpp"

class
SymbolTableVisitor : public Visitor, public VisitorHelper<SharedPtr<Type>> {
 public:
  SymbolTableVisitor();
  ~SymbolTableVisitor() override = default;

  std::unique_ptr<SymbolLayerTree> ConstructSymbolTree(Program* program);

  void Visit(ClassDeclaration* class_declaration) override;
  void Visit(ClassDeclarationList* class_declaration_list) override;
  void Visit(DeclarationList* declaration_list) override;
  void Visit(MethodDeclaration* method_declaration) override;
  void Visit(VariableDeclaration* declaration) override;
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
  void Visit(CommaExpressionList* expression_list) override;
  void Visit(MethodCall* call) override;
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

  SharedPtr<Type> Accept(AstNode* ast_node) override;

 private:
  void CheckTypesAndWarn(SharedPtr<Type> to, SharedPtr<Type> from);
  
  void CheckTypesConvertable(SharedPtr<Type> to, SharedPtr<Type> from);
  void WarnNarrowing(SharedPtr<Type> to, SharedPtr<Type> from);

  void CheckHasCommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs);
  void CheckTypePrimitive(SharedPtr<Type> type);

  //void CheckTypePrimitive(SharedPtr<Type> type);

  void CheckRedeclared(const Symbol& symbol);
  void CheckRedeclared(const SharedPtr<Type>& type, const Symbol& symbol);
  void CheckDeclaredAnywhere(const Symbol& symbol);

  void ScopeGoUp();
  void ScopeGoDown(const std::string& name = "anonymous");
  void ScopeGoDownClass(SharedPtr<ClassType> type);

  ProgramStack<SharedPtr<Type>> stack;

  SymbolLayerTree::Iterator layer_iterator;
  ClassTable* class_table;

  //TODO change to unique_pte
  std::unique_ptr<SymbolLayerTree> tree;

  NaiveTypeConverter converter;

  SharedPtr<ClassType> current_class;
  SharedPtr<MethodType> current_method;
};

