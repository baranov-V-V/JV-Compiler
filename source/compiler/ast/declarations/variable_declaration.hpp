#pragma once

#include <string>

#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/visitors/visitor.hpp"
#include "types/type.hpp"

class VariableDeclaration: public Declaration {
 public:
  VariableDeclaration(SharedPtr<Type> type, const Symbol& identifier);
  ~VariableDeclaration() override = default;
  
  void Accept(Visitor* visitor) override;

  SharedPtr<Type> type;
};
