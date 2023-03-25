#pragma

#include "ast/expressions/expression.hpp"
#include "ast/core/compare_operation.hpp"

class CompareOpExpression : public Expression {
 public:
  CompareOpExpression(Expression* lhs, CompareOperation operation, Expression* rhs);
  ~CompareOpExpression() override = default;
  void Accept(Visitor* visitor) override;

  Expression* lhs;
  CompareOperation operation;
  Expression* rhs;
};

