#include "new_array_expression.hpp"

#include <utility>

void NewArrayExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

NewArrayExpression::NewArrayExpression(SharedPtr<Type> type, Expression* size) : type(std::move(type)), size(size) {}

NewArrayExpression::~NewArrayExpression() {
  delete size;
}
