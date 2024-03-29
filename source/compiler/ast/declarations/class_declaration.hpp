#pragma once

#include <string>
#include <memory>

#include "compiler/ast/declarations/declaration_list.hpp"
#include "compiler/visitors/visitor.hpp"
#include "compiler/types/class_type.hpp"

class ClassDeclaration: public AstNode {
 public:
  ClassDeclaration(SharedPtr<ClassType> class_type, DeclarationList* decl_list);
  virtual ~ClassDeclaration();

  virtual void Accept(Visitor* visitor) override;

  SharedPtr<ClassType> class_type;
  DeclarationList* declaration_list;
};
