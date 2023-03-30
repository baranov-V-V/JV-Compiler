#pragma once

#include "expression.hpp"
#include "types/class_type.hpp"

class NewClassExpression : public Expression {
 public:
  explicit NewClassExpression(SharedPtr<Type> type);
  ~NewClassExpression() override = default;

  void Accept(Visitor* visitor) override;

  SharedPtr<ClassType> type;
};
