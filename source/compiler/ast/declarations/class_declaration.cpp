#include "class_declaration.hpp"

ClassDeclaration::ClassDeclaration(const std::string& class_name,
                                   DeclarationList* decl_list) :
  class_name(class_name), declaration_list(decl_list) {}

ClassDeclaration::~ClassDeclaration() {
  delete declaration_list;
}

void ClassDeclaration::Accept(Visitor* visitor) {
  return;
  visitor->Visit(this);
}
