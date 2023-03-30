#include "new_class_expression.hpp"

#include <utility>

void NewClassExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

NewClassExpression::NewClassExpression(SharedPtr<Type> type) : type(std::move(type)) {}
