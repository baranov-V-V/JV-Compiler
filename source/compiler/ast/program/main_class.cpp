#include "main_class.hpp"

MainClass::MainClass(StatementList* statement_list) :
  statement_list(statement_list) {}

MainClass::~MainClass() {
  delete statement_list;
}

void MainClass::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
