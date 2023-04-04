#pragma once

#include "ast/expressions/expression.hpp"
#include "ast/core/basic_list.hpp"

class CommaExpressionList : public BasicList<Expression> {
 public:
  CommaExpressionList() = default;
  explicit CommaExpressionList(Expression* expression);
  ~CommaExpressionList() override = default;

  void Accept(Visitor* visitor) override;
};
