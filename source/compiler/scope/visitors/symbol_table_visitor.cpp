#include "compiler/core/logger.hpp"

#include "symbol_table_visitor.hpp"
#include "compiler/ast/ast.hpp"
#include "class_table_visitor.hpp"
#include "compiler/scope/layers/class_scope_layer.hpp"

SymbolTableVisitor::SymbolTableVisitor() {}

SymbolTable* SymbolTableVisitor::ConstructSymbolTree(Program* program) {
  ScopeLayer* global = new ScopeLayer(nullptr, "global");
  tree = new SymbolLayerTree(global);
  layer_iterator = SymbolLayerTree::Iterator(global);

  ClassTableVisitor class_table_visitor;
  class_table = class_table_visitor.ConstructClassTable(program);

  Visit(program);

  SymbolTable* table = new SymbolTable(global);
  return table;
}

void SymbolTableVisitor::Visit(ClassDeclaration* class_declaration) {
  ScopeGoDownClass(class_declaration->class_type);
  
  //put all fields in class layer
  for (const auto& entry : class_table->GetInfo(class_declaration->class_type).GetAllFields()) {
    
  }

  class_declaration->declaration_list->Accept(this);

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

}

void SymbolTableVisitor::Visit(MathOpExpression* expression) {

}

void SymbolTableVisitor::Visit(MethodCallExpression* expression) {

}

void SymbolTableVisitor::Visit(NewArrayExpression* expression) {

}

void SymbolTableVisitor::Visit(NewClassExpression* expression) {

}

void SymbolTableVisitor::Visit(NotExpression* expression) {
  SharedPtr<Type> type = Accept(expression->expression);

  CheckAndWarn(TypeFactory::GetBoolTy(), type);

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
  SharedPtr<Type> class_type = Accept(call->caller);
  call->expression_list->Accept(this);

  if (!class_type->IsClass()) {
    COMPILER_ERROR("Method Call of a non-class caller with type []", class_type->ToString())
  }

  // rewrite ClassTableWith Symbol
  /*
  //class exists
  if (class_table->GetInfo()) {
  }

  // method exists
  if () {
  }

  // check num args
  if () {
    COMPILER_ERROR("Not enough args")
  }


  // check args types
  for (size_t i = 0; i < num_args; ++i) {
    auto arg_type =
      std::dynamic_pointer_cast<Expression>((*comma_expr_list)[i])->GetType();
    if (arg_type != func_type.arg_types[i]) {
      //CheckAndWarn()
    }
  }
   */
}

void SymbolTableVisitor::Visit(AssertStatement* statement) {
  SharedPtr<Type> type = Accept(statement->expression);
  CheckConvertable(TypeFactory::GetBoolTy(), type);
}

void SymbolTableVisitor::Visit(AssignmentStatement* statement) {
  SharedPtr<Type> lvalue_type = Accept(statement->value);
  SharedPtr<Type> expr_type = Accept(statement->expression);

  // implement
}

void SymbolTableVisitor::Visit(IfElseStatement* statement) {

}

void SymbolTableVisitor::Visit(IfStatement* statement) {

}

void SymbolTableVisitor::Visit(LocalVariableStatement* statement) {

}

void SymbolTableVisitor::Visit(MethodCallStatement* statement) {

}

void SymbolTableVisitor::Visit(PrintStatement* statement) {

}

void SymbolTableVisitor::Visit(ReturnStatement* statement) {

}

void SymbolTableVisitor::Visit(StatementList* statement) {

}

void SymbolTableVisitor::Visit(StatementListStatement* statement) {

}

void SymbolTableVisitor::Visit(WhileStatement* statement) {

}

void SymbolTableVisitor::Visit(ArrayLValue* statement) {

}

void SymbolTableVisitor::Visit(FieldLValue* statement) {

}

void SymbolTableVisitor::Visit(IdentifierLValue* statement) {
  //if (layer_iterator->)
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

void SymbolTableVisitor::CheckConvertable(SharedPtr<Type> to, SharedPtr<Type> from) {
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

void SymbolTableVisitor::CheckRedeclared(const Symbol& symbol) {
  if (layer_iterator->IsDeclaredCurrent(symbol)) {
    //Previous declaration at {}:{} add previous
    COMPILER_ERROR("Variable {} is already declared", symbol.name)
  }
}

void SymbolTableVisitor::CheckAndWarn(SharedPtr<Type> to, SharedPtr<Type> from) {
  CheckConvertable(to, from);
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
