

#include "comma_expression_list.hpp"

CommaExpressionList::CommaExpressionList(Expression *expression) {
  elements.push_back(expression);
}

void CommaExpressionList::Accept(Visitor *visitor) {
  for (Expression* element: elements) {
    element->Accept(visitor);
  }
}
