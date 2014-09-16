exp: lexer.c lexer.h exp_flex.c
	clang -o exp lexer.c exp_flex.c

lexer.c: exp.ll
	flex -DYY_DECL="Token * yylex()" exp.ll

lexer.h: exp.ll
	flex -DYY_DECL="Token * yylex()" exp.ll

clean:
	rm -f exp 
	rm -f lexer.c lexer.h
	rm -f *.o 
