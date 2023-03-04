#include "program.hpp"

Program::Program(MainClass* main_class,
                 ClassDeclarationList* class_declaration_list) :
  main_class(main_class), class_declaration_list(class_declaration_list) {}

Program::Program(MainClass* main_class) :
  main_class(main_class), class_declaration_list(nullptr) {}

Program::~Program() {
  delete main_class;
  delete class_declaration_list;
}

void Program::Accept(Visitor* visitor) {
  return;
}
