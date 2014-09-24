//
// lex_teste.c
//
// Teste do analisador lexico para linguagem Mini C
//
// Andrei de A. Formiga, 2014-09-21
//

#include <stdio.h>
#include <stdlib.h>

#include "minic_tokens.h"
#include "lexer.h"

void inicializa_analise(char *nome_arq)
{
  FILE *f = fopen(nome_arq, "r");

  if (f == NULL) { 
    fprintf(stderr, "Nao foi possivel abrir o arquivo de entrada: %s\n", nome_arq);
    exit(1);
  }

  yyin = f;
}

void finaliza_analise()
{
  fclose(yyin);
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("Uso: mclex <arquivo>\n");
    return 0; 
  }

  printf("Entrada: %s\n", argv[1]);

  return 0; 
}


