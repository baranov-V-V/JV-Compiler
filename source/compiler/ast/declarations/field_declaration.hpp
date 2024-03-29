#pragma once

#include "declaration.hpp"
#include "types/type.hpp"
#include "compiler/util/symbol.hpp"

class FieldDeclaration : public Declaration {
 public:
  FieldDeclaration(SharedPtr<Type> type, const Symbol& identifier);
  ~FieldDeclaration() override = default;

  void Accept(Visitor* visitor) override;

  SharedPtr<Type> type;
};