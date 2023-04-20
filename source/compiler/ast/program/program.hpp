#pragma once

#include <map>
#include "ast/core/ast_node.hpp"
#include "ast/program/main_class.hpp"
#include "ast/declarations/class_declaration_list.hpp"

class Visitor;

class Program : public AstNode {
 public:
  Program(MainClass* main_class);

  Program(MainClass* main_class, ClassDeclarationList* class_declaration_list);

  ~Program() override;

  void Accept(Visitor* visitor) override;

  MainClass* main_class;
  ClassDeclarationList* class_declaration_list;
};
