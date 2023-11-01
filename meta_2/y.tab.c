/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "uccompiler.y"

  #include <stdio.h>
  extern int yylex(void);
  void yyerror(char *);
  extern char *yytext;

#line 78 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BITWISEAND = 258,              /* BITWISEAND  */
    BITWISEOR = 259,               /* BITWISEOR  */
    BITWISEXOR = 260,              /* BITWISEXOR  */
    AND = 261,                     /* AND  */
    ASSIGN = 262,                  /* ASSIGN  */
    MUL = 263,                     /* MUL  */
    COMMA = 264,                   /* COMMA  */
    DIV = 265,                     /* DIV  */
    EQ = 266,                      /* EQ  */
    GE = 267,                      /* GE  */
    GT = 268,                      /* GT  */
    LBRACE = 269,                  /* LBRACE  */
    LE = 270,                      /* LE  */
    LPAR = 271,                    /* LPAR  */
    LT = 272,                      /* LT  */
    MINUS = 273,                   /* MINUS  */
    MOD = 274,                     /* MOD  */
    NE = 275,                      /* NE  */
    NOT = 276,                     /* NOT  */
    OR = 277,                      /* OR  */
    PLUS = 278,                    /* PLUS  */
    RBRACE = 279,                  /* RBRACE  */
    RPAR = 280,                    /* RPAR  */
    SEMI = 281,                    /* SEMI  */
    IDENTIFIER = 282,              /* IDENTIFIER  */
    DECIMAL = 283,                 /* DECIMAL  */
    NATURAL = 284,                 /* NATURAL  */
    CHRLIT = 285,                  /* CHRLIT  */
    CHAR = 286,                    /* CHAR  */
    ELSE = 287,                    /* ELSE  */
    WHILE = 288,                   /* WHILE  */
    IF = 289,                      /* IF  */
    INT = 290,                     /* INT  */
    SHORT = 291,                   /* SHORT  */
    DOUBLE = 292,                  /* DOUBLE  */
    RETURN = 293,                  /* RETURN  */
    VOID = 294,                    /* VOID  */
    RESERVED = 295                 /* RESERVED  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define BITWISEAND 258
#define BITWISEOR 259
#define BITWISEXOR 260
#define AND 261
#define ASSIGN 262
#define MUL 263
#define COMMA 264
#define DIV 265
#define EQ 266
#define GE 267
#define GT 268
#define LBRACE 269
#define LE 270
#define LPAR 271
#define LT 272
#define MINUS 273
#define MOD 274
#define NE 275
#define NOT 276
#define OR 277
#define PLUS 278
#define RBRACE 279
#define RPAR 280
#define SEMI 281
#define IDENTIFIER 282
#define DECIMAL 283
#define NATURAL 284
#define CHRLIT 285
#define CHAR 286
#define ELSE 287
#define WHILE 288
#define IF 289
#define INT 290
#define SHORT 291
#define DOUBLE 292
#define RETURN 293
#define VOID 294
#define RESERVED 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BITWISEAND = 3,                 /* BITWISEAND  */
  YYSYMBOL_BITWISEOR = 4,                  /* BITWISEOR  */
  YYSYMBOL_BITWISEXOR = 5,                 /* BITWISEXOR  */
  YYSYMBOL_AND = 6,                        /* AND  */
  YYSYMBOL_ASSIGN = 7,                     /* ASSIGN  */
  YYSYMBOL_MUL = 8,                        /* MUL  */
  YYSYMBOL_COMMA = 9,                      /* COMMA  */
  YYSYMBOL_DIV = 10,                       /* DIV  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_LPAR = 16,                      /* LPAR  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_NE = 20,                        /* NE  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_PLUS = 23,                      /* PLUS  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_RPAR = 25,                      /* RPAR  */
  YYSYMBOL_SEMI = 26,                      /* SEMI  */
  YYSYMBOL_IDENTIFIER = 27,                /* IDENTIFIER  */
  YYSYMBOL_DECIMAL = 28,                   /* DECIMAL  */
  YYSYMBOL_NATURAL = 29,                   /* NATURAL  */
  YYSYMBOL_CHRLIT = 30,                    /* CHRLIT  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_ELSE = 32,                      /* ELSE  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_IF = 34,                        /* IF  */
  YYSYMBOL_INT = 35,                       /* INT  */
  YYSYMBOL_SHORT = 36,                     /* SHORT  */
  YYSYMBOL_DOUBLE = 37,                    /* DOUBLE  */
  YYSYMBOL_RETURN = 38,                    /* RETURN  */
  YYSYMBOL_VOID = 39,                      /* VOID  */
  YYSYMBOL_RESERVED = 40,                  /* RESERVED  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_FuctionsAndDeclarations = 42,   /* FuctionsAndDeclarations  */
  YYSYMBOL_FuctionDefinition = 43,         /* FuctionDefinition  */
  YYSYMBOL_FuctionBody = 44,               /* FuctionBody  */
  YYSYMBOL_DeclarationAndStatements = 45,  /* DeclarationAndStatements  */
  YYSYMBOL_FuctionDeclaration = 46,        /* FuctionDeclaration  */
  YYSYMBOL_FuctionDeclarator = 47,         /* FuctionDeclarator  */
  YYSYMBOL_ParameterList = 48,             /* ParameterList  */
  YYSYMBOL_ParameterDeclaration = 49,      /* ParameterDeclaration  */
  YYSYMBOL_Declaration = 50,               /* Declaration  */
  YYSYMBOL_TypeSpec = 51,                  /* TypeSpec  */
  YYSYMBOL_Declarator = 52,                /* Declarator  */
  YYSYMBOL_Statement = 53,                 /* Statement  */
  YYSYMBOL_Expr = 54                       /* Expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   433

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    27,    27,    28,    29,    30,    31,    32,    35,    37,
      39,    40,    41,    42,    45,    47,    49,    50,    53,    55,
      57,    58,    59,    60,    61,    64,    66,    68,    70,    72,
      74,    76,    77,    80,    81,    82,    83,    84,    87,    88,
      89,    90,    91,    94,    95,    96,    97,    98,    99,   102,
     103,   104,   107,   109,   110,   111,   112,   113
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BITWISEAND",
  "BITWISEOR", "BITWISEXOR", "AND", "ASSIGN", "MUL", "COMMA", "DIV", "EQ",
  "GE", "GT", "LBRACE", "LE", "LPAR", "LT", "MINUS", "MOD", "NE", "NOT",
  "OR", "PLUS", "RBRACE", "RPAR", "SEMI", "IDENTIFIER", "DECIMAL",
  "NATURAL", "CHRLIT", "CHAR", "ELSE", "WHILE", "IF", "INT", "SHORT",
  "DOUBLE", "RETURN", "VOID", "RESERVED", "$accept",
  "FuctionsAndDeclarations", "FuctionDefinition", "FuctionBody",
  "DeclarationAndStatements", "FuctionDeclaration", "FuctionDeclarator",
  "ParameterList", "ParameterDeclaration", "Declaration", "TypeSpec",
  "Declarator", "Statement", "Expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      40,   -37,   -37,   -37,   -37,   -37,    24,   -37,   -37,   -37,
      -7,   -37,   -37,   -37,   -37,    -3,   -12,     6,   403,    -6,
      69,   -37,   -37,    -4,   403,   403,   403,   403,    10,   -37,
     -37,   -37,   292,    40,    28,   -37,    27,    95,    48,    49,
     403,    32,    69,    -4,    69,   131,    59,    41,   179,     2,
     -37,     2,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   -37,   -37,   -37,    45,   403,   403,   155,   -37,   -37,
     -37,   -37,   -37,   -37,   271,   385,   353,   371,   334,   292,
     -37,   292,   -37,   399,     9,     9,     9,     9,     2,   -37,
     399,   313,     2,   -37,   202,   225,   -37,   403,    95,    95,
     248,   -37,    38,   -37,    95,   -37
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    20,    21,    23,    24,    22,     0,     5,     6,     7,
       0,     1,     2,     3,     4,     0,     0,     0,     0,     0,
       0,    14,     8,     0,     0,     0,     0,     0,    53,    56,
      54,    55,    25,     0,     0,    16,     0,     0,     0,     0,
       0,     0,    13,     0,    12,     0,     0,     0,     0,    50,
      51,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    15,    18,     0,     0,     0,     0,     9,    11,
      10,    26,    19,    57,     0,    40,    41,    42,    39,    31,
      35,    32,    36,    43,    46,    48,    45,    47,    34,    37,
      44,    38,    33,    27,     0,     0,    30,     0,     0,     0,
      32,    29,     0,    52,     0,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,    68,   -37,   -26,    74,   -37,   -37,    51,     5,
      62,    63,   -36,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,    22,    41,     8,    16,    34,    35,    42,
      43,    17,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    74,    20,    33,    18,     9,    48,    49,    50,    51,
      58,    14,    60,    19,    21,    23,    79,    58,    80,    60,
      15,    67,    77,    46,    11,     1,    52,    66,    67,     2,
       3,     4,    70,     5,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    72,    73,     1,    78,   104,   105,     2,
       3,     4,    10,     5,    75,    76,    18,    82,    10,   103,
     114,     1,   111,   112,    12,     2,     3,     4,   115,     5,
      13,    36,     0,    37,    71,    24,    47,    25,     0,   110,
      26,     0,    27,     0,     0,    36,    28,    29,    30,    31,
       1,     0,    38,    39,     2,     3,     4,    40,     5,    37,
       0,    24,     0,    25,     0,     0,    26,     0,    27,     0,
       0,     0,    28,    29,    30,    31,     0,     0,    38,    39,
       0,     0,     0,    40,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     0,    64,     0,    65,    66,
      67,    68,     0,    69,    70,     0,     0,    81,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     0,
      64,     0,    65,    66,    67,    68,     0,    69,    70,     0,
       0,   106,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     0,    64,     0,    65,    66,    67,    68,
       0,    69,    70,     0,    83,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     0,    64,     0,    65,
      66,    67,    68,     0,    69,    70,     0,   108,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     0,
      64,     0,    65,    66,    67,    68,     0,    69,    70,     0,
     109,    53,    54,    55,    56,    57,    58,     0,    60,    61,
      62,    63,     0,    64,     0,    65,    66,    67,    68,     0,
      69,    70,     0,   113,    53,    54,    55,    56,    57,    58,
     107,    60,    61,    62,    63,     0,    64,     0,    65,    66,
      67,    68,     0,    69,    70,    53,    54,    55,    56,    57,
      58,     0,    60,    61,    62,    63,     0,    64,     0,    65,
      66,    67,    68,     0,    69,    70,    53,    54,    55,    56,
       0,    58,     0,    60,    61,    62,    63,     0,    64,     0,
      65,    66,    67,    68,     0,     0,    70,    53,    54,    55,
       0,     0,    58,     0,    60,    61,    62,    63,     0,    64,
       0,    65,    66,    67,    68,     0,    53,    70,    55,     0,
       0,    58,     0,    60,    61,    62,    63,     0,    64,     0,
      65,    66,    67,    68,    53,     0,    70,     0,     0,    58,
       0,    60,    61,    62,    63,     0,    64,     0,    65,    66,
      67,    68,     0,    58,    70,    60,    61,    62,    63,     0,
      64,     0,    65,    66,    67,    68,     0,    58,    70,    60,
       0,    62,    63,     0,    64,     0,    65,    66,    67,    24,
       0,    25,    70,     0,    26,     0,    27,     0,     0,     0,
      28,    29,    30,    31
};

static const yytype_int8 yycheck[] =
{
      18,    37,    14,     9,     7,     0,    24,    25,    26,    27,
       8,     6,    10,    16,    26,     9,    42,     8,    44,    10,
      27,    19,    40,    27,     0,    31,    16,    18,    19,    35,
      36,    37,    23,    39,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    25,    27,    31,    24,    75,    76,    35,
      36,    37,     0,    39,    16,    16,     7,    26,     6,    24,
      32,    31,   108,   109,     6,    35,    36,    37,   114,    39,
       6,    19,    -1,    14,    33,    16,    23,    18,    -1,   107,
      21,    -1,    23,    -1,    -1,    33,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    37,    38,    39,    14,
      -1,    16,    -1,    18,    -1,    -1,    21,    -1,    23,    -1,
      -1,    -1,    27,    28,    29,    30,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    17,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    -1,    17,    18,    19,    20,
      -1,    22,    23,    -1,    25,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    17,
      18,    19,    20,    -1,    22,    23,    -1,    25,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    17,    18,    19,    20,    -1,    22,    23,    -1,
      25,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    -1,    15,    -1,    17,    18,    19,    20,    -1,
      22,    23,    -1,    25,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    17,    18,
      19,    20,    -1,    22,    23,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    -1,    15,    -1,    17,
      18,    19,    20,    -1,    22,    23,     3,     4,     5,     6,
      -1,     8,    -1,    10,    11,    12,    13,    -1,    15,    -1,
      17,    18,    19,    20,    -1,    -1,    23,     3,     4,     5,
      -1,    -1,     8,    -1,    10,    11,    12,    13,    -1,    15,
      -1,    17,    18,    19,    20,    -1,     3,    23,     5,    -1,
      -1,     8,    -1,    10,    11,    12,    13,    -1,    15,    -1,
      17,    18,    19,    20,     3,    -1,    23,    -1,    -1,     8,
      -1,    10,    11,    12,    13,    -1,    15,    -1,    17,    18,
      19,    20,    -1,     8,    23,    10,    11,    12,    13,    -1,
      15,    -1,    17,    18,    19,    20,    -1,     8,    23,    10,
      -1,    12,    13,    -1,    15,    -1,    17,    18,    19,    16,
      -1,    18,    23,    -1,    21,    -1,    23,    -1,    -1,    -1,
      27,    28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    35,    36,    37,    39,    42,    43,    46,    50,
      51,     0,    43,    46,    50,    27,    47,    52,     7,    16,
      14,    26,    44,     9,    16,    18,    21,    23,    27,    28,
      29,    30,    54,     9,    48,    49,    51,    14,    33,    34,
      38,    45,    50,    51,    53,    54,    27,    52,    54,    54,
      54,    54,    16,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    15,    17,    18,    19,    20,    22,
      23,    49,    25,    27,    53,    16,    16,    54,    24,    45,
      45,    26,    26,    25,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    24,    54,    54,    26,     9,    25,    25,
      54,    53,    53,    25,    32,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    42,    42,    43,    44,
      45,    45,    45,    45,    46,    47,    48,    48,    49,    50,
      51,    51,    51,    51,    51,    52,    53,    53,    53,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     1,     1,     3,     3,
       2,     2,     1,     1,     3,     4,     1,     2,     2,     5,
       1,     1,     1,     1,     1,     3,     2,     3,     7,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     6,     1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* FuctionsAndDeclarations: FuctionsAndDeclarations FuctionDefinition  */
#line 27 "uccompiler.y"
                                                                   {;}
#line 1373 "y.tab.c"
    break;

  case 3: /* FuctionsAndDeclarations: FuctionsAndDeclarations FuctionDeclaration  */
#line 28 "uccompiler.y"
                                                                    {;}
#line 1379 "y.tab.c"
    break;

  case 4: /* FuctionsAndDeclarations: FuctionsAndDeclarations Declaration  */
#line 29 "uccompiler.y"
                                                             {;}
#line 1385 "y.tab.c"
    break;

  case 5: /* FuctionsAndDeclarations: FuctionDefinition  */
#line 30 "uccompiler.y"
                                           {;}
#line 1391 "y.tab.c"
    break;

  case 6: /* FuctionsAndDeclarations: FuctionDeclaration  */
#line 31 "uccompiler.y"
                                            {;}
#line 1397 "y.tab.c"
    break;

  case 7: /* FuctionsAndDeclarations: Declaration  */
#line 32 "uccompiler.y"
                                     {;}
#line 1403 "y.tab.c"
    break;

  case 8: /* FuctionDefinition: TypeSpec FuctionDeclarator FuctionBody  */
#line 35 "uccompiler.y"
                                                          {;}
#line 1409 "y.tab.c"
    break;

  case 9: /* FuctionBody: LBRACE DeclarationAndStatements RBRACE  */
#line 37 "uccompiler.y"
                                                    {;}
#line 1415 "y.tab.c"
    break;

  case 10: /* DeclarationAndStatements: Statement DeclarationAndStatements  */
#line 39 "uccompiler.y"
                                                             {;}
#line 1421 "y.tab.c"
    break;

  case 11: /* DeclarationAndStatements: Declaration DeclarationAndStatements  */
#line 40 "uccompiler.y"
                                                               {;}
#line 1427 "y.tab.c"
    break;

  case 12: /* DeclarationAndStatements: Statement  */
#line 41 "uccompiler.y"
                                    {;}
#line 1433 "y.tab.c"
    break;

  case 13: /* DeclarationAndStatements: Declaration  */
#line 42 "uccompiler.y"
                                      {;}
#line 1439 "y.tab.c"
    break;

  case 14: /* FuctionDeclaration: TypeSpec FuctionDeclarator SEMI  */
#line 45 "uccompiler.y"
                                                    {;}
#line 1445 "y.tab.c"
    break;

  case 15: /* FuctionDeclarator: IDENTIFIER LPAR ParameterList RPAR  */
#line 47 "uccompiler.y"
                                                      {;}
#line 1451 "y.tab.c"
    break;

  case 16: /* ParameterList: ParameterDeclaration  */
#line 49 "uccompiler.y"
                                    {;}
#line 1457 "y.tab.c"
    break;

  case 17: /* ParameterList: COMMA ParameterDeclaration  */
#line 50 "uccompiler.y"
                                          {;}
#line 1463 "y.tab.c"
    break;

  case 18: /* ParameterDeclaration: TypeSpec IDENTIFIER  */
#line 53 "uccompiler.y"
                                          {;}
#line 1469 "y.tab.c"
    break;

  case 19: /* Declaration: TypeSpec Declarator COMMA Declarator SEMI  */
#line 55 "uccompiler.y"
                                                       {;}
#line 1475 "y.tab.c"
    break;

  case 20: /* TypeSpec: CHAR  */
#line 57 "uccompiler.y"
               {;}
#line 1481 "y.tab.c"
    break;

  case 21: /* TypeSpec: INT  */
#line 58 "uccompiler.y"
              {;}
#line 1487 "y.tab.c"
    break;

  case 22: /* TypeSpec: VOID  */
#line 59 "uccompiler.y"
               {;}
#line 1493 "y.tab.c"
    break;

  case 23: /* TypeSpec: SHORT  */
#line 60 "uccompiler.y"
                {;}
#line 1499 "y.tab.c"
    break;

  case 24: /* TypeSpec: DOUBLE  */
#line 61 "uccompiler.y"
                 {;}
#line 1505 "y.tab.c"
    break;

  case 25: /* Declarator: IDENTIFIER ASSIGN Expr  */
#line 64 "uccompiler.y"
                                   {;}
#line 1511 "y.tab.c"
    break;

  case 26: /* Statement: Expr SEMI  */
#line 66 "uccompiler.y"
                     {;}
#line 1517 "y.tab.c"
    break;

  case 27: /* Statement: LBRACE Statement RBRACE  */
#line 68 "uccompiler.y"
                                   {;}
#line 1523 "y.tab.c"
    break;

  case 28: /* Statement: IF LPAR Expr RPAR Statement ELSE Statement  */
#line 70 "uccompiler.y"
                                                      {;}
#line 1529 "y.tab.c"
    break;

  case 29: /* Statement: WHILE LPAR Expr RPAR Statement  */
#line 72 "uccompiler.y"
                                          {;}
#line 1535 "y.tab.c"
    break;

  case 30: /* Statement: RETURN Expr SEMI  */
#line 74 "uccompiler.y"
                            {;}
#line 1541 "y.tab.c"
    break;

  case 31: /* Expr: Expr ASSIGN Expr  */
#line 76 "uccompiler.y"
                        {;}
#line 1547 "y.tab.c"
    break;

  case 32: /* Expr: Expr COMMA Expr  */
#line 77 "uccompiler.y"
                      {;}
#line 1553 "y.tab.c"
    break;

  case 33: /* Expr: Expr PLUS Expr  */
#line 80 "uccompiler.y"
                     {;}
#line 1559 "y.tab.c"
    break;

  case 34: /* Expr: Expr MINUS Expr  */
#line 81 "uccompiler.y"
                      {;}
#line 1565 "y.tab.c"
    break;

  case 35: /* Expr: Expr MUL Expr  */
#line 82 "uccompiler.y"
                    {;}
#line 1571 "y.tab.c"
    break;

  case 36: /* Expr: Expr DIV Expr  */
#line 83 "uccompiler.y"
                    {;}
#line 1577 "y.tab.c"
    break;

  case 37: /* Expr: Expr MOD Expr  */
#line 84 "uccompiler.y"
                    {;}
#line 1583 "y.tab.c"
    break;

  case 38: /* Expr: Expr OR Expr  */
#line 87 "uccompiler.y"
                   {;}
#line 1589 "y.tab.c"
    break;

  case 39: /* Expr: Expr AND Expr  */
#line 88 "uccompiler.y"
                    {;}
#line 1595 "y.tab.c"
    break;

  case 40: /* Expr: Expr BITWISEAND Expr  */
#line 89 "uccompiler.y"
                           {;}
#line 1601 "y.tab.c"
    break;

  case 41: /* Expr: Expr BITWISEOR Expr  */
#line 90 "uccompiler.y"
                          {;}
#line 1607 "y.tab.c"
    break;

  case 42: /* Expr: Expr BITWISEXOR Expr  */
#line 91 "uccompiler.y"
                           {;}
#line 1613 "y.tab.c"
    break;

  case 43: /* Expr: Expr EQ Expr  */
#line 94 "uccompiler.y"
                   {;}
#line 1619 "y.tab.c"
    break;

  case 44: /* Expr: Expr NE Expr  */
#line 95 "uccompiler.y"
                   {;}
#line 1625 "y.tab.c"
    break;

  case 45: /* Expr: Expr LE Expr  */
#line 96 "uccompiler.y"
                   {;}
#line 1631 "y.tab.c"
    break;

  case 46: /* Expr: Expr GE Expr  */
#line 97 "uccompiler.y"
                   {;}
#line 1637 "y.tab.c"
    break;

  case 47: /* Expr: Expr LT Expr  */
#line 98 "uccompiler.y"
                   {;}
#line 1643 "y.tab.c"
    break;

  case 48: /* Expr: Expr GT Expr  */
#line 99 "uccompiler.y"
                   {;}
#line 1649 "y.tab.c"
    break;

  case 49: /* Expr: PLUS Expr  */
#line 102 "uccompiler.y"
                {;}
#line 1655 "y.tab.c"
    break;

  case 50: /* Expr: MINUS Expr  */
#line 103 "uccompiler.y"
                 {;}
#line 1661 "y.tab.c"
    break;

  case 51: /* Expr: NOT Expr  */
#line 104 "uccompiler.y"
               {;}
#line 1667 "y.tab.c"
    break;

  case 52: /* Expr: IDENTIFIER LPAR Expr COMMA Expr RPAR  */
#line 107 "uccompiler.y"
                                           {;}
#line 1673 "y.tab.c"
    break;

  case 53: /* Expr: IDENTIFIER  */
#line 109 "uccompiler.y"
                 {;}
#line 1679 "y.tab.c"
    break;

  case 54: /* Expr: NATURAL  */
#line 110 "uccompiler.y"
              {;}
#line 1685 "y.tab.c"
    break;

  case 55: /* Expr: CHRLIT  */
#line 111 "uccompiler.y"
             {;}
#line 1691 "y.tab.c"
    break;

  case 56: /* Expr: DECIMAL  */
#line 112 "uccompiler.y"
              {;}
#line 1697 "y.tab.c"
    break;

  case 57: /* Expr: LPAR Expr RPAR  */
#line 113 "uccompiler.y"
                     {;}
#line 1703 "y.tab.c"
    break;


#line 1707 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 116 "uccompiler.y"

void yyerror(char *error) {
    printf("%s '%s'\n", error, yytext);
}
