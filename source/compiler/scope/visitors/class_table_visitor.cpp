#include "class_table_visitor.hpp"
#include "ast/ast.hpp"

ClassTable* ClassTableVisitor::ConstructClassTable(Program* program) {
  table = new ClassTable();

  program->Accept(this);

  return table;
}

void ClassTableVisitor::Visit(MainClass* main_class) {
  table->CreateClassInfo(main_class->type);
}

void ClassTableVisitor::Visit(Program* program) {
  Visit(program->main_class);
  Visit(program->class_declaration_list);
}

void ClassTableVisitor::Visit(ClassDeclaration* class_declaration) {
  table->CreateClassInfo(class_declaration->class_type);
  current_type = class_declaration->class_type;
  class_declaration->declaration_list->Accept(this);
}

void ClassTableVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  class_declaration_list->Accept(this);
}

void ClassTableVisitor::Visit(DeclarationList* declaration_list) {
  declaration_list->Accept(this);
}

void ClassTableVisitor::Visit(FieldDeclaration* declaration) {
  table->AddField(current_type, declaration->type);
}

void ClassTableVisitor::Visit(MethodDeclaration* method_declaration) {
  table->AddMethod(current_type, method_declaration->method_type);
}