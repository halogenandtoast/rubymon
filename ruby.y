%{
#include "vm.h"
#include <stdio.h>
void yyerror(VM* vm, const char* error) {
  fprintf(stderr, "Error: %s", error);
}
extern int yylex();
%}

%right '='
%left '+' '-'
%left '*' '/'

%union {
  int num;
  char* str;
}

%token<num> NUMBER TERM LPAREN RPAREN
%token<str> ID

%type<num> program statements statement expression opt_term

%parse-param { VM* vm };

%start program

%%
program: statements opt_term

statements: statements TERM statement
          | statement
          ;

statement: ID expression { printf("%d\n", $2); }
         | ID '=' expression { printf("assign: %s => %d", $1, $3); }
         | expression
         ;

expression: expression '+' expression { $$ = $1 + $3;; }
          | expression '-' expression { $$ = $1 - $3; }
          | expression '*' expression { $$ = $1 * $3; }
          | expression '/' expression { $$ = $1 / $3; }
          | LPAREN expression RPAREN { $$ = $2; }
          | NUMBER { $$ = $1; }
          ;

opt_term: TERM
        |
        ;

%%
