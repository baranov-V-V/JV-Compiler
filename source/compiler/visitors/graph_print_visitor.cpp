#include "graph_print_visitor.hpp"
#include "compiler/ast/ast.hpp"
#include <iostream>

//path = file.png
void GraphPrintVisitor::Print(const std::filesystem::path& filename,
                              Program* program) {
  std::filesystem::path dot_file(filename);
  dot_file.replace_extension("dot");
  std::string command = "dot -Tpng " + dot_file.string() + " -o " + filename.string(); 
  
  //std::cout << "dot file :" << dot_file.string() << std::endl;
  //std::cout << "png file :" << filename.string() << std::endl;
  
  std::filesystem::create_directories(dot_file.parent_path()); 
  //stream = fmt::output_file(dot_file.c_str());
  Visit(program);
  stream.close();

  //std::cerr << "graphing done with code: " << system(command.c_str());
}

void GraphPrintVisitor::Visit(Program* program) {
  stream.print("digraph structs {{\n");
  stream.print("node [shape=\"record\", style=\"filled\"];\n");
  stream.print("\tnode{} [label =\"<first> Program\", color=\"grey14\", fillcolor=\"gray38\"]\n", reinterpret_cast<void*>(program));
  program->main_class->Accept(this);
  stream.print("\t\tnode{}:sw -> node{} [color=\"navy\"];\n", reinterpret_cast<void*>(program), reinterpret_cast<void*>(program->main_class));
  stream.print("}}");
}

void GraphPrintVisitor::Visit(MainClass* main_class) {
  stream.print("\tnode{} [label =\"<first> MainClass\", color=\"grey14\", fillcolor=\"gray38\"]\n", reinterpret_cast<void*>(main_class));
  main_class->statement_list->Accept(this);
  stream.print("\t\tnode{}:sw -> node{} [color=\"navy\"];\n", reinterpret_cast<void*>(main_class), reinterpret_cast<void*>(main_class->statement_list));
}

void GraphPrintVisitor::Visit(ClassDeclaration* class_declaration) {
  //class_declaration->class_name
}

void GraphPrintVisitor::Visit(ClassDeclarationList* class_declaration_list) {}

void GraphPrintVisitor::Visit(DeclarationList* declaration_list) {}

void GraphPrintVisitor::Visit(MethodDeclaration* method_declaration) {}

void GraphPrintVisitor::Visit(VariableDeclaration* variable_declaration) {}

void GraphPrintVisitor::Visit(BinOpExpression* expression) {}

void GraphPrintVisitor::Visit(TrueExpression* expression) {}

void GraphPrintVisitor::Visit(FalseExpression* expression) {}

void GraphPrintVisitor::Visit(IdentifierExpression* expression) {}

void GraphPrintVisitor::Visit(IntegerExpression* expression) {}

void GraphPrintVisitor::Visit(NotExpression* expression) {}

void GraphPrintVisitor::Visit(AssignmentStatement* statement) {}

void GraphPrintVisitor::Visit(IfElseStatement* statement) {}

void GraphPrintVisitor::Visit(IfStatement* statement) {}

void GraphPrintVisitor::Visit(PrintStatement* statement) {}

void GraphPrintVisitor::Visit(ReturnStatement* statement) {}

void GraphPrintVisitor::Visit(WhileStatement* statement) {}

void GraphPrintVisitor::Visit(StatementList* statement) {}

void GraphPrintVisitor::Visit(LocalVariableStatement* statement) {}

void GraphPrintVisitor::Visit(StatementListStatement* statement) {}
