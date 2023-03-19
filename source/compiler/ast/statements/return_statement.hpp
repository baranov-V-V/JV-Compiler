#pragma once

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class ReturnStatement: public Statement {
 public:
  ReturnStatement(Expression* expr);
  virtual ~ReturnStatement() override;
  
  virtual void Accept(Visitor* visitor) override;

  Expression* expression;
};
