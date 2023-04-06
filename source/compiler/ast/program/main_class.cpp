#include "main_class.hpp"
#include "types/type_factory.hpp"

MainClass::MainClass(StatementList* statement_list) :
  statement_list(statement_list), type(TypeFactory::GetClassTy(Symbol("main"))) {}

MainClass::~MainClass() {
  delete statement_list;
}

void MainClass::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
