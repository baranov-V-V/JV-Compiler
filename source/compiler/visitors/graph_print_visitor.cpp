#include "compiler/core/logger.hpp"

#include "graph_print_visitor.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

// path = file.png
void GraphPrintVisitor::Print(const std::filesystem::path& filename,
                              Program* program) {

  std::filesystem::path dot_file(filename);

  dot_file.replace_extension("dot");
  std::string command = "dot -Tpng " + dot_file.string() + " -o " + filename.string(); 
  
  LOG_DEBUG("dot file : {}", dot_file.string());
  LOG_DEBUG("png file : {}", filename.string());

  if (!dot_file.parent_path().empty()) {
    std::filesystem::create_directories(dot_file.parent_path());
  }

  fmt::ostream tmp_ostream = fmt::output_file(dot_file.c_str());
  stream = &tmp_ostream;

  fict_node_no = 10000;
  Visit(program);
  stream = nullptr;
  tmp_ostream.close();

  LOG_INFO("graphing done with code: {}", system(command.c_str()));

  //std::filesystem::remove(dot_file);
}

void GraphPrintVisitor::Visit(Program* program) {
  stream->print("digraph Ast {{\n");
  stream->print("node [shape=\"record\", style=\"filled\"];\n");

  PrintNode<void*>("Program", (void*) program);

  program->main_class->Accept(this);
  PrintEdge<void*, void*>((void*) program, (void*) program->main_class);

  if (!program->class_declaration_list->elements.empty()) {
    program->class_declaration_list->Accept(this);
    PrintEdge<void*, void*>((void*) program, (void*) program->class_declaration_list);
  }

  stream->print("}}");
}

void GraphPrintVisitor::Visit(MainClass* main_class) {
  PrintNode<void*>("Main Class", (void*) main_class);

  Visit(main_class->statement_list);

  PrintEdge<void*, void*>((void*) main_class, (void*) main_class->statement_list);
}

void GraphPrintVisitor::Visit(ClassDeclaration* class_declaration) {
  PrintNode<void*>(fmt::format("Class {}", class_declaration->class_type->ToString()), (void*) class_declaration);
  Visit(class_declaration->declaration_list);
  PrintEdge<void*, void*>((void*) class_declaration, (void*) class_declaration->declaration_list);
}

void GraphPrintVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  PrintNode<void*>("Class Declarations", class_declaration_list);
  class_declaration_list->Accept(this);
  for (ClassDeclaration* declaration : class_declaration_list->elements) {
    PrintEdge<void*, void*>((void*) class_declaration_list, (void*) declaration);
  }
}

void GraphPrintVisitor::Visit(DeclarationList* list) {
  PrintList(list, "Decl List");
}

void GraphPrintVisitor::Visit(MethodDeclaration* declaration) {
  PrintNode<void*>(fmt::format("Decl [{}] {}", declaration->method_type->ToString(), declaration->identifier.name),
            declaration);

  Visit(declaration->statement_list);

  PrintEdge<void*, void*>(declaration, declaration->statement_list);
}

void GraphPrintVisitor::Visit(VariableDeclaration* declaration) {
  PrintNode<void*>(fmt::format("Decl [{}] {}", declaration->type->ToString(), declaration->identifier.name), declaration);
}

void GraphPrintVisitor::Visit(TrueExpression* expression) {
  PrintNode<void*>("True", expression);
}

void GraphPrintVisitor::Visit(FalseExpression* expression) {
  PrintNode<void*>("False", expression);
}

void GraphPrintVisitor::Visit(IdentifierExpression* expression) {
  PrintNode<void*>(expression->identifier.name, expression);
}

void GraphPrintVisitor::Visit(IntegerExpression* expression) {
  PrintNode<void*>(fmt::format("{}", expression->value), expression);
}

void GraphPrintVisitor::Visit(NotExpression* expression) {
  PrintNode<void*>("!", expression);

  expression->expression->Accept(this);

  PrintEdge<void*, void*>(expression, expression->expression);
}

void GraphPrintVisitor::Visit(AssignmentStatement* statement) {
  PrintNode<void*>("=", statement);

  statement->expression->Accept(this);
  statement->value->Accept(this);

  PrintEdge<void*, void*>(statement, statement->value, "sw");
  PrintEdge<void*, void*>(statement, statement->expression, "se");
}

void GraphPrintVisitor::Visit(IfElseStatement* statement) {
  PrintNode<void*>("If", statement);

  statement->cond_expression->Accept(this);
  statement->statement_true->Accept(this);
  statement->statement_false->Accept(this);

  //TODO make labels on arrows

  PrintEdge<void*, void*>(statement, statement->cond_expression, "s");
  PrintEdge<void*, void*>(statement, statement->statement_true, "se");
  PrintEdge<void*, void*>(statement, statement->statement_false, "sw");
}

void GraphPrintVisitor::Visit(IfStatement* statement) {
  PrintNode<void*>("If", statement);

  statement->cond_expression->Accept(this);
  statement->statement_true->Accept(this);

  //TODO make labels on arrows

  PrintEdge<void*, void*>(statement, statement->cond_expression, "s");
  PrintEdge<void*, void*>(statement, statement->statement_true, "se");
}

void GraphPrintVisitor::Visit(PrintStatement* statement) {
  PrintNode<void*>("Printf", statement);
  statement->expression->Accept(this);
  PrintEdge<void*, void*>(statement, statement->expression);
}

void GraphPrintVisitor::Visit(ReturnStatement* statement) {
  PrintNode<void*>("Return", statement);
  statement->expression->Accept(this);
  PrintEdge<void*, void*>(statement, statement->expression);
}

void GraphPrintVisitor::Visit(WhileStatement* statement) {
  PrintNode<void*>("While", statement);

  statement->cond_expression->Accept(this);
  statement->statement->Accept(this);

  PrintEdge<void*, void*>(statement, statement->cond_expression, "sw");
  PrintEdge<void*, void*>(statement, statement->statement, "se");
}

void GraphPrintVisitor::Visit(StatementList* statement) {
  PrintList(statement, "Stmt List");
}

void GraphPrintVisitor::Visit(LocalVariableStatement* statement) {
  PrintNode<void*>(fmt::format("Decl [{}] {}",
                        statement->variable_declaration->type->ToString(),
                        statement->variable_declaration->identifier.name), statement);
}

void GraphPrintVisitor::Visit(StatementListStatement* statement) {
  PrintNode<void*>("Stmt List Stmt", statement);

  Visit(statement->statement_list);

  PrintEdge<void*, void*>(statement, statement->statement_list);
}

void GraphPrintVisitor::Visit(LogicOpExpression* expression) {
  PrintNode<void*>(fmt::format("{}", GetLogicStrOp(expression->operation)), expression);

  expression->lhs->Accept(this);
  expression->rhs->Accept(this);

  PrintEdge<void*, void*>(expression, expression->lhs, "se");
  PrintEdge<void*, void*>(expression, expression->rhs, "sw");
}

void GraphPrintVisitor::Visit(CompareOpExpression* expression) {
  PrintNode<void*>(fmt::format("{}", GetCompareStrOp(expression->operation)), expression);

  expression->lhs->Accept(this);
  expression->rhs->Accept(this);

  PrintEdge<void*, void*>(expression, expression->lhs, "se");
  PrintEdge<void*, void*>(expression, expression->rhs, "sw");
}

void GraphPrintVisitor::Visit(MathOpExpression* expression) {
  PrintNode<void*>(fmt::format("{}", GetMathStrOp(expression->operation)), expression);

  expression->lhs->Accept(this);
  expression->rhs->Accept(this);

  PrintEdge<void*, void*>(expression, expression->lhs, "se");
  PrintEdge<void*, void*>(expression, expression->rhs, "sw");
}

void GraphPrintVisitor::Visit(ArrayIdxExpression *expression) {
  PrintNode<void*>("Array operator[]", expression);

  expression->expr->Accept(this);
  expression->idx->Accept(this);

  PrintEdge<void*, void*>(expression, expression->idx, "se");
  PrintEdge<void*, void*>(expression, expression->expr, "sw");
}

void GraphPrintVisitor::Visit(LengthExpression *expression) {
  PrintNode<void*>("Length Expr", expression);

  expression->identifier->Accept(this);

  PrintEdge<void*, void*>(expression, expression->identifier);
}

void GraphPrintVisitor::Visit(MethodCallExpression* expression) {
  PrintNode<void*>("Method Call Expr", expression);
  PrintEdge<void*, void*>(expression, expression->call);
}

void GraphPrintVisitor::Visit(NewArrayExpression* expression) {
  PrintNode<void*>(fmt::format("New {}", expression->type->ToString()), expression);

  expression->size->Accept(this);
  //TODO add Size fict
  PrintEdge<void*, void*>(expression, expression->size);
}

void GraphPrintVisitor::Visit(NewClassExpression* expression) {
  PrintNode<void*>(fmt::format("New {}", expression->type->ToString()), expression);
}

void GraphPrintVisitor::Visit(ThisExpression* expression) {
  PrintNode<void*>("This", expression);
}

void GraphPrintVisitor::Visit(CommaExpressionList* list) {
  PrintList(list, "Comma Expr List", ",");
}

void GraphPrintVisitor::Visit(MethodCall* call) {
  PrintNode<void*>(fmt::format("Call {}", call->function_name.name), call);

  call->caller->Accept(this);
  Visit(call->expression_list);

  PrintEdge<void*, void*>(call, call->caller, "sw");
  PrintEdge<void*, void*>(call, call->expression_list, "se");
}

void GraphPrintVisitor::Visit(AssertStatement* statement) {
  PrintNode<void*>("Assert Stmt", statement);
  PrintEdge<void*, void*>(statement, statement->expression);
}

void GraphPrintVisitor::Visit(MethodCallStatement* statement) {
  PrintNode<void*>("Method Call Stmt", statement);
  PrintEdge<void*, void*>(statement, statement->call);
}

void GraphPrintVisitor::Visit(ArrayLValue* statement) {
  PrintNode<void*>(fmt::format("{}[]", statement->identifier.name), statement);
  PrintEdge<void*, void*>(statement, statement->idx, "se");
}

void GraphPrintVisitor::Visit(FieldLValue *statement) {
  //pass
}

void GraphPrintVisitor::Visit(IdentifierLValue* statement) {
  PrintNode<void*>(statement->name.name, statement);
}

void GraphPrintVisitor::Visit(FieldDeclaration* declaration) {
  PrintNode<void*>(fmt::format("Field [{}] {}", declaration->type->ToString(), declaration->identifier.name),
            (void*) declaration);
}

template<class ListType>
void GraphPrintVisitor::PrintList(ListType* list, const std::string& name, const std::string& delimiter) {
  PrintNode<void*>(name, list);

  if (list->elements.empty()) {
    PrintNode<int>("Empty", fict_node_no);
    PrintEdge<void*, int>(list, fict_node_no);
    ++fict_node_no;
    return;
  }

  list->elements.at(0)->Accept(this);
  PrintEdge<void*, void*>(list, list->elements.at(0), "sw");

  if (list->elements.size() == 1) {
    return;
  }

  PrintNode<int>(delimiter, fict_node_no);
  list->elements.at(1)->Accept(this);
  PrintEdge<int, void*>(fict_node_no, list->elements.at(1), "sw");
  PrintEdge<void*, int>(list, fict_node_no, "se");
  ++fict_node_no;

  for (int i = 2; i < list->elements.size(); ++i) {
    PrintNode<int>(delimiter, fict_node_no);
    list->elements.at(i)->Accept(this);
    PrintEdge<int, void*>(fict_node_no, list->elements.at(i), "sw");
    PrintEdge<int, int>(fict_node_no - 1, fict_node_no, "se");
    ++fict_node_no;
  }
}

template<typename NodeType>
void GraphPrintVisitor::PrintNode(const std::string& name, NodeType node) {
  stream->print("\tnode{} [label =\"<first> {}\", color=\"grey14\", fillcolor=\"gray38\"];\n", node, name);
}

template<typename FromType, typename ToType>
void GraphPrintVisitor::PrintEdge(FromType from, ToType to, const std::string& direction) {
  if (!direction.empty()) {
    stream->print("\t\tnode{}:{} -> node{} [color=\"navy\"];\n", from, direction, to);
  } else {
    stream->print("\t\tnode{} -> node{} [color=\"navy\"];\n", from, to);
  }
}

