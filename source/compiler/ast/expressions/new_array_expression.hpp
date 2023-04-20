#pragma once

#include "types/type.hpp"
#include "expression.hpp"

class NewArrayExpression : public Expression {
 public:
  NewArrayExpression(SharedPtr<Type> type, Expression* size);

  ~NewArrayExpression() override;

  void Accept(Visitor* visitor) override;

  SharedPtr<Type> type;
  Expression* size;
};
