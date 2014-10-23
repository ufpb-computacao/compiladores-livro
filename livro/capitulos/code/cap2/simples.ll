%option noyywrap 

CPF [0-9]{3}\.[0-9]{3}\.[0-9]{3}-[0-9]{2}
EMAIL [[:alnum:]\._]+@[[:alnum:]]+\.[[:alnum:]]+

%%

{CPF}   { printf("CPF\n"); }
{EMAIL} { printf("EMAIL\n"); }
.       { printf("Caractere nao reconhecido\n"); }

%%

// funcao principal que chama o analisador
int main()
{
  yylex();
}
