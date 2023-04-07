#pragma once

#include "visitors/visitor.hpp"
#include "scope/tables/class_table.hpp"
#include "visitors/empty_visitor.hpp"

/**
 * @brief Constructs ClassTable, do not make any type-check/redeclaration-check;
 * 
 */
class ClassTableVisitor : public EmptyVisitor {
 public:
  ~ClassTableVisitor() override = default;
  ClassTableVisitor() = default;

  ClassTable* ConstructClassTable(Program* program);

  void Visit(ClassDeclaration* class_declaration) override;
  void Visit(ClassDeclarationList* class_declaration_list) override;
  void Visit(DeclarationList* declaration_list) override;
  void Visit(FieldDeclaration* declaration) override;
  void Visit(MethodDeclaration* method_declaration) override;
  void Visit(MainClass* main_class) override;
  void Visit(Program* program) override;

 private:
  ClassTable* table;
  SharedPtr<ClassType> current_type;
};