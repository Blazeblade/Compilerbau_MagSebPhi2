
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
#include <stdlib.h>


#define NOT_DEFINED -1
#define GLOBAL 0
#define LOCAL 1
#define PARAMETER 2




/* Line 189 of yacc.c  */
#line 90 "bin/parser.c"

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
#line 23 "src/parser.y"

  int 				num;
  char*				id;
  struct varentry 	*var;
  struct funcentry 	*func;
 // struct symentry	*sym;
  struct funccallparlist *plist;



/* Line 214 of yacc.c  */
#line 174 "bin/parser.c"
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
#line 199 "bin/parser.c"

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
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

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
      22,    24,    28,    31,    36,    38,    39,    48,    49,    59,
      64,    70,    72,    76,    79,    80,    83,    85,    88,    91,
      93,    95,    99,   102,   104,   108,   109,   116,   118,   119,
     124,   125,   126,   134,   135,   144,   148,   152,   156,   159,
     163,   167,   171,   175,   179,   183,   187,   191,   195,   198,
     203,   207,   209,   211,   213,   215,   219,   224,   228
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    40,    41,    -1,    41,    -1,
      43,    12,    -1,    48,    12,    -1,    45,    -1,    12,    -1,
       7,    -1,     8,    -1,    43,    11,    44,    -1,    42,    44,
      -1,    15,    37,    16,    36,    -1,    15,    -1,    -1,    42,
      15,    35,    34,    46,    13,    51,    14,    -1,    -1,    42,
      15,    35,    49,    34,    47,    13,    51,    14,    -1,    42,
      15,    35,    34,    -1,    42,    15,    35,    49,    34,    -1,
      50,    -1,    49,    11,    50,    -1,    42,    44,    -1,    -1,
      51,    52,    -1,    53,    -1,    43,    12,    -1,    62,    12,
      -1,    54,    -1,    58,    -1,     9,    62,    12,    -1,     9,
      12,    -1,    12,    -1,    13,    51,    14,    -1,    -1,     5,
      35,    62,    55,    34,    56,    -1,    52,    -1,    -1,    52,
       6,    57,    52,    -1,    -1,    -1,     4,    59,    35,    62,
      34,    60,    52,    -1,    -1,     3,    61,    52,     4,    35,
      62,    34,    12,    -1,    62,    17,    62,    -1,    62,    18,
      62,    -1,    62,    19,    62,    -1,    33,    62,    -1,    62,
      21,    62,    -1,    62,    20,    62,    -1,    62,    25,    62,
      -1,    62,    24,    62,    -1,    62,    23,    62,    -1,    62,
      22,    62,    -1,    62,    29,    62,    -1,    62,    28,    62,
      -1,    62,    30,    62,    -1,    28,    62,    -1,    15,    37,
      63,    36,    -1,    35,    62,    34,    -1,    64,    -1,    63,
      -1,    16,    -1,    15,    -1,    15,    35,    34,    -1,    15,
      35,    65,    34,    -1,    65,    11,    62,    -1,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    95,    96,   100,   101,   102,   103,   107,
     108,   112,   127,   152,   172,   195,   194,   222,   221,   264,
     284,   307,   323,   341,   362,   364,   368,   369,   370,   371,
     372,   373,   382,   383,   388,   392,   392,   397,   398,   398,
     402,   402,   402,   403,   403,   407,   412,   413,   414,   415,
     416,   417,   418,   424,   430,   431,   432,   433,   434,   435,
     443,   444,   445,   450,   461,   476,   500,   534,   539
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
  "@1", "@2", "function_declaration", "function_parameter_list",
  "function_parameter", "stmt_list", "stmt", "stmt_block",
  "stmt_conditional", "$@3", "stmt_conditional_r", "$@4", "stmt_loop",
  "$@5", "$@6", "$@7", "expression", "primary", "function_call",
  "function_call_parameters", 0
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
      42,    43,    43,    44,    44,    46,    45,    47,    45,    48,
      48,    49,    49,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    55,    54,    56,    57,    56,
      59,    60,    58,    61,    58,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     1,     1,     1,
       1,     3,     2,     4,     1,     0,     8,     0,     9,     4,
       5,     1,     3,     2,     0,     2,     1,     2,     2,     1,
       1,     3,     2,     1,     3,     0,     6,     1,     0,     4,
       0,     0,     7,     0,     8,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     4,
       3,     1,     1,     1,     1,     3,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     8,     0,     2,     4,     0,     0,     7,
       0,     1,     3,    14,    12,     0,     5,     6,     0,     0,
      14,    11,    15,     0,     0,    21,     0,     0,    23,     0,
      17,    13,    24,    22,     0,     0,    24,    43,    40,     0,
       0,    33,    24,    16,    64,    63,     0,     0,     0,     0,
       0,    25,    26,    29,    30,     0,    62,    61,     0,     0,
       0,     0,    32,     0,     0,     0,     0,    58,    48,     0,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,     0,    35,    31,    34,
      65,    68,     0,    64,     0,    60,    45,    46,    47,    50,
      49,    54,    53,    52,    51,    56,    55,    57,     0,     0,
       0,     0,    66,    59,     0,    41,     0,    67,     0,     0,
      37,    36,     0,    42,    38,    44,     0,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    49,    50,    14,     9,    27,    34,
      10,    24,    25,    35,    51,    52,    53,   110,   121,   126,
      54,    60,   119,    59,    55,    56,    57,    92
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -59
static const yytype_int16 yypact[] =
{
      52,   -59,   -59,   -59,    22,    52,   -59,    15,    36,   -59,
      39,   -59,   -59,    19,   -59,    42,   -59,   -59,    -5,    50,
      41,   -59,    61,    42,    -7,   -59,    53,    86,   -59,    55,
      92,   -59,   -59,   -59,    93,    72,   -59,   -59,   -59,    76,
      37,   -59,   -59,   -59,    32,   -59,   163,   163,   163,    42,
      71,   -59,   -59,   -59,   -59,   185,   -59,   -59,   105,   152,
      94,   163,   -59,   199,   138,   160,   100,   -59,   -59,   213,
     -59,   -59,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   -59,   124,   163,    73,   -59,   -59,
     -59,    73,    -6,   -59,   101,   -59,    73,   -10,   102,   262,
     262,   106,   106,   106,   106,   109,   109,   -59,   113,   231,
     110,   163,   -59,   -59,   163,   -59,   152,    73,   249,   152,
     143,   -59,   146,   -59,   -59,   -59,   152,   -59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   -59,   157,    26,    45,     1,   -59,   -59,   -59,
     -59,   -59,   134,   -19,   -58,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,   -40,   103,   -59,   -59
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -21
static const yytype_int8 yytable[] =
{
      63,    85,     1,     2,    29,   111,    67,    68,    69,    74,
      75,    76,    77,    78,    79,    80,    21,    58,    81,    82,
      83,    87,    11,    64,    28,    91,     7,    30,   112,    22,
      13,     7,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,    23,     8,   109,    15,    16,    62,
       8,    17,    44,    45,    18,    23,    19,    20,   120,     1,
       2,   123,     1,     2,     3,    46,    26,    65,   127,    66,
      47,   117,    48,   -19,   118,    37,    38,    39,    19,     1,
       2,    40,    15,    70,    41,    42,    43,    44,    45,    31,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    32,
      46,    81,    82,    83,   -20,    47,    36,    48,    37,    38,
      39,    61,     1,     2,    40,    93,    45,    41,    42,    84,
      44,    45,    75,    76,    77,    78,    79,    80,   108,    86,
      81,    82,    83,    46,    81,    82,    83,   113,    47,    83,
      48,    37,    38,    39,   116,     1,     2,    40,   114,   124,
      41,    42,    89,    44,    45,    37,    38,    39,   125,     1,
       2,    40,    12,    33,    41,    42,    46,    44,    45,    94,
       0,    47,     0,    48,     0,    44,    45,     0,    44,    45,
      46,     0,     0,     0,     0,    47,     0,    48,    46,     0,
       0,    46,     0,    47,    90,    48,    47,    71,    48,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    88,     0,    81,    82,    83,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,     0,     0,     0,    95,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,     0,     0,     0,   115,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
       0,     0,     0,   122,    77,    78,    79,    80,     0,     0,
      81,    82,    83
};

static const yytype_int8 yycheck[] =
{
      40,    59,     7,     8,    11,    11,    46,    47,    48,    19,
      20,    21,    22,    23,    24,    25,    15,    36,    28,    29,
      30,    61,     0,    42,    23,    65,     0,    34,    34,    34,
      15,     5,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    18,     0,    86,    11,    12,    12,
       5,    12,    15,    16,    35,    29,    37,    15,   116,     7,
       8,   119,     7,     8,    12,    28,    16,    35,   126,    37,
      33,   111,    35,    12,   114,     3,     4,     5,    37,     7,
       8,     9,    11,    12,    12,    13,    14,    15,    16,    36,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    13,
      28,    28,    29,    30,    12,    33,    13,    35,     3,     4,
       5,    35,     7,     8,     9,    15,    16,    12,    13,    14,
      15,    16,    20,    21,    22,    23,    24,    25,     4,    35,
      28,    29,    30,    28,    28,    29,    30,    36,    33,    30,
      35,     3,     4,     5,    34,     7,     8,     9,    35,     6,
      12,    13,    14,    15,    16,     3,     4,     5,    12,     7,
       8,     9,     5,    29,    12,    13,    28,    15,    16,    66,
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
      48,     0,    41,    15,    44,    11,    12,    12,    35,    37,
      15,    44,    34,    42,    49,    50,    16,    46,    44,    11,
      34,    36,    13,    50,    47,    51,    13,     3,     4,     5,
       9,    12,    13,    14,    15,    16,    28,    33,    35,    42,
      43,    52,    53,    54,    58,    62,    63,    64,    51,    61,
      59,    35,    12,    62,    51,    35,    37,    62,    62,    62,
      12,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    28,    29,    30,    14,    52,    35,    62,    12,    14,
      34,    62,    65,    15,    63,    34,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,     4,    62,
      55,    11,    34,    36,    35,    34,    34,    62,    62,    60,
      52,    56,    34,    52,     6,    12,    57,    52
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
#line 82 "src/parser.y"
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
#line 107 "src/parser.y"
    {(yyval.id)=integer;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 108 "src/parser.y"
    {(yyval.id)=voidtype;;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 113 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof(*(yyval.var)));
			assert((yyval.var)!=NULL);
			(yyval.var)->varname=(yyvsp[(3) - (3)].var)->varname;
			if((yyvsp[(3) - (3)].var)->arrdim>=0){
					(yyval.var)->vartype=1;
					add_var((yyval.var)->varname, (yyval.var)->vartype,(yyvsp[(3) - (3)].var)->arrdim,NULL);
				}
				else {
					(yyval.var)->vartype=0;
					add_var((yyval.var)->varname, (yyval.var)->vartype,NOT_DEFINED,NULL);
				}
			//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 128 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof(*(yyval.var)));
			assert((yyval.var)!=NULL);
			if((yyvsp[(1) - (2)].id)==voidtype) {
				fprintf(stderr,"Variables can not be of type void (%s). Line: %d Column: %d \n",(yyvsp[(2) - (2)].var)->varname, (yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);
			} 
			else {
				(yyval.var)->varname=(yyvsp[(2) - (2)].var)->varname;
				if((yyvsp[(2) - (2)].var)->arrdim>=0){
					(yyval.var)->vartype=1;
					add_var((yyval.var)->varname, (yyval.var)->vartype,(yyvsp[(2) - (2)].var)->arrdim,NULL);
				}
				else {
					(yyval.var)->vartype=0;
					add_var((yyval.var)->varname, (yyval.var)->vartype,NOT_DEFINED,NULL);
				}
				//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
				//printf("DEBUG --- Symboltable: ");
				//print_vars();
			}
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 153 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof(*(yyval.var)));
			assert((yyval.var)!=NULL);
			if(find_var((yyvsp[(1) - (4)].id))){
				(yyval.var)=find_var((yyvsp[(1) - (4)].id));
				if((yyval.var)->scope==get_func_scope())
					fprintf(stderr,"This Symbol was already defined (%s), Line: %d Column: %d \n",(yyval.var)->varname, (yylsp[(1) - (4)]).first_line,(yylsp[(1) - (4)]).first_column);
				else{
					(yyval.var)->varname=(yyvsp[(1) - (4)].id);
					(yyval.var)->vartype=1;
					(yyval.var)->arrdim= (yyvsp[(3) - (4)].num);
				}
			}	
			else{
				(yyval.var)->varname=(yyvsp[(1) - (4)].id);
				(yyval.var)->vartype=1;
				(yyval.var)->arrdim= (yyvsp[(3) - (4)].num);
			}
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 173 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof(*(yyval.var)));
			assert((yyval.var)!=NULL);
			if(find_var((yyvsp[(1) - (1)].id))){
				(yyval.var)=find_var((yyvsp[(1) - (1)].id));
				if((yyval.var)->scope==get_func_scope())
					fprintf(stderr,"This Symbol was already defined (%s), Line: %d Column: %d \n",(yyval.var)->varname, (yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);
				else{
					(yyval.var)->varname=(yyvsp[(1) - (1)].id);
					(yyval.var)->arrdim=NOT_DEFINED;
				}
			}	
			else{
				(yyval.var)->varname=(yyvsp[(1) - (1)].id);
				(yyval.var)->arrdim=NOT_DEFINED;

			}
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 195 "src/parser.y"
    {
			if(find_func((yyvsp[(2) - (4)].id))){
				if(is_func_proto((yyvsp[(2) - (4)].id))){
					if((yyvsp[(1) - (4)].id)!=find_func((yyvsp[(2) - (4)].id))->returntype){	
						fprintf(stderr,"Types mismatch from function %s's declaration. Line: %d Column: %d \n",(yyvsp[(2) - (4)].id), (yylsp[(1) - (4)]).first_line,(yylsp[(1) - (4)]).first_column);
					}
					set_func_to_decl((yyvsp[(2) - (4)].id));
					set_func_scope(find_func((yyvsp[(2) - (4)].id)));
				}
				else{	
					fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",(yyvsp[(2) - (4)].id), (yylsp[(1) - (4)]).first_line,(yylsp[(1) - (4)]).first_column);
				}
			}
			else{										
				(yyval.func)=malloc(sizeof(*(yyval.func)));
				assert((yyval.func)!=NULL);
				(yyval.func)->funcname=(yyvsp[(2) - (4)].id);
				(yyval.func)->returntype=(int)(yyvsp[(1) - (4)].id);
				(yyval.func)->dim=0;
				add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,NULL);
				set_func_scope(find_func((yyvsp[(2) - (4)].id)));
				}
			gencodeopfunc(opFUNC_DEF, NULL, find_func((yyvsp[(2) - (4)].id)));
		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 219 "src/parser.y"
    {gencodeopfunc(opFUNC_DEF_END, NULL, find_func((yyvsp[(2) - (8)].id)));set_func_scope(NULL);backpatchreturn();;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 222 "src/parser.y"
    {	
     		if(find_func((yyvsp[(2) - (5)].id))){
				if(is_func_proto((yyvsp[(2) - (5)].id))){
					if(!check_funccallpar(find_func((yyvsp[(2) - (5)].id)), (yyvsp[(4) - (5)].func))){
						fprintf(stderr,"Function-Parameter definition does not match the declaration of function %s. Line: %d Column: %d \n",(yyvsp[(2) - (5)].id), (yylsp[(1) - (5)]).first_line,(yylsp[(1) - (5)]).first_column);
					}
					if((yyvsp[(1) - (5)].id)!=find_func((yyvsp[(2) - (5)].id))->returntype){
						fprintf(stderr,"Type mismatch from function %s's declaration. Line: %d Column: %d \n",(yyvsp[(2) - (5)].id), (yylsp[(1) - (5)]).first_line,(yylsp[(1) - (5)]).first_column);
					}
					if(strcmp ((yyvsp[(4) - (5)].func)->funcname,"temp1")==0){
						delete_func (find_func("temp1"));
						set_func_to_decl ((yyvsp[(2) - (5)].id));
						set_func_scope(find_func((yyvsp[(2) - (5)].id)));
						gencodeopfunc(opFUNC_DEF, (yyvsp[(4) - (5)].func), find_func((yyvsp[(2) - (5)].id)));
					}
					else{
						printf("INTERNAL ERROR: Function has not the expected TEMP_NAME!\n");
					}
				}
				else{
					fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",(yyvsp[(2) - (5)].id), (yylsp[(1) - (5)]).first_line,(yylsp[(1) - (5)]).first_column);
				}
			}
			else{
				if(strcmp ((yyvsp[(4) - (5)].func)->funcname,"temp1") == 0){
					(yyval.func)=find_func("temp1");
					(yyval.func)->dim=count_pars((yyval.func)->funcname);
					(yyval.func)->funcname=(yyvsp[(2) - (5)].id);
					(yyval.func)->returntype=(int)(yyvsp[(1) - (5)].id);
					add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,(yyval.func)->var);
					delete_func((yyval.func));
					gencodeopfunc(opFUNC_DEF, (yyvsp[(4) - (5)].func), find_func((yyvsp[(2) - (5)].id)));
				}
				else{
					printf("INTERNAL ERROR: Function has not the expected TEMP_NAME!\n");
				}
			}			
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 260 "src/parser.y"
    {gencodeopfunc(opFUNC_DEF_END, NULL, find_func((yyvsp[(2) - (9)].id)));set_func_scope(NULL);backpatchreturn();;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 265 "src/parser.y"
    {
			if(find_func((yyvsp[(2) - (4)].id))){
				fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",(yyvsp[(2) - (4)].id), (yylsp[(1) - (4)]).first_line,(yylsp[(1) - (4)]).first_column);
				set_func_to_proto (find_func((yyvsp[(2) - (4)].id)));
				set_scope_for_pars (find_func((yyvsp[(2) - (4)].id)));
			}
			else{
				(yyval.func)=malloc(sizeof(*(yyval.func)));
				assert((yyval.func)!=NULL);
				(yyval.func)->funcname=(yyvsp[(2) - (4)].id);
				(yyval.func)->returntype=(int)(yyvsp[(1) - (4)].id);
				(yyval.func)->dim=0;
				add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,NULL);
				set_func_to_proto((yyval.func));
				set_scope_for_pars ((yyval.func));
			}
			set_func_scope(NULL);
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 285 "src/parser.y"
    {
			if(find_func((yyvsp[(2) - (5)].id))) {
				fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",(yyvsp[(2) - (5)].id), (yylsp[(1) - (5)]).first_line,(yylsp[(1) - (5)]).first_column);
				delete_func ("temp1");
				set_func_to_proto(find_func((yyvsp[(2) - (5)].id)));
				set_scope_for_pars (find_func((yyvsp[(2) - (5)].id)));
			}
			else{
				(yyval.func)=find_func("temp1");
				(yyval.func)->dim=count_pars((yyval.func)->funcname);
				(yyval.func)->funcname=(yyvsp[(2) - (5)].id);
				(yyval.func)->returntype=(int)(yyvsp[(1) - (5)].id);
				add_func((yyval.func)->funcname, (yyval.func)->returntype,(yyval.func)->dim,(yyval.func)->var);
				delete_func((yyval.func));				//Deletes the temp function	
				set_func_to_proto(find_func((yyvsp[(2) - (5)].id)));
				set_scope_for_pars (find_func((yyvsp[(2) - (5)].id)));															
			}
			set_func_scope(NULL);
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 308 "src/parser.y"
    {
			(yyval.func)=malloc(sizeof(*(yyval.func)));
			assert((yyval.func)!=NULL);
			if(!find_func("temp1"))	{
				add_func("temp1", 0,0,NULL);
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(1) - (1)].var)->varname, (yyvsp[(1) - (1)].var)->vartype, (yyvsp[(1) - (1)].var)->arrdim);
				(yyvsp[(1) - (1)].var)->scope=(yyval.func);
			} 
			else{	
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(1) - (1)].var)->varname, (yyvsp[(1) - (1)].var)->vartype, (yyvsp[(1) - (1)].var)->arrdim);
				(yyvsp[(1) - (1)].var)->scope=(yyval.func);
			}
		;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 324 "src/parser.y"
    {
			(yyval.func)=malloc(sizeof(*(yyval.func)));
			assert((yyval.func)!=NULL);
			if(!find_func("temp1")){
				add_func("temp1", 0,0,NULL);
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(3) - (3)].var)->varname, (yyvsp[(3) - (3)].var)->vartype, (yyvsp[(3) - (3)].var)->arrdim);
			} 
			else{
				(yyval.func)=find_func("temp1");
				add_funcpar("temp1",(yyvsp[(3) - (3)].var)->varname, (yyvsp[(3) - (3)].var)->vartype, (yyvsp[(3) - (3)].var)->arrdim);
				//add_var($3->varname, $3->vartype, $3->arrdim,1,0);
			}
		;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 342 "src/parser.y"
    {
			(yyval.var)=malloc(sizeof(*(yyval.var)));
			assert((yyval.var)!=NULL);
			(yyval.var)->varname = (yyvsp[(2) - (2)].var)->varname; 
			if((yyvsp[(1) - (2)].id)==voidtype) { 
				fprintf(stderr,"Function parameters can not be of type void. Line: %d Column: %d \n", (yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column); 
			} 
			else {
				if((yyvsp[(2) - (2)].var)->arrdim>=0){
					(yyval.var)->vartype=1;
					(yyval.var)->arrdim=(yyvsp[(2) - (2)].var)->arrdim;
				}
				else {
					(yyval.var)->vartype=0;
					(yyval.var)->arrdim=NOT_DEFINED;
				}
			}
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 369 "src/parser.y"
    {resetTempCount();;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 370 "src/parser.y"
    {resetTempCount();;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 371 "src/parser.y"
    {resetTempCount();;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 372 "src/parser.y"
    {resetTempCount();;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 373 "src/parser.y"
    {
										if((yyvsp[(2) - (3)].var)->scope!=NULL){
											if((yyvsp[(2) - (3)].var)->scope->returntype==2){ 
												fprintf(stderr,"Function was declared as VOID. It can not return a value. Either use \"RETURN;\" or use type int for the func. Line: %d Column: %d \n",	(yylsp[(1) - (3)]).first_line,(yylsp[(1) - (3)]).first_column);
											}
										}
										gencodeop1(opRETURN, (yyvsp[(2) - (3)].var));
										{resetTempCount();}
										;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 382 "src/parser.y"
    {gencodeop1(opRETURN, NULL);{resetTempCount();};}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 383 "src/parser.y"
    {resetTempCount();;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 392 "src/parser.y"
    {genif((yyvsp[(3) - (3)].var));genifgoto();;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 397 "src/parser.y"
    {backpatchif(0);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 398 "src/parser.y"
    {backpatchif(1);genifgoto();;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 398 "src/parser.y"
    {backpatchif(0);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 402 "src/parser.y"
    {genwhilebegin();;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 402 "src/parser.y"
    {genwhile((yyvsp[(4) - (5)].var));genwhilegotobegin();;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 402 "src/parser.y"
    {backpatchwhile();;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 403 "src/parser.y"
    {gendowhile();;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 403 "src/parser.y"
    {gendowhileend((yyvsp[(6) - (8)].var));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 407 "src/parser.y"
    {(yyval.var) = (yyvsp[(3) - (3)].var);
												gencodeass((yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
												if((yyvsp[(1) - (3)].var)->tempCodePos>-1) {
													setCodeToNOP((yyvsp[(1) - (3)].var)->tempCodePos);
												};}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 412 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opLOGICAL_OR, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 413 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opLOGICAL_AND, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 414 "src/parser.y"
    {(yyval.var) = gencodeopexp1(opLOGICAL_NOT, (yyvsp[(2) - (2)].var));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 415 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opEQ, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 416 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opNE, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 417 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opLS, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 418 "src/parser.y"
    {
												struct varentry *t0;struct varentry *t1;
												t0 = gencodeopexp2(opLS, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
												t1 = gencodeopexp2(opEQ, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
												(yyval.var) = gencodeopexp2(opLOGICAL_OR, t0, t1);
												;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 424 "src/parser.y"
    {	
												struct varentry *t0;struct varentry *t1;
												t0 = gencodeopexp2(opGT, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
												t1 = gencodeopexp2(opEQ, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));
												(yyval.var) = gencodeopexp2(opLOGICAL_OR, t0, t1);
												;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 430 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opGT, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 431 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opADD, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 432 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opSUB, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 433 "src/parser.y"
    {(yyval.var) = gencodeopexp2(opMUL, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].var));;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 434 "src/parser.y"
    {(yyval.var) = gencodeopexp1(opMINUS, (yyvsp[(2) - (2)].var));;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 435 "src/parser.y"
    {
												if(!find_var((yyvsp[(1) - (4)].id)))
													(yyval.var) = gencodeloadarr(find_funcpar2((yyvsp[(1) - (4)].id)), (yyvsp[(3) - (4)].var));
												else
													(yyval.var) = gencodeloadarr(find_var((yyvsp[(1) - (4)].id)), (yyvsp[(3) - (4)].var));
												(yyval.var)->tempArrPos=(yyvsp[(3) - (4)].var)->val;
												(yyval.var)->tempArrPos2=(yyvsp[(3) - (4)].var);
												;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 443 "src/parser.y"
    {(yyval.var) = (yyvsp[(2) - (3)].var);}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 444 "src/parser.y"
    {(yyval.var) = (yyvsp[(1) - (1)].func);}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 445 "src/parser.y"
    {(yyval.var) = (yyvsp[(1) - (1)].var);}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 450 "src/parser.y"
    {								//random id for primary-NUMs
			char *s;
			s=malloc(20);
			do{
				int i=rand()%100;
			sprintf(s,"int_prim%d",i);
			}while(find_var(s));
			add_var(s,0, NOT_DEFINED, (yyvsp[(1) - (1)].num));
			(yyval.var) = find_var(s);
			free(s);
			;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 461 "src/parser.y"
    {	
			if(find_var((yyvsp[(1) - (1)].id))) {
				(yyval.var) = find_var((yyvsp[(1) - (1)].id));
			} 
			else if(find_funcpar2((yyvsp[(1) - (1)].id))) {
				(yyval.var)=find_funcpar2((yyvsp[(1) - (1)].id));
			}
			else {
				fprintf(stderr,"ERROR! The variable %s was not declared. Line: %d Column: %d \n", (yyvsp[(1) - (1)].id), (yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);
				add_var ((yyvsp[(1) - (1)].id), 0,NOT_DEFINED,0);
				(yyval.var)= find_var((yyvsp[(1) - (1)].id));
			}
	  ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 477 "src/parser.y"
    {
			funcentry_t *f;
			//printf("DEBUG --- Function call regocnised[%s()].\n",$1);
			if(find_func((yyvsp[(1) - (3)].id))){
				f = find_func((yyvsp[(1) - (3)].id));
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call! Line: %d Column: %d \n", (yylsp[(1) - (3)]).first_line,(yylsp[(1) - (3)]).first_column);
				add_func("undeclared1",0,0,NULL);
				f=find_func("undeclared1");
			}
			varentry_t *v;
			char *s;
			s=malloc(20);
			do{
			int i=rand()%100;
			sprintf(s,"int_call%d",i);
			}while(find_var(s));
			add_var(s,0,-1,0);
			v=find_var(s);
			free(s);
			(yyval.func) = gencodeopfunccall(opCALL, v, f, opcodeFindFunctionDef(f));
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 501 "src/parser.y"
    {
			funcentry_t *f;
			//printf("DEBUG --- Parameterise Function call regocnised[%s()].\n",$1);
			if(find_func((yyvsp[(1) - (4)].id))){
				f = find_func((yyvsp[(1) - (4)].id));
				if(check_funccallpar(f, (yyvsp[(3) - (4)].plist))){
					//printf("Functional Call Param Check OK!\n");
				}
				else{
					fprintf(stderr,"ERROR: Functional Call Param Check FAILED![%s(%s)] Line: %d Column: %d \n",f->funcname,(yyvsp[(3) - (4)].plist)->var->varname, (yylsp[(1) - (4)]).first_line,(yylsp[(1) - (4)]).first_column);
				}
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!Line: %d Column: %d \n", (yylsp[(1) - (4)]).first_line,(yylsp[(1) - (4)]).first_column);
				add_func("undeclared1",0,0,NULL);
				f=find_func("undeclared1");
				
			}
			varentry_t *v;
			char *s;
			s=malloc(20);
			do{
				int i=rand()%100;
			sprintf(s,"int_call%d",i);
			}while(find_var(s));
			add_var(s,0,-1,(yyvsp[(3) - (4)].plist)->count);
			v=find_var(s);
			free(s);
			(yyval.func) = gencodeopfunccall(opCALL, v, f, opcodeFindFunctionDef(f));
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 535 "src/parser.y"
    {
			(yyval.plist)->count += 1;
			gencodeop1(opPARAM, (yyvsp[(3) - (3)].var));
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 540 "src/parser.y"
    {
			(yyval.plist) = create_pars_list((yyvsp[(1) - (1)].var));
			gencodeop1(opPARAM, (yyvsp[(1) - (1)].var));
		;}
    break;



/* Line 1455 of yacc.c  */
#line 2291 "bin/parser.c"
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
#line 546 "src/parser.y"


void yyerror (const char *msg)
{
  fprintf(stderr,"ERROR: %s, Line: %d Column: %d \n",msg, yylloc.first_line,yylloc.first_column);
}

