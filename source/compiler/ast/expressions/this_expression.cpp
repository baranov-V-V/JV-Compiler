#include "this_expression.hpp"

void ThisExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
