#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/core/binary_operations.hpp"

#include "compiler/ast/declarations/class_declaration_list.hpp"
#include "compiler/ast/declarations/class_declaration.hpp"
#include "compiler/ast/declarations/declaration_list.hpp"
#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/ast/declarations/method_declaration.hpp"
#include "compiler/ast/declarations/variable_declaration.hpp"

#include "compiler/ast/expressions/binary_op_expression.hpp"
#include "compiler/ast/expressions/bool_expression.hpp"
#include "compiler/ast/expressions/identifier_expression.hpp"
#include "compiler/ast/expressions/integer_expression.hpp"
#include "compiler/ast/expressions/not_expression.hpp"

#include "compiler/ast/program/main_class.hpp"
#include "compiler/ast/program/program.hpp"

#include "compiler/ast/statements/assignment_statement.hpp"
#include "compiler/ast/statements/if_else_statement.hpp"
#include "compiler/ast/statements/if_statement.hpp"
#include "compiler/ast/statements/print_statement.hpp"
#include "compiler/ast/statements/return_statement.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/ast/statements/statement_list_statement.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/statements/while_statement.hpp"
#include "compiler/ast/statements/local_variable_statement.hpp"

#include "compiler/ast/types/integer.hpp"
#include "compiler/ast/types/type.hpp"