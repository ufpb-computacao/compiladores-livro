//
// exp_flex.c
//
// Analisador lexico para expressoes usando flex
//
// Andrei de A. Formiga, 2014-09-01
//

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "exp_tokens.h"

// variavel global para o buffer 
YY_BUFFER_STATE buffer;

void inicializa_analise(char *str)
{
  buffer = yy_scan_string(str);
}

// obtem o proximo token ou NULL para fim de arquivo
Token *proximo_token() 
{
  return yylex();
}

void finaliza_analise()
{
  yy_delete_buffer(buffer);
}

char *operador_str(int op)
{
  char *res;

  switch (op) {
  case SOMA:
    res = "SOMA";
    break;

  case SUB:
    res = "SUB";
    break;

  case MULT:
    res = "MULT";
    break;

  case DIV:
    res = "DIV";
    break;

  default:
    res = "NENHUM";
  }

  return res;
}

void imprime_token(Token *tok)
{
  printf("Tipo: ");
  switch (tok->tipo) {
  case TOK_NUM:
    printf("Numero \t -- Valor: %d\n", tok->valor);
    break;

  case TOK_OP:
    printf("Operador \t -- Valor: %s\n", operador_str(tok->valor));
    break;

  case TOK_PONT:
    printf("Pontuacao  -- Valor: %s\n", (tok->valor == PARESQ ? "PARESQ" : "PARDIR"));
    break;

  case TOK_ERRO: 
    printf("Erro: token nao reconhecido!\n");
    break;

  default:
    printf("TIPO DE TOKEN DESCONHECIOO\n");
  }
}

// funcao principal
int main(int argc, char **argv)
{
  char  entrada[200];
  Token *tok;

  printf("Analise Lexica para Expressoes\n");

  printf("Expressao: ");
  fgets(entrada, 200, stdin);

  inicializa_analise(entrada);

  printf("\n===== Analise =====\n");

  tok = proximo_token();
  while (tok != NULL) {
    imprime_token(tok);
    tok = proximo_token();
  }

  printf("\n");

  return 0;
}

