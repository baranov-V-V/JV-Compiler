#pragma once

#include <string>

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class AssignmentStatement: public Statement {
 public:
  AssignmentStatement(const std::string& identifier, Expression* expr);
  virtual ~AssignmentStatement() override;

  virtual void Accept(Visitor* visitor) override;

  const std::string identifier;
  Expression* expression;
};
