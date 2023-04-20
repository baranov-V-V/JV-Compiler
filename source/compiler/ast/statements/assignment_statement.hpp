#pragma once

#include <string>

#include "ast/statements/statement.hpp"
#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"
#include "ast/values/l_value.hpp"

class AssignmentStatement : public Statement {
 public:
  AssignmentStatement(LValue* identifier, Expression* expr);

  ~AssignmentStatement() override;

  void Accept(Visitor* visitor) override;

  LValue* value;
  Expression* expression;
};
