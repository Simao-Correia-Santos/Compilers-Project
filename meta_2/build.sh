#!/bin/sh
rm -f uccompiler lex.yy.c y.tab.c y.tab.h
yacc -d -v -t -g --report=all uccompiler.y
lex uccompiler.l
cc -o uccompiler lex.yy.c y.tab.c ast.c -Wall -Wno-unused-function
