#pragma once

#include <string>

#include "ast/declarations/declaration.hpp"
#include "ast/statements/statement_list.hpp"
#include "visitors/visitor.hpp"
#include "types/type.hpp"
#include "types/method_type.hpp"

class MethodDeclaration : public Declaration {
 public:
  MethodDeclaration(const Symbol& identifier, SharedPtr<MethodType> method_type, StatementList* statement_list);

  ~MethodDeclaration() override;

  void Accept(Visitor* visitor) override;

  SharedPtr<MethodType> method_type;
  StatementList* statement_list;
};