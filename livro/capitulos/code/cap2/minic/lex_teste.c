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
  // destroi tabelas
  destroi_tab_strings();
  destroi_tab_simbolos(); 

  // fecha arquivo de entrada
  fclose(yyin);
}

void imprime_token(Token *tok)
{
  char *tipo; 

  switch (tok->tipo) {
  case TOK_PCHAVE: 
    tipo = "palavra chave";
    break;

  case TOK_ID:
    tipo = "identificador";
    break;

  case TOK_NUM:
    tipo = "numero";
    break;

  case TOK_PONT:
    tipo = "pontuacao";
    break;

  case TOK_OP:
    tipo = "operador";
    break;

  case TOK_STRING:
    tipo = "string";
    break;

  case TOK_PROLOGO:
    tipo = "prologo";
    break;

  case TOK_ERRO:
    tipo = "erro";
    break;

  default:
    tipo = "desconhecido";
  }

  printf("Tipo: %s - Valor: %d\n", tipo, tok->valor);
}

int main(int argc, char **argv)
{
  Token *tok;

  if (argc < 2) {
    printf("Uso: mclex <arquivo>\n");
    return 0; 
  }

  inicializa_analise(argv[1]);

  tok = yylex();
  while (tok != NULL) {
    imprime_token(tok);
    tok = yylex();
  }

  finaliza_analise();

  return 0; 
}


