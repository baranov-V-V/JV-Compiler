#include "statement_list_node.hpp"

StatementListNode::StatementListNode(StatementList* statement_list) :
  statement_list(statement_list) {}

void StatementListNode::Accept(Visitor* visitor) {
  statement_list->Accept(visitor);
}
