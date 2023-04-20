#pragma once

#include <string>
#include <memory>

#include "ast/declarations/declaration_list.hpp"
#include "visitors/visitor.hpp"
#include "types/class_type.hpp"

class ClassDeclaration : public AstNode {
 public:
  ClassDeclaration(SharedPtr<ClassType> class_type, DeclarationList* decl_list);

  virtual ~ClassDeclaration();

  virtual void Accept(Visitor* visitor) override;

  SharedPtr<ClassType> class_type;
  DeclarationList* declaration_list;
};
