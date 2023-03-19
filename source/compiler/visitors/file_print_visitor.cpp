#include "file_print_visitor.hpp"
#include "compiler/ast/ast.hpp"

#define PRINT_TABBED(str) PrintTabs(); stream << str << std::endl;
#define EXECUTE_TABBED(code) PrintTabs(); code
#define VISIT_TABBED(code) ++tabs_count; code --tabs_count;

void FilePrintVisitor::Print(const std::string& filename, Program* program) {
  tabs_count = 0;
  stream.open(filename);
  Visit(program);
  stream.close();
}

void FilePrintVisitor::Visit(Program* program) {
  PRINT_TABBED("Program")
  VISIT_TABBED(
    program->main_class->Accept(this);
  )
}

void FilePrintVisitor::Visit(MainClass* main_class) {
  PRINT_TABBED("Main Class")
  VISIT_TABBED(
    main_class->statement_list->Accept(this);
  )
}

void FilePrintVisitor::Visit(ClassDeclaration* class_declaration) {
  return;
}

void FilePrintVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  PRINT_TABBED("Class Declaration List")
  VISIT_TABBED(
    class_declaration_list->Accept(this);
  )
}

void FilePrintVisitor::Visit(DeclarationList* declaration_list) {
  PRINT_TABBED("Decaration List")
  VISIT_TABBED(
    declaration_list->Accept(this);
  )
}

void FilePrintVisitor::Visit(MethodDeclaration* method_declaration) {
  return;
}

void FilePrintVisitor::Visit(VariableDeclaration* variable_declaration) {
  EXECUTE_TABBED(
    stream << "Decl int " << variable_declaration->identifier << std::endl;
  )
}

void FilePrintVisitor::Visit(BinOpExpression* expression) {
  PRINT_TABBED("Bin Op Expr")
  VISIT_TABBED(
    expression->lhs->Accept(this);
    PRINT_TABBED(bin_ops[(int) expression->operation])
    expression->rhs->Accept(this);
  )
}

void FilePrintVisitor::Visit(TrueExpression* expression) {
  PRINT_TABBED("True Expr")
}

void FilePrintVisitor::Visit(FalseExpression* expression) {
  PRINT_TABBED("False Expr")
}

void FilePrintVisitor::Visit(IdentifierExpression* expression) {
  EXECUTE_TABBED(
    stream << "Identifier Expr " << expression->identifier << std::endl;
  )
}

void FilePrintVisitor::Visit(IntegerExpression* expression) {
  EXECUTE_TABBED(
    stream << "Integer Expr \"" << expression->value << "\"" << std::endl;
  )
}

void FilePrintVisitor::Visit(NotExpression* expression) {
  PRINT_TABBED("Not Expr")
  VISIT_TABBED(
    expression->expression->Accept(this);
  )
}

void FilePrintVisitor::Visit(AssignmentStatement* statement) {
  PRINT_TABBED("Assignment Expr")
  VISIT_TABBED(
    EXECUTE_TABBED(
      stream << "Identifier "<< statement->identifier << std::endl;
    )
    statement->expression->Accept(this);
  )
}

void FilePrintVisitor::Visit(IfElseStatement* statement) {
  PRINT_TABBED("If Else Statement")
  VISIT_TABBED(
    statement->cond_expression->Accept(this);
    statement->statement_true->Accept(this);
    statement->statement_false->Accept(this);
  )
}

void FilePrintVisitor::Visit(IfStatement* statement) {
  PRINT_TABBED("If Statement")
  VISIT_TABBED(
    statement->cond_expression->Accept(this);
    statement->statement_true->Accept(this);
  )
}

void FilePrintVisitor::Visit(PrintStatement* statement) {
  PRINT_TABBED("Print Statement")
  VISIT_TABBED(
    statement->expression->Accept(this);
  )
}

void FilePrintVisitor::Visit(ReturnStatement* statement) {
  PRINT_TABBED("Return Statement")
  VISIT_TABBED(
    statement->expression->Accept(this);
  )
}

void FilePrintVisitor::Visit(WhileStatement* statement) {
  PRINT_TABBED("While Statement")
  VISIT_TABBED(
    statement->cond_expression->Accept(this);
    statement->statement->Accept(this);
  )
}

void FilePrintVisitor::Visit(StatementList* statement) {
  PRINT_TABBED("Statement List")
  VISIT_TABBED(
    statement->Accept(this);
  )
}

void FilePrintVisitor::Visit(LocalVariableStatement* statement) {
  PRINT_TABBED("Local Var Decl")
  VISIT_TABBED(
    statement->variable_declaration->Accept(this);
  )
}

void FilePrintVisitor::Visit(StatementListStatement* statement) {
  PRINT_TABBED("Statement List Statement")
  VISIT_TABBED(
    statement->statement_list->Accept(this);
  )
}

void FilePrintVisitor::PrintTabs() {
  for (int i = 0; i < tabs_count; ++i) {
    stream << "\t";
  };
}

#undef PRINT_TABBED
#undef VISIT_TABBED