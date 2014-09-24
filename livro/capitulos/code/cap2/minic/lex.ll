
%option noyywrap 
%option nodefault
%option outfile="lexer.c" header-file="lexer.h"

%top {
#include "minic_tokens.h"
#include "tabelas.h"

// prototipo da funcao token
Token *token(int, int); 
}

NUM [0-9]+
ID [[:alpha:]]([[:alnum:]])*
STRING \"[^\"\n]*\"

%% 

[[:space:]]  {  }  /* ignora espacos em branco */
\/\/[^\n]*     {  }  /* elimina comentarios */

"#include <stdio.h>"  { return token(TOK_PROLOGO, 0); }

{STRING} { return token(TOK_STRING, adiciona_string(yytext)); } 

if       { return token(TOK_PCHAVE, PC_IF); } 
else     { return token(TOK_PCHAVE, PC_ELSE); }
while    { return token(TOK_PCHAVE, PC_WHILE); }
return   { return token(TOK_PCHAVE, PC_RETURN); }
printf   { return token(TOK_PCHAVE, PC_PRINTF); } 

{NUM}    { return token(TOK_NUM, atoi(yytext)); }
{ID}     { return token(TOK_ID, adiciona_simbolo(yytext)); }

\+       { return token(TOK_OP, SOMA);  }
-        { return token(TOK_OP, SUB);   }
\*       { return token(TOK_OP, MULT);  }
\/       { return token(TOK_OP, DIV);   }
\<       { return token(TOK_OP, MENOR); } 
==       { return token(TOK_OP, IGUAL); }
&&       { return token(TOK_OP, AND);   }
!        { return token(TOK_OP, NOT);   }
=        { return token(TOK_OP, ATRIB); }

\(       { return token(TOK_PONT, PARESQ); }
\)       { return token(TOK_PONT, PARDIR); }
\{       { return token(TOK_PONT, CHVESQ); }
\}       { return token(TOK_PONT, CHVDIR); }
,        { return token(TOK_PONT, VIRG);   }
;        { return token(TOK_PONT, PNTVIRG); }

.        { return token(TOK_ERRO, 0);  }

%% 

Token tok;

Token *token(int tipo, int valor)
{
  tok.tipo = tipo;
  tok.valor = valor;

  return &tok;
}

int main()
{
  Token *tok = yylex();

  printf("Tipo: %d -- Valor: %d\n", tok->tipo, tok->valor);

  while (tok->tipo != TOK_ID) {
    tok = yylex();
    printf("Tipo: %d -- Valor: %d\n", tok->tipo, tok->valor);
  }
  
  return 0;
}

