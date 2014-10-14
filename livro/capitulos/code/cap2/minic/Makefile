mclex: lexer.c lexer.h tabelas.c lex_teste.c
	gcc -o mclex lexer.c tabelas.c lex_teste.c

lexer.c: lex.ll
	flex -DYY_DECL="Token * yylex()" lex.ll

lexer.h: lex.ll
	flex -DYY_DECL="Token * yylex()" lex.ll

clean:
	rm -f mclex
	rm -f lexer.c lexer.h
	rm -f *.o 
