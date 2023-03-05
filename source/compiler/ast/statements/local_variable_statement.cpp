#include "local_variable_statement.hpp"

LocalVariableStatement::LocalVariableStatement(
    VariableDeclaration* var_decl) : variable_declaration(var_decl) {}

LocalVariableStatement::~LocalVariableStatement() {
  delete variable_declaration;
}

void LocalVariableStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

