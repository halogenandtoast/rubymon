all: ruby

ruby: main.c y.tab.c lex.yy.c vm.c hash.c string.c
	cc main.c vm.c y.tab.c lex.yy.c hash.c string.c -o ruby -ggdb

y.tab.c: ruby.y
	yacc -d ruby.y

lex.yy.c: ruby.l
	lex ruby.l

clean:
	rm ruby y.tab.c y.tab.h lex.yy.c
