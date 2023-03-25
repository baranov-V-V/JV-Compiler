#pragma once

#include <map>
#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/program/main_class.hpp"
#include "compiler/ast/declarations/class_declaration_list.hpp"
#include "compiler/visitors/visitor.hpp"
#include "core/compiler.hpp"

class Program: public AstNode {
 public:
  Program(MainClass* main_class, ClassDeclarationList* class_declaration_list);
  Program(MainClass* main_class);
  ~Program() override;

  void Accept(Visitor* visitor) override;

  MainClass*  main_class;
  ClassDeclarationList* class_declaration_list;
};
