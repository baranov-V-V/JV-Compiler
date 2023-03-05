#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/declarations/class_declaration.hpp"
#include "compiler/visitors/visitor.hpp"

class ClassDeclarationList: public BasicList<ClassDeclaration> {
 public:
  ClassDeclarationList() = default;
  ClassDeclarationList(ClassDeclaration* class_decl);
  virtual ~ClassDeclarationList() = default;

  virtual void Accept(Visitor* visitor) override;
};
