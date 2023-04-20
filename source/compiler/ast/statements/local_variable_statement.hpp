#pragma once

#include <string>

#include "ast/statements/statement.hpp"
#include "ast/declarations/variable_declaration.hpp"
#include "visitors/visitor.hpp"

class LocalVariableStatement : public Statement {
 public:
  LocalVariableStatement(VariableDeclaration* var_decl);

  virtual ~LocalVariableStatement() override;

  void Accept(Visitor* visitor) override;

  VariableDeclaration* variable_declaration;
};