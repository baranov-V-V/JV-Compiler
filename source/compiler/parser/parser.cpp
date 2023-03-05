// A Bison parser, made by GNU Bison 3.5.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hpp"


// Unqualified %code blocks.
#line 21 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"

  #include "driver.hpp"
  #include "location.hh"

  #include "../ast/core/ast_node.hpp"
  #include "../ast/core/basic_list.hpp"
  #include "../ast/core/binary_operations.hpp"
  #include "../ast/declarations/class_declaration_list.hpp"
  #include "../ast/declarations/class_declaration.hpp"
  #include "../ast/declarations/declaration_list.hpp"
  #include "../ast/declarations/declaration.hpp"
  #include "../ast/declarations/method_declaration.hpp"
  #include "../ast/declarations/variable_declaration.hpp"

  #include "../ast/expressions/binary_op_expression.hpp"
  #include "../ast/expressions/bool_expression.hpp"
  #include "../ast/expressions/identifier_expression.hpp"
  #include "../ast/expressions/integer_expression.hpp"
  #include "../ast/expressions/not_expression.hpp"

  #include "../ast/program/main_class.hpp"
  #include "../ast/program/program.hpp"

  #include "../ast/statements/assignment_statement.hpp"
  #include "../ast/statements/if_else_statement.hpp"
  #include "../ast/statements/if_statement.hpp"
  #include "../ast/statements/print_statement.hpp"
  #include "../ast/statements/return_statement.hpp"
  #include "../ast/statements/statement_list.hpp"
  #include "../ast/statements/statement_list_statement.hpp"
  #include "../ast/statements/statement.hpp"
  #include "../ast/statements/while_statement.hpp"
  #include "../ast/statements/local_variable_statement.hpp"

  #include "../ast/types/integer.hpp"
  #include "../ast/types/type.hpp"

  static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
    return scanner.ScanToken();
  }

#line 87 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 178 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 53: // expr
        value.YY_MOVE_OR_COPY< Expression* > (YY_MOVE (that.value));
        break;

      case 51: // local_variable_statement
        value.YY_MOVE_OR_COPY< LocalVariableStatement* > (YY_MOVE (that.value));
        break;

      case 48: // main_class
        value.YY_MOVE_OR_COPY< MainClass* > (YY_MOVE (that.value));
        break;

      case 47: // program
        value.YY_MOVE_OR_COPY< Program* > (YY_MOVE (that.value));
        break;

      case 50: // statement
        value.YY_MOVE_OR_COPY< Statement* > (YY_MOVE (that.value));
        break;

      case 52: // statement_list
        value.YY_MOVE_OR_COPY< StatementList* > (YY_MOVE (that.value));
        break;

      case 49: // variable_declaration
        value.YY_MOVE_OR_COPY< VariableDeclaration* > (YY_MOVE (that.value));
        break;

      case 3: // "+"
      case 4: // "-"
      case 5: // "*"
      case 6: // "/"
      case 7: // "=="
      case 8: // "!="
      case 9: // "<"
      case 10: // ">"
      case 11: // "||"
      case 12: // "&&"
      case 13: // "%"
      case 45: // "number"
      case 54: // integer_literal
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 44: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 53: // expr
        value.move< Expression* > (YY_MOVE (that.value));
        break;

      case 51: // local_variable_statement
        value.move< LocalVariableStatement* > (YY_MOVE (that.value));
        break;

      case 48: // main_class
        value.move< MainClass* > (YY_MOVE (that.value));
        break;

      case 47: // program
        value.move< Program* > (YY_MOVE (that.value));
        break;

      case 50: // statement
        value.move< Statement* > (YY_MOVE (that.value));
        break;

      case 52: // statement_list
        value.move< StatementList* > (YY_MOVE (that.value));
        break;

      case 49: // variable_declaration
        value.move< VariableDeclaration* > (YY_MOVE (that.value));
        break;

      case 3: // "+"
      case 4: // "-"
      case 5: // "*"
      case 6: // "/"
      case 7: // "=="
      case 8: // "!="
      case 9: // "<"
      case 10: // ">"
      case 11: // "||"
      case 12: // "&&"
      case 13: // "%"
      case 45: // "number"
      case 54: // integer_literal
        value.move< int > (YY_MOVE (that.value));
        break;

      case 44: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 53: // expr
        value.copy< Expression* > (that.value);
        break;

      case 51: // local_variable_statement
        value.copy< LocalVariableStatement* > (that.value);
        break;

      case 48: // main_class
        value.copy< MainClass* > (that.value);
        break;

      case 47: // program
        value.copy< Program* > (that.value);
        break;

      case 50: // statement
        value.copy< Statement* > (that.value);
        break;

      case 52: // statement_list
        value.copy< StatementList* > (that.value);
        break;

      case 49: // variable_declaration
        value.copy< VariableDeclaration* > (that.value);
        break;

      case 3: // "+"
      case 4: // "-"
      case 5: // "*"
      case 6: // "/"
      case 7: // "=="
      case 8: // "!="
      case 9: // "<"
      case 10: // ">"
      case 11: // "||"
      case 12: // "&&"
      case 13: // "%"
      case 45: // "number"
      case 54: // integer_literal
        value.copy< int > (that.value);
        break;

      case 44: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 53: // expr
        value.move< Expression* > (that.value);
        break;

      case 51: // local_variable_statement
        value.move< LocalVariableStatement* > (that.value);
        break;

      case 48: // main_class
        value.move< MainClass* > (that.value);
        break;

      case 47: // program
        value.move< Program* > (that.value);
        break;

      case 50: // statement
        value.move< Statement* > (that.value);
        break;

      case 52: // statement_list
        value.move< StatementList* > (that.value);
        break;

      case 49: // variable_declaration
        value.move< VariableDeclaration* > (that.value);
        break;

      case 3: // "+"
      case 4: // "-"
      case 5: // "*"
      case 6: // "/"
      case 7: // "=="
      case 8: // "!="
      case 9: // "<"
      case 10: // ">"
      case 11: // "||"
      case 12: // "&&"
      case 13: // "%"
      case 45: // "number"
      case 54: // integer_literal
        value.move< int > (that.value);
        break;

      case 44: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 53: // expr
        yylhs.value.emplace< Expression* > ();
        break;

      case 51: // local_variable_statement
        yylhs.value.emplace< LocalVariableStatement* > ();
        break;

      case 48: // main_class
        yylhs.value.emplace< MainClass* > ();
        break;

      case 47: // program
        yylhs.value.emplace< Program* > ();
        break;

      case 50: // statement
        yylhs.value.emplace< Statement* > ();
        break;

      case 52: // statement_list
        yylhs.value.emplace< StatementList* > ();
        break;

      case 49: // variable_declaration
        yylhs.value.emplace< VariableDeclaration* > ();
        break;

      case 3: // "+"
      case 4: // "-"
      case 5: // "*"
      case 6: // "/"
      case 7: // "=="
      case 8: // "!="
      case 9: // "<"
      case 10: // ">"
      case 11: // "||"
      case 12: // "&&"
      case 13: // "%"
      case 45: // "number"
      case 54: // integer_literal
        yylhs.value.emplace< int > ();
        break;

      case 44: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 148 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Program* > () = new Program(yystack_[0].value.as < MainClass* > ()); driver.SetProgram(yylhs.value.as < Program* > ()); }
#line 846 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 3:
#line 152 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < MainClass* > () = new MainClass(yystack_[2].value.as < StatementList* > ()); }
#line 852 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 4:
#line 178 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < VariableDeclaration* > () = new VariableDeclaration(yystack_[1].value.as < std::string > ()); }
#line 858 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 5:
#line 182 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = yystack_[0].value.as < LocalVariableStatement* > (); }
#line 864 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 6:
#line 184 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = new StatementListStatement(yystack_[1].value.as < StatementList* > ()); }
#line 870 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 7:
#line 186 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = new IfElseStatement(yystack_[4].value.as < Expression* > (), yystack_[2].value.as < Statement* > (), yystack_[0].value.as < Statement* > ()); }
#line 876 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 8:
#line 188 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = new IfStatement(yystack_[2].value.as < Expression* > (), yystack_[0].value.as < Statement* > ()); }
#line 882 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 9:
#line 190 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = new WhileStatement(yystack_[2].value.as < Expression* > (), yystack_[0].value.as < Statement* > ()); }
#line 888 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 10:
#line 192 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = new PrintStatement(yystack_[2].value.as < Expression* > ()); }
#line 894 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 11:
#line 194 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Statement* > () = new AssignmentStatement(yystack_[3].value.as < std::string > (), yystack_[1].value.as < Expression* > ()); }
#line 900 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 12:
#line 198 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < LocalVariableStatement* > () = new LocalVariableStatement(yystack_[0].value.as < VariableDeclaration* > ()); }
#line 906 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 13:
#line 202 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < StatementList* > () = new StatementList(yystack_[0].value.as < Statement* > ()); }
#line 912 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 14:
#line 204 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < StatementList* > () = yystack_[1].value.as < StatementList* > (); yylhs.value.as < StatementList* > ()->Add(yystack_[0].value.as < Statement* > ()); }
#line 918 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 15:
#line 208 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Expression* > () = yystack_[1].value.as < Expression* > (); }
#line 924 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 16:
#line 210 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::PLUS, yystack_[0].value.as < Expression* > ());}
#line 930 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 17:
#line 212 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::MINUS, yystack_[0].value.as < Expression* > ());}
#line 936 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 18:
#line 214 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::MUL, yystack_[0].value.as < Expression* > ());}
#line 942 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 19:
#line 216 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::DIV, yystack_[0].value.as < Expression* > ());}
#line 948 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 20:
#line 218 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::EQUAL, yystack_[0].value.as < Expression* > ());}
#line 954 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 21:
#line 220 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::NEQUAL, yystack_[0].value.as < Expression* > ());}
#line 960 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 22:
#line 222 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::LESS, yystack_[0].value.as < Expression* > ());}
#line 966 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 23:
#line 224 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::GREATER, yystack_[0].value.as < Expression* > ());}
#line 972 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 24:
#line 226 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::OR, yystack_[0].value.as < Expression* > ());}
#line 978 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 25:
#line 228 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::AND, yystack_[0].value.as < Expression* > ());}
#line 984 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 26:
#line 230 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  {yylhs.value.as < Expression* > () = new BinOpExpression(yystack_[2].value.as < Expression* > (), BinOperation::PERCENT, yystack_[0].value.as < Expression* > ());}
#line 990 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 27:
#line 232 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Expression* > () = new IdentifierExpression(yystack_[0].value.as < std::string > ()); }
#line 996 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 28:
#line 234 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Expression* > () = new IntegerExpression(yystack_[0].value.as < int > ()); }
#line 1002 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 29:
#line 236 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Expression* > () = new TrueExpression(); }
#line 1008 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 30:
#line 238 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Expression* > () = new FalseExpression(); }
#line 1014 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 31:
#line 240 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < Expression* > () = new NotExpression(yystack_[0].value.as < Expression* > ()); }
#line 1020 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 32:
#line 243 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 1026 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;

  case 33:
#line 245 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"
  { yylhs.value.as < int > () = -yystack_[0].value.as < int > (); }
#line 1032 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"
    break;


#line 1036 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -30;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -15,   -29,    22,   -30,     5,   -30,    -3,    -5,    -9,    10,
      25,    41,    39,    40,    40,    45,    46,    48,    21,    52,
     -30,   -30,   -30,    -4,    35,    -2,    -2,    -2,    49,    -2,
      51,   -30,   -30,    24,    -2,    -2,   -30,   -30,   -30,   -30,
     104,   -30,   119,   134,   -30,    82,   -30,   -30,   175,   149,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    40,    40,    50,   -30,   -30,    13,    13,    57,    57,
     175,   175,   186,   186,     0,     0,   164,    47,   -30,   -30,
      40,   -30
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,     5,     0,     0,     0,     0,     0,     0,     0,
       0,    14,     6,     0,     0,     0,    29,    30,    27,    32,
       0,    28,     0,     0,     4,     0,     3,    33,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     8,     9,    10,
       0,     7
  };

  const signed char
  parser::yypgoto_[] =
  {
     -30,   -30,   -30,   -30,   -23,   -30,    64,    -6,   -30
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     2,     3,    20,    21,    22,    23,    40,    41
  };

  const signed char
  parser::yytable_[] =
  {
      31,    31,    33,    50,    51,    52,    53,    54,    55,    56,
      57,     1,    34,    60,    35,     4,    14,    30,    52,    53,
      42,    43,     5,    45,    15,     6,    60,    16,    48,    49,
      36,    37,     8,     7,     9,    10,    17,    18,    77,    78,
      19,    11,    38,    39,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    14,    32,    81,    12,    13,
      14,    25,    26,    15,    27,    28,    16,    29,    15,    47,
      60,    16,    46,    44,    79,    17,    18,    80,    24,    19,
      17,    18,     0,     0,    19,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,    61,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,    62,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,    63,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,    65,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    50,    51,
      52,    53,     0,     0,    56,    57,     0,     0,    60,    50,
      51,    52,    53,     0,     0,     0,     0,     0,     0,    60
  };

  const signed char
  parser::yycheck_[] =
  {
      23,    24,     4,     3,     4,     5,     6,     7,     8,     9,
      10,    26,    14,    13,    16,    44,    20,    21,     5,     6,
      26,    27,     0,    29,    28,    20,    13,    31,    34,    35,
      32,    33,    37,    36,    43,    25,    40,    41,    61,    62,
      44,    16,    44,    45,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    20,    21,    80,    17,    20,
      20,    16,    16,    28,    16,    44,    31,    15,    28,    45,
      13,    31,    21,    24,    24,    40,    41,    30,    14,    44,
      40,    41,    -1,    -1,    44,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     3,     4,
       5,     6,    -1,    -1,     9,    10,    -1,    -1,    13,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    13
  };

  const signed char
  parser::yystos_[] =
  {
       0,    26,    47,    48,    44,     0,    20,    36,    37,    43,
      25,    16,    17,    20,    20,    28,    31,    40,    41,    44,
      49,    50,    51,    52,    52,    16,    16,    16,    44,    15,
      21,    50,    21,     4,    14,    16,    32,    33,    44,    45,
      53,    54,    53,    53,    24,    53,    21,    45,    53,    53,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    17,    17,    17,    24,    17,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    50,    50,    24,
      30,    50
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    46,    47,    48,    49,    50,    50,    50,    50,    50,
      50,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,    13,     3,     1,     3,     7,     5,     5,
       5,     4,     1,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     2,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"==\"", "\"!=\"", "\"<\"", "\">\"", "\"||\"", "\"&&\"",
  "\"%\"", "\"!\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"",
  "\"}\"", "\".\"", "\",\"", "\";\"", "\"main\"", "\"class\"", "\"this\"",
  "\"if\"", "\"new\"", "\"else\"", "\"while\"", "\"true\"", "\"false\"",
  "\"extends\"", "\"assert\"", "\"public\"", "\"static\"", "\"return\"",
  "\"length\"", "\"println\"", "\"int\"", "\"bool\"", "\"void\"",
  "\"identifier\"", "\"number\"", "$accept", "program", "main_class",
  "variable_declaration", "statement", "local_variable_statement",
  "statement_list", "expr", "integer_literal", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   147,   147,   151,   177,   181,   183,   185,   187,   189,
     191,   193,   197,   201,   203,   207,   209,   211,   213,   215,
     217,   219,   221,   223,   225,   227,   229,   231,   233,   235,
     237,   239,   242,   244
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1493 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.cpp"

#line 247 "/home/viktor/repos/MiniCompiler/source/compiler/parser/parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
