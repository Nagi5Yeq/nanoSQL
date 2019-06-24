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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {char *strVal;char *id;int intVal;float flVal;char *condition;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
