#include "statement_list_statement.hpp"

StatementListStatement::StatementListStatement(StatementList* statement_list) :
  statement_list(statement_list) {}

void StatementListStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
