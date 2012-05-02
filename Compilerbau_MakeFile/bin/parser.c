
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 7 "src/parser.y"

#include "include/uthash.h";
#include "symtab.h";
#include "ir_code_gen.h";
#include <assert.h>


#define NOT_DEFINED -1
#define GLOBAL 0
#define LOCAL 1
#define PARAMETER 2




/* Line 189 of yacc.c  */
#line 89 "bin/parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DO = 258,
     WHILE = 259,
     IF = 260,
     ELSE = 261,
     INT = 262,
     VOID = 263,
     RETURN = 264,
     COLON = 265,
     COMMA = 266,
     SEMICOLON = 267,
     BRACE_OPEN = 268,
     BRACE_CLOSE = 269,
     ID = 270,
     NUM = 271,
     ASSIGN = 272,
     LOGICAL_OR = 273,
     LOGICAL_AND = 274,
     NE = 275,
     EQ = 276,
     GT = 277,
     GTEQ = 278,
     LSEQ = 279,
     LS = 280,
     SHIFT_RIGHT = 281,
     SHIFT_LEFT = 282,
     MINUS = 283,
     PLUS = 284,
     MUL = 285,
     UNARY_PLUS = 286,
     UNARY_MINUS = 287,
     LOGICAL_NOT = 288,
     PARA_CLOSE = 289,
     PARA_OPEN = 290,
     BRACKET_CLOSE = 291,
     BRACKET_OPEN = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 22 "src/parser.y"

  int 				num;
  char*				id;
  struct varentry 	*var;
  struct funcentry 	*func;
  struct symentry	*sym;
  struct funccallparlist *plist;



/* Line 214 of yacc.c  */
#line 173 "bin/parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 198 "bin/parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   292

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    16,    18,    20,
      22,    24,    28,    31,    36,    38,    46,    55,    60,    66,
      68,    72,    75,    76,    79,    81,    84,    87,    89,    91,
      95,    98,   100,   104,   105,   112,   114,   115,   120,   121,
     122,   130,   131,   140,   144,   148,   152,   155,   159,   163,
     167,   171,   175,   179,   183,   187,   191,   194,   199,   203,
     205,   207,   209,   211,   215,   220,   224
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    40,    41,    -1,    41,    -1,
      43,    12,    -1,    46,    12,    -1,    45,    -1,    12,    -1,
       7,    -1,     8,    -1,    43,    11,    44,    -1,    42,    44,
      -1,    15,    37,    16,    36,    -1,    15,    -1,    42,    15,
      35,    34,    13,    49,    14,    -1,    42,    15,    35,    47,
      34,    13,    49,    14,    -1,    42,    15,    35,    34,    -1,
      42,    15,    35,    47,    34,    -1,    48,    -1,    47,    11,
      48,    -1,    42,    44,    -1,    -1,    49,    50,    -1,    51,
      -1,    43,    12,    -1,    60,    12,    -1,    52,    -1,    56,
      -1,     9,    60,    12,    -1,     9,    12,    -1,    12,    -1,
      13,    49,    14,    -1,    -1,     5,    35,    60,    53,    34,
      54,    -1,    50,    -1,    -1,    50,     6,    55,    50,    -1,
      -1,    -1,     4,    57,    35,    60,    34,    58,    50,    -1,
      -1,     3,    59,    50,     4,    35,    60,    34,    12,    -1,
      60,    17,    60,    -1,    60,    18,    60,    -1,    60,    19,
      60,    -1,    33,    60,    -1,    60,    21,    60,    -1,    60,
      20,    60,    -1,    60,    25,    60,    -1,    60,    24,    60,
      -1,    60,    23,    60,    -1,    60,    22,    60,    -1,    60,
      29,    60,    -1,    60,    28,    60,    -1,    60,    30,    60,
      -1,    28,    60,    -1,    15,    37,    61,    36,    -1,    35,
      60,    34,    -1,    62,    -1,    61,    -1,    16,    -1,    15,
      -1,    15,    35,    34,    -1,    15,    35,    63,    34,    -1,
      63,    11,    60,    -1,    60,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    94,    95,    99,   100,   101,   102,   106,
     107,   111,   126,   151,   165,   182,   194,   211,   224,   242,
     261,   282,   307,   309,   313,   314,   315,   316,   317,   318,
     329,   330,   335,   339,   339,   344,   345,   345,   349,   349,
     349,   350,   350,   354,   355,   356,   357,   358,   359,   360,
     361,   368,   375,   376,   377,   378,   379,   380,   388,   389,
     390,   395,   396,   410,   423,   444,   449
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DO", "WHILE", "IF", "ELSE", "INT",
  "VOID", "RETURN", "COLON", "COMMA", "SEMICOLON", "BRACE_OPEN",
  "BRACE_CLOSE", "ID", "NUM", "ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "NE",
  "EQ", "GT", "GTEQ", "LSEQ", "LS", "SHIFT_RIGHT", "SHIFT_LEFT", "MINUS",
  "PLUS", "MUL", "UNARY_PLUS", "UNARY_MINUS", "LOGICAL_NOT", "PARA_CLOSE",
  "PARA_OPEN", "BRACKET_CLOSE", "BRACKET_OPEN", "$accept", "program",
  "program_element_list", "program_element", "type",
  "variable_declaration", "identifier_declaration", "function_definition",
  "function_declaration", "function_parameter_list", "function_parameter",
  "stmt_list", "stmt", "stmt_block", "stmt_conditional", "$@1",
  "stmt_conditional_r", "$@2", "stmt_loop", "$@3", "$@4", "$@5",
  "expression", "primary", "function_call", "function_call_parameters", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    42,
      42,    43,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      50,    50,    51,    53,    52,    54,    55,    54,    57,    58,
      56,    59,    56,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     1,     1,     1,
       1,     3,     2,     4,     1,     7,     8,     4,     5,     1,
       3,     2,     0,     2,     1,     2,     2,     1,     1,     3,
       2,     1,     3,     0,     6,     1,     0,     4,     0,     0,
       7,     0,     8,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     4,     3,     1,
       1,     1,     1,     3,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     8,     0,     2,     4,     0,     0,     7,
       0,     1,     3,    14,    12,     0,     5,     6,     0,     0,
      14,    11,    17,     0,     0,    19,     0,    22,    21,     0,
      18,    13,     0,    20,    22,    41,    38,     0,     0,    31,
      22,    15,    62,    61,     0,     0,     0,     0,     0,    23,
      24,    27,    28,     0,    60,    59,     0,     0,     0,     0,
      30,     0,     0,     0,     0,    56,    46,     0,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,    33,    29,    32,    63,    66,
       0,    62,     0,    58,    43,    44,    45,    48,    47,    52,
      51,    50,    49,    54,    53,    55,     0,     0,     0,     0,
      64,    57,     0,    39,     0,    65,     0,     0,    35,    34,
       0,    40,    36,    42,     0,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    47,    48,    14,     9,    10,    24,
      25,    32,    49,    50,    51,   108,   119,   124,    52,    58,
     117,    57,    53,    54,    55,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -57
static const yytype_int16 yypact[] =
{
      52,   -57,   -57,   -57,    22,    52,   -57,    15,    36,   -57,
      39,   -57,   -57,    19,   -57,    42,   -57,   -57,    -5,    50,
      41,   -57,    60,    42,    -7,   -57,    53,   -57,   -57,    55,
      86,   -57,    72,   -57,   -57,   -57,   -57,    69,    37,   -57,
     -57,   -57,    32,   -57,   163,   163,   163,    42,    71,   -57,
     -57,   -57,   -57,   185,   -57,   -57,   105,   152,    76,   163,
     -57,   199,   138,   160,   100,   -57,   -57,   213,   -57,   -57,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   -57,   124,   163,    73,   -57,   -57,   -57,    73,
      -6,   -57,    70,   -57,    73,   -10,   102,   262,   262,   106,
     106,   106,   106,    99,    99,   -57,   104,   231,   103,   163,
     -57,   -57,   163,   -57,   152,    73,   249,   152,   142,   -57,
     132,   -57,   -57,   -57,   152,   -57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -57,   -57,   -57,   144,    26,    45,     1,   -57,   -57,   -57,
     129,   -17,   -56,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -38,    98,   -57,   -57
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      61,    83,     1,     2,    29,   109,    65,    66,    67,    72,
      73,    74,    75,    76,    77,    78,    21,    56,    79,    80,
      81,    85,    11,    62,    28,    89,     7,    30,   110,    22,
      13,     7,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,    23,     8,   107,    15,    16,    60,
       8,    17,    42,    43,    18,    23,    19,    20,   118,     1,
       2,   121,     1,     2,     3,    44,    26,    63,   125,    64,
      45,   115,    46,    27,   116,    35,    36,    37,    19,     1,
       2,    38,    15,    68,    39,    40,    41,    42,    43,    31,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    34,
      44,    79,    80,    81,    59,    45,   111,    46,    35,    36,
      37,    84,     1,     2,    38,    91,    43,    39,    40,    82,
      42,    43,    73,    74,    75,    76,    77,    78,   106,    81,
      79,    80,    81,    44,    79,    80,    81,   114,    45,   112,
      46,    35,    36,    37,   123,     1,     2,    38,   122,    12,
      39,    40,    87,    42,    43,    35,    36,    37,    33,     1,
       2,    38,    92,     0,    39,    40,    44,    42,    43,     0,
       0,    45,     0,    46,     0,    42,    43,     0,    42,    43,
      44,     0,     0,     0,     0,    45,     0,    46,    44,     0,
       0,    44,     0,    45,    88,    46,    45,    69,    46,     0,
       0,     0,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    86,     0,    79,    80,    81,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,     0,     0,     0,    93,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,     0,     0,     0,   113,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
       0,     0,     0,   120,    75,    76,    77,    78,     0,     0,
      79,    80,    81
};

static const yytype_int8 yycheck[] =
{
      38,    57,     7,     8,    11,    11,    44,    45,    46,    19,
      20,    21,    22,    23,    24,    25,    15,    34,    28,    29,
      30,    59,     0,    40,    23,    63,     0,    34,    34,    34,
      15,     5,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    18,     0,    84,    11,    12,    12,
       5,    12,    15,    16,    35,    29,    37,    15,   114,     7,
       8,   117,     7,     8,    12,    28,    16,    35,   124,    37,
      33,   109,    35,    13,   112,     3,     4,     5,    37,     7,
       8,     9,    11,    12,    12,    13,    14,    15,    16,    36,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    13,
      28,    28,    29,    30,    35,    33,    36,    35,     3,     4,
       5,    35,     7,     8,     9,    15,    16,    12,    13,    14,
      15,    16,    20,    21,    22,    23,    24,    25,     4,    30,
      28,    29,    30,    28,    28,    29,    30,    34,    33,    35,
      35,     3,     4,     5,    12,     7,     8,     9,     6,     5,
      12,    13,    14,    15,    16,     3,     4,     5,    29,     7,
       8,     9,    64,    -1,    12,    13,    28,    15,    16,    -1,
      -1,    33,    -1,    35,    -1,    15,    16,    -1,    15,    16,
      28,    -1,    -1,    -1,    -1,    33,    -1,    35,    28,    -1,
      -1,    28,    -1,    33,    34,    35,    33,    12,    35,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    12,    -1,    28,    29,    30,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    -1,    -1,    -1,    34,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    -1,    -1,    -1,    34,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      -1,    -1,    -1,    34,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    12,    39,    40,    41,    42,    43,    45,
      46,     0,    41,    15,    44,    11,    12,    12,    35,    37,
      15,    44,    34,    42,    47,    48,    16,    13,    44,    11,
      34,    36,    49,    48,    13,     3,     4,     5,     9,    12,
      13,    14,    15,    16,    28,    33,    35,    42,    43,    50,
      51,    52,    56,    60,    61,    62,    49,    59,    57,    35,
      12,    60,    49,    35,    37,    60,    60,    60,    12,    12,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    28,
      29,    30,    14,    50,    35,    60,    12,    14,    34,    60,
      63,    15,    61,    34,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,     4,    60,    53,    11,
      34,    36,    35,    34,    34,    60,    60,    58,    50,    54,
      34,    50,     6,    12,    55,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 81 "src/parser.y"
    {
		printf("\n\n----------DEBUG printing all functions and variables----------:\n");
		printf("<<----------DEBUG Functions---------->>:\n");
		print_funcs();
		printf("<<----------DEBUG Variables---------->>:\n");
		print_vars();
		printf("<<----------DEBUG IR---------->>:\n");
		debugPrintAllopcodes();
		printf("<<----------DEBUG END---------->>:\n\n\n");
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 106 "src/parser.y"
    {(yyval.id)=integer;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 107 "src/parser.y"
    {(yyval.id)=voidtype;;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 112 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof((yyval.var)));
			assert((yyval.var)!=NULL);
			(yyval.var)->varname=(yyvsp[(3) - (3)].sym)->name;
			if((yyvsp[(3) - (3)].sym)->arrdim>=0){
					(yyval.var)->vartype=1;
					add_var((yyval.var)->varname, (yyval.var)->vartype,(yyvsp[(3) - (3)].sym)->arrdim,GLOBAL,NULL);
				}
				else {
					(yyval.var)->vartype=0;
					add_var((yyval.var)->varname, (yyval.var)->vartype,NOT_DEFINED,GLOBAL,NULL);
				}
			//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 127 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof((yyval.var)));
			assert((yyval.var)!=NULL);
			if((yyvsp[(1) - (2)].id)==voidtype) {
				fprintf(stderr,"Variables can not be of type void (%s).\n",(yyvsp[(2) - (2)].sym)->name);
			} 
			else {
				(yyval.var)->varname=(yyvsp[(2) - (2)].sym)->name;
				if((yyvsp[(2) - (2)].sym)->arrdim>=0){
					(yyval.var)->vartype=1;
					add_var((yyval.var)->varname, (yyval.var)->vartype,(yyvsp[(2) - (2)].sym)->arrdim,GLOBAL,NULL);
				}
				else {
					(yyval.var)->vartype=0;
					add_var((yyval.var)->varname, (yyval.var)->vartype,NOT_DEFINED,GLOBAL,NULL);
				}
				//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
				//printf("DEBUG --- Symboltable: ");
				//print_vars();
			}
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 152 "src/parser.y"
    {
			(yyval.sym)=malloc(sizeof((yyval.sym)));
			assert((yyval.sym)!=NULL);
			if(find_sym((yyvsp[(1) - (4)].id))){
				(yyval.sym)=find_sym((yyvsp[(1) - (4)].id));
				fprintf(stderr,"This Symbol was already defined.(%s)\n",(yyval.sym)->name);
			}	
			else{
				(yyval.sym)->name=(yyvsp[(1) - (4)].id);
				(yyval.sym)->arrdim= (yyvsp[(3) - (4)].num);
				//printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 166 "src/parser.y"
    {
			(yyval.sym)=malloc(sizeof((yyval.sym)));
			assert((yyval.sym)!=NULL);
			if(find_sym((yyvsp[(1) - (1)].id))){
				(yyval.sym)=find_sym((yyvsp[(1) - (1)].id));
				fprintf(stderr,"This Symbol was already defined.(%s)\n",(yyval.sym)->name);
			}	
			else{
				(yyval.sym)->name=(yyvsp[(1) - (1)].id);
				(yyval.sym)->arrdim=NOT_DEFINED;
				//printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 183 "src/parser.y"
    {
			(yyval.func)=malloc(sizeof((yyval.func)));
			assert((yyval.func)!=NULL);
			(yyval.func)->funcname=(yyvsp[(2) - (7)].id);
			(yyval.func)->returntype=(int)(yyvsp[(1) - (7)].id);
			(yyval.func)->dim=0;
			(yyval.func)->arrdim=NOT_DEFINED;
			add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,(yyval.func)->arrdim,NULL);
			gencodeopfunc(opFUNC_DEF, NULL, find_func((yyvsp[(2) - (7)].id)), -1);

		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 195 "src/parser.y"
    {	
			(yyval.func)=find_func("temp1");
			(yyval.func)->dim=count_pars((yyval.func)->funcname);
			(yyval.func)->funcname=(yyvsp[(2) - (8)].id);
			(yyval.func)->returntype=(int)(yyvsp[(1) - (8)].id);
			(yyval.func)->arrdim=NOT_DEFINED;
			add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,(yyval.func)->arrdim,(yyval.func)->var);
			delete_func((yyval.func));
			//$$=find_func("temp1");
			//$$->var=NULL;
			gencodeopfunc(opFUNC_DEF, NULL, find_func((yyvsp[(2) - (8)].id)), -1);
			
		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 212 "src/parser.y"
    {
			(yyval.func)=malloc(sizeof((yyval.func)));
			assert((yyval.func)!=NULL);
			(yyval.func)->funcname=(yyvsp[(2) - (4)].id);
			(yyval.func)->returntype=(int)(yyvsp[(1) - (4)].id);
			(yyval.func)->dim=0;
			(yyval.func)->arrdim=NOT_DEFINED;
			add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,(yyval.func)->arrdim,NULL);
			//printf("DEBUG --- Function was added to Symboltable: %s\n",$$->funcname);
			//printf("DEBUG --- Symboltable: ");
			//print_funcs();
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 225 "src/parser.y"
    {
			(yyval.func)=find_func("temp1");
			(yyval.func)->dim=count_pars((yyval.func)->funcname);
			(yyval.func)->funcname=(yyvsp[(2) - (5)].id);
			(yyval.func)->returntype=(int)(yyvsp[(1) - (5)].id);
			(yyval.func)->arrdim=NOT_DEFINED;
			add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,(yyval.func)->arrdim,(yyval.func)->var);
			delete_func((yyval.func));				//Deletes the temp function
			//$$=find_func("temp1");
			//$$->var=NULL;
			//printf("DEBUG --- Function was added to Symboltable: %s\n",$$->funcname);
			//printf("DEBUG --- Symboltable: ");
			//print_funcs();			
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 243 "src/parser.y"
    {
			(yyval.func)=malloc(sizeof((yyval.func)));
			assert((yyval.func)!=NULL);
			if(!find_func("temp1"))
			{
				add_func("temp1", 0,0,NOT_DEFINED,NULL);
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(1) - (1)].var)->varname, (yyvsp[(1) - (1)].var)->vartype, (yyvsp[(1) - (1)].var)->arrdim);
				//add_var($1->varname, $1->vartype, $1->arrdim,1,0);
			} 
			else 
			{	
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(1) - (1)].var)->varname, (yyvsp[(1) - (1)].var)->vartype, (yyvsp[(1) - (1)].var)->arrdim);
				//add_var($1->varname, $1->vartype, $1->arrdim,1,0);
				
			}
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 262 "src/parser.y"
    {
			(yyval.func)=malloc(sizeof((yyval.func)));
			assert((yyval.func)!=NULL);
			if(!find_func("temp1"))
			{
				add_func("temp1", 0,0,NOT_DEFINED,NULL);
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(3) - (3)].var)->varname, (yyvsp[(3) - (3)].var)->vartype, (yyvsp[(3) - (3)].var)->arrdim);
				//add_var($3->varname, $3->vartype, $3->arrdim,1,0);
			} 
			else 
			{
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(3) - (3)].var)->varname, (yyvsp[(3) - (3)].var)->vartype, (yyvsp[(3) - (3)].var)->arrdim);
				//add_var($3->varname, $3->vartype, $3->arrdim,1,0);
			}
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 283 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof((yyval.var)));
			assert((yyval.var)!=NULL);
			(yyval.var)->varname = (yyvsp[(2) - (2)].sym)->name; 
			if((yyvsp[(1) - (2)].id)==voidtype) { 
				fprintf(stderr,"Function parameters can not be of type void.\n"); 
			} 
			else {
				if((yyvsp[(2) - (2)].sym)->arrdim>=0){
						(yyval.var)->vartype=1;
						(yyval.var)->arrdim=(yyvsp[(2) - (2)].sym)->arrdim;
						//add_funcpar(funcname, $$->name, $$->type, $2->arrdim);
					}
				else {
						(yyval.var)->vartype=0;
						(yyval.var)->arrdim=NOT_DEFINED;
						//add_var($$->varname, $$->vartype,-1);
					}
				}
			//printf("DEBUG --- Symboltable: ");
			//print_all(); 
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 314 "src/parser.y"
    {resetTempCount();;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 315 "src/parser.y"
    {resetTempCount();;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 316 "src/parser.y"
    {resetTempCount();;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 317 "src/parser.y"
    {resetTempCount();;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 318 "src/parser.y"
    {
									if((yyvsp[(2) - (3)].var)->scope!=NULL)
									{
										if((yyvsp[(2) - (3)].var)->vartype==2) //$2->scope->retType
										{
											printf("ERROR: Function was declarad as VOID. It can not return a value. Either use \"RETURN;\" or use type int for the func.\n");
										}
									}
									gencodeop1(opRETURN, (yyvsp[(2) - (3)].var));
									{resetTempCount();}
								;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 329 "src/parser.y"
    {gencodeop1(opRETURN, NULL);{resetTempCount();};}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 330 "src/parser.y"
    {resetTempCount();;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 339 "src/parser.y"
    {genif((yyvsp[(3) - (3)].var));genifgoto();;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 344 "src/parser.y"
    {backpatchif(0);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 345 "src/parser.y"
    {backpatchif(1);genifgoto();;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 345 "src/parser.y"
    {backpatchif(0);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 349 "src/parser.y"
    {genwhilebegin();;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 349 "src/parser.y"
    {genwhile((yyvsp[(4) - (5)].var));genwhilegotobegin();;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 349 "src/parser.y"
    {backpatchwhile();;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 350 "src/parser.y"
    {gendowhile();;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 350 "src/parser.y"
    {gendowhileend((yyvsp[(6) - (8)].var));;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 354 "src/parser.y"
    {(yyval.var) = (yyvsp[(3) - (3)].var);gencodeass((yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));if((yyvsp[(1) - (3)].var)->tempCodePos>-1) {setCodeToNOP((yyvsp[(1) - (3)].var)->tempCodePos);};}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 355 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opLOGICAL_OR, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 356 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opLOGICAL_AND, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 357 "src/parser.y"
    {(yyval.var) = gencodeopexp1(opLOGICAL_NOT, (yyvsp[(2) - (2)].var));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 358 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opEQ, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 359 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opNE, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 360 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opLS, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 361 "src/parser.y"
    {	//$$ = $1 <= $2 -> $$ = $1 < $2 || $1 == $2;
											struct varentry *t0;struct varentry *t1;
											t0 = gencodeopexp2(opLS, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
											t1 = gencodeopexp2(opEQ, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
											(yyval.var) = gencodeopexp2(opLOGICAL_OR, t0, t1);
											//$$ = gencodeopexp2(opLSEQ, $1, $3);
										;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 368 "src/parser.y"
    {	//$$ = $1 >= $2 -> $$ = $1 > $2 || $1 == $2;
											struct varentry *t0;struct varentry *t1;
											t0 = gencodeopexp2(opGT, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
											t1 = gencodeopexp2(opEQ, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
											(yyval.var) = gencodeopexp2(opLOGICAL_OR, t0, t1);
											//$$ = gencodeopexp2(opGTEQ, $1, $3);
										;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 375 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opGT, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 376 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opADD, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 377 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opSUB, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 378 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opMUL, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 379 "src/parser.y"
    {(yyval.var) = gencodeopexp1(opMINUS, (yyvsp[(2) - (2)].var));;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 380 "src/parser.y"
    {
		if(!find_var((yyvsp[(1) - (4)].id)))
			(yyval.var) = gencodeloadarr(find_funcpar2((yyvsp[(1) - (4)].id)), (yyvsp[(3) - (4)].var));
		else
			(yyval.var) = gencodeloadarr(find_var((yyvsp[(1) - (4)].id)), (yyvsp[(3) - (4)].var));
		(yyval.var)->tempArrPos=(yyvsp[(3) - (4)].var)->val;
		(yyval.var)->tempArrPos2=(yyvsp[(3) - (4)].var);
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 388 "src/parser.y"
    {(yyval.var) = (yyvsp[(2) - (3)].var);}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 389 "src/parser.y"
    {(yyval.var) = (yyvsp[(1) - (1)].func);/*$$ = irtempInt();*//*TODO: Check whether v0 or v1 is needed as a temp register. for e.g. i = f() + g() -> i = v0 + v1*/;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 390 "src/parser.y"
    {(yyval.var) = (yyvsp[(1) - (1)].var);}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 395 "src/parser.y"
    {add_var("int",0, NOT_DEFINED,GLOBAL, (yyvsp[(1) - (1)].num));(yyval.var) = find_var("int");;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 396 "src/parser.y"
    {	
			if(find_var((yyvsp[(1) - (1)].id))) {
			(yyval.var) = find_var((yyvsp[(1) - (1)].id));
		} else {
			//TODO: It seems that global variables are not recognised, check this!
			fprintf(stderr,"ERROR! The variable %s was not declared. Line: %d Column: %d \n", (yyvsp[(1) - (1)].id), yylloc.first_line,yylloc.first_column);
			//We assume the variable should have been declared. so we declare it for the user...
			add_var ((yyvsp[(1) - (1)].id), 0,NOT_DEFINED, GLOBAL,0);
			(yyval.var)= find_var((yyvsp[(1) - (1)].id));
			//yyerror("syntax error");
		}
	  ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 411 "src/parser.y"
    {
			funcentry_t *f;
			printf("DEBUG --- Function call regocnised[%s()].\n",(yyvsp[(1) - (3)].id));
			if(find_func((yyvsp[(1) - (3)].id))){
				f = find_func((yyvsp[(1) - (3)].id));
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!\n");
			}
			//$$ = gencodeopfunccall(opCALL, putInt ("int", 0, 0), sFunc, opcodeFindFunctionDef(sFunc));

		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 424 "src/parser.y"
    {
			funcentry_t *f;
			printf("DEBUG --- Parameterise Function call regocnised[%s()].\n",(yyvsp[(1) - (4)].id));
			if(find_func((yyvsp[(1) - (4)].id))){
				f = find_func((yyvsp[(1) - (4)].id));
				if(check_funccallpar(f, (yyvsp[(3) - (4)].plist))){
					printf("Functional Call Param Check OK!\n");
				}
				else{
					fprintf(stderr,"ERROR: Functional Call Param Check FAILED![%s(%s)]\n",f->funcname,(yyvsp[(3) - (4)].plist)->var);
				}
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!\n");
			}
			//$$ = gencodeopfunccall(opCALL, putInt ("int", 0, $3->count), f, opcodeFindFunctionDef(f));
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 445 "src/parser.y"
    {
			(yyval.plist)->count += 1;
			gencodeop1(opPARAM, (yyvsp[(3) - (3)].var));
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 450 "src/parser.y"
    {
			(yyval.plist) = createParamList((yyvsp[(1) - (1)].var));
			gencodeop1(opPARAM, (yyvsp[(1) - (1)].var));
		;}
    break;



/* Line 1455 of yacc.c  */
#line 2190 "bin/parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 456 "src/parser.y"


void yyerror (const char *msg)
{
  printf("ERROR: %s\n", msg);
}

