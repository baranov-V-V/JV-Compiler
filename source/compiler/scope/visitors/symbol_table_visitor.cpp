#include "compiler/core/logger.hpp"

#include "symbol_table_visitor.hpp"
#include "compiler/ast/ast.hpp"
#include "class_table_visitor.hpp"

#include "compiler/scope/layers/class_scope_layer.hpp"
#include "types/type_factory.hpp"

SymbolTableVisitor::SymbolTableVisitor() {}

std::unique_ptr<SymbolLayerTree> SymbolTableVisitor::ConstructSymbolTree(Program* program) {

  ClassTableVisitor class_table_visitor;
  tree = std::make_unique<SymbolLayerTree>(class_table_visitor.ConstructClassTable(program));
  layer_iterator = tree->begin();

  //class_table = class_table_visitor.ConstructClassTable(program);

  Visit(program);

  //SymbolTable* table = new SymbolTable(global);
  return std::move(tree);
}

void SymbolTableVisitor::Visit(ClassDeclaration* class_declaration) {
  ScopeGoDownClass(class_declaration->class_type);
  
  //put all fields in class layer
  for (const auto& entry : class_table->GetInfo(class_declaration->class_type).GetAllFields()) {
    CheckRedeclared(entry.second, entry.first);
    layer_iterator->DeclareVariable(entry.first, entry.second);
  }

  /*
  //put all methods in class layer
  for (const auto& entry : class_table->GetInfo(class_declaration->class_type).GetAllMethods()) {
    CheckRedeclared(entry.second, entry.first);
    layer_iterator->DeclareVariable(entry.first, entry.second);
  }
  */

  current_class = class_declaration->class_type;
  Visit(class_declaration->declaration_list);

  ScopeGoUp();
}

void SymbolTableVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  class_declaration_list->Accept(this);
}

void SymbolTableVisitor::Visit(DeclarationList* declaration_list) {
  declaration_list->Accept(this);
}

void SymbolTableVisitor::Visit(MethodDeclaration* method_declaration) {
  ScopeGoDown(method_declaration->method_type->ToString());

  current_method = method_declaration->method_type;

  CheckRedeclared(current_class, Symbol("__this"));
  layer_iterator->DeclareVariable(Symbol("__this"), current_class);

  for (const TypeEntry& entry : method_declaration->method_type->GetArgs()) {
    CheckRedeclared(entry.type, entry.symbol);
    layer_iterator->DeclareVariable(entry.symbol, entry.type);
  }

  method_declaration->statement_list->Accept(this);

  ScopeGoUp();
}

void SymbolTableVisitor::Visit(VariableDeclaration* declaration) {
  CheckRedeclared(declaration->type, declaration->identifier);

  layer_iterator->DeclareVariable(declaration->identifier, declaration->type);
}

void SymbolTableVisitor::Visit(ArrayIdxExpression* expression) {
  SharedPtr<Type> array = Accept(expression->expr);
  SharedPtr<Type> idx = Accept(expression->idx);

  if (!array->IsArray()) {
    COMPILER_ERROR("Index of non-array type: [{}]", array->ToString());
  }

  if (!idx->IsInteger()) {
    COMPILER_ERROR("Index of array expected [int], got: [{}]", idx->ToString());
  }

  stack.Put(std::reinterpret_pointer_cast<ArrayType>(array)->GetElemType());
}

void SymbolTableVisitor::Visit(TrueExpression* expression) {
  stack.Put(TypeFactory::GetBoolTy());
}

void SymbolTableVisitor::Visit(FalseExpression* expression) {
  stack.Put(TypeFactory::GetBoolTy());
}

void SymbolTableVisitor::Visit(CompareOpExpression* expression) {
  SharedPtr<Type> lhs = Accept(expression->lhs);
  CheckTypePrimitive(lhs);

  SharedPtr<Type> rhs = Accept(expression->rhs);
  CheckTypePrimitive(rhs);

  stack.Put(TypeFactory::GetBoolTy());
}

void SymbolTableVisitor::Visit(IdentifierExpression* expression) {
  CheckDeclaredAnywhere(expression->identifier);
  stack.Put(layer_iterator->GetFromAnywhere(expression->identifier)->GetType());
}

void SymbolTableVisitor::Visit(IntegerExpression* expression) {
  stack.Put(TypeFactory::GetIntTy());
}

void SymbolTableVisitor::Visit(LengthExpression* expression) {
  SharedPtr<Type> type = Accept(expression->identifier);

  if (!type->IsArray()) {
    COMPILER_ERROR("Length of non-array type: [{}]", type->ToString());
  }

  stack.Put(TypeFactory::GetIntTy());
}

void SymbolTableVisitor::Visit(LogicOpExpression* expression) {
  SharedPtr<Type> lhs = Accept(expression->lhs);
  SharedPtr<Type> rhs = Accept(expression->rhs);

  CheckTypesAndWarn(TypeFactory::GetBoolTy(), lhs);
  CheckTypesAndWarn(TypeFactory::GetBoolTy(), rhs);

  stack.Put(TypeFactory::GetBoolTy());
}

void SymbolTableVisitor::Visit(MathOpExpression* expression) {
  SharedPtr<Type> lhs = Accept(expression->lhs);
  CheckTypePrimitive(lhs);

  SharedPtr<Type> rhs = Accept(expression->rhs);
  CheckTypePrimitive(rhs);

  //CheckCommonType(lhs, rhs);

  stack.Put(converter.CommonType(lhs, rhs));
}

void SymbolTableVisitor::Visit(MethodCallExpression* expression) {
  expression->call->Accept(this);
}

void SymbolTableVisitor::Visit(NewArrayExpression* expression) {
  SharedPtr<Type> size_type = Accept(expression->size);
  
  if (size_type->IsInteger()) {
    COMPILER_ERROR("In new expression: size of array expected [int], got: [{}]", size_type->ToString())
  }

  stack.Put(TypeFactory::GetArrayTy(expression->type));
}

void SymbolTableVisitor::Visit(NewClassExpression* expression) {
  stack.Put(expression->type);
}

void SymbolTableVisitor::Visit(NotExpression* expression) {
  SharedPtr<Type> type = Accept(expression->expression);

  CheckTypesAndWarn(TypeFactory::GetBoolTy(), type);

  stack.Put(TypeFactory::GetBoolTy());
}

void SymbolTableVisitor::Visit(ThisExpression* expression) {
  ClassScopeLayer* class_scope = layer_iterator->GetClassScope();

  if (class_scope == nullptr) {
    COMPILER_ERROR("Cannot use <this> in static context");
  }

  stack.Put(class_scope->GetType());
}

void SymbolTableVisitor::Visit(MainClass* main_class) {
  main_class->statement_list->Accept(this);
}

void SymbolTableVisitor::Visit(Program* program) {
  ScopeGoDown("main");
  program->main_class->Accept(this);
  ScopeGoUp();

  program->class_declaration_list->Accept(this);
}

void SymbolTableVisitor::Visit(CommaExpressionList* expression_list) {
  expression_list->Accept(this);
}

void SymbolTableVisitor::Visit(MethodCall* call) {
  SharedPtr<Type> type = Accept(call->caller);
  call->expression_list->Accept(this);

  //is class at all
  if (!type->IsClass()) {
    COMPILER_ERROR("Method Call of a non-class caller with type []", type->ToString())
  }

  //has info about this class
  SharedPtr<ClassType> class_type = std::reinterpret_pointer_cast<ClassType>(type);
  if (!class_table->HasInfo(class_type)) {
    COMPILER_ERROR("Method Call of a non-existent class with type {}", class_type->ToString());
  }

  // method exists
  if (!class_table->GetInfo(class_type).HasMethodType(call->function_name)) {
    COMPILER_ERROR("Call of a non-existent method {}", call->function_name.name);
  }

  // check num args
  SharedPtr<MethodType> method_type = class_table->GetInfo(class_type).GetMethodType(call->function_name);
  int args_count = method_type->GetArgsNum();
  if (args_count != call->expression_list->elements.size()) {
    COMPILER_ERROR("Call of method has {} args, expected: {}", call->expression_list->elements.size(), args_count);
  }

  call->expression_list->Accept(this);
  for (int i = args_count - 1; i >= 0; --i) {
    CheckTypesAndWarn(method_type->GetArg(i).type, stack.TopAndPop());
  }

  stack.Put(method_type->GetReturnType());
}

void SymbolTableVisitor::Visit(AssertStatement* statement) {
  SharedPtr<Type> type = Accept(statement->expression);
  CheckTypesConvertable(TypeFactory::GetBoolTy(), type);
}

void SymbolTableVisitor::Visit(AssignmentStatement* statement) {
  SharedPtr<Type> lvalue_type = Accept(statement->value);
  SharedPtr<Type> expr_type = Accept(statement->expression);

  CheckTypesAndWarn(lvalue_type, expr_type);
}

void SymbolTableVisitor::Visit(IfElseStatement* statement) {
  CheckTypesAndWarn(TypeFactory::GetBoolTy(), Accept(statement->cond_expression));

  ScopeGoDown("if");
  statement->statement_true->Accept(this);
  ScopeGoUp();

  ScopeGoDown("else");
  statement->statement_false->Accept(this);
  ScopeGoUp();
}

void SymbolTableVisitor::Visit(IfStatement* statement) {
  CheckTypesAndWarn(TypeFactory::GetBoolTy(), Accept(statement->cond_expression));

  ScopeGoDown("if_only");
  statement->statement_true->Accept(this);
  ScopeGoUp();
}

void SymbolTableVisitor::Visit(LocalVariableStatement* statement) {
  statement->variable_declaration->Accept(this);
}

void SymbolTableVisitor::Visit(MethodCallStatement* statement) {
  statement->call->Accept(this);
  stack.Pop();
}

void SymbolTableVisitor::Visit(PrintStatement* statement) {
  //print only for primitive
  CheckTypePrimitive(Accept(statement->expression));
}

void SymbolTableVisitor::Visit(ReturnStatement* statement) {
  SharedPtr<Type> type = Accept(statement->expression);

  CheckTypesAndWarn(current_method->GetReturnType(), type);
}

void SymbolTableVisitor::Visit(StatementList* statement) {
  statement->Accept(this);
}

void SymbolTableVisitor::Visit(StatementListStatement* statement) {
  ScopeGoDown("stmt_list_stmt");
  statement->statement_list->Accept(this);
  ScopeGoUp();
}

void SymbolTableVisitor::Visit(WhileStatement* statement) {
  ScopeGoDown("while");

  CheckTypesAndWarn(TypeFactory::GetBoolTy(), Accept(statement->cond_expression));
  statement->statement->Accept(this);

  ScopeGoUp();
}

void SymbolTableVisitor::Visit(ArrayLValue* statement) {
  CheckDeclaredAnywhere(statement->identifier);
  SharedPtr<Type> type = layer_iterator->GetFromAnywhere(statement->identifier)->GetType();

  if (!type->IsArray()) {
    COMPILER_ERROR("Operatorp[] of non-array type: [{}]", type->ToString());
  }

  SharedPtr<Type> idx = Accept(statement->idx);

  if (!idx->IsInteger()) {
    COMPILER_ERROR("Index of array expected [int], got: [{}]", idx->ToString());
  }

  SharedPtr<ArrayType> array_type = std::reinterpret_pointer_cast<ArrayType>(type);

  stack.Put(array_type->GetElemType());
}

void SymbolTableVisitor::Visit(FieldLValue* statement) {
  //pass not used for now
}

void SymbolTableVisitor::Visit(IdentifierLValue* statement) {
  CheckDeclaredAnywhere(statement->name);
  SharedPtr<Type> type = layer_iterator->GetFromAnywhere(statement->name)->GetType();

  stack.Put(type);
}

void SymbolTableVisitor::Visit(FieldDeclaration* declaration) {
  //pass, already checked in class_table_visitor
}

void SymbolTableVisitor::ScopeGoUp() {
  layer_iterator.GoUp();
}

void SymbolTableVisitor::ScopeGoDown(const std::string& name) {
  tree->AddLayer(*layer_iterator, name);
  layer_iterator.GoDown();
}

void SymbolTableVisitor::ScopeGoDownClass(SharedPtr<ClassType> type) {
  tree->AddClassLayer(*layer_iterator, type);
  layer_iterator.GoDown();
}

SharedPtr<Type> SymbolTableVisitor::Accept(AstNode* ast_node) {
  ast_node->Accept(this);
  return stack.TopAndPop();
}

void SymbolTableVisitor::CheckTypesConvertable(SharedPtr<Type> to, SharedPtr<Type> from) {
  if (!converter.IsNarrowingConvertable(to, from)) {
    COMPILER_ERROR("Could not convert [{}] to [{}]", from->ToString(), to->ToString())
  }
}

void SymbolTableVisitor::WarnNarrowing(SharedPtr<Type> to, SharedPtr<Type> from) {
  if (!converter.IsConvertable(to, from) &&
      converter.IsNarrowingConvertable(to, from)) {
    COMPILER_WARNING("Narrowing conversion from [{}] to [{}]", from->ToString(), to->ToString())
  }
}

void SymbolTableVisitor::CheckHasCommonType(SharedPtr<Type> lhs,
                                         SharedPtr<Type> rhs) {
  if (!converter.HasCommonType(lhs, rhs)) {
    COMPILER_ERROR("Types [{}], [{}] doesnt have common type", lhs->ToString(), rhs->ToString())
  }
}

void SymbolTableVisitor::CheckTypePrimitive(SharedPtr<Type> type) {
  if (!type->IsPrimitive()) {
    COMPILER_ERROR("Operand is not of primitive type: [{}]", type->ToString());
  }
}

void SymbolTableVisitor::CheckRedeclared(const Symbol& symbol) {
  if (layer_iterator->IsDeclaredCurrent(symbol)) {
    //Previous declaration at {}:{} add previous
    COMPILER_ERROR("Variable \"{}\" has already been declared", symbol.name)
  }
}

void SymbolTableVisitor::CheckTypesAndWarn(SharedPtr<Type> to, SharedPtr<Type> from) {
  CheckTypesConvertable(to, from);
  WarnNarrowing(to, from);
}

void SymbolTableVisitor::CheckRedeclared(const SharedPtr<Type>& type, const Symbol& symbol) {
  if (layer_iterator->IsDeclaredCurrent(symbol)) {
    //Previous declaration at {}:{} add previous
    COMPILER_ERROR("Variable [{}] {} is already declared", type->ToString(), symbol.name)
  }
}

void SymbolTableVisitor::CheckDeclaredAnywhere(const Symbol& symbol) {
  if (!layer_iterator->IsDeclaredAnywhere(symbol)) {
    COMPILER_ERROR("Identifier `{}` is not declared in this scope", symbol.name)
  }
}
