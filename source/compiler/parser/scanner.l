%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hpp"
    #include "parser.hpp"

    #define TOKEN yy::parser::token
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
float [0-9]+\.[0-9]+
blank [ \t\r]

%{
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%
%{
  yy::location& loc = driver.location;
  loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"="         return yy::parser::make_ASSIGN      (loc);
"&&"        return yy::parser::make_AND         (TOKEN::TOK_AND, loc);
"||"        return yy::parser::make_OR          (TOKEN::TOK_OR, loc);
"<"         return yy::parser::make_LESS        (TOKEN::TOK_LESS, loc);
">"         return yy::parser::make_GREATER     (TOKEN::TOK_GREATER, loc);
"=="        return yy::parser::make_EQUAL       (TOKEN::TOK_EQUAL, loc);
"!="        return yy::parser::make_NEQUAL      (TOKEN::TOK_NEQUAL, loc);
"+"         return yy::parser::make_PLUS        (TOKEN::TOK_PLUS, loc);
"-"         return yy::parser::make_MINUS       (TOKEN::TOK_MINUS, loc);
"*"         return yy::parser::make_MUL         (TOKEN::TOK_MUL, loc);
"/"         return yy::parser::make_DIV         (TOKEN::TOK_DIV, loc);
"%"         return yy::parser::make_PERCENT     (TOKEN::TOK_PERCENT, loc);
"!"         return yy::parser::make_NOT         (loc);
"("         return yy::parser::make_LPAREN      (loc);
")"         return yy::parser::make_RPAREN      (loc);
"["         return yy::parser::make_LSQUARE     (loc);
"]"         return yy::parser::make_RSQUARE     (loc);
"{"         return yy::parser::make_LBRACKET    (loc);
"}"         return yy::parser::make_RBRACKET    (loc);
"."         return yy::parser::make_DOT         (loc);
","         return yy::parser::make_COLON       (loc);
";"         return yy::parser::make_SEMICOLON   (loc);
"new"       return yy::parser::make_NEW         (loc);
"this"      return yy::parser::make_THIS        (loc);
"true"      return yy::parser::make_TRUE        (loc);
"false"     return yy::parser::make_FALSE       (loc);
"if"        return yy::parser::make_IF          (loc);
"else"      return yy::parser::make_ELSE        (loc);
"while"     return yy::parser::make_WHILE       (loc);
"assert"    return yy::parser::make_ASSERT      (loc);
"class"     return yy::parser::make_CLASS       (loc);
"extends"   return yy::parser::make_EXTENDS     (loc);
"public"    return yy::parser::make_PUBLIC      (loc);
"static"    return yy::parser::make_STATIC      (loc);
"return"    return yy::parser::make_RETURN      (loc);
"int"       return yy::parser::make_INT         (loc);
"bool"      return yy::parser::make_BOOL        (loc);
"float"     return yy::parser::make_FLOAT       (loc);
"void"      return yy::parser::make_VOID        (loc);
"main"      return yy::parser::make_MAIN        (loc);
"println"   return yy::parser::make_PRINT       (loc);
"length"    return yy::parser::make_LENGTH      (loc);
{int}       return make_NUMBER(yytext, loc);
{float}     return make_FLOAT(yytext, loc);
{id}        return yy::parser::make_IDENTIFIER(yytext, loc);
.          {
              throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  }
  return yy::parser::make_NUMBER((int) n, loc);
}

yy::parser::symbol_type make_FLOAT(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  float n = atof(s.c_str());
  return yy::parser::make_FLOAT(n, loc);
}