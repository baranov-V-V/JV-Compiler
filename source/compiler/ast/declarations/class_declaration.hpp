#pragma once

#include <string>
#include <memory>

#include "compiler/ast/declarations/declaration_list.hpp"
#include "compiler/visitors/visitor.hpp"

class ClassDeclaration: public AstNode {
 public:
  ClassDeclaration(const std::string& class_name, DeclarationList* decl_list);
  virtual ~ClassDeclaration();

  virtual void Accept(Visitor* visitor) override;

  std::string class_name;
  DeclarationList* declaration_list;
};
