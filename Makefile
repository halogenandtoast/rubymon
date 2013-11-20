all: ruby

ruby: main.c y.tab.c lex.yy.c vm.c hash.c string.c fixnum.c
	cc main.c vm.c y.tab.c lex.yy.c hash.c string.c fixnum.c -o ruby -ggdb -O0 -g3 -fno-inline

y.tab.c: ruby.y
	yacc -d ruby.y

lex.yy.c: ruby.l
	lex ruby.l

clean:
	rm ruby y.tab.c y.tab.h lex.yy.c
