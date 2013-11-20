%{
#include "vm.h"
#include "fixnum.h"
#include "string.h"
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
  VALUE val;
}

%token<num> NUMBER TERM LPAREN RPAREN
%token<str> ID STR

%type<val> program statements statement expression id
%type<num> opt_term

%parse-param { VM* vm };
%error-verbose

%start program

%%
program: statements opt_term

statements: statements TERM statement
          | statement
          ;

statement: id expression { rb_print($2); $$ = Qnil; }
         | id '=' expression { $$ = rb_vm_store(vm, $1, $3); }
         | expression
         ;

expression: expression '+' expression { $$ = rb_fixnum_add($1, $3); }
          | expression '-' expression { $$ = rb_fixnum_sub($1, $3); }
          | expression '*' expression { $$ = rb_fixnum_mult($1, $3); }
          | expression '/' expression { $$ = rb_fixnum_div($1,$3); }
          | LPAREN expression RPAREN { $$ = $2; }
          | NUMBER { $$ = rb_fixnum_new($1); }
          | STR { $$ = rb_str_new($1); free($1); }
          | id { $$ = rb_vm_lookup(vm, $1); }
          ;

id: ID { $$ = rb_str_new($1); }
  ;

opt_term: TERM { ; }
        | {}
        ;

%%
