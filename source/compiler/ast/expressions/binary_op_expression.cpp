#include "binary_op_expression.hpp"

BinOpExpression::BinOpExpression(Expression* lhs, BinOperation op,
                                 Expression* rhs) :
  lhs(lhs), rhs(rhs), operation(op) {}

BinOpExpression::~BinOpExpression() {
  delete rhs;
  delete lhs;
}

void BinOpExpression::Accept(Visitor* visitor) {
  return;
}

/*
int BinOpExpr::Eval() const {
  int tmp = 0;

  switch(op) {
    case Operation::OP_AND:     tmp = lhs->Eval() && rhs->Eval(); break;
    case Operation::OP_OR:      tmp = lhs->Eval() || rhs->Eval(); break;
    case Operation::OP_LESS:    tmp = lhs->Eval() <  rhs->Eval(); break;
    case Operation::OP_GREATER: tmp = lhs->Eval() >  rhs->Eval(); break;
    case Operation::OP_EQUAL:   tmp = lhs->Eval() == rhs->Eval(); break;
    case Operation::OP_PLUS:    tmp = lhs->Eval() +  rhs->Eval(); break;
    case Operation::OP_MINUS:   tmp = lhs->Eval() -  rhs->Eval(); break;
    case Operation::OP_STAR:    tmp = lhs->Eval() *  rhs->Eval(); break;
    case Operation::OP_SLASH:   tmp = lhs->Eval() /  rhs->Eval(); break;
    case Operation::OP_RMNDR:   tmp = lhs->Eval() %  rhs->Eval(); break;
    default: break;
  }
    return tmp;
}
*/