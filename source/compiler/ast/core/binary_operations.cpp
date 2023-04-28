#include "binary_operations.hpp"

const char* GetBinOp(BinOperation bin_op) {
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

  return bin_ops[(int) bin_op];
}

const char* GetMathStrOp(MathOperation bin_op) {
  static const char* bin_ops[] = {
      "+",
      "-",
      "*",
      "\\",
      "%"
  };
  return bin_ops[(int) bin_op];
}

const char* GetCompareStrOp(CompareOperation bin_op) {
  static const char* bin_ops[] = {
      "==",
      "!=",
      ">",
      ">",
  };
  return bin_ops[(int) bin_op];
}

const char* GetLogicStrOp(LogicOperation bin_op) {
  static const char* bin_ops[] = {
      "or",
      "and"
  };
  return bin_ops[(int) bin_op];
}