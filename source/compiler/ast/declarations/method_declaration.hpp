#pragma once

#include <string>

#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/visitors/visitor.hpp"

class MethodDeclaration: public Declaration {
 public:
  MethodDeclaration(const std::string& identifier, StatementList* statement_list);
  virtual ~MethodDeclaration() override;

  virtual void Accept(Visitor* visitor) override;
  //type
  //formals
  StatementList* statement_list;
};