#pragma once

enum class BinOperation {
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
  PERCENT,
  NCOUNT
};

enum class CompareOperation {
  EQUAL = 0,
  NEQUAL,
  LESS,
  GREATER,
  NCOUNT
};

enum class LogicOperation {
  OR = 0,
  AND,
  NCOUNT
};

enum class MathOperation {
  PLUS = 0,
  MINUS,
  MUL,
  DIV,
  PERCENT,
  NCOUNT
};

const char* GetMathStrOp(MathOperation bin_op);

const char* GetLogicStrOp(LogicOperation bin_op);

const char* GetCompareStrOp(CompareOperation bin_op);

const char* GetBinOp(BinOperation bin_op);
