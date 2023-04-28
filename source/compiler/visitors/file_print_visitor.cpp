#include "file_print_visitor.hpp"
#include "compiler/ast/ast.hpp"

#define PRINT_TABBED(str) PrintTabs(); stream << str << std::endl;
#define EXECUTE_TABBED(code) PrintTabs(); code
#define VISIT_TABBED(code) ++tabs_count; code --tabs_count;

void FilePrintVisitor::Print(const std::filesystem::path& filename, Program* program) {
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
  PRINT_TABBED("Main ClassRef")
  VISIT_TABBED(
    Visit(main_class->statement_list);
  )
}

void FilePrintVisitor::Visit(ClassDeclaration* class_declaration) {
  PRINT_TABBED("ClassDeclaration")
  VISIT_TABBED(
    EXECUTE_TABBED(stream << "type " << class_declaration->class_type->ToString() << std::endl;)
    class_declaration->declaration_list->Accept(this);
  )
}

void FilePrintVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  PRINT_TABBED("ClassRef Declaration List")
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
  PRINT_TABBED("Method Declaration")
  VISIT_TABBED(
    EXECUTE_TABBED(stream << "type" << (int) method_declaration->method_type->GetReturnType()->GetTypeId() <<
    " " << method_declaration->identifier.name << "()" << std::endl; )
  )
}

void FilePrintVisitor::Visit(VariableDeclaration* variable_declaration) {
  PRINT_TABBED("Variable declaration")
  EXECUTE_TABBED(
    stream << "Decl type(" << (int) variable_declaration->type->GetTypeId() << ") " <<
    variable_declaration->identifier.name << std::endl;
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
    stream << "Identifier Expr " << expression->identifier.name << std::endl;
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
  PRINT_TABBED("Assignment Stmt")
  VISIT_TABBED(
    statement->value->Accept(this);
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

void FilePrintVisitor::Visit(LogicOpExpression* expression) {
  PRINT_TABBED("Logic Op Expr")
  VISIT_TABBED(
      expression->lhs->Accept(this);
      PRINT_TABBED(GetLogicStrOp(expression->operation))
      expression->rhs->Accept(this);
  )
}

void FilePrintVisitor::Visit(CompareOpExpression* expression) {
  PRINT_TABBED("Compare Op Expr")
  VISIT_TABBED(
      expression->lhs->Accept(this);
      PRINT_TABBED(GetCompareStrOp(expression->operation))
      expression->rhs->Accept(this);
  )
}

void FilePrintVisitor::Visit(MathOpExpression* expression) {
  PRINT_TABBED("Math Op Expr")
  VISIT_TABBED(
    expression->lhs->Accept(this);
    PRINT_TABBED(GetMathStrOp(expression->operation))
    expression->rhs->Accept(this);
  )
}

void FilePrintVisitor::Visit(ArrayIdxExpression* expression) {
  PRINT_TABBED("ArrayIdxExpression")
  VISIT_TABBED(
    expression->expr->Accept(this);
    expression->idx->Accept(this);
  )
}

void FilePrintVisitor::Visit(LengthExpression* expression) {
  PRINT_TABBED("LengthExpression")
  VISIT_TABBED(
    expression->identifier->Accept(this);
  )
}

void FilePrintVisitor::Visit(MethodCallExpression* expression) {
  PRINT_TABBED("MethodCallExpression")
  VISIT_TABBED(
    expression->call->Accept(this);
  )
}

void FilePrintVisitor::Visit(NewArrayExpression* expression) {
  PRINT_TABBED("NewArrayExpression")
  VISIT_TABBED(
    EXECUTE_TABBED(
      stream << (int) expression->type.get()->GetTypeId() << std::endl;
    )
    expression->size->Accept(this);
  )
}

void FilePrintVisitor::Visit(NewClassExpression* expression) {
  PRINT_TABBED("NewClassExpression")
  VISIT_TABBED(
    EXECUTE_TABBED(
       stream << expression->type.get()->ToString() << std::endl;
    )
  )
}

void FilePrintVisitor::Visit(ThisExpression* expression) {
  PRINT_TABBED("ThisExpression")
}

void FilePrintVisitor::Visit(CommaExpressionList* program) {
  PRINT_TABBED("CommaExprList")
  VISIT_TABBED(
    program->Accept(this);
  )
}

void FilePrintVisitor::Visit(AssertStatement* statement) {
  PRINT_TABBED("Assert")
  VISIT_TABBED(
    statement->expression->Accept(this);
  )
}

void FilePrintVisitor::Visit(MethodCallStatement* statement) {
  PRINT_TABBED("MethodCallStatement")
  VISIT_TABBED(
    statement->call->Accept(this);
  )
}

void FilePrintVisitor::Visit(MethodCall* program) {
  PRINT_TABBED("MethodCall")
  VISIT_TABBED(
    program->caller->Accept(this);
    EXECUTE_TABBED(stream << program->function_name.name << std::endl;)
    program->expression_list->Accept(this);
  )
}

void FilePrintVisitor::Visit(ArrayLValue* statement) {
  PRINT_TABBED("ArrayLValue")
  VISIT_TABBED(
    EXECUTE_TABBED(stream << statement->identifier.name << std::endl;)
    statement->idx->Accept(this);
  )
}

void FilePrintVisitor::Visit(FieldLValue* statement) {
  PRINT_TABBED("ArrayLValue")
}

void FilePrintVisitor::Visit(IdentifierLValue* statement) {
  PRINT_TABBED("IdLValue")
  VISIT_TABBED(
    EXECUTE_TABBED(stream << statement->name.name << std::endl;)
  )
}

void FilePrintVisitor::Visit(FieldDeclaration* declaration) {
  PRINT_TABBED("Field declaration")
  EXECUTE_TABBED(
    stream << "Decl type(" << (int) declaration->type->GetTypeId() << ") " <<
           declaration << std::endl;
  )
}

#undef PRINT_TABBED
#undef VISIT_TABBED