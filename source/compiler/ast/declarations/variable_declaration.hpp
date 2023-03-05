#pragma once

#include <string>

#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/visitors/visitor.hpp"

class VariableDeclaration: public Declaration {
 public:
  VariableDeclaration(const std::string& identifier);
  virtual ~VariableDeclaration() = default;
  
  void Accept(Visitor* visitor) override;

  //type always int
};
