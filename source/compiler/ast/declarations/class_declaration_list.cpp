#include "class_declaration_list.hpp"

ClassDeclarationList::ClassDeclarationList(ClassDeclaration* class_decl) {
  elements.push_back(class_decl);
}

void ClassDeclarationList::Accept(Visitor* visitor) {
  for (ClassDeclaration* element: elements) {
    element->Accept(visitor);
  }
}
