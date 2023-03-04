#pragma once

#include <string>

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class IdentifierExpression: public Expression {
 public:
  IdentifierExpression(const std::string& identifier);
  virtual ~IdentifierExpression() = default;

  virtual void Accept(Visitor* visitor) override;

  std::string identifier;
};
