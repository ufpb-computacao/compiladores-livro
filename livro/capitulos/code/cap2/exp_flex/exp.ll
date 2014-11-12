%option noyywrap 
%option nodefault
%option outfile="lexer.c" header-file="lexer.h"

%top {
#include "exp_tokens.h"
}

NUM [0-9]+

%%

[[:space:]] { }  /* ignora espacos */

{NUM}   { return token(TOK_NUM,  atoi(yytext)); }
\+      { return token(TOK_OP,   SOMA);   }
-       { return token(TOK_OP,   SUB);    }
\*      { return token(TOK_OP,   MULT);   }
\/      { return token(TOK_OP,   DIV);    }
\(      { return token(TOK_PONT, PARESQ); }
\)      { return token(TOK_PONT, PARDIR); } 

.       { return token(TOK_ERRO, 0);      }  //  erro para
                                             // token desconhecido
%%

// variavel global para um token
Token tok;

Token * token(int tipo, int valor)
{
  tok.tipo = tipo;
  tok.valor = valor;
  return &tok;
}

