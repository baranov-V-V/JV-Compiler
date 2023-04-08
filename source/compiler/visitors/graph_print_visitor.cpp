#include "compiler/core/logger.hpp"

#include "graph_print_visitor.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

// path = file.png
void GraphPrintVisitor::Print(const std::filesystem::path& filename,
                              Program* program) {

  std::filesystem::path dot_file(filename);
  //TODO(smth mayber wrong here)
  dot_file.replace_extension("dot");
  std::string command = "dot -Tpng " + dot_file.string() + " -o " + filename.string(); 
  
  LOG_DEBUG("dot file : {}", dot_file.string());
  LOG_DEBUG("png file : {}", filename.string());
  
  std::filesystem::create_directories(dot_file.parent_path()); 
  fmt::ostream tmp_ostream = fmt::output_file(dot_file.c_str());
  stream = &tmp_ostream;

  fict_node_no = 10000;
  Visit(program);
  stream = nullptr;
  tmp_ostream.close();

  LOG_INFO("graphing done with code: {}", system(command.c_str()));
}

void GraphPrintVisitor::Visit(Program* program) {
  stream->print("digraph Ast {{\n");
  stream->print("node [shape=\"record\", style=\"filled\"];\n");
  stream->print("\tnode{} [label =\"<first> Program\", color=\"grey14\", fillcolor=\"gray38\"]\n", reinterpret_cast<void*>(program));
  program->main_class->Accept(this);
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\"];\n", reinterpret_cast<void*>(program), reinterpret_cast<void*>(program->main_class));
  stream->print("}}");
}

void GraphPrintVisitor::Visit(MainClass* main_class) {
  stream->print("\tnode{} [label =\"<first> MainClass\", color=\"grey14\", fillcolor=\"gray38\"]\n", reinterpret_cast<void*>(main_class));
  main_class->statement_list->Accept(this);
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\"];\n", reinterpret_cast<void*>(main_class), reinterpret_cast<void*>(main_class->statement_list));
}

void GraphPrintVisitor::Visit(ClassDeclaration* class_declaration) {
  return;
}

void GraphPrintVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  return;
}

void GraphPrintVisitor::Visit(DeclarationList* declaration_list) {

}

void GraphPrintVisitor::Visit(MethodDeclaration* method_declaration) {}

void GraphPrintVisitor::Visit(VariableDeclaration* variable_declaration) {}

/*
void GraphPrintVisitor::Visit(BinOpExpression* expression) {
  stream->print("\tnode{} [label =\"<first> {}\", color=\"grey14\", fillcolor=\"gray38\"]\n", GetBinOp(expression->operation), reinterpret_cast<void*>(expression));
  expression->lhs->Accept(this);
  expression->rhs->Accept(this);
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\"];\n", reinterpret_cast<void*>(expression), reinterpret_cast<void*>(expression->lhs));
  stream->print("\t\tnode{}:se -> node{} [color=\"navy\"];\n", reinterpret_cast<void*>(expression), reinterpret_cast<void*>(expression->rhs));
}
*/

void GraphPrintVisitor::Visit(TrueExpression* expression) {
  stream->print("\tnode{} [label =\"<first> False\", color=\"grey14\", fillcolor=\"olivedrab3\"]\n", reinterpret_cast<void*>(expression));
}

void GraphPrintVisitor::Visit(FalseExpression* expression) {
  stream->print("\tnode{} [label =\"<first> True\", color=\"grey14\", fillcolor=\"orangered2\"]\n", reinterpret_cast<void*>(expression));
}

void GraphPrintVisitor::Visit(IdentifierExpression* expression) {
  stream->print("\tnode{} [label =\"<first> [int] {}\", color=\"grey14\", fillcolor=\"lightyellow\"]\n", reinterpret_cast<void*>(expression), expression->identifier.name);
}

void GraphPrintVisitor::Visit(IntegerExpression* expression) {
  stream->print("\tnode{} [label =\"<first> [int] {}\", color=\"grey14\", fillcolor=\"skyblue1\"]\n", reinterpret_cast<void*>(expression), expression->value);
}

void GraphPrintVisitor::Visit(NotExpression* expression) {
  
}

void GraphPrintVisitor::Visit(AssignmentStatement* statement) {
  stream->print("\tnode{} [label =\"<first> Assignment \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  /*


  stream->print("\tnode{} [label =\"<first> [Id] {} \", color=\"grey14\", fillcolor=\"gray38\"]\n",\
    (void*) &statement->identifier, statement->identifier
  );

  statement->expression->Accept(this);
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\"];\n",
    (void*) statement, (void*) &statement->identifier
  );
  */
  stream->print("\t\tnode{}:se -> node{} [color=\"navy\"];\n",
    (void*) statement, (void*) &statement->expression
  );
}

void GraphPrintVisitor::Visit(IfElseStatement* statement) {
  stream->print("\tnode{} [label =\"<first> IfElse \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  statement->cond_expression->Accept(this);
  statement->statement_true->Accept(this);
  statement->statement_false->Accept(this);
  stream->print("\t\tnode{}:s -> node{} [color=\"navy\" label = \"cond\"];\n",
    (void*) statement, (void*) statement->cond_expression
  );
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\" label = \"true\"];\n",
    (void*) statement, (void*) statement->statement_true
  );
  stream->print("\t\tnode{}:se -> node{} [color=\"navy\" label = \"false\"];\n",
    (void*) statement, (void*) statement->statement_false
  );
}

void GraphPrintVisitor::Visit(IfStatement* statement) {
  stream->print("\tnode{} [label =\"<first> If \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  statement->cond_expression->Accept(this);
  statement->statement_true->Accept(this);
  stream->print("\t\tnode{}:s -> node{} [color=\"navy\" label = \"cond\"];\n",
    (void*) statement, (void*) statement->cond_expression
  );
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\" label = \"true\"];\n",
    (void*) statement, (void*) statement->statement_true
  );
}

void GraphPrintVisitor::Visit(PrintStatement* statement) {
  stream->print("\tnode{} [label =\"<first> Print \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  statement->expression->Accept(this);
  stream->print("\t\tnode{}:s -> node{} [color=\"navy\"];\n",
    (void*) statement, (void*) statement->expression
  );
}

void GraphPrintVisitor::Visit(ReturnStatement* statement) {
  stream->print("\tnode{} [label =\"<first> Return \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  statement->expression->Accept(this);
  stream->print("\t\tnode{}:s -> node{} [color=\"navy\"];\n",
    (void*) statement, (void*) statement->expression
  );
}

void GraphPrintVisitor::Visit(WhileStatement* statement) {
  stream->print("\tnode{} [label =\"<first> While \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  statement->cond_expression->Accept(this);
  statement->statement->Accept(this);
  stream->print("\t\tnode{}:se -> node{} [color=\"navy\" label = \"cond\"];\n",
    (void*) statement, (void*) statement->cond_expression
  );
  stream->print("\t\tnode{}:sw -> node{} [color=\"navy\" label = \"stmt\"];\n",
    (void*) statement, (void*) statement->statement
  );
}

void GraphPrintVisitor::Visit(StatementList* statement) {
  stream->print("\tnode{} [label =\"<first> StmtList \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  
  int curr_no = fict_node_no;
  MakeFictListNodes(statement->elements.size());
  
  if (curr_no = fict_node_no) {
    stream->print("\tnode{} [label =\"<first> Empty \", color=\"grey14\", fillcolor=\"gray38\"]\n",
      fict_node_no
    );
    ++fict_node_no;
    return;
  }

  


}

void GraphPrintVisitor::Visit(LocalVariableStatement* statement) {
  stream->print("\tnode{} [label =\"<first> Local Var Decl |<second> [Id] {}\", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement, statement->variable_declaration->identifier.name
  );
}

void GraphPrintVisitor::Visit(StatementListStatement* statement) {
  stream->print("\tnode{} [label =\"<first> StmtListStmt \", color=\"grey14\", fillcolor=\"gray38\"]\n",
    (void*) statement
  );
  Visit(statement->statement_list);
  stream->print("\t\tnode{}:s -> node{} [color=\"navy\"];\n",
    (void*) statement, (void*) statement->statement_list
  );
}

void GraphPrintVisitor::MakeFictListNodes(int count) {
  for (int i = 0; i < count; ++i) {
    stream->print("\tnode{} [label =\"<first> Fict \", color=\"grey14\", fillcolor=\"gray38\"]\n",
      fict_node_no
    );
    ++fict_node_no;
  }
}

void GraphPrintVisitor::Visit(LogicOpExpression* expression) {

}

void GraphPrintVisitor::Visit(CompareOpExpression* expression) {

}

void GraphPrintVisitor::Visit(MathOpExpression* expression) {

}

void GraphPrintVisitor::Visit(ArrayIdxExpression *expression) {

}

void GraphPrintVisitor::Visit(LengthExpression *expression) {

}

void GraphPrintVisitor::Visit(MethodCallExpression *expression) {

}

void GraphPrintVisitor::Visit(NewArrayExpression *expression) {

}

void GraphPrintVisitor::Visit(NewClassExpression *expression) {

}

void GraphPrintVisitor::Visit(ThisExpression *expression) {

}

void GraphPrintVisitor::Visit(CommaExpressionList *program) {

}

void GraphPrintVisitor::Visit(MethodCall *program) {

}

void GraphPrintVisitor::Visit(AssertStatement *statement) {

}

void GraphPrintVisitor::Visit(MethodCallStatement *statement) {

}

void GraphPrintVisitor::Visit(ArrayLValue *statement) {

}

void GraphPrintVisitor::Visit(FieldLValue *statement) {

}

void GraphPrintVisitor::Visit(IdentifierLValue *statement) {

}

void GraphPrintVisitor::Visit(FieldDeclaration* declaration) {

}
