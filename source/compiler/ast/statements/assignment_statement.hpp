#pragma once

#include <string>

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"
#include "ast/values/l_value.hpp"

class AssignmentStatement: public Statement {
 public:
  AssignmentStatement(LValue* identifier, Expression* expr);
  ~AssignmentStatement() override;

  void Accept(Visitor* visitor) override;

  LValue* value;
  Expression* expression;
};
