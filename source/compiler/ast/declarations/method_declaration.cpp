#include "method_declaration.hpp"

MethodDeclaration::MethodDeclaration(const std::string& identifier,
                                     StatementList* statement_list) :
  Declaration(identifier), statement_list(statement_list) {}

MethodDeclaration::~MethodDeclaration() {
  delete statement_list;
}

void MethodDeclaration::Accept(Visitor* visitor) {
  return;
}
