%{
#include "vm.h"
#include "y.tab.h"
#include <string.h>
%}

%option noyywrap

%%
"\""([^\"])*"\"" { memcpy(yylval.str, yytext + 1, yyleng - 2); yylval.str[yyleng -2] = '\0'; return STR; }
[a-z]+ { yylval.str = strdup(yytext); return ID; }
"(" { return LPAREN; }
")" { return RPAREN; }
[0-9]+ { yylval.num = atoi(yytext); return NUMBER; }
[\+] { return '+'; }
[\-] { return '-'; }
[\*] { return '*'; }
[/] { return '/'; }
[\=] { return '='; }
[\n] { return TERM; }
[\t ] { ; }
. { fprintf(stderr, "Invalid token: %s", yytext); exit(1); }
%%
