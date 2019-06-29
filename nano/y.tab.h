/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
	  /* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
#undef DELETE
/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
	UNIQUE = 258,
	TABLE = 259,
	SELECT = 260,
	INSERT = 261,
	DROP = 262,
	DELETE = 263,
	INDEX = 264,
	QUIT = 265,
	EXECFILE = 266,
	FROM = 267,
	WHERE = 268,
	CREATE = 269,
	RESET = 270,
	COMMENT = 271,
	INTO = 272,
	VALUES = 273,
	ON = 274,
	PRIMARY = 275,
	KEY = 276,
	INTT = 277,
	CHART = 278,
	FLOATT = 279,
	ANND = 280,
	UNEXPECTED = 281,
	WHITESPACE = 282,
	FEOF = 283,
	ERR = 284,
	STRING = 285,
	FILENAME = 286,
	identifier = 287,
	intnum = 288,
	fnum = 289,
	LE = 290,
	GE = 291,
	NE = 292
};
#endif
/* Tokens.  */
#define UNIQUE 258
#define TABLE 259
#define SELECT 260
#define INSERT 261
#define DROP 262
#define DELETE 263
#define INDEX 264
#define QUIT 265
#define EXECFILE 266
#define FROM 267
#define WHERE 268
#define CREATE 269
#define RESET 270
#define COMMENT 271
#define INTO 272
#define VALUES 273
#define ON 274
#define PRIMARY 275
#define KEY 276
#define INTT 277
#define CHART 278
#define FLOATT 279
#define ANND 280
#define UNEXPECTED 281
#define WHITESPACE 282
#define FEOF 283
#define ERR 284
#define STRING 285
#define FILENAME 286
#define identifier 287
#define intnum 288
#define fnum 289
#define LE 290
#define GE 291
#define NE 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 30 "interpreter.ypp" /* yacc.c:1909  */
	char *strVal; char *id; int intVal; float flVal; char *condition;

#line 131 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
