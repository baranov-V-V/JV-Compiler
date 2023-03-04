%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include <string>
  
  #include "../ast/forward_declaration.hpp"

  class Scanner;
  class Driver;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
  #include "driver.hpp"
  #include "location.hh"

  #include "../ast/core/ast_node.hpp"
  #include "../ast/core/basic_list.hpp"
  #include "../ast/core/binary_operations.hpp"
  #include "../ast/declarations/class_declaration_list.hpp"
  #include "../ast/declarations/class_declaration.hpp"
  #include "../ast/declarations/declaration_list.hpp"
  #include "../ast/declarations/declaration.hpp"
  //#include "../ast/declarations/method_declaration.hpp"
  #include "../ast/declarations/variable_declaration.hpp"

  #include "../ast/expressions/binary_op_expression.hpp"
  #include "../ast/expressions/bool_expression.hpp"
  #include "../ast/expressions/identifier_expression.hpp"
  #include "../ast/expressions/integer_expression.hpp"
  #include "../ast/expressions/not_expression.hpp"

  #include "../ast/program/main_class.hpp"
  #include "../ast/program/program.hpp"

  #include "../ast/statements/assignment_statement.hpp"
  #include "../ast/statements/if_else_statement.hpp"
  #include "../ast/statements/if_statement.hpp"
  #include "../ast/statements/print_statement.hpp"
  #include "../ast/statements/return_statement.hpp"
  #include "../ast/statements/statement_list.hpp"
  #include "../ast/statements/statement_list_node.hpp"
  #include "../ast/statements/statement.hpp"
  #include "../ast/statements/while_statement.hpp"
  #include "../ast/statements/local_variable_statement.hpp"

  #include "../ast/types/integer.hpp"
  #include "../ast/types/type.hpp"

  static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
    return scanner.ScanToken();
  }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
  END 0 "end of file"

%token
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
  ASSIGN "="
  NOT "!"
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
  NEW "new"
  THIS "this"
  TRUE "true"
  FALSE "false"
  IF "if"
  ELSE "else"
  WHILE "while"
  ASSERT "assert"
  CLASS "class"
  EXTENDS "extends"
  PUBLIC "public"
  STATIC "static"
  RETURN "return"
  PRINT "print"
  LENGTH "length"

%token
  INT "int"
  BOOL "bool"
  VOID "void"


%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%nterm <int> integer_literal
//%nterm <int> binary_operator

%nterm <Program*> program
%nterm <MainClass*> main_class
%nterm <ClassDeclarationList*> class_declaration_list
%nterm <ClassDeclaration*> class_declaration
%nterm <DeclarationList*> declaration_list
%nterm <Declaration*> declaration
%nterm <VariableDeclaration*> variable_declaration
%nterm <LocalVariableStatement*> local_variable_statement
%nterm <Statement*> statement
%nterm <StatementList*> statement_list
%nterm <StatementListNode*> statement_list_node
%nterm <Expression*> expr

%%
%start program;

program : main_class 
  { $$ = new Program($1); driver.SetProgram($$); }
;

class_declaration_list: class_declaration 
  { $$ = new ClassDeclarationList($1); }
                      | class_declaration_list class_declaration
  { $$ = $1; $$->Add($2); }
;

main_class: "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statement_list "}" "}"
  { $$ = new MainClass($11); }
;

class_declaration: "class" "identifier" "{" declaration_list "}" 
  { $$ = new ClassDeclaration($4); }
                 | "class" "identifier" "extends" "identifier" "{" declaration_list "}"
  { $$ = new ClassDeclaration($6); }
;

statement_list: statement 
  { $$ = new StatementList($1); }
              | statement_list statement 
  { $$ = $1; $$->Add($2); }
;

declaration_list : declaration
  { $$ = DeclarationList($1); }
                 | declaration_list declaration
  { $$ = $1; $$->Add($2); }
;

declaration: variable_declaration
  { $$ = $1; }
;

variable_declaration: "int" "identifier" ";"
  { $$ = new VariableDeclaration($2); }
;

local_variable_statement: variable_declaration
  { $$ = new LocalVariableStatement($1); }
;

statement: local_variable_statement
  { $$ = $1; }
         | "{" statement_list "}"
  { $$ = new StatementListNode($2); }
         | "if"  "(" expr ")" statement
  { $$ = new IfStatement($3, $5); }
         | "if"  "(" expr ")" statement "else" statement
  { $$ = new IfElseStatement($3, $5, $7); }
         | "while" "(" expr ")" statement
  { $$ = new WhileStatement($3, $5); }
         | "print" "(" expr ")" ";"
  { $$ = new PrintStatement($3); }
         | "identifier" "=" expr ";"
  { $$ = new AssignmentStatement($1, $3); }
;


expr  : expr "&&"   expr
  {$$ = new BinOpExpression($1, BinOperation::AND, $3);}
      | expr "||"   expr
  {$$ = new BinOpExpression($1, BinOperation::OR, $3);}
      | expr "<"    expr
  {$$ = new BinOpExpression($1, BinOperation::LESS, $3);}
      | expr ">"    expr
  {$$ = new BinOpExpression($1, BinOperation::GREATER, $3);}
      | expr "=="   expr
  {$$ = new BinOpExpression($1, BinOperation::EQUAL, $3);}
      | expr "!="   expr
  {$$ = new BinOpExpression($1, BinOperation::NEQUAL, $3);}
      | expr "+"    expr
  {$$ = new BinOpExpression($1, BinOperation::PLUS, $3);}
      | expr "-"   expr
  {$$ = new BinOpExpression($1, BinOperation::MINUS, $3);}
      | expr "*"    expr
  {$$ = new BinOpExpression($1, BinOperation::MUL, $3);}
      | expr "/"   expr
  {$$ = new BinOpExpression($1, BinOperation::DIV, $3);}
      | expr "%"   expr
  {$$ = new BinOpExpression($1, BinOperation::PERCENT, $3);}
      | "(" expr ")"
  { $$ = $2; }
      | "identifier"
  { $$ = new IdentifierExpression($1); }
      | integer_literal
  { $$ = new IntegerExpression($1); }
      | "true"
  { $$ = new TrueExpression(); }
      | "false"
  { $$ = new FalseExpression(); }
      | "!" expr
  { $$ = new NotExpression($2); }


integer_literal: "number" 
  { $$ = $1; }
               | "-" "number" 
  { $$ = -$2; };

/*binary_operator : "&&" 
                | "||" 
                | "<" 
                | ">" 
                | "=="
                | "!="
                | "+"  
                | "-"  
                | "*" 
                | "/" 
                | "%";
*/

%left "&&" "||";
%left "==" "!=" "!";
%left "<" ">";
%left "+" "-";
%left "*" "/";

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
