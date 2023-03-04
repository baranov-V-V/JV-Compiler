#include "statement_list.hpp"

StatementList::StatementList(Statement* statement) {
  elements.push_back(statement);
}

void StatementList::Accept(Visitor* visitor) { return; }
