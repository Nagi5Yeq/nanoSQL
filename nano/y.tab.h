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
	INTO = 271,
	VALUES = 272,
	ON = 273,
	PRIMARY = 274,
	KEY = 275,
	INTT = 276,
	CHART = 277,
	FLOATT = 278,
	ANND = 279,
	UNEXPECTED = 280,
	WHITESPACE = 281,
	FEOF = 282,
	ERR = 283,
	STRING = 284,
	FILENAME = 285,
	identifier = 286,
	intnum = 287,
	fnum = 288,
	LE = 289,
	GE = 290,
	NE = 291
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
#define INTO 271
#define VALUES 272
#define ON 273
#define PRIMARY 274
#define KEY 275
#define INTT 276
#define CHART 277
#define FLOATT 278
#define ANND 279
#define UNEXPECTED 280
#define WHITESPACE 281
#define FEOF 282
#define ERR 283
#define STRING 284
#define FILENAME 285
#define identifier 286
#define intnum 287
#define fnum 288
#define LE 289
#define GE 290
#define NE 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 30 "interpreter.ypp" /* yacc.c:1909  */
	char *strVal; char *id; int intVal; float flVal; char *condition;

#line 129 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
