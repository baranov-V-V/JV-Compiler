#include "class_declaration.hpp"

#include <utility>

ClassDeclaration::ClassDeclaration(SharedPtr<ClassType> class_type,
                                   DeclarationList* decl_list) :
  class_type(std::move(class_type)), declaration_list(decl_list) {}

ClassDeclaration::~ClassDeclaration() {
  delete declaration_list;
}

void ClassDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
