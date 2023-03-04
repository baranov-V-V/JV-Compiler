#include "local_variable_statement.hpp"

LocalVariableStatement::LocalVariableStatement(
    VariableDeclaration* var_decl) : variable_declaration(var_decl) {}

void LocalVariableStatement::Accept(Visitor* visitor) {
  //variable_declaration.ccept
}

LocalVariableStatement::~LocalVariableStatement() {
  delete variable_declaration;
}
