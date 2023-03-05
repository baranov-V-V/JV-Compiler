#pragma once

enum BinOperation {  
  PLUS = 0,
  MINUS,
  MUL,
  DIV,
  EQUAL,
  NEQUAL,
  LESS,
  GREATER,
  OR,
  AND,
  PERCENT
};

static const char* bin_ops[] = {
  "+",
  "-",
  "*",
  "\\",
  "==",
  "!=",
  "<",
  ">",
  "||",
  "&&",
  "%"
};
