#include "declaration_list.hpp"

DeclarationList::DeclarationList(Declaration* declaration) {
  elements.push_back(declaration);
}

void DeclarationList::Accept(Visitor* visitor) {
  for (Declaration* element : elements) {
    element->Accept(visitor);
  }
}
