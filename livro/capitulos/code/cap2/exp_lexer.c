// 
// exp_lexer.c
// Analisador lexico para linguagem de expressoes aritmeticas
//
// Andrei de Araujo Formiga, 2014-07-25
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// --- definicao de constantes e tipos -----------------------------

// constantes booleanas
#define TRUE            1
#define FALSE           0

// constantes para tipo de token
#define TOK_NUM         0 
#define TOK_OP          1
#define TOK_PONT        2

// constantes para valores de operadores
#define SOMA            0
#define SUB             1
#define MULT            2
#define DIV             3

// constantes para valores de pontuacao (parenteses)
#define PARESQ          0
#define PARDIR          1

// estrutura que representa um token
typedef struct 
{
  int tipo;
  int valor;
} Token; 


// --- variaveis globais -------------------------------------------

// string contendo os caracteres de operadores
const char *ops = "+-*/";

// string que contem o codigo que esta em analise
char *codigo;

// tamanho da string com o codigo
int tamanho;

// guarda posicao atual no codigo
int pos;


// --- funcoes -----------------------------------------------------

// funcao utilitaria para obter proximo caractere do codigo 
// retorna -1 quando chega ao final da string
char le_caractere(void)
{
  char c;

  if (pos < tamanho) {
    c = codigo[pos];
    pos++;
  }
  else
    c = -1;

  return c;
}

// determina se um caractere eh um operador, e retorna o tipo se for
int operador(char c)
{
  int res; 

  switch (c) {
  case '+':
    res = SOMA;
    break;
    
  case '-':
    res = SUB;
    break;

  case '*':
    res = MULT;
    break;

  case '/':
    res = DIV;
    break;

  default:
    res = -1;
  }

  return res;
}

// inicializa a analise lexica do codigo em uma string
void inicializa_analise(char *prog)
{
  codigo = prog;
  tamanho = strlen(codigo);
  pos = 0;
}

// funcao que faz a analise lexica, retornando o proximo token
Token *proximo_token(Token *tok)
{
  char c;
  char valor[200];    // string para obter valor de um numero
  int  vpos = 0;      // posicao na string de valor

  c = le_caractere();
  // pula todos os espacos em branco
  while (isspace(c)) {
    c = le_caractere();
  }

  if (isdigit(c)) {
    tok->tipo = TOK_NUM;
    valor[vpos++] = c;
    c = le_caractere();
    while (isdigit(c)) {
      valor[vpos++] = c;
      c = le_caractere();
    }
    // retorna o primeiro caractere que nao eh um digito
    // para ser lido como parte do proximo token
    pos--;
    // termina a string de valor com um caractere 0
    valor[vpos] = '\0';
    // converte string de valor para numero
    tok->valor = atoi(valor);
  }
  else if (strchr(ops, c) != NULL) {
    tok->tipo  = TOK_OP;
    tok->valor = operador(c);
  }
  else if (c == '(' || c == ')') {
    tok->tipo  = TOK_PONT;
    tok->valor = (c == '(' ? PARESQ : PARDIR);
  }
  else
    return NULL;

  return tok;
}

// imprime um token
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

  default:
    printf("TIPO DE TOKEN DESCONHECIOO\n");
  }
}


// --- funcao principal --------------------------------------------
int main(void)
{
  char  entrada[200];
  Token tok;

  printf("Analise Lexica para Expressoes\n");

  printf("Expressao: ");
  fgets(entrada, 200, stdin);

  inicializa_analise(entrada);

  printf("\n===== Analise =====\n");

  while (proximo_token(&tok) != NULL) {
    imprime_token(&tok);
  }

  printf("\n");

  return 0;
}

