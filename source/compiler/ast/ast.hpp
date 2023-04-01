#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/core/binary_operations.hpp"

#include "compiler/ast/declarations/class_declaration.hpp"
#include "compiler/ast/declarations/class_declaration_list.hpp"
#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/ast/declarations/declaration_list.hpp"
#include "compiler/ast/declarations/method_declaration.hpp"
#include "compiler/ast/declarations/variable_declaration.hpp"

#include "compiler/ast/expressions/array_idx_expression.hpp"
#include "compiler/ast/expressions/bool_expression.hpp"
#include "compiler/ast/expressions/compare_op_expression.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/ast/expressions/float_expression.hpp"
#include "compiler/ast/expressions/identifier_expression.hpp"
#include "compiler/ast/expressions/integer_expression.hpp"
#include "compiler/ast/expressions/length_expression.hpp"
#include "compiler/ast/expressions/logic_op_expression.hpp"
#include "compiler/ast/expressions/math_op_expression.hpp"
#include "compiler/ast/expressions/method_call_expression.hpp"
#include "compiler/ast/expressions/new_array_expression.hpp"
#include "compiler/ast/expressions/new_class_expression.hpp"
#include "compiler/ast/expressions/not_expression.hpp"
#include "compiler/ast/expressions/this_expression.hpp"

#include "compiler/ast/functional/comma_expression_list.hpp"
#include "compiler/ast/functional/method_call.hpp"

#include "compiler/ast/program/main_class.hpp"
#include "compiler/ast/program/program.hpp"


#include "compiler/ast/statements/assert_statement.hpp"
#include "compiler/ast/statements/assignment_statement.hpp"
#include "compiler/ast/statements/if_else_statement.hpp"
#include "compiler/ast/statements/if_statement.hpp"
#include "compiler/ast/statements/local_variable_statement.hpp"
#include "compiler/ast/statements/mehtod_call_statement.hpp"
#include "compiler/ast/statements/print_statement.hpp"
#include "compiler/ast/statements/return_statement.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/ast/statements/statement_list_statement.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/statements/while_statement.hpp"

#include "compiler/ast/values/array_l_value.hpp"
#include "compiler/ast/values/field_l_value.hpp"
#include "compiler/ast/values/identifier_l_value.hpp"
#include "compiler/ast/values/l_value.hpp"