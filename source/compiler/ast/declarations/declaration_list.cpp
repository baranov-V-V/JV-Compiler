#include "declaration_list.hpp"

DeclarationList::DeclarationList(Declaration* decaration) {
  elements.push_back(decaration);
}

void DeclarationList::Accept(Visitor* visitor) {
  for (Declaration* element : elements) {
    element->Accept(visitor);
  }
}
