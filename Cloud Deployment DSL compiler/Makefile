# Use classic lex/yacc commands
LEX=flex
YACC=yacc
CC=cc
CFLAGS=-O2 -Wall


all: cloudopt

y.tab.c y.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c: lexer.l y.tab.h
	$(LEX) lexer.l

cloudopt: y.tab.c lex.yy.c ast.c optimizer.c codegen.c main.c
	$(CC) $(CFLAGS) y.tab.c lex.yy.c ast.c optimizer.c codegen.c main.c -o cloudopt -ll

clean:
	rm -f y.tab.c y.tab.h lex.yy.c cloudopt *.o

.PHONY: all clean
