#include "symbol_table_visitor.hpp"
#include "compiler/ast/ast.hpp"

SymbolTableVisitor::SymbolTableVisitor() {}

SymbolLayerTree *SymbolTableVisitor::ConstructSymbolTree(Program *program) {
    ScopeLayer* global = new ScopeLayer(nullptr, global);
    SymbolLayerTree* tree = new SymbolLayerTree(global);

    return tree;
}

void SymbolTableVisitor::Visit(ClassDeclaration* class_declaration) {

}

void SymbolTableVisitor::Visit(ClassDeclarationList* class_declaration_list) {

}

void SymbolTableVisitor::Visit(DeclarationList* declaration_list) {

}

void SymbolTableVisitor::Visit(MethodDeclaration* method_declaration) {

}

void SymbolTableVisitor::Visit(VariableDeclaration* variable_declarations) {

}

void SymbolTableVisitor::Visit(ArrayIdxExpression* expression) {

}

void SymbolTableVisitor::Visit(TrueExpression* expression) {

}

void SymbolTableVisitor::Visit(FalseExpression* expression) {

}

void SymbolTableVisitor::Visit(CompareOpExpression* expression) {

}

void SymbolTableVisitor::Visit(IdentifierExpression* expression) {

}

void SymbolTableVisitor::Visit(IntegerExpression* expression) {

}

void SymbolTableVisitor::Visit(LengthExpression* expression) {

}

void SymbolTableVisitor::Visit(LogicOpExpression* expression) {

}

void SymbolTableVisitor::Visit(MathOpExpression* expression) {

}

void SymbolTableVisitor::Visit(MethodCallExpression* expression) {

}

void SymbolTableVisitor::Visit(NewArrayExpression* expression) {

}

void SymbolTableVisitor::Visit(NewClassExpression* expression) {

}

void SymbolTableVisitor::Visit(NotExpression* expression) {

}

void SymbolTableVisitor::Visit(ThisExpression* expression) {

}

void SymbolTableVisitor::Visit(MainClass* main_class) {

}

void SymbolTableVisitor::Visit(Program* program) {

}

void SymbolTableVisitor::Visit(CommaExpressionList* program) {

}

void SymbolTableVisitor::Visit(MethodCall* program) {

}

void SymbolTableVisitor::Visit(AssertStatement* statement) {

}

void SymbolTableVisitor::Visit(AssignmentStatement* statement) {

}

void SymbolTableVisitor::Visit(IfElseStatement* statement) {

}

void SymbolTableVisitor::Visit(IfStatement* statement) {

}

void SymbolTableVisitor::Visit(LocalVariableStatement* statement) {

}

void SymbolTableVisitor::Visit(MethodCallStatement* statement) {

}

void SymbolTableVisitor::Visit(PrintStatement* statement) {

}

void SymbolTableVisitor::Visit(ReturnStatement* statement) {

}

void SymbolTableVisitor::Visit(StatementList* statement) {

}

void SymbolTableVisitor::Visit(StatementListStatement* statement) {

}

void SymbolTableVisitor::Visit(WhileStatement* statement) {

}

void SymbolTableVisitor::Visit(ArrayLValue* statement) {

}

void SymbolTableVisitor::Visit(FieldLValue* statement) {

}

void SymbolTableVisitor::Visit(IdentifierLValue* statement) {

}

void SymbolTableVisitor::Visit(FieldDeclaration* declaration) {

}

void SymbolTableVisitor::ScopeGoUp() {
  layer_iterator.GoUp();
}

void SymbolTableVisitor::ScopeGoDown() {
  layer_iterator.GoDown();
}

void SymbolTableVisitor::VisitClassInfo(Program* program) {
  VisitClassInfo(program->main_class);
  VisitClassInfo(program->class_declaration_list);
}

void SymbolTableVisitor::VisitClassInfo(MainClass* main_class) {
  class_table.CreateClassInfo(main_class->type);
}

void SymbolTableVisitor::VisitClassInfo(ClassDeclaration* class_declaration) {
  class_table.CreateClassInfo(class_declaration->class_type);
  VisitClassInfo(class_declaration->declaration_list);
}

void SymbolTableVisitor::VisitClassInfo(ClassDeclarationList* class_declaration_list) {
  for (ClassDeclaration* declaration : class_declaration_list->elements) {
    VisitClassInfo(declaration);
  }
}

void SymbolTableVisitor::VisitClassInfo(FieldDeclaration* declaration) {

}

void SymbolTableVisitor::VisitClassInfo(MethodDeclaration* method_declaration) {

}

void SymbolTableVisitor::VisitClassInfo(DeclarationList* declaration_list) {

}
