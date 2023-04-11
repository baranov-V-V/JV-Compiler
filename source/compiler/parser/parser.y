%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include <string>
  
  #include "../ast/forward_declaration.hpp"

  #include "../types/type.hpp"
  #include "../types/type_factory.hpp"

  class Type;
  class ArgEntry;
  class Scanner;
  class Driver;
}

%define parse.trace
%define parse.error verbose

%code {
  #include "driver.hpp"
  #include "location.hh"

  #include "../ast/core/ast_node.hpp"
  #include "../ast/core/basic_list.hpp"
  #include "../ast/core/binary_operations.hpp"

  #include "../ast/declarations/class_declaration.hpp"
  #include "../ast/declarations/class_declaration_list.hpp"
  #include "../ast/declarations/declaration.hpp"
  #include "../ast/declarations/declaration_list.hpp"
  #include "../ast/declarations/field_declaration.hpp"
  #include "../ast/declarations/method_declaration.hpp"
  #include "../ast/declarations/variable_declaration.hpp"

  #include "../ast/expressions/array_idx_expression.hpp"
  #include "../ast/expressions/bool_expression.hpp"
  #include "../ast/expressions/compare_op_expression.hpp"
  #include "../ast/expressions/expression.hpp"
  #include "../ast/expressions/float_expression.hpp"
  #include "../ast/expressions/identifier_expression.hpp"
  #include "../ast/expressions/integer_expression.hpp"
  #include "../ast/expressions/length_expression.hpp"
  #include "../ast/expressions/logic_op_expression.hpp"
  #include "../ast/expressions/math_op_expression.hpp"
  #include "../ast/expressions/method_call_expression.hpp"
  #include "../ast/expressions/new_array_expression.hpp"
  #include "../ast/expressions/new_class_expression.hpp"
  #include "../ast/expressions/not_expression.hpp"
  #include "../ast/expressions/this_expression.hpp"

  #include "../ast/functional/comma_expression_list.hpp"
  #include "../ast/functional/method_call.hpp"

  #include "../ast/program/main_class.hpp"
  #include "../ast/program/program.hpp"

  #include "../ast/statements/assert_statement.hpp"
  #include "../ast/statements/assignment_statement.hpp"
  #include "../ast/statements/if_else_statement.hpp"
  #include "../ast/statements/if_statement.hpp"
  #include "../ast/statements/local_variable_statement.hpp"
  #include "../ast/statements/mehtod_call_statement.hpp"
  #include "../ast/statements/print_statement.hpp"
  #include "../ast/statements/return_statement.hpp"
  #include "../ast/statements/statement_list.hpp"
  #include "../ast/statements/statement_list_statement.hpp"
  #include "../ast/statements/statement.hpp"
  #include "../ast/statements/while_statement.hpp"

  #include "../ast/values/array_l_value.hpp"
  #include "../ast/values/field_l_value.hpp"
  #include "../ast/values/identifier_l_value.hpp"
  #include "../ast/values/l_value.hpp"

  #include "../types/type.hpp"
  #include "../types/type_factory.hpp"

  static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
    return scanner.ScanToken();
  }
}

%lex-param { Scanner& scanner }
%lex-param { Driver& driver }
%parse-param { Scanner& scanner }
%parse-param { Driver& driver }

%locations

%define api.token.prefix {TOK_}

%token
  END 0 "end of file"
  <int> PLUS "+"
  <int> MINUS "-"
  <int> MUL "*"
  <int> DIV "/"
  <int> EQUAL "=="
  <int> NEQUAL "!="
  <int> LESS "<"
  <int> GREATER ">"
  <int> OR "||"
  <int> AND "&&"
  <int> PERCENT "%"
    
%token
  NOT "!"
  ASSIGN "="
  LPAREN "("
  RPAREN ")"
  LSQUARE "["
  RSQUARE "]"
  LBRACKET "{"
  RBRACKET "}"
  DOT "."
  COLON ","
  SEMICOLON ";"

%token
  MAIN "main"
  CLASS "class"
  THIS "this"
  IF "if"
  NEW "new"
  ELSE "else"
  WHILE "while"
  TRUE "true"
  FALSE "false"
  EXTENDS "extends"
  ASSERT "assert"
  PUBLIC "public"
  STATIC "static"
  RETURN "return"
  LENGTH "length"
  PRINT "println"
  INT "int"
  BOOL "bool"
  FLOAT "float"
  VOID "void"
  <std::string> IDENTIFIER "identifier"
  <int> NUMBER "number"
  <float> FLOAT_NUMBER "float_number"


%nterm <Program*> program
%nterm <MainClass*> main_class
%nterm <ClassDeclaration*> class_declaration
%nterm <ClassDeclarationList*> class_declaration_list
%nterm <Declaration*> class_member_declaration
%nterm <DeclarationList*> declaration_list
%nterm <MethodDeclaration*> method_declaration
%nterm <VariableDeclaration*> variable_declaration
%nterm <FieldDeclaration*> field_declaration

%nterm <Expression*> expr
%nterm <CommaExpressionList*> comma_expr_list
%nterm <ArgEntry> formals
%nterm <std::vector<ArgEntry>> comma_formals_list
%nterm <MethodCall*> method_call

%nterm <SharedPtr<Type>> type
%nterm <SharedPtr<Type>> simple_type
%nterm <SharedPtr<Type>> array_type

%nterm <LValue*> lvalue

%nterm <Statement*> statement
%nterm <LocalVariableStatement*> local_variable_statement
%nterm <StatementList*> statement_list

%nterm <int> integer_literal

%left "&&" "||";
%left "==" "!=" "!";
%left "<" ">";
%left "+" "-";
%left "*" "/" "%";
%left "(";

%%
%start program;

program : main_class 
  { $$ = new Program($1, new ClassDeclarationList()); driver.SetProgram($$); $$->location = driver.GetLocation(); }
        | main_class class_declaration_list
  { $$ = new Program($1, $2); driver.SetProgram($$); $$->location = driver.GetLocation(); }
;

main_class: "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statement_list "}" "}"
  { $$ = new MainClass($11); $$->location = driver.GetLocation(); }
;

class_declaration_list: class_declaration 
  { $$ = new ClassDeclarationList($1); $$->location = driver.GetLocation(); }
                      | class_declaration_list class_declaration
  { $$ = $1; $$->Add($2); }
;

class_declaration: "class" "identifier" "{" declaration_list "}" 
  { $$ = new ClassDeclaration(TypeFactory::GetClassTy(Symbol($2, driver.GetLocation())), $4); $$->location = driver.GetLocation(); }
                 | "class" "identifier" "extends" "identifier" "{" declaration_list "}"
  { $$ = new ClassDeclaration(TypeFactory::GetClassTy(Symbol($2, driver.GetLocation())), $6); $$->location = driver.GetLocation(); }
;

declaration_list : class_member_declaration
  { $$ = new DeclarationList($1); $$->location = driver.GetLocation(); }
                 | declaration_list class_member_declaration
  { $$ = $1; $$->Add($2); }
;

class_member_declaration: field_declaration
  { $$ = $1; }
  			 | method_declaration
  { $$ = $1; }

field_declaration: type "identifier" ";"
  { $$ = new FieldDeclaration($1, Symbol($2, driver.GetLocation())); $$->location = driver.GetLocation(); }
;

variable_declaration: type "identifier" ";"
  { $$ = new VariableDeclaration($1, Symbol($2, driver.GetLocation())); $$->location = driver.GetLocation(); }
;

//TODO (make new rule)
//  		    | type "identifier" "=" expr ";"
  //  { $$ = new VariableDeclaration($1, Symbol($2, driver.GetLocation())); $$->location = driver.GetLocation(); }

method_declaration: type "identifier" "(" comma_formals_list ")" "{" statement_list "}"
  { $$ = new MethodDeclaration(Symbol($2, driver.GetLocation()), TypeFactory::GetMethodTy(Symbol($2, driver.GetLocation()), $4, $1), $7); $$->location = driver.GetLocation(); }
;

comma_formals_list: formals
  { $$ = std::vector<ArgEntry>(); $$.push_back($1); }
                  | comma_formals_list "," formals
  { $$ = $1; $$.push_back($3); }
                  |
  { /* empty */ $$ = $$ = std::vector<ArgEntry>(); }
;

formals: type "identifier" { $$ = ArgEntry($1, Symbol($2, driver.GetLocation())); }
;

type: simple_type { $$ = $1; }
    | array_type  { $$ = $1;  }
;

array_type: simple_type "[" "]"
  { $$ = TypeFactory::GetArrayTy($1); }
;

simple_type: "int"
  { $$ = TypeFactory::GetIntTy(); }
           | "bool"
  { $$ = TypeFactory::GetBoolTy(); }
           | "void"
  { $$ = TypeFactory::GetVoidTy(); }
           | "float"
  { $$ = TypeFactory::GetFloatTy(); }
           | "identifier"
  { $$ = TypeFactory::GetClassTy(Symbol($1, driver.GetLocation())); }
;

statement: local_variable_statement
  { $$ = $1; }
         | "{" statement_list "}"
  { $$ = new StatementListStatement($2); $$->location = driver.GetLocation(); }
         | "if"  "(" expr ")" "{" statement_list "}" "else" "{" statement_list "}"
  { $$ = new IfElseStatement($3, $6, $10); $$->location = driver.GetLocation(); }
         | "if"  "(" expr ")" "{" statement_list "}"
  { $$ = new IfStatement($3, $6); $$->location = driver.GetLocation(); }
         | "while"  "(" expr ")" "{" statement_list "}"
  { $$ = new WhileStatement($3, $6); $$->location = driver.GetLocation(); }
         | "println"  "(" expr ")" ";"
  { $$ = new PrintStatement($3); $$->location = driver.GetLocation(); }
         | lvalue "=" expr ";"
  { $$ = new AssignmentStatement($1, $3); $$->location = driver.GetLocation(); }
  	     | method_call ";"
  { $$ = new MethodCallStatement($1); $$->location = driver.GetLocation(); }
  	     | "return" expr ";"
  { $$ = new ReturnStatement($2); $$->location = driver.GetLocation(); }
;

//neeeeed expression instead of identifier
lvalue: "identifier"
  { $$ = new IdentifierLValue(Symbol($1, driver.GetLocation())); $$->location = driver.GetLocation(); }
      | "identifier" "[" expr "]"
  { $$ = new ArrayLValue(Symbol($1, driver.GetLocation()), $3); $$->location = driver.GetLocation(); }
;

local_variable_statement: variable_declaration
  { $$ = new LocalVariableStatement($1); $$->location = driver.GetLocation(); }
;

statement_list: statement 
  { $$ = new StatementList($1); $$->location = driver.GetLocation(); }
              | statement_list statement 
  { $$ = $1; $$->Add($2); }
              |
  { /* empty */ $$ = new StatementList(); $$->location = driver.GetLocation(); }
;

//need rule for this.x
expr: "(" expr ")"
  { $$ = $2; }
      | expr "+"    expr
  {$$ = new MathOpExpression($1, MathOperation::PLUS, $3); $$->location = driver.GetLocation(); }
      | expr "-"    expr
  {$$ = new MathOpExpression($1, MathOperation::MINUS, $3); $$->location = driver.GetLocation(); }
      | expr "*"    expr
  {$$ = new MathOpExpression($1, MathOperation::MUL, $3); $$->location = driver.GetLocation(); }
      | expr "/"    expr
  {$$ = new MathOpExpression($1, MathOperation::DIV, $3); $$->location = driver.GetLocation(); }
      | expr "=="   expr
  {$$ = new CompareOpExpression($1, CompareOperation::EQUAL, $3); $$->location = driver.GetLocation(); }
      | expr "!="   expr
  {$$ = new CompareOpExpression($1, CompareOperation::NEQUAL, $3); $$->location = driver.GetLocation(); }
      | expr "<"    expr
  {$$ = new CompareOpExpression($1, CompareOperation::LESS, $3); $$->location = driver.GetLocation(); }
      | expr ">"    expr
  {$$ = new CompareOpExpression($1, CompareOperation::GREATER, $3); $$->location = driver.GetLocation(); }
      | expr "||"   expr
  {$$ = new LogicOpExpression($1, LogicOperation::OR, $3); $$->location = driver.GetLocation(); }
      | expr "&&"   expr
  {$$ = new LogicOpExpression($1, LogicOperation::AND, $3); $$->location = driver.GetLocation(); }
      | expr "%"    expr
  {$$ = new MathOpExpression($1, MathOperation::PERCENT, $3); $$->location = driver.GetLocation(); }
      | "identifier"
  { $$ = new IdentifierExpression(Symbol($1, driver.GetLocation())); $$->location = driver.GetLocation(); }
      | integer_literal
  { $$ = new IntegerExpression($1); $$->location = driver.GetLocation(); }
      | "true"
  { $$ = new TrueExpression(); $$->location = driver.GetLocation(); }
      | "false"
  { $$ = new FalseExpression(); $$->location = driver.GetLocation(); }
      | "!" expr
  { $$ = new NotExpression($2); $$->location = driver.GetLocation(); }
      | expr "[" expr "]"
  { $$ = new ArrayIdxExpression($1, $3); $$->location = driver.GetLocation(); }
      | expr "." "length"
  { $$ = new LengthExpression($1); $$->location = driver.GetLocation(); }
      | "new" simple_type "[" expr "]"
  { $$ = new NewArrayExpression($2, $4); $$->location = driver.GetLocation(); }
      | "new" "identifier" "(" ")"
  { $$ = new NewClassExpression(TypeFactory::GetClassTy(Symbol($2))); $$->location = driver.GetLocation(); }
      | "this"
  { $$ = new ThisExpression(); $$->location = driver.GetLocation(); }
      | method_call
  { $$ = new MethodCallExpression($1); $$->location = driver.GetLocation(); }

method_call: expr "." "identifier" "(" comma_expr_list ")"
  { $$ = new MethodCall(Symbol($3, driver.GetLocation()), $1, $5); $$->location = driver.GetLocation(); }
           | expr "." "identifier" "(" ")"
  { $$ = new MethodCall(Symbol($3, driver.GetLocation()), $1, new CommaExpressionList()); $$->location = driver.GetLocation(); }
;

comma_expr_list: expr
  { $$ = new CommaExpressionList($1); $$->location = driver.GetLocation(); }
               | comma_expr_list "," expr
  { $$ = $1; $$->Add($3); }
;

integer_literal : "number" 
  { $$ = $1; }
        	| "-" "number"
  { $$ = -$2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << "parser error! " << l << ": " << m << '\n';
}
