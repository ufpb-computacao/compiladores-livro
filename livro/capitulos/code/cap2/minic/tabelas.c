//
// tabelas.c
//
// Tabela de strings e tabela de simbolos
//
// Andrei de A. Formiga, 2014-09-19
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes para tamanho das tabelas
#define MAX_STRINGS                     200
#define MAX_SIMBOLOS                    300

// Tabela de strings
char *strings[MAX_STRINGS]; 
int num_strings = 0; 

// Tabela de simbolos
char *simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;

// adiciona uma string na tabela de strings, removendo as aspas
// retorna o numero da string na tabela
int adiciona_string(char *str_asp)
{
  int tam = strlen(str_asp) - 1;  // tamanho da string (sem aspas, com \0)
  char *str;

  // verifica se tabela esta cheia
  if (num_strings > MAX_STRINGS) {
    fprintf(stderr, "Limite maximo de strings ultrapassado\n");
    exit(1);
  }

  // aloca espaco para a string
  str = (char*) malloc(tam);

  if (str == NULL) {
    fprintf(stderr, "Nao foi possivel alocar espaco para a string no. %d\n", num_strings);
    exit(1);
  }

  strncpy(str, str_asp + 1, tam);
  str[tam] = '\0';
  strings[num_strings] = str;
  return num_strings++;
}

void destroi_tab_strings()
{
  int i; 

  for (i = 0; i < num_strings; ++i) {
    free(strings[i]);
  }
}

// adiciona um identificador na tabela de simbolos, se ainda 
// nao estiver na tabela. se o identificador ja estiver na 
// tabela, retorna seu numero
int adiciona_simbolo(char *id)
{
  int i;
  char *simb;

  // busca pelo identificador na tabela atual
  for (i = 0; i < num_simbolos; ++i) { 
    if (strcmp(id, simbolos[i]) == 0)
      return i;   // se encontrou, retorna o indice
  }

  // verifica se tabela esta cheia 
  if (num_simbolos > MAX_SIMBOLOS) {
    fprintf(stderr, "Limite maximo de simbolos ultrapassado\n"); 
    exit(1);
  }

  // aloca espaco para o simbolo
  simb = (char*) malloc(strlen(id));

  if (simb == NULL) {
    fprintf(stderr, "Nao foi possivel alocar espaco para simbolo no. %d\n", num_simbolos);
    exit(1);
  }

  strcpy(simb, id); 
  simbolos[num_simbolos] = simb;
  return num_simbolos++;
}

void destroi_tab_simbolos()
{
  int i; 

  for (i = 0; i < num_simbolos; ++i) {
    free(simbolos[i]);
  }
}
