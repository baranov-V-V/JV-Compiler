#pragma once

#include <string>

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"
#include "util/symbol.hpp"

class IdentifierExpression: public Expression {
 public:
  IdentifierExpression(const Symbol& identifier);
  virtual ~IdentifierExpression() = default;

  virtual void Accept(Visitor* visitor) override;

  Symbol identifier;
};
