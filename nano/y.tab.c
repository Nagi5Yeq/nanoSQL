/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "interpreter.ypp"
    
    #include <cstdio>
    #include <stdlib.h>
    #include <string>
    #include <time.h>
    #include "SQLcommand.hpp"
    #include "TableInfo.hpp"
    #include "ConditionContent.hpp"
    #include "CatalogManager.hpp"
    #include "API.hpp"
    #include "BufferManager.hpp"
    
    std::string tmpAttrName;
    int fileflag=0;
    int attrcount;
    SQLcommand sql;
    TableInfo tableInfo;
    API api;
    extern "C"{
        void yyerror(const char *s);
        extern int yylex(void);
        extern int yylineno;
    }
        extern char* yytext;
        extern FILE* yyin;
    
#line 30 "interpreter.ypp"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {char *strVal;char *id;int intVal;float flVal;char *condition;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 58 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define UNIQUE 257
#define TABLE 258
#define SELECT 259
#define INSERT 260
#define DROP 261
#define DELETE 262
#define INDEX 263
#define QUIT 264
#define EXECFILE 265
#define FROM 266
#define WHERE 267
#define CREATE 268
#define RESET 269
#define INTO 270
#define VALUES 271
#define ON 272
#define PRIMARY 273
#define KEY 274
#define INTT 275
#define CHART 276
#define FLOATT 277
#define ANND 278
#define UNEXPECTED 279
#define WHITESPACE 280
#define FEOF 281
#define ERR 282
#define STRING 283
#define FILENAME 284
#define identifier 285
#define intnum 286
#define fnum 287
#define LE 288
#define GE 289
#define NE 290
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   13,   18,
   19,   19,    4,    4,    4,   14,   14,   20,   20,   11,
   15,   15,    1,    1,    2,    2,    2,    2,    3,    3,
    3,    3,    3,    3,    5,    5,    9,   12,   12,   21,
   21,   23,   24,   24,    7,    8,   25,   25,   25,   22,
    6,   26,   16,   17,   10,
};
static const YYINT yylen[] = {                            2,
    2,    2,    2,    2,    2,    2,    2,    3,    2,    3,
    3,    3,    3,    3,    3,    3,    3,    4,    8,    7,
    1,    3,    1,    1,    1,    5,    5,    1,    3,    1,
    4,    5,    2,    0,    3,    3,    3,    3,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    8,    6,    1,
    3,    1,    2,    3,    1,    1,    1,    4,    1,    5,
    1,    1,    3,    3,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   30,    0,   28,    0,    0,
    0,    0,    0,    0,    9,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,
    4,    5,    6,    7,    0,    0,    0,   47,    0,   63,
   65,   64,    0,    0,    8,    0,    0,   10,    0,   11,
   12,   13,   14,   16,   17,   15,    0,    0,   29,    0,
    0,   31,    0,    0,    0,   18,   26,   27,    0,   56,
    0,    0,   32,   55,    0,    0,   50,   52,    0,   23,
   24,   25,   21,    0,    0,   40,   39,   41,   43,   42,
   44,    0,   57,    0,   59,    0,   49,    0,    0,   20,
    0,   38,   36,   37,   35,    0,   62,   54,    0,    0,
   51,    0,   22,    0,    0,   48,   19,   58,    0,   61,
    0,   60,
};
static const YYINT yydgoto[] = {                          8,
   72,   81,  102,   93,    0,  131,   85,   82,   49,   52,
   18,    9,   10,   11,   12,   13,   14,   15,   94,   19,
   86,  120,   87,   88,  106,  118,
};
static const YYINT yysindex[] = {                      -246,
  -42, -260, -238, -259,  -48, -266, -218, -227,  -32,  -31,
  -23,  -17,  -10,   -3,    5,    0, -222,    0,  -40, -226,
 -226, -220, -226,  -39,    0,    7, -226, -220,    8, -215,
   10,   11,   12,   15,   16,   17,   18,    0,    0,    0,
    0,    0,    0,    0, -226, -226, -213,    0, -198,    0,
    0,    0, -189, -226,    0,   39, -192,    0,   22,    0,
    0,    0,    0,    0,    0,    0, -189, -189,    0,   42,
 -202,    0, -189, -201, -226,    0,    0,    0, -240,    0,
 -193,  -59,    0,    0, -214,    9,    0,    0,   46,    0,
    0,    0,    0,   13, -202,    0,    0,    0,    0,    0,
    0, -235,    0,   47,    0, -169,    0, -264, -202,    0,
 -240,    0,    0,    0,    0, -197,    0,    0, -184,   50,
    0,   51,    0,   52,   54,    0,    0,    0, -190,    0,
   55,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   38,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   38,   38,    0,    0,
    0,    0,   38,    0,    0,    0,    0,    0,    0,    0,
   40,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   14,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yygindex[] = {                         0,
  -44,    3,    0,  -11,    0,    0,    0,   -8,  -15,   74,
   56,   96,   97,   98,   99,  100,  101,  102,    0,  107,
    0,    0,    4,    0,    0,    0,
};
#define YYTABLESIZE 243
static const YYINT yytable[] = {                         17,
  100,  101,   99,   47,   47,   50,   23,   53,  119,   20,
   25,   56,    1,    2,    3,    4,   26,    5,    6,   21,
   84,    7,   77,   78,   22,   16,   38,   39,   83,   67,
   68,    1,    2,    3,    4,   40,   29,   30,   73,   27,
    7,   41,   90,   45,   28,   91,   92,  113,   42,  107,
  114,  115,  108,  110,   53,   43,  111,   53,   48,   89,
  103,  104,  105,   44,   51,   55,   58,   59,   60,   61,
   62,   16,   70,   63,   64,   65,   66,   71,   74,   75,
   76,   79,   80,   84,   95,  109,  116,  117,  124,  125,
  126,  127,  128,  129,  130,  132,   34,  112,   33,  123,
  122,   57,   69,   31,   32,   33,   34,   35,   36,   37,
   24,  121,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   46,   54,    0,   96,   97,
   98,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   16,
};
static const YYINT yycheck[] = {                         42,
   60,   61,   62,   44,   44,   21,  266,   23,  273,  270,
   59,   27,  259,  260,  261,  262,  283,  264,  265,  258,
  285,  268,   67,   68,  263,  285,   59,   59,   73,   45,
   46,  259,  260,  261,  262,   59,  264,  265,   54,  258,
  268,   59,  283,  266,  263,  286,  287,  283,   59,   41,
  286,  287,   44,   41,   41,   59,   44,   44,  285,   75,
  275,  276,  277,   59,  285,   59,   59,  283,   59,   59,
   59,  285,  271,   59,   59,   59,   59,  267,   40,  272,
   59,   40,  285,  285,  278,   40,   40,  257,  286,  274,
   41,   41,   41,   40,  285,   41,   59,   95,   59,  111,
  109,   28,   47,    8,    8,    8,    8,    8,    8,    8,
    4,  108,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  266,  266,   -1,  288,  289,
  290,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  285,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 319
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"UNIQUE","TABLE","SELECT","INSERT","DROP","DELETE","INDEX","QUIT",
"EXECFILE","FROM","WHERE","CREATE","RESET","INTO","VALUES","ON","PRIMARY","KEY",
"INTT","CHART","FLOATT","ANND","UNEXPECTED","WHITESPACE","FEOF","ERR","STRING",
"FILENAME","identifier","intnum","fnum","LE","GE","NE",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : line",
"line : create_table ';'",
"line : create_index ';'",
"line : select_statement ';'",
"line : delete_statement ';'",
"line : drop_table ';'",
"line : drop_index ';'",
"line : insert_statement ';'",
"line : EXECFILE STRING ';'",
"line : QUIT ';'",
"line : line QUIT ';'",
"line : line create_table ';'",
"line : line create_index ';'",
"line : line select_statement ';'",
"line : line delete_statement ';'",
"line : line insert_statement ';'",
"line : line drop_table ';'",
"line : line drop_index ';'",
"line : line EXECFILE STRING ';'",
"create_index : CREATE INDEX indexname ON tablename '(' attrname ')'",
"insert_statement : INSERT INTO tablename VALUES '(' valuelist ')'",
"valuelist : value",
"valuelist : valuelist ',' value",
"value : STRING",
"value : intnum",
"value : fnum",
"select_statement : SELECT '*' FROM tablename where_clause",
"select_statement : SELECT attrs FROM tablename where_clause",
"attrs : selectattr",
"attrs : attrs ',' selectattr",
"selectattr : identifier",
"delete_statement : DELETE FROM tablename where_clause",
"delete_statement : DELETE attrs FROM tablename where_clause",
"where_clause : WHERE condition",
"where_clause :",
"condition : attrname operation fnum",
"condition : attrname operation STRING",
"condition : attrname operation intnum",
"condition : condition ANND condition",
"operation : GE",
"operation : LE",
"operation : NE",
"operation : '<'",
"operation : '>'",
"operation : '='",
"number : intnum",
"number : fnum",
"tablename : identifier",
"create_table : CREATE TABLE tablename '(' table_element_list ',' table_constraint ')'",
"create_table : CREATE TABLE tablename '(' table_element_list ')'",
"table_element_list : table_element",
"table_element_list : table_element_list ',' table_element",
"table_element : column_def",
"column_def : attrn data_type",
"column_def : attrn data_type column_constraint",
"attrn : identifier",
"attrname : identifier",
"data_type : INTT",
"data_type : CHART '(' intnum ')'",
"data_type : FLOATT",
"table_constraint : PRIMARY KEY '(' priattr ')'",
"priattr : identifier",
"column_constraint : UNIQUE",
"drop_table : DROP TABLE tablename",
"drop_index : DROP INDEX indexname",
"indexname : identifier",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 351 "interpreter.ypp"
void yyerror(const char *s)
{
    std::string tmp1,tmp2;
    char c;
    
    tmp1=s;
    tmp2=yytext;
    if (strcmp(yytext,";") && strcmp(s,"Unterminated string"))
        while ((c=yylex())!=';');

    if (strcmp(s,"Char is defined too long or too short!") && strcmp(s,"Too many attributes!"))
        printf("%s near '%s'\n",s,tmp2.c_str());
    else
        printf("%s\n",s);
}
#line 401 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 54 "interpreter.ypp"
	{
    api.createTable(tableInfo);
    tableInfo.reset();
}
break;
case 2:
#line 58 "interpreter.ypp"
	{
    api.createIndex(sql);
    sql.reset();
}
break;
case 3:
#line 62 "interpreter.ypp"
	{
    api.selectRecord(sql);
    sql.reset();
}
break;
case 4:
#line 66 "interpreter.ypp"
	{
    api.deleteRecord(sql);
    sql.reset();
}
break;
case 5:
#line 70 "interpreter.ypp"
	{
    api.dropTable(sql);
    sql.reset();
}
break;
case 6:
#line 74 "interpreter.ypp"
	{
    api.dropIndex(sql);
    sql.reset();
}
break;
case 7:
#line 78 "interpreter.ypp"
	{
    api.insertRecord(sql);
    sql.reset();
}
break;
case 8:
#line 82 "interpreter.ypp"
	{
    const char* path=yystack.l_mark[-1].strVal;
    char temp[512];
    int i;
    getcwd(temp, 512);
    std::string s;
    for (i=0; temp[i]!='\0'; i++)
        s+=temp[i];

    s+='/';
    char file[50];
    strcpy(file,s.c_str());
    strcat(file,path);
    FILE *fp=fopen(file,"r");
    if(fp==NULL)
        printf("Cannot open file %s\n", yystack.l_mark[-1].strVal);
    else {
        fileflag=1;
        yyin=fp;
    }
}
break;
case 9:
#line 103 "interpreter.ypp"
	{
    printf("Closing files and writing back buffer...\n");
    BufferManager bm;
    bm.writeBackAllCache();
    bm.closeAllFiles();
    printf("Operation finished.\n");
    
    printf("Thank you~\n");
    exit(EXIT_SUCCESS);
}
break;
case 10:
#line 114 "interpreter.ypp"
	{
    printf("Closing files and writing back buffer...\n");
    BufferManager bm;
    bm.writeBackAllCache();
    bm.closeAllFiles();
    printf("Operation finished.\n");
    
    printf("Thanks for using~\n");
    exit(EXIT_SUCCESS);
}
break;
case 11:
#line 124 "interpreter.ypp"
	{
    api.createTable(tableInfo);
    tableInfo.reset();
}
break;
case 12:
#line 128 "interpreter.ypp"
	{
    api.createIndex(sql);
    sql.reset();
}
break;
case 13:
#line 132 "interpreter.ypp"
	{
    api.selectRecord(sql);
    sql.reset();
}
break;
case 14:
#line 136 "interpreter.ypp"
	{
    api.deleteRecord(sql);
    sql.reset();
}
break;
case 15:
#line 140 "interpreter.ypp"
	{
    api.insertRecord(sql);
    sql.reset();
}
break;
case 16:
#line 144 "interpreter.ypp"
	{
    api.dropTable(sql);
    sql.reset();
}
break;
case 17:
#line 148 "interpreter.ypp"
	{
    api.dropIndex(sql);
    sql.reset();
}
break;
case 18:
#line 152 "interpreter.ypp"
	{
    const char* path=yystack.l_mark[-1].strVal;
    char temp[512];
    int i;
    getcwd(temp, 512);
    std::string s;
    for (i=0; temp[i]!='\0'; i++)
    s+=temp[i];
    
    s+='/';
    char file[50];
    strcpy(file,s.c_str());
    strcat(file,path);
    FILE *fp=fopen(file,"r");
    if(fp==NULL)
    printf("Cannot open file %s\n", yystack.l_mark[-1].strVal);
    else {
        fileflag=1;
        yyin=fp;
    }
}
break;
case 21:
#line 182 "interpreter.ypp"
	{}
break;
case 22:
#line 183 "interpreter.ypp"
	{}
break;
case 23:
#line 187 "interpreter.ypp"
	{
    if(sql.attrNum>31) {
        printf("Too many values!\n");
        yyparse();
    }
    else {
        sql.attrNum++;
        sql.condCont[sql.attrNum].attrValueStr=yystack.l_mark[0].strVal;
        sql.condCont[sql.attrNum].attrType="CHAR";
    }
}
break;
case 24:
#line 198 "interpreter.ypp"
	{
    if(sql.attrNum>31) {
        printf("Too many values!\n");
        yyparse();
    }
    else {
        sql.attrNum++;
        sql.condCont[sql.attrNum].attrValueFlo=(float)yystack.l_mark[0].intVal;
        sql.condCont[sql.attrNum].attrValueInt=yystack.l_mark[0].intVal;
        sql.condCont[sql.attrNum].attrType="INT";
    }
}
break;
case 25:
#line 210 "interpreter.ypp"
	{
    if(sql.attrNum>31) {
        printf("Too many values!\n");
        yyparse();
    }
    else {
        sql.attrNum++;
        sql.condCont[sql.attrNum].attrValueFlo=yystack.l_mark[0].flVal;
        sql.condCont[sql.attrNum].attrType="FLOAT";
    }
}
break;
case 26:
#line 223 "interpreter.ypp"
	{ }
break;
case 27:
#line 224 "interpreter.ypp"
	{;}
break;
case 30:
#line 229 "interpreter.ypp"
	{ }
break;
case 31:
#line 230 "interpreter.ypp"
	{;}
break;
case 32:
#line 231 "interpreter.ypp"
	{;}
break;
case 33:
#line 233 "interpreter.ypp"
	{;}
break;
case 34:
#line 234 "interpreter.ypp"
	{;}
break;
case 35:
#line 238 "interpreter.ypp"
	{
    sql.condNum++;
    sql.condCont[sql.condNum].attrName=tmpAttrName;
    sql.condCont[sql.condNum].op=yystack.l_mark[-1].strVal;
    sql.condCont[sql.condNum].attrValueFlo=yystack.l_mark[0].flVal;
    sql.condCont[sql.condNum].attrType="FLOAT";
}
break;
case 36:
#line 246 "interpreter.ypp"
	{
    sql.condNum++;
    sql.condCont[sql.condNum].attrName=tmpAttrName;
    sql.condCont[sql.condNum].op=yystack.l_mark[-1].strVal;
    sql.condCont[sql.condNum].attrValueStr=yystack.l_mark[0].strVal;
    sql.condCont[sql.condNum].attrType="CHAR";
}
break;
case 37:
#line 254 "interpreter.ypp"
	{
    sql.condNum++;
    sql.condCont[sql.condNum].attrName=tmpAttrName;
    sql.condCont[sql.condNum].op=yystack.l_mark[-1].strVal;
    sql.condCont[sql.condNum].attrValueFlo=yystack.l_mark[0].intVal;
    sql.condCont[sql.condNum].attrValueInt=yystack.l_mark[0].intVal;
    sql.condCont[sql.condNum].attrType="INT";
}
break;
case 38:
#line 262 "interpreter.ypp"
	{;}
break;
case 39:
#line 265 "interpreter.ypp"
	{strcpy(yyval.strVal,">=");}
break;
case 40:
#line 266 "interpreter.ypp"
	{strcpy(yyval.strVal,"<=");}
break;
case 41:
#line 267 "interpreter.ypp"
	{strcpy(yyval.strVal,"<>");}
break;
case 42:
#line 268 "interpreter.ypp"
	{strcpy(yyval.strVal,"<");}
break;
case 43:
#line 269 "interpreter.ypp"
	{strcpy(yyval.strVal,">");}
break;
case 44:
#line 270 "interpreter.ypp"
	{strcpy(yyval.strVal,"=");}
break;
case 45:
#line 272 "interpreter.ypp"
	{yyval.flVal=yystack.l_mark[0].intVal;}
break;
case 46:
#line 273 "interpreter.ypp"
	{yyval.flVal=yystack.l_mark[0].flVal;}
break;
case 47:
#line 275 "interpreter.ypp"
	{
    sql.tableName=yystack.l_mark[0].id;
    tableInfo.tableName=yystack.l_mark[0].id;
}
break;
case 49:
#line 283 "interpreter.ypp"
	{printf("creating...");}
break;
case 55:
#line 294 "interpreter.ypp"
	{
    if(tableInfo.attrNum<32) {
        tableInfo.attrNum++;
        tableInfo.attrName[tableInfo.attrNum-1]=yystack.l_mark[0].id;
    }
    else {
        yyerror("Too many attributes!");
        tableInfo.reset();
        yyparse();
    }
}
break;
case 56:
#line 305 "interpreter.ypp"
	{
    tmpAttrName=yystack.l_mark[0].id;
    sql.attrName=yystack.l_mark[0].id;
}
break;
case 57:
#line 311 "interpreter.ypp"
	{
    tableInfo.attrType[tableInfo.attrNum-1]="int";
}
break;
case 58:
#line 314 "interpreter.ypp"
	{
    if (yystack.l_mark[-1].intVal>255 || yystack.l_mark[-1].intVal<1) {
        yyerror("Char is defined too long or too short!");
        tableInfo.reset();
        yyparse();
    }
    else
        tableInfo.attrType[tableInfo.attrNum-1]="char("+to_string(yystack.l_mark[-1].intVal)+")";
}
break;
case 59:
#line 323 "interpreter.ypp"
	{
    tableInfo.attrType[tableInfo.attrNum-1]="float";
}
break;
case 60:
#line 327 "interpreter.ypp"
	{ }
break;
case 61:
#line 329 "interpreter.ypp"
	{
    tableInfo.primaryKey=yystack.l_mark[0].id;
}
break;
case 62:
#line 333 "interpreter.ypp"
	{
    tableInfo.attrUnique[tableInfo.attrNum-1]='Y';
}
break;
case 63:
#line 340 "interpreter.ypp"
	{;}
break;
case 64:
#line 342 "interpreter.ypp"
	{;}
break;
case 65:
#line 344 "interpreter.ypp"
	{
    sql.indexName=yystack.l_mark[0].id;
}
break;
#line 1007 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
