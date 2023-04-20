#include "method_declaration.hpp"

MethodDeclaration::MethodDeclaration(const Symbol& identifier, SharedPtr<MethodType> method_type,
                                     StatementList* statement_list) :
  Declaration(identifier), method_type(std::move(method_type)), statement_list(statement_list) {}

MethodDeclaration::~MethodDeclaration() {
  delete statement_list;
}

void MethodDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
