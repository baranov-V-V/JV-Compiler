#pragma once

#include <string>

#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"
#include "util/symbol.hpp"

class IdentifierExpression : public Expression {
 public:
  IdentifierExpression(const Symbol& identifier);

  virtual ~IdentifierExpression() = default;

  virtual void Accept(Visitor* visitor) override;

  Symbol identifier;
};
