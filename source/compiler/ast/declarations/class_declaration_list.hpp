#pragma once

#include "ast/core/ast_node.hpp"
#include "ast/declarations/class_declaration.hpp"
#include "visitors/visitor.hpp"

class ClassDeclarationList : public BasicList<ClassDeclaration> {
 public:
  ClassDeclarationList() = default;

  explicit ClassDeclarationList(ClassDeclaration* class_decl);

  ~ClassDeclarationList() override = default;

  void Accept(Visitor* visitor) override;
};
