#pragma

#include "ast/expressions/expression.hpp"
#include "ast/core/binary_operations.hpp"

class CompareOpExpression : public Expression {
 public:
  CompareOpExpression(Expression* lhs, CompareOperation operation, Expression* rhs);

  ~CompareOpExpression() override;

  void Accept(Visitor* visitor) override;

  Expression* lhs;
  CompareOperation operation;
  Expression* rhs;
};

