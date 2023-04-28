#include "mehtod_call_statement.hpp"

void MethodCallStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

MethodCallStatement::MethodCallStatement(MethodCall* call) : call(call) {}

MethodCallStatement::~MethodCallStatement() {
  delete call;
}
