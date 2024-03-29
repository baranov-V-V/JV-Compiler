#include "compiler/core/logger.hpp"
#include "class_table_visitor.hpp"
#include "ast/ast.hpp"

std::unique_ptr<ClassTable> ClassTableVisitor::ConstructClassTable(Program* program) {
  table = std::make_unique<ClassTable>();

  program->Accept(this);

  return std::move(table);
}

void ClassTableVisitor::Visit(MainClass* main_class) {
  table->CreateClassInfo(main_class->type);
}

void ClassTableVisitor::Visit(Program* program) {
  Visit(program->main_class);
  Visit(program->class_declaration_list);
}

void ClassTableVisitor::Visit(ClassDeclaration* class_declaration) {
  CheckRedeclared(class_declaration->class_type);
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
  table->AddField(current_type, declaration->identifier, declaration->type);
}

void ClassTableVisitor::Visit(MethodDeclaration* method_declaration) {
  CheckRedeclared(method_declaration->identifier);
  table->AddMethod(current_type, method_declaration->identifier, method_declaration->method_type);
}

void ClassTableVisitor::CheckRedeclared(const SharedPtr<ClassType>& class_type) {
  if (table->HasInfo(class_type)) {
    COMPILER_ERROR("Redeclaration of class {}", class_type->ToString());
  }
}

void ClassTableVisitor::CheckRedeclared(const Symbol& method) {
  if (table->GetInfo(current_type).HasMethodType(method)) {
    COMPILER_ERROR("Redeclaration of method with name '{}'", method.name);
  }
}
