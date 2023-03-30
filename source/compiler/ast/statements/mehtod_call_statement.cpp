#include "mehtod_call_statement.hpp"

void MehtodCallStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

MehtodCallStatement::MehtodCallStatement(MethodCall* call) : call(call) {}

MehtodCallStatement::~MehtodCallStatement() {
  delete call;
}
