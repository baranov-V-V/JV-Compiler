#pragma once

#include <string>

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/declarations/variable_declaration.hpp"
#include "compiler/visitors/visitor.hpp"

class LocalVariableStatement: public Statement {
 public:
  LocalVariableStatement(VariableDeclaration* var_decl);
  virtual ~LocalVariableStatement() override;
  
  void Accept(Visitor* visitor) override;

  VariableDeclaration* variable_declaration;
};